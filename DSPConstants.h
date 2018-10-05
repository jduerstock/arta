/*
	File:		DSPConstants.h

	Contains:	Constants for the Macintosh DSP API

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

*/
//=========================================================================================

#ifndef __DSPConstants__
#define __DSPConstants__

//==========================================================================================
// 						DSP MODULE/SECTION DEFINTIONS
//==========================================================================================

//------------------------------------------------------------------------------------------
// 	FIFOFlags
//------------------------------------------------------------------------------------------
#define kdspFIFOMaskAllMessages			0x00000000	// disable all messages					
													// (p) priority of FIFO messages in descending order 
#define kdspFIFOEnableOverUnderMessage	0x00000001	// (3) enable message when FIFO transfer causes an overrun or underrun															
#define kdspFIFOEnableFullEmptyMessage  0x00000002	// (2) enable message when FIFO goes full or empty				
#define kdspFIFOEnableHighLowMessage	0x00000004	// (1) enable message when FIFO goes at least half full or half empty
#define kdspFIFOEnableLinkMessage		0x00000008	// (4) enable message when FIFO's link is traversed								

#define kdspFIFOOverUnderTaskInactive	0x00000010	// if task accessing FIFO causes either FIFO overrun or underrun then set task inactive															
#define kdspFIFOFullEmptyTaskInactive	0x00000020	// if task accessing FIFO causes either FIFO full    or empty    then set task inactive																

//------------------------------------------------------------------------------------------
//	ModuleFlags (Check out DSPConstantsPrivate.h to see all of the flags)
//------------------------------------------------------------------------------------------
#define kdspAutoCache 					0x00000000	// select the auto cache model				
#define	kdspDemandCache					0x00000001	// select the demand cache model			
#define kdspOnChipSectionTable			0x00000004	// put the section table on-chip
#define kdspOnChipStack					0x00000020	// A stack of the specified size will be created on-chip
#define kdspOffChipStack				0x00000040	// A stack of the specified size will be created off-chip

//------------------------------------------------------------------------------------------
// 	GPBFlags (see DSPConstantsPrivate.h for the complete list of flags)
//------------------------------------------------------------------------------------------
#define kdspLumpyModule					0x00000000	// use bnEstimate
#define kdspSmoothModule				0x00000001	// see DSPConstantsPrivate.h

//------------------------------------------------------------------------------------------
//	SectionFlags (some of these flags are defined in the private file)
//------------------------------------------------------------------------------------------
// Costs the DSP one instruction to use the following flags:
#define	kdspLeaveSection				0x00000000	// do not load or save this section			
#define	kdspLoadSection					0x00000001	// load this section 						
#define	kdspSaveSection					0x00000002	// save this section						
#define	kdspClearSection				0x00000004	// fill this section with zeroes			
#define	kdspSaveOnContextSwitch			0x00000008	// save this section on context switch		

#define	kdspExternal					0x00000000	// Never loaded on chip						
#define	kdspBankA						0x00000020	// load in bank A if possible				
#define	kdspBankB						0x00000040	// load in bank B if possible				
#define	kdspAnyBank			(kdspBankA | kdspBankB)	// load anywhere							
#define kdspStaticSection				0x00000080	// this section statically allocated before runtime					

#define kdspFIFOSection					0x00000100	// section is an FIFO buffer				
#define kdspReservedSectionFlag0200		0x00000200	// reserved
#define kdspReservedSectionFlag0400		0x00000400	// when loading convert from a FIFO
#define kdspReservedSectionFlag0800		0x00000800	// when saving  convert to   a FIFO

#define	kdspReservedSectionFlag1000		0x00001000	// this is a HIHO Section		
#define kdspReservedSectionFlag2000		0x00002000	// this flag bit will hold the kdspToggleSectionTable fkag from the module's flag 
#define kdspReservedSectionFlag4000		0x00004000	// when loading convert from a HIHO
#define kdspReservedSectionFlag8000		0x00008000	// when saving  convert to   a HIHO

// Costs the DSP two instructions to use the following flags:
#define kdspNotIOBufferSection			0x00010000	// All cases other than below				
#define	kdspInputBuffer					0x00020000	// section is an input buffer				
#define	kdspOutputBuffer				0x00040000	// section is an output buffer				
#define kdspReservedSectionFlag80000	0x00080000	// section is an InterTask Buffer			
#define	kdspScalableSection				0x00100000	// section size can be scaled				
#define kdspReservedSectionFlag200000	0x00200000	// Reserved for use by the DSP Manager					
#define	kdspDSPUseOnly					0x00400000	// only DSP should modify this memory		

//------------------------------------------------------------------------------------------
// 	SectionDataTypes
//------------------------------------------------------------------------------------------
#define	kdspNonData						0x00000000	// data in section is beyond description	
#define	kdsp3200Float					0x00000001	// data is 3200 float format				
#define	kdspIEEEFloat					0x00000002	// data is in IEEE float format				
#define	kdspInt32						0x00000003	// data is 32bit integer					
#define	kdspInt1616						0x00000004	// data is 16bit integer packed				
#define	kdspInt8888						0x00000005	// data is 8bit integer packed				
#define	kdspmuLaw						0x00000006	// data is muLaw format						
#define	kdspALaw						0x00000007	// data is A law format						
#define	kdspAppSpecificData				0x0000FFFF	// data is application specific				

//==========================================================================================
// 						DSP CLIENT DEFINTIONS
//==========================================================================================
//------------------------------------------------------------------------------------------
// 	constants used by a client to specify where to insert a task
//------------------------------------------------------------------------------------------
#define	kdspHeadInsert					0x00000004		// insert at head of list					
#define	kdspTailInsert					0x00000008		// insert tail of list						
#define	kdspBeforeInsert				0x00000010		// insert before reference link				
#define	kdspAfterInsert					0x00000020		// insert after reference link				
#define kdspAnyPositionInsert			kdspHeadInsert	// caller does not care where it goes	

//------------------------------------------------------------------------------------------
//	constants for messages received by client tasks
//------------------------------------------------------------------------------------------
#define kdspBIOPinChangedState			0x62696f70	//  'biop'	bio pin has changed state

#define kdspFIFOMessage					0x66000000	//	'f'		prefix used for FIFO messages
#define kdspFIFOLinkMessage				0x666c6e6b	//  'flnk'	the FIFO's link was traversed
#define kdspFIFOOverrunMessage			0x666f7672	//	'fovr'	the FIFO's buffer filled  before the FIFO write completed											
#define kdspFIFOUnderrunMessage			0x66756e64	//	'fund'	the FIFO's buffer emptied before the FIFO read  completed
#define kdspFIFOFullMessage				0x6666756c	//	'fful'	the FIFO's buffer is exactly full										
#define kdspFIFOEmptyMessage			0x66656d70	//	'femp'	the FIFO's buffer is exactly empty										
#define kdspFIFOHighMessage				0x66686967	//	'fhig'	the FIFO's buffer is at least half full  but not exactly full												
#define kdspFIFOLowMessage				0x666c6f77	//	'flow'	the FIFO's buffer is at least half empty but not exactly empty												
#define kdspFIFOPrimeMessage			0x66707269	//	'fpri'	application specific	

#define kdspExceptionMessage			0x78000000	//  'x'		prefix used for dsp exception messages
#define kdspExceptionReset				0x78727374	//	'xrst'									
#define kdspExceptionBusError			0x78627573	//	'xbus'							
#define kdspExceptionIllegalOpcode		0x78696c6c	//	'xill'	
#define kdspExceptionReservedOne		0x78727631	//	'xrv1'		
#define kdspExceptionAddressError		0x78616472	//	'xadr'	
#define kdspExceptionDAUOverUnderflow	0x78646175	//	'xdau'	
#define kdspExceptionNotANumber			0x786e616e	//	'xnan'	
#define kdspExceptionReservedTwo		0x78727632	//	'xrv2'		
#define kdspExceptionExternalIntZero	0x78657830	//	'xex0'		
#define kdspExceptionTimer				0x7874696d	//	'xtim'	
#define kdspExceptionReservedThree		0x78727633	//	'xrv3'	
#define kdspExceptionSIOInputBufFull	0x78736962	//	'xsib'		
#define kdspExceptionSIOOutputBufEmpty	0x78736f62	//	'xsob'	
#define kdspExceptionSIODMAInputFrame	0x78736966	//	'xsif'
#define kdspExceptionSIODMAOutputFrame	0x78736f66	//	'xsof'	
#define kdspExceptionExternalIntOne		0x78657831	//	'xex1'	

#define kdspExceptionRuntimeError		0x78657272	//	'xerr'	

#define kdspGPBMessage					0x67000000	//	'g' 	prefix used for GPB messages						
#define kdspGPBTaskActive				0x67616374	//	'gact'	the task is   active						
#define kdspGPBTaskInactive				0x67696e61	//	'gina'	the task is inactive							
#define kdspGPBFrameOverrun				0x676f7672	//	'govr'	this task was involved in a frame ovverrun and is now inactive							
#define kdspGPBFrameSkip				0x67736b70	//	'gskp'	this task has skipped one or more frames due to a frame ovverun							

//------------------------------------------------------------------------------------------
// read/write permission constants for clients
//------------------------------------------------------------------------------------------
#define kdspWritePermission				0x0001
#define kdspReadPermission				0x0002
#define kdspReadWritePermission 		(kdspWritePermission|kdspReadPermission)

//------------------------------------------------------------------------------------------
// constants for indexed devices
//------------------------------------------------------------------------------------------

// CPU processor types
#define kdsp3210						'3210'

// General constants
#define kdspDeviceFeatures				'feat'

// CPU constants
#define kdspDeviceName					'dnam'
#define kdspDeviceICON					'dicn'
#define kdspSlotNumber					'dslt'
#define kdspProcessorType				'ptyp'
#define kdspPhaseRegister				'phas'
#define kdspPhaseRollover				'phro'
#define	kdspFrameRate					'fmrt'

// IO constants
#define kdspIODeviceName				'ionm'
#define kdspIODeviceICON				'ioic'

// Selectors for BIO devices
#define	kdspBIOPinState					'bios'
#define	kdspBIOPinDirection				'biod'
#define	kdspBIOInterruptMask			'biom'
#define	kdspBIOInterruptHandler			'bioh'

// Selectors for SIO devices
#define	kdspSampleRate					'smrt'
#define	kdspSampleFormat				'smsz'

//  Use option's current index
#define	kdspCurrentIndex					-1

// CPU device feature bits
#define kdspMotherBoard						0
#define kdspCanBeSlaveCPUDevice				1
#define kdspCanOnlyAccessDSPZone			2

//  IO device types
#define kdspSIOTypeDevice 					0
#define	kdspBIOTypeDevice 					1

// SIO device feature bits
#define kdspStdSoundCompatible				0
#define kdspRegisterDSPOutputSifter			1
#define kdspInstallDSPInputDriver			2
#define kdspInputDriverOptionsDialogBox		3

// BIO Pin constants
#define kdspBIOPinZero					(0)
#define kdspBIOPinOne					(1)
#define kdspBIOPinTwo					(2)
#define kdspBIOPinThree					(3)
#define kdspBIOPinFour					(4)
#define kdspBIOPinFive					(5)
#define kdspBIOPinSix					(6)
#define kdspBIOPinSeven					(7)

#define kdspBIOConfigurePinForInput		(0)
#define	kdspBIOConfigurePinForOutput	(1)

#define kdspBIOPinKeepCurrentState		(0)
#define	kdspBIOPinSetToZero				(1)
#define	kdspBIOPinSetToOne				(2)
#define	kdspBIOPinToggleCurrentState	(3)

//------------------------------------------------------------------------------------------
// constants for DSP API functions
//------------------------------------------------------------------------------------------
#define kevtMessageToHost				(17)
#define kevtCacheSection				(22)
#define kevtCopyFIFO					(23)
#define	kevtGetSectionSize				(43)
#define kevtGPBSetUseActual				(44)
#define kevtGPBExpectedCycles			(45)
#define kevtGPBElapsedCycles			(46)
#define kevtSemaphoreSet				(47)
#define kevtSemaphoreClear				(48)
#define kevtGPBChangeMode				(49)
#define	kevtSetSkipCount				(50)
#define kevtSetTaskInactive				(51)
#define kevtBlockMove					(53)
#define	kevtNumRealTimeFrames			(113)	

//==========================================================================================
//	constants for errors returned by Macintosh DSP API
//==========================================================================================

//------------------------------------------------------------------------------------------
// Misc Errors
//  Error numbers allocated to the Real-Time Manager:  -2600 -> -2674   (JDB 7/14)
// 	The next available error code number is -2669
//	N.B. If you add an error, also add it to the DSPErrorStrings.r file.
//------------------------------------------------------------------------------------------
#define kdspUnimplemented				(-2626) 	// This feature is not done				
#define kdspParamErr					(-2638)		// bad parameter passed in				

//------------------------------------------------------------------------------------------
// DSPFIFO Errors
//------------------------------------------------------------------------------------------
#define kdspNotAFIFOSection				(-2634)		// The section is not a FIFO
#define kdspNoMessageInterrupt			(-2636)		// no message passing without a vector
#define kdspFIFOInUseByDSP				(-2653)		// This FIFO is currently being accessed by the DSP
#define kdspTaskMustBeInActive			(-2654)		// Can only Dipose of InActive structures
#define kdspNotFirstFIFO				(-2655)		// The FIFO must be the first fifo in the link to wrap it

//------------------------------------------------------------------------------------------
// DSPList Errors
//------------------------------------------------------------------------------------------
#define	kdspPositionIllegalErr			(-2600)		// Illegal DSPPosition type				
#define	kdspPositionBusyErr				(-2601)		// DSPPosition already occupied			
#define kdspInvalidReferenceErr			(-2602)		// illegal insertion request			
#define kdspNonExistantReferenceErr		(-2603)		// reference element does not exist		
#define kdspNonExistantElementErr		(-2604)		// deletion element not found			

//------------------------------------------------------------------------------------------
// DSPMemory Errors
//------------------------------------------------------------------------------------------
#define kdspMemFullErr					(-2605)		// heap full, allocation failed			
#define kdspAddressNotInZone			(-2606)		// address is not in a zone				
#define kdspNilAddress					(-2617)		// Trying to dispose of nil				
#define kdspContainingNilAddress		(-2618)		// Trying to dispose of (nil, nil)		
#define	kdspInvalidZoneSize				(-2619)		// Heap Size must be factor of four		
#define	kdspInvalidZoneBase				(-2620)		// Heap base must be long word aligned	

//------------------------------------------------------------------------------------------
// DSPClient Errors
//------------------------------------------------------------------------------------------
#define kdspDeviceNotFound 				(-2607)		// no device matching given name		
#define kdspInvalidIndexErr				(-2608)		// no device (or whatever) matching index given		
#define kdspDeviceHasActiveClients		(-2609)		// can't sign out device with clients	
#define kdspInvalidPermission			(-2622)		// invalid permission for operation		
#define kdspWritePermissionDenied		(-2623)		// client already exist w/ write perm	
#define kdspClientNameInvalid			(-2624)		// client name must be [1……31] bytes	
#define kdspInvalidOptionSelector		(-2625)		// options selector not recognized		
#define	kdspInvalidIODeviceType 		(-2641)		// invalid io device type, index out of range
#define kdspInvalidClientICON			(-2651)		// An invalid ICON was passed in
#define kdspDeviceCantBeSlave			(-2662)		// The specified cpu device cannot be a slave

//------------------------------------------------------------------------------------------
// Resource Loader Errors
//------------------------------------------------------------------------------------------
#define kdspModuleNotFound				(-2610)		// the module does not exist			
#define kdspModuleUncompatibleRate		(-2611)		// incompatible frame or sample rate	
#define kdspUnknownDSPFResourceVersion	(-2613)		// DSPF resource not recognized			
#define kdspUnknownDSPSectionTag		(-2614)		// DSPF resource not recognized	
#define kdspZeroGPB						(-2648)		// The Module has GPB set to zero.
#define kdspTwoStacks					(-2665)		// Can not have both an on-chip and an off-chip stack

//------------------------------------------------------------------------------------------
// DSPStorage Errors
//------------------------------------------------------------------------------------------
#define kdspStorageNotFound				(-2629)		// theAmount and Location do no exist	
#define kdspNotEnoughOnChipMemory		(-2630)		// not enough on-chip memory to allocate

//------------------------------------------------------------------------------------------
// DSPAllocation Errors
//------------------------------------------------------------------------------------------
#define kdspCouldNotAllocate			(-2612)		// Could not allocate the module		
#define kdspMoreThanOneModule			(-2621)		// can allocate only one module for now	
#define kdspSectionAlreadyConnected		(-2627)		// One of the Sections has already been	
													// connected. (i.e. FIFO Sections)			
#define kdspSectionsDoNotMatch			(-2628)		// the sections which are being 		
													// connected either do not have the 	
													// same size or the same type or
													// they are both input or both output
#define kdspSectionsNotInSameTask		(-2640)		// The sections that are being connected
													// are not in the same task
#define kdspSectionNotFound				(-2631)		// Could not find the specified section	
#define kdspBothFIFOsAllocated			(-2632)		// Both FIFO sections have already been	
													// attached to FIFOs					
#define kdspHadToUseOffChipMemory		(-2633)		// at least 1 section which was supposed	
													// to be on-chip was set up off-chip.	
													// The module will still run, but not	
													// as quickly							
#define kdspAlreadyAllocated			(-2635)		// You can not make a mew ITB or 		
													// connect sections if the task has		
													// already been allocated.				
#define kdspTooManyITBs					(-2637)		// You can not have more than 			
													// MAX_MAP_SECTIONS ITBs				
#define kdspInvalidModuleAddress		(-2646)		// Passed in a nil module address
#define kdspAIAOMustLoadOrSave			(-2649)		// When connecting a FIFO to an AIAO, the
													// AIAO must move data or the connection
													// will not work.
#define kdspFIFOsNotConnected			(-2650)		// You can not insert a task if all of the
													// FIFOs are not connected to other FIFOs.
#define kdspNotAllocated				(-2652)		// You must insert the task before you can
													// call DSPGetSectionData
#define kdspTaskNotInstalled			(-2666)		// You can not get the available on-chip memory
													// until after the task is installed
													
//------------------------------------------------------------------------------------------
// DSPTask Errors
//------------------------------------------------------------------------------------------
#define kdspTaskRefNumAlreadyAllocated	(-2615)		// trying to reuse used DSPTaskRefNum 	
#define kdspNilMessageActionProc		(-2639)		// passed in nil where MessageActionProc required
#define kdspInvalidCPUDevicePtr			(-2642)		// passed in nil for the DSPCPUDeviceParamBlkPtr
#define kdspInvalidTaskRefNumPtr		(-2643)		// passed in nil for the DSPTaskRefNumPtr
#define kdspInvalidTaskAddress			(-2644)		// passed in nil for the DSPTaskAddressPtr
#define kdspInvalidTaskRefNum			(-2645)		// passed in nil for the DSPTaskRefNum
#define kdspInvalidTaskName				(-2647)		// length of name must be > 0 and < 31
#define kdspNoMasterSlaveRelationship	(-2656)		// tasks to be synchronized must be on one
													// DSP or on DSPs that have master-slave relationship
#define kdspAllTasksMustBeRealTime		(-2657)		// tasks to be synchronized that are on different
													// DSPs must all be in the real-time task list
#define kdspNotEnoughTime				(-2658)		// didn’t have enough time to successfully synchronize
													// all the taks
#define kdspChangingState				(-2659)		// task is in the process of going (in)active
#define kdspAlreadyActive				(-2660)		// task is in already active
#define kdspAlreadyInactive				(-2661)		// task is in already inactive
#define kdspTimeOutErr					(-2667)		// timed out trying to set the task inactive (probably a stupid time
													//  share task that never calls return(RV)!)  <SM10> JDB
#define kdspFrameOverrunRecoveryErr		(-2668)		// DSP is in frame overrun recovery, can’t install now.
													

//------------------------------------------------------------------------------------------
// DSPGPB Errors
//------------------------------------------------------------------------------------------
#define kdspNotEnoughGPB				(-2616)		// not enough real time for allocation	

//------------------------------------------------------------------------------------------
// DSP Address Fixup Errors
//------------------------------------------------------------------------------------------
#define	kdspOnChipPatchup				(-2663)		// auto-init using address already on chip
#define kdspBadRelocationType			(-2664)		// internal assert - unrecognized relocation type from linker

#endif
