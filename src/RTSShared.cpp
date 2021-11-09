/**
 * Source: RivaTuner Statics Server SDK Samples
 * Original author: Unwinder
 * All rights belong to Unwinder
 */

#include "RTSShared.h"

int RTSSUpdateOSDEntry(const RTSSCrossConfig* config, const char* osdEntry) {
	// initially not updated successfully 
	int result = 1;
	char targetText[256];
	snprintf(targetText, sizeof(targetText), "<P=%d,%d><S=%d><C0=%02x%02x%02x%02x><C0>%s", 
		config->position[0], config->position[1], config->scale, 
		config->color[3], config->color[0], config->color[1], config->color[2], config->crosshair);
	//printw("sending %s\n", targetText);
	
	// write config to shared RTSS memory
	HANDLE sharedFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "RTSSSharedMemoryV2");
	if (sharedFile == NULL) {
		// file not available
		result = -1;
	} else {
		LPVOID sharedMap = MapViewOfFile(sharedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		RTSSharedMemory* sharedMem = (RTSSharedMemory*)sharedMap;
		
		if (sharedMem == NULL) {
			// mapping not successful
			result = -2;
		} else {
			if ((sharedMem->dwSignature == 'RTSS') &&
				(sharedMem->dwVersion >= 0x00020000)) {
				bool found = false;
				// write in two passes
				//1st pass : find previously captured OSD slot
				//2nd pass : otherwise find the first unused OSD slot and capture it
				for (int pass = 0; pass < 2; pass++) {
					for (int entry = 1; entry < sharedMem->dwOSDArrSize; entry++) {
						//allow primary OSD clients (i.e. EVGA Precision / MSI Afterburner) to use the first slot exclusively, so third party
						//applications start scanning the slots from the second one
						RTSSharedMemory::RTSSharedMemoryOSDEntry* pEntry = 
							(RTSSharedMemory::RTSSharedMemoryOSDEntry*)
							((LPBYTE)sharedMem + sharedMem->dwOSDArrOffset + entry * sharedMem->dwOSDEntrySize);

						if (pass > 0) {
							if (lstrlenA(pEntry->szOSDOwner) == 0) {
								lstrcpyA(pEntry->szOSDOwner, osdEntry);
							}
						}
						if (lstrcmpA(pEntry->szOSDOwner, osdEntry) == 0) {
							if (sharedMem->dwVersion >= 0x00020007) {
								//use extended text slot for v2.7 and higher shared memory, it allows displaying 4096 symbols
								//instead of 256 for regular text slot
								if (sharedMem->dwVersion >= 0x0002000e) {
									//OSD locking is supported on v2.14 and higher shared memory
									DWORD dwBusy = _interlockedbittestandset(&sharedMem->dwBusy, 0);
									//bit 0 of this variable will be set if OSD is locked by renderer and cannot be refreshed atm
									if (!dwBusy) {
										lstrcpynA(pEntry->szOSDEx, targetText, sizeof(pEntry->szOSDEx) - 1);
										sharedMem->dwBusy = 0;
									}
								} else {
									lstrcpynA(pEntry->szOSDEx, targetText, sizeof(pEntry->szOSDEx) - 1);
								}
							} else {
								lstrcpynA(pEntry->szOSD, targetText, sizeof(pEntry->szOSD) - 1);
							}
							sharedMem->dwOSDFrame++;
							found = true;
							result = 0;
							break;
						}
					}
					if (found) {
						break;
					}
				}
			} else {
				// not the correct signature
				result = -3;
			}
			UnmapViewOfFile(sharedMap);
		}
		CloseHandle(sharedFile);
	}
	return result;
}

int RTSSReleaseOSDEntry(const char* osdEntry) {
	// initially not released successfully
	int result = 1;
	// reset shared RTSS memory
	HANDLE sharedFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "RTSSSharedMemoryV2");
	if (sharedFile == NULL) {
		// file not available
		result = -1;
	} else {
		LPVOID sharedMap = MapViewOfFile(sharedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		RTSSharedMemory* sharedMem= (RTSSharedMemory*)sharedMap;
		if (sharedMem == NULL) {
			// mapping failed
			result = -2;
		} else {
			if ((sharedMem->dwSignature == 'RTSS') &&
				(sharedMem->dwVersion >= 0x00020000)) {
				for (int dwEntry = 1; dwEntry < sharedMem->dwOSDArrSize; dwEntry++) {
					RTSSharedMemory::RTSSharedMemoryOSDEntry* entry = 
						(RTSSharedMemory::RTSSharedMemoryOSDEntry*)
						((LPBYTE)sharedMem + sharedMem->dwOSDArrOffset + dwEntry * sharedMem->dwOSDEntrySize);
					// zero out claimed entry
					if (lstrcmpA(entry->szOSDOwner, osdEntry) == 0) {
						SecureZeroMemory(entry, sharedMem->dwOSDEntrySize);
						sharedMem->dwOSDFrame++;
						result = 0;
					}
				}
			} else {
				// wrong signature
				result = -3;
			}
			UnmapViewOfFile(sharedMem);
		}
		CloseHandle(sharedFile);
	}
	return result;
}