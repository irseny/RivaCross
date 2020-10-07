/**
 * Source: RivaTuner Statics Server SDK Samples
 * Original author: Unwinder
 * All rights belong to Unwinder
 */

#include "RTSShared.h"

int RTSSUpdateOSDEntry(const RTSSCrossConfig* config, const char* osdEntry) {
	// initially not updated successfully 
	int result = 0x0;
	char targetText[256];
	snprintf(targetText, sizeof(targetText), "<P=%d,%d><S=%d><C0=%02x%02x%02x><C0>%s<P=0,0>", 
		config->position[0], config->position[1], config->scale, 
		config->color[0], config->color[1], config->color[2], config->crosshair);
	//printw("sending %s\n", targetText);
	
	// write config to shared RTSS memory
	HANDLE sharedFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "RTSSSharedMemoryV2");
	if (sharedFile != NULL) {
		LPVOID sharedMap = MapViewOfFile(sharedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		RTSSharedMemory* sharedMem = (RTSSharedMemory*)sharedMap;
		if (sharedMem != NULL) {
			if ((sharedMem->dwSignature == 'RTSS') &&
				(sharedMem->dwVersion >= 0x00020000)) {
				
				char entryNames[2][256] = {
					"RTSS_Crosshair_Overlay",
					"RTSS_Crosshair_Placeholder"
				};
				for (int iName = 0; iName < 2; iName++) {
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

							if (pass) {
								if (lstrlenA(pEntry->szOSDOwner) == 0) {
									lstrcpyA(pEntry->szOSDOwner, entryNames[iName]);
								}
							}
							if (lstrcmpA(pEntry->szOSDOwner, entryNames[iName]) == 0) {
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
								result |= 0x1<<iName;
								break;
							}
						}
						if (found) {
							break;
						}
					}
				}
			}
			UnmapViewOfFile(sharedMap);
		}
		CloseHandle(sharedFile);
	}
	return result >= 0x3;
}

int RTSSReleaseOSDEntry(const char* osdEntry) {
	// initially not released successfully
	int reset = 0x0;
	// reset shared RTSS memory
	HANDLE sharedFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "RTSSSharedMemoryV2");
	if (sharedFile != NULL) {
		LPVOID sharedMap = MapViewOfFile(sharedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		RTSSharedMemory* sharedMem= (RTSSharedMemory*)sharedMap;
		if (sharedMem != NULL) {
			if ((sharedMem->dwSignature == 'RTSS') &&
				(sharedMem->dwVersion >= 0x00020000)) {
				for (int dwEntry = 1; dwEntry < sharedMem->dwOSDArrSize; dwEntry++)
				{
					RTSSharedMemory::RTSSharedMemoryOSDEntry* entry = 
						(RTSSharedMemory::RTSSharedMemoryOSDEntry*)
						((LPBYTE)sharedMem + sharedMem->dwOSDArrOffset + dwEntry * sharedMem->dwOSDEntrySize);					
					// zero placeholder and overlay entries
					if (lstrcmpA(entry->szOSDOwner, "RTSS_Crosshair_Placeholder") == 0) {
						SecureZeroMemory(entry, sharedMem->dwOSDEntrySize);
						sharedMem->dwOSDFrame++;
						reset |= 0x1;
					}
					if (lstrcmpA(entry->szOSDOwner, "RTSS_Crosshair_Overlay") == 0) {
						SecureZeroMemory(entry, sharedMem->dwOSDEntrySize);
						sharedMem->dwOSDFrame++;
						reset |= 0x2;
					}
				}
			}
			UnmapViewOfFile(sharedMem);
		}
		CloseHandle(sharedFile);
	}
	return reset >= 0x3;
}