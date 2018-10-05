/*
	File:		StandardSound.h

	Contains:	Public interface to Standard Sound for Cathedral

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

*/


#ifndef __StandardSound__
#define __StandardSound__

#include "DSPManager.h"

//==========================================================================================
//	Patch Bay constants
//==========================================================================================
enum PatchPoint {kStdSndRecorder, kStdSndPreProcessor, kStdSndPlayer, kStdSndPostProcessor,
		kStdSndInput, kStdSndOutput};

//==========================================================================================
//	Default Sample Rates (Fixed samples/sec) and Frame Rates (Fixed milliseconds)
//==========================================================================================
#define kStdSnd24kHz 	0x5DC00000
#define kStdSnd32kHz 	0x7D000000
#define kStdSnd48kHz 	0xBB800000

#define kStdSnd5ms		0x00050000
#define kStdSnd10ms		0x000A0000

//==========================================================================================
//	Stream IDs
//==========================================================================================
#define kStdSndSystemStream			-1
#define kStdSndSystemInputStream	-2
#define kStdSndSystemOutputStream	-3

//==========================================================================================
//	Stream Status
//==========================================================================================

typedef enum {
	kStdSndStreamIsInactive,
	kStdSndStreamDontKnowIfActive,
	kStdSndStreamIsActive
} DSPStreamStatus;
	
//==========================================================================================
//	Structures
//==========================================================================================

typedef unsigned long SoundStream;

#ifndef __cplusplus
typedef enum PatchPoint PatchPoint;
typedef struct StdSndStreamInfo StdSndStreamInfo;
#endif

//==========================================================================================
//	Error Constants
//==========================================================================================
#define kStdSndErr						-750
#define kNoDSPManagerErr				-751
#define kNoDSPDeviceErr					-752
#define kOpenDeviceErr					-753
#define	kStdSndSampleRateNotAvailable	-754
#define	kStdSndFrameRateNotAvailable	-755
#define	kStdSndOptionNotAvailable		-756
#define kStdSndBadStream				-757
#define kStdSndBadIndex					-758
#define kStdSndBadInfoVersion			-759

//==========================================================================================
// misc dispatcher constants & macros
//==========================================================================================
#define kStdSndGetIndexedStream				128
#define kStdSndGetStreamCPUIndex			129
#define kStdSndInsertTask					130
#define kStdSndGetStreamSections			131
#define kStdSndTestSampleAndFrameRate		132
#define kStdSndSetSampleAndFrameRate		133
#define kStdSndGetStreamInfo				134
#define kStdSndRemoveTask					135
#define kStdSndGetSampleAndFrameRate		136

#define kStdSndSetInputGain					137
#define kStdSndSetOutputAttenuation			138
#define kStdSndGetInputGain					139
#define kStdSndGetOutputAttenuation			140
#define kStdSndGetSampleTime				141

#define kStdSndReserved1					142
#define kStdSndGetMonitorGain				143
#define kStdSndSetMonitorGain				144

#define kStdSndGetInputDeviceConnection		145
#define kStdSndSignInCPUDevice				146
#define kStdSndSignOutCPUDevice				147
#define kStdSndTaskChangingState			148
#define kStdSndGetStreamGivenTask			149
#define kStdSndOnlySystemTasks				150
#define kStdSndGetStreamOutputStatus		151
#define kStdSndGetDeviceInfo				152
#define kStdSndSetDeviceInfo				153

#define kInstallTasks						154
#define kInstallStream						155
#define kDSPLookupDeviceIndex				156
#define kStdSndSetSystemStream				157

#define kStdSndInfoVersion					1

struct StdSndStreamInfo {
	short			stVersion;			// Version of this info struct
	SoundStream		stStream;			// SoundStream to get info for
	PatchPoint		stPatchPoint;		// Patch point to get info for
	unsigned long	stFlags;			// Type flags
	Fixed			stFrameRate;		// Frame rate in milliseconds
	Fixed			stSampleRate;		// Sample rate in samples/sec
	unsigned long	stTime;				// Time in samples
	unsigned short	stCPUDeviceIndex;	// Device index for this patch point
	Str31			stName;				// Name of this Stream
	Handle			stICON;				// Icon of the Stream
};
typedef StdSndStreamInfo *StdSndStreamInfoPtr;

pascal OSErr StdSndGetIndexedStream(SoundStream *theStream, long index)
	   = DSPDispatch(kStdSndGetIndexedStream)

pascal OSErr StdSndGetStreamCPUIndex(SoundStream theStream, PatchPoint patchPoint, unsigned short *cpuDeviceIndex)
	   = DSPDispatch(kStdSndGetStreamCPUIndex)

pascal OSErr StdSndGetStreamInfo(StdSndStreamInfoPtr theSI)
	   = DSPDispatch(kStdSndGetStreamInfo)

pascal OSErr StdSndInsertTask(SoundStream theStream, DSPTaskRefNum theTask, PatchPoint patchPoint)
	   = DSPDispatch(kStdSndInsertTask)

pascal OSErr StdSndRemoveTask(SoundStream theStream, DSPTaskRefNum theTask, PatchPoint patchPoint)
	   = DSPDispatch(kStdSndRemoveTask)

pascal OSErr StdSndGetStreamSections(SoundStream theStream, DSPSectionRefNum *leftChannel, DSPSectionRefNum *rightChannel)
	   = DSPDispatch(kStdSndGetStreamSections)

pascal OSErr StdSndTestSampleAndFrameRate(SoundStream theStream, Fixed frame, Fixed sample)
	   = DSPDispatch(kStdSndTestSampleAndFrameRate)

pascal OSErr StdSndSetSampleAndFrameRate(SoundStream theStream, Fixed frame, Fixed sample)
	   = DSPDispatch(kStdSndSetSampleAndFrameRate)

pascal OSErr StdSndGetSampleAndFrameRate(SoundStream theStream, Fixed *frame, Fixed *sample)
	   = DSPDispatch(kStdSndGetSampleAndFrameRate)

pascal OSErr StdSndSetInputGain(SoundStream theStream, unsigned long leftGain, unsigned long rightGain)
	   = DSPDispatch(kStdSndSetInputGain)

pascal OSErr StdSndSetOutputAttenuation(SoundStream theStream, unsigned long leftAttenuation, unsigned long rightAttenuation)
	   = DSPDispatch(kStdSndSetOutputAttenuation)

pascal OSErr StdSndGetInputGain(SoundStream theStream, unsigned long *leftGain, unsigned long *rightGain)
	   = DSPDispatch(kStdSndGetInputGain)

pascal OSErr StdSndGetOutputAttenuation(SoundStream theStream, unsigned long *leftAttenuation, unsigned long *rightAttenuation)
	   = DSPDispatch(kStdSndGetOutputAttenuation)

pascal OSErr StdSndGetSampleTime(SoundStream theStream, unsigned long *time)
	   = DSPDispatch(kStdSndGetSampleTime)

pascal OSErr StdSndGetMonitorGain(SoundStream theStream, Fixed *leftGain, Fixed *rightGain)
	   = DSPDispatch(kStdSndGetMonitorGain)

pascal OSErr StdSndSetMonitorGain(SoundStream theStream, Fixed leftGain, Fixed rightGain)
	   = DSPDispatch(kStdSndSetMonitorGain)

pascal OSErr StdSndGetInputDeviceConnection(SoundStream theStream, short *deviceStatus)
	   = DSPDispatch(kStdSndGetInputDeviceConnection)

pascal OSErr StdSndGetStreamOutputStatus(SoundStream theStream, DSPStreamStatus *streamStatus)
	   = DSPDispatch(kStdSndGetStreamOutputStatus)

pascal OSErr StdSndGetDeviceInfo(SoundStream theStream, OSType infoType, Ptr infoData)
	   = DSPDispatch(kStdSndGetDeviceInfo)
	   
pascal OSErr StdSndSetDeviceInfo(SoundStream theStream, OSType infoType, Ptr infoData)
	   = DSPDispatch(kStdSndSetDeviceInfo)
#endif
