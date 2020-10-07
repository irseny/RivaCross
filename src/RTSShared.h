/**
 * Source: RivaTuner Statics Server SDK Samples
 * Original author: Unwinder
 * All rights belong to Unwinder
 */

#pragma once

#include "stdafx.h"

typedef struct {
	DWORD	dwVersion;
	char	szFilename[MAX_PATH];
	DWORD	dwFramerate;
	DWORD	dwFramesize;
	DWORD	dwFormat;
	DWORD	dwQuality;
	DWORD	dwThreads;
	BOOL	bCaptureOSD;
	DWORD	dwAudioCaptureFlags;
	DWORD	dwVideoCaptureFlagsEx;
	DWORD	dwAudioCaptureFlags2;
	DWORD	dwPrerecordSizeLimit;
	DWORD	dwPrerecordTimeLimit;
} RTSSVideoCaptureParam;

typedef struct RTSSharedMemoryV10 {
	DWORD	dwSignature;
		//signature allows applications to verify status of shared memory

		//The signature can be set to:
		//'RTSS'	- statistics server's memory is initialized and contains 
		//			valid data 
		//0xDEAD	- statistics server's memory is marked for deallocation and
		//			no longer contain valid data
		//otherwise	the memory is not initialized
	DWORD	dwVersion;
		//structure version ((major<<16) + minor)
		//must be set to 0x00010000 for v1.0 structure
	DWORD	dwTime0;
		//start time of framerate measurement period (in milliseconds)

		//Take a note that this field must contain non-zero value to calculate 
		//framerate properly!
	DWORD	dwTime1;
		//end time of framerate measurement period (in milliseconds)
	DWORD	dwFrames;
		//amount of frames rendered during (dwTime1 - dwTime0) period 

		//to calculate framerate use the following formula:
		//1000.0f * dwFrames / (dwTime1 - dwTime0)

} RTSSharedMemoryV10;

typedef struct RTSSharedMemoryV11 {
	DWORD	dwSignature;
		//signature allows applications to verify status of shared memory

		//The signature can be set to:
		//'RTSS'	- statistics server's memory is initialized and contains 
		//			valid data 
		//0xDEAD	- statistics server's memory is marked for deallocation and
		//			no longer contain valid data
		//otherwise	the memory is not initialized
	DWORD	dwVersion;
		//structure version ((major<<16) + minor)
		//must be set to 0x00010001 for v1.1 structure
	DWORD	dwTime0;
		//start time of framerate measurement period (in milliseconds)

		//Take a note that this field must contain non-zero value to calculate 
		//framerate properly!
	DWORD	dwTime1;
		//end time of framerate measurement period (in milliseconds)
	DWORD	dwFrames;
		//amount of frames rendered during (dwTime1 - dwTime0) period

		//to calculate framerate use the following formula:
		//1000.0f * dwFrames / (dwTime1 - dwTime0)

	DWORD	dwOSDFlags;
		//bitmask, containing combination of OSDFLAG_... flags

		//Note: set OSDFLAG_UPDATED flag as soon as you change any OSD related
		//field
	DWORD	dwOSDX;
		//OSD X-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the right side of the screen)
	DWORD	dwOSDY;
		//OSD Y-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the bottom side of the screen)
	DWORD	dwOSDPixel;
		//OSD pixel zooming ratio
	DWORD	dwOSDColor;
		//OSD color in RGB format
	char	szOSD[256];
		//OSD text
	char	szOSDOwner[32];
		//OSD owner ID

		//Use this field to capture OSD and prevent other applications from
		//using OSD when it is already in use by your application.
		//You should change this field only if it is empty (i.e. when OSD is
		//not owned by any application) or if it is set to your own application's
		//ID (i.e. when you own OSD)
		//You shouldn't change any OSD related feilds until you own OSD

} RTSSharedMemoryV11;

typedef struct RTSSharedMemoryV12 {
	DWORD	dwSignature;
		//signature allows applications to verify status of shared memory

		//The signature can be set to:
		//'RTSS'	- statistics server's memory is initialized and contains 
		//			valid data 
		//0xDEAD	- statistics server's memory is marked for deallocation and
		//			no longer contain valid data
		//otherwise	the memory is not initialized
	DWORD	dwVersion;
		//structure version ((major<<16) + minor)
		//must be set to 0x00010002 for v1.2 structure
	DWORD	dwTime0;
		//start time of framerate measurement period (in milliseconds)

		//Take a note that this field must contain non-zero value to calculate 
		//framerate properly!
	DWORD	dwTime1;
		//end time of framerate measurement period (in milliseconds)
	DWORD	dwFrames;
		//amount of frames rendered during (dwTime1 - dwTime0) period

		//to calculate framerate use the following formula:
		//1000.0f * dwFrames / (dwTime1 - dwTime0)

	DWORD	dwOSDFlags;
		//bitmask, containing combination of OSDFLAG_... flags

		//Note: set OSDFLAG_UPDATED flag as soon as you change any OSD related
		//field
	DWORD	dwOSDX;
		//OSD X-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the right side of the screen)
	DWORD	dwOSDY;
		//OSD Y-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the bottom side of the screen)
	DWORD	dwOSDPixel;
		//OSD pixel zooming ratio
	DWORD	dwOSDColor;
		//OSD color in RGB format
	char	szOSD[256];
		//primary OSD slot text
	char	szOSDOwner[32];
		//primary OSD slot owner ID

		//Use this field to capture OSD slot and prevent other applications from
		//using OSD when it is already in use by your application.
		//You should change this field only if it is empty (i.e. when OSD slot is
		//not owned by any application) or if it is set to your own application's
		//ID (i.e. when you own OSD slot)
		//You shouldn't change any OSD related feilds until you own OSD slot

	char	szOSD1[256];
		//OSD slot 1 text
	char	szOSD1Owner[32];
		//OSD slot 1 owner ID
	char	szOSD2[256];
		//OSD slot 2 text
	char	szOSD2Owner[32];
		//OSD slot 2 owner ID
	char	szOSD3[256];
		//OSD slot 3 text
	char	szOSD3Owner[32];
		//OSD slot 3 owner ID
} RTSSharedMemoryV12;

typedef struct RTSSharedMemoryV13 {
	DWORD	dwSignature;
		//signature allows applications to verify status of shared memory

		//The signature can be set to:
		//'RTSS'	- statistics server's memory is initialized and contains 
		//			valid data 
		//0xDEAD	- statistics server's memory is marked for deallocation and
		//			no longer contain valid data
		//otherwise	the memory is not initialized
	DWORD	dwVersion;
		//structure version ((major<<16) + minor)
		//must be set to 0x00010003 for v1.3 structure
	DWORD	dwTime0;
		//start time of framerate measurement period (in milliseconds)

		//Take a note that this field must contain non-zero value to calculate 
		//framerate properly!
	DWORD	dwTime1;
		//end time of framerate measurement period (in milliseconds)
	DWORD	dwFrames;
		//amount of frames rendered during (dwTime1 - dwTime0) period

		//to calculate framerate use the following formula:
		//1000.0f * dwFrames / (dwTime1 - dwTime0)

	DWORD	dwOSDFlags;
		//bitmask, containing combination of OSDFLAG_... flags

		//Note: set OSDFLAG_UPDATED flag as soon as you change any OSD related
		//field
	DWORD	dwOSDX;
		//OSD X-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the right side of the screen)
	DWORD	dwOSDY;
		//OSD Y-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
		//pixel offset from the bottom side of the screen)
	DWORD	dwOSDPixel;
		//OSD pixel zooming ratio
	DWORD	dwOSDColor;
		//OSD color in RGB format
	char	szOSD[256];
		//primary OSD slot text
	char	szOSDOwner[32];
		//primary OSD slot owner ID

		//Use this field to capture OSD slot and prevent other applications from
		//using OSD when it is already in use by your application.
		//You should change this field only if it is empty (i.e. when OSD slot is
		//not owned by any application) or if it is set to your own application's
		//ID (i.e. when you own OSD slot)
		//You shouldn't change any OSD related feilds until you own OSD slot

	char	szOSD1[256];
		//OSD slot 1 text
	char	szOSD1Owner[32];
		//OSD slot 1 owner ID
	char	szOSD2[256];
		//OSD slot 2 text
	char	szOSD2Owner[32];
		//OSD slot 2 owner ID
	char	szOSD3[256];
		//OSD slot 3 text
	char	szOSD3Owner[32];
		//OSD slot 3 owner ID

	DWORD	dwStatFlags;
		//bitmask containing combination of STATFLAG_... flags
	DWORD	dwStatTime0;
		//statistics record period start time
	DWORD	dwStatTime1;
		//statistics record period end time
	DWORD	dwStatFrames;
		//total amount of frames rendered during statistics record period
	DWORD	dwStatCount;
		//amount of min/avg/max measurements during statistics record period 
	DWORD	dwStatFramerateMin;
		//minimum instantaneous framerate measured during statistics record period 
	DWORD	dwStatFramerateAvg;
		//average instantaneous framerate measured during statistics record period 
	DWORD	dwStatFramerateMax;
		//maximum instantaneous framerate measured during statistics record period 
} RTSSharedMemoryV13;

typedef struct RTSSharedMemory {
	DWORD	dwSignature;
		//signature allows applications to verify status of shared memory

		//The signature can be set to:
		//'RTSS'	- statistics server's memory is initialized and contains 
		//			valid data 
		//0xDEAD	- statistics server's memory is marked for deallocation and
		//			no longer contain valid data
		//otherwise	the memory is not initialized
	DWORD	dwVersion;
		//structure version ((major<<16) + minor)
		//must be set to 0x0002xxxx for v2.x structure 

	DWORD	dwAppEntrySize;
		//size of RTSS_SHARED_MEMORY_OSD_ENTRY for compatibility with future versions
	DWORD	dwAppArrOffset;
		//offset of arrOSD array for compatibility with future versions
	DWORD	dwAppArrSize;
		//size of arrOSD array for compatibility with future versions

	DWORD	dwOSDEntrySize;
		//size of RTSS_SHARED_MEMORY_APP_ENTRY for compatibility with future versions
	DWORD	dwOSDArrOffset;
		//offset of arrApp array for compatibility with future versions
	DWORD	dwOSDArrSize;
		//size of arrOSD array for compatibility with future versions

	DWORD	dwOSDFrame;
		//Global OSD frame ID. Increment it to force the server to update OSD for all currently active 3D
		//applications.

	//next fields are valid for v2.14 and newer shared memory format only

	LONG dwBusy;
		//set bit 0 when you're writing to shared memory and reset it when done

		//WARNING: do not forget to reset it, otherwise you'll completely lock OSD updates for all clients


	//next fields are valid for v2.15 and newer shared memory format only

	DWORD dwDesktopVideoCaptureFlags;
	DWORD dwDesktopVideoCaptureStat[5];
		//shared copy of desktop video capture flags and performance stats for 64-bit applications

	//OSD slot descriptor structure

	typedef struct RTSSharedMemoryOSDEntry {
		char	szOSD[256];
			//OSD slot text
		char	szOSDOwner[256];
			//OSD slot owner ID

		//next fields are valid for v2.7 and newer shared memory format only

		char	szOSDEx[4096];
			//extended OSD slot text

		//next fields are valid for v2.12 and newer shared memory format only

		BYTE	buffer[262144];
			//OSD slot data buffer

	} RTSSharedMemoryOSDEntry;

	//application descriptor structure

	typedef struct RTSSharedMemoryAppEntry {
		//application identification related fields

		DWORD	dwProcessID;
			//process ID
		char	szName[MAX_PATH];
			//process executable name
		DWORD	dwFlags;
			//application specific flags

		//instantaneous framerate related fields

		DWORD	dwTime0;
			//start time of framerate measurement period (in milliseconds)

			//Take a note that this field must contain non-zero value to calculate 
			//framerate properly!
		DWORD	dwTime1;
			//end time of framerate measurement period (in milliseconds)
		DWORD	dwFrames;
			//amount of frames rendered during (dwTime1 - dwTime0) period
		DWORD	dwFrameTime;
			//frame time (in microseconds)
			//to calculate framerate use the following formulas:
			//1000.0f * dwFrames / (dwTime1 - dwTime0) for framerate calculated once per second
			//or
			//1000000.0f / dwFrameTime for framerate calculated once per frame 
			
		//framerate statistics related fields
		DWORD	dwStatFlags;
			//bitmask containing combination of STATFLAG_... flags
		DWORD	dwStatTime0;
			//statistics record period start time
		DWORD	dwStatTime1;
			//statistics record period end time
		DWORD	dwStatFrames;
			//total amount of frames rendered during statistics record period
		DWORD	dwStatCount;
			//amount of min/avg/max measurements during statistics record period 
		DWORD	dwStatFramerateMin;
			//minimum instantaneous framerate measured during statistics record period 
		DWORD	dwStatFramerateAvg;
			//average instantaneous framerate measured during statistics record period 
		DWORD	dwStatFramerateMax;
			//maximum instantaneous framerate measured during statistics record period 

		//OSD related fields
		DWORD	dwOSDX;
			//OSD X-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
			//pixel offset from the right side of the screen)
		DWORD	dwOSDY;
			//OSD Y-coordinate (coordinate wrapping is allowed, i.e. -5 defines 5
			//pixel offset from the bottom side of the screen)
		DWORD	dwOSDPixel;
			//OSD pixel zooming ratio
		DWORD	dwOSDColor;
			//OSD color in RGB format
		DWORD	dwOSDFrame;
			//application specific OSD frame ID. Don't change it directly!
		DWORD	dwScreenCaptureFlags;
		char	szScreenCapturePath[MAX_PATH];
		
		//next fields are valid for v2.1 and newer shared memory format only
		DWORD	dwOSDBgndColor;
			//OSD background color in RGB format

		//next fields are valid for v2.2 and newer shared memory format only
		DWORD	dwVideoCaptureFlags;
		char	szVideoCapturePath[MAX_PATH];
		DWORD	dwVideoFramerate;
		DWORD	dwVideoFramesize;
		DWORD	dwVideoFormat;
		DWORD	dwVideoQuality;
		DWORD	dwVideoCaptureThreads;

		DWORD	dwScreenCaptureQuality;
		DWORD	dwScreenCaptureThreads;

		//next fields are valid for v2.3 and newer shared memory format only

		DWORD	dwAudioCaptureFlags;

		//next fields are valid for v2.4 and newer shared memory format only

		DWORD	dwVideoCaptureFlagsEx;

		//next fields are valid for v2.5 and newer shared memory format only

		DWORD	dwAudioCaptureFlags2;

		DWORD	dwStatFrameTimeMin;
		DWORD	dwStatFrameTimeAvg;
		DWORD	dwStatFrameTimeMax;
		DWORD	dwStatFrameTimeCount;

		DWORD	dwStatFrameTimeBuf[1024];
		DWORD	dwStatFrameTimeBufPos;
		DWORD	dwStatFrameTimeBufFramerate;

		//next fields are valid for v2.6 and newer shared memory format only

		LARGE_INTEGER qwAudioCapturePTTEventPush;
		LARGE_INTEGER qwAudioCapturePTTEventRelease;

		LARGE_INTEGER qwAudioCapturePTTEventPush2;
		LARGE_INTEGER qwAudioCapturePTTEventRelease2;

		//next fields are valid for v2.8 and newer shared memory format only

		DWORD	dwPrerecordSizeLimit;
		DWORD	dwPrerecordTimeLimit;

		//next fields are valid for v2.13 and newer shared memory format only

		LARGE_INTEGER qwStatTotalTime;
		DWORD	dwStatFrameTimeLowBuf[1024];
		DWORD	dwStatFramerate1Dot0PercentLow;
		DWORD	dwStatFramerate0Dot1PercentLow;

	} RTSSharedMemoryAppEntry;

	//WARNING: next fields should never (!!!) be accessed directly, use the offsets to access them in order to provide 
	//compatibility with future versions

	RTSSharedMemoryOSDEntry arrOSD[8];
		//array of OSD slots
	RTSSharedMemoryAppEntry arrApp[256];
		//array of application descriptors

	//next fields are valid for v2.9 and newer shared memory format only

	//WARNING: due to design flaw there is no offset available for this field, so it must be calculated manually as
	//dwAppArrOffset + dwAppArrSize * dwAppEntrySize

	RTSSVideoCaptureParam autoVideoCaptureParam;		

} RTSSharedMemory;

typedef struct {
	HANDLE hMapFile;
	RTSSharedMemory* pMem;
} RTSSThreadParam;

typedef struct RTSSEmbeddedObject {
	DWORD dwSignature;
		//embedded object signature
	DWORD dwSize;
		//embedded object size in bytes
	LONG dwWidth;
		//embedded object width in pixels (if positive) or in chars (if negative)
	LONG dwHeight;
		//embedded object height in pixels (if positive) or in chars (if negative)
	LONG dwMargin;
		//embedded object margin in pixels
} RTSSEmbeddedObject;

typedef struct RTSSEmbeddedObjectGraph {
	RTSSEmbeddedObject header;
	DWORD dwFlags;
		//bitmask containing RTSS_EMBEDDED_OBJECT_GRAPH_FLAG_XXX flags
	FLOAT fltMin;
		//graph mininum value
	FLOAT fltMax;	
		//graph maximum value
	DWORD dwDataCount;
		//count of data samples in fltData array
	FLOAT fltData[0];
		//graph data samples array

} RTSSEmbeddedObjectGraph;

typedef struct RTSSCrossConfig {
	char crosshair[64]; // crosshair text
	int position[2]; // position on screen (coordinate system determined by RTSS)
	unsigned int scale; // crosshair size (usage depends on RTSS configuration)
	unsigned char color[3]; // color in RGB format
} RTSSCrossConfig;

int RTSSUpdateOSDEntry(const RTSSCrossConfig* config, const char* osdEntry);
int RTSSReleaseOSDEntry(const char* osdEntry);


