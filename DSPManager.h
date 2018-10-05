/*
	File:		DSPManager.h

	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

*/

//======================================================================================
#ifndef __DSPManager__
#define __DSPManager__
#include <types.h>

//--------------------------------------------------------------------------------------
// DSPManager Version Number
//
// 0x09 	changes DSPNewTask & DSPInsertTask
// 0x0A HBS DSPIODevice calls now require a iopbDeviceType to be passed in the parameter
//			block
// 0x0B APS Changed DSPModule Structure
// 0x0C APS FIFO API changed.
// 0x0D	APS	FIFO API Changed again (Linked FIFOs Rev. 4)
//--------------------------------------------------------------------------------------
#define kdspManagerBuildVersion		0x0000000D

//======================================================================================
// 							N E W  D A T A  T Y P E S
//======================================================================================
typedef unsigned long	DSPPosition;			// type for position parameter
typedef unsigned long 	DSPCycles;				// type for processing bandwidth
typedef unsigned long	DSPClientRefNum;		// type for DSPClient reference number
typedef unsigned long	DSPIODeviceRefNum;		// type for DSPIODevice reference number
typedef unsigned long	DSPCPUDeviceRefNum;		// type for DSPCPUDevice reference number
typedef unsigned long	DSPTaskRefNum;			// type for DSPTask reference number
typedef unsigned long	DSPModuleRefNum;		// type for DSPModule reference number
typedef unsigned long	DSPSectionRefNum;		// type for DSPSection reference number
typedef unsigned long	DSPFIFORefNum;			// type for DSPFIFO reference number
typedef unsigned long	DSPLinkedFIFORefNum;	// type for DSPLinkedFIFO reference number
typedef unsigned long	DSPSynchRefNum;			// type for TaskToSynch and SynchTasks reference number
typedef pascal void (*MessageActionProc)(struct DSPMessage *theMessage);

enum DSPConnectionType {
	kdspDirectConnection,
	kdspIndirectConnection,
	kdspHIHOConnection
};

enum DSPTaskPriority {
	kdspRealTime,
	kdspTimeShare
};

typedef enum { 
	kdspTaskIsActive, 
	kdspTaskIsInactive, 
	kdspTaskIsGoingInactive, 
	kdspTaskIsGoingActive, 
	kdspInvalidTask 
} DSPTaskStatus;

#ifndef __cplusplus
typedef struct	DSPDeviceParamBlk		DSPDeviceParamBlk;
typedef struct	DSPCPUDeviceParamBlk	DSPCPUDeviceParamBlk;
typedef struct	DSPIODeviceParamBlk		DSPIODeviceParamBlk;
typedef struct	DSPBIODeviceParamBlk	DSPBIODeviceParamBlk;
typedef	struct	DSPSIODeviceParamBlk	DSPSIODeviceParamBlk;
typedef struct	DSPFIFO					DSPFIFO;
typedef struct	DSPFIFOAddress			DSPFIFOAddress;
typedef struct	DSPMessage				DSPMessage;
typedef struct	DSPClientInfoParamBlk	DSPClientInfoParamBlk;
typedef struct	DSPTaskInfoParamBlk		DSPTaskInfoParamBlk;
typedef struct	DSPModuleInfoParamBlk	DSPModuleInfoParamBlk;
typedef struct	DSPSectionInfoParamBlk	DSPSectionInfoParamBlk;
typedef struct	DSPGPBModeIndicator		DSPGPBModeIndicator;
typedef enum	DSPConnectionType		DSPConnectionType;
typedef enum	DSPTaskPriority			DSPTaskPriority;
#endif

//======================================================================================
// 								S T R U C T U R E S
//======================================================================================
//======================================================================================
// DSPFIFOAddress
//======================================================================================
struct DSPFIFOAddress {
	struct DSPFIFO *l;			// logical pointer
	struct DSPFIFO *p;			// physical pointer
	};

//======================================================================================
// DSPParamBlkHeader
//		this parameter block header is shared between the DSPIODeviceParamblock
//		and the DSPCPUDeviceParamBlk. The reason we declare things this way is so that
//		we can have routines that operate only on the common parts of the structures
//		therefore making the code smaller, easier to write, easier to maintain, etc…
//
//		pbhDeviceIndex			the index for this device
//		pbhClientPermission		read/write permission for this client
//		pbhClientRefNum			the reference number for this client
//		pbhClientName			the name of this client
//		pbhDeviceName			the device name for the io or cpu device
//		pbhDeviceICON			the device icon for the io or cpu device
//
//======================================================================================
#define DSPDeviceParamBlkHeader\
	unsigned short			pbhDeviceIndex;\
	unsigned short			pbhClientPermission;\
	DSPClientRefNum			pbhClientRefNum;\
	Str31					pbhClientName;\
	Handle					pbhClientICON;\
	Str31					pbhDeviceName;\
	Handle					pbhDeviceICON;

//======================================================================================
// DSPDeviceParamBlk:
//======================================================================================
struct DSPDeviceParamBlk {
	DSPDeviceParamBlkHeader
	};

//======================================================================================
// DSPCPUDeviceParamBlk:
//		this parameter block is used for controlling a cpu device. It shares the
//		DSPParamBlkHeader with the io device.
//======================================================================================
struct DSPCPUDeviceParamBlk {
	DSPDeviceParamBlkHeader
	unsigned char		cpuSlotNumber;			// the slot number the card is in
	unsigned char		cpuProcessorNumber;		// the processor number, zero based
	OSType				cpuProcessorType;		// the type of the processor
	DSPCycles			cpuMaxCycles;			// max processor execution cycles per frame
	DSPCycles			cpuAllocatedCycles;		// num cycles currently allocated
	DSPCycles			cpuCurRealTimeLoading;	// num cycles used during the last frame
	DSPCycles			cpuTimeShareLoading;	// num cycles it took for time share list
	DSPCycles			cpuTimeShareFreq;		// how often the timeshare list is run
	Fixed				cpuFrameRate;			// num frames per second for this cpu device
	MessageActionProc	cpuClientMessageActionProc;
	unsigned long		cpuClientRefCon;
	};
	
//======================================================================================
// DSPIODeviceParamBlk
//		this parameter block is used for controlling a io device. It shares the 
//		DSPParamBlkHeader with the cpu device.
//======================================================================================
struct DSPIODeviceParamBlk {
	DSPDeviceParamBlkHeader
	unsigned short			iopbIODeviceIndex;	// index of this io device
	unsigned short			iopbIODeviceType;	// type of this io device
	unsigned char			iopbReserved[32];	// data specific to the io device
	};

struct DSPBIODeviceParamBlk {
	DSPDeviceParamBlkHeader
	unsigned short			iopbIODeviceIndex;	// index of this io device
	unsigned short			iopbIODeviceType;	// type  of this io device
	struct DSPMessage		*bioMessageHandler;	// gets called when state of bio pin changes
	unsigned char			bioPinState;		// 0 level low, 1 = logic level high
	unsigned char			bioPinDirection;	// 0 = input only, 1 = output only
	unsigned char			bioPinIntEnable;	// 0 = interrupt masked, 1 = interrupt enabled
	unsigned char			bioReserved[25];	// reserved space
	};

struct DSPSIODeviceParamBlk {
	DSPDeviceParamBlkHeader
	unsigned short			iopbIODeviceIndex;	// index of this io device
	unsigned short			iopbIODeviceType;	// type of this io device
	Fixed					sioSampleRate;		// sample rate for this io device, rate is for both input and output
	unsigned long			sioSampleFormat;	// sample size for this io device, size is for both input and output
	DSPFIFOAddress			sioInputFIFO;		// pass the physical pointer to your dsp code
	DSPFIFOAddress			sioOutputFIFO;		// pass the physical pointer to your dsp code
	unsigned char			sioDMAEnable;		// 0 = off, 1 = on, enables both input and output
	unsigned char			sioFeatures;		// contains bit that indicates if it can be used for standard sound etc…
	unsigned char			sioReserved[6];		// reserved space
	};
	

//======================================================================================
// DSPBandwidth: is used to represent guaranteed processing bandwidth 
// information.
//======================================================================================
struct DSPBandwidth {							// bn = ba-ndwidth
	DSPCycles				bnEstimate;			// worst case pre-runtime
	DSPCycles				bnActual;			// worst case runtime
	unsigned long			bnFlags;			// control flags
	};


//======================================================================================
// DSPMessage: used for passing messages back and forth between the kernel and the driver.
//======================================================================================
struct DSPMessage {
	MessageActionProc		msVector;			// vector of routine
	unsigned long			msData[3];			// application specific data
	};
	
//======================================================================================
// DSPGPBModeIndicator: used for requesting more (or less) GPB when a module is running.
//======================================================================================
struct DSPGPBModeIndicator {
	unsigned short		miCurrentMode;			// Mode in which the module is operating 
												// (only the DSP code should change this)
	unsigned short		miNextMode;				// (only the DSP Manager should change this value)
	};

//======================================================================================
//  “G E T   I N F O”   M E S S A G E   P A R A M   B L O C K S
//======================================================================================
//--------------------------------------------------------------------------------------
// DSPClientInfoParamBlk
//		this parameter block is used for getting information on a client that is
//		signed in to the DSPManager.
//--------------------------------------------------------------------------------------
struct DSPClientInfoParamBlk {
	DSPClientRefNum			ciClientRefNum;		// Returned ref num of the client
	unsigned short			ciClientPermission;	// Returned read/write permission of the client
	Handle					ciClientICON;		// Returned icon of the client
	Str31					ciClientName;		// Returned name of the client
	};

//--------------------------------------------------------------------------------------
// DSPTaskInfoParamBlk
//		this parameter block is used for getting information on a task that is
//		installed on the DSP.
//--------------------------------------------------------------------------------------
struct DSPTaskInfoParamBlk {
	DSPTaskRefNum			tiRefNum;			// Returned reference number for this task
	unsigned long			tiRefCon;			// Returned application specific long
	MessageActionProc		tiVector;			// Returned Vector of task action proc
	unsigned long			tiFlags;			// Returned flags for DSPTask control
	Str31					tiName;				// Returned name of this DSPTask
	};

//--------------------------------------------------------------------------------------
// DSPModuleInfoParamBlk
//		this parameter block is used for getting information on a module that is
//		installed on the DSP.
//--------------------------------------------------------------------------------------
struct DSPModuleInfoParamBlk {
	DSPModuleRefNum			miRefNum;			// Returned reference number of this module
	struct DSPBandwidth		miGPB;				// Returned guaranteed processing bandwidth
	unsigned long			miFlags;			// Returned module flags
	unsigned long			miNumSections;		// Returned number of sections in module
	Str31					miName;				// Returned name of DSPModule
	unsigned long			miExecutions;		// Returned number of executions
	unsigned long			miSkipCount;		// Returned number of modules to skip
	};

//--------------------------------------------------------------------------------------
// DSPSectionInfoParamBlk
//		this parameter block is used for getting information on a section that is
//		installed on the DSP.
//--------------------------------------------------------------------------------------
struct DSPSectionInfoParamBlk {
	DSPSectionRefNum		siRefNum;			// Returned reference number for this section
	unsigned long			siSize;				// Returned size of data in actual section
	unsigned long			siFlags;			// Returned section flags
	unsigned long			siType;				// Returned for section connection type checking
	Str31					siName;				// Returned name of this section
	Ptr						siPrimary;			// Returned current location of section data
	Ptr						siSecondary;		// Returned optional section data storage location
	DSPSectionRefNum		siPrevSection;		// Returned Previous Connection
	DSPSectionRefNum		siNextSection;		// Returned Next Connection
	DSPFIFORefNum			siFIFORefNum;		// Returned RefNum of the FIFO
	Ptr						siPrimaryPhys;		// Returned current physical location of section data
	Ptr						siSecondaryPhys;	// Returned optional physical section data storage location
	};
	
	
//======================================================================================
// 				A D D I T I O N A L  S T R U C T U R E  D A T A  T Y P E S 
//======================================================================================
typedef	DSPCPUDeviceParamBlk	*DSPCPUDeviceParamBlkPtr,	**DSPCPUDeviceParamBlkHandle;
typedef	DSPIODeviceParamBlk		*DSPIODeviceParamBlkPtr,	**DSPIODeviceParamBlkHandle;
typedef	DSPBIODeviceParamBlk	*DSPBIODeviceParamBlkPtr,	**DSPBIODeviceParamBlkHandle;
typedef	DSPSIODeviceParamBlk	*DSPSIODeviceParamBlkPtr,	**DSPSIODeviceParamBlkHandle;
typedef	DSPClientInfoParamBlk	*DSPClientInfoParamBlkPtr,	**DSPClientInfoParamBlkHandle;
typedef	DSPTaskInfoParamBlk		*DSPTaskInfoParamBlkPtr,	**DSPTaskInfoParamBlkHandle;
typedef	DSPModuleInfoParamBlk	*DSPModuleInfoParamBlkPtr,	**DSPModuleInfoParamBlkHandle;
typedef	DSPSectionInfoParamBlk	*DSPSectionInfoParamBlkPtr,	**DSPSectionInfoParamBlkHandle;
typedef DSPGPBModeIndicator		*DSPGPBModeIndicatorPtr,	**DSPGPBModeIndicatorHandle;

#ifndef __cplusplus
typedef	DSPMessage				*DSPMessagePtr,			**DSPMessageHandle;
#else
typedef	unsigned long			*DSPMessagePtr,			**DSPMessageHandle;
#endif

//======================================================================================
// 					D S P  M A N A G E R  T R A P  D I S P A T C H E R
//======================================================================================
//======================================================================================
// misc dispatcher constants & macros
//======================================================================================
#define	_DSPDispatch						0xABF5
#define	MOVEL								0x303C
#define	DSPDispatch(select)					{MOVEL,select,_DSPDispatch};

//======================================================================================
// dispatch selectors for external calls
//======================================================================================
#define kdspGetTrapAddress					0
#define kdspSetTrapAddress					1
#define kdspGetIndexedCPUDevice				2
#define kdspOpenCPUDevice					3
#define kdspCloseCPUDevice					4
#define kdspGetIndexedCPUDeviceOption		5
#define kdspSetIndexedCPUDeviceOption		6
#define kdspGetIndexedIODevice				7
#define kdspOpenIODevice					8
#define kdspCloseIODevice					9
#define kdspGetIndexedIODeviceOption		10
#define kdspSetIndexedIODeviceOption		11
#define kdspSignInCPUDevice					12
#define kdspSignOutCPUDevice				13
#define kdspSignInIODevice					14
#define kdspSignOutIODevice					15
#define kdspLoadModule						16
#define kdspUnloadModule					17
#define kdspConnectSections					18
#define kdspNewInterTaskBuffer				19
#define kdspNewTask							20
#define kdspDisposeTask						21
#define kdspInsertTask						22
#define kdspManagerVersion					23
#define kdspRemoveTask						24
#define kdspTaskToSynchronize				25
#define kdspAddressInZone					26			// 4/16/92 JDB. Ripped out SynchronizeDevice
#define kdspSynchronizeTasks				27
#define kdspSetTaskActive					28
#define kdspSetTaskInactive					29
#define kdspCreateZone						30
#define kdspNewAddress						31
#define kdspDisposeAddress					32
#define kdspGetAddressSize					33
#define kdspGetZoneSize						34
#define kdspGetAddress						35
#define kdspGetZone							36
#define kdspInsertDouble					37
#define kdspRemoveDouble					38
#define kdspInsertSingle					39
#define kdspRemoveSingle					40
#define kdspGetSection						41
#define kdspNewFIFO							42
#define kdspDisposeFIFO						43
#define kdspGetSectionData					44
#define kdspFIFORead						45
#define	kdspFIFOWrite						46
#define	kdspFIFOGetReadCount				47
#define	kdspFIFOGetWriteCount				48
#define	kdspFIFOGetSize						49
#define kdspCreateModule					50
#define kdspInsertModule					51
#define kdspDisposeModule					52
#define kdspRemoveModule					53
#define kdspGetClientZone					54
#define kdspNewStorage						55
#define kdspAllocateStorage					56
#define kdspUnreserveStorage				57
#define kdspDeallocateStorage				58
#define kdspDisposeStorage					59
#define kdspProcessMessages					60
#define kdspFIFOClearInterrupt				61
#define kdspFIFOGetRefCon					62
#define kdspFIFOSetRefCon					63
#define kdspFIFOGetMessageMode				64
#define kdspFIFOSetMessageMode				65
#define kdspFIFOReset						66
#define kdspSetTaskRefCon					67
#define kdspGetTaskRefCon					68
#define kdspGetIndexedClient				69
#define kdspGetIndexedTask					70
#define kdspGetOwnerClient					71
#define kdspGetIndexedModule				72
#define kdspGetOwnerTask					73
#define kdspGetIndexedSection				74
#define kdspGetOwnerModule					75
#define kdspGetClientInfo					76
#define kdspGetTaskInfo						77
#define kdspGetModuleInfo					78
#define kdspGetSectionInfo					79
#define kdspConnectITBSections				80
#define kdspConnectTwoFIFOSections			81
#define kdspConnectFIFOToAIAOSections		82
#define kdspConnectFIFOSections				83
#define kdspConnectRegularSections			84
#define kdspAllocate						85
#define kdspUpdateCPUDeviceInfo				86
#define	kdspDisposeOneFIFO					87
#define	kdspFIFOSwap						88
#define kdspCountModule						89
#define kdspDontCountModule					90
#define kdspSetSkipCount					91
#define kdspGetTaskStatus					92
#define kdspSetCPUDeviceBondage				93
#define kdspFIFOGetMessageDispatch			94
#define kdspUpdateGPBPrefFile				95
#define kdspFIFOSetMessageThreshold			96
#define kdspSetGPBMode						97
#define kdspDontUpdateGPBPrefs				98
#define kdspUpdateGPBPreferenceFile			99
#define kdspConnectHIHOSections				100
#define kdspDisposeZone						101
#define kdspClientMessageDispatch			102
#define kdspFIFOGetMessageActionProc		103
#define kdspFIFOSetMessageActionProc		104
#define kdspSetSystemTask					105
#define kdspGetAvailableOnChipMemory		106
#define kdspSetSectionSize					107
#define kdspGetPtrSize						108
#define kdspAllocateDriverFIFO				109
#define kdspDisposeDriverFIFO				110
#define kdspPatchPrevAndNext				111
#define kdspSetUpLowAndHighPointerFromTask	112
#define kdspAllocateSharedSections			113
#define kdspAllocateSection					114
#define kdspAllocateModule					115
#define kdspNewStorageSection				116
#define kdspClientRefNumToDSPClientPtr		117
#define kdspGetDeviceRefNum					118
#define kdspAddClient						119
#define kdspRemoveClient					120
#define kdspGetCPUDeviceGivenIndex			121
#define kdspGetIODeviceGivenIndex			122
#define kdspUpdateIODeviceParamBlk			123
#define kdspGetTaskGivenSectionTable		124
#define kdspGetExceptionNotification		125
#define kdspCPUDeviceRefNumToDevicePtr		126
#define kdspConfigureSlaveDevice			127

//•••••••••••• 128-255 are for Standard Sound •••••••••

#define kdspGetCPUDeviceGivenRefNum			256
#define kdspGetIODeviceGivenRefNum			257
#define kdspGetFIFOPtr						258
#define kdspGetMaxCycles					259
#define kdspGetUsedCycles					260
#define kdspCyclesInTask					261
#define kdspNewPhysicalPtr					262
#define kdspDisposePhysicalPtr				263
#define kdspVMPresent						264
#define kdspGetDSPZone						265
#define kdspComputePhysical					266
#define kdspCleanUpZone						267
#define kdspLogicalToPhysical				268
#define kdspSectionStructPtr2RefNum			269
#define kdspSectionRefNum2StructPtr			270
#define kdspAttachAddrFixups				271
#define kdspTryToCacheVanillaProgram		272
#define kdspConvertDSPFtoDSPModule			273
#define kdspGetTaskPtr						274
#define kdspGetModulePtr					275
#define kdspGetSectionPtr					276
#define kdspCheckTask						277
#define kdspPatchOneAddress					278
#define kdspPatchAllAddresses				279
#define kdspSetUpTask						280
#define kdspTaskGetMessageDispatch			281
#define kdspGetOverrunNotification			282
#define kdspCheckHIHOConnections			283
#define kdspPowerManager					284
#define kdspConvertFrameRate				285
#define kdspAllocateSegment					286
#define kdspLoadKernel						287
#define kdspConnectIndirectSections			288
#define kdspGetGPBModes						289
#define kdspDeviceCall						290
#define kdspDriverCall						291
#define kdspGetResource						292
#define kdspCreateAliasToResfile			293
#define kdspRebootCPUDevice					294
#define kdspLoadSlotDrivers					295
#define kdspGetTimeShareLoading				296

//======================================================================================
// DSP Manager dispatched traps (external only)
//======================================================================================
pascal OSErr DSPGetIndexedCPUDevice (DSPCPUDeviceParamBlkPtr theCPUParamBlk)
		= DSPDispatch(kdspGetIndexedCPUDevice)
pascal OSErr DSPOpenCPUDevice (DSPCPUDeviceParamBlkPtr theCPUParamBlk)
		= DSPDispatch(kdspOpenCPUDevice)
pascal OSErr DSPCloseCPUDevice (DSPCPUDeviceParamBlkPtr theCPUParamBlk)
		= DSPDispatch(kdspCloseCPUDevice)
pascal OSErr DSPUpdateCPUDeviceInfo (DSPCPUDeviceParamBlkPtr theCPUParamBlk)
		= DSPDispatch(kdspUpdateCPUDeviceInfo)
pascal OSErr DSPGetIndexedCPUDeviceOption (DSPCPUDeviceParamBlkPtr theCPUParamBlk, 
		unsigned short theOptionIndex, OSType theOptionType, unsigned long *theOption)
		= DSPDispatch(kdspGetIndexedCPUDeviceOption)
pascal OSErr DSPSetIndexedCPUDeviceOption (DSPCPUDeviceParamBlkPtr theCPUParamBlk, 
		unsigned short theOptionIndex, OSType theOptionType)
		= DSPDispatch(kdspSetIndexedCPUDeviceOption)
pascal OSErr DSPGetIndexedIODevice (DSPIODeviceParamBlkPtr theIOParamBlk)
		= DSPDispatch(kdspGetIndexedIODevice)
pascal OSErr DSPOpenIODevice (DSPIODeviceParamBlkPtr theIOParamBlk)
		= DSPDispatch(kdspOpenIODevice)
pascal OSErr DSPCloseIODevice (DSPIODeviceParamBlkPtr theIOParamBlk)
		= DSPDispatch(kdspCloseIODevice)
pascal OSErr DSPGetIndexedIODeviceOption (DSPIODeviceParamBlkPtr theIOParamBlk, 
		unsigned short theOptionIndex, OSType theOptionType, unsigned long *theOption)
		= DSPDispatch(kdspGetIndexedIODeviceOption)
pascal OSErr DSPSetIndexedIODeviceOption (DSPIODeviceParamBlkPtr theIOParamBlk, 
		unsigned short theOptionIndex, OSType theOptionType)
		= DSPDispatch(kdspSetIndexedIODeviceOption)
pascal OSErr DSPLoadModule(	StringPtr theName, DSPTaskRefNum theTaskRefNum, 
		DSPPosition thePosition, DSPModuleRefNum theReferenceModuleRefNum, 
		DSPModuleRefNum *theNewModuleRefNum, long theScale )
		= DSPDispatch(kdspLoadModule)
pascal OSErr DSPUnloadModule( DSPTaskRefNum theTaskRefNum, 
		DSPModuleRefNum theModuleRefNum )
		= DSPDispatch(kdspUnloadModule)
pascal OSErr DSPConnectSections ( DSPSectionRefNum sectionOneRefNum, 
		DSPSectionRefNum sectionTwoRefNum, DSPConnectionType theConnectionType )
		= DSPDispatch(kdspConnectSections)
pascal OSErr DSPNewInterTaskBuffer ( DSPTaskRefNum theTaskRefNum, 
		unsigned long theSize, unsigned short theDataType, 
		Str31 theInterTaskBufferName, short bankPreference, 
		DSPSectionRefNum *theReturnedSection )
		= DSPDispatch(kdspNewInterTaskBuffer)
pascal OSErr DSPNewTask( DSPCPUDeviceParamBlkPtr theCPUDevice, 
		MessageActionProc theVector, StringPtr theTaskName, DSPTaskRefNum *theRefNum )
		= DSPDispatch(kdspNewTask)
pascal OSErr DSPDisposeTask( DSPTaskRefNum theTaskRefNum )
		= DSPDispatch(kdspDisposeTask)
pascal OSErr DSPInsertTask( DSPCPUDeviceParamBlkPtr theCPUDevice, 
		DSPTaskRefNum theNewTaskRefNum, DSPPosition thePosition, 
		DSPTaskPriority interruptLevel, DSPTaskRefNum theRelativeTaskRefNum )
		= DSPDispatch(kdspInsertTask)
pascal OSErr DSPRemoveTask( DSPTaskRefNum theTaskRefNum )
		= DSPDispatch(kdspRemoveTask)
pascal OSErr DSPTaskToSynchronize(DSPTaskRefNum theRefNum, unsigned long frameDelay, DSPSynchRefNum *synchRefNum)
		= DSPDispatch(kdspTaskToSynchronize)
pascal OSErr DSPSynchronizeTasks( DSPSynchRefNum *synchRefNum )
		= DSPDispatch(kdspSynchronizeTasks)
pascal OSErr DSPSetTaskActive (DSPTaskRefNum theRefNum)
		= DSPDispatch(kdspSetTaskActive)
pascal OSErr DSPSetTaskInactive (DSPTaskRefNum theRefNum)
		= DSPDispatch(kdspSetTaskInactive)
pascal OSErr DSPGetSection( DSPModuleRefNum theModuleRefNum, 
		StringPtr theSectionName, DSPSectionRefNum *theSectionRefNum )
		= DSPDispatch(kdspGetSection)
pascal OSErr DSPNewFIFO (DSPSectionRefNum theSectionRefNum, 
		DSPFIFORefNum *theFIFORefNum, unsigned long theSize, 
		Ptr logical, Ptr physical, Boolean fifoFull,
		MessageActionProc theInterrupt)
		= DSPDispatch(kdspNewFIFO)
pascal OSErr DSPDisposeFIFO (DSPSectionRefNum theSectionRefNum)
		= DSPDispatch(kdspDisposeFIFO)
pascal OSErr DSPGetSectionData (DSPSectionRefNum theSectionRefNum, Ptr *theData)
		= DSPDispatch(kdspGetSectionData)
pascal unsigned long DSPFIFORead (DSPFIFORefNum theFIFORefNum, Ptr theDestination, 
		unsigned long theCount)
		= DSPDispatch(kdspFIFORead)
pascal unsigned long DSPFIFOWrite (DSPFIFORefNum theFIFORefNum, Ptr theSource, 
		unsigned long theCount)
		= DSPDispatch(kdspFIFOWrite)
pascal unsigned long DSPFIFOGetReadCount (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOGetReadCount)
pascal unsigned long DSPFIFOGetWriteCount (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOGetWriteCount)
pascal unsigned long DSPFIFOGetSize (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOGetSize)
pascal OSErr DSPFIFOClearInterrupt (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOClearInterrupt)
pascal unsigned long DSPFIFOGetRefCon (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOGetRefCon)
pascal OSErr DSPFIFOSetRefCon (DSPFIFORefNum theFIFORefNum, unsigned long theValue)
		= DSPDispatch(kdspFIFOSetRefCon)
pascal unsigned long DSPFIFOGetMessageMode (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOGetMessageMode)
pascal OSErr DSPFIFOSetMessageMode (DSPFIFORefNum theFIFORefNum, 
		unsigned long theFlags)
		= DSPDispatch(kdspFIFOSetMessageMode)
pascal unsigned long DSPManagerVersion(void)
		= DSPDispatch(kdspManagerVersion)
pascal OSErr DSPFIFOReset (DSPFIFORefNum theFIFORefNum)
		= DSPDispatch(kdspFIFOReset)
pascal OSErr DSPSetTaskRefCon (DSPTaskRefNum theRefNum, unsigned long theData)
		= DSPDispatch(kdspSetTaskRefCon)
pascal unsigned long DSPGetTaskRefCon (DSPTaskRefNum theRefNum)
		= DSPDispatch(kdspGetTaskRefCon)
pascal OSErr DSPGetIndexedClient (unsigned long theIndex, DSPCPUDeviceParamBlkPtr theCPUDevice, DSPClientRefNum *theClientRefNum)
		= DSPDispatch(kdspGetIndexedClient)
pascal OSErr DSPGetIndexedTask (unsigned long theIndex, DSPTaskPriority interruptLevel, DSPCPUDeviceParamBlkPtr theCPUDevice, DSPTaskRefNum	*theTaskRefNum)
		= DSPDispatch(kdspGetIndexedTask)
pascal OSErr DSPGetOwnerClient (DSPTaskRefNum theTaskRefNum, DSPClientRefNum *theClientRefNum)
		= DSPDispatch(kdspGetOwnerClient)
pascal OSErr DSPGetIndexedModule (unsigned long theIndex, DSPTaskRefNum theTaskRefNum, DSPModuleRefNum *theModuleRefNum)
		= DSPDispatch(kdspGetIndexedModule)
pascal OSErr DSPGetOwnerTask (DSPModuleRefNum theModuleRefNum, DSPTaskRefNum *theTaskRefNum)
		= DSPDispatch(kdspGetOwnerTask)
pascal OSErr DSPGetIndexedSection (unsigned long theIndex, DSPModuleRefNum theModuleRefNum, DSPSectionRefNum *theSectionRefNum)
		= DSPDispatch(kdspGetIndexedSection)
pascal OSErr DSPGetOwnerModule (DSPSectionRefNum theSectionRefNum, DSPModuleRefNum *theModuleRefNum)
		= DSPDispatch(kdspGetOwnerModule)
pascal OSErr DSPGetClientInfo (DSPClientInfoParamBlkHandle theClientParamBlkHdl)
		= DSPDispatch(kdspGetClientInfo)
pascal OSErr DSPGetTaskInfo (DSPTaskInfoParamBlkHandle theTaskParamBlkHdl)
		= DSPDispatch(kdspGetTaskInfo)
pascal OSErr DSPGetModuleInfo (DSPModuleInfoParamBlkHandle theModuleParamBlkHdl)
		= DSPDispatch(kdspGetModuleInfo)
pascal OSErr DSPGetSectionInfo (DSPSectionInfoParamBlkHandle theSectionParamBlkHdl)
		= DSPDispatch(kdspGetSectionInfo)
pascal OSErr DSPCountModule(DSPModuleRefNum theModuleRefNum)
		= DSPDispatch(kdspCountModule)
pascal OSErr DSPDontCountModule(DSPModuleRefNum theModuleRefNum)
		= DSPDispatch(kdspDontCountModule)
pascal OSErr DSPSetSkipCount(DSPModuleRefNum theModuleRefNum, unsigned long theCount)
		= DSPDispatch(kdspSetSkipCount)
pascal DSPTaskStatus DSPGetTaskStatus(DSPTaskRefNum theRefNum)
		= DSPDispatch(kdspGetTaskStatus)
pascal OSErr DSPSetCPUDeviceBondage( DSPCPUDeviceParamBlkPtr cpuDevice1, DSPCPUDeviceParamBlkPtr cpuDevice2 )
		= DSPDispatch(kdspSetCPUDeviceBondage)
pascal OSErr DSPFIFOSetMessageThreshold(DSPFIFORefNum theFIFORefNum, unsigned long theThreshold)
		= DSPDispatch(kdspFIFOSetMessageThreshold)
pascal OSErr DSPFIFOSwap (DSPFIFORefNum theFIFORefNum, unsigned long theSize, Ptr logical, Ptr physical, Boolean fifoFull, MessageActionProc theInterrupt)
		= DSPDispatch(kdspFIFOSwap)
pascal OSErr DSPSetGPBMode(DSPModuleRefNum theModuleRefNum, unsigned short desiredMode )
		= DSPDispatch(kdspSetGPBMode)
pascal OSErr DSPDontUpdateGPBPrefs (DSPModuleRefNum theModuleRefNum)
		= DSPDispatch(kdspDontUpdateGPBPrefs)
pascal OSErr DSPUpdateGPBPreferenceFile (DSPModuleRefNum theModuleRefNum)
		= DSPDispatch(kdspUpdateGPBPreferenceFile)
pascal OSErr DSPFIFOGetMessageActionProc (DSPFIFORefNum theFIFORefNum, MessageActionProc *theVector)
		= DSPDispatch(kdspFIFOGetMessageActionProc)
pascal OSErr DSPFIFOSetMessageActionProc (DSPFIFORefNum theFIFORefNum, MessageActionProc theVector)
		= DSPDispatch(kdspFIFOSetMessageActionProc)
pascal OSErr DSPGetAvailableOnChipMemory(DSPModuleRefNum theModuleRefNum, unsigned long *theSize)
		= DSPDispatch(kdspGetAvailableOnChipMemory)
pascal OSErr DSPSetSectionSize(DSPSectionRefNum theSectionRefNum, unsigned long theSize)
		= DSPDispatch(kdspSetSectionSize)
#endif
