@ Shared entry points and data addresses used by recovered C modules.
.syntax unified
.thumb
.global CopyEncodedTextToBuffer
.thumb_set CopyEncodedTextToBuffer, 0x08018c25
.global WriteNumericPrefix
.thumb_set WriteNumericPrefix, 0x08018cb9
.global ReadSelectorOffsetByte
.thumb_set ReadSelectorOffsetByte, 0x08013a5d
.global ResolveContextTextPointerFromByte
.thumb_set ResolveContextTextPointerFromByte, 0x080cb4e0
.global ResolveContextRecordTextPointer
.thumb_set ResolveContextRecordTextPointer, 0x080ca1bd
.global WriteUnsignedNumberText
.thumb_set WriteUnsignedNumberText, 0x08018abd
.global WriteHalfwordTextWithMode
.thumb_set WriteHalfwordTextWithMode, 0x080142dd
.global FormatHalfwordToDecimalAscii
.thumb_set FormatHalfwordToDecimalAscii, 0x08002fb9
.global CountNullTerminatedBytes
.thumb_set CountNullTerminatedBytes, 0x081444b9
.global CountStatusRecordsWithBits0And1
.thumb_set CountStatusRecordsWithBits0And1, 0x080cecf5
.ifndef OMIT_CountSelectedRecordFlags
.global CountSelectedRecordFlags
.thumb_set CountSelectedRecordFlags, 0x080ce8a9
.endif
.global GetSelectedFlagMilestoneCount
.thumb_set GetSelectedFlagMilestoneCount, 0x080ced2d
.ifndef OMIT_CountObjectAnimationSteps
.global CountObjectAnimationSteps
.thumb_set CountObjectAnimationSteps, 0x0801075d
.endif
.global InspectEquipmentForScan
.thumb_set InspectEquipmentForScan, 0x080cae2d
.ifndef OMIT_ReplaceEquipmentSlotForScan
.global ReplaceEquipmentSlotForScan
.thumb_set ReplaceEquipmentSlotForScan, 0x080caf79
.endif
.global ProcessSelectedPoolUnitEntry
.thumb_set ProcessSelectedPoolUnitEntry, 0x080cc65d
.global UnsignedDivide
.thumb_set UnsignedDivide, 0x08142ab1
.global gBucketRandomHalfwords
.equ gBucketRandomHalfwords, 0x085295d4
.global gMissionRewardModifiers
.equ gMissionRewardModifiers, 0x08521214
.global gMissionRewardLinkHead
.equ gMissionRewardLinkHead, 0x020028c8
.global NextRandom15
.thumb_set NextRandom15, 0x08002805
.global RunTaskGroup
.thumb_set RunTaskGroup, 0x080069f4
.global ConfigureTaskGroup
.thumb_set ConfigureTaskGroup, 0x08006a7c
.global AttachTaskCallback
.thumb_set AttachTaskCallback, 0x08006adc
.global Routine_08001194
.thumb_set Routine_08001194, 0x08001194
.global Routine_08001244
.thumb_set Routine_08001244, 0x08001244
.global Routine_08002804
.thumb_set Routine_08002804, 0x08002804
.global Routine_08001cd0
.thumb_set Routine_08001cd0, 0x08001cd0
.global Routine_08001ce0
.thumb_set Routine_08001ce0, 0x08001ce0
.global AppendTransformedSpriteListToOam
.thumb_set AppendTransformedSpriteListToOam, 0x080014c8
.global AppendSpriteListToOam
.thumb_set AppendSpriteListToOam, 0x080016d4
.global ResetOamAndAffineMatrices
.thumb_set ResetOamAndAffineMatrices, 0x08003454
.global RetailCopyBytes
.thumb_set RetailCopyBytes, 0x081443fc
.ifndef OMIT_RetailCall_0809d6bc
.global RetailCall_0809d6bc
.thumb_set RetailCall_0809d6bc, 0x0809d6bd
.endif
.ifndef OMIT_RetailCall_080b7dc8
.global RetailCall_080b7dc8
.thumb_set RetailCall_080b7dc8, 0x080b7dc9
.endif
.ifndef OMIT_RetailCall_080a12fc
.global RetailCall_080a12fc
.thumb_set RetailCall_080a12fc, 0x080a12fd
.endif
.ifndef OMIT_RetailCall_0812ee98
.global RetailCall_0812ee98
.thumb_set RetailCall_0812ee98, 0x0812ee99
.endif
.ifndef OMIT_RetailCall_080a05c4
.global RetailCall_080a05c4
.thumb_set RetailCall_080a05c4, 0x080a05c5
.endif
.ifndef OMIT_RetailCall_08099c1c
.global RetailCall_08099c1c
.thumb_set RetailCall_08099c1c, 0x08099c1d
.endif
.ifndef OMIT_RetailCall_08099d08
.global RetailCall_08099d08
.thumb_set RetailCall_08099d08, 0x08099d09
.endif
.ifndef OMIT_RetailCall_08099d34
.global RetailCall_08099d34
.thumb_set RetailCall_08099d34, 0x08099d35
.endif
.ifndef OMIT_RetailCall_080b7c50
.global RetailCall_080b7c50
.thumb_set RetailCall_080b7c50, 0x080b7c51
.endif
.ifndef OMIT_RetailCall_080a3778
.global RetailCall_080a3778
.thumb_set RetailCall_080a3778, 0x080a3779
.endif
.ifndef OMIT_RetailCall_080a3848
.global RetailCall_080a3848
.thumb_set RetailCall_080a3848, 0x080a3849
.endif
.ifndef OMIT_RetailCall_080b4a1c
.global RetailCall_080b4a1c
.thumb_set RetailCall_080b4a1c, 0x080b4a1d
.endif
.ifndef OMIT_RetailCall_080b4c90
.global RetailCall_080b4c90
.thumb_set RetailCall_080b4c90, 0x080b4c91
.endif
.ifndef OMIT_RetailCall_080c8280
.global RetailCall_080c8280
.thumb_set RetailCall_080c8280, 0x080c8281
.endif
.ifndef OMIT_RetailCall_080cdcec
.global RetailCall_080cdcec
.thumb_set RetailCall_080cdcec, 0x080cdced
.endif
.ifndef OMIT_RetailCall_080c8298
.global RetailCall_080c8298
.thumb_set RetailCall_080c8298, 0x080c8299
.endif
.ifndef OMIT_RetailCall_0812e470
.global RetailCall_0812e470
.thumb_set RetailCall_0812e470, 0x0812e471
.endif
.ifndef OMIT_RetailCall_0801cc18
.global RetailCall_0801cc18
.thumb_set RetailCall_0801cc18, 0x0801cc19
.endif
.ifndef OMIT_RetailCall_08099644
.global RetailCall_08099644
.thumb_set RetailCall_08099644, 0x08099645
.endif
.ifndef OMIT_RetailCall_08002804
.global RetailCall_08002804
.thumb_set RetailCall_08002804, 0x08002805
.endif
.ifndef OMIT_RetailCall_08142950
.global RetailCall_08142950
.thumb_set RetailCall_08142950, 0x08142951
.endif
.global SelectMapClippingBuffer
.thumb_set SelectMapClippingBuffer, 0x0801ad39
.global ReadMapCellPrimaryByte
.thumb_set ReadMapCellPrimaryByte, 0x0801cc19
.ifndef OMIT_GetScenePathBuffer
.global GetScenePathBuffer
.thumb_set GetScenePathBuffer, 0x08121c59
.endif
.global ProjectMapCellCoordinates
.thumb_set ProjectMapCellCoordinates, 0x0801ca79
.global MapCellToScreenCoordinates
.thumb_set MapCellToScreenCoordinates, 0x0801c919
.global CheckMapCornerState
.thumb_set CheckMapCornerState, 0x0801ec29
.global ReadMapCornerStateFlag
.thumb_set ReadMapCornerStateFlag, 0x0801e63d
.global ResolveMapCellCornerSelection
.thumb_set ResolveMapCellCornerSelection, 0x0801d131
.global ContinueMapClippingRuns
.thumb_set ContinueMapClippingRuns, 0x0801efb1
.global BiosCpuFastSet
.thumb_set BiosCpuFastSet, 0x08141869
.global BiosLz77UnCompWram
.thumb_set BiosLz77UnCompWram, 0x08141891
.global DecodeA7IndexedGraphics
.thumb_set DecodeA7IndexedGraphics, 0x08005319
.global LookupIndexedArchiveRecord
.thumb_set LookupIndexedArchiveRecord, 0x080071a9
.global ReadIndexedArchiveEntryCount
.thumb_set ReadIndexedArchiveEntryCount, 0x080071e5
.global DecodeCustomLzssGraphics
.thumb_set DecodeCustomLzssGraphics, 0x0800543d
.global Routine_0800221c
.thumb_set Routine_0800221c, 0x0800221c
.global WaitForDmaChannelIdle
.thumb_set WaitForDmaChannelIdle, 0x08003a08
.global CallR2Trampoline
.thumb_set CallR2Trampoline, 0x0814224c
.global SignedModulo
.thumb_set SignedModulo, 0x08142950

/* Direct retail helpers consumed by the readable C09 phase controller. */
.global C09GetRandomSeedAddress
.thumb_set C09GetRandomSeedAddress, 0x08002831
.global CoreFrontier_00004C40
.thumb_set CoreFrontier_00004C40, 0x08004c41
.global CoreFrontier_00025464
.thumb_set CoreFrontier_00025464, 0x08025465
.global CoreFrontier_000C72F8
.thumb_set CoreFrontier_000C72F8, 0x080c72f9
.global CoreFrontier_000C72E4
.thumb_set CoreFrontier_000C72E4, 0x080c72e5
.global CoreFrontier_001219F4
.thumb_set CoreFrontier_001219F4, 0x081219f5
.global CoreFrontier_000C1994
.thumb_set CoreFrontier_000C1994, 0x080c1995
.global CoreFrontier_000C1980
.thumb_set CoreFrontier_000C1980, 0x080c1981
.global CoreFrontier_000C738C
.thumb_set CoreFrontier_000C738C, 0x080c738d
.global CoreFrontier_000C19BC
.thumb_set CoreFrontier_000C19BC, 0x080c19bd
.global CoreFrontier_000C7240
.thumb_set CoreFrontier_000C7240, 0x080c7241
.global CoreFrontier_000C7284
.thumb_set CoreFrontier_000C7284, 0x080c7285
.global CoreFrontier_0009D3A8
.thumb_set CoreFrontier_0009D3A8, 0x0809d3a9
.ifndef OMIT_CoreConsumer_0009836C
.global CoreConsumer_0009836C
.thumb_set CoreConsumer_0009836C, 0x0809836d
.endif
.global CompilerCallViaR1
.thumb_set CompilerCallViaR1, 0x08142249
.ifndef OMIT_BattleCallbackProducer_000A8194
.global BattleCallbackProducer_000A8194
.thumb_set BattleCallbackProducer_000A8194, 0x080a8195
.endif
.global CoreFrontier_000A8264
.thumb_set CoreFrontier_000A8264, 0x080a8265
.global BattleCallbackProducer_000A8270
.thumb_set BattleCallbackProducer_000A8270, 0x080a8271
.global CoreFrontier_000A899C
.thumb_set CoreFrontier_000A899C, 0x080a899d
.global CoreFrontier_000A89D8
.thumb_set CoreFrontier_000A89D8, 0x080a89d9
.global CoreFrontier_000A8A54
.thumb_set CoreFrontier_000A8A54, 0x080a8a55
.global CoreFrontier_000A7138
.thumb_set CoreFrontier_000A7138, 0x080a7139
.global CoreFrontier_000A8934
.thumb_set CoreFrontier_000A8934, 0x080a8935
.global sub_0809993C
.thumb_set sub_0809993C, 0x0809993d
.ifndef OMIT_CoreConsumer_0009D6BC
.global CoreConsumer_0009D6BC
.thumb_set CoreConsumer_0009D6BC, 0x0809d6bd
.endif

.global CreateMissionRewardUnit
.thumb_set CreateMissionRewardUnit, 0x080c9645

.ifndef OMIT_GetMissionRewardWeightBonus
.global GetMissionRewardWeightBonus
.thumb_set GetMissionRewardWeightBonus, 0x080d2301
.endif

.ifndef OMIT_SelectMissionRewardGroupRoot
.global SelectMissionRewardGroupRoot
.thumb_set SelectMissionRewardGroupRoot, 0x080d2381
.endif

.ifndef OMIT_GetMissionRewardLevelAverage
.global GetMissionRewardLevelAverage
.thumb_set GetMissionRewardLevelAverage, 0x080ca079
.endif
.global RetailInitializeFourRecordHeaders
.thumb_set RetailInitializeFourRecordHeaders, 0x080027e4
.global RetailInitializeStoragePool
.thumb_set RetailInitializeStoragePool, 0x080023ec
.global gStartupRecordStorage
.equ gStartupRecordStorage, 0x03000ee0
.global gPoolImageBegin
.equ gPoolImageBegin, 0x080000fc
.global gPoolImageEnd
.equ gPoolImageEnd, 0x0800023c
.global SetIndexedFlagState
.thumb_set SetIndexedFlagState, 0x080c9574
.global IsIndexedSceneFlagSet
.thumb_set IsIndexedSceneFlagSet, 0x080c9540
.ifndef OMIT_ReleaseSceneHandle
.global ReleaseSceneHandle
.thumb_set ReleaseSceneHandle, 0x08122454
.endif
.global gSceneCommandDefinitionTable
.equ gSceneCommandDefinitionTable, 0x083a7ee4
.ifndef OMIT_CreateSceneContextEntry
.global CreateSceneContextEntry
.thumb_set CreateSceneContextEntry, 0x081223c8
.endif
.global CreateSceneActionRecord
.thumb_set CreateSceneActionRecord, 0x08126ea4
.global CreateSceneEventRecord
.thumb_set CreateSceneEventRecord, 0x0812638c
.ifndef OMIT_HasSceneHandle
.global HasSceneHandle
.thumb_set HasSceneHandle, 0x08122484
.endif
.global CreateSceneCommandActionRecord
.thumb_set CreateSceneCommandActionRecord, 0x08126dfc
.global ResolveSceneEntityHandle
.thumb_set ResolveSceneEntityHandle, 0x081255c8
.global ApplySceneCommandByteTriple
.thumb_set ApplySceneCommandByteTriple, 0x08126b3c
.global ApplySceneCommandBytePair
.thumb_set ApplySceneCommandBytePair, 0x08124560
.global ResolveSceneSelectorByte
.thumb_set ResolveSceneSelectorByte, 0x08036330
.global ApplyResolvedSceneSelector
.thumb_set ApplyResolvedSceneSelector, 0x08036584
.global ApplySceneCommandValue
.thumb_set ApplySceneCommandValue, 0x081263b0
.global ApplySceneCommandModeValue
.thumb_set ApplySceneCommandModeValue, 0x081263dc
.global ApplySceneCommandContext
.thumb_set ApplySceneCommandContext, 0x0812640c
.global ApplySceneThreeByteCommand
.thumb_set ApplySceneThreeByteCommand, 0x08126b6c
.global QueueSceneActionB0WithWord
.thumb_set QueueSceneActionB0WithWord, 0x0812b7d0
.global QueueSceneAction44
.thumb_set QueueSceneAction44, 0x0812bd2c
.global QueueSceneAction44WithByte
.thumb_set QueueSceneAction44WithByte, 0x0812bce4
.global QueueSceneAction08
.thumb_set QueueSceneAction08, 0x0812bd0c
.global SetContentStateFlag40
.thumb_set SetContentStateFlag40, 0x080c7378
.global QueueSceneAction108
.thumb_set QueueSceneAction108, 0x0812c4e4
.global ResetSceneViewState
.thumb_set ResetSceneViewState, 0x08125938
.global SetIndexedUnitState
.thumb_set SetIndexedUnitState, 0x080cd884
.global ApplySceneEntityState
.thumb_set ApplySceneEntityState, 0x08124710
.global GetSceneActionContextBase
.thumb_set GetSceneActionContextBase, 0x08096d7d
.global FindSceneEntityForUnitRecord
.thumb_set FindSceneEntityForUnitRecord, 0x08099561
.ifndef OMIT_ResolveSceneUnitByEncodedId
.global ResolveSceneUnitByEncodedId
.thumb_set ResolveSceneUnitByEncodedId, 0x08121cb5
.endif
.global FindUnitPoolRecordById
.thumb_set FindUnitPoolRecordById, 0x080c83cd
.global ApplyScenePackedAction
.thumb_set ApplyScenePackedAction, 0x081242a0
.global HandleSceneCommandZero
.thumb_set HandleSceneCommandZero, 0x08124648
.global ResolveSceneHandleValue
.thumb_set ResolveSceneHandleValue, 0x08125624
.ifndef OMIT_ResolveSceneCommandSelector
.global ResolveSceneCommandSelector
.thumb_set ResolveSceneCommandSelector, 0x08121d9c
.endif
.global ResolveSceneCommandByte
.thumb_set ResolveSceneCommandByte, 0x08141728
.global ApplySceneCommandMask
.thumb_set ApplySceneCommandMask, 0x0812800c
.global ProcessSceneCommandByte
.thumb_set ProcessSceneCommandByte, 0x08125760
.global ProcessSceneCommandValue
.thumb_set ProcessSceneCommandValue, 0x08124d58
.global ProcessSceneCommandFields
.thumb_set ProcessSceneCommandFields, 0x08126b08
.global ProcessSceneCommandHandleIndex
.thumb_set ProcessSceneCommandHandleIndex, 0x08124fd0
.global StartSceneCommandTask
.thumb_set StartSceneCommandTask, 0x080d376d
.global ClearSceneCommandTaskState
.thumb_set ClearSceneCommandTaskState, 0x080d37ad
.global ReadSceneTileElevation
.thumb_set ReadSceneTileElevation, 0x0801cc19
.global ProjectScenePosition
.thumb_set ProjectScenePosition, 0x0801c919
.global SelectSceneEntityAtPosition
.thumb_set SelectSceneEntityAtPosition, 0x0801bb0d
.global SelectSceneObjectAtPosition
.thumb_set SelectSceneObjectAtPosition, 0x0801ba21
.global QueueSceneCommandAtPosition
.thumb_set QueueSceneCommandAtPosition, 0x08128899
.global SceneSelectionTypeByIndex
.set SceneSelectionTypeByIndex, 0x083a8190
.ifndef OMIT_GetSceneCommandTaskContext
.global GetSceneCommandTaskContext
.thumb_set GetSceneCommandTaskContext, 0x08121dbc
.endif
.global IsSceneCommandTaskComplete
.thumb_set IsSceneCommandTaskComplete, 0x080d3879
.global ReleaseSceneCommandTaskContext
.thumb_set ReleaseSceneCommandTaskContext, 0x080d3865
.ifndef OMIT_SetSceneCommandTaskContext
.global SetSceneCommandTaskContext
.thumb_set SetSceneCommandTaskContext, 0x08121da8
.endif
.global QueueSceneCommandWithPackedArguments
.thumb_set QueueSceneCommandWithPackedArguments, 0x08127b81
.global ProcessSceneCommandWithMode
.thumb_set ProcessSceneCommandWithMode, 0x08126aa9
.ifndef OMIT_SetCurrentSceneEntityRecord
.global SetCurrentSceneEntityRecord
.thumb_set SetCurrentSceneEntityRecord, 0x08121dd0
.endif
.ifndef OMIT_SetSceneRuntimeControlByte
.global SetSceneRuntimeControlByte
.thumb_set SetSceneRuntimeControlByte, 0x08121bdc
.endif
.global HandleSceneRuntimeModeFour
.thumb_set HandleSceneRuntimeModeFour, 0x08124f25
.global HandleSceneRuntimeModeEight
.thumb_set HandleSceneRuntimeModeEight, 0x080a9529
.global CreateSceneActionFromEntityPair
.thumb_set CreateSceneActionFromEntityPair, 0x08126e35
.global ProcessSceneActionSelector
.thumb_set ProcessSceneActionSelector, 0x08123e01
.global GetIndexedFlagState
.thumb_set GetIndexedFlagState, 0x080c95a9
.global ClearSelectedSceneRuntimeBytes
.thumb_set ClearSelectedSceneRuntimeBytes, 0x08121d40
.global GetCurrentOrPendingSceneRecordIndex
.thumb_set GetCurrentOrPendingSceneRecordIndex, 0x0800a025
.ifndef OMIT_SetSceneRuntimeCommandByte
.global SetSceneRuntimeCommandByte
.thumb_set SetSceneRuntimeCommandByte, 0x08121d80
.endif

.ifndef OMIT_Allocate_08007138
.global Allocate_08007138
.thumb_set Allocate_08007138, 0x08007139
.endif
.ifndef OMIT_Free_08007170
.global Free_08007170
.thumb_set Free_08007170, 0x08007171
.endif
.ifndef OMIT_HandleRecordBaseFromToken
.global HandleRecordBaseFromToken
.thumb_set HandleRecordBaseFromToken, 0x08005bfd
.endif
.ifndef OMIT_InitializeOpaqueSceneContext
.global InitializeOpaqueSceneContext
.thumb_set InitializeOpaqueSceneContext, 0x08121b8d
.endif
.ifndef OMIT_ReadSceneHandleSlot
.global ReadSceneHandleSlot
.thumb_set ReadSceneHandleSlot, 0x08121d0d
.endif
.ifndef OMIT_WriteSceneHandleSlot
.global WriteSceneHandleSlot
.thumb_set WriteSceneHandleSlot, 0x08121d21
.endif
.ifndef OMIT_TryRegisterSceneHandle
.global TryRegisterSceneHandle
.thumb_set TryRegisterSceneHandle, 0x08122405
.endif
.ifndef OMIT_RemoveTaskSubtree_080058A4
.global RemoveTaskSubtree_080058A4
.thumb_set RemoveTaskSubtree_080058A4, 0x080058a5
.endif
.ifndef OMIT_CreateTaskNode_08005954
.global CreateTaskNode_08005954
.thumb_set CreateTaskNode_08005954, 0x08005955
.endif
.ifndef OMIT_RunTaskTree_08005A24
.global RunTaskTree_08005A24
.thumb_set RunTaskTree_08005A24, 0x08005a25
.endif
.ifndef OMIT_CreateCurrentTask_08005B6C
.global CreateCurrentTask_08005B6C
.thumb_set CreateCurrentTask_08005B6C, 0x08005b6d
.endif
.ifndef OMIT_AllocateCurrentTaskBytes_08005B28
.global AllocateCurrentTaskBytes_08005B28
.thumb_set AllocateCurrentTaskBytes_08005B28, 0x08005b29
.endif
.ifndef OMIT_FreeCurrentTaskBytes_08005B40
.global FreeCurrentTaskBytes_08005B40
.thumb_set FreeCurrentTaskBytes_08005B40, 0x08005b41
.endif
.ifndef OMIT_CopyBytes_081443FC
.global CopyBytes_081443FC
.thumb_set CopyBytes_081443FC, 0x081443fd
.endif
.ifndef OMIT_RemainderSwapped_0814187C
.global RemainderSwapped_0814187C
.thumb_set RemainderSwapped_0814187C, 0x0814187d
.endif
.ifndef OMIT_ExpandStreamChunk_08005C54
.global ExpandStreamChunk_08005C54
.thumb_set ExpandStreamChunk_08005C54, 0x08005c55
.endif
.ifndef OMIT_FillStreamChunk_08005E7C
.global FillStreamChunk_08005E7C
.thumb_set FillStreamChunk_08005E7C, 0x08005e7d
.endif
.ifndef OMIT_StreamTransferCallback_08005EF8
.global StreamTransferCallback_08005EF8
.thumb_set StreamTransferCallback_08005EF8, 0x08005ef9
.endif
.ifndef OMIT_CopyTileMatrix_08005FC4
.global CopyTileMatrix_08005FC4
.thumb_set CopyTileMatrix_08005FC4, 0x08005fc5
.endif
.ifndef OMIT_MapTransferCallback_0800620C
.global MapTransferCallback_0800620C
.thumb_set MapTransferCallback_0800620C, 0x0800620d
.endif
.ifndef OMIT_CreateStreamTransfer_08006878
.global CreateStreamTransfer_08006878
.thumb_set CreateStreamTransfer_08006878, 0x08006879
.endif
.ifndef OMIT_CreateMapTransfer_080068D4
.global CreateMapTransfer_080068D4
.thumb_set CreateMapTransfer_080068D4, 0x080068d5
.endif
.ifndef OMIT_QueueDmaCopy16
.global QueueDmaCopy16
.thumb_set QueueDmaCopy16, 0x08000a99
.endif
.ifndef OMIT_QueueDmaCopy32
.global QueueDmaCopy32
.thumb_set QueueDmaCopy32, 0x08000add
.endif
.ifndef OMIT_QueueDmaFixedSource32
.global QueueDmaFixedSource32
.thumb_set QueueDmaFixedSource32, 0x08000b69
.endif
.ifndef OMIT_QueueDmaSequence16
.global QueueDmaSequence16
.thumb_set QueueDmaSequence16, 0x08000bad
.endif
.global ApplySceneSelectionValue
.thumb_set ApplySceneSelectionValue, 0x081416dd
.global FinalizeSceneSelectionCommand
.thumb_set FinalizeSceneSelectionCommand, 0x08141709
.global GetCurrentSceneRecordIndex
.thumb_set GetCurrentSceneRecordIndex, 0x0800a019
.global SetIndexedSceneCommandValue
.thumb_set SetIndexedSceneCommandValue, 0x080c95c1
.global ApplySceneCommandOperands
.thumb_set ApplySceneCommandOperands, 0x08127af9
.ifndef OMIT_ProcessSceneActionRecordSelection
.global ProcessSceneActionRecordSelection
.thumb_set ProcessSceneActionRecordSelection, 0x08124481
.endif
.global ProcessSceneNibblePair
.thumb_set ProcessSceneNibblePair, 0x08124975
.global SetSceneEntityCoordinates
.thumb_set SetSceneEntityCoordinates, 0x08099e68
.global ApplySceneEntityStateMasks
.thumb_set ApplySceneEntityStateMasks, 0x0809a570
.global ClearSceneEntityAttachments
.thumb_set ClearSceneEntityAttachments, 0x0809a09c
.global UpdateSceneEntityAction
.thumb_set UpdateSceneEntityAction, 0x0809a2ac
.global RefreshSceneEntityPresentation
.thumb_set RefreshSceneEntityPresentation, 0x0809a530
.global ResolveSceneCommandHandle
.thumb_set ResolveSceneCommandHandle, 0x08125578
.global SetSceneRuntimeModeField
.thumb_set SetSceneRuntimeModeField, 0x08121d40
.global DispatchSceneCommandPayload
.thumb_set DispatchSceneCommandPayload, 0x08141570
.global SceneCommandRecordBlocksUpdateA
.thumb_set SceneCommandRecordBlocksUpdateA, 0x080c8364
.global SceneCommandRecordBlocksUpdateB
.thumb_set SceneCommandRecordBlocksUpdateB, 0x080c8348
.global DivideSignedValues
.thumb_set DivideSignedValues, 0x081426b8
.global ResolveSceneGridPosition
.thumb_set ResolveSceneGridPosition, 0x08124e75
.global ApplySceneSelectionAtPosition
.thumb_set ApplySceneSelectionAtPosition, 0x08127bc5
.global ApplySceneSelectionAtGridPosition
.thumb_set ApplySceneSelectionAtGridPosition, 0x08127c11
.global InitializeSceneModeThree
.thumb_set InitializeSceneModeThree, 0x0802b8e9
.global PrepareSceneModeNine
.thumb_set PrepareSceneModeNine, 0x081258cd
.global IsSceneModeNineReady
.thumb_set IsSceneModeNineReady, 0x0802dd59
.global RunSceneModeNine
.thumb_set RunSceneModeNine, 0x0812a061
.global RunSceneModeTen
.thumb_set RunSceneModeTen, 0x0812b209
.global RunSceneModeEleven
.thumb_set RunSceneModeEleven, 0x0812b231
.global RunSceneModeFourteen
.thumb_set RunSceneModeFourteen, 0x0812c511
.global ResolveCurrentSceneSelector
.thumb_set ResolveCurrentSceneSelector, 0x08036351
.global TestSceneSelectorState
.thumb_set TestSceneSelectorState, 0x08036441
.global GetSceneSelectorValueByIndex
.thumb_set GetSceneSelectorValueByIndex, 0x08036331
.global FindSceneSelectorFieldSlot
.thumb_set FindSceneSelectorFieldSlot, 0x080364bd
.global GetSceneSelectorCandidateIfUnused
.thumb_set GetSceneSelectorCandidateIfUnused, 0x080364fd
.ifndef OMIT_UpdateSceneSelectorRecordFields
.global UpdateSceneSelectorRecordFields
.thumb_set UpdateSceneSelectorRecordFields, 0x0803652d
.endif
.global BiosCpuSet
.thumb_set BiosCpuSet, 0x0814186c
.global PrepareRomRestartA
.thumb_set PrepareRomRestartA, 0x08145798
.global PrepareRomRestartB
.thumb_set PrepareRomRestartB, 0x081452f4
.global JumpToRomEntry
.thumb_set JumpToRomEntry, 0x08142244
.global BiosObjAffineSet
.thumb_set BiosObjAffineSet, 0x08141894
.global CountNameTextTokens
.thumb_set CountNameTextTokens, 0x0812b5d5
.global AcknowledgeInputEdge
.thumb_set AcknowledgeInputEdge, 0x080023d1
.global PlayNameEditorSound
.thumb_set PlayNameEditorSound, 0x08141541
.ifndef OMIT_ReadNameKeyboardToken
.global ReadNameKeyboardToken
.thumb_set ReadNameKeyboardToken, 0x0812b539
.endif
.global MeasureEditedNameWidth
.thumb_set MeasureEditedNameWidth, 0x0812b185
.global RedrawEditedName
.thumb_set RedrawEditedName, 0x0812ae8d
.global FindOrInsertRecord8
.thumb_set FindOrInsertRecord8, 0x08000fc8
.global GetJobProperty
.thumb_set GetJobProperty, 0x080c8570
.ifndef OMIT_GetUnitProperty
.global GetUnitProperty
.thumb_set GetUnitProperty, 0x080c92f0
.endif
.ifndef OMIT_GetGameFlag
.global GetGameFlag
.thumb_set GetGameFlag, 0x080c9540
.endif
.ifndef OMIT_SetGameFlag
.global SetGameFlag
.thumb_set SetGameFlag, 0x080c9574
.endif
.ifndef OMIT_ReadSaveByte
.global ReadSaveByte
.thumb_set ReadSaveByte, 0x080c95a8
.endif
.global ReadUnitField
.thumb_set ReadUnitField, 0x080c7ea4
.global UnitField27HasBit15
.thumb_set UnitField27HasBit15, 0x080c8240
.global UnitField27HasBit13
.thumb_set UnitField27HasBit13, 0x080c8260
.global AdjustInventoryReservedQuantity
.thumb_set AdjustInventoryReservedQuantity, 0x080cab25
.global UnitField01Equals
.thumb_set UnitField01Equals, 0x080c8194
.global ReadCurrentContentIndex
.thumb_set ReadCurrentContentIndex, 0x0800a018
.global ReadSelectedContentIndex
.thumb_set ReadSelectedContentIndex, 0x0800a024
.global GetRecord70Property
.thumb_set GetRecord70Property, 0x080ce4dd
.global DecodeTextPageEntry
.thumb_set DecodeTextPageEntry, 0x08013e9d
.global SetOpposingStateCounters
.thumb_set SetOpposingStateCounters, 0x080cd774
.global UnitField19IsZero
.thumb_set UnitField19IsZero, 0x080c8280
.ifndef OMIT_GetItemProperty
.global GetItemProperty
.thumb_set GetItemProperty, 0x080ca7a4
.endif
.ifndef OMIT_SyncPairedAbilityState
.global SyncPairedAbilityState
.thumb_set SyncPairedAbilityState, 0x080cd620
.endif
.global UnitHasPetrify
.thumb_set UnitHasPetrify, 0x080cd92c
.ifndef OMIT_GetEffectiveUnitSpeed
.global GetEffectiveUnitSpeed
.thumb_set GetEffectiveUnitSpeed, 0x0812e368
.endif
.global UnitBlocksChargeTime
.thumb_set UnitBlocksChargeTime, 0x080cdcec
.global ReadUnitCounterD8
.thumb_set ReadUnitCounterD8, 0x080ce3a0
.global UnitStateEDBit6
.thumb_set UnitStateEDBit6, 0x080cdcec
.global UnitStateE8HasBit6
.thumb_set UnitStateE8HasBit6, 0x080cd92c
.global UnitStateE9HasBit0
.thumb_set UnitStateE9HasBit0, 0x080cd95c
.global UnitStateE9HasBit3
.thumb_set UnitStateE9HasBit3, 0x080cd9a4
.global UnitStateE9HasBit4
.thumb_set UnitStateE9HasBit4, 0x080cd9bc
.global UnitStateE9HasBit7
.thumb_set UnitStateE9HasBit7, 0x080cda04
.ifndef OMIT_UnitStateEAHasBit7
.global UnitStateEAHasBit7
.thumb_set UnitStateEAHasBit7, 0x080cdadc
.endif
.ifndef OMIT_UnitStateEBHasBit2
.global UnitStateEBHasBit2
.thumb_set UnitStateEBHasBit2, 0x080cdb24
.endif
.ifndef OMIT_CanBattleUnitTakeTurn
.global CanBattleUnitTakeTurn
.thumb_set CanBattleUnitTakeTurn, 0x0812e4a8
.endif
.ifndef OMIT_ResolveBattleObjectById
.global ResolveBattleObjectById
.thumb_set ResolveBattleObjectById, 0x08022840
.endif
.ifndef OMIT_AllocateBattleRecordBlock
.global AllocateBattleRecordBlock
.thumb_set AllocateBattleRecordBlock, 0x08022840
.endif
.ifndef OMIT_RetailCall_080a433c
.global RetailCall_080a433c
.thumb_set RetailCall_080a433c, 0x080a433d
.endif
.ifndef OMIT_RetailCall_0809915c
.global RetailCall_0809915c
.thumb_set RetailCall_0809915c, 0x0809915d
.endif
.ifndef OMIT_RetailCall_0809920c
.global RetailCall_0809920c
.thumb_set RetailCall_0809920c, 0x0809920d
.endif
.ifndef OMIT_RetailCall_0809aac8
.global RetailCall_0809aac8
.thumb_set RetailCall_0809aac8, 0x0809aac9
.endif
.ifndef OMIT_RetailCall_080a22f0
.global RetailCall_080a22f0
.thumb_set RetailCall_080a22f0, 0x080a22f1
.endif
.ifndef OMIT_RetailCall_080a23b8
.global RetailCall_080a23b8
.thumb_set RetailCall_080a23b8, 0x080a23b9
.endif
.ifndef OMIT_RetailCall_080a4274
.global RetailCall_080a4274
.thumb_set RetailCall_080a4274, 0x080a4275
.endif
.ifndef OMIT_RetailCall_080b3150
.global RetailCall_080b3150
.thumb_set RetailCall_080b3150, 0x080b3151
.endif
.ifndef OMIT_RetailCall_080cd6a8
.global RetailCall_080cd6a8
.thumb_set RetailCall_080cd6a8, 0x080cd6a9
.endif
.ifndef OMIT_RetailCall_080cd8b4
.global RetailCall_080cd8b4
.thumb_set RetailCall_080cd8b4, 0x080cd8b5
.endif
.ifndef OMIT_RetailCall_080cd8e4
.global RetailCall_080cd8e4
.thumb_set RetailCall_080cd8e4, 0x080cd8e5
.endif
.ifndef OMIT_RetailCall_080cd92c
.global RetailCall_080cd92c
.thumb_set RetailCall_080cd92c, 0x080cd92d
.endif
.ifndef OMIT_RetailCall_080cd944
.global RetailCall_080cd944
.thumb_set RetailCall_080cd944, 0x080cd945
.endif
.ifndef OMIT_RetailCall_080cdaac
.global RetailCall_080cdaac
.thumb_set RetailCall_080cdaac, 0x080cdaad
.endif
.ifndef OMIT_RetailCall_080cdcbc
.global RetailCall_080cdcbc
.thumb_set RetailCall_080cdcbc, 0x080cdcbd
.endif
.ifndef OMIT_RetailCall_0812ea44
.global RetailCall_0812ea44
.thumb_set RetailCall_0812ea44, 0x0812ea45
.endif
.ifndef OMIT_RetailCall_08133b84
.global RetailCall_08133b84
.thumb_set RetailCall_08133b84, 0x08133b85
.endif
.ifndef OMIT_InitializeBattleTurnState
.global InitializeBattleTurnState
.thumb_set InitializeBattleTurnState, 0x0809de94
.endif
.ifndef OMIT_RunBattleTurnManager
.global RunBattleTurnManager
.thumb_set RunBattleTurnManager, 0x0809e1e0
.endif
.ifndef OMIT_ReleaseBattleObject
.global ReleaseBattleObject
.thumb_set ReleaseBattleObject, 0x08022854
.endif
.global UnitHasQuicken
.thumb_set UnitHasQuicken, 0x080cd8b4
.ifndef OMIT_AdvanceBattleChargeTime
.global AdvanceBattleChargeTime
.thumb_set AdvanceBattleChargeTime, 0x0809df7c
.endif
.global DecodeMissionItemId
.thumb_set DecodeMissionItemId, 0x080cb4a4
.global gSaveSection21A0
.equ gSaveSection21A0, 0x020021a0
.global gCopyRecordMemory
.equ gCopyRecordMemory, 0x0836d4bc

.global UnitHasIndexedRecord
.thumb_set UnitHasIndexedRecord, 0x080c817d

.global ReadRecordCopySource
.thumb_set ReadRecordCopySource, 0x080cbb7d

.global gUnitRecords14
.set gUnitRecords14, 0x085273d8

.global gRecordCopyBuffer
.set gRecordCopyBuffer, 0x03003a60

.ifndef OMIT_ApplyUnitJob
.global ApplyUnitJob
.thumb_set ApplyUnitJob, 0x080c8c25
.endif
.ifndef OMIT_ClearUnitEquipmentForJobChange
.global ClearUnitEquipmentForJobChange
.thumb_set ClearUnitEquipmentForJobChange, 0x080cb4c1
.endif
.global UnitField04Equals24
.thumb_set UnitField04Equals24, 0x080c8229

.global ReadJobRelatedValue
.thumb_set ReadJobRelatedValue, 0x080c9135

.global ReadClassValue
.thumb_set ReadClassValue, 0x080ccae9

.global gJobMapping
.set gJobMapping, 0x085231f4

.global gJobs
.set gJobs, 0x08521a14

.ifndef OMIT_ReadJobMappingValue
.global ReadJobMappingValue
.thumb_set ReadJobMappingValue, 0x080c93f1
.endif
.global gClearMemory
.equ gClearMemory, 0x0836d4b8
.global _call_via_r3
.thumb_set _call_via_r3, 0x08142251
.global _call_via_r4
.thumb_set _call_via_r4, 0x08142255
.global ReadTextMetricForPrefix
.thumb_set ReadTextMetricForPrefix, 0x08014779
.ifndef OMIT_TraceBattlePathSegment
.global TraceBattlePathSegment
.thumb_set TraceBattlePathSegment, 0x08148a0c
.endif
.global _call_via_r2
.thumb_set _call_via_r2, 0x0814224d
.global CalculateUnitSpeed
.thumb_set CalculateUnitSpeed, 0x080ca580
.global UnitStateECBit2
.thumb_set UnitStateECBit2, 0x080cda34
.global UnitStateEAHasBit1
.thumb_set UnitStateEAHasBit1, 0x080cda64
.global UnitStateEAHasBit5
.thumb_set UnitStateEAHasBit5, 0x080cdaac
.global UnitStateEAHasBit6
.thumb_set UnitStateEAHasBit6, 0x080cdac4

.global SetUnitStateE8Bit1
.thumb_set SetUnitStateE8Bit1, 0x080cdd1c
.global SetUnitStateE8Bit2
.thumb_set SetUnitStateE8Bit2, 0x080cdd40
.global SetUnitStateE8Bit3
.thumb_set SetUnitStateE8Bit3, 0x080cdd64
.global SetUnitStateE8Bit4
.thumb_set SetUnitStateE8Bit4, 0x080cdd88
.global SetUnitStateE8Bit5
.thumb_set SetUnitStateE8Bit5, 0x080cddac
.global SetUnitStateE8Bit6
.thumb_set SetUnitStateE8Bit6, 0x080cddd0
.global SetUnitStateE8Bit7
.thumb_set SetUnitStateE8Bit7, 0x080cddf4
.global SetUnitStateE9Bit1
.thumb_set SetUnitStateE9Bit1, 0x080cde38
.ifndef OMIT_SetUnitStateE9Bit0
.global SetUnitStateE9Bit0
.thumb_set SetUnitStateE9Bit0, 0x080cde14
.endif
.global SetUnitStateE9Bit2
.thumb_set SetUnitStateE9Bit2, 0x080cde5c
.global SetUnitStateE9Bit4
.thumb_set SetUnitStateE9Bit4, 0x080cdea4
.global SetUnitStateE9Bit5
.thumb_set SetUnitStateE9Bit5, 0x080cdec8
.global SetUnitStateE9Bit6
.thumb_set SetUnitStateE9Bit6, 0x080cdeec
.global SetUnitStateE9Bit7
.thumb_set SetUnitStateE9Bit7, 0x080cdf10
.global SetUnitStateEABit0
.thumb_set SetUnitStateEABit0, 0x080cdf30
.global SetUnitStateECBit2
.thumb_set SetUnitStateECBit2, 0x080cdf54
.global SetUnitStateECBit1
.thumb_set SetUnitStateECBit1, 0x080cdf78
.global SetUnitStateEABit1
.thumb_set SetUnitStateEABit1, 0x080cdf9c
.global SetUnitStateEABit2
.thumb_set SetUnitStateEABit2, 0x080cdfc0
.global SetUnitStateEABit4
.thumb_set SetUnitStateEABit4, 0x080cdfe4
.global SetUnitStateEABit5
.thumb_set SetUnitStateEABit5, 0x080ce008
.global SetUnitStateEABit6
.thumb_set SetUnitStateEABit6, 0x080ce02c
.global SetUnitStateEABit7
.thumb_set SetUnitStateEABit7, 0x080ce050
.global SetUnitStateEBBit0
.thumb_set SetUnitStateEBBit0, 0x080ce070
.global SetUnitStateEBBit1
.thumb_set SetUnitStateEBBit1, 0x080ce094
.global SetUnitStateEBBit2
.thumb_set SetUnitStateEBBit2, 0x080ce0b8
.global SetUnitStateEBBit3
.thumb_set SetUnitStateEBBit3, 0x080ce0dc
.global SetUnitStateEBBit4
.thumb_set SetUnitStateEBBit4, 0x080ce100
.global SetUnitStateEBBit5
.thumb_set SetUnitStateEBBit5, 0x080ce124
.global SetUnitStateEBBit6
.thumb_set SetUnitStateEBBit6, 0x080ce148
.global SetUnitStateEBBit7
.thumb_set SetUnitStateEBBit7, 0x080ce16c
.global SetUnitStateECBit0
.thumb_set SetUnitStateECBit0, 0x080ce18c
.global SetUnitStateEABit3
.thumb_set SetUnitStateEABit3, 0x080ce1b0
.global SetUnitStateEDBit3
.thumb_set SetUnitStateEDBit3, 0x080ce2f0
.global SetUnitStateECBit3
.thumb_set SetUnitStateECBit3, 0x080ce1d4
.global SetUnitStateECBit4
.thumb_set SetUnitStateECBit4, 0x080ce1f8
.global SetUnitStateECBit5
.thumb_set SetUnitStateECBit5, 0x080ce21c
.global SetUnitStateECBit6
.thumb_set SetUnitStateECBit6, 0x080ce240
.global SetUnitStateECBit7
.thumb_set SetUnitStateECBit7, 0x080ce264
.global SetUnitStateEDBit0
.thumb_set SetUnitStateEDBit0, 0x080ce284
.global SetUnitStateEDBit1
.thumb_set SetUnitStateEDBit1, 0x080ce2a8
.global SetUnitStateEDBit2
.thumb_set SetUnitStateEDBit2, 0x080ce2cc
.global WriteUnitCounterD8
.thumb_set WriteUnitCounterD8, 0x080ce418
.global WriteUnitCounterD9
.thumb_set WriteUnitCounterD9, 0x080ce420
.global WriteUnitCounterDA
.thumb_set WriteUnitCounterDA, 0x080ce428
.global WriteUnitCounterDB
.thumb_set WriteUnitCounterDB, 0x080ce430
.global WriteUnitCounterDC
.thumb_set WriteUnitCounterDC, 0x080ce438
.global WriteUnitCounterDD
.thumb_set WriteUnitCounterDD, 0x080ce440
.global WriteUnitCounterDE
.thumb_set WriteUnitCounterDE, 0x080ce448
.global WriteUnitCounterDF
.thumb_set WriteUnitCounterDF, 0x080ce450
.global WriteUnitCounterE0
.thumb_set WriteUnitCounterE0, 0x080ce458
.global WriteUnitCounterE1
.thumb_set WriteUnitCounterE1, 0x080ce460
.global WriteUnitCounterE2
.thumb_set WriteUnitCounterE2, 0x080ce468
.global WriteUnitCounterE3
.thumb_set WriteUnitCounterE3, 0x080ce470
.global WriteUnitCounterE4
.thumb_set WriteUnitCounterE4, 0x080ce478
.global WriteUnitCounterE5
.thumb_set WriteUnitCounterE5, 0x080ce480
.global WriteUnitCounterE6
.thumb_set WriteUnitCounterE6, 0x080ce488
.ifndef OMIT_UseThreeForBattleCounterD8
.global UseThreeForBattleCounterD8
.thumb_set UseThreeForBattleCounterD8, 0x08131030
.endif
.global EvaluateBattleCounterD8Condition
.thumb_set EvaluateBattleCounterD8Condition, 0x081308f4
.global GetSceneSelectorCategory
.thumb_set GetSceneSelectorCategory, 0x08038cdc

.ifndef OMIT_CompactSaveRecords64
.global CompactSaveRecords64
.thumb_set CompactSaveRecords64, 0x080caa74
.endif
.global DispatchCompactSaveRecords
.thumb_set DispatchCompactSaveRecords, 0x080028c8

.ifndef OMIT_GetMissionProperty
.global GetMissionProperty
.thumb_set GetMissionProperty, 0x080ce4dd
.endif

.ifndef OMIT_CountPendingHalfwordRecords
.global CountPendingHalfwordRecords
.thumb_set CountPendingHalfwordRecords, 0x080cca80
.endif
.global CompactPendingHalfwordRecords
.thumb_set CompactPendingHalfwordRecords, 0x080cc2b4
.global GetBattleObjectOwner
.thumb_set GetBattleObjectOwner, 0x08021c3c
.global SetBattleObjectFlag
.thumb_set SetBattleObjectFlag, 0x08021de4
.global GetBattleObjectFlags
.thumb_set GetBattleObjectFlags, 0x08021de0

.global IsBattleCoordinateWithinMap
.thumb_set IsBattleCoordinateWithinMap, 0x0801cc7c

.global GetBattleCoordinateFlags
.thumb_set GetBattleCoordinateFlags, 0x0801cd08

.global Routine_08141540
.thumb_set Routine_08141540, 0x08141540

.global GetBattleCoordinateOccupant
.thumb_set GetBattleCoordinateOccupant, 0x08149384

.global GetBattleCoordinateValue
.thumb_set GetBattleCoordinateValue, 0x081493ac

.ifndef OMIT_IsMissionRequirementStateSatisfied
.global IsMissionRequirementStateSatisfied
.thumb_set IsMissionRequirementStateSatisfied, 0x080ceecc
.endif

@ External interfaces used by recovered mission progression modules.
.global IsSceneSelectorActive
.thumb_set IsSceneSelectorActive, 0x08036441
.global HasInventoryItem
.thumb_set HasInventoryItem, 0x080cb321
.global WriteSaveByte
.thumb_set WriteSaveByte, 0x080c95c1
.global AddInventoryItem
.thumb_set AddInventoryItem, 0x080ca901
.global gSaveData
.set gSaveData, 0x02000000
.global gContentState
.set gContentState, 0x020020d0

.global ReadMissionCategoryNibble
.thumb_set ReadMissionCategoryNibble, 0x080cb9cd

.global gEquipmentClassMasks
.set gEquipmentClassMasks, 0x0851d0f4

.global GetAbilityListEntry
.thumb_set GetAbilityListEntry, 0x080cd481

.global EquipmentProvidesAbility
.thumb_set EquipmentProvidesAbility, 0x080cd1fd
.ifndef OMIT_ApplyItemAbilityFlags
.global ApplyItemAbilityFlags
.thumb_set ApplyItemAbilityFlags, 0x080ccf45
.endif

.global CheckEquipmentSet
.thumb_set CheckEquipmentSet, 0x080caba9

.global ReleaseEventRuntimeObject
.thumb_set ReleaseEventRuntimeObject, 0x08005a25

.global GetEventRuntimePayload
.thumb_set GetEventRuntimePayload, 0x08005bfd

.global GetInventoryPartition
.thumb_set GetInventoryPartition, 0x080cb211

.global IsItemIdInRange1To252
.thumb_set IsItemIdInRange1To252, 0x080cb1f5

.ifndef OMIT_UnitItemCategoryAllowed
.global UnitItemCategoryAllowed
.thumb_set UnitItemCategoryAllowed, 0x080cb451
.endif

.ifndef OMIT_GetInventoryItemClass
.global GetInventoryItemClass
.thumb_set GetInventoryItemClass, 0x080cbd35
.endif

@ Observed item-adjustment descriptors and selector helper.
.global gItemAdjustment2
.set gItemAdjustment2, 0x08528a44
.global gItemAdjustment3
.set gItemAdjustment3, 0x08528aa4
.global gItemAdjustment4
.set gItemAdjustment4, 0x08528b04
.global gItemAdjustment5
.set gItemAdjustment5, 0x08528b64
.global gItemAdjustment6
.set gItemAdjustment6, 0x08528bc4
.ifndef OMIT_GetItemAdjustmentRecord
.global GetItemAdjustmentRecord
.thumb_set GetItemAdjustmentRecord, 0x080cccf1
.endif
.ifndef OMIT_ItemAmountAdjustmentApplies
.global ItemAmountAdjustmentApplies
.thumb_set ItemAmountAdjustmentApplies, 0x080cc959
.endif
.global gItems
.set gItems, 0x0851d180
.global gAmountRecords10
.set gAmountRecords10, 0x08527e62
.ifndef OMIT_CalculateItemAmount
.global CalculateItemAmount
.thumb_set CalculateItemAmount, 0x080cbc15
.endif
.ifndef OMIT_ReadItemAdjustmentEntry
.global ReadItemAdjustmentEntry
.thumb_set ReadItemAdjustmentEntry, 0x080cc9f1
.endif
.ifndef OMIT_ItemInAdjustmentList
.global ItemInAdjustmentList
.thumb_set ItemInAdjustmentList, 0x080cc9a1
.endif
.global BattleSetupRoutine_814224C
.thumb_set BattleSetupRoutine_814224C, 0x0814224c
.global CountBattleUnitRecords
.thumb_set CountBattleUnitRecords, 0x08099cdc
.global CountLinkedNodes
.thumb_set CountLinkedNodes, 0x080c7b09
.global _call_via_r6
.thumb_set _call_via_r6, 0x0814225d
.global _call_via_r2
.thumb_set _call_via_r2, 0x0814224d
.global GetListOwnerWord0
.thumb_set GetListOwnerWord0, 0x080c7b75
.ifndef OMIT_VisitLinkedNodes
.global VisitLinkedNodes
.thumb_set VisitLinkedNodes, 0x080c7cc1
.endif
.global BattleListNodeVisitCallback
.thumb_set BattleListNodeVisitCallback, 0x080221e5
.global InitializeBattleUnitRecord
.thumb_set InitializeBattleUnitRecord, 0x08142250
.ifndef OMIT_SelectNextBattleUnit
.global SelectNextBattleUnit
.thumb_set SelectNextBattleUnit, 0x0809e05c
.endif
.ifndef OMIT_TickOpposingStateCounters
.global TickOpposingStateCounters
.thumb_set TickOpposingStateCounters, 0x080cd7f0
.endif
.ifndef OMIT_ResetBattleUnitTransientState
.global ResetBattleUnitTransientState
.thumb_set ResetBattleUnitTransientState, 0x08097298
.endif
.global BattleUnitGate_8131030
.thumb_set BattleUnitGate_8131030, 0x08131030
.global BattleUnitEffect_8133BB4
.thumb_set BattleUnitEffect_8133BB4, 0x08133bb4
.global gBattleDirectionButtons
.set gBattleDirectionButtons, 0x0200f3a4
.global gBattleGridDirectionButtons
.set gBattleGridDirectionButtons, 0x0200f3a6
.global gBattleDirectionMappingModeByte
.set gBattleDirectionMappingModeByte, 0x02002fc0
.global gIWRAMHalfwordAt03000004
.set gIWRAMHalfwordAt03000004, 0x03000004
.global HandleMovementModeThree
.thumb_set HandleMovementModeThree, 0x08025175
.ifndef OMIT_UpdateBattleMovementGrid
.global UpdateBattleMovementGrid
.thumb_set UpdateBattleMovementGrid, 0x08024ad9
.endif
.global GetSceneRecordPixelX
.thumb_set GetSceneRecordPixelX, 0x08035a21
.global GetSceneRecordPixelY
.thumb_set GetSceneRecordPixelY, 0x08035a45
.global SetDisplayRecordPosition
.thumb_set SetDisplayRecordPosition, 0x0804c789
.ifndef OMIT_UnitStateE8HasBit2
.global UnitStateE8HasBit2
.thumb_set UnitStateE8HasBit2, 0x080cd8cc
.endif
.ifndef OMIT_UnitStateE8HasBit3
.global UnitStateE8HasBit3
.thumb_set UnitStateE8HasBit3, 0x080cd8e4
.endif
.ifndef OMIT_UnitStateE9HasBit1
.global UnitStateE9HasBit1
.thumb_set UnitStateE9HasBit1, 0x080cd974
.endif
.ifndef OMIT_UnitStateEAHasBit4
.global UnitStateEAHasBit4
.thumb_set UnitStateEAHasBit4, 0x080cda94
.endif
.ifndef OMIT_UnitStateEBHasBit0
.global UnitStateEBHasBit0
.thumb_set UnitStateEBHasBit0, 0x080cdaf4
.endif
.ifndef OMIT_UnitStateEBHasBit1
.global UnitStateEBHasBit1
.thumb_set UnitStateEBHasBit1, 0x080cdb0c
.endif
.ifndef OMIT_UnitStateEBHasBit3
.global UnitStateEBHasBit3
.thumb_set UnitStateEBHasBit3, 0x080cdb3c
.endif
.ifndef OMIT_UnitStateEBHasBit4
.global UnitStateEBHasBit4
.thumb_set UnitStateEBHasBit4, 0x080cdb54
.endif
.ifndef OMIT_UnitStateEBHasBit5
.global UnitStateEBHasBit5
.thumb_set UnitStateEBHasBit5, 0x080cdb6c
.endif
.ifndef OMIT_UnitStateEBHasBit6
.global UnitStateEBHasBit6
.thumb_set UnitStateEBHasBit6, 0x080cdb84
.endif
.ifndef OMIT_UnitStateEBHasBit7
.global UnitStateEBHasBit7
.thumb_set UnitStateEBHasBit7, 0x080cdb9c
.endif
.ifndef OMIT_UnitStateECBit0
.global UnitStateECBit0
.thumb_set UnitStateECBit0, 0x080cdbb4
.endif
.ifndef OMIT_ReadUnitCounterD9
.global ReadUnitCounterD9
.thumb_set ReadUnitCounterD9, 0x080ce3a8
.endif
.ifndef OMIT_ReadUnitCounterDA
.global ReadUnitCounterDA
.thumb_set ReadUnitCounterDA, 0x080ce3b0
.endif
.ifndef OMIT_ReadUnitCounterDB
.global ReadUnitCounterDB
.thumb_set ReadUnitCounterDB, 0x080ce3b8
.endif
.ifndef OMIT_ReadUnitCounterDC
.global ReadUnitCounterDC
.thumb_set ReadUnitCounterDC, 0x080ce3c0
.endif
.ifndef OMIT_ReadUnitCounterDD
.global ReadUnitCounterDD
.thumb_set ReadUnitCounterDD, 0x080ce3c8
.endif
.ifndef OMIT_ReadUnitCounterDE
.global ReadUnitCounterDE
.thumb_set ReadUnitCounterDE, 0x080ce3d0
.endif
.ifndef OMIT_ReadUnitCounterDF
.global ReadUnitCounterDF
.thumb_set ReadUnitCounterDF, 0x080ce3d8
.endif
.ifndef OMIT_ReadUnitCounterE0
.global ReadUnitCounterE0
.thumb_set ReadUnitCounterE0, 0x080ce3e0
.endif
.ifndef OMIT_ReadUnitCounterE1
.global ReadUnitCounterE1
.thumb_set ReadUnitCounterE1, 0x080ce3e8
.endif
.ifndef OMIT_ReadUnitCounterE2
.global ReadUnitCounterE2
.thumb_set ReadUnitCounterE2, 0x080ce3f0
.endif
.ifndef OMIT_ReadUnitCounterE3
.global ReadUnitCounterE3
.thumb_set ReadUnitCounterE3, 0x080ce3f8
.endif
.ifndef OMIT_ReadUnitCounterE4
.global ReadUnitCounterE4
.thumb_set ReadUnitCounterE4, 0x080ce400
.endif
.ifndef OMIT_ReadUnitCounterE5
.global ReadUnitCounterE5
.thumb_set ReadUnitCounterE5, 0x080ce408
.endif

.global WriteTextControlMarker
.thumb_set WriteTextControlMarker, 0x08018c95
.ifndef OMIT_GetContentPointer123
.global GetContentPointer123
.thumb_set GetContentPointer123, 0x080cb525
.endif
.ifndef OMIT_FindJobMappingKey
.global FindJobMappingKey
.thumb_set FindJobMappingKey, 0x080c9401
.endif
.ifndef OMIT_GetMissionPropertyByte
.global GetMissionPropertyByte
.thumb_set GetMissionPropertyByte, 0x080ce4dd
.endif
.global ResolveMissionTextValue
.thumb_set ResolveMissionTextValue, 0x080cec79
.global ResolveContextTextPointer
.thumb_set ResolveContextTextPointer, 0x080ceb35

.global TextRoutine_08013528
.thumb_set TextRoutine_08013528, 0x08013529
.global TextRoutine_08013728
.thumb_set TextRoutine_08013728, 0x08013729
.global TextRoutine_08015110
.thumb_set TextRoutine_08015110, 0x08015111
.global ClearTextContextRecordRange
.thumb_set ClearTextContextRecordRange, 0x08013859
.global CopyTextContextRecordFields
.thumb_set CopyTextContextRecordFields, 0x08013911
.global ApplyTextContextGlyphOffset
.thumb_set ApplyTextContextGlyphOffset, 0x0801348d
.global LoadTextGlyphBitmapAndWidth
.thumb_set LoadTextGlyphBitmapAndWidth, 0x0801344d
.global CopyTextContextRecordToBuffer
.thumb_set CopyTextContextRecordToBuffer, 0x08013891
.global OverlayTextContextGlyphRows
.thumb_set OverlayTextContextGlyphRows, 0x080139b9
.global TextRoutine_0801360C
.thumb_set TextRoutine_0801360C, 0x0801360d
.global TextRoutine_080137C0
.thumb_set TextRoutine_080137C0, 0x080137c1
.global TextRoutine_08015DAC
.thumb_set TextRoutine_08015DAC, 0x08015dad
.global TextRoutine_08018CEC
.thumb_set TextRoutine_08018CEC, 0x08018ced
.global TextRoutine_08016070
.thumb_set TextRoutine_08016070, 0x08016071
.global TextRoutine_0801624C
.thumb_set TextRoutine_0801624C, 0x0801624d
.ifndef OMIT_RenderTextTileRectangle_08016268
.global RenderTextTileRectangle_08016268
.thumb_set RenderTextTileRectangle_08016268, 0x08016269
.endif
.ifndef OMIT_RenderTextLayoutContent_08016344
.global RenderTextLayoutContent_08016344
.thumb_set RenderTextLayoutContent_08016344, 0x08016345
.endif
.ifndef OMIT_FillTextHalfwordRows_08016560
.global FillTextHalfwordRows_08016560
.thumb_set FillTextHalfwordRows_08016560, 0x08016561
.endif
.ifndef OMIT_RenderTextSpecialFrame_080165C4
.global RenderTextSpecialFrame_080165C4
.thumb_set RenderTextSpecialFrame_080165C4, 0x080165c5
.endif
.ifndef OMIT_RenderTextAlternateTiles_08016800
.global RenderTextAlternateTiles_08016800
.thumb_set RenderTextAlternateTiles_08016800, 0x08016801
.endif
.ifndef OMIT_WriteTextTileGridBorder_0801692C
.global WriteTextTileGridBorder_0801692C
.thumb_set WriteTextTileGridBorder_0801692C, 0x0801692d
.endif
.ifndef OMIT_RenderTextFramedTileGrid_08016800
.global RenderTextFramedTileGrid_08016800
.thumb_set RenderTextFramedTileGrid_08016800, 0x08016801
.endif

.ifndef OMIT_DetachFreePoolBlock_08006DA0
.global DetachFreePoolBlock_08006DA0
.thumb_set DetachFreePoolBlock_08006DA0, 0x08006da1
.endif
.ifndef OMIT_InsertFreePoolBlock_08006E28
.global InsertFreePoolBlock_08006E28
.thumb_set InsertFreePoolBlock_08006E28, 0x08006e29
.endif
.ifndef OMIT_AllocatePoolBlockWords_08006EC0
.global AllocatePoolBlockWords_08006EC0
.thumb_set AllocatePoolBlockWords_08006EC0, 0x08006ec1
.endif
.ifndef OMIT_CoalesceReleasedPoolBlock_08006FCC
.global CoalesceReleasedPoolBlock_08006FCC
.thumb_set CoalesceReleasedPoolBlock_08006FCC, 0x08006fcd
.endif
.ifndef OMIT_InitializePool_080070C8
.global InitializePool_080070C8
.thumb_set InitializePool_080070C8, 0x080070c9
.endif
.ifndef OMIT_GetPoolAllocationSize_0800717C
.global GetPoolAllocationSize_0800717C
.thumb_set GetPoolAllocationSize_0800717C, 0x0800717d
.endif
.ifndef OMIT_FindIndexedTreeNeighbors
.global FindIndexedTreeNeighbors
.thumb_set FindIndexedTreeNeighbors, 0x08006c89
.endif
.ifndef OMIT_RecoveredInitializeIndexedTreeFreeHead
.global RecoveredInitializeIndexedTreeFreeHead
.thumb_set RecoveredInitializeIndexedTreeFreeHead, 0x08006d39
.endif
.global _call_via_r5
.thumb_set _call_via_r5, 0x08142259

.ifndef OMIT_AdvanceSceneTransition_08122160
.global AdvanceSceneTransition_08122160
.thumb_set AdvanceSceneTransition_08122160, 0x08122161
.endif
.ifndef OMIT_RunSceneCommandLoop_08122ABC
.global RunSceneCommandLoop_08122ABC
.thumb_set RunSceneCommandLoop_08122ABC, 0x08122abd
.endif
.ifndef OMIT_SceneHelper_08004C40
.global SceneHelper_08004C40
.thumb_set SceneHelper_08004C40, 0x08004c41
.endif
.ifndef OMIT_SceneHelper_080058A4
.global SceneHelper_080058A4
.thumb_set SceneHelper_080058A4, 0x080058a5
.endif
.ifndef OMIT_SceneHelper_08005B18
.global SceneHelper_08005B18
.thumb_set SceneHelper_08005B18, 0x08005b19
.endif
.ifndef OMIT_SceneHelper_08005BFC
.global SceneHelper_08005BFC
.thumb_set SceneHelper_08005BFC, 0x08005bfd
.endif
.ifndef OMIT_SceneHelper_08005C04
.global SceneHelper_08005C04
.thumb_set SceneHelper_08005C04, 0x08005c05
.endif
.ifndef OMIT_SceneHelper_08005C14
.global SceneHelper_08005C14
.thumb_set SceneHelper_08005C14, 0x08005c15
.endif
.ifndef OMIT_SceneHelper_08005C34
.global SceneHelper_08005C34
.thumb_set SceneHelper_08005C34, 0x08005c35
.endif
.ifndef OMIT_SceneHelper_08009A14
.global SceneHelper_08009A14
.thumb_set SceneHelper_08009A14, 0x08009a15
.endif
.ifndef OMIT_SceneHelper_08022E90
.global SceneHelper_08022E90
.thumb_set SceneHelper_08022E90, 0x08022e91
.endif
.ifndef OMIT_SceneHelper_0803600C
.global SceneHelper_0803600C
.thumb_set SceneHelper_0803600C, 0x0803600d
.endif
.ifndef OMIT_SceneHelper_080C72E4
.global SceneHelper_080C72E4
.thumb_set SceneHelper_080C72E4, 0x080c72e5
.endif
.ifndef OMIT_SceneHelper_080C74B4
.global SceneHelper_080C74B4
.thumb_set SceneHelper_080C74B4, 0x080c74b5
.endif
.ifndef OMIT_SceneHelper_080C7548
.global SceneHelper_080C7548
.thumb_set SceneHelper_080C7548, 0x080c7549
.endif
.ifndef OMIT_SceneHelper_080C9574
.global SceneHelper_080C9574
.thumb_set SceneHelper_080C9574, 0x080c9575
.endif
.ifndef OMIT_SceneHelper_080D241C
.global SceneHelper_080D241C
.thumb_set SceneHelper_080D241C, 0x080d241d
.endif
.ifndef OMIT_SceneHelper_080D37C4
.global SceneHelper_080D37C4
.thumb_set SceneHelper_080D37C4, 0x080d37c5
.endif
.ifndef OMIT_SceneHelper_080D37F8
.global SceneHelper_080D37F8
.thumb_set SceneHelper_080D37F8, 0x080d37f9
.endif
.ifndef OMIT_SceneHelper_080D3864
.global SceneHelper_080D3864
.thumb_set SceneHelper_080D3864, 0x080d3865
.endif
.ifndef OMIT_SceneHelper_080D3878
.global SceneHelper_080D3878
.thumb_set SceneHelper_080D3878, 0x080d3879
.endif
.ifndef OMIT_SceneHelper_08121B8C
.global SceneHelper_08121B8C
.thumb_set SceneHelper_08121B8C, 0x08121b8d
.endif
.ifndef OMIT_SceneHelper_08121D0C
.global SceneHelper_08121D0C
.thumb_set SceneHelper_08121D0C, 0x08121d0d
.endif
.ifndef OMIT_SceneHelper_08121DA8
.global SceneHelper_08121DA8
.thumb_set SceneHelper_08121DA8, 0x08121da9
.endif
.ifndef OMIT_SceneHelper_08121DBC
.global SceneHelper_08121DBC
.thumb_set SceneHelper_08121DBC, 0x08121dbd
.endif
.ifndef OMIT_SceneHelper_08121E1C
.global SceneHelper_08121E1C
.thumb_set SceneHelper_08121E1C, 0x08121e1d
.endif
.ifndef OMIT_SceneHelper_08124CE8
.global SceneHelper_08124CE8
.thumb_set SceneHelper_08124CE8, 0x08124ce9
.endif
.ifndef OMIT_SceneHelper_081253CC
.global SceneHelper_081253CC
.thumb_set SceneHelper_081253CC, 0x081253cd
.endif
.ifndef OMIT_SceneHelper_081256C8
.global SceneHelper_081256C8
.thumb_set SceneHelper_081256C8, 0x081256c9
.endif
.ifndef OMIT_SceneHelper_081258AC
.global SceneHelper_081258AC
.thumb_set SceneHelper_081258AC, 0x081258ad
.endif
.ifndef OMIT_SceneTaskCallback_08121FB8
.global SceneTaskCallback_08121FB8
.thumb_set SceneTaskCallback_08121FB8, 0x08121fb9
.endif

@ Scene entity consumer batch 02 aliases.
.ifndef OMIT_ApplySceneEntityOperation_0809836C
.global ApplySceneEntityOperation_0809836C
.thumb_set ApplySceneEntityOperation_0809836C, 0x809836d
.endif
.ifndef OMIT_EntityHelper_0801CC18
.global EntityHelper_0801CC18
.thumb_set EntityHelper_0801CC18, 0x801cc19
.endif
.ifndef OMIT_EntityHelper_08099560
.global EntityHelper_08099560
.thumb_set EntityHelper_08099560, 0x8099561
.endif
.ifndef OMIT_EntityHelper_080C8240
.global EntityHelper_080C8240
.thumb_set EntityHelper_080C8240, 0x80c8241
.endif
.ifndef OMIT_EntityHelper_080C8260
.global EntityHelper_080C8260
.thumb_set EntityHelper_080C8260, 0x80c8261
.endif
.ifndef OMIT_EntityHelper_080C8280
.global EntityHelper_080C8280
.thumb_set EntityHelper_080C8280, 0x80c8281
.endif
.ifndef OMIT_EntityHelper_080C8298
.global EntityHelper_080C8298
.thumb_set EntityHelper_080C8298, 0x80c8299
.endif
.ifndef OMIT_EntityHelper_080C83CC
.global EntityHelper_080C83CC
.thumb_set EntityHelper_080C83CC, 0x80c83cd
.endif
.ifndef OMIT_EntityHelper_080CD92C
.global EntityHelper_080CD92C
.thumb_set EntityHelper_080CD92C, 0x80cd92d
.endif
.ifndef OMIT_EntityHelper_080CDA04
.global EntityHelper_080CDA04
.thumb_set EntityHelper_080CDA04, 0x80cda05
.endif
.ifndef OMIT_EntityHelper_080CDADC
.global EntityHelper_080CDADC
.thumb_set EntityHelper_080CDADC, 0x80cdadd
.endif
.ifndef OMIT_EntityHelper_080CDB24
.global EntityHelper_080CDB24
.thumb_set EntityHelper_080CDB24, 0x80cdb25
.endif
.ifndef OMIT_EntityHelper_080CE380
.global EntityHelper_080CE380
.thumb_set EntityHelper_080CE380, 0x80ce381
.endif
.ifndef OMIT_EntityHelper_08121B64
.global EntityHelper_08121B64
.thumb_set EntityHelper_08121B64, 0x8121b65
.endif
.ifndef OMIT_EntityHelper_08121B78
.global EntityHelper_08121B78
.thumb_set EntityHelper_08121B78, 0x8121b79
.endif
.ifndef OMIT_EntityHelper_08121C58
.global EntityHelper_08121C58
.thumb_set EntityHelper_08121C58, 0x8121c59
.endif
.ifndef OMIT_EntityHelper_08121CB4
.global EntityHelper_08121CB4
.thumb_set EntityHelper_08121CB4, 0x8121cb5
.endif
.ifndef OMIT_FilterSceneEntitiesForTransition_08124850
.global FilterSceneEntitiesForTransition_08124850
.thumb_set FilterSceneEntitiesForTransition_08124850, 0x8124851
.endif
.ifndef OMIT_UpdateSceneEntityActions_081247B4
.global UpdateSceneEntityActions_081247B4
.thumb_set UpdateSceneEntityActions_081247B4, 0x81247b5
.endif

@ Scene placement batch 03 helpers validated by retail call-site preflight.
.ifndef OMIT_DetermineSceneFacing_08124ACC
.global DetermineSceneFacing_08124ACC
.thumb_set DetermineSceneFacing_08124ACC, 0x8124acd
.endif
.ifndef OMIT_PlacementHelper_08002804
.global PlacementHelper_08002804
.thumb_set PlacementHelper_08002804, 0x8002805
.endif
.ifndef OMIT_PlacementHelper_0801CC18
.global PlacementHelper_0801CC18
.thumb_set PlacementHelper_0801CC18, 0x801cc19
.endif
.ifndef OMIT_PlacementHelper_08092440
.global PlacementHelper_08092440
.thumb_set PlacementHelper_08092440, 0x8092441
.endif
.ifndef OMIT_PlacementHelper_08099560
.global PlacementHelper_08099560
.thumb_set PlacementHelper_08099560, 0x8099561
.endif
.ifndef OMIT_PlacementHelper_08099644
.global PlacementHelper_08099644
.thumb_set PlacementHelper_08099644, 0x8099645
.endif
.ifndef OMIT_PlacementHelper_0809A304
.global PlacementHelper_0809A304
.thumb_set PlacementHelper_0809A304, 0x809a305
.endif
.ifndef OMIT_PlacementHelper_080C6858
.global PlacementHelper_080C6858
.thumb_set PlacementHelper_080C6858, 0x80c6859
.endif
.ifndef OMIT_PlacementHelper_080C8240
.global PlacementHelper_080C8240
.thumb_set PlacementHelper_080C8240, 0x80c8241
.endif
.ifndef OMIT_PlacementHelper_080C83CC
.global PlacementHelper_080C83CC
.thumb_set PlacementHelper_080C83CC, 0x80c83cd
.endif
.ifndef OMIT_PlacementHelper_080C95A8
.global PlacementHelper_080C95A8
.thumb_set PlacementHelper_080C95A8, 0x80c95a9
.endif
.ifndef OMIT_PlacementHelper_080C9644
.global PlacementHelper_080C9644
.thumb_set PlacementHelper_080C9644, 0x80c9645
.endif
.ifndef OMIT_PlacementHelper_08121C70
.global PlacementHelper_08121C70
.thumb_set PlacementHelper_08121C70, 0x8121c71
.endif
.ifndef OMIT_PlacementHelper_08121CB4
.global PlacementHelper_08121CB4
.thumb_set PlacementHelper_08121CB4, 0x8121cb5
.endif
.ifndef OMIT_PlacementHelper_08121E08
.global PlacementHelper_08121E08
.thumb_set PlacementHelper_08121E08, 0x8121e09
.endif
.ifndef OMIT_PlacementHelper_081242A0
.global PlacementHelper_081242A0
.thumb_set PlacementHelper_081242A0, 0x81242a1
.endif
.ifndef OMIT_PlacementHelper_08124710
.global PlacementHelper_08124710
.thumb_set PlacementHelper_08124710, 0x8124711
.endif
.ifndef OMIT_RefreshSceneUnitPlacement_08124CE8
.global RefreshSceneUnitPlacement_08124CE8
.thumb_set RefreshSceneUnitPlacement_08124CE8, 0x8124ce9
.endif

/* MODEL-C01 caller labels; owned entries and Thumb bits come from scope.json. */
.ifndef OMIT_UnitModelCall_CA2E8
.global UnitModelCall_CA2E8
.thumb_set UnitModelCall_CA2E8, 0x080ca2e9
.endif
.ifndef OMIT_UnitModelCall_CA394
.global UnitModelCall_CA394
.thumb_set UnitModelCall_CA394, 0x080ca395
.endif
.ifndef OMIT_UnitModelCall_CA624
.global UnitModelCall_CA624
.thumb_set UnitModelCall_CA624, 0x080ca625
.endif
.ifndef OMIT_UnitModelCall_CA66C
.global UnitModelCall_CA66C
.thumb_set UnitModelCall_CA66C, 0x080ca66d
.endif
.ifndef OMIT_UnitModelCall_CA6B4
.global UnitModelCall_CA6B4
.thumb_set UnitModelCall_CA6B4, 0x080ca6b5
.endif
.ifndef OMIT_UnitModelCall_CA6FC
.global UnitModelCall_CA6FC
.thumb_set UnitModelCall_CA6FC, 0x080ca6fd
.endif
.ifndef OMIT_UnitModelCall_CA4F0
.global UnitModelCall_CA4F0
.thumb_set UnitModelCall_CA4F0, 0x080ca4f1
.endif
.ifndef OMIT_UnitModelExternalCall_CA900
.global UnitModelExternalCall_CA900
.thumb_set UnitModelExternalCall_CA900, 0x080ca901
.endif
.ifndef OMIT_UnitModelExternalCall_CCF44
.global UnitModelExternalCall_CCF44
.thumb_set UnitModelExternalCall_CCF44, 0x080ccf45
.endif

/* ARM7TDMI register-call veneers used by C function-pointer calls. */
.global _call_via_r0
.thumb_set _call_via_r0, 0x08142245
.global _call_via_r1
.thumb_set _call_via_r1, 0x08142249

.ifndef OMIT_C02_GetCE8A8
.global C02_GetCE8A8
.thumb_set C02_GetCE8A8, 0x080ce8a9
.endif
.ifndef OMIT_C02_GetCED2C
.global C02_GetCED2C
.thumb_set C02_GetCED2C, 0x080ced2d
.endif
.ifndef OMIT_C02_ExpiredStateZero
.global C02_ExpiredStateZero
.thumb_set C02_ExpiredStateZero, 0x080cf061
.endif
.ifndef OMIT_C02_ExpiredStateFollowup
.global C02_ExpiredStateFollowup
.thumb_set C02_ExpiredStateFollowup, 0x080cf119
.endif

.ifndef OMIT_CallBattleContextSwap_080A21B4
.global CallBattleContextSwap_080A21B4
.thumb_set CallBattleContextSwap_080A21B4, 0x080a21b5
.endif
.ifndef OMIT_BattleRecordProperty_080CCD50
.global BattleRecordProperty_080CCD50
.thumb_set BattleRecordProperty_080CCD50, 0x080ccd51
.endif
.ifndef OMIT_BattleRecordReplacement_08099494
.global BattleRecordReplacement_08099494
.thumb_set BattleRecordReplacement_08099494, 0x08099495
.endif
.ifndef OMIT_BattleRecordInitialGate_080C8280
.global BattleRecordInitialGate_080C8280
.thumb_set BattleRecordInitialGate_080C8280, 0x080c8281
.endif
.ifndef OMIT_BattleRecordZeroState_0812F17C
.global BattleRecordZeroState_0812F17C
.thumb_set BattleRecordZeroState_0812F17C, 0x0812f17d
.endif
.ifndef OMIT_BattleRecordSkipCounters_080CD8CC
.global BattleRecordSkipCounters_080CD8CC
.thumb_set BattleRecordSkipCounters_080CD8CC, 0x080cd8cd
.endif
.ifndef OMIT_BattleRecordIncrementCounter_080C8240
.global BattleRecordIncrementCounter_080C8240
.thumb_set BattleRecordIncrementCounter_080C8240, 0x080c8241
.endif
.ifndef OMIT_BattleRecordRefreshContext_08099BAC
.global BattleRecordRefreshContext_08099BAC
.thumb_set BattleRecordRefreshContext_08099BAC, 0x08099bad
.endif

/* Direct retail callees used by BattleTargetResolver_000A23B8. */
.global RetailCall_08099bac
.thumb_set RetailCall_08099bac, 0x08099bad
.global RetailCall_0809a740
.thumb_set RetailCall_0809a740, 0x0809a741
.global RetailCall_0809a77c
.thumb_set RetailCall_0809a77c, 0x0809a77d
.global RetailCall_0809aa94
.thumb_set RetailCall_0809aa94, 0x0809aa95
.global RetailCall_0809d86c
.thumb_set RetailCall_0809d86c, 0x0809d86d
.global RetailCall_080a215c
.thumb_set RetailCall_080a215c, 0x080a215d
.global RetailCall_080a2210
.thumb_set RetailCall_080a2210, 0x080a2211
.global RetailCall_080a39f8
.thumb_set RetailCall_080a39f8, 0x080a39f9
.global ReadBattleRecordFallbackProperty_080B42D4
.thumb_set ReadBattleRecordFallbackProperty_080B42D4, 0x080b42d5
.global RetailCall_080a8858
.thumb_set RetailCall_080a8858, 0x080a8859
.global RetailCall_080a8968
.thumb_set RetailCall_080a8968, 0x080a8969
.global RetailCall_080c7ea4
.thumb_set RetailCall_080c7ea4, 0x080c7ea5
.global RetailCall_080c8240
.thumb_set RetailCall_080c8240, 0x080c8241
.global RetailCall_080ca7a4
.thumb_set RetailCall_080ca7a4, 0x080ca7a5
.global RetailCall_080ca900
.thumb_set RetailCall_080ca900, 0x080ca901
.global RetailCall_080ca9e8
.thumb_set RetailCall_080ca9e8, 0x080ca9e9
.global RetailCall_080ccd50
.thumb_set RetailCall_080ccd50, 0x080ccd51
.global RetailCall_080cd8cc
.thumb_set RetailCall_080cd8cc, 0x080cd8cd
.global RetailCall_0812e0fc
.thumb_set RetailCall_0812e0fc, 0x0812e0fd
.global RetailCall_0812e6a4
.thumb_set RetailCall_0812e6a4, 0x0812e6a5
.global RetailCall_0812ed98
.thumb_set RetailCall_0812ed98, 0x0812ed99
.global RetailCall_0812ef94
.thumb_set RetailCall_0812ef94, 0x0812ef95
.global RetailCall_0812f0cc
.thumb_set RetailCall_0812f0cc, 0x0812f0cd
.global RetailCall_0812f0d8
.thumb_set RetailCall_0812f0d8, 0x0812f0d9
.global RetailCall_0812f0e4
.thumb_set RetailCall_0812f0e4, 0x0812f0e5
.global RetailCall_0812f154
.thumb_set RetailCall_0812f154, 0x0812f155
.global RetailCall_0812f17c
.thumb_set RetailCall_0812f17c, 0x0812f17d
.global RetailCall_0812f1dc
.thumb_set RetailCall_0812f1dc, 0x0812f1dd
.global RetailCall_0812f2a4
.thumb_set RetailCall_0812f2a4, 0x0812f2a5
.global RetailCall_0812f328
.thumb_set RetailCall_0812f328, 0x0812f329
.global RetailCall_0812f34c
.thumb_set RetailCall_0812f34c, 0x0812f34d
.global RetailCall_0812f358
.thumb_set RetailCall_0812f358, 0x0812f359
.global RetailCall_0812f39c
.thumb_set RetailCall_0812f39c, 0x0812f39d
.global RetailCall_08130200
.thumb_set RetailCall_08130200, 0x08130201
.global RetailCall_081302f8
.thumb_set RetailCall_081302f8, 0x081302f9
.global RetailCall_08130654
.thumb_set RetailCall_08130654, 0x08130655
.global RetailCall_08130688
.thumb_set RetailCall_08130688, 0x08130689
.global RetailCall_08130868
.thumb_set RetailCall_08130868, 0x08130869
.global RetailCall_08130fbc
.thumb_set RetailCall_08130fbc, 0x08130fbd
.global RetailCall_08131024
.thumb_set RetailCall_08131024, 0x08131025
.global RetailCall_08131378
.thumb_set RetailCall_08131378, 0x08131379
.global RetailCall_08131b20
.thumb_set RetailCall_08131b20, 0x08131b21
.global RetailCall_08131c58
.thumb_set RetailCall_08131c58, 0x08131c59
.global RetailCall_081329ec
.thumb_set RetailCall_081329ec, 0x081329ed
.global RetailCall_0813388c
.thumb_set RetailCall_0813388c, 0x0813388d
.global RetailCall_08133988
.thumb_set RetailCall_08133988, 0x08133989
.global RetailCall_08133bb4
.thumb_set RetailCall_08133bb4, 0x08133bb5
.global RetailCall_08133bc4
.thumb_set RetailCall_08133bc4, 0x08133bc5
.global RetailCall_08133bd4
.thumb_set RetailCall_08133bd4, 0x08133bd5
.global RetailCall_08133c00
.thumb_set RetailCall_08133c00, 0x08133c01
.global RetailCall_08134170
.thumb_set RetailCall_08134170, 0x08134171
.global RetailCall_0814224c
.thumb_set RetailCall_0814224c, 0x0814224d
.global RetailCall_08142250
.thumb_set RetailCall_08142250, 0x08142251

@ JOB-CONTROLLER-C07 selected direct-call aliases.
@ Addresses are the frozen entries in the controller scope; bodies remain in their selected modules.
.ifndef OMIT_ApplyUnitJobWithFlag
.global ApplyUnitJobWithFlag
.thumb_set ApplyUnitJobWithFlag, 0x080c93c9
.endif
.ifndef OMIT_BattleDependency_00133BC4
.global BattleDependency_00133BC4
.thumb_set BattleDependency_00133BC4, 0x08133bc5
.endif
.ifndef OMIT_BattleRuntimeDependency_00141520
.global BattleRuntimeDependency_00141520
.thumb_set BattleRuntimeDependency_00141520, 0x08141521
.endif
.ifndef OMIT_CoreDependency29_000CB808
.global CoreDependency29_000CB808
.thumb_set CoreDependency29_000CB808, 0x080cb809
.endif
.ifndef OMIT_CoreDependency29_000CB868
.global CoreDependency29_000CB868
.thumb_set CoreDependency29_000CB868, 0x080cb869
.endif
.ifndef OMIT_CoreDependency29_000CB8D4
.global CoreDependency29_000CB8D4
.thumb_set CoreDependency29_000CB8D4, 0x080cb8d5
.endif
.ifndef OMIT_CoreFrontier_000CB928
.global CoreFrontier_000CB928
.thumb_set CoreFrontier_000CB928, 0x080cb929
.endif
.ifndef OMIT_CoreFrontier_001443FC
.global CoreFrontier_001443FC
.thumb_set CoreFrontier_001443FC, 0x081443fd
.endif
.ifndef OMIT_CoreGlobal36_00088CDC
.global CoreGlobal36_00088CDC
.thumb_set CoreGlobal36_00088CDC, 0x08088cdd
.endif
.ifndef OMIT_CoreGlobal36_000C8A24
.global CoreGlobal36_000C8A24
.thumb_set CoreGlobal36_000C8A24, 0x080c8a25
.endif
.ifndef OMIT_CoreMutationDependency_00011860
.global CoreMutationDependency_00011860
.thumb_set CoreMutationDependency_00011860, 0x08011861
.endif
.ifndef OMIT_CoreRecursive37_00089BA4
.global CoreRecursive37_00089BA4
.thumb_set CoreRecursive37_00089BA4, 0x08089ba5
.endif
.ifndef OMIT_CoreRegion_00035578
.global CoreRegion_00035578
.thumb_set CoreRegion_00035578, 0x08035579
.endif
.ifndef OMIT_CoreRegion_0004C4D4
.global CoreRegion_0004C4D4
.thumb_set CoreRegion_0004C4D4, 0x0804c4d5
.endif
.ifndef OMIT_CoreRegion_0004C7A0
.global CoreRegion_0004C7A0
.thumb_set CoreRegion_0004C7A0, 0x0804c7a1
.endif
.ifndef OMIT_CoreRegion_000717CC
.global CoreRegion_000717CC
.thumb_set CoreRegion_000717CC, 0x080717cd
.endif
.ifndef OMIT_CoreRegion_0008A604
.global CoreRegion_0008A604
.thumb_set CoreRegion_0008A604, 0x0808a605
.endif
.ifndef OMIT_CoreScene34_00075620
.global CoreScene34_00075620
.thumb_set CoreScene34_00075620, 0x08075621
.endif
.ifndef OMIT_CoreScene34_00075E24
.global CoreScene34_00075E24
.thumb_set CoreScene34_00075E24, 0x08075e25
.endif
.ifndef OMIT_CoreScene34_00075FA8
.global CoreScene34_00075FA8
.thumb_set CoreScene34_00075FA8, 0x08075fa9
.endif
.ifndef OMIT_CoreScene34_00076420
.global CoreScene34_00076420
.thumb_set CoreScene34_00076420, 0x08076421
.endif
.ifndef OMIT_CoreScene34_00080DB4
.global CoreScene34_00080DB4
.thumb_set CoreScene34_00080DB4, 0x08080db5
.endif
.ifndef OMIT_CoreScene34_00080E00
.global CoreScene34_00080E00
.thumb_set CoreScene34_00080E00, 0x08080e01
.endif
.ifndef OMIT_CoreScene34_00085678
.global CoreScene34_00085678
.thumb_set CoreScene34_00085678, 0x08085679
.endif
.ifndef OMIT_CoreScene34_00085770
.global CoreScene34_00085770
.thumb_set CoreScene34_00085770, 0x08085771
.endif
.ifndef OMIT_CoreScene34_00085820
.global CoreScene34_00085820
.thumb_set CoreScene34_00085820, 0x08085821
.endif
.ifndef OMIT_CoreScene34_00087B30
.global CoreScene34_00087B30
.thumb_set CoreScene34_00087B30, 0x08087b31
.endif
.ifndef OMIT_CoreScene34_00087C5C
.global CoreScene34_00087C5C
.thumb_set CoreScene34_00087C5C, 0x08087c5d
.endif
.ifndef OMIT_ReadUnitRecordProperty10Or11
.global ReadUnitRecordProperty10Or11
.thumb_set ReadUnitRecordProperty10Or11, 0x080cb7c1
.endif
.ifndef OMIT_SceneTaskDependency_0001174C
.global SceneTaskDependency_0001174C
.thumb_set SceneTaskDependency_0001174C, 0x0801174d
.endif
.ifndef OMIT_SceneTaskDependency_00013380
.global SceneTaskDependency_00013380
.thumb_set SceneTaskDependency_00013380, 0x08013381
.endif
.ifndef OMIT_SceneTaskDependency_00019A8C
.global SceneTaskDependency_00019A8C
.thumb_set SceneTaskDependency_00019A8C, 0x08019a8d
.endif
.ifndef OMIT_SceneTaskDependency_00141540
.global SceneTaskDependency_00141540
.thumb_set SceneTaskDependency_00141540, 0x08141541
.endif
.ifndef OMIT_sub_08013364
.global sub_08013364
.thumb_set sub_08013364, 0x08013365
.endif

/* External callees used by the readable C migration of A5B98. */
.ifndef OMIT_RetailCall_08021054
.global RetailCall_08021054
.thumb_set RetailCall_08021054, 0x08021055
.endif
.ifndef OMIT_RetailCall_08021854
.global RetailCall_08021854
.thumb_set RetailCall_08021854, 0x08021855
.endif
.ifndef OMIT_RetailCall_0802192c
.global RetailCall_0802192c
.thumb_set RetailCall_0802192c, 0x0802192d
.endif
.ifndef OMIT_RetailCall_08021c84
.global RetailCall_08021c84
.thumb_set RetailCall_08021c84, 0x08021c85
.endif
.ifndef OMIT_RetailCall_08021c8c
.global RetailCall_08021c8c
.thumb_set RetailCall_08021c8c, 0x08021c8d
.endif
.ifndef OMIT_RetailCall_0802200c
.global RetailCall_0802200c
.thumb_set RetailCall_0802200c, 0x0802200d
.endif
.ifndef OMIT_RetailCall_08022840
.global RetailCall_08022840
.thumb_set RetailCall_08022840, 0x08022841
.endif
.ifndef OMIT_RetailCall_08022854
.global RetailCall_08022854
.thumb_set RetailCall_08022854, 0x08022855
.endif
.ifndef OMIT_RetailCall_0808f7f8
.global RetailCall_0808f7f8
.thumb_set RetailCall_0808f7f8, 0x0808f7f9
.endif
.ifndef OMIT_RetailCall_08096d7c
.global RetailCall_08096d7c
.thumb_set RetailCall_08096d7c, 0x08096d7d
.endif
.ifndef OMIT_RetailCall_08096f3c
.global RetailCall_08096f3c
.thumb_set RetailCall_08096f3c, 0x08096f3d
.endif
.ifndef OMIT_RetailCall_08096f7c
.global RetailCall_08096f7c
.thumb_set RetailCall_08096f7c, 0x08096f7d
.endif
.ifndef OMIT_RetailCall_0809801c
.global RetailCall_0809801c
.thumb_set RetailCall_0809801c, 0x0809801d
.endif
.ifndef OMIT_RetailCall_0809836c
.global RetailCall_0809836c
.thumb_set RetailCall_0809836c, 0x0809836d
.endif
.ifndef OMIT_RetailCall_08099c30
.global RetailCall_08099c30
.thumb_set RetailCall_08099c30, 0x08099c31
.endif
.ifndef OMIT_RetailCall_08099c34
.global RetailCall_08099c34
.thumb_set RetailCall_08099c34, 0x08099c35
.endif
.ifndef OMIT_RetailCall_08099c64
.global RetailCall_08099c64
.thumb_set RetailCall_08099c64, 0x08099c65
.endif
.ifndef OMIT_RetailCall_0809a09c
.global RetailCall_0809a09c
.thumb_set RetailCall_0809a09c, 0x0809a09d
.endif
.ifndef OMIT_RetailCall_0809a570
.global RetailCall_0809a570
.thumb_set RetailCall_0809a570, 0x0809a571
.endif
.ifndef OMIT_RetailCall_0809a68c
.global RetailCall_0809a68c
.thumb_set RetailCall_0809a68c, 0x0809a68d
.endif
.ifndef OMIT_RetailCall_0809a6c4
.global RetailCall_0809a6c4
.thumb_set RetailCall_0809a6c4, 0x0809a6c5
.endif
.ifndef OMIT_RetailCall_0809a6ec
.global RetailCall_0809a6ec
.thumb_set RetailCall_0809a6ec, 0x0809a6ed
.endif
.ifndef OMIT_RetailCall_0809fdc0
.global RetailCall_0809fdc0
.thumb_set RetailCall_0809fdc0, 0x0809fdc1
.endif
.ifndef OMIT_RetailCall_080a10d4
.global RetailCall_080a10d4
.thumb_set RetailCall_080a10d4, 0x080a10d5
.endif
.ifndef OMIT_RetailCall_080a1600
.global RetailCall_080a1600
.thumb_set RetailCall_080a1600, 0x080a1601
.endif
.ifndef OMIT_RetailCall_080a1a14
.global RetailCall_080a1a14
.thumb_set RetailCall_080a1a14, 0x080a1a15
.endif
.ifndef OMIT_RetailCall_080a1e2c
.global RetailCall_080a1e2c
.thumb_set RetailCall_080a1e2c, 0x080a1e2d
.endif
.ifndef OMIT_RetailCall_080a52d4
.global RetailCall_080a52d4
.thumb_set RetailCall_080a52d4, 0x080a52d5
.endif
.ifndef OMIT_RetailCall_080a54e0
.global RetailCall_080a54e0
.thumb_set RetailCall_080a54e0, 0x080a54e1
.endif
.ifndef OMIT_RetailCall_080a5580
.global RetailCall_080a5580
.thumb_set RetailCall_080a5580, 0x080a5581
.endif
.ifndef OMIT_RetailCall_080a5994
.global RetailCall_080a5994
.thumb_set RetailCall_080a5994, 0x080a5995
.endif
.ifndef OMIT_RetailCall_080a5a7c
.global RetailCall_080a5a7c
.thumb_set RetailCall_080a5a7c, 0x080a5a7d
.endif
.ifndef OMIT_RetailCall_080a9270
.global RetailCall_080a9270
.thumb_set RetailCall_080a9270, 0x080a9271
.endif
.ifndef OMIT_RetailCall_080a9298
.global RetailCall_080a9298
.thumb_set RetailCall_080a9298, 0x080a9299
.endif
.ifndef OMIT_RetailCall_080a929c
.global RetailCall_080a929c
.thumb_set RetailCall_080a929c, 0x080a929d
.endif
.ifndef OMIT_RetailCall_080a9448
.global RetailCall_080a9448
.thumb_set RetailCall_080a9448, 0x080a9449
.endif
.ifndef OMIT_RetailCall_080b336c
.global RetailCall_080b336c
.thumb_set RetailCall_080b336c, 0x080b336d
.endif
.ifndef OMIT_RetailCall_080b351c
.global RetailCall_080b351c
.thumb_set RetailCall_080b351c, 0x080b351d
.endif
.ifndef OMIT_RetailCall_080b4238
.global RetailCall_080b4238
.thumb_set RetailCall_080b4238, 0x080b4239
.endif
.ifndef OMIT_RetailCall_080b4278
.global RetailCall_080b4278
.thumb_set RetailCall_080b4278, 0x080b4279
.endif
.ifndef OMIT_RetailCall_080bd130
.global RetailCall_080bd130
.thumb_set RetailCall_080bd130, 0x080bd131
.endif
.ifndef OMIT_RetailCall_080c92f0
.global RetailCall_080c92f0
.thumb_set RetailCall_080c92f0, 0x080c92f1
.endif
.ifndef OMIT_RetailCall_080cbb40
.global RetailCall_080cbb40
.thumb_set RetailCall_080cbb40, 0x080cbb41
.endif
.ifndef OMIT_RetailCall_080d3508
.global RetailCall_080d3508
.thumb_set RetailCall_080d3508, 0x080d3509
.endif
.ifndef OMIT_RetailCall_080d376c
.global RetailCall_080d376c
.thumb_set RetailCall_080d376c, 0x080d376d
.endif
.ifndef OMIT_RetailCall_080d37ac
.global RetailCall_080d37ac
.thumb_set RetailCall_080d37ac, 0x080d37ad
.endif
.ifndef OMIT_RetailCall_080d37c4
.global RetailCall_080d37c4
.thumb_set RetailCall_080d37c4, 0x080d37c5
.endif
.ifndef OMIT_RetailCall_080d37f8
.global RetailCall_080d37f8
.thumb_set RetailCall_080d37f8, 0x080d37f9
.endif
.ifndef OMIT_RetailCall_080d3864
.global RetailCall_080d3864
.thumb_set RetailCall_080d3864, 0x080d3865
.endif
.ifndef OMIT_RetailCall_080d3878
.global RetailCall_080d3878
.thumb_set RetailCall_080d3878, 0x080d3879
.endif
.ifndef OMIT_RetailCall_080d39b0
.global RetailCall_080d39b0
.thumb_set RetailCall_080d39b0, 0x080d39b1
.endif
.ifndef OMIT_RetailCall_0812eed0
.global RetailCall_0812eed0
.thumb_set RetailCall_0812eed0, 0x0812eed1
.endif
.ifndef OMIT_RetailCall_0812ef08
.global RetailCall_0812ef08
.thumb_set RetailCall_0812ef08, 0x0812ef09
.endif
.ifndef OMIT_RetailCall_0812f194
.global RetailCall_0812f194
.thumb_set RetailCall_0812f194, 0x0812f195
.endif
.ifndef OMIT_RetailCall_08141520
.global RetailCall_08141520
.thumb_set RetailCall_08141520, 0x08141521
.endif
.ifndef OMIT_RetailCall_080a9528
.global RetailCall_080a9528
.thumb_set RetailCall_080a9528, 0x080a9529
.endif
.ifndef OMIT_RetailCall_08024abc
.global RetailCall_08024abc
.thumb_set RetailCall_08024abc, 0x08024abd
.endif
.ifndef OMIT_RetailCall_0809a260
.global RetailCall_0809a260
.thumb_set RetailCall_0809a260, 0x0809a261
.endif
.ifndef OMIT_RetailCall_0809f8ec
.global RetailCall_0809f8ec
.thumb_set RetailCall_0809f8ec, 0x0809f8ed
.endif
.ifndef OMIT_RetailCall_08096f8c
.global RetailCall_08096f8c
.thumb_set RetailCall_08096f8c, 0x08096f8d
.endif
.ifndef OMIT_RetailCall_080a9548
.global RetailCall_080a9548
.thumb_set RetailCall_080a9548, 0x080a9549
.endif
.ifndef OMIT_RetailCall_080cd944
.global RetailCall_080cd944
.thumb_set RetailCall_080cd944, 0x080cd945
.endif
.ifndef OMIT_RetailCall_080cdb54
.global RetailCall_080cdb54
.thumb_set RetailCall_080cdb54, 0x080cdb55
.endif
.ifndef OMIT_RetailCall_080cdb6c
.global RetailCall_080cdb6c
.thumb_set RetailCall_080cdb6c, 0x080cdb6d
.endif
.ifndef OMIT_RetailCall_080bc8c4
.global RetailCall_080bc8c4
.thumb_set RetailCall_080bc8c4, 0x080bc8c5
.endif
.ifndef OMIT_RetailCall_080bc810
.global RetailCall_080bc810
.thumb_set RetailCall_080bc810, 0x080bc811
.endif
.ifndef OMIT_RetailCall_080bc8e8
.global RetailCall_080bc8e8
.thumb_set RetailCall_080bc8e8, 0x080bc8e9
.endif
.ifndef OMIT_RetailCall_080bc878
.global RetailCall_080bc878
.thumb_set RetailCall_080bc878, 0x080bc879
.endif
.ifndef OMIT_RetailCall_08134b88
.global RetailCall_08134b88
.thumb_set RetailCall_08134b88, 0x08134b89
.endif
.ifndef OMIT_RetailCall_080a80c8
.global RetailCall_080a80c8
.thumb_set RetailCall_080a80c8, 0x080a80c9
.endif

/* Pending acquisition transaction: source-backed collection interfaces. */
.ifndef OMIT_GetPrimaryInventoryQuantity
.global GetPrimaryInventoryQuantity
.thumb_set GetPrimaryInventoryQuantity, 0x080388c9
.endif
.ifndef OMIT_InsertCollectionRecordByte
.global InsertCollectionRecordByte
.thumb_set InsertCollectionRecordByte, 0x080384f1
.endif
.ifndef OMIT_InsertCollectionRecordHalfword
.global InsertCollectionRecordHalfword
.thumb_set InsertCollectionRecordHalfword, 0x08038629
.endif
.ifndef OMIT_CompactPendingHalfwordRecordsAndDispatch
.global CompactPendingHalfwordRecordsAndDispatch
.thumb_set CompactPendingHalfwordRecordsAndDispatch, 0x080cb27d
.endif

/* Acquisition dialog transaction interfaces. */
.ifndef OMIT_IT01_WaitForVBlank
.global IT01_WaitForVBlank
.thumb_set IT01_WaitForVBlank, 0x08003399
.endif
.ifndef OMIT_IT01_PollText
.global IT01_PollText
.thumb_set IT01_PollText, 0x08011861
.endif
.ifndef OMIT_IT01_Message
.global IT01_Message
.thumb_set IT01_Message, 0x08011b31
.endif
.ifndef OMIT_IT01_ServiceText
.global IT01_ServiceText
.thumb_set IT01_ServiceText, 0x08011c61
.endif
.ifndef OMIT_IT01_ClearText
.global IT01_ClearText
.thumb_set IT01_ClearText, 0x08013365
.endif
.ifndef OMIT_IT01_RenderText
.global IT01_RenderText
.thumb_set IT01_RenderText, 0x08015111
.endif
.ifndef OMIT_IT01_SetInterfaceByte
.global IT01_SetInterfaceByte
.thumb_set IT01_SetInterfaceByte, 0x08031709
.endif
.ifndef OMIT_IT01_ResetInterfaceByte
.global IT01_ResetInterfaceByte
.thumb_set IT01_ResetInterfaceByte, 0x08031715
.endif
.ifndef OMIT_IT01_CreateText
.global IT01_CreateText
.thumb_set IT01_CreateText, 0x080354ad
.endif
.ifndef OMIT_IT01_EnableInterface
.global IT01_EnableInterface
.thumb_set IT01_EnableInterface, 0x080358b1
.endif
.ifndef OMIT_IT01_SetSlotMode
.global IT01_SetSlotMode
.thumb_set IT01_SetSlotMode, 0x080359e5
.endif
.ifndef OMIT_IT01_ClearPendingRows
.global IT01_ClearPendingRows
.thumb_set IT01_ClearPendingRows, 0x08038821
.endif
.ifndef OMIT_IT01_QueuePending
.global IT01_QueuePending
.thumb_set IT01_QueuePending, 0x08038859
.endif
.ifndef OMIT_IT01_CommitPending
.global IT01_CommitPending
.thumb_set IT01_CommitPending, 0x0803890d
.endif
.ifndef OMIT_IT01_PrepareDisplay
.global IT01_PrepareDisplay
.thumb_set IT01_PrepareDisplay, 0x08039d1d
.endif
.ifndef OMIT_IT01_DisplayMappedId
.global IT01_DisplayMappedId
.thumb_set IT01_DisplayMappedId, 0x08039df5
.endif
.ifndef OMIT_IT01_ChangePanel
.global IT01_ChangePanel
.thumb_set IT01_ChangePanel, 0x0808a605
.endif
.ifndef OMIT_IT01_PlaySound
.global IT01_PlaySound
.thumb_set IT01_PlaySound, 0x08141541
.endif

/* Acquisition selection transaction interfaces. */
.ifndef OMIT_IT02_BuildRecordList
.global IT02_BuildRecordList
.thumb_set IT02_BuildRecordList, 0x080d1219
.endif
.ifndef OMIT_IT02_TestRecordList
.global IT02_TestRecordList
.thumb_set IT02_TestRecordList, 0x0803d035
.endif
.ifndef OMIT_IT02_SetNodeInterfaceBit
.global IT02_SetNodeInterfaceBit
.thumb_set IT02_SetNodeInterfaceBit, 0x08035845
.endif
.ifndef OMIT_IT02_SetupDisplay
.global IT02_SetupDisplay
.thumb_set IT02_SetupDisplay, 0x0808a269
.endif
.ifndef OMIT_IT02_CpuSet
.global IT02_CpuSet
.thumb_set IT02_CpuSet, 0x0814186d
.endif
.ifndef OMIT_IT02_GetDisplayRegion
.global IT02_GetDisplayRegion
.thumb_set IT02_GetDisplayRegion, 0x0808b8e5
.endif
.ifndef OMIT_IT02_SetDisplayTiles
.global IT02_SetDisplayTiles
.thumb_set IT02_SetDisplayTiles, 0x0808b7c1
.endif
.ifndef OMIT_IT02_SetDisplayFill
.global IT02_SetDisplayFill
.thumb_set IT02_SetDisplayFill, 0x0808b859
.endif
.ifndef OMIT_IT02_ConfigureRecordList
.global IT02_ConfigureRecordList
.thumb_set IT02_ConfigureRecordList, 0x08037c85
.endif
.ifndef OMIT_IT02_SetRegionPalette
.global IT02_SetRegionPalette
.thumb_set IT02_SetRegionPalette, 0x0808b951
.endif
.ifndef OMIT_IT02_DrawTileFrame
.global IT02_DrawTileFrame
.thumb_set IT02_DrawTileFrame, 0x08016345
.endif
.ifndef OMIT_IT02_DrawMappedFrame
.global IT02_DrawMappedFrame
.thumb_set IT02_DrawMappedFrame, 0x08016561
.endif
.ifndef OMIT_IT02_ResolveCollectionText
.global IT02_ResolveCollectionText
.thumb_set IT02_ResolveCollectionText, 0x08018525
.endif
.ifndef OMIT_IT02_CopyTextToRegion
.global IT02_CopyTextToRegion
.thumb_set IT02_CopyTextToRegion, 0x08035679
.endif
.ifndef OMIT_IT02_RefreshRecordSelection
.global IT02_RefreshRecordSelection
.thumb_set IT02_RefreshRecordSelection, 0x08042149
.endif
.ifndef OMIT_IT02_ShowRecordText
.global IT02_ShowRecordText
.thumb_set IT02_ShowRecordText, 0x080372fd
.endif
.ifndef OMIT_IT02_ProcessSelectionInput
.global IT02_ProcessSelectionInput
.thumb_set IT02_ProcessSelectionInput, 0x080421a5
.endif
.ifndef OMIT_IT02_SetDisplayObjectMode
.global IT02_SetDisplayObjectMode
.thumb_set IT02_SetDisplayObjectMode, 0x0804c7a1
.endif
.ifndef OMIT_IT02_SelectionSound
.global IT02_SelectionSound
.thumb_set IT02_SelectionSound, 0x081416dd
.endif
.ifndef OMIT_IT02_ApplyRecordType
.global IT02_ApplyRecordType
.thumb_set IT02_ApplyRecordType, 0x0800a041
.endif

/* Inventory removal/staging transaction interfaces. */
.ifndef OMIT_IT03_EmitInterfaceEvent
.global IT03_EmitInterfaceEvent
.thumb_set IT03_EmitInterfaceEvent, 0x08031709
.endif
.ifndef OMIT_IT03_SetAudioParameter
.global IT03_SetAudioParameter
.thumb_set IT03_SetAudioParameter, 0x08141571
.endif
.ifndef OMIT_IT03_SetInterfaceParameter
.global IT03_SetInterfaceParameter
.thumb_set IT03_SetInterfaceParameter, 0x080354ad
.endif
.ifndef OMIT_IT03_RefreshCurrency
.global IT03_RefreshCurrency
.thumb_set IT03_RefreshCurrency, 0x08035c49
.endif
.ifndef OMIT_IT03_ReadCategoryOneCount
.global IT03_ReadCategoryOneCount
.thumb_set IT03_ReadCategoryOneCount, 0x080385e5
.endif
.ifndef OMIT_IT03_ReadCategoryTwoCount
.global IT03_ReadCategoryTwoCount
.thumb_set IT03_ReadCategoryTwoCount, 0x08038705
.endif
.ifndef OMIT_IT03_RemoveCategoryOne
.global IT03_RemoveCategoryOne
.thumb_set IT03_RemoveCategoryOne, 0x080385a9
.endif
.ifndef OMIT_IT03_RemoveCategoryTwo
.global IT03_RemoveCategoryTwo
.thumb_set IT03_RemoveCategoryTwo, 0x080386c9
.endif
.ifndef OMIT_IT03_ReadItemCount
.global IT03_ReadItemCount
.thumb_set IT03_ReadItemCount, 0x080cb2b5
.endif
.ifndef OMIT_IT03_RemoveItem
.global IT03_RemoveItem
.thumb_set IT03_RemoveItem, 0x080ca9e9
.endif
.ifndef OMIT_IT03_SetMessageMode
.global IT03_SetMessageMode
.thumb_set IT03_SetMessageMode, 0x0803e079
.endif
.ifndef OMIT_IT03_SetMessageRecord
.global IT03_SetMessageRecord
.thumb_set IT03_SetMessageRecord, 0x0803e1c1
.endif
.ifndef OMIT_IT03_SetMessageAmount
.global IT03_SetMessageAmount
.thumb_set IT03_SetMessageAmount, 0x0803e2e1
.endif
.ifndef OMIT_IT03_SignedRemainder
.global IT03_SignedRemainder
.thumb_set IT03_SignedRemainder, 0x08142951
.endif

/* Inventory progression controller interfaces. */
.ifndef OMIT_IP03_StopSound
.global IP03_StopSound
.thumb_set IP03_StopSound, 0x08141521
.endif
.ifndef OMIT_IP03_ResetInterface
.global IP03_ResetInterface
.thumb_set IP03_ResetInterface, 0x08031715
.endif
.ifndef OMIT_IP03_PrepareSelectionDisplay
.global IP03_PrepareSelectionDisplay
.thumb_set IP03_PrepareSelectionDisplay, 0x080454a9
.endif
.ifndef OMIT_IP03_AdvanceEmptyRecord
.global IP03_AdvanceEmptyRecord
.thumb_set IP03_AdvanceEmptyRecord, 0x080d0f75
.endif
.ifndef OMIT_IP03_ResolveRecord
.global IP03_ResolveRecord
.thumb_set IP03_ResolveRecord, 0x080d2de1
.endif
.ifndef OMIT_IP03_ReadRecordProperty
.global IP03_ReadRecordProperty
.thumb_set IP03_ReadRecordProperty, 0x08045485
.endif
.ifndef OMIT_IP03_BuildCandidateList
.global IP03_BuildCandidateList
.thumb_set IP03_BuildCandidateList, 0x08045cf9
.endif
.ifndef OMIT_IP03_BuildAlternateList
.global IP03_BuildAlternateList
.thumb_set IP03_BuildAlternateList, 0x08045d91
.endif
.ifndef OMIT_IP03_RandomWord
.global IP03_RandomWord
.thumb_set IP03_RandomWord, 0x08002805
.endif
.ifndef OMIT_IP03_DrawIndicator
.global IP03_DrawIndicator
.thumb_set IP03_DrawIndicator, 0x08001f35
.endif
.ifndef OMIT_IP03_TestUnitCondition
.global IP03_TestUnitCondition
.thumb_set IP03_TestUnitCondition, 0x080c8195
.endif
.ifndef OMIT_IP03_SignedDivide
.global IP03_SignedDivide
.thumb_set IP03_SignedDivide, 0x081426b9
.endif
.ifndef OMIT_IP03_ClearBuffer
.global IP03_ClearBuffer
.thumb_set IP03_ClearBuffer, 0x08144461
.endif
.ifndef OMIT_IP03_ReadStagePrimary
.global IP03_ReadStagePrimary
.thumb_set IP03_ReadStagePrimary, 0x080d2115
.endif
.ifndef OMIT_IP03_ReadStageSecondary
.global IP03_ReadStageSecondary
.thumb_set IP03_ReadStageSecondary, 0x080d21a9
.endif
.ifndef OMIT_IP03_ReadStageAmount
.global IP03_ReadStageAmount
.thumb_set IP03_ReadStageAmount, 0x080d2ee9
.endif
.ifndef OMIT_IP03_ReadStageCount
.global IP03_ReadStageCount
.thumb_set IP03_ReadStageCount, 0x080d2f09
.endif
.ifndef OMIT_IP03_AdjustSelectionAmounts
.global IP03_AdjustSelectionAmounts
.thumb_set IP03_AdjustSelectionAmounts, 0x080469f9
.endif
.ifndef OMIT_IP03_RefreshSelectionRecord
.global IP03_RefreshSelectionRecord
.thumb_set IP03_RefreshSelectionRecord, 0x08045669
.endif
.ifndef OMIT_IP03_ApplyRecordOutcome
.global IP03_ApplyRecordOutcome
.thumb_set IP03_ApplyRecordOutcome, 0x08045df5
.endif
.ifndef OMIT_IP03_ShowProgressionRecord
.global IP03_ShowProgressionRecord
.thumb_set IP03_ShowProgressionRecord, 0x080461d5
.endif
.ifndef OMIT_IP03_TestCollectionFlag
.global IP03_TestCollectionFlag
.thumb_set IP03_TestCollectionFlag, 0x08036331
.endif
.ifndef OMIT_IP03_ClearCollectionFlag
.global IP03_ClearCollectionFlag
.thumb_set IP03_ClearCollectionFlag, 0x080362dd
.endif
.ifndef OMIT_IP03_ConfigureProgressionPanel
.global IP03_ConfigureProgressionPanel
.thumb_set IP03_ConfigureProgressionPanel, 0x0804a15d
.endif
.ifndef OMIT_IP03_RefreshProgressionPanel
.global IP03_RefreshProgressionPanel
.thumb_set IP03_RefreshProgressionPanel, 0x0804a2e5
.endif
.ifndef OMIT_IP03_SetProgressionPanelRecord
.global IP03_SetProgressionPanelRecord
.thumb_set IP03_SetProgressionPanelRecord, 0x0804a3cd
.endif
.ifndef OMIT_IP03_FindRecordPosition
.global IP03_FindRecordPosition
.thumb_set IP03_FindRecordPosition, 0x08049ed1
.endif
.ifndef OMIT_IP03_UnsignedRemainder
.global IP03_UnsignedRemainder
.thumb_set IP03_UnsignedRemainder, 0x08142b29
.endif
.ifndef OMIT_IP03_ShowProgressionIncrease
.global IP03_ShowProgressionIncrease
.thumb_set IP03_ShowProgressionIncrease, 0x080457b1
.endif
.ifndef OMIT_IP03_ActivateProgressionRules
.global IP03_ActivateProgressionRules
.thumb_set IP03_ActivateProgressionRules, 0x080ce93d
.endif
.ifndef OMIT_IP03_RefreshProgressionRules
.global IP03_RefreshProgressionRules
.thumb_set IP03_RefreshProgressionRules, 0x080cbbc5
.endif
.ifndef OMIT_IP03_ApplyProgressionThreshold
.global IP03_ApplyProgressionThreshold
.thumb_set IP03_ApplyProgressionThreshold, 0x08046855
.endif
.ifndef OMIT_IP03_ResolveThresholdReward
.global IP03_ResolveThresholdReward
.thumb_set IP03_ResolveThresholdReward, 0x08046911
.endif
.ifndef OMIT_IP03_ShowThresholdReward
.global IP03_ShowThresholdReward
.thumb_set IP03_ShowThresholdReward, 0x080458a5
.endif
.ifndef OMIT_IP03_ShowThresholdIncrease
.global IP03_ShowThresholdIncrease
.thumb_set IP03_ShowThresholdIncrease, 0x08045b05
.endif
.ifndef OMIT_IP03_CountUnitSlots
.global IP03_CountUnitSlots
.thumb_set IP03_CountUnitSlots, 0x0803600d
.endif
.ifndef OMIT_IP03_InitializeResultText
.global IP03_InitializeResultText
.thumb_set IP03_InitializeResultText, 0x0801174d
.endif
.ifndef OMIT_IP03_ResolveUnitAbilityRow
.global IP03_ResolveUnitAbilityRow
.thumb_set IP03_ResolveUnitAbilityRow, 0x080cd481
.endif
.ifndef OMIT_IP03_RefreshUnitAbility
.global IP03_RefreshUnitAbility
.thumb_set IP03_RefreshUnitAbility, 0x080cd621
.endif
.ifndef OMIT_IP03_ShowLearnedUnit
.global IP03_ShowLearnedUnit
.thumb_set IP03_ShowLearnedUnit, 0x08045bfd
.endif
.ifndef OMIT_IP03_GetUnitName
.global IP03_GetUnitName
.thumb_set IP03_GetUnitName, 0x080c7ea5
.endif
.ifndef OMIT_IP03_FormatTwoStrings
.global IP03_FormatTwoStrings
.thumb_set IP03_FormatTwoStrings, 0x08038cf1
.endif
.ifndef OMIT_IP03_FormatThreeStrings
.global IP03_FormatThreeStrings
.thumb_set IP03_FormatThreeStrings, 0x08038d11
.endif
.ifndef OMIT_IP03_FormatFourStrings
.global IP03_FormatFourStrings
.thumb_set IP03_FormatFourStrings, 0x08038d41
.endif
.ifndef OMIT_IP03_TestMissionProgressRoute
.global IP03_TestMissionProgressRoute
.thumb_set IP03_TestMissionProgressRoute, 0x080d2fb9
.endif
.ifndef OMIT_IP03_ApplyMissionProgress
.global IP03_ApplyMissionProgress
.thumb_set IP03_ApplyMissionProgress, 0x080cfa49
.endif
.ifndef OMIT_IP03_ApplyMissionFailure
.global IP03_ApplyMissionFailure
.thumb_set IP03_ApplyMissionFailure, 0x080d2fd9
.endif
.ifndef OMIT_IP03_ApplyLiveRecord
.global IP03_ApplyLiveRecord
.thumb_set IP03_ApplyLiveRecord, 0x080d1e71
.endif
.ifndef OMIT_IP03_ApplyAuxiliaryRecord
.global IP03_ApplyAuxiliaryRecord
.thumb_set IP03_ApplyAuxiliaryRecord, 0x080d2eb5
.endif
.ifndef OMIT_IP03_AdvanceRecordGroup
.global IP03_AdvanceRecordGroup
.thumb_set IP03_AdvanceRecordGroup, 0x08036035
.endif
.ifndef OMIT_IP03_ReadProgressionField
.global IP03_ReadProgressionField
.thumb_set IP03_ReadProgressionField, 0x080c95a9
.endif
.ifndef OMIT_IP03_SelectMissionReward
.global IP03_SelectMissionReward
.thumb_set IP03_SelectMissionReward, 0x080d241d
.endif

.ifndef OMIT_RetailCall_080a8a68
.global RetailCall_080a8a68
.thumb_set RetailCall_080a8a68, 0x080a8a69
.endif

.ifndef OMIT_RetailCall_080a8a64
.global RetailCall_080a8a64
.thumb_set RetailCall_080a8a64, 0x080a8a65
.endif

.ifndef OMIT_RetailCall_080a8958
.global RetailCall_080a8958
.thumb_set RetailCall_080a8958, 0x080a8959
.endif

.ifndef OMIT_RetailCall_080a8940
.global RetailCall_080a8940
.thumb_set RetailCall_080a8940, 0x080a8941
.endif

.ifndef OMIT_RetailCall_080a9588
.global RetailCall_080a9588
.thumb_set RetailCall_080a9588, 0x080a9589
.endif

.ifndef OMIT_RetailCall_0802d72c
.global RetailCall_0802d72c
.thumb_set RetailCall_0802d72c, 0x0802d72d
.endif

.ifndef OMIT_RetailCall_0802d704
.global RetailCall_0802d704
.thumb_set RetailCall_0802d704, 0x0802d705
.endif

.ifndef OMIT_RetailCall_08099544
.global RetailCall_08099544
.thumb_set RetailCall_08099544, 0x08099545
.endif

.ifndef OMIT_RetailCall_080c71b4
.global RetailCall_080c71b4
.thumb_set RetailCall_080c71b4, 0x080c71b5
.endif

.ifndef OMIT_RetailCall_0800a5c8
.global RetailCall_0800a5c8
.thumb_set RetailCall_0800a5c8, 0x0800a5c9
.endif

.ifndef OMIT_RetailCall_08009fd0
.global RetailCall_08009fd0
.thumb_set RetailCall_08009fd0, 0x08009fd1
.endif

.ifndef OMIT_RetailCall_08009fbc
.global RetailCall_08009fbc
.thumb_set RetailCall_08009fbc, 0x08009fbd
.endif

.ifndef OMIT_RetailCall_0802b880
.global RetailCall_0802b880
.thumb_set RetailCall_0802b880, 0x0802b881
.endif

.ifndef OMIT_RetailCall_0809f850
.global RetailCall_0809f850
.thumb_set RetailCall_0809f850, 0x0809f851
.endif

.ifndef OMIT_RetailCall_080c95c0
.global RetailCall_080c95c0
.thumb_set RetailCall_080c95c0, 0x080c95c1
.endif

.ifndef OMIT_RetailCall_080255fc
.global RetailCall_080255fc
.thumb_set RetailCall_080255fc, 0x080255fd
.endif

.ifndef OMIT_RetailCall_0800a024
.global RetailCall_0800a024
.thumb_set RetailCall_0800a024, 0x0800a025
.endif

.ifndef OMIT_RetailCall_0808f8e8
.global RetailCall_0808f8e8
.thumb_set RetailCall_0808f8e8, 0x0808f8e9
.endif

.ifndef OMIT_RetailCall_0808fa98
.global RetailCall_0808fa98
.thumb_set RetailCall_0808fa98, 0x0808fa99
.endif

.ifndef OMIT_RetailCall_0808f848
.global RetailCall_0808f848
.thumb_set RetailCall_0808f848, 0x0808f849
.endif

.ifndef OMIT_RetailCall_080b8100
.global RetailCall_080b8100
.thumb_set RetailCall_080b8100, 0x080b8101
.endif

.ifndef OMIT_RetailCall_080b8414
.global RetailCall_080b8414
.thumb_set RetailCall_080b8414, 0x080b8415
.endif

.ifndef OMIT_RetailCall_080ba6d0
.global RetailCall_080ba6d0
.thumb_set RetailCall_080ba6d0, 0x080ba6d1
.endif

.ifndef OMIT_RetailCall_0800a018
.global RetailCall_0800a018
.thumb_set RetailCall_0800a018, 0x0800a019
.endif

.ifndef OMIT_RetailCall_080bc780
.global RetailCall_080bc780
.thumb_set RetailCall_080bc780, 0x080bc781
.endif

.ifndef OMIT_RetailCall_080bc798
.global RetailCall_080bc798
.thumb_set RetailCall_080bc798, 0x080bc799
.endif

.ifndef OMIT_RetailCall_08099cdc
.global RetailCall_08099cdc
.thumb_set RetailCall_08099cdc, 0x08099cdd
.endif

.ifndef OMIT_RetailCall_0809a9a8
.global RetailCall_0809a9a8
.thumb_set RetailCall_0809a9a8, 0x0809a9a9
.endif

.ifndef OMIT_RetailCall_0809a9cc
.global RetailCall_0809a9cc
.thumb_set RetailCall_0809a9cc, 0x0809a9cd
.endif

.ifndef OMIT_RetailCall_0809aa38
.global RetailCall_0809aa38
.thumb_set RetailCall_0809aa38, 0x0809aa39
.endif

.ifndef OMIT_RetailCall_080924f4
.global RetailCall_080924f4
.thumb_set RetailCall_080924f4, 0x080924f5
.endif

.ifndef OMIT_RetailCall_0809a5c0
.global RetailCall_0809a5c0
.thumb_set RetailCall_0809a5c0, 0x0809a5c1
.endif

.ifndef OMIT_RetailCall_08099a70
.global RetailCall_08099a70
.thumb_set RetailCall_08099a70, 0x08099a71
.endif

.ifndef OMIT_RetailCall_08135624
.global RetailCall_08135624
.thumb_set RetailCall_08135624, 0x08135625
.endif

.ifndef OMIT_RetailCall_08134b38
.global RetailCall_08134b38
.thumb_set RetailCall_08134b38, 0x08134b39
.endif

.ifndef OMIT_RetailCall_080bc7d4
.global RetailCall_080bc7d4
.thumb_set RetailCall_080bc7d4, 0x080bc7d5
.endif

.ifndef OMIT_RetailCall_080bc7fc
.global RetailCall_080bc7fc
.thumb_set RetailCall_080bc7fc, 0x080bc7fd
.endif

.ifndef OMIT_RetailCall_080bc900
.global RetailCall_080bc900
.thumb_set RetailCall_080bc900, 0x080bc901
.endif

.ifndef OMIT_RetailCall_080925a4
.global RetailCall_080925a4
.thumb_set RetailCall_080925a4, 0x080925a5
.endif

.ifndef OMIT_RetailCall_080922cc
.global RetailCall_080922cc
.thumb_set RetailCall_080922cc, 0x080922cd
.endif

.ifndef OMIT_RetailCall_08092390
.global RetailCall_08092390
.thumb_set RetailCall_08092390, 0x08092391
.endif

.ifndef RetailCall_080bc950
.global RetailCall_080bc950
.thumb_set RetailCall_080bc950, 0x080bc951
.endif

.ifndef RetailCall_080bc984
.global RetailCall_080bc984
.thumb_set RetailCall_080bc984, 0x080bc985
.endif

.ifndef RetailCall_080bc9cc
.global RetailCall_080bc9cc
.thumb_set RetailCall_080bc9cc, 0x080bc9cd
.endif

.ifndef RetailCall_080bc9e4
.global RetailCall_080bc9e4
.thumb_set RetailCall_080bc9e4, 0x080bc9e5
.endif

.ifndef RetailCall_080bc9b8
.global RetailCall_080bc9b8
.thumb_set RetailCall_080bc9b8, 0x080bc9b9
.endif

.ifndef RetailCall_080bc994
.global RetailCall_080bc994
.thumb_set RetailCall_080bc994, 0x080bc995
.endif

.ifndef RetailCall_080c144c
.global RetailCall_080c144c
.thumb_set RetailCall_080c144c, 0x080c144d
.endif

.ifndef RetailCall_080c1438
.global RetailCall_080c1438
.thumb_set RetailCall_080c1438, 0x080c1439
.endif

.ifndef RetailCall_080c1460
.global RetailCall_080c1460
.thumb_set RetailCall_080c1460, 0x080c1461
.endif

.ifndef RetailCall_080c1b2c
.global RetailCall_080c1b2c
.thumb_set RetailCall_080c1b2c, 0x080c1b2d
.endif

.ifndef RetailCall_080c15c0
.global RetailCall_080c15c0
.thumb_set RetailCall_080c15c0, 0x080c15c1
.endif

.ifndef RetailCall_080c17c8
.global RetailCall_080c17c8
.thumb_set RetailCall_080c17c8, 0x080c17c9
.endif

.ifndef RetailCall_080c17b8
.global RetailCall_080c17b8
.thumb_set RetailCall_080c17b8, 0x080c17b9
.endif

.ifndef RetailCall_08099e68
.global RetailCall_08099e68
.thumb_set RetailCall_08099e68, 0x08099e69
.endif

.ifndef RetailCall_0809a624
.global RetailCall_0809a624
.thumb_set RetailCall_0809a624, 0x0809a625
.endif

.ifndef RetailCall_08098a88
.global RetailCall_08098a88
.thumb_set RetailCall_08098a88, 0x08098a89
.endif

.ifndef RetailCall_0802b70c
.global RetailCall_0802b70c
.thumb_set RetailCall_0802b70c, 0x0802b70d
.endif

.ifndef RetailCall_080294e4
.global RetailCall_080294e4
.thumb_set RetailCall_080294e4, 0x080294e5
.endif

.ifndef RetailCall_0802542c
.global RetailCall_0802542c
.thumb_set RetailCall_0802542c, 0x0802542d
.endif

.ifndef RetailCall_08025448
.global RetailCall_08025448
.thumb_set RetailCall_08025448, 0x08025449
.endif

.ifndef RetailCall_08005028
.global RetailCall_08005028
.thumb_set RetailCall_08005028, 0x08005029
.endif

.ifndef RetailCall_080c75f4
.global RetailCall_080c75f4
.thumb_set RetailCall_080c75f4, 0x080c75f5
.endif

.ifndef RetailCall_080c7650
.global RetailCall_080c7650
.thumb_set RetailCall_080c7650, 0x080c7651
.endif

.ifndef RetailCall_080254a0
.global RetailCall_080254a0
.thumb_set RetailCall_080254a0, 0x080254a1
.endif

.ifndef RetailCall_080cd584
.global RetailCall_080cd584
.thumb_set RetailCall_080cd584, 0x080cd585
.endif

.ifndef RetailCall_080bc914
.global RetailCall_080bc914
.thumb_set RetailCall_080bc914, 0x080bc915
.endif

.ifndef RetailCall_080bc934
.global RetailCall_080bc934
.thumb_set RetailCall_080bc934, 0x080bc935
.endif

.ifndef RetailCall_080bc944
.global RetailCall_080bc944
.thumb_set RetailCall_080bc944, 0x080bc945
.endif

.ifndef RetailCall_08099ea0
.global RetailCall_08099ea0
.thumb_set RetailCall_08099ea0, 0x08099ea1
.endif

.ifndef RetailCall_08099f00
.global RetailCall_08099f00
.thumb_set RetailCall_08099f00, 0x08099f01
.endif

.ifndef RetailCall_0809a5e0
.global RetailCall_0809a5e0
.thumb_set RetailCall_0809a5e0, 0x0809a5e1
.endif

.ifndef RetailCall_08149368
.global RetailCall_08149368
.thumb_set RetailCall_08149368, 0x08149369
.endif

.ifndef RetailCall_0801d938
.global RetailCall_0801d938
.thumb_set RetailCall_0801d938, 0x0801d939
.endif

.ifndef RetailCall_080231ac
.global RetailCall_080231ac
.thumb_set RetailCall_080231ac, 0x080231ad
.endif

.ifndef RetailCall_080bca24
.global RetailCall_080bca24
.thumb_set RetailCall_080bca24, 0x080bca25
.endif

.ifndef RetailCall_080bca40
.global RetailCall_080bca40
.thumb_set RetailCall_080bca40, 0x080bca41
.endif

.ifndef RetailCall_080bca54
.global RetailCall_080bca54
.thumb_set RetailCall_080bca54, 0x080bca55
.endif

.ifndef RetailCall_080c7668
.global RetailCall_080c7668
.thumb_set RetailCall_080c7668, 0x080c7669
.endif

.ifndef RetailCall_080c76c4
.global RetailCall_080c76c4
.thumb_set RetailCall_080c76c4, 0x080c76c5
.endif

.ifndef RetailCall_080c7214
.global RetailCall_080c7214
.thumb_set RetailCall_080c7214, 0x080c7215
.endif

.ifndef RetailCall_080cda7c
.global RetailCall_080cda7c
.thumb_set RetailCall_080cda7c, 0x080cda7d
.endif

.ifndef RetailCall_08025584
.global RetailCall_08025584
.thumb_set RetailCall_08025584, 0x08025585
.endif

.ifndef RetailCall_080294d8
.global RetailCall_080294d8
.thumb_set RetailCall_080294d8, 0x080294d9
.endif

.ifndef RetailCall_08029544
.global RetailCall_08029544
.thumb_set RetailCall_08029544, 0x08029545
.endif

.ifndef RetailCall_08011860
.global RetailCall_08011860
.thumb_set RetailCall_08011860, 0x08011861
.endif

.ifndef RetailCall_08013380
.global RetailCall_08013380
.thumb_set RetailCall_08013380, 0x08013381
.endif

.ifndef RetailCall_080c1780
.global RetailCall_080c1780
.thumb_set RetailCall_080c1780, 0x080c1781
.endif

.ifndef RetailCall_080c1700
.global RetailCall_080c1700
.thumb_set RetailCall_080c1700, 0x080c1701
.endif

.ifndef RetailCall_0802966c
.global RetailCall_0802966c
.thumb_set RetailCall_0802966c, 0x0802966d
.endif

.ifndef RetailCall_08009afc
.global RetailCall_08009afc
.thumb_set RetailCall_08009afc, 0x08009afd
.endif

.ifndef RetailCall_080c1920
.global RetailCall_080c1920
.thumb_set RetailCall_080c1920, 0x080c1921
.endif

.ifndef RetailCall_0809a204
.global RetailCall_0809a204
.thumb_set RetailCall_0809a204, 0x0809a205
.endif

.ifndef RetailCall_080c19dc
.global RetailCall_080c19dc
.thumb_set RetailCall_080c19dc, 0x080c19dd
.endif

.ifndef RetailCall_080c15dc
.global RetailCall_080c15dc
.thumb_set RetailCall_080c15dc, 0x080c15dd
.endif

.ifndef RetailCall_080c1a04
.global RetailCall_080c1a04
.thumb_set RetailCall_080c1a04, 0x080c1a05
.endif

.ifndef RetailCall_080c1654
.global RetailCall_080c1654
.thumb_set RetailCall_080c1654, 0x080c1655
.endif

.ifndef RetailCall_080c1748
.global RetailCall_080c1748
.thumb_set RetailCall_080c1748, 0x080c1749
.endif

.ifndef RetailCall_080c1484
.global RetailCall_080c1484
.thumb_set RetailCall_080c1484, 0x080c1485
.endif

.ifndef RetailCall_080c1500
.global RetailCall_080c1500
.thumb_set RetailCall_080c1500, 0x080c1501
.endif

.ifndef RetailCall_080c14b0
.global RetailCall_080c14b0
.thumb_set RetailCall_080c14b0, 0x080c14b1
.endif

.ifndef RetailCall_080ca3ec
.global RetailCall_080ca3ec
.thumb_set RetailCall_080ca3ec, 0x080ca3ed
.endif

.ifndef RetailCall_0809a604
.global RetailCall_0809a604
.thumb_set RetailCall_0809a604, 0x0809a605
.endif

.ifndef RetailCall_0809d8f0
.global RetailCall_0809d8f0
.thumb_set RetailCall_0809d8f0, 0x0809d8f1
.endif

.ifndef RetailCall_080c1514
.global RetailCall_080c1514
.thumb_set RetailCall_080c1514, 0x080c1515
.endif

.ifndef RetailCall_080c1528
.global RetailCall_080c1528
.thumb_set RetailCall_080c1528, 0x080c1529
.endif

.ifndef RetailCall_080c1a78
.global RetailCall_080c1a78
.thumb_set RetailCall_080c1a78, 0x080c1a79
.endif

.ifndef RetailCall_080c19f0
.global RetailCall_080c19f0
.thumb_set RetailCall_080c19f0, 0x080c19f1
.endif

.ifndef RetailCall_080c14d8
.global RetailCall_080c14d8
.thumb_set RetailCall_080c14d8, 0x080c14d9
.endif

.ifndef RetailCall_080c153c
.global RetailCall_080c153c
.thumb_set RetailCall_080c153c, 0x080c153d
.endif

.ifndef RetailCall_0812f1ac
.global RetailCall_0812f1ac
.thumb_set RetailCall_0812f1ac, 0x0812f1ad
.endif

.ifndef RetailCall_080c1b18
.global RetailCall_080c1b18
.thumb_set RetailCall_080c1b18, 0x080c1b19
.endif

.ifndef RetailCall_08142ab0
.global RetailCall_08142ab0
.thumb_set RetailCall_08142ab0, 0x08142ab1
.endif

.ifndef RetailCall_08025688
.global RetailCall_08025688
.thumb_set RetailCall_08025688, 0x08025689
.endif

.ifndef RetailCall_08029514
.global RetailCall_08029514
.thumb_set RetailCall_08029514, 0x08029515
.endif

.ifndef RetailCall_0809f9d8
.global RetailCall_0809f9d8
.thumb_set RetailCall_0809f9d8, 0x0809f9d9
.endif

.ifndef RetailCall_08098130
.global RetailCall_08098130
.thumb_set RetailCall_08098130, 0x08098131
.endif

.ifndef RetailCall_0809f9a8
.global RetailCall_0809f9a8
.thumb_set RetailCall_0809f9a8, 0x0809f9a9
.endif

.ifndef RetailCall_0809f9c0
.global RetailCall_0809f9c0
.thumb_set RetailCall_0809f9c0, 0x0809f9c1
.endif

.ifndef RetailCall_0809f9d0
.global RetailCall_0809f9d0
.thumb_set RetailCall_0809f9d0, 0x0809f9d1
.endif

.ifndef RetailCall_080a8a90
.global RetailCall_080a8a90
.thumb_set RetailCall_080a8a90, 0x080a8a91
.endif

.ifndef RetailCall_080a8a80
.global RetailCall_080a8a80
.thumb_set RetailCall_080a8a80, 0x080a8a81
.endif

.ifndef RetailCall_080a8aac
.global RetailCall_080a8aac
.thumb_set RetailCall_080a8aac, 0x080a8aad
.endif

.ifndef RetailCall_080bd328
.global RetailCall_080bd328
.thumb_set RetailCall_080bd328, 0x080bd329
.endif

.ifndef RetailCall_080bd34c
.global RetailCall_080bd34c
.thumb_set RetailCall_080bd34c, 0x080bd34d
.endif

.ifndef RetailCall_080bd340
.global RetailCall_080bd340
.thumb_set RetailCall_080bd340, 0x080bd341
.endif

.ifndef RetailCall_08092638
.global RetailCall_08092638
.thumb_set RetailCall_08092638, 0x08092639
.endif

.ifndef RetailCall_080230a8
.global RetailCall_080230a8
.thumb_set RetailCall_080230a8, 0x080230a9
.endif

.ifndef RetailCall_0809a664
.global RetailCall_0809a664
.thumb_set RetailCall_0809a664, 0x0809a665
.endif

.ifndef RetailCall_0809a63c
.global RetailCall_0809a63c
.thumb_set RetailCall_0809a63c, 0x0809a63d
.endif

.ifndef RetailCall_0809d464
.global RetailCall_0809d464
.thumb_set RetailCall_0809d464, 0x0809d465
.endif

.ifndef RetailCall_0809b818
.global RetailCall_0809b818
.thumb_set RetailCall_0809b818, 0x0809b819
.endif

.ifndef RetailCall_0809d7e4
.global RetailCall_0809d7e4
.thumb_set RetailCall_0809d7e4, 0x0809d7e5
.endif

.ifndef RetailCall_0809d638
.global RetailCall_0809d638
.thumb_set RetailCall_0809d638, 0x0809d639
.endif

.ifndef RetailCall_0809d620
.global RetailCall_0809d620
.thumb_set RetailCall_0809d620, 0x0809d621
.endif

.ifndef RetailCall_080c19a8
.global RetailCall_080c19a8
.thumb_set RetailCall_080c19a8, 0x080c19a9
.endif

.ifndef RetailCall_0809b88c
.global RetailCall_0809b88c
.thumb_set RetailCall_0809b88c, 0x0809b88d
.endif

.ifndef RetailCall_0809d614
.global RetailCall_0809d614
.thumb_set RetailCall_0809d614, 0x0809d615
.endif

.ifndef RetailCall_0809d640
.global RetailCall_0809d640
.thumb_set RetailCall_0809d640, 0x0809d641
.endif

.ifndef RetailCall_0809caf4
.global RetailCall_0809caf4
.thumb_set RetailCall_0809caf4, 0x0809caf5
.endif

.ifndef RetailCall_0809a710
.global RetailCall_0809a710
.thumb_set RetailCall_0809a710, 0x0809a711
.endif

.ifndef RetailCall_080b7f4c
.global RetailCall_080b7f4c
.thumb_set RetailCall_080b7f4c, 0x080b7f4d
.endif

.ifndef RetailCall_08141540
.global RetailCall_08141540
.thumb_set RetailCall_08141540, 0x08141541
.endif

.ifndef RetailCall_08099fb0
.global RetailCall_08099fb0
.thumb_set RetailCall_08099fb0, 0x08099fb1
.endif

.ifndef RetailCall_080b5880
.global RetailCall_080b5880
.thumb_set RetailCall_080b5880, 0x080b5881
.endif

.ifndef RetailCall_080a8288
.global RetailCall_080a8288
.thumb_set RetailCall_080a8288, 0x080a8289
.endif

.ifndef RetailCall_080a82c0
.global RetailCall_080a82c0
.thumb_set RetailCall_080a82c0, 0x080a82c1
.endif

.ifndef RetailCall_080b7e1c
.global RetailCall_080b7e1c
.thumb_set RetailCall_080b7e1c, 0x080b7e1d
.endif

.ifndef RetailCall_080b7f18
.global RetailCall_080b7f18
.thumb_set RetailCall_080b7f18, 0x080b7f19
.endif

.ifndef RetailCall_080b7efc
.global RetailCall_080b7efc
.thumb_set RetailCall_080b7efc, 0x080b7efd
.endif

.ifndef RetailCall_080b7e08
.global RetailCall_080b7e08
.thumb_set RetailCall_080b7e08, 0x080b7e09
.endif

.ifndef RetailCall_080b7edc
.global RetailCall_080b7edc
.thumb_set RetailCall_080b7edc, 0x080b7edd
.endif

.ifndef RetailCall_080b7e7c
.global RetailCall_080b7e7c
.thumb_set RetailCall_080b7e7c, 0x080b7e7d
.endif

.ifndef RetailCall_0801d624
.global RetailCall_0801d624
.thumb_set RetailCall_0801d624, 0x0801d625
.endif

.ifndef RetailCall_0801d918
.global RetailCall_0801d918
.thumb_set RetailCall_0801d918, 0x0801d919
.endif

.ifndef RetailCall_0801d8b8
.global RetailCall_0801d8b8
.thumb_set RetailCall_0801d8b8, 0x0801d8b9
.endif

.ifndef RetailCall_0801cc7c
.global RetailCall_0801cc7c
.thumb_set RetailCall_0801cc7c, 0x0801cc7d
.endif

.ifndef RetailCall_08025560
.global RetailCall_08025560
.thumb_set RetailCall_08025560, 0x08025561
.endif

.ifndef RetailCall_080c1ad4
.global RetailCall_080c1ad4
.thumb_set RetailCall_080c1ad4, 0x080c1ad5
.endif

.ifndef RetailCall_080294fc
.global RetailCall_080294fc
.thumb_set RetailCall_080294fc, 0x080294fd
.endif

.ifndef RetailCall_08099560
.global RetailCall_08099560
.thumb_set RetailCall_08099560, 0x08099561
.endif

.ifndef RetailCall_0809a900
.global RetailCall_0809a900
.thumb_set RetailCall_0809a900, 0x0809a901
.endif

.ifndef RetailCall_0809185c
.global RetailCall_0809185c
.thumb_set RetailCall_0809185c, 0x0809185d
.endif

.ifndef RetailCall_08091dc0
.global RetailCall_08091dc0
.thumb_set RetailCall_08091dc0, 0x08091dc1
.endif

.ifndef RetailCall_08091e48
.global RetailCall_08091e48
.thumb_set RetailCall_08091e48, 0x08091e49
.endif

.ifndef RetailCall_080922a4
.global RetailCall_080922a4
.thumb_set RetailCall_080922a4, 0x080922a5
.endif

.ifndef RetailCall_080922c4
.global RetailCall_080922c4
.thumb_set RetailCall_080922c4, 0x080922c5
.endif

.ifndef RetailCall_08092288
.global RetailCall_08092288
.thumb_set RetailCall_08092288, 0x08092289
.endif

.ifndef RetailCall_0809a950
.global RetailCall_0809a950
.thumb_set RetailCall_0809a950, 0x0809a951
.endif

.ifndef RetailCall_08091930
.global RetailCall_08091930
.thumb_set RetailCall_08091930, 0x08091931
.endif

.ifndef RetailCall_080917f8
.global RetailCall_080917f8
.thumb_set RetailCall_080917f8, 0x080917f9
.endif

.ifndef OMIT_AdvanceBattlePhaseBody
.global AdvanceBattlePhaseBody
.thumb_set AdvanceBattlePhaseBody, 0x8a3be19
.endif

/* Mission reward transaction: selected-source-bound real interfaces. */
.ifndef OMIT_MR04_PanelTileAddress
.global MR04_PanelTileAddress
.thumb_set MR04_PanelTileAddress, 0x0808b92d
.endif
.ifndef OMIT_MR04_DrawRewardRow
.global MR04_DrawRewardRow
.thumb_set MR04_DrawRewardRow, 0x08037a31
.endif
.ifndef OMIT_MR04_FillRewardArea
.global MR04_FillRewardArea
.thumb_set MR04_FillRewardArea, 0x08089369
.endif
.ifndef OMIT_MR04_CpuSet
.global MR04_CpuSet
.thumb_set MR04_CpuSet, 0x0814186d
.endif
.ifndef OMIT_MR04_UpdateRecordOutcome
.global MR04_UpdateRecordOutcome
.thumb_set MR04_UpdateRecordOutcome, 0x080cf119
.endif

.ifndef OMIT_MR04_SelectRandomReward
.global MR04_SelectRandomReward
.thumb_set MR04_SelectRandomReward, 0x080d21a9
.endif

/* Equipment transaction controller interfaces, verified against selected entries. */
.ifndef OMIT_EquipmentCall_74CE8
.global EquipmentCall_74CE8
.thumb_set EquipmentCall_74CE8, 0x08074ce9
.endif
.ifndef OMIT_EquipmentCall_74908
.global EquipmentCall_74908
.thumb_set EquipmentCall_74908, 0x08074909
.endif
.ifndef OMIT_EquipmentCall_74A54
.global EquipmentCall_74A54
.thumb_set EquipmentCall_74A54, 0x08074a55
.endif
.ifndef OMIT_EquipmentCall_774B4
.global EquipmentCall_774B4
.thumb_set EquipmentCall_774B4, 0x080774b5
.endif
.ifndef OMIT_EquipmentCall_73254
.global EquipmentCall_73254
.thumb_set EquipmentCall_73254, 0x08073255
.endif
.ifndef OMIT_EquipmentCall_72C78
.global EquipmentCall_72C78
.thumb_set EquipmentCall_72C78, 0x08072c79
.endif
.ifndef OMIT_EquipmentCall_748AC
.global EquipmentCall_748AC
.thumb_set EquipmentCall_748AC, 0x080748ad
.endif
.ifndef OMIT_EquipmentCall_88DF0
.global EquipmentCall_88DF0
.thumb_set EquipmentCall_88DF0, 0x08088df1
.endif
.ifndef OMIT_EquipmentCall_88FEC
.global EquipmentCall_88FEC
.thumb_set EquipmentCall_88FEC, 0x08088fed
.endif
.ifndef OMIT_EquipmentCall_89CE4
.global EquipmentCall_89CE4
.thumb_set EquipmentCall_89CE4, 0x08089ce5
.endif
.ifndef OMIT_EquipmentCall_8A1EC
.global EquipmentCall_8A1EC
.thumb_set EquipmentCall_8A1EC, 0x0808a1ed
.endif
.ifndef OMIT_EquipmentCall_8C354
.global EquipmentCall_8C354
.thumb_set EquipmentCall_8C354, 0x0808c355
.endif
.ifndef OMIT_EquipmentCall_8C630
.global EquipmentCall_8C630
.thumb_set EquipmentCall_8C630, 0x0808c631
.endif
.ifndef OMIT_EquipmentCall_8CACC
.global EquipmentCall_8CACC
.thumb_set EquipmentCall_8CACC, 0x0808cacd
.endif
.ifndef OMIT_EquipmentCall_7B858
.global EquipmentCall_7B858
.thumb_set EquipmentCall_7B858, 0x0807b859
.endif
.ifndef OMIT_EquipmentCall_79838
.global EquipmentCall_79838
.thumb_set EquipmentCall_79838, 0x08079839
.endif
.ifndef OMIT_EquipmentCall_8C16C
.global EquipmentCall_8C16C
.thumb_set EquipmentCall_8C16C, 0x0808c16d
.endif
.ifndef OMIT_EquipmentCall_7A094
.global EquipmentCall_7A094
.thumb_set EquipmentCall_7A094, 0x0807a095
.endif
.ifndef OMIT_EquipmentCall_7974C
.global EquipmentCall_7974C
.thumb_set EquipmentCall_7974C, 0x0807974d
.endif
.ifndef OMIT_EquipmentCall_799C0
.global EquipmentCall_799C0
.thumb_set EquipmentCall_799C0, 0x080799c1
.endif
.ifndef OMIT_EquipmentCall_82AEC
.global EquipmentCall_82AEC
.thumb_set EquipmentCall_82AEC, 0x08082aed
.endif
.ifndef OMIT_EquipmentCall_7A734
.global EquipmentCall_7A734
.thumb_set EquipmentCall_7A734, 0x0807a735
.endif
.ifndef OMIT_EquipmentCall_7A6CC
.global EquipmentCall_7A6CC
.thumb_set EquipmentCall_7A6CC, 0x0807a6cd
.endif
.ifndef OMIT_EquipmentCall_8EF4C
.global EquipmentCall_8EF4C
.thumb_set EquipmentCall_8EF4C, 0x0808ef4d
.endif
.ifndef OMIT_EquipmentCall_8AA18
.global EquipmentCall_8AA18
.thumb_set EquipmentCall_8AA18, 0x0808aa19
.endif
.ifndef OMIT_EquipmentCall_CB0D8
.global EquipmentCall_CB0D8
.thumb_set EquipmentCall_CB0D8, 0x080cb0d9
.endif
.ifndef OMIT_EquipmentCall_7614C
.global EquipmentCall_7614C
.thumb_set EquipmentCall_7614C, 0x0807614d
.endif
.ifndef OMIT_EquipmentCall_8C9C4
.global EquipmentCall_8C9C4
.thumb_set EquipmentCall_8C9C4, 0x0808c9c5
.endif
.ifndef OMIT_EquipmentWaitForNextVBlank
.global EquipmentWaitForNextVBlank
.thumb_set EquipmentWaitForNextVBlank, 0x08003399
.endif
.ifndef OMIT_EquipmentScanMask81
.global EquipmentScanMask81
.thumb_set EquipmentScanMask81, 0x080cb54d
.endif

/* Game-image transition policy and existing dependencies. */
.ifndef OMIT_SaveCall_CA0F8
.global SaveCall_CA0F8
.thumb_set SaveCall_CA0F8, 0x080ca0f9
.endif
.ifndef OMIT_SaveCall_CA150
.global SaveCall_CA150
.thumb_set SaveCall_CA150, 0x080ca151
.endif
.ifndef OMIT_SaveCall_CA1F0
.global SaveCall_CA1F0
.thumb_set SaveCall_CA1F0, 0x080ca1f1
.endif
.ifndef OMIT_SaveCall_13B57C
.global SaveCall_13B57C
.thumb_set SaveCall_13B57C, 0x0813b57d
.endif
.ifndef OMIT_SaveCall_13B2A8
.global SaveCall_13B2A8
.thumb_set SaveCall_13B2A8, 0x0813b2a9
.endif
.ifndef OMIT_SaveCall_13BC7C
.global SaveCall_13BC7C
.thumb_set SaveCall_13BC7C, 0x0813bc7d
.endif
.ifndef OMIT_SaveCall_C95D8
.global SaveCall_C95D8
.thumb_set SaveCall_C95D8, 0x080c95d9
.endif
.ifndef OMIT_SaveCall_C960C
.global SaveCall_C960C
.thumb_set SaveCall_C960C, 0x080c960d
.endif
.ifndef OMIT_SaveCall_12C030
.global SaveCall_12C030
.thumb_set SaveCall_12C030, 0x0812c031
.endif
.ifndef OMIT_SaveCall_1457FC
.global SaveCall_1457FC
.thumb_set SaveCall_1457FC, 0x081457fd
.endif
.ifndef OMIT_SaveCall_33C8
.global SaveCall_33C8
.thumb_set SaveCall_33C8, 0x080033c9
.endif
.ifndef OMIT_SaveCall_1DB78
.global SaveCall_1DB78
.thumb_set SaveCall_1DB78, 0x0801db79
.endif
.ifndef OMIT_SaveCall_1339C
.global SaveCall_1339C
.thumb_set SaveCall_1339C, 0x0801339d
.endif
.ifndef OMIT_SaveCall_231C0
.global SaveCall_231C0
.thumb_set SaveCall_231C0, 0x080231c1
.endif
.ifndef OMIT_SaveCall_13B9F8
.global SaveCall_13B9F8
.thumb_set SaveCall_13B9F8, 0x0813b9f9
.endif
.ifndef OMIT_SaveCall_13BA5C
.global SaveCall_13BA5C
.thumb_set SaveCall_13BA5C, 0x0813ba5d
.endif
.ifndef OMIT_ReadDecodedGameImage
.global ReadDecodedGameImage
.thumb_set ReadDecodedGameImage, 0x0813b481
.endif
.ifndef OMIT_WriteEncodedGameImage
.global WriteEncodedGameImage
.thumb_set WriteEncodedGameImage, 0x0813b0d5
.endif
.ifndef OMIT_PrepareTransitionGameImage
.global PrepareTransitionGameImage
.thumb_set PrepareTransitionGameImage, 0x0812c171
.endif
.ifndef OMIT_PrepareGameImageHeader
.global PrepareGameImageHeader
.thumb_set PrepareGameImageHeader, 0x0813bb05
.endif

/* Connected game-image restoration controller interfaces. */
.ifndef OMIT_RestoreCall_137B50
.global RestoreCall_137B50
.thumb_set RestoreCall_137B50, 0x08137b51
.endif
.ifndef OMIT_RestoreCall_137CC4
.global RestoreCall_137CC4
.thumb_set RestoreCall_137CC4, 0x08137cc5
.endif
.ifndef OMIT_RestoreCall_137EC4
.global RestoreCall_137EC4
.thumb_set RestoreCall_137EC4, 0x08137ec5
.endif
.ifndef OMIT_RestoreCall_1380A8
.global RestoreCall_1380A8
.thumb_set RestoreCall_1380A8, 0x081380a9
.endif
.ifndef OMIT_RestoreCall_1380B8
.global RestoreCall_1380B8
.thumb_set RestoreCall_1380B8, 0x081380b9
.endif
.ifndef OMIT_RestoreCall_138284
.global RestoreCall_138284
.thumb_set RestoreCall_138284, 0x08138285
.endif
.ifndef OMIT_RestoreCall_4C834
.global RestoreCall_4C834
.thumb_set RestoreCall_4C834, 0x0804c835
.endif
.ifndef OMIT_RestoreCall_6B8C
.global RestoreCall_6B8C
.thumb_set RestoreCall_6B8C, 0x08006b8d
.endif
.ifndef OMIT_RestoreCall_141748
.global RestoreCall_141748
.thumb_set RestoreCall_141748, 0x08141749
.endif
.ifndef OMIT_RestoreCall_138354
.global RestoreCall_138354
.thumb_set RestoreCall_138354, 0x08138355
.endif
.ifndef OMIT_RestoreCall_13839C
.global RestoreCall_13839C
.thumb_set RestoreCall_13839C, 0x0813839d
.endif
.ifndef OMIT_RestoreCall_1384B0
.global RestoreCall_1384B0
.thumb_set RestoreCall_1384B0, 0x081384b1
.endif
.ifndef OMIT_RestoreCall_1385CC
.global RestoreCall_1385CC
.thumb_set RestoreCall_1385CC, 0x081385cd
.endif
.ifndef OMIT_RestoreCall_1386BC
.global RestoreCall_1386BC
.thumb_set RestoreCall_1386BC, 0x081386bd
.endif
.ifndef OMIT_RestoreCall_138A3C
.global RestoreCall_138A3C
.thumb_set RestoreCall_138A3C, 0x08138a3d
.endif
.ifndef OMIT_RestoreCall_138B4C
.global RestoreCall_138B4C
.thumb_set RestoreCall_138B4C, 0x08138b4d
.endif
.ifndef OMIT_RestoreCall_138DA4
.global RestoreCall_138DA4
.thumb_set RestoreCall_138DA4, 0x08138da5
.endif
.ifndef OMIT_RestoreCall_138E80
.global RestoreCall_138E80
.thumb_set RestoreCall_138E80, 0x08138e81
.endif
.ifndef OMIT_RestoreCall_9920
.global RestoreCall_9920
.thumb_set RestoreCall_9920, 0x08009921
.endif
.ifndef OMIT_RestoreCall_137C48
.global RestoreCall_137C48
.thumb_set RestoreCall_137C48, 0x08137c49
.endif
.ifndef OMIT_RestoreCall_3888
.global RestoreCall_3888
.thumb_set RestoreCall_3888, 0x08003889
.endif
.ifndef OMIT_RestoreCall_39E8
.global RestoreCall_39E8
.thumb_set RestoreCall_39E8, 0x080039e9
.endif
.ifndef OMIT_RestoreCall_38C8
.global RestoreCall_38C8
.thumb_set RestoreCall_38C8, 0x080038c9
.endif
.ifndef OMIT_RestoreCall_13B6A4
.global RestoreCall_13B6A4
.thumb_set RestoreCall_13B6A4, 0x0813b6a5
.endif

/* Battle action calculation typed interfaces. */
.ifndef OMIT_BattleCalculationCall_0812FD44
.global BattleCalculationCall_0812FD44
.thumb_set BattleCalculationCall_0812FD44, 0x0812fd45
.endif
.ifndef OMIT_BattleCalculationCall_0812FDDC
.global BattleCalculationCall_0812FDDC
.thumb_set BattleCalculationCall_0812FDDC, 0x0812fddd
.endif
.ifndef OMIT_BattleCalculationCall_0812FE28
.global BattleCalculationCall_0812FE28
.thumb_set BattleCalculationCall_0812FE28, 0x0812fe29
.endif
.ifndef OMIT_BattleCalculationCall_0812F5E0
.global BattleCalculationCall_0812F5E0
.thumb_set BattleCalculationCall_0812F5E0, 0x0812f5e1
.endif
.ifndef OMIT_BattleCalculationCall_0812F8A4
.global BattleCalculationCall_0812F8A4
.thumb_set BattleCalculationCall_0812F8A4, 0x0812f8a5
.endif
.ifndef OMIT_BattleCalculationCall_0812FA90
.global BattleCalculationCall_0812FA90
.thumb_set BattleCalculationCall_0812FA90, 0x0812fa91
.endif
.ifndef OMIT_BattleCalculationCall_0812FC74
.global BattleCalculationCall_0812FC74
.thumb_set BattleCalculationCall_0812FC74, 0x0812fc75
.endif
.ifndef OMIT_BattleCalculationCall_0812FAFC
.global BattleCalculationCall_0812FAFC
.thumb_set BattleCalculationCall_0812FAFC, 0x0812fafd
.endif
.ifndef OMIT_BattleCalculationCall_080CD50C
.global BattleCalculationCall_080CD50C
.thumb_set BattleCalculationCall_080CD50C, 0x080cd50d
.endif
.ifndef OMIT_BattleCalculationCall_0812F8E8
.global BattleCalculationCall_0812F8E8
.thumb_set BattleCalculationCall_0812F8E8, 0x0812f8e9
.endif
.ifndef OMIT_BattleCalculationCall_080D2CC4
.global BattleCalculationCall_080D2CC4
.thumb_set BattleCalculationCall_080D2CC4, 0x080d2cc5
.endif
.ifndef OMIT_BattleCalculationCall_080CDA4C
.global BattleCalculationCall_080CDA4C
.thumb_set BattleCalculationCall_080CDA4C, 0x080cda4d
.endif
.ifndef OMIT_BattleCalculationCall_08130620
.global BattleCalculationCall_08130620
.thumb_set BattleCalculationCall_08130620, 0x08130621
.endif

.ifndef OMIT_CalculateBattleActionAmount
.global CalculateBattleActionAmount
.thumb_set CalculateBattleActionAmount, 0x0812fe39
.endif

/* Typed battle effect rule interfaces; implementations remain selected. */
.ifndef OMIT_EffectRuleCall_080C8384
.global EffectRuleCall_080C8384
.thumb_set EffectRuleCall_080C8384, 0x080c8385
.endif
.ifndef OMIT_EffectRuleCall_080CDBCC
.global EffectRuleCall_080CDBCC
.thumb_set EffectRuleCall_080CDBCC, 0x080cdbcd
.endif
.ifndef OMIT_EffectRuleCall_0813189C
.global EffectRuleCall_0813189C
.thumb_set EffectRuleCall_0813189C, 0x0813189d
.endif
.ifndef OMIT_EffectRuleCall_081314FC
.global EffectRuleCall_081314FC
.thumb_set EffectRuleCall_081314FC, 0x081314fd
.endif
.ifndef OMIT_EffectRuleCall_08130CC4
.global EffectRuleCall_08130CC4
.thumb_set EffectRuleCall_08130CC4, 0x08130cc5
.endif
.ifndef OMIT_EffectRuleCall_08130D54
.global EffectRuleCall_08130D54
.thumb_set EffectRuleCall_08130D54, 0x08130d55
.endif
.ifndef OMIT_EffectRuleCall_08130D80
.global EffectRuleCall_08130D80
.thumb_set EffectRuleCall_08130D80, 0x08130d81
.endif
.ifndef OMIT_EffectRuleCall_08130DCC
.global EffectRuleCall_08130DCC
.thumb_set EffectRuleCall_08130DCC, 0x08130dcd
.endif
.ifndef OMIT_EffectRuleCall_0813054C
.global EffectRuleCall_0813054C
.thumb_set EffectRuleCall_0813054C, 0x0813054d
.endif
.ifndef OMIT_EffectRuleCall_0813079C
.global EffectRuleCall_0813079C
.thumb_set EffectRuleCall_0813079C, 0x0813079d
.endif
.ifndef OMIT_EffectRuleCall_081307C8
.global EffectRuleCall_081307C8
.thumb_set EffectRuleCall_081307C8, 0x081307c9
.endif
.ifndef OMIT_EffectRuleCall_081307F4
.global EffectRuleCall_081307F4
.thumb_set EffectRuleCall_081307F4, 0x081307f5
.endif
.ifndef OMIT_EffectRuleCall_08130150
.global EffectRuleCall_08130150
.thumb_set EffectRuleCall_08130150, 0x08130151
.endif

/* Typed effect resolution interfaces; existing bodies are reused. */
.ifndef OMIT_EffectResolutionCall_0812F2CC
.global EffectResolutionCall_0812F2CC
.thumb_set EffectResolutionCall_0812F2CC, 0x0812f2cd
.endif
.ifndef OMIT_EffectResolutionCall_0812F124
.global EffectResolutionCall_0812F124
.thumb_set EffectResolutionCall_0812F124, 0x0812f125
.endif
.ifndef OMIT_EffectResolutionCall_08133A58
.global EffectResolutionCall_08133A58
.thumb_set EffectResolutionCall_08133A58, 0x08133a59
.endif
.ifndef OMIT_EffectResolutionCall_0812DAB8
.global EffectResolutionCall_0812DAB8
.thumb_set EffectResolutionCall_0812DAB8, 0x0812dab9
.endif
.ifndef OMIT_EffectResolutionCall_0812D398
.global EffectResolutionCall_0812D398
.thumb_set EffectResolutionCall_0812D398, 0x0812d399
.endif
.ifndef OMIT_EffectResolutionCall_0812DAEC
.global EffectResolutionCall_0812DAEC
.thumb_set EffectResolutionCall_0812DAEC, 0x0812daed
.endif
.ifndef OMIT_EffectResolutionCall_0812F068
.global EffectResolutionCall_0812F068
.thumb_set EffectResolutionCall_0812F068, 0x0812f069
.endif
.ifndef OMIT_EffectResolutionCall_0812F054
.global EffectResolutionCall_0812F054
.thumb_set EffectResolutionCall_0812F054, 0x0812f055
.endif
.ifndef OMIT_EffectResolutionCall_0812D388
.global EffectResolutionCall_0812D388
.thumb_set EffectResolutionCall_0812D388, 0x0812d389
.endif
.ifndef OMIT_EffectResolutionCall_0812D5F4
.global EffectResolutionCall_0812D5F4
.thumb_set EffectResolutionCall_0812D5F4, 0x0812d5f5
.endif
.ifndef OMIT_EffectResolutionCall_0812DA0C
.global EffectResolutionCall_0812DA0C
.thumb_set EffectResolutionCall_0812DA0C, 0x0812da0d
.endif
.ifndef OMIT_EffectResolutionCall_0812D99C
.global EffectResolutionCall_0812D99C
.thumb_set EffectResolutionCall_0812D99C, 0x0812d99d
.endif
.ifndef OMIT_EffectResolutionCall_0812F008
.global EffectResolutionCall_0812F008
.thumb_set EffectResolutionCall_0812F008, 0x0812f009
.endif
.ifndef OMIT_EffectResolutionCall_0812D358
.global EffectResolutionCall_0812D358
.thumb_set EffectResolutionCall_0812D358, 0x0812d359
.endif
.ifndef OMIT_EffectResolutionCall_0812D2F0
.global EffectResolutionCall_0812D2F0
.thumb_set EffectResolutionCall_0812D2F0, 0x0812d2f1
.endif
.ifndef OMIT_EffectResolutionCall_0812DB5C
.global EffectResolutionCall_0812DB5C
.thumb_set EffectResolutionCall_0812DB5C, 0x0812db5d
.endif
.ifndef OMIT_EffectResolutionCall_0812F1CC
.global EffectResolutionCall_0812F1CC
.thumb_set EffectResolutionCall_0812F1CC, 0x0812f1cd
.endif
.ifndef OMIT_EffectResolutionCall_080CD8FC
.global EffectResolutionCall_080CD8FC
.thumb_set EffectResolutionCall_080CD8FC, 0x080cd8fd
.endif
.ifndef OMIT_EffectResolutionCall_08131220
.global EffectResolutionCall_08131220
.thumb_set EffectResolutionCall_08131220, 0x08131221
.endif
.ifndef OMIT_EffectResolutionCall_08131160
.global EffectResolutionCall_08131160
.thumb_set EffectResolutionCall_08131160, 0x08131161
.endif
.ifndef OMIT_EffectResolutionCall_0813112C
.global EffectResolutionCall_0813112C
.thumb_set EffectResolutionCall_0813112C, 0x0813112d
.endif
.ifndef OMIT_EffectResolutionCall_080CDCA4
.global EffectResolutionCall_080CDCA4
.thumb_set EffectResolutionCall_080CDCA4, 0x080cdca5
.endif

/* Effect application interfaces: verified exact Thumb targets. */
.ifndef OWN_EffectApplicationCall_0802DA00
.global EffectApplicationCall_0802DA00
.thumb_set EffectApplicationCall_0802DA00, 0x0802da01
.endif
.ifndef OWN_EffectApplicationCall_0802DC60
.global EffectApplicationCall_0802DC60
.thumb_set EffectApplicationCall_0802DC60, 0x0802dc61
.endif
.ifndef OWN_EffectApplicationCall_08098E7C
.global EffectApplicationCall_08098E7C
.thumb_set EffectApplicationCall_08098E7C, 0x08098e7d
.endif
.ifndef OWN_EffectApplicationCall_080C832C
.global EffectApplicationCall_080C832C
.thumb_set EffectApplicationCall_080C832C, 0x080c832d
.endif
.ifndef OWN_EffectApplicationCall_080CD364
.global EffectApplicationCall_080CD364
.thumb_set EffectApplicationCall_080CD364, 0x080cd365
.endif
.ifndef OWN_EffectApplicationCall_080CD544
.global EffectApplicationCall_080CD544
.thumb_set EffectApplicationCall_080CD544, 0x080cd545
.endif
.ifndef OWN_EffectApplicationCall_080CDE80
.global EffectApplicationCall_080CDE80
.thumb_set EffectApplicationCall_080CDE80, 0x080cde81
.endif
.ifndef OWN_EffectApplicationCall_080CE314
.global EffectApplicationCall_080CE314
.thumb_set EffectApplicationCall_080CE314, 0x080ce315
.endif
.ifndef OWN_EffectApplicationCall_0812D660
.global EffectApplicationCall_0812D660
.thumb_set EffectApplicationCall_0812D660, 0x0812d661
.endif
.ifndef OWN_EffectApplicationCall_0812D7FC
.global EffectApplicationCall_0812D7FC
.thumb_set EffectApplicationCall_0812D7FC, 0x0812d7fd
.endif
.ifndef OWN_EffectApplicationCall_0812EBD0
.global EffectApplicationCall_0812EBD0
.thumb_set EffectApplicationCall_0812EBD0, 0x0812ebd1
.endif
.ifndef OWN_EffectApplicationCall_0812EDF0
.global EffectApplicationCall_0812EDF0
.thumb_set EffectApplicationCall_0812EDF0, 0x0812edf1
.endif
.ifndef OWN_EffectApplicationCall_08131BB8
.global EffectApplicationCall_08131BB8
.thumb_set EffectApplicationCall_08131BB8, 0x08131bb9
.endif
.ifndef OWN_EffectApplicationCall_08131C28
.global EffectApplicationCall_08131C28
.thumb_set EffectApplicationCall_08131C28, 0x08131c29
.endif
.ifndef OWN_EffectApplicationCall_08131DD4
.global EffectApplicationCall_08131DD4
.thumb_set EffectApplicationCall_08131DD4, 0x08131dd5
.endif
.ifndef OWN_EffectApplicationCall_081320E8
.global EffectApplicationCall_081320E8
.thumb_set EffectApplicationCall_081320E8, 0x081320e9
.endif
.ifndef OWN_EffectApplicationCall_08132160
.global EffectApplicationCall_08132160
.thumb_set EffectApplicationCall_08132160, 0x08132161
.endif
.ifndef OWN_EffectApplicationCall_081321B4
.global EffectApplicationCall_081321B4
.thumb_set EffectApplicationCall_081321B4, 0x081321b5
.endif
.ifndef OWN_EffectApplicationCall_0813255C
.global EffectApplicationCall_0813255C
.thumb_set EffectApplicationCall_0813255C, 0x0813255d
.endif
.ifndef OWN_EffectApplicationCall_08132CB8
.global EffectApplicationCall_08132CB8
.thumb_set EffectApplicationCall_08132CB8, 0x08132cb9
.endif
.ifndef OWN_EffectApplicationCall_08132D84
.global EffectApplicationCall_08132D84
.thumb_set EffectApplicationCall_08132D84, 0x08132d85
.endif
.ifndef OWN_EffectApplicationCall_08132DDC
.global EffectApplicationCall_08132DDC
.thumb_set EffectApplicationCall_08132DDC, 0x08132ddd
.endif
.ifndef OWN_EffectApplicationCall_08132E2C
.global EffectApplicationCall_08132E2C
.thumb_set EffectApplicationCall_08132E2C, 0x08132e2d
.endif
.ifndef OWN_EffectApplicationCall_0813325C
.global EffectApplicationCall_0813325C
.thumb_set EffectApplicationCall_0813325C, 0x0813325d
.endif
.ifndef OWN_EffectApplicationCall_08133CC8
.global EffectApplicationCall_08133CC8
.thumb_set EffectApplicationCall_08133CC8, 0x08133cc9
.endif

/* Reaction eligibility: exact source-pinned Thumb interfaces. */
.ifndef OWN_ReactionPolicyCall_0812E55C
.global ReactionPolicyCall_0812E55C
.thumb_set ReactionPolicyCall_0812E55C, 0x0812e55d
.endif
.ifndef OWN_ReactionPolicyCall_081306E0
.global ReactionPolicyCall_081306E0
.thumb_set ReactionPolicyCall_081306E0, 0x081306e1
.endif
.ifndef OWN_ReactionPolicyCall_0812E1A8
.global ReactionPolicyCall_0812E1A8
.thumb_set ReactionPolicyCall_0812E1A8, 0x0812e1a9
.endif
.ifndef OWN_ReactionPolicyCall_0812E6E0
.global ReactionPolicyCall_0812E6E0
.thumb_set ReactionPolicyCall_0812E6E0, 0x0812e6e1
.endif

/* Mission/event controller: source-decoded Thumb interfaces. */
.ifndef OWN_MissionEventCall_08006ADC
.global MissionEventCall_08006ADC
.thumb_set MissionEventCall_08006ADC, 0x08006add
.endif
.ifndef OWN_MissionEventCall_08008818
.global MissionEventCall_08008818
.thumb_set MissionEventCall_08008818, 0x08008819
.endif
.ifndef OWN_MissionEventCall_08008880
.global MissionEventCall_08008880
.thumb_set MissionEventCall_08008880, 0x08008881
.endif
.ifndef OWN_MissionEventCall_08013404
.global MissionEventCall_08013404
.thumb_set MissionEventCall_08013404, 0x08013405
.endif
.ifndef OWN_MissionEventCall_08013428
.global MissionEventCall_08013428
.thumb_set MissionEventCall_08013428, 0x08013429
.endif
.ifndef OWN_MissionEventCall_08030044
.global MissionEventCall_08030044
.thumb_set MissionEventCall_08030044, 0x08030045
.endif
.ifndef OWN_MissionEventCall_080314C8
.global MissionEventCall_080314C8
.thumb_set MissionEventCall_080314C8, 0x080314c9
.endif
.ifndef OWN_MissionEventCall_08031658
.global MissionEventCall_08031658
.thumb_set MissionEventCall_08031658, 0x08031659
.endif
.ifndef OWN_MissionEventCall_08031674
.global MissionEventCall_08031674
.thumb_set MissionEventCall_08031674, 0x08031675
.endif
.ifndef OWN_MissionEventCall_080318E8
.global MissionEventCall_080318E8
.thumb_set MissionEventCall_080318E8, 0x080318e9
.endif
.ifndef OWN_MissionEventCall_08031978
.global MissionEventCall_08031978
.thumb_set MissionEventCall_08031978, 0x08031979
.endif
.ifndef OWN_MissionEventCall_0803591C
.global MissionEventCall_0803591C
.thumb_set MissionEventCall_0803591C, 0x0803591d
.endif
.ifndef OWN_MissionEventCall_08035D00
.global MissionEventCall_08035D00
.thumb_set MissionEventCall_08035D00, 0x08035d01
.endif
.ifndef OWN_MissionEventCall_08035E04
.global MissionEventCall_08035E04
.thumb_set MissionEventCall_08035E04, 0x08035e05
.endif
.ifndef OWN_MissionEventCall_080365B8
.global MissionEventCall_080365B8
.thumb_set MissionEventCall_080365B8, 0x080365b9
.endif
.ifndef OWN_MissionEventCall_08036CA8
.global MissionEventCall_08036CA8
.thumb_set MissionEventCall_08036CA8, 0x08036ca9
.endif
.ifndef OWN_MissionEventCall_08036D44
.global MissionEventCall_08036D44
.thumb_set MissionEventCall_08036D44, 0x08036d45
.endif
.ifndef OWN_MissionEventCall_0803701C
.global MissionEventCall_0803701C
.thumb_set MissionEventCall_0803701C, 0x0803701d
.endif
.ifndef OWN_MissionEventCall_08037428
.global MissionEventCall_08037428
.thumb_set MissionEventCall_08037428, 0x08037429
.endif
.ifndef OWN_MissionEventCall_080376AC
.global MissionEventCall_080376AC
.thumb_set MissionEventCall_080376AC, 0x080376ad
.endif
.ifndef OWN_MissionEventCall_080376F4
.global MissionEventCall_080376F4
.thumb_set MissionEventCall_080376F4, 0x080376f5
.endif
.ifndef OWN_MissionEventCall_08038324
.global MissionEventCall_08038324
.thumb_set MissionEventCall_08038324, 0x08038325
.endif
.ifndef OWN_MissionEventCall_08038B00
.global MissionEventCall_08038B00
.thumb_set MissionEventCall_08038B00, 0x08038b01
.endif
.ifndef OWN_MissionEventCall_08038B2C
.global MissionEventCall_08038B2C
.thumb_set MissionEventCall_08038B2C, 0x08038b2d
.endif
.ifndef OWN_MissionEventCall_08038B58
.global MissionEventCall_08038B58
.thumb_set MissionEventCall_08038B58, 0x08038b59
.endif
.ifndef OWN_MissionEventCall_0803A958
.global MissionEventCall_0803A958
.thumb_set MissionEventCall_0803A958, 0x0803a959
.endif
.ifndef OWN_MissionEventCall_08044038
.global MissionEventCall_08044038
.thumb_set MissionEventCall_08044038, 0x08044039
.endif
.ifndef OWN_MissionEventCall_0804409C
.global MissionEventCall_0804409C
.thumb_set MissionEventCall_0804409C, 0x0804409d
.endif
.ifndef OWN_MissionEventCall_0804413C
.global MissionEventCall_0804413C
.thumb_set MissionEventCall_0804413C, 0x0804413d
.endif
.ifndef OWN_MissionEventCall_08044158
.global MissionEventCall_08044158
.thumb_set MissionEventCall_08044158, 0x08044159
.endif
.ifndef OWN_MissionEventCall_08045390
.global MissionEventCall_08045390
.thumb_set MissionEventCall_08045390, 0x08045391
.endif
.ifndef OWN_MissionEventCall_0804BDDC
.global MissionEventCall_0804BDDC
.thumb_set MissionEventCall_0804BDDC, 0x0804bddd
.endif
.ifndef OWN_MissionEventCall_080C9540
.global MissionEventCall_080C9540
.thumb_set MissionEventCall_080C9540, 0x080c9541
.endif
.ifndef OWN_MissionEventCall_080D1A18
.global MissionEventCall_080D1A18
.thumb_set MissionEventCall_080D1A18, 0x080d1a19
.endif
.ifndef OWN_MissionEventCall_080D2E6C
.global MissionEventCall_080D2E6C
.thumb_set MissionEventCall_080D2E6C, 0x080d2e6d
.endif
.ifndef OWN_MissionEventCall_081417E8
.global MissionEventCall_081417E8
.thumb_set MissionEventCall_081417E8, 0x081417e9
.endif

.ifndef OMIT_BattleActivationCall_0800397C
.global BattleActivationCall_0800397C
.thumb_set BattleActivationCall_0800397C, 0x0800397d
.endif

.ifndef OMIT_BattleActivationCall_08096BA0
.global BattleActivationCall_08096BA0
.thumb_set BattleActivationCall_08096BA0, 0x08096ba1
.endif

.ifndef OMIT_BattleActivationCall_080BD11C
.global BattleActivationCall_080BD11C
.thumb_set BattleActivationCall_080BD11C, 0x080bd11d
.endif

.ifndef OMIT_BattleActivationCall_0809AB14
.global BattleActivationCall_0809AB14
.thumb_set BattleActivationCall_0809AB14, 0x0809ab15
.endif

.ifndef OMIT_BattleActivationCall_081256BC
.global BattleActivationCall_081256BC
.thumb_set BattleActivationCall_081256BC, 0x081256bd
.endif

.ifndef OMIT_BattleActivationCall_08024758
.global BattleActivationCall_08024758
.thumb_set BattleActivationCall_08024758, 0x08024759
.endif

.ifndef OMIT_BattleActivationCall_08121BF4
.global BattleActivationCall_08121BF4
.thumb_set BattleActivationCall_08121BF4, 0x08121bf5
.endif

.ifndef OMIT_BattleActivationCall_0802DBA0
.global BattleActivationCall_0802DBA0
.thumb_set BattleActivationCall_0802DBA0, 0x0802dba1
.endif

.ifndef OMIT_ActivateBattleSceneModeSeven
.global ActivateBattleSceneModeSeven
.thumb_set ActivateBattleSceneModeSeven, 0x08123d51
.endif

.ifndef OMIT_SelectionCall_0800A018
.global SelectionCall_0800A018
.thumb_set SelectionCall_0800A018, 0x800a019
.endif

.ifndef OMIT_SelectionCall_08011860
.global SelectionCall_08011860
.thumb_set SelectionCall_08011860, 0x8011861
.endif

.ifndef OMIT_SelectionCall_08013380
.global SelectionCall_08013380
.thumb_set SelectionCall_08013380, 0x8013381
.endif

.ifndef OMIT_SelectionCall_0801CC18
.global SelectionCall_0801CC18
.thumb_set SelectionCall_0801CC18, 0x801cc19
.endif

.ifndef OMIT_SelectionCall_08021854
.global SelectionCall_08021854
.thumb_set SelectionCall_08021854, 0x8021855
.endif

.ifndef OMIT_SelectionCall_0802192C
.global SelectionCall_0802192C
.thumb_set SelectionCall_0802192C, 0x802192d
.endif

.ifndef OMIT_SelectionCall_0802200C
.global SelectionCall_0802200C
.thumb_set SelectionCall_0802200C, 0x802200d
.endif

.ifndef OMIT_SelectionCall_0802542C
.global SelectionCall_0802542C
.thumb_set SelectionCall_0802542C, 0x802542d
.endif

.ifndef OMIT_SelectionCall_08025464
.global SelectionCall_08025464
.thumb_set SelectionCall_08025464, 0x8025465
.endif

.ifndef OMIT_SelectionCall_080294BC
.global SelectionCall_080294BC
.thumb_set SelectionCall_080294BC, 0x80294bd
.endif

.ifndef OMIT_SelectionCall_080294E4
.global SelectionCall_080294E4
.thumb_set SelectionCall_080294E4, 0x80294e5
.endif

.ifndef OMIT_SelectionCall_08029544
.global SelectionCall_08029544
.thumb_set SelectionCall_08029544, 0x8029545
.endif

.ifndef OMIT_SelectionCall_0802966C
.global SelectionCall_0802966C
.thumb_set SelectionCall_0802966C, 0x802966d
.endif

.ifndef OMIT_SelectionCall_0802B70C
.global SelectionCall_0802B70C
.thumb_set SelectionCall_0802B70C, 0x802b70d
.endif

.ifndef OMIT_SelectionCall_0802B880
.global SelectionCall_0802B880
.thumb_set SelectionCall_0802B880, 0x802b881
.endif

.ifndef OMIT_SelectionCall_0802D704
.global SelectionCall_0802D704
.thumb_set SelectionCall_0802D704, 0x802d705
.endif

.ifndef OMIT_SelectionCall_0802D72C
.global SelectionCall_0802D72C
.thumb_set SelectionCall_0802D72C, 0x802d72d
.endif

.ifndef OMIT_SelectionCall_0802FB64
.global SelectionCall_0802FB64
.thumb_set SelectionCall_0802FB64, 0x802fb65
.endif

.ifndef OMIT_SelectionCall_0802FB94
.global SelectionCall_0802FB94
.thumb_set SelectionCall_0802FB94, 0x802fb95
.endif

.ifndef OMIT_SelectionCall_0802FC74
.global SelectionCall_0802FC74
.thumb_set SelectionCall_0802FC74, 0x802fc75
.endif

.ifndef OMIT_SelectionCall_08092440
.global SelectionCall_08092440
.thumb_set SelectionCall_08092440, 0x8092441
.endif

.ifndef OMIT_SelectionCall_08096F3C
.global SelectionCall_08096F3C
.thumb_set SelectionCall_08096F3C, 0x8096f3d
.endif

.ifndef OMIT_SelectionCall_08096F7C
.global SelectionCall_08096F7C
.thumb_set SelectionCall_08096F7C, 0x8096f7d
.endif

.ifndef OMIT_SelectionCall_08099560
.global SelectionCall_08099560
.thumb_set SelectionCall_08099560, 0x8099561
.endif

.ifndef OMIT_SelectionCall_080995C0
.global SelectionCall_080995C0
.thumb_set SelectionCall_080995C0, 0x80995c1
.endif

.ifndef OMIT_SelectionCall_0809961C
.global SelectionCall_0809961C
.thumb_set SelectionCall_0809961C, 0x809961d
.endif

.ifndef OMIT_SelectionCall_08099644
.global SelectionCall_08099644
.thumb_set SelectionCall_08099644, 0x8099645
.endif

.ifndef OMIT_SelectionCall_08099C1C
.global SelectionCall_08099C1C
.thumb_set SelectionCall_08099C1C, 0x8099c1d
.endif

.ifndef OMIT_SelectionCall_08099C30
.global SelectionCall_08099C30
.thumb_set SelectionCall_08099C30, 0x8099c31
.endif

.ifndef OMIT_SelectionCall_08099CC4
.global SelectionCall_08099CC4
.thumb_set SelectionCall_08099CC4, 0x8099cc5
.endif

.ifndef OMIT_SelectionCall_0809A68C
.global SelectionCall_0809A68C
.thumb_set SelectionCall_0809A68C, 0x809a68d
.endif

.ifndef OMIT_SelectionCall_0809A6C4
.global SelectionCall_0809A6C4
.thumb_set SelectionCall_0809A6C4, 0x809a6c5
.endif

.ifndef OMIT_SelectionCall_080A8288
.global SelectionCall_080A8288
.thumb_set SelectionCall_080A8288, 0x80a8289
.endif

.ifndef OMIT_SelectionCall_080A82C0
.global SelectionCall_080A82C0
.thumb_set SelectionCall_080A82C0, 0x80a82c1
.endif

.ifndef OMIT_SelectionCall_080A9528
.global SelectionCall_080A9528
.thumb_set SelectionCall_080A9528, 0x80a9529
.endif

.ifndef OMIT_SelectionCall_080A9548
.global SelectionCall_080A9548
.thumb_set SelectionCall_080A9548, 0x80a9549
.endif

.ifndef OMIT_SelectionCall_080A9588
.global SelectionCall_080A9588
.thumb_set SelectionCall_080A9588, 0x80a9589
.endif

.ifndef OMIT_SelectionCall_080B7FC8
.global SelectionCall_080B7FC8
.thumb_set SelectionCall_080B7FC8, 0x80b7fc9
.endif

.ifndef OMIT_SelectionCall_080BA66C
.global SelectionCall_080BA66C
.thumb_set SelectionCall_080BA66C, 0x80ba66d
.endif

.ifndef OMIT_SelectionCall_080BA728
.global SelectionCall_080BA728
.thumb_set SelectionCall_080BA728, 0x80ba729
.endif

.ifndef OMIT_SelectionCall_080BA7D8
.global SelectionCall_080BA7D8
.thumb_set SelectionCall_080BA7D8, 0x80ba7d9
.endif

.ifndef OMIT_SelectionCall_080BA7FC
.global SelectionCall_080BA7FC
.thumb_set SelectionCall_080BA7FC, 0x80ba7fd
.endif

.ifndef OMIT_SelectionCall_080BA818
.global SelectionCall_080BA818
.thumb_set SelectionCall_080BA818, 0x80ba819
.endif

.ifndef OMIT_SelectionCall_080C7554
.global SelectionCall_080C7554
.thumb_set SelectionCall_080C7554, 0x80c7555
.endif

.ifndef OMIT_SelectionCall_080C7560
.global SelectionCall_080C7560
.thumb_set SelectionCall_080C7560, 0x80c7561
.endif

.ifndef OMIT_SelectionCall_080C8298
.global SelectionCall_080C8298
.thumb_set SelectionCall_080C8298, 0x80c8299
.endif

.ifndef OMIT_SelectionCall_080CDD04
.global SelectionCall_080CDD04
.thumb_set SelectionCall_080CDD04, 0x80cdd05
.endif

.ifndef OMIT_SelectionCall_08133BC4
.global SelectionCall_08133BC4
.thumb_set SelectionCall_08133BC4, 0x8133bc5
.endif

.ifndef OMIT_SelectionCall_08141540
.global SelectionCall_08141540
.thumb_set SelectionCall_08141540, 0x8141541
.endif

.ifndef OMIT_SelectionCall_08141570
.global SelectionCall_08141570
.thumb_set SelectionCall_08141570, 0x8141571
.endif

.ifndef OMIT_AdvanceBattleSceneRecordBody
.global AdvanceBattleSceneRecordBody
.thumb_set AdvanceBattleSceneRecordBody, 0x080b84b5
.endif

.ifndef OMIT_InitializeDirectionChoiceObject
.global InitializeDirectionChoiceObject
.thumb_set InitializeDirectionChoiceObject, 0x080a1b59
.endif

.ifndef OMIT_AdvanceDirectionChoiceObject
.global AdvanceDirectionChoiceObject
.thumb_set AdvanceDirectionChoiceObject, 0x080a1be9
.endif

.ifndef OMIT_DirectionProjectCoordinates
.global DirectionProjectCoordinates
.thumb_set DirectionProjectCoordinates, 0x0801c985
.endif

.ifndef OMIT_DirectionPlaySound
.global DirectionPlaySound
.thumb_set DirectionPlaySound, 0x08141541
.endif

.ifndef OMIT_InitializeDirectionChoiceObjectBody
.global InitializeDirectionChoiceObjectBody
.thumb_set InitializeDirectionChoiceObjectBody, 0x08a414a1
.endif

.ifndef OMIT_AdvanceDirectionChoiceObjectBody
.global AdvanceDirectionChoiceObjectBody
.thumb_set AdvanceDirectionChoiceObjectBody, 0x08a415a1
.endif

.ifndef OMIT_RetailCall_08007c84
.global RetailCall_08007c84
.thumb_set RetailCall_08007c84, 0x08007c85
.endif

.ifndef OMIT_RetailCall_0809a398
.global RetailCall_0809a398
.thumb_set RetailCall_0809a398, 0x0809a399
.endif

.ifndef OMIT_RetailCall_0809a530
.global RetailCall_0809a530
.thumb_set RetailCall_0809a530, 0x0809a531
.endif

.ifndef OMIT_RetailCall_0809a53c
.global RetailCall_0809a53c
.thumb_set RetailCall_0809a53c, 0x0809a53d
.endif

.ifndef OMIT_RetailCall_0809adec
.global RetailCall_0809adec
.thumb_set RetailCall_0809adec, 0x0809aded
.endif

.ifndef OMIT_RetailCall_0809ae84
.global RetailCall_0809ae84
.thumb_set RetailCall_0809ae84, 0x0809ae85
.endif

.ifndef OMIT_RetailCall_0809aef8
.global RetailCall_0809aef8
.thumb_set RetailCall_0809aef8, 0x0809aef9
.endif

.ifndef OMIT_RetailCall_0809b120
.global RetailCall_0809b120
.thumb_set RetailCall_0809b120, 0x0809b121
.endif

.ifndef OMIT_RetailCall_0809b218
.global RetailCall_0809b218
.thumb_set RetailCall_0809b218, 0x0809b219
.endif

.ifndef OMIT_RetailCall_0809b470
.global RetailCall_0809b470
.thumb_set RetailCall_0809b470, 0x0809b471
.endif

.ifndef OMIT_RetailCall_0809b6d0
.global RetailCall_0809b6d0
.thumb_set RetailCall_0809b6d0, 0x0809b6d1
.endif

.ifndef OMIT_RetailCall_0809b7c0
.global RetailCall_0809b7c0
.thumb_set RetailCall_0809b7c0, 0x0809b7c1
.endif

.ifndef OMIT_RetailCall_081426b8
.global RetailCall_081426b8
.thumb_set RetailCall_081426b8, 0x081426b9
.endif

.ifndef OMIT_RetailCall_081438bc
.global RetailCall_081438bc
.thumb_set RetailCall_081438bc, 0x081438bd
.endif

.ifndef OMIT_RetailCall_0809b014
.global RetailCall_0809b014
.thumb_set RetailCall_0809b014, 0x0809b015
.endif

.ifndef OMIT_RetailCall_08148a98
.global RetailCall_08148a98
.thumb_set RetailCall_08148a98, 0x08148a99
.endif

.ifndef OMIT_RetailCall_0801cd08
.global RetailCall_0801cd08
.thumb_set RetailCall_0801cd08, 0x0801cd09
.endif

.ifndef OMIT_RetailCall_08099840
.global RetailCall_08099840
.thumb_set RetailCall_08099840, 0x08099841
.endif

.ifndef OMIT_RetailCall_0809c6b8
.global RetailCall_0809c6b8
.thumb_set RetailCall_0809c6b8, 0x0809c6b9
.endif

.ifndef OMIT_RetailCall_0809c8c8
.global RetailCall_0809c8c8
.thumb_set RetailCall_0809c8c8, 0x0809c8c9
.endif

.ifndef OMIT_RetailCall_080cdadc
.global RetailCall_080cdadc
.thumb_set RetailCall_080cdadc, 0x080cdadd
.endif

.ifndef OMIT_RetailCall_080cdb24
.global RetailCall_080cdb24
.thumb_set RetailCall_080cdb24, 0x080cdb25
.endif

.ifndef OMIT_InitializeBattleRouteRecord
.global InitializeBattleRouteRecord
.thumb_set InitializeBattleRouteRecord, 0x809d465
.endif

.ifndef OMIT_ApplyBattleRouteEndpointPolicy
.global ApplyBattleRouteEndpointPolicy
.thumb_set ApplyBattleRouteEndpointPolicy, 0x809b819
.endif

.ifndef OMIT_CheckBattleRouteAdjustment
.global CheckBattleRouteAdjustment
.thumb_set CheckBattleRouteAdjustment, 0x809b015
.endif

.ifndef OMIT_GetBattleRouteAdjustmentFlag
.global GetBattleRouteAdjustmentFlag
.thumb_set GetBattleRouteAdjustmentFlag, 0x809d615
.endif

.ifndef OMIT_QueryBattleRouteNodePending
.global QueryBattleRouteNodePending
.thumb_set QueryBattleRouteNodePending, 0x809d641
.endif

.ifndef OMIT_AccumulateBattleRouteNodePending
.global AccumulateBattleRouteNodePending
.thumb_set AccumulateBattleRouteNodePending, 0x809c9e9
.endif

.ifndef OMIT_CollectBattleTurnUnitPointers_0809F78C
.global CollectBattleTurnUnitPointers_0809F78C
.thumb_set CollectBattleTurnUnitPointers_0809F78C, 0x0809f78d
.endif

.ifndef OMIT_VisitListOwnerWord
.global VisitListOwnerWord
.thumb_set VisitListOwnerWord, 0x0809abe9
.endif

.ifndef OMIT_TurnInitializeOrderMarker
.global TurnInitializeOrderMarker
.thumb_set TurnInitializeOrderMarker, 0x0809ad95
.endif

.ifndef OMIT_ContentAppendCallback
.global ContentAppendCallback
.thumb_set ContentAppendCallback, 0x0809ac21
.endif

/* Existing helper entry interfaces for battle unit continuation. */
.ifndef OMIT_UnitContinuationCall_0809E8F8
.global UnitContinuationCall_0809E8F8
.thumb_set UnitContinuationCall_0809E8F8, 0x0809e8f9
.endif
.ifndef OMIT_UnitContinuationCall_080A7C9C
.global UnitContinuationCall_080A7C9C
.thumb_set UnitContinuationCall_080A7C9C, 0x080a7c9d
.endif
.ifndef OMIT_UnitContinuationCall_080A87B4
.global UnitContinuationCall_080A87B4
.thumb_set UnitContinuationCall_080A87B4, 0x080a87b5
.endif
.ifndef OMIT_UnitContinuationCall_080A87DC
.global UnitContinuationCall_080A87DC
.thumb_set UnitContinuationCall_080A87DC, 0x080a87dd
.endif
.ifndef OMIT_UnitContinuationCall_080A8800
.global UnitContinuationCall_080A8800
.thumb_set UnitContinuationCall_080A8800, 0x080a8801
.endif
.ifndef OMIT_UnitContinuationCall_080A880C
.global UnitContinuationCall_080A880C
.thumb_set UnitContinuationCall_080A880C, 0x080a880d
.endif
.ifndef OMIT_UnitContinuationCall_080A8810
.global UnitContinuationCall_080A8810
.thumb_set UnitContinuationCall_080A8810, 0x080a8811
.endif
.ifndef OMIT_UnitContinuationCall_080A8990
.global UnitContinuationCall_080A8990
.thumb_set UnitContinuationCall_080A8990, 0x080a8991
.endif
.ifndef OMIT_UnitContinuationCall_080A92E4
.global UnitContinuationCall_080A92E4
.thumb_set UnitContinuationCall_080A92E4, 0x080a92e5
.endif
.ifndef OMIT_UnitContinuationCall_080C73C4
.global UnitContinuationCall_080C73C4
.thumb_set UnitContinuationCall_080C73C4, 0x080c73c5
.endif
.ifndef OMIT_UnitContinuationCall_080C73D8
.global UnitContinuationCall_080C73D8
.thumb_set UnitContinuationCall_080C73D8, 0x080c73d9
.endif
.ifndef OMIT_UnitContinuationCall_080C746C
.global UnitContinuationCall_080C746C
.thumb_set UnitContinuationCall_080C746C, 0x080c746d
.endif
.ifndef OMIT_UnitContinuationCall_081303AC
.global UnitContinuationCall_081303AC
.thumb_set UnitContinuationCall_081303AC, 0x081303ad
.endif
.ifndef OMIT_UnitContinuationCall_081303FC
.global UnitContinuationCall_081303FC
.thumb_set UnitContinuationCall_081303FC, 0x081303fd
.endif

/* Direct helper entries used by the A9F24 battle callback reconstruction. */
.ifndef OMIT_RetailCall_080A7EC4
.global RetailCall_080a7ec4
.thumb_set RetailCall_080a7ec4, 0x080a7ec5
.endif
.ifndef OMIT_RetailCall_080A8390
.global RetailCall_080a8390
.thumb_set RetailCall_080a8390, 0x080a8391
.endif
.ifndef OMIT_RetailCall_080A9E6C
.global RetailCall_080a9e6c
.thumb_set RetailCall_080a9e6c, 0x080a9e6d
.endif
.ifndef OMIT_RetailCall_080E2C00
.global RetailCall_080e2c00
.thumb_set RetailCall_080e2c00, 0x080e2c01
.endif
.ifndef OMIT_RetailCall_0809D66C
.global RetailCall_0809d66c
.thumb_set RetailCall_0809d66c, 0x0809d66d
.endif
.ifndef OMIT_RetailCall_080A92E4
.global RetailCall_080a92e4
.thumb_set RetailCall_080a92e4, 0x080a92e5
.endif
.ifndef OMIT_RetailCall_08141570
.global RetailCall_08141570
.thumb_set RetailCall_08141570, 0x08141571
.endif

.ifndef OMIT_RetailCall_0809ccd4
.global RetailCall_0809ccd4
.thumb_set RetailCall_0809ccd4, 0x0809ccd5
.endif

/* Upstream address-only aliases, PR18 ece7856b4816550174d46a7e6e9b246a5a70a54c */
.ifndef OMIT_func_080007C8
.global func_080007C8
.thumb_set func_080007C8, 0x080007c9
.endif
.ifndef OMIT_func_080008E0
.global func_080008E0
.thumb_set func_080008E0, 0x080008e1
.endif
.ifndef OMIT_func_080009AC
.global func_080009AC
.thumb_set func_080009AC, 0x080009ad
.endif
.ifndef OMIT_func_08000A48
.global func_08000A48
.thumb_set func_08000A48, 0x08000a49
.endif
.ifndef OMIT_func_08000A98
.global func_08000A98
.thumb_set func_08000A98, 0x08000a99
.endif
.ifndef OMIT_func_08000ADC
.global func_08000ADC
.thumb_set func_08000ADC, 0x08000add
.endif
.ifndef OMIT_func_08000B20
.global func_08000B20
.thumb_set func_08000B20, 0x08000b21
.endif
.ifndef OMIT_func_08000B68
.global func_08000B68
.thumb_set func_08000B68, 0x08000b69
.endif
.ifndef OMIT_func_08000BAC
.global func_08000BAC
.thumb_set func_08000BAC, 0x08000bad
.endif
.ifndef OMIT_func_08000C08
.global func_08000C08
.thumb_set func_08000C08, 0x08000c09
.endif
.ifndef OMIT_func_08000C64
.global func_08000C64
.thumb_set func_08000C64, 0x08000c65
.endif
.ifndef OMIT_func_08000CB8
.global func_08000CB8
.thumb_set func_08000CB8, 0x08000cb9
.endif
.ifndef OMIT_func_08000D08
.global func_08000D08
.thumb_set func_08000D08, 0x08000d09
.endif
.ifndef OMIT_func_08000D48
.global func_08000D48
.thumb_set func_08000D48, 0x08000d49
.endif
.ifndef OMIT_func_08000D90
.global func_08000D90
.thumb_set func_08000D90, 0x08000d91
.endif
.ifndef OMIT_func_08000E40
.global func_08000E40
.thumb_set func_08000E40, 0x08000e41
.endif
.ifndef OMIT_func_08000EC8
.global func_08000EC8
.thumb_set func_08000EC8, 0x08000ec9
.endif
.ifndef OMIT_func_08000F48
.global func_08000F48
.thumb_set func_08000F48, 0x08000f49
.endif
.ifndef OMIT_func_080014C8
.global func_080014C8
.thumb_set func_080014C8, 0x080014c9
.endif
.ifndef OMIT_func_080016D4
.global func_080016D4
.thumb_set func_080016D4, 0x080016d5
.endif
.ifndef OMIT_func_080018A0
.global func_080018A0
.thumb_set func_080018A0, 0x080018a1
.endif
.ifndef OMIT_func_08001CF0
.global func_08001CF0
.thumb_set func_08001CF0, 0x08001cf1
.endif
.ifndef OMIT_func_08001DAC
.global func_08001DAC
.thumb_set func_08001DAC, 0x08001dad
.endif
.ifndef OMIT_func_08001E18
.global func_08001E18
.thumb_set func_08001E18, 0x08001e19
.endif
.ifndef OMIT_func_08001ED0
.global func_08001ED0
.thumb_set func_08001ED0, 0x08001ed1
.endif
.ifndef OMIT_func_08001F34
.global func_08001F34
.thumb_set func_08001F34, 0x08001f35
.endif
.ifndef OMIT_func_08001FEC
.global func_08001FEC
.thumb_set func_08001FEC, 0x08001fed
.endif
.ifndef OMIT_func_08002050
.global func_08002050
.thumb_set func_08002050, 0x08002051
.endif
.ifndef OMIT_func_08002108
.global func_08002108
.thumb_set func_08002108, 0x08002109
.endif
.ifndef OMIT_func_080023D0
.global func_080023D0
.thumb_set func_080023D0, 0x080023d1
.endif
.ifndef OMIT_func_08002480
.global func_08002480
.thumb_set func_08002480, 0x08002481
.endif
.ifndef OMIT_func_08002524
.global func_08002524
.thumb_set func_08002524, 0x08002525
.endif
.ifndef OMIT_func_08002710
.global func_08002710
.thumb_set func_08002710, 0x08002711
.endif
.ifndef OMIT_func_08002768
.global func_08002768
.thumb_set func_08002768, 0x08002769
.endif
.ifndef OMIT_func_080027B8
.global func_080027B8
.thumb_set func_080027B8, 0x080027b9
.endif
.ifndef OMIT_func_080027E4
.global func_080027E4
.thumb_set func_080027E4, 0x080027e5
.endif
.ifndef OMIT_func_08002800
.global func_08002800
.thumb_set func_08002800, 0x08002801
.endif
.ifndef OMIT_func_08002804
.global func_08002804
.thumb_set func_08002804, 0x08002805
.endif
.ifndef OMIT_func_08002824
.global func_08002824
.thumb_set func_08002824, 0x08002825
.endif
.ifndef OMIT_func_08002830
.global func_08002830
.thumb_set func_08002830, 0x08002831
.endif
.ifndef OMIT_func_080028C8
.global func_080028C8
.thumb_set func_080028C8, 0x080028c9
.endif
.ifndef OMIT_func_080029CC
.global func_080029CC
.thumb_set func_080029CC, 0x080029cd
.endif
.ifndef OMIT_func_08002A08
.global func_08002A08
.thumb_set func_08002A08, 0x08002a09
.endif
.ifndef OMIT_func_08002A3C
.global func_08002A3C
.thumb_set func_08002A3C, 0x08002a3d
.endif
.ifndef OMIT_func_08002A78
.global func_08002A78
.thumb_set func_08002A78, 0x08002a79
.endif
.ifndef OMIT_func_08002A90
.global func_08002A90
.thumb_set func_08002A90, 0x08002a91
.endif
.ifndef OMIT_func_08002AAC
.global func_08002AAC
.thumb_set func_08002AAC, 0x08002aad
.endif
.ifndef OMIT_func_08002AC8
.global func_08002AC8
.thumb_set func_08002AC8, 0x08002ac9
.endif
.ifndef OMIT_func_08002AE4
.global func_08002AE4
.thumb_set func_08002AE4, 0x08002ae5
.endif
.ifndef OMIT_func_08002B28
.global func_08002B28
.thumb_set func_08002B28, 0x08002b29
.endif
.ifndef OMIT_func_08002B4C
.global func_08002B4C
.thumb_set func_08002B4C, 0x08002b4d
.endif
.ifndef OMIT_func_08002B68
.global func_08002B68
.thumb_set func_08002B68, 0x08002b69
.endif
.ifndef OMIT_func_08002B90
.global func_08002B90
.thumb_set func_08002B90, 0x08002b91
.endif
.ifndef OMIT_func_08002BB8
.global func_08002BB8
.thumb_set func_08002BB8, 0x08002bb9
.endif
.ifndef OMIT_func_08002C38
.global func_08002C38
.thumb_set func_08002C38, 0x08002c39
.endif
.ifndef OMIT_func_08002C6C
.global func_08002C6C
.thumb_set func_08002C6C, 0x08002c6d
.endif
.ifndef OMIT_func_08002CB0
.global func_08002CB0
.thumb_set func_08002CB0, 0x08002cb1
.endif
.ifndef OMIT_func_08002D04
.global func_08002D04
.thumb_set func_08002D04, 0x08002d05
.endif
.ifndef OMIT_func_08002D60
.global func_08002D60
.thumb_set func_08002D60, 0x08002d61
.endif
.ifndef OMIT_func_08002DA4
.global func_08002DA4
.thumb_set func_08002DA4, 0x08002da5
.endif
.ifndef OMIT_func_08003088
.global func_08003088
.thumb_set func_08003088, 0x08003089
.endif
.ifndef OMIT_func_080030D8
.global func_080030D8
.thumb_set func_080030D8, 0x080030d9
.endif
.ifndef OMIT_func_0800323C
.global func_0800323C
.thumb_set func_0800323C, 0x0800323d
.endif
.ifndef OMIT_func_08003398
.global func_08003398
.thumb_set func_08003398, 0x08003399
.endif
.ifndef OMIT_func_080033C8
.global func_080033C8
.thumb_set func_080033C8, 0x080033c9
.endif
.ifndef OMIT_func_08003410
.global func_08003410
.thumb_set func_08003410, 0x08003411
.endif
.ifndef OMIT_func_08003508
.global func_08003508
.thumb_set func_08003508, 0x08003509
.endif
.ifndef OMIT_func_08003558
.global func_08003558
.thumb_set func_08003558, 0x08003559
.endif
.ifndef OMIT_func_080035A8
.global func_080035A8
.thumb_set func_080035A8, 0x080035a9
.endif
.ifndef OMIT_func_08003620
.global func_08003620
.thumb_set func_08003620, 0x08003621
.endif
.ifndef OMIT_func_080038C8
.global func_080038C8
.thumb_set func_080038C8, 0x080038c9
.endif
.ifndef OMIT_func_080038E8
.global func_080038E8
.thumb_set func_080038E8, 0x080038e9
.endif
.ifndef OMIT_func_08003900
.global func_08003900
.thumb_set func_08003900, 0x08003901
.endif
.ifndef OMIT_func_08003918
.global func_08003918
.thumb_set func_08003918, 0x08003919
.endif
.ifndef OMIT_func_08003934
.global func_08003934
.thumb_set func_08003934, 0x08003935
.endif
.ifndef OMIT_func_0800395C
.global func_0800395C
.thumb_set func_0800395C, 0x0800395d
.endif
.ifndef OMIT_func_0800397C
.global func_0800397C
.thumb_set func_0800397C, 0x0800397d
.endif
.ifndef OMIT_func_080039E8
.global func_080039E8
.thumb_set func_080039E8, 0x080039e9
.endif
.ifndef OMIT_func_08003A08
.global func_08003A08
.thumb_set func_08003A08, 0x08003a09
.endif
.ifndef OMIT_func_08003A74
.global func_08003A74
.thumb_set func_08003A74, 0x08003a75
.endif
.ifndef OMIT_func_08003A80
.global func_08003A80
.thumb_set func_08003A80, 0x08003a81
.endif
.ifndef OMIT_func_08004C40
.global func_08004C40
.thumb_set func_08004C40, 0x08004c41
.endif
.ifndef OMIT_func_08004CD4
.global func_08004CD4
.thumb_set func_08004CD4, 0x08004cd5
.endif
.ifndef OMIT_func_08004D68
.global func_08004D68
.thumb_set func_08004D68, 0x08004d69
.endif
.ifndef OMIT_func_08004FF4
.global func_08004FF4
.thumb_set func_08004FF4, 0x08004ff5
.endif
.ifndef OMIT_func_08005318
.global func_08005318
.thumb_set func_08005318, 0x08005319
.endif
.ifndef OMIT_func_080053D4
.global func_080053D4
.thumb_set func_080053D4, 0x080053d5
.endif
.ifndef OMIT_func_0800543C
.global func_0800543C
.thumb_set func_0800543C, 0x0800543d
.endif
.ifndef OMIT_func_0800588C
.global func_0800588C
.thumb_set func_0800588C, 0x0800588d
.endif
.ifndef OMIT_func_080058A4
.global func_080058A4
.thumb_set func_080058A4, 0x080058a5
.endif
.ifndef OMIT_func_08005954
.global func_08005954
.thumb_set func_08005954, 0x08005955
.endif
.ifndef OMIT_func_08005A24
.global func_08005A24
.thumb_set func_08005A24, 0x08005a25
.endif
.ifndef OMIT_func_08005B00
.global func_08005B00
.thumb_set func_08005B00, 0x08005b01
.endif
.ifndef OMIT_func_08005B0C
.global func_08005B0C
.thumb_set func_08005B0C, 0x08005b0d
.endif
.ifndef OMIT_func_08005B18
.global func_08005B18
.thumb_set func_08005B18, 0x08005b19
.endif
.ifndef OMIT_func_08005B28
.global func_08005B28
.thumb_set func_08005B28, 0x08005b29
.endif
.ifndef OMIT_func_08005B40
.global func_08005B40
.thumb_set func_08005B40, 0x08005b41
.endif
.ifndef OMIT_func_08005B58
.global func_08005B58
.thumb_set func_08005B58, 0x08005b59
.endif
.ifndef OMIT_func_08005B6C
.global func_08005B6C
.thumb_set func_08005B6C, 0x08005b6d
.endif
.ifndef OMIT_func_08005BA8
.global func_08005BA8
.thumb_set func_08005BA8, 0x08005ba9
.endif
.ifndef OMIT_func_08005BAC
.global func_08005BAC
.thumb_set func_08005BAC, 0x08005bad
.endif
.ifndef OMIT_func_08005BB0
.global func_08005BB0
.thumb_set func_08005BB0, 0x08005bb1
.endif
.ifndef OMIT_func_08005BC4
.global func_08005BC4
.thumb_set func_08005BC4, 0x08005bc5
.endif
.ifndef OMIT_func_08005BF8
.global func_08005BF8
.thumb_set func_08005BF8, 0x08005bf9
.endif
.ifndef OMIT_func_08005BFC
.global func_08005BFC
.thumb_set func_08005BFC, 0x08005bfd
.endif
.ifndef OMIT_func_08005C00
.global func_08005C00
.thumb_set func_08005C00, 0x08005c01
.endif
.ifndef OMIT_func_08005C04
.global func_08005C04
.thumb_set func_08005C04, 0x08005c05
.endif
.ifndef OMIT_func_08005C14
.global func_08005C14
.thumb_set func_08005C14, 0x08005c15
.endif
.ifndef OMIT_func_08005C34
.global func_08005C34
.thumb_set func_08005C34, 0x08005c35
.endif
.ifndef OMIT_func_080068AC
.global func_080068AC
.thumb_set func_080068AC, 0x080068ad
.endif
.ifndef OMIT_func_08006904
.global func_08006904
.thumb_set func_08006904, 0x08006905
.endif
.ifndef OMIT_func_08006940
.global func_08006940
.thumb_set func_08006940, 0x08006941
.endif
.ifndef OMIT_func_08006954
.global func_08006954
.thumb_set func_08006954, 0x08006955
.endif
.ifndef OMIT_func_080069F4
.global func_080069F4
.thumb_set func_080069F4, 0x080069f5
.endif
.ifndef OMIT_func_08006A7C
.global func_08006A7C
.thumb_set func_08006A7C, 0x08006a7d
.endif
.ifndef OMIT_func_08006AB8
.global func_08006AB8
.thumb_set func_08006AB8, 0x08006ab9
.endif
.ifndef OMIT_func_08006ADC
.global func_08006ADC
.thumb_set func_08006ADC, 0x08006add
.endif
.ifndef OMIT_func_08006AF8
.global func_08006AF8
.thumb_set func_08006AF8, 0x08006af9
.endif
.ifndef OMIT_func_08006B14
.global func_08006B14
.thumb_set func_08006B14, 0x08006b15
.endif
.ifndef OMIT_func_08006B5C
.global func_08006B5C
.thumb_set func_08006B5C, 0x08006b5d
.endif
.ifndef OMIT_func_08006B8C
.global func_08006B8C
.thumb_set func_08006B8C, 0x08006b8d
.endif
.ifndef OMIT_func_08006B9C
.global func_08006B9C
.thumb_set func_08006B9C, 0x08006b9d
.endif
.ifndef OMIT_func_08006BB4
.global func_08006BB4
.thumb_set func_08006BB4, 0x08006bb5
.endif
.ifndef OMIT_func_08006BE0
.global func_08006BE0
.thumb_set func_08006BE0, 0x08006be1
.endif
.ifndef OMIT_func_08006C04
.global func_08006C04
.thumb_set func_08006C04, 0x08006c05
.endif
.ifndef OMIT_func_08006C24
.global func_08006C24
.thumb_set func_08006C24, 0x08006c25
.endif
.ifndef OMIT_func_08006C48
.global func_08006C48
.thumb_set func_08006C48, 0x08006c49
.endif
.ifndef OMIT_func_08006C6C
.global func_08006C6C
.thumb_set func_08006C6C, 0x08006c6d
.endif
.ifndef OMIT_func_08006EC0
.global func_08006EC0
.thumb_set func_08006EC0, 0x08006ec1
.endif
.ifndef OMIT_func_08006FCC
.global func_08006FCC
.thumb_set func_08006FCC, 0x08006fcd
.endif
.ifndef OMIT_func_080070C8
.global func_080070C8
.thumb_set func_080070C8, 0x080070c9
.endif
.ifndef OMIT_func_08007138
.global func_08007138
.thumb_set func_08007138, 0x08007139
.endif
.ifndef OMIT_func_08007170
.global func_08007170
.thumb_set func_08007170, 0x08007171
.endif
.ifndef OMIT_func_0800717C
.global func_0800717C
.thumb_set func_0800717C, 0x0800717d
.endif
.ifndef OMIT_func_0800718C
.global func_0800718C
.thumb_set func_0800718C, 0x0800718d
.endif
.ifndef OMIT_func_080071A8
.global func_080071A8
.thumb_set func_080071A8, 0x080071a9
.endif
.ifndef OMIT_func_080071E4
.global func_080071E4
.thumb_set func_080071E4, 0x080071e5
.endif
.ifndef OMIT_func_080071E8
.global func_080071E8
.thumb_set func_080071E8, 0x080071e9
.endif
.ifndef OMIT_func_08007244
.global func_08007244
.thumb_set func_08007244, 0x08007245
.endif
.ifndef OMIT_func_08007258
.global func_08007258
.thumb_set func_08007258, 0x08007259
.endif
.ifndef OMIT_func_08007270
.global func_08007270
.thumb_set func_08007270, 0x08007271
.endif
.ifndef OMIT_func_0800749C
.global func_0800749C
.thumb_set func_0800749C, 0x0800749d
.endif
.ifndef OMIT_func_080075CC
.global func_080075CC
.thumb_set func_080075CC, 0x080075cd
.endif
.ifndef OMIT_func_08007620
.global func_08007620
.thumb_set func_08007620, 0x08007621
.endif
.ifndef OMIT_func_080076A0
.global func_080076A0
.thumb_set func_080076A0, 0x080076a1
.endif
.ifndef OMIT_func_080076F4
.global func_080076F4
.thumb_set func_080076F4, 0x080076f5
.endif
.ifndef OMIT_func_0800777C
.global func_0800777C
.thumb_set func_0800777C, 0x0800777d
.endif
.ifndef OMIT_func_080077E4
.global func_080077E4
.thumb_set func_080077E4, 0x080077e5
.endif
.ifndef OMIT_func_08007880
.global func_08007880
.thumb_set func_08007880, 0x08007881
.endif
.ifndef OMIT_func_08007894
.global func_08007894
.thumb_set func_08007894, 0x08007895
.endif
.ifndef OMIT_func_08007A4C
.global func_08007A4C
.thumb_set func_08007A4C, 0x08007a4d
.endif
.ifndef OMIT_func_08007A60
.global func_08007A60
.thumb_set func_08007A60, 0x08007a61
.endif
.ifndef OMIT_func_08007A74
.global func_08007A74
.thumb_set func_08007A74, 0x08007a75
.endif
.ifndef OMIT_func_08007AD0
.global func_08007AD0
.thumb_set func_08007AD0, 0x08007ad1
.endif
.ifndef OMIT_func_08007B70
.global func_08007B70
.thumb_set func_08007B70, 0x08007b71
.endif
.ifndef OMIT_func_080082EC
.global func_080082EC
.thumb_set func_080082EC, 0x080082ed
.endif
.ifndef OMIT_func_08008818
.global func_08008818
.thumb_set func_08008818, 0x08008819
.endif
.ifndef OMIT_func_08008880
.global func_08008880
.thumb_set func_08008880, 0x08008881
.endif
.ifndef OMIT_func_080088D8
.global func_080088D8
.thumb_set func_080088D8, 0x080088d9
.endif
.ifndef OMIT_func_08008938
.global func_08008938
.thumb_set func_08008938, 0x08008939
.endif
.ifndef OMIT_func_08008954
.global func_08008954
.thumb_set func_08008954, 0x08008955
.endif
.ifndef OMIT_func_08008D50
.global func_08008D50
.thumb_set func_08008D50, 0x08008d51
.endif
.ifndef OMIT_func_08008DFC
.global func_08008DFC
.thumb_set func_08008DFC, 0x08008dfd
.endif
.ifndef OMIT_func_08008E78
.global func_08008E78
.thumb_set func_08008E78, 0x08008e79
.endif
.ifndef OMIT_func_080096B0
.global func_080096B0
.thumb_set func_080096B0, 0x080096b1
.endif
.ifndef OMIT_func_0800975C
.global func_0800975C
.thumb_set func_0800975C, 0x0800975d
.endif
.ifndef OMIT_func_080098C4
.global func_080098C4
.thumb_set func_080098C4, 0x080098c5
.endif
.ifndef OMIT_func_080098F4
.global func_080098F4
.thumb_set func_080098F4, 0x080098f5
.endif
.ifndef OMIT_func_08009964
.global func_08009964
.thumb_set func_08009964, 0x08009965
.endif
.ifndef OMIT_func_08009990
.global func_08009990
.thumb_set func_08009990, 0x08009991
.endif
.ifndef OMIT_func_080099A4
.global func_080099A4
.thumb_set func_080099A4, 0x080099a5
.endif
.ifndef OMIT_func_080099C4
.global func_080099C4
.thumb_set func_080099C4, 0x080099c5
.endif
.ifndef OMIT_func_08009A14
.global func_08009A14
.thumb_set func_08009A14, 0x08009a15
.endif
.ifndef OMIT_func_08009AFC
.global func_08009AFC
.thumb_set func_08009AFC, 0x08009afd
.endif
.ifndef OMIT_func_08009C04
.global func_08009C04
.thumb_set func_08009C04, 0x08009c05
.endif
.ifndef OMIT_func_08009C18
.global func_08009C18
.thumb_set func_08009C18, 0x08009c19
.endif
.ifndef OMIT_func_08009C94
.global func_08009C94
.thumb_set func_08009C94, 0x08009c95
.endif
.ifndef OMIT_func_08009CE0
.global func_08009CE0
.thumb_set func_08009CE0, 0x08009ce1
.endif
.ifndef OMIT_func_08009DD0
.global func_08009DD0
.thumb_set func_08009DD0, 0x08009dd1
.endif
.ifndef OMIT_func_08009E9C
.global func_08009E9C
.thumb_set func_08009E9C, 0x08009e9d
.endif
.ifndef OMIT_func_08009FBC
.global func_08009FBC
.thumb_set func_08009FBC, 0x08009fbd
.endif
.ifndef OMIT_func_08009FD0
.global func_08009FD0
.thumb_set func_08009FD0, 0x08009fd1
.endif
.ifndef OMIT_func_0800A018
.global func_0800A018
.thumb_set func_0800A018, 0x0800a019
.endif
.ifndef OMIT_func_0800A024
.global func_0800A024
.thumb_set func_0800A024, 0x0800a025
.endif
.ifndef OMIT_func_0800A040
.global func_0800A040
.thumb_set func_0800A040, 0x0800a041
.endif
.ifndef OMIT_func_0800A06C
.global func_0800A06C
.thumb_set func_0800A06C, 0x0800a06d
.endif
.ifndef OMIT_func_0800A0B4
.global func_0800A0B4
.thumb_set func_0800A0B4, 0x0800a0b5
.endif
.ifndef OMIT_func_0800A0B8
.global func_0800A0B8
.thumb_set func_0800A0B8, 0x0800a0b9
.endif
.ifndef OMIT_func_0800A1AC
.global func_0800A1AC
.thumb_set func_0800A1AC, 0x0800a1ad
.endif
.ifndef OMIT_func_0800A1BC
.global func_0800A1BC
.thumb_set func_0800A1BC, 0x0800a1bd
.endif
.ifndef OMIT_func_0800A1D0
.global func_0800A1D0
.thumb_set func_0800A1D0, 0x0800a1d1
.endif
.ifndef OMIT_func_0800A1E4
.global func_0800A1E4
.thumb_set func_0800A1E4, 0x0800a1e5
.endif
.ifndef OMIT_func_0800A210
.global func_0800A210
.thumb_set func_0800A210, 0x0800a211
.endif
.ifndef OMIT_func_0800A244
.global func_0800A244
.thumb_set func_0800A244, 0x0800a245
.endif
.ifndef OMIT_func_0800A2F0
.global func_0800A2F0
.thumb_set func_0800A2F0, 0x0800a2f1
.endif
.ifndef OMIT_func_0800A330
.global func_0800A330
.thumb_set func_0800A330, 0x0800a331
.endif
.ifndef OMIT_func_0800A36C
.global func_0800A36C
.thumb_set func_0800A36C, 0x0800a36d
.endif
.ifndef OMIT_func_0800A3E4
.global func_0800A3E4
.thumb_set func_0800A3E4, 0x0800a3e5
.endif
.ifndef OMIT_func_0800A490
.global func_0800A490
.thumb_set func_0800A490, 0x0800a491
.endif
.ifndef OMIT_func_0800A4EC
.global func_0800A4EC
.thumb_set func_0800A4EC, 0x0800a4ed
.endif
.ifndef OMIT_func_0800A4F8
.global func_0800A4F8
.thumb_set func_0800A4F8, 0x0800a4f9
.endif
.ifndef OMIT_func_0800A564
.global func_0800A564
.thumb_set func_0800A564, 0x0800a565
.endif
.ifndef OMIT_func_0800A5A0
.global func_0800A5A0
.thumb_set func_0800A5A0, 0x0800a5a1
.endif
.ifndef OMIT_func_0800A5C8
.global func_0800A5C8
.thumb_set func_0800A5C8, 0x0800a5c9
.endif
.ifndef OMIT_func_0800A5D4
.global func_0800A5D4
.thumb_set func_0800A5D4, 0x0800a5d5
.endif
.ifndef OMIT_func_0800A5EC
.global func_0800A5EC
.thumb_set func_0800A5EC, 0x0800a5ed
.endif
.ifndef OMIT_func_0800A5F8
.global func_0800A5F8
.thumb_set func_0800A5F8, 0x0800a5f9
.endif
.ifndef OMIT_func_0800A61C
.global func_0800A61C
.thumb_set func_0800A61C, 0x0800a61d
.endif
.ifndef OMIT_func_0800A640
.global func_0800A640
.thumb_set func_0800A640, 0x0800a641
.endif
.ifndef OMIT_func_0800A654
.global func_0800A654
.thumb_set func_0800A654, 0x0800a655
.endif
.ifndef OMIT_func_0800A668
.global func_0800A668
.thumb_set func_0800A668, 0x0800a669
.endif
.ifndef OMIT_func_0800A67C
.global func_0800A67C
.thumb_set func_0800A67C, 0x0800a67d
.endif
.ifndef OMIT_func_0800ACA8
.global func_0800ACA8
.thumb_set func_0800ACA8, 0x0800aca9
.endif
.ifndef OMIT_func_0800ADD8
.global func_0800ADD8
.thumb_set func_0800ADD8, 0x0800add9
.endif
.ifndef OMIT_func_0800AEA0
.global func_0800AEA0
.thumb_set func_0800AEA0, 0x0800aea1
.endif
.ifndef OMIT_func_0800AF8C
.global func_0800AF8C
.thumb_set func_0800AF8C, 0x0800af8d
.endif
.ifndef OMIT_func_0800B2A4
.global func_0800B2A4
.thumb_set func_0800B2A4, 0x0800b2a5
.endif
.ifndef OMIT_func_0800B394
.global func_0800B394
.thumb_set func_0800B394, 0x0800b395
.endif
.ifndef OMIT_func_0800B47C
.global func_0800B47C
.thumb_set func_0800B47C, 0x0800b47d
.endif
.ifndef OMIT_func_0800B568
.global func_0800B568
.thumb_set func_0800B568, 0x0800b569
.endif
.ifndef OMIT_func_0800BB74
.global func_0800BB74
.thumb_set func_0800BB74, 0x0800bb75
.endif
.ifndef OMIT_func_0800BBA0
.global func_0800BBA0
.thumb_set func_0800BBA0, 0x0800bba1
.endif
.ifndef OMIT_func_0800BBD4
.global func_0800BBD4
.thumb_set func_0800BBD4, 0x0800bbd5
.endif
.ifndef OMIT_func_0800BC08
.global func_0800BC08
.thumb_set func_0800BC08, 0x0800bc09
.endif
.ifndef OMIT_func_0800BC4C
.global func_0800BC4C
.thumb_set func_0800BC4C, 0x0800bc4d
.endif
.ifndef OMIT_func_0800BC90
.global func_0800BC90
.thumb_set func_0800BC90, 0x0800bc91
.endif
.ifndef OMIT_func_0800BCE0
.global func_0800BCE0
.thumb_set func_0800BCE0, 0x0800bce1
.endif
.ifndef OMIT_func_0800BD24
.global func_0800BD24
.thumb_set func_0800BD24, 0x0800bd25
.endif
.ifndef OMIT_func_0800BD7C
.global func_0800BD7C
.thumb_set func_0800BD7C, 0x0800bd7d
.endif
.ifndef OMIT_func_0800BD90
.global func_0800BD90
.thumb_set func_0800BD90, 0x0800bd91
.endif
.ifndef OMIT_func_0800BDA4
.global func_0800BDA4
.thumb_set func_0800BDA4, 0x0800bda5
.endif
.ifndef OMIT_func_0800BDD0
.global func_0800BDD0
.thumb_set func_0800BDD0, 0x0800bdd1
.endif
.ifndef OMIT_func_0800BDF8
.global func_0800BDF8
.thumb_set func_0800BDF8, 0x0800bdf9
.endif
.ifndef OMIT_func_0800BE10
.global func_0800BE10
.thumb_set func_0800BE10, 0x0800be11
.endif
.ifndef OMIT_func_0800BE78
.global func_0800BE78
.thumb_set func_0800BE78, 0x0800be79
.endif
.ifndef OMIT_func_0800BED8
.global func_0800BED8
.thumb_set func_0800BED8, 0x0800bed9
.endif
.ifndef OMIT_func_0800BEDC
.global func_0800BEDC
.thumb_set func_0800BEDC, 0x0800bedd
.endif
.ifndef OMIT_func_0800BEE0
.global func_0800BEE0
.thumb_set func_0800BEE0, 0x0800bee1
.endif
.ifndef OMIT_func_0800BF04
.global func_0800BF04
.thumb_set func_0800BF04, 0x0800bf05
.endif
.ifndef OMIT_func_0800BF50
.global func_0800BF50
.thumb_set func_0800BF50, 0x0800bf51
.endif
.ifndef OMIT_func_0800BF88
.global func_0800BF88
.thumb_set func_0800BF88, 0x0800bf89
.endif
.ifndef OMIT_func_0800BFC8
.global func_0800BFC8
.thumb_set func_0800BFC8, 0x0800bfc9
.endif
.ifndef OMIT_func_0800C038
.global func_0800C038
.thumb_set func_0800C038, 0x0800c039
.endif
.ifndef OMIT_func_0800C050
.global func_0800C050
.thumb_set func_0800C050, 0x0800c051
.endif
.ifndef OMIT_func_0800C068
.global func_0800C068
.thumb_set func_0800C068, 0x0800c069
.endif
.ifndef OMIT_func_0800C084
.global func_0800C084
.thumb_set func_0800C084, 0x0800c085
.endif
.ifndef OMIT_func_0800C0AC
.global func_0800C0AC
.thumb_set func_0800C0AC, 0x0800c0ad
.endif
.ifndef OMIT_func_0800C148
.global func_0800C148
.thumb_set func_0800C148, 0x0800c149
.endif
.ifndef OMIT_func_0800C15C
.global func_0800C15C
.thumb_set func_0800C15C, 0x0800c15d
.endif
.ifndef OMIT_func_0800C1AC
.global func_0800C1AC
.thumb_set func_0800C1AC, 0x0800c1ad
.endif
.ifndef OMIT_func_0800C1C8
.global func_0800C1C8
.thumb_set func_0800C1C8, 0x0800c1c9
.endif
.ifndef OMIT_func_0800C224
.global func_0800C224
.thumb_set func_0800C224, 0x0800c225
.endif
.ifndef OMIT_func_0800C2C0
.global func_0800C2C0
.thumb_set func_0800C2C0, 0x0800c2c1
.endif
.ifndef OMIT_func_0800C2FC
.global func_0800C2FC
.thumb_set func_0800C2FC, 0x0800c2fd
.endif
.ifndef OMIT_func_0800C34C
.global func_0800C34C
.thumb_set func_0800C34C, 0x0800c34d
.endif
.ifndef OMIT_func_0800C3CC
.global func_0800C3CC
.thumb_set func_0800C3CC, 0x0800c3cd
.endif
.ifndef OMIT_func_0800C4B4
.global func_0800C4B4
.thumb_set func_0800C4B4, 0x0800c4b5
.endif
.ifndef OMIT_func_0800C600
.global func_0800C600
.thumb_set func_0800C600, 0x0800c601
.endif
.ifndef OMIT_func_0800C614
.global func_0800C614
.thumb_set func_0800C614, 0x0800c615
.endif
.ifndef OMIT_func_0800C628
.global func_0800C628
.thumb_set func_0800C628, 0x0800c629
.endif
.ifndef OMIT_func_0800C64C
.global func_0800C64C
.thumb_set func_0800C64C, 0x0800c64d
.endif
.ifndef OMIT_func_0800C668
.global func_0800C668
.thumb_set func_0800C668, 0x0800c669
.endif
.ifndef OMIT_func_0800C6C0
.global func_0800C6C0
.thumb_set func_0800C6C0, 0x0800c6c1
.endif
.ifndef OMIT_func_0800C6CC
.global func_0800C6CC
.thumb_set func_0800C6CC, 0x0800c6cd
.endif
.ifndef OMIT_func_0800C70C
.global func_0800C70C
.thumb_set func_0800C70C, 0x0800c70d
.endif
.ifndef OMIT_func_0800C720
.global func_0800C720
.thumb_set func_0800C720, 0x0800c721
.endif
.ifndef OMIT_func_0800C804
.global func_0800C804
.thumb_set func_0800C804, 0x0800c805
.endif
.ifndef OMIT_func_0800C9E4
.global func_0800C9E4
.thumb_set func_0800C9E4, 0x0800c9e5
.endif
.ifndef OMIT_func_0800CAF0
.global func_0800CAF0
.thumb_set func_0800CAF0, 0x0800caf1
.endif
.ifndef OMIT_func_0800CBFC
.global func_0800CBFC
.thumb_set func_0800CBFC, 0x0800cbfd
.endif
.ifndef OMIT_func_0800D61C
.global func_0800D61C
.thumb_set func_0800D61C, 0x0800d61d
.endif
.ifndef OMIT_func_0800D664
.global func_0800D664
.thumb_set func_0800D664, 0x0800d665
.endif
.ifndef OMIT_func_0800D73C
.global func_0800D73C
.thumb_set func_0800D73C, 0x0800d73d
.endif
.ifndef OMIT_func_0800D884
.global func_0800D884
.thumb_set func_0800D884, 0x0800d885
.endif
.ifndef OMIT_func_0800D8F8
.global func_0800D8F8
.thumb_set func_0800D8F8, 0x0800d8f9
.endif
.ifndef OMIT_func_0800DA48
.global func_0800DA48
.thumb_set func_0800DA48, 0x0800da49
.endif
.ifndef OMIT_func_0800DAB8
.global func_0800DAB8
.thumb_set func_0800DAB8, 0x0800dab9
.endif
.ifndef OMIT_func_0800DB0C
.global func_0800DB0C
.thumb_set func_0800DB0C, 0x0800db0d
.endif
.ifndef OMIT_func_0800DBE8
.global func_0800DBE8
.thumb_set func_0800DBE8, 0x0800dbe9
.endif
.ifndef OMIT_func_0800DC34
.global func_0800DC34
.thumb_set func_0800DC34, 0x0800dc35
.endif
.ifndef OMIT_func_0800DC7C
.global func_0800DC7C
.thumb_set func_0800DC7C, 0x0800dc7d
.endif
.ifndef OMIT_func_0800DCA0
.global func_0800DCA0
.thumb_set func_0800DCA0, 0x0800dca1
.endif
.ifndef OMIT_func_0800DCF0
.global func_0800DCF0
.thumb_set func_0800DCF0, 0x0800dcf1
.endif
.ifndef OMIT_func_0800DD10
.global func_0800DD10
.thumb_set func_0800DD10, 0x0800dd11
.endif
.ifndef OMIT_func_0800DD30
.global func_0800DD30
.thumb_set func_0800DD30, 0x0800dd31
.endif
.ifndef OMIT_func_0800DD5C
.global func_0800DD5C
.thumb_set func_0800DD5C, 0x0800dd5d
.endif
.ifndef OMIT_func_0800DD88
.global func_0800DD88
.thumb_set func_0800DD88, 0x0800dd89
.endif
.ifndef OMIT_func_0800DDBC
.global func_0800DDBC
.thumb_set func_0800DDBC, 0x0800ddbd
.endif
.ifndef OMIT_func_0800DDDC
.global func_0800DDDC
.thumb_set func_0800DDDC, 0x0800dddd
.endif
.ifndef OMIT_func_0800DE20
.global func_0800DE20
.thumb_set func_0800DE20, 0x0800de21
.endif
.ifndef OMIT_func_0800DE40
.global func_0800DE40
.thumb_set func_0800DE40, 0x0800de41
.endif
.ifndef OMIT_func_0800E110
.global func_0800E110
.thumb_set func_0800E110, 0x0800e111
.endif
.ifndef OMIT_func_0800E1A0
.global func_0800E1A0
.thumb_set func_0800E1A0, 0x0800e1a1
.endif
.ifndef OMIT_func_0800E454
.global func_0800E454
.thumb_set func_0800E454, 0x0800e455
.endif
.ifndef OMIT_func_0800E718
.global func_0800E718
.thumb_set func_0800E718, 0x0800e719
.endif
.ifndef OMIT_func_0800F068
.global func_0800F068
.thumb_set func_0800F068, 0x0800f069
.endif
.ifndef OMIT_func_0800F308
.global func_0800F308
.thumb_set func_0800F308, 0x0800f309
.endif
.ifndef OMIT_func_0800F480
.global func_0800F480
.thumb_set func_0800F480, 0x0800f481
.endif
.ifndef OMIT_func_0800F770
.global func_0800F770
.thumb_set func_0800F770, 0x0800f771
.endif
.ifndef OMIT_func_0800F860
.global func_0800F860
.thumb_set func_0800F860, 0x0800f861
.endif
.ifndef OMIT_func_0800F93C
.global func_0800F93C
.thumb_set func_0800F93C, 0x0800f93d
.endif
.ifndef OMIT_func_0800F9C0
.global func_0800F9C0
.thumb_set func_0800F9C0, 0x0800f9c1
.endif
.ifndef OMIT_func_0800FEAC
.global func_0800FEAC
.thumb_set func_0800FEAC, 0x0800fead
.endif
.ifndef OMIT_func_0800FF00
.global func_0800FF00
.thumb_set func_0800FF00, 0x0800ff01
.endif
.ifndef OMIT_func_08010004
.global func_08010004
.thumb_set func_08010004, 0x08010005
.endif
.ifndef OMIT_func_08010058
.global func_08010058
.thumb_set func_08010058, 0x08010059
.endif
.ifndef OMIT_func_080100AC
.global func_080100AC
.thumb_set func_080100AC, 0x080100ad
.endif
.ifndef OMIT_func_0801010C
.global func_0801010C
.thumb_set func_0801010C, 0x0801010d
.endif
.ifndef OMIT_func_080101CC
.global func_080101CC
.thumb_set func_080101CC, 0x080101cd
.endif
.ifndef OMIT_func_08010220
.global func_08010220
.thumb_set func_08010220, 0x08010221
.endif
.ifndef OMIT_func_08010284
.global func_08010284
.thumb_set func_08010284, 0x08010285
.endif
.ifndef OMIT_func_08010358
.global func_08010358
.thumb_set func_08010358, 0x08010359
.endif
.ifndef OMIT_func_0801040C
.global func_0801040C
.thumb_set func_0801040C, 0x0801040d
.endif
.ifndef OMIT_func_080105B8
.global func_080105B8
.thumb_set func_080105B8, 0x080105b9
.endif
.ifndef OMIT_func_080105C4
.global func_080105C4
.thumb_set func_080105C4, 0x080105c5
.endif
.ifndef OMIT_func_0801075C
.global func_0801075C
.thumb_set func_0801075C, 0x0801075d
.endif
.ifndef OMIT_func_080107D4
.global func_080107D4
.thumb_set func_080107D4, 0x080107d5
.endif
.ifndef OMIT_func_08010884
.global func_08010884
.thumb_set func_08010884, 0x08010885
.endif
.ifndef OMIT_func_0801093C
.global func_0801093C
.thumb_set func_0801093C, 0x0801093d
.endif
.ifndef OMIT_func_08010DD0
.global func_08010DD0
.thumb_set func_08010DD0, 0x08010dd1
.endif
.ifndef OMIT_func_08010E64
.global func_08010E64
.thumb_set func_08010E64, 0x08010e65
.endif
.ifndef OMIT_func_08010F30
.global func_08010F30
.thumb_set func_08010F30, 0x08010f31
.endif
.ifndef OMIT_func_08010FD0
.global func_08010FD0
.thumb_set func_08010FD0, 0x08010fd1
.endif
.ifndef OMIT_func_08010FEC
.global func_08010FEC
.thumb_set func_08010FEC, 0x08010fed
.endif
.ifndef OMIT_func_08010FF0
.global func_08010FF0
.thumb_set func_08010FF0, 0x08010ff1
.endif
.ifndef OMIT_func_08011010
.global func_08011010
.thumb_set func_08011010, 0x08011011
.endif
.ifndef OMIT_func_08011014
.global func_08011014
.thumb_set func_08011014, 0x08011015
.endif
.ifndef OMIT_func_08011030
.global func_08011030
.thumb_set func_08011030, 0x08011031
.endif
.ifndef OMIT_func_08011034
.global func_08011034
.thumb_set func_08011034, 0x08011035
.endif
.ifndef OMIT_func_08011040
.global func_08011040
.thumb_set func_08011040, 0x08011041
.endif
.ifndef OMIT_func_08011058
.global func_08011058
.thumb_set func_08011058, 0x08011059
.endif
.ifndef OMIT_func_080110CC
.global func_080110CC
.thumb_set func_080110CC, 0x080110cd
.endif
.ifndef OMIT_func_080110D8
.global func_080110D8
.thumb_set func_080110D8, 0x080110d9
.endif
.ifndef OMIT_func_080110F8
.global func_080110F8
.thumb_set func_080110F8, 0x080110f9
.endif
.ifndef OMIT_func_08011100
.global func_08011100
.thumb_set func_08011100, 0x08011101
.endif
.ifndef OMIT_func_08011118
.global func_08011118
.thumb_set func_08011118, 0x08011119
.endif
.ifndef OMIT_func_08011120
.global func_08011120
.thumb_set func_08011120, 0x08011121
.endif
.ifndef OMIT_func_08011138
.global func_08011138
.thumb_set func_08011138, 0x08011139
.endif
.ifndef OMIT_func_08011140
.global func_08011140
.thumb_set func_08011140, 0x08011141
.endif
.ifndef OMIT_func_08011150
.global func_08011150
.thumb_set func_08011150, 0x08011151
.endif
.ifndef OMIT_func_0801115C
.global func_0801115C
.thumb_set func_0801115C, 0x0801115d
.endif
.ifndef OMIT_func_08011198
.global func_08011198
.thumb_set func_08011198, 0x08011199
.endif
.ifndef OMIT_func_080111A8
.global func_080111A8
.thumb_set func_080111A8, 0x080111a9
.endif
.ifndef OMIT_func_08011204
.global func_08011204
.thumb_set func_08011204, 0x08011205
.endif
.ifndef OMIT_func_0801121C
.global func_0801121C
.thumb_set func_0801121C, 0x0801121d
.endif
.ifndef OMIT_func_08011280
.global func_08011280
.thumb_set func_08011280, 0x08011281
.endif
.ifndef OMIT_func_080112A4
.global func_080112A4
.thumb_set func_080112A4, 0x080112a5
.endif
.ifndef OMIT_func_080112CC
.global func_080112CC
.thumb_set func_080112CC, 0x080112cd
.endif
.ifndef OMIT_func_080112D4
.global func_080112D4
.thumb_set func_080112D4, 0x080112d5
.endif
.ifndef OMIT_func_080112E8
.global func_080112E8
.thumb_set func_080112E8, 0x080112e9
.endif
.ifndef OMIT_func_080112F0
.global func_080112F0
.thumb_set func_080112F0, 0x080112f1
.endif
.ifndef OMIT_func_0801133C
.global func_0801133C
.thumb_set func_0801133C, 0x0801133d
.endif
.ifndef OMIT_func_08011348
.global func_08011348
.thumb_set func_08011348, 0x08011349
.endif
.ifndef OMIT_func_080113B4
.global func_080113B4
.thumb_set func_080113B4, 0x080113b5
.endif
.ifndef OMIT_func_08011428
.global func_08011428
.thumb_set func_08011428, 0x08011429
.endif
.ifndef OMIT_func_08011484
.global func_08011484
.thumb_set func_08011484, 0x08011485
.endif
.ifndef OMIT_func_08011564
.global func_08011564
.thumb_set func_08011564, 0x08011565
.endif
.ifndef OMIT_func_0801159C
.global func_0801159C
.thumb_set func_0801159C, 0x0801159d
.endif
.ifndef OMIT_func_080115D8
.global func_080115D8
.thumb_set func_080115D8, 0x080115d9
.endif
.ifndef OMIT_func_08011614
.global func_08011614
.thumb_set func_08011614, 0x08011615
.endif
.ifndef OMIT_func_08011634
.global func_08011634
.thumb_set func_08011634, 0x08011635
.endif
.ifndef OMIT_func_08011644
.global func_08011644
.thumb_set func_08011644, 0x08011645
.endif
.ifndef OMIT_func_08011710
.global func_08011710
.thumb_set func_08011710, 0x08011711
.endif
.ifndef OMIT_func_0801174C
.global func_0801174C
.thumb_set func_0801174C, 0x0801174d
.endif
.ifndef OMIT_func_08011860
.global func_08011860
.thumb_set func_08011860, 0x08011861
.endif
.ifndef OMIT_func_08011B30
.global func_08011B30
.thumb_set func_08011B30, 0x08011b31
.endif
.ifndef OMIT_func_08011C60
.global func_08011C60
.thumb_set func_08011C60, 0x08011c61
.endif
.ifndef OMIT_func_08011CC4
.global func_08011CC4
.thumb_set func_08011CC4, 0x08011cc5
.endif
.ifndef OMIT_func_08011D9C
.global func_08011D9C
.thumb_set func_08011D9C, 0x08011d9d
.endif
.ifndef OMIT_func_08011EA4
.global func_08011EA4
.thumb_set func_08011EA4, 0x08011ea5
.endif
.ifndef OMIT_func_08011EBC
.global func_08011EBC
.thumb_set func_08011EBC, 0x08011ebd
.endif
.ifndef OMIT_func_08012014
.global func_08012014
.thumb_set func_08012014, 0x08012015
.endif
.ifndef OMIT_func_080120F0
.global func_080120F0
.thumb_set func_080120F0, 0x080120f1
.endif
.ifndef OMIT_func_08012910
.global func_08012910
.thumb_set func_08012910, 0x08012911
.endif
.ifndef OMIT_func_08012950
.global func_08012950
.thumb_set func_08012950, 0x08012951
.endif
.ifndef OMIT_func_08012A98
.global func_08012A98
.thumb_set func_08012A98, 0x08012a99
.endif
.ifndef OMIT_func_08012BEC
.global func_08012BEC
.thumb_set func_08012BEC, 0x08012bed
.endif
.ifndef OMIT_func_08012C30
.global func_08012C30
.thumb_set func_08012C30, 0x08012c31
.endif
.ifndef OMIT_func_08012D3C
.global func_08012D3C
.thumb_set func_08012D3C, 0x08012d3d
.endif
.ifndef OMIT_func_08013060
.global func_08013060
.thumb_set func_08013060, 0x08013061
.endif
.ifndef OMIT_func_08013108
.global func_08013108
.thumb_set func_08013108, 0x08013109
.endif
.ifndef OMIT_func_08013210
.global func_08013210
.thumb_set func_08013210, 0x08013211
.endif
.ifndef OMIT_func_08013364
.global func_08013364
.thumb_set func_08013364, 0x08013365
.endif
.ifndef OMIT_func_08013380
.global func_08013380
.thumb_set func_08013380, 0x08013381
.endif
.ifndef OMIT_func_08013390
.global func_08013390
.thumb_set func_08013390, 0x08013391
.endif
.ifndef OMIT_func_0801339C
.global func_0801339C
.thumb_set func_0801339C, 0x0801339d
.endif
.ifndef OMIT_func_080133B0
.global func_080133B0
.thumb_set func_080133B0, 0x080133b1
.endif
.ifndef OMIT_func_08013404
.global func_08013404
.thumb_set func_08013404, 0x08013405
.endif
.ifndef OMIT_func_08013428
.global func_08013428
.thumb_set func_08013428, 0x08013429
.endif
.ifndef OMIT_func_08013434
.global func_08013434
.thumb_set func_08013434, 0x08013435
.endif
.ifndef OMIT_func_0801344C
.global func_0801344C
.thumb_set func_0801344C, 0x0801344d
.endif
.ifndef OMIT_func_08013528
.global func_08013528
.thumb_set func_08013528, 0x08013529
.endif
.ifndef OMIT_func_08013570
.global func_08013570
.thumb_set func_08013570, 0x08013571
.endif
.ifndef OMIT_func_0801360C
.global func_0801360C
.thumb_set func_0801360C, 0x0801360d
.endif
.ifndef OMIT_func_08013728
.global func_08013728
.thumb_set func_08013728, 0x08013729
.endif
.ifndef OMIT_func_08013794
.global func_08013794
.thumb_set func_08013794, 0x08013795
.endif
.ifndef OMIT_func_080137C0
.global func_080137C0
.thumb_set func_080137C0, 0x080137c1
.endif
.ifndef OMIT_func_08013800
.global func_08013800
.thumb_set func_08013800, 0x08013801
.endif
.ifndef OMIT_func_08013858
.global func_08013858
.thumb_set func_08013858, 0x08013859
.endif
.ifndef OMIT_func_08013890
.global func_08013890
.thumb_set func_08013890, 0x08013891
.endif
.ifndef OMIT_func_08013910
.global func_08013910
.thumb_set func_08013910, 0x08013911
.endif
.ifndef OMIT_func_080139B8
.global func_080139B8
.thumb_set func_080139B8, 0x080139b9
.endif
.ifndef OMIT_func_08013A88
.global func_08013A88
.thumb_set func_08013A88, 0x08013a89
.endif
.ifndef OMIT_func_08013AAC
.global func_08013AAC
.thumb_set func_08013AAC, 0x08013aad
.endif
.ifndef OMIT_func_08013ACC
.global func_08013ACC
.thumb_set func_08013ACC, 0x08013acd
.endif
.ifndef OMIT_func_08013B08
.global func_08013B08
.thumb_set func_08013B08, 0x08013b09
.endif
.ifndef OMIT_func_08013B50
.global func_08013B50
.thumb_set func_08013B50, 0x08013b51
.endif
.ifndef OMIT_func_08013B7C
.global func_08013B7C
.thumb_set func_08013B7C, 0x08013b7d
.endif
.ifndef OMIT_func_08013BC0
.global func_08013BC0
.thumb_set func_08013BC0, 0x08013bc1
.endif
.ifndef OMIT_func_08013BEC
.global func_08013BEC
.thumb_set func_08013BEC, 0x08013bed
.endif
.ifndef OMIT_func_08013C20
.global func_08013C20
.thumb_set func_08013C20, 0x08013c21
.endif
.ifndef OMIT_func_08013E9C
.global func_08013E9C
.thumb_set func_08013E9C, 0x08013e9d
.endif
.ifndef OMIT_func_08013F20
.global func_08013F20
.thumb_set func_08013F20, 0x08013f21
.endif
.ifndef OMIT_func_0801407C
.global func_0801407C
.thumb_set func_0801407C, 0x0801407d
.endif
.ifndef OMIT_func_080142DC
.global func_080142DC
.thumb_set func_080142DC, 0x080142dd
.endif
.ifndef OMIT_func_0801446C
.global func_0801446C
.thumb_set func_0801446C, 0x0801446d
.endif
.ifndef OMIT_func_080144F4
.global func_080144F4
.thumb_set func_080144F4, 0x080144f5
.endif
.ifndef OMIT_func_08014778
.global func_08014778
.thumb_set func_08014778, 0x08014779
.endif
.ifndef OMIT_func_08014B84
.global func_08014B84
.thumb_set func_08014B84, 0x08014b85
.endif
.ifndef OMIT_func_080150D4
.global func_080150D4
.thumb_set func_080150D4, 0x080150d5
.endif
.ifndef OMIT_func_08015110
.global func_08015110
.thumb_set func_08015110, 0x08015111
.endif
.ifndef OMIT_func_0801539C
.global func_0801539C
.thumb_set func_0801539C, 0x0801539d
.endif
.ifndef OMIT_func_080154D8
.global func_080154D8
.thumb_set func_080154D8, 0x080154d9
.endif
.ifndef OMIT_func_080157A8
.global func_080157A8
.thumb_set func_080157A8, 0x080157a9
.endif
.ifndef OMIT_func_08015858
.global func_08015858
.thumb_set func_08015858, 0x08015859
.endif
.ifndef OMIT_func_08015C90
.global func_08015C90
.thumb_set func_08015C90, 0x08015c91
.endif
.ifndef OMIT_func_08015D58
.global func_08015D58
.thumb_set func_08015D58, 0x08015d59
.endif
.ifndef OMIT_func_08015DAC
.global func_08015DAC
.thumb_set func_08015DAC, 0x08015dad
.endif
.ifndef OMIT_func_080161A0
.global func_080161A0
.thumb_set func_080161A0, 0x080161a1
.endif
.ifndef OMIT_func_080161BC
.global func_080161BC
.thumb_set func_080161BC, 0x080161bd
.endif
.ifndef OMIT_func_080161D4
.global func_080161D4
.thumb_set func_080161D4, 0x080161d5
.endif
.ifndef OMIT_func_08016210
.global func_08016210
.thumb_set func_08016210, 0x08016211
.endif
.ifndef OMIT_func_08016234
.global func_08016234
.thumb_set func_08016234, 0x08016235
.endif
.ifndef OMIT_func_0801624C
.global func_0801624C
.thumb_set func_0801624C, 0x0801624d
.endif
.ifndef OMIT_func_08016268
.global func_08016268
.thumb_set func_08016268, 0x08016269
.endif
.ifndef OMIT_func_08016344
.global func_08016344
.thumb_set func_08016344, 0x08016345
.endif
.ifndef OMIT_func_08016560
.global func_08016560
.thumb_set func_08016560, 0x08016561
.endif
.ifndef OMIT_func_080165C4
.global func_080165C4
.thumb_set func_080165C4, 0x080165c5
.endif
.ifndef OMIT_func_08016800
.global func_08016800
.thumb_set func_08016800, 0x08016801
.endif
.ifndef OMIT_func_0801692C
.global func_0801692C
.thumb_set func_0801692C, 0x0801692d
.endif
.ifndef OMIT_func_08016A08
.global func_08016A08
.thumb_set func_08016A08, 0x08016a09
.endif
.ifndef OMIT_func_08016A98
.global func_08016A98
.thumb_set func_08016A98, 0x08016a99
.endif
.ifndef OMIT_func_08016AEC
.global func_08016AEC
.thumb_set func_08016AEC, 0x08016aed
.endif
.ifndef OMIT_func_08016B50
.global func_08016B50
.thumb_set func_08016B50, 0x08016b51
.endif
.ifndef OMIT_func_08016BBC
.global func_08016BBC
.thumb_set func_08016BBC, 0x08016bbd
.endif
.ifndef OMIT_func_08016BD8
.global func_08016BD8
.thumb_set func_08016BD8, 0x08016bd9
.endif
.ifndef OMIT_func_08016C90
.global func_08016C90
.thumb_set func_08016C90, 0x08016c91
.endif
.ifndef OMIT_func_08016D64
.global func_08016D64
.thumb_set func_08016D64, 0x08016d65
.endif
.ifndef OMIT_func_08016E1C
.global func_08016E1C
.thumb_set func_08016E1C, 0x08016e1d
.endif
.ifndef OMIT_func_08016E4C
.global func_08016E4C
.thumb_set func_08016E4C, 0x08016e4d
.endif
.ifndef OMIT_func_08016E88
.global func_08016E88
.thumb_set func_08016E88, 0x08016e89
.endif
.ifndef OMIT_func_08016FE4
.global func_08016FE4
.thumb_set func_08016FE4, 0x08016fe5
.endif
.ifndef OMIT_func_08017180
.global func_08017180
.thumb_set func_08017180, 0x08017181
.endif
.ifndef OMIT_func_080172F0
.global func_080172F0
.thumb_set func_080172F0, 0x080172f1
.endif
.ifndef OMIT_func_08017424
.global func_08017424
.thumb_set func_08017424, 0x08017425
.endif
.ifndef OMIT_func_08017508
.global func_08017508
.thumb_set func_08017508, 0x08017509
.endif
.ifndef OMIT_func_08017514
.global func_08017514
.thumb_set func_08017514, 0x08017515
.endif
.ifndef OMIT_func_08017528
.global func_08017528
.thumb_set func_08017528, 0x08017529
.endif
.ifndef OMIT_func_080175E0
.global func_080175E0
.thumb_set func_080175E0, 0x080175e1
.endif
.ifndef OMIT_func_08017618
.global func_08017618
.thumb_set func_08017618, 0x08017619
.endif
.ifndef OMIT_func_08017734
.global func_08017734
.thumb_set func_08017734, 0x08017735
.endif
.ifndef OMIT_func_0801784C
.global func_0801784C
.thumb_set func_0801784C, 0x0801784d
.endif
.ifndef OMIT_func_08017884
.global func_08017884
.thumb_set func_08017884, 0x08017885
.endif
.ifndef OMIT_func_0801799C
.global func_0801799C
.thumb_set func_0801799C, 0x0801799d
.endif
.ifndef OMIT_func_08017A90
.global func_08017A90
.thumb_set func_08017A90, 0x08017a91
.endif
.ifndef OMIT_func_08017AC4
.global func_08017AC4
.thumb_set func_08017AC4, 0x08017ac5
.endif
.ifndef OMIT_func_08017AD8
.global func_08017AD8
.thumb_set func_08017AD8, 0x08017ad9
.endif
.ifndef OMIT_func_08017AF4
.global func_08017AF4
.thumb_set func_08017AF4, 0x08017af5
.endif
.ifndef OMIT_func_08017B1C
.global func_08017B1C
.thumb_set func_08017B1C, 0x08017b1d
.endif
.ifndef OMIT_func_08017B44
.global func_08017B44
.thumb_set func_08017B44, 0x08017b45
.endif
.ifndef OMIT_func_08017B48
.global func_08017B48
.thumb_set func_08017B48, 0x08017b49
.endif
.ifndef OMIT_func_08017B50
.global func_08017B50
.thumb_set func_08017B50, 0x08017b51
.endif
.ifndef OMIT_func_08017B68
.global func_08017B68
.thumb_set func_08017B68, 0x08017b69
.endif
.ifndef OMIT_func_08017B9C
.global func_08017B9C
.thumb_set func_08017B9C, 0x08017b9d
.endif
.ifndef OMIT_func_08017BE8
.global func_08017BE8
.thumb_set func_08017BE8, 0x08017be9
.endif
.ifndef OMIT_func_08017BF4
.global func_08017BF4
.thumb_set func_08017BF4, 0x08017bf5
.endif
.ifndef OMIT_func_08017C28
.global func_08017C28
.thumb_set func_08017C28, 0x08017c29
.endif
.ifndef OMIT_func_08017C68
.global func_08017C68
.thumb_set func_08017C68, 0x08017c69
.endif
.ifndef OMIT_func_08017D18
.global func_08017D18
.thumb_set func_08017D18, 0x08017d19
.endif
.ifndef OMIT_func_08017DB4
.global func_08017DB4
.thumb_set func_08017DB4, 0x08017db5
.endif
.ifndef OMIT_func_08017E28
.global func_08017E28
.thumb_set func_08017E28, 0x08017e29
.endif
.ifndef OMIT_func_08017E80
.global func_08017E80
.thumb_set func_08017E80, 0x08017e81
.endif
.ifndef OMIT_func_08017F04
.global func_08017F04
.thumb_set func_08017F04, 0x08017f05
.endif
.ifndef OMIT_func_08017FA8
.global func_08017FA8
.thumb_set func_08017FA8, 0x08017fa9
.endif
.ifndef OMIT_func_08017FB0
.global func_08017FB0
.thumb_set func_08017FB0, 0x08017fb1
.endif
.ifndef OMIT_func_08017FBC
.global func_08017FBC
.thumb_set func_08017FBC, 0x08017fbd
.endif
.ifndef OMIT_func_08017FC4
.global func_08017FC4
.thumb_set func_08017FC4, 0x08017fc5
.endif
.ifndef OMIT_func_08017FE8
.global func_08017FE8
.thumb_set func_08017FE8, 0x08017fe9
.endif
.ifndef OMIT_func_0801843C
.global func_0801843C
.thumb_set func_0801843C, 0x0801843d
.endif
.ifndef OMIT_func_08018470
.global func_08018470
.thumb_set func_08018470, 0x08018471
.endif
.ifndef OMIT_func_08018484
.global func_08018484
.thumb_set func_08018484, 0x08018485
.endif
.ifndef OMIT_func_080184D0
.global func_080184D0
.thumb_set func_080184D0, 0x080184d1
.endif
.ifndef OMIT_func_08018518
.global func_08018518
.thumb_set func_08018518, 0x08018519
.endif
.ifndef OMIT_func_08018524
.global func_08018524
.thumb_set func_08018524, 0x08018525
.endif
.ifndef OMIT_func_080185B8
.global func_080185B8
.thumb_set func_080185B8, 0x080185b9
.endif
.ifndef OMIT_func_080185C8
.global func_080185C8
.thumb_set func_080185C8, 0x080185c9
.endif
.ifndef OMIT_func_08018624
.global func_08018624
.thumb_set func_08018624, 0x08018625
.endif
.ifndef OMIT_func_080189A0
.global func_080189A0
.thumb_set func_080189A0, 0x080189a1
.endif
.ifndef OMIT_func_08018A0C
.global func_08018A0C
.thumb_set func_08018A0C, 0x08018a0d
.endif
.ifndef OMIT_func_08018A24
.global func_08018A24
.thumb_set func_08018A24, 0x08018a25
.endif
.ifndef OMIT_func_08018A90
.global func_08018A90
.thumb_set func_08018A90, 0x08018a91
.endif
.ifndef OMIT_func_08018AA8
.global func_08018AA8
.thumb_set func_08018AA8, 0x08018aa9
.endif
.ifndef OMIT_func_08018ABC
.global func_08018ABC
.thumb_set func_08018ABC, 0x08018abd
.endif
.ifndef OMIT_func_08018C24
.global func_08018C24
.thumb_set func_08018C24, 0x08018c25
.endif
.ifndef OMIT_func_08018C94
.global func_08018C94
.thumb_set func_08018C94, 0x08018c95
.endif
.ifndef OMIT_func_08018CB8
.global func_08018CB8
.thumb_set func_08018CB8, 0x08018cb9
.endif
.ifndef OMIT_func_08018CEC
.global func_08018CEC
.thumb_set func_08018CEC, 0x08018ced
.endif
.ifndef OMIT_func_08018D4C
.global func_08018D4C
.thumb_set func_08018D4C, 0x08018d4d
.endif
.ifndef OMIT_func_08018D80
.global func_08018D80
.thumb_set func_08018D80, 0x08018d81
.endif
.ifndef OMIT_func_08018DAC
.global func_08018DAC
.thumb_set func_08018DAC, 0x08018dad
.endif
.ifndef OMIT_func_08018DF0
.global func_08018DF0
.thumb_set func_08018DF0, 0x08018df1
.endif
.ifndef OMIT_func_08018E94
.global func_08018E94
.thumb_set func_08018E94, 0x08018e95
.endif
.ifndef OMIT_func_08018EB4
.global func_08018EB4
.thumb_set func_08018EB4, 0x08018eb5
.endif
.ifndef OMIT_func_08018FF0
.global func_08018FF0
.thumb_set func_08018FF0, 0x08018ff1
.endif
.ifndef OMIT_func_0801904C
.global func_0801904C
.thumb_set func_0801904C, 0x0801904d
.endif
.ifndef OMIT_func_080190A8
.global func_080190A8
.thumb_set func_080190A8, 0x080190a9
.endif
.ifndef OMIT_func_08019120
.global func_08019120
.thumb_set func_08019120, 0x08019121
.endif
.ifndef OMIT_func_080191B0
.global func_080191B0
.thumb_set func_080191B0, 0x080191b1
.endif
.ifndef OMIT_func_0801920C
.global func_0801920C
.thumb_set func_0801920C, 0x0801920d
.endif
.ifndef OMIT_func_08019268
.global func_08019268
.thumb_set func_08019268, 0x08019269
.endif
.ifndef OMIT_func_0801928C
.global func_0801928C
.thumb_set func_0801928C, 0x0801928d
.endif
.ifndef OMIT_func_080192C0
.global func_080192C0
.thumb_set func_080192C0, 0x080192c1
.endif
.ifndef OMIT_func_08019398
.global func_08019398
.thumb_set func_08019398, 0x08019399
.endif
.ifndef OMIT_func_080193CC
.global func_080193CC
.thumb_set func_080193CC, 0x080193cd
.endif
.ifndef OMIT_func_080194A8
.global func_080194A8
.thumb_set func_080194A8, 0x080194a9
.endif
.ifndef OMIT_func_08019574
.global func_08019574
.thumb_set func_08019574, 0x08019575
.endif
.ifndef OMIT_func_08019608
.global func_08019608
.thumb_set func_08019608, 0x08019609
.endif
.ifndef OMIT_func_08019638
.global func_08019638
.thumb_set func_08019638, 0x08019639
.endif
.ifndef OMIT_func_08019680
.global func_08019680
.thumb_set func_08019680, 0x08019681
.endif
.ifndef OMIT_func_080196B0
.global func_080196B0
.thumb_set func_080196B0, 0x080196b1
.endif
.ifndef OMIT_func_080196E0
.global func_080196E0
.thumb_set func_080196E0, 0x080196e1
.endif
.ifndef OMIT_func_08019710
.global func_08019710
.thumb_set func_08019710, 0x08019711
.endif
.ifndef OMIT_func_08019740
.global func_08019740
.thumb_set func_08019740, 0x08019741
.endif
.ifndef OMIT_func_08019758
.global func_08019758
.thumb_set func_08019758, 0x08019759
.endif
.ifndef OMIT_func_080197BC
.global func_080197BC
.thumb_set func_080197BC, 0x080197bd
.endif
.ifndef OMIT_func_08019814
.global func_08019814
.thumb_set func_08019814, 0x08019815
.endif
.ifndef OMIT_func_0801984C
.global func_0801984C
.thumb_set func_0801984C, 0x0801984d
.endif
.ifndef OMIT_func_080199EC
.global func_080199EC
.thumb_set func_080199EC, 0x080199ed
.endif
.ifndef OMIT_func_08019A50
.global func_08019A50
.thumb_set func_08019A50, 0x08019a51
.endif
.ifndef OMIT_func_08019A8C
.global func_08019A8C
.thumb_set func_08019A8C, 0x08019a8d
.endif
.ifndef OMIT_func_08019AE4
.global func_08019AE4
.thumb_set func_08019AE4, 0x08019ae5
.endif
.ifndef OMIT_func_08019B48
.global func_08019B48
.thumb_set func_08019B48, 0x08019b49
.endif
.ifndef OMIT_func_08019C74
.global func_08019C74
.thumb_set func_08019C74, 0x08019c75
.endif
.ifndef OMIT_func_08019D18
.global func_08019D18
.thumb_set func_08019D18, 0x08019d19
.endif
.ifndef OMIT_func_08019E84
.global func_08019E84
.thumb_set func_08019E84, 0x08019e85
.endif
.ifndef OMIT_func_08019FC8
.global func_08019FC8
.thumb_set func_08019FC8, 0x08019fc9
.endif
.ifndef OMIT_func_0801A060
.global func_0801A060
.thumb_set func_0801A060, 0x0801a061
.endif
.ifndef OMIT_func_0801AC78
.global func_0801AC78
.thumb_set func_0801AC78, 0x0801ac79
.endif
.ifndef OMIT_func_0801AD1C
.global func_0801AD1C
.thumb_set func_0801AD1C, 0x0801ad1d
.endif
.ifndef OMIT_func_0801AD38
.global func_0801AD38
.thumb_set func_0801AD38, 0x0801ad39
.endif
.ifndef OMIT_func_0801AD60
.global func_0801AD60
.thumb_set func_0801AD60, 0x0801ad61
.endif
.ifndef OMIT_func_0801ADA4
.global func_0801ADA4
.thumb_set func_0801ADA4, 0x0801ada5
.endif
.ifndef OMIT_func_0801AE00
.global func_0801AE00
.thumb_set func_0801AE00, 0x0801ae01
.endif
.ifndef OMIT_func_0801AE10
.global func_0801AE10
.thumb_set func_0801AE10, 0x0801ae11
.endif
.ifndef OMIT_func_0801AE20
.global func_0801AE20
.thumb_set func_0801AE20, 0x0801ae21
.endif
.ifndef OMIT_func_0801AE9C
.global func_0801AE9C
.thumb_set func_0801AE9C, 0x0801ae9d
.endif
.ifndef OMIT_func_0801AF08
.global func_0801AF08
.thumb_set func_0801AF08, 0x0801af09
.endif
.ifndef OMIT_func_0801B630
.global func_0801B630
.thumb_set func_0801B630, 0x0801b631
.endif
.ifndef OMIT_func_0801B6C8
.global func_0801B6C8
.thumb_set func_0801B6C8, 0x0801b6c9
.endif
.ifndef OMIT_func_0801B798
.global func_0801B798
.thumb_set func_0801B798, 0x0801b799
.endif
.ifndef OMIT_func_0801B7F8
.global func_0801B7F8
.thumb_set func_0801B7F8, 0x0801b7f9
.endif
.ifndef OMIT_func_0801B814
.global func_0801B814
.thumb_set func_0801B814, 0x0801b815
.endif
.ifndef OMIT_func_0801B848
.global func_0801B848
.thumb_set func_0801B848, 0x0801b849
.endif
.ifndef OMIT_func_0801B878
.global func_0801B878
.thumb_set func_0801B878, 0x0801b879
.endif
.ifndef OMIT_func_0801B888
.global func_0801B888
.thumb_set func_0801B888, 0x0801b889
.endif
.ifndef OMIT_func_0801B898
.global func_0801B898
.thumb_set func_0801B898, 0x0801b899
.endif
.ifndef OMIT_func_0801B938
.global func_0801B938
.thumb_set func_0801B938, 0x0801b939
.endif
.ifndef OMIT_func_0801BA20
.global func_0801BA20
.thumb_set func_0801BA20, 0x0801ba21
.endif
.ifndef OMIT_func_0801BB0C
.global func_0801BB0C
.thumb_set func_0801BB0C, 0x0801bb0d
.endif
.ifndef OMIT_func_0801BB94
.global func_0801BB94
.thumb_set func_0801BB94, 0x0801bb95
.endif
.ifndef OMIT_func_0801BC94
.global func_0801BC94
.thumb_set func_0801BC94, 0x0801bc95
.endif
.ifndef OMIT_func_0801BCF8
.global func_0801BCF8
.thumb_set func_0801BCF8, 0x0801bcf9
.endif
.ifndef OMIT_func_0801BD2C
.global func_0801BD2C
.thumb_set func_0801BD2C, 0x0801bd2d
.endif
.ifndef OMIT_func_0801BD68
.global func_0801BD68
.thumb_set func_0801BD68, 0x0801bd69
.endif
.ifndef OMIT_func_0801BDB0
.global func_0801BDB0
.thumb_set func_0801BDB0, 0x0801bdb1
.endif
.ifndef OMIT_func_0801C918
.global func_0801C918
.thumb_set func_0801C918, 0x0801c919
.endif
.ifndef OMIT_func_0801C960
.global func_0801C960
.thumb_set func_0801C960, 0x0801c961
.endif
.ifndef OMIT_func_0801C984
.global func_0801C984
.thumb_set func_0801C984, 0x0801c985
.endif
.ifndef OMIT_func_0801C9F0
.global func_0801C9F0
.thumb_set func_0801C9F0, 0x0801c9f1
.endif
.ifndef OMIT_func_0801CA48
.global func_0801CA48
.thumb_set func_0801CA48, 0x0801ca49
.endif
.ifndef OMIT_func_0801CA78
.global func_0801CA78
.thumb_set func_0801CA78, 0x0801ca79
.endif
.ifndef OMIT_func_0801CAB8
.global func_0801CAB8
.thumb_set func_0801CAB8, 0x0801cab9
.endif
.ifndef OMIT_func_0801CBE8
.global func_0801CBE8
.thumb_set func_0801CBE8, 0x0801cbe9
.endif
.ifndef OMIT_func_0801CBF8
.global func_0801CBF8
.thumb_set func_0801CBF8, 0x0801cbf9
.endif
.ifndef OMIT_func_0801CC18
.global func_0801CC18
.thumb_set func_0801CC18, 0x0801cc19
.endif
.ifndef OMIT_func_0801CC38
.global func_0801CC38
.thumb_set func_0801CC38, 0x0801cc39
.endif
.ifndef OMIT_func_0801CC7C
.global func_0801CC7C
.thumb_set func_0801CC7C, 0x0801cc7d
.endif
.ifndef OMIT_func_0801CD08
.global func_0801CD08
.thumb_set func_0801CD08, 0x0801cd09
.endif
.ifndef OMIT_func_0801CD6C
.global func_0801CD6C
.thumb_set func_0801CD6C, 0x0801cd6d
.endif
.ifndef OMIT_func_0801CD7C
.global func_0801CD7C
.thumb_set func_0801CD7C, 0x0801cd7d
.endif
.ifndef OMIT_func_0801CDA4
.global func_0801CDA4
.thumb_set func_0801CDA4, 0x0801cda5
.endif
.ifndef OMIT_func_0801CE44
.global func_0801CE44
.thumb_set func_0801CE44, 0x0801ce45
.endif
.ifndef OMIT_func_0801CF10
.global func_0801CF10
.thumb_set func_0801CF10, 0x0801cf11
.endif
.ifndef OMIT_func_0801D494
.global func_0801D494
.thumb_set func_0801D494, 0x0801d495
.endif
.ifndef OMIT_func_0801D58C
.global func_0801D58C
.thumb_set func_0801D58C, 0x0801d58d
.endif
.ifndef OMIT_func_0801D818
.global func_0801D818
.thumb_set func_0801D818, 0x0801d819
.endif
.ifndef OMIT_func_0801D880
.global func_0801D880
.thumb_set func_0801D880, 0x0801d881
.endif
.ifndef OMIT_func_0801D890
.global func_0801D890
.thumb_set func_0801D890, 0x0801d891
.endif
.ifndef OMIT_func_0801D8B8
.global func_0801D8B8
.thumb_set func_0801D8B8, 0x0801d8b9
.endif
.ifndef OMIT_func_0801D918
.global func_0801D918
.thumb_set func_0801D918, 0x0801d919
.endif
.ifndef OMIT_func_0801D928
.global func_0801D928
.thumb_set func_0801D928, 0x0801d929
.endif
.ifndef OMIT_func_0801D980
.global func_0801D980
.thumb_set func_0801D980, 0x0801d981
.endif
.ifndef OMIT_func_0801DA10
.global func_0801DA10
.thumb_set func_0801DA10, 0x0801da11
.endif
.ifndef OMIT_func_0801DB2C
.global func_0801DB2C
.thumb_set func_0801DB2C, 0x0801db2d
.endif
.ifndef OMIT_func_0801DB78
.global func_0801DB78
.thumb_set func_0801DB78, 0x0801db79
.endif
.ifndef OMIT_func_0801DC24
.global func_0801DC24
.thumb_set func_0801DC24, 0x0801dc25
.endif
.ifndef OMIT_func_0801DC5C
.global func_0801DC5C
.thumb_set func_0801DC5C, 0x0801dc5d
.endif
.ifndef OMIT_func_0801DC7C
.global func_0801DC7C
.thumb_set func_0801DC7C, 0x0801dc7d
.endif
.ifndef OMIT_func_0801DCB8
.global func_0801DCB8
.thumb_set func_0801DCB8, 0x0801dcb9
.endif
.ifndef OMIT_func_0801DD00
.global func_0801DD00
.thumb_set func_0801DD00, 0x0801dd01
.endif
.ifndef OMIT_func_0801DD34
.global func_0801DD34
.thumb_set func_0801DD34, 0x0801dd35
.endif
.ifndef OMIT_func_0801DD68
.global func_0801DD68
.thumb_set func_0801DD68, 0x0801dd69
.endif
.ifndef OMIT_func_0801DDB4
.global func_0801DDB4
.thumb_set func_0801DDB4, 0x0801ddb5
.endif
.ifndef OMIT_func_0801DE20
.global func_0801DE20
.thumb_set func_0801DE20, 0x0801de21
.endif
.ifndef OMIT_func_0801DF8C
.global func_0801DF8C
.thumb_set func_0801DF8C, 0x0801df8d
.endif
.ifndef OMIT_func_0801DFDC
.global func_0801DFDC
.thumb_set func_0801DFDC, 0x0801dfdd
.endif
.ifndef OMIT_func_0801E038
.global func_0801E038
.thumb_set func_0801E038, 0x0801e039
.endif
.ifndef OMIT_func_0801E0DC
.global func_0801E0DC
.thumb_set func_0801E0DC, 0x0801e0dd
.endif
.ifndef OMIT_func_0801E1B8
.global func_0801E1B8
.thumb_set func_0801E1B8, 0x0801e1b9
.endif
.ifndef OMIT_func_0801E204
.global func_0801E204
.thumb_set func_0801E204, 0x0801e205
.endif
.ifndef OMIT_func_0801E458
.global func_0801E458
.thumb_set func_0801E458, 0x0801e459
.endif
.ifndef OMIT_func_0801E58C
.global func_0801E58C
.thumb_set func_0801E58C, 0x0801e58d
.endif
.ifndef OMIT_func_0801E5E0
.global func_0801E5E0
.thumb_set func_0801E5E0, 0x0801e5e1
.endif
.ifndef OMIT_func_0801E610
.global func_0801E610
.thumb_set func_0801E610, 0x0801e611
.endif
.ifndef OMIT_func_0801E620
.global func_0801E620
.thumb_set func_0801E620, 0x0801e621
.endif
.ifndef OMIT_func_0801E630
.global func_0801E630
.thumb_set func_0801E630, 0x0801e631
.endif
.ifndef OMIT_func_0801E63C
.global func_0801E63C
.thumb_set func_0801E63C, 0x0801e63d
.endif
.ifndef OMIT_func_0801E648
.global func_0801E648
.thumb_set func_0801E648, 0x0801e649
.endif
.ifndef OMIT_func_0801E658
.global func_0801E658
.thumb_set func_0801E658, 0x0801e659
.endif
.ifndef OMIT_func_0801E674
.global func_0801E674
.thumb_set func_0801E674, 0x0801e675
.endif
.ifndef OMIT_func_0801E680
.global func_0801E680
.thumb_set func_0801E680, 0x0801e681
.endif
.ifndef OMIT_func_0801E68C
.global func_0801E68C
.thumb_set func_0801E68C, 0x0801e68d
.endif
.ifndef OMIT_func_0801E6B4
.global func_0801E6B4
.thumb_set func_0801E6B4, 0x0801e6b5
.endif
.ifndef OMIT_func_0801E6F0
.global func_0801E6F0
.thumb_set func_0801E6F0, 0x0801e6f1
.endif
.ifndef OMIT_func_0801E700
.global func_0801E700
.thumb_set func_0801E700, 0x0801e701
.endif
.ifndef OMIT_func_0801E710
.global func_0801E710
.thumb_set func_0801E710, 0x0801e711
.endif
.ifndef OMIT_func_0801E954
.global func_0801E954
.thumb_set func_0801E954, 0x0801e955
.endif
.ifndef OMIT_func_0801EC28
.global func_0801EC28
.thumb_set func_0801EC28, 0x0801ec29
.endif
.ifndef OMIT_func_0801EC78
.global func_0801EC78
.thumb_set func_0801EC78, 0x0801ec79
.endif
.ifndef OMIT_func_0801ED24
.global func_0801ED24
.thumb_set func_0801ED24, 0x0801ed25
.endif
.ifndef OMIT_func_0801EFB0
.global func_0801EFB0
.thumb_set func_0801EFB0, 0x0801efb1
.endif
.ifndef OMIT_func_0801F098
.global func_0801F098
.thumb_set func_0801F098, 0x0801f099
.endif
.ifndef OMIT_func_0801F124
.global func_0801F124
.thumb_set func_0801F124, 0x0801f125
.endif
.ifndef OMIT_func_0801F1A8
.global func_0801F1A8
.thumb_set func_0801F1A8, 0x0801f1a9
.endif
.ifndef OMIT_func_0801F2EC
.global func_0801F2EC
.thumb_set func_0801F2EC, 0x0801f2ed
.endif
.ifndef OMIT_func_0801F438
.global func_0801F438
.thumb_set func_0801F438, 0x0801f439
.endif
.ifndef OMIT_func_0801F548
.global func_0801F548
.thumb_set func_0801F548, 0x0801f549
.endif
.ifndef OMIT_func_0801F62C
.global func_0801F62C
.thumb_set func_0801F62C, 0x0801f62d
.endif
.ifndef OMIT_func_0801F80C
.global func_0801F80C
.thumb_set func_0801F80C, 0x0801f80d
.endif
.ifndef OMIT_func_0801FEB8
.global func_0801FEB8
.thumb_set func_0801FEB8, 0x0801feb9
.endif
.ifndef OMIT_func_08020008
.global func_08020008
.thumb_set func_08020008, 0x08020009
.endif
.ifndef OMIT_func_0802006C
.global func_0802006C
.thumb_set func_0802006C, 0x0802006d
.endif
.ifndef OMIT_func_0802046C
.global func_0802046C
.thumb_set func_0802046C, 0x0802046d
.endif
.ifndef OMIT_func_08020478
.global func_08020478
.thumb_set func_08020478, 0x08020479
.endif
.ifndef OMIT_func_08020484
.global func_08020484
.thumb_set func_08020484, 0x08020485
.endif
.ifndef OMIT_func_08020490
.global func_08020490
.thumb_set func_08020490, 0x08020491
.endif
.ifndef OMIT_func_080204B0
.global func_080204B0
.thumb_set func_080204B0, 0x080204b1
.endif
.ifndef OMIT_func_080204D0
.global func_080204D0
.thumb_set func_080204D0, 0x080204d1
.endif
.ifndef OMIT_func_08020538
.global func_08020538
.thumb_set func_08020538, 0x08020539
.endif
.ifndef OMIT_func_0802058C
.global func_0802058C
.thumb_set func_0802058C, 0x0802058d
.endif
.ifndef OMIT_func_080205C8
.global func_080205C8
.thumb_set func_080205C8, 0x080205c9
.endif
.ifndef OMIT_func_080205F8
.global func_080205F8
.thumb_set func_080205F8, 0x080205f9
.endif
.ifndef OMIT_func_08020618
.global func_08020618
.thumb_set func_08020618, 0x08020619
.endif
.ifndef OMIT_func_08020628
.global func_08020628
.thumb_set func_08020628, 0x08020629
.endif
.ifndef OMIT_func_0802066C
.global func_0802066C
.thumb_set func_0802066C, 0x0802066d
.endif
.ifndef OMIT_func_080206C0
.global func_080206C0
.thumb_set func_080206C0, 0x080206c1
.endif
.ifndef OMIT_func_08020714
.global func_08020714
.thumb_set func_08020714, 0x08020715
.endif
.ifndef OMIT_func_08020734
.global func_08020734
.thumb_set func_08020734, 0x08020735
.endif
.ifndef OMIT_func_08020774
.global func_08020774
.thumb_set func_08020774, 0x08020775
.endif
.ifndef OMIT_func_08020BA0
.global func_08020BA0
.thumb_set func_08020BA0, 0x08020ba1
.endif
.ifndef OMIT_func_08020DA0
.global func_08020DA0
.thumb_set func_08020DA0, 0x08020da1
.endif
.ifndef OMIT_func_08020E3C
.global func_08020E3C
.thumb_set func_08020E3C, 0x08020e3d
.endif
.ifndef OMIT_func_08020F34
.global func_08020F34
.thumb_set func_08020F34, 0x08020f35
.endif
.ifndef OMIT_func_08020F64
.global func_08020F64
.thumb_set func_08020F64, 0x08020f65
.endif
.ifndef OMIT_func_08020F6C
.global func_08020F6C
.thumb_set func_08020F6C, 0x08020f6d
.endif
.ifndef OMIT_func_08020F80
.global func_08020F80
.thumb_set func_08020F80, 0x08020f81
.endif
.ifndef OMIT_func_08020FA4
.global func_08020FA4
.thumb_set func_08020FA4, 0x08020fa5
.endif
.ifndef OMIT_func_08020FC8
.global func_08020FC8
.thumb_set func_08020FC8, 0x08020fc9
.endif
.ifndef OMIT_func_08020FCC
.global func_08020FCC
.thumb_set func_08020FCC, 0x08020fcd
.endif
.ifndef OMIT_func_08020FF0
.global func_08020FF0
.thumb_set func_08020FF0, 0x08020ff1
.endif
.ifndef OMIT_func_08020FF4
.global func_08020FF4
.thumb_set func_08020FF4, 0x08020ff5
.endif
.ifndef OMIT_func_08021004
.global func_08021004
.thumb_set func_08021004, 0x08021005
.endif
.ifndef OMIT_func_08021044
.global func_08021044
.thumb_set func_08021044, 0x08021045
.endif
.ifndef OMIT_func_0802104C
.global func_0802104C
.thumb_set func_0802104C, 0x0802104d
.endif
.ifndef OMIT_func_08021054
.global func_08021054
.thumb_set func_08021054, 0x08021055
.endif
.ifndef OMIT_func_080210E4
.global func_080210E4
.thumb_set func_080210E4, 0x080210e5
.endif
.ifndef OMIT_func_08021290
.global func_08021290
.thumb_set func_08021290, 0x08021291
.endif
.ifndef OMIT_func_080213DC
.global func_080213DC
.thumb_set func_080213DC, 0x080213dd
.endif
.ifndef OMIT_func_08021484
.global func_08021484
.thumb_set func_08021484, 0x08021485
.endif
.ifndef OMIT_func_0802158C
.global func_0802158C
.thumb_set func_0802158C, 0x0802158d
.endif
.ifndef OMIT_func_08021618
.global func_08021618
.thumb_set func_08021618, 0x08021619
.endif
.ifndef OMIT_func_08021A3C
.global func_08021A3C
.thumb_set func_08021A3C, 0x08021a3d
.endif
.ifndef OMIT_func_08021AD0
.global func_08021AD0
.thumb_set func_08021AD0, 0x08021ad1
.endif
.ifndef OMIT_func_08021B1C
.global func_08021B1C
.thumb_set func_08021B1C, 0x08021b1d
.endif
.ifndef OMIT_func_08021B54
.global func_08021B54
.thumb_set func_08021B54, 0x08021b55
.endif
.ifndef OMIT_func_08021B9C
.global func_08021B9C
.thumb_set func_08021B9C, 0x08021b9d
.endif
.ifndef OMIT_func_08021BD4
.global func_08021BD4
.thumb_set func_08021BD4, 0x08021bd5
.endif
.ifndef OMIT_func_08021C08
.global func_08021C08
.thumb_set func_08021C08, 0x08021c09
.endif
.ifndef OMIT_func_08021C2C
.global func_08021C2C
.thumb_set func_08021C2C, 0x08021c2d
.endif
.ifndef OMIT_func_08021C38
.global func_08021C38
.thumb_set func_08021C38, 0x08021c39
.endif
.ifndef OMIT_func_08021C3C
.global func_08021C3C
.thumb_set func_08021C3C, 0x08021c3d
.endif
.ifndef OMIT_func_08021C5C
.global func_08021C5C
.thumb_set func_08021C5C, 0x08021c5d
.endif
.ifndef OMIT_func_08021C84
.global func_08021C84
.thumb_set func_08021C84, 0x08021c85
.endif
.ifndef OMIT_func_08021C8C
.global func_08021C8C
.thumb_set func_08021C8C, 0x08021c8d
.endif
.ifndef OMIT_func_08021C90
.global func_08021C90
.thumb_set func_08021C90, 0x08021c91
.endif
.ifndef OMIT_func_08021CB0
.global func_08021CB0
.thumb_set func_08021CB0, 0x08021cb1
.endif
.ifndef OMIT_func_08021D0C
.global func_08021D0C
.thumb_set func_08021D0C, 0x08021d0d
.endif
.ifndef OMIT_func_08021D14
.global func_08021D14
.thumb_set func_08021D14, 0x08021d15
.endif
.ifndef OMIT_func_08021D40
.global func_08021D40
.thumb_set func_08021D40, 0x08021d41
.endif
.ifndef OMIT_func_08021D98
.global func_08021D98
.thumb_set func_08021D98, 0x08021d99
.endif
.ifndef OMIT_func_08021D9C
.global func_08021D9C
.thumb_set func_08021D9C, 0x08021d9d
.endif
.ifndef OMIT_func_08021DA0
.global func_08021DA0
.thumb_set func_08021DA0, 0x08021da1
.endif
.ifndef OMIT_func_08021DA8
.global func_08021DA8
.thumb_set func_08021DA8, 0x08021da9
.endif
.ifndef OMIT_func_08021DE0
.global func_08021DE0
.thumb_set func_08021DE0, 0x08021de1
.endif
.ifndef OMIT_func_08021DE4
.global func_08021DE4
.thumb_set func_08021DE4, 0x08021de5
.endif
.ifndef OMIT_func_08021DF8
.global func_08021DF8
.thumb_set func_08021DF8, 0x08021df9
.endif
.ifndef OMIT_func_08021E28
.global func_08021E28
.thumb_set func_08021E28, 0x08021e29
.endif
.ifndef OMIT_func_08021E3C
.global func_08021E3C
.thumb_set func_08021E3C, 0x08021e3d
.endif
.ifndef OMIT_func_08021E60
.global func_08021E60
.thumb_set func_08021E60, 0x08021e61
.endif
.ifndef OMIT_func_08021E64
.global func_08021E64
.thumb_set func_08021E64, 0x08021e65
.endif
.ifndef OMIT_func_08021E68
.global func_08021E68
.thumb_set func_08021E68, 0x08021e69
.endif
.ifndef OMIT_func_08021E7C
.global func_08021E7C
.thumb_set func_08021E7C, 0x08021e7d
.endif
.ifndef OMIT_func_08021F18
.global func_08021F18
.thumb_set func_08021F18, 0x08021f19
.endif
.ifndef OMIT_func_0802200C
.global func_0802200C
.thumb_set func_0802200C, 0x0802200d
.endif
.ifndef OMIT_func_0802202C
.global func_0802202C
.thumb_set func_0802202C, 0x0802202d
.endif
.ifndef OMIT_func_08022068
.global func_08022068
.thumb_set func_08022068, 0x08022069
.endif
.ifndef OMIT_func_08022080
.global func_08022080
.thumb_set func_08022080, 0x08022081
.endif
.ifndef OMIT_func_08022094
.global func_08022094
.thumb_set func_08022094, 0x08022095
.endif
.ifndef OMIT_func_080220B4
.global func_080220B4
.thumb_set func_080220B4, 0x080220b5
.endif
.ifndef OMIT_func_080220CC
.global func_080220CC
.thumb_set func_080220CC, 0x080220cd
.endif
.ifndef OMIT_func_080220E8
.global func_080220E8
.thumb_set func_080220E8, 0x080220e9
.endif
.ifndef OMIT_func_08022104
.global func_08022104
.thumb_set func_08022104, 0x08022105
.endif
.ifndef OMIT_func_08022128
.global func_08022128
.thumb_set func_08022128, 0x08022129
.endif
.ifndef OMIT_func_08022148
.global func_08022148
.thumb_set func_08022148, 0x08022149
.endif
.ifndef OMIT_func_08022164
.global func_08022164
.thumb_set func_08022164, 0x08022165
.endif
.ifndef OMIT_func_08022194
.global func_08022194
.thumb_set func_08022194, 0x08022195
.endif
.ifndef OMIT_func_080221BC
.global func_080221BC
.thumb_set func_080221BC, 0x080221bd
.endif
.ifndef OMIT_func_080221E4
.global func_080221E4
.thumb_set func_080221E4, 0x080221e5
.endif
.ifndef OMIT_func_08022238
.global func_08022238
.thumb_set func_08022238, 0x08022239
.endif
.ifndef OMIT_func_08022268
.global func_08022268
.thumb_set func_08022268, 0x08022269
.endif
.ifndef OMIT_func_08022748
.global func_08022748
.thumb_set func_08022748, 0x08022749
.endif
.ifndef OMIT_func_08022770
.global func_08022770
.thumb_set func_08022770, 0x08022771
.endif
.ifndef OMIT_func_08022794
.global func_08022794
.thumb_set func_08022794, 0x08022795
.endif
.ifndef OMIT_func_080227BC
.global func_080227BC
.thumb_set func_080227BC, 0x080227bd
.endif
.ifndef OMIT_func_0802282C
.global func_0802282C
.thumb_set func_0802282C, 0x0802282d
.endif
.ifndef OMIT_func_08022840
.global func_08022840
.thumb_set func_08022840, 0x08022841
.endif
.ifndef OMIT_func_08022854
.global func_08022854
.thumb_set func_08022854, 0x08022855
.endif
.ifndef OMIT_func_08022868
.global func_08022868
.thumb_set func_08022868, 0x08022869
.endif
.ifndef OMIT_func_08022874
.global func_08022874
.thumb_set func_08022874, 0x08022875
.endif
.ifndef OMIT_func_0802292C
.global func_0802292C
.thumb_set func_0802292C, 0x0802292d
.endif
.ifndef OMIT_func_08022A04
.global func_08022A04
.thumb_set func_08022A04, 0x08022a05
.endif
.ifndef OMIT_func_08022A9C
.global func_08022A9C
.thumb_set func_08022A9C, 0x08022a9d
.endif
.ifndef OMIT_func_08022B24
.global func_08022B24
.thumb_set func_08022B24, 0x08022b25
.endif
.ifndef OMIT_func_08022BA4
.global func_08022BA4
.thumb_set func_08022BA4, 0x08022ba5
.endif
.ifndef OMIT_func_08022C2C
.global func_08022C2C
.thumb_set func_08022C2C, 0x08022c2d
.endif
.ifndef OMIT_func_08022C44
.global func_08022C44
.thumb_set func_08022C44, 0x08022c45
.endif
.ifndef OMIT_func_08022C64
.global func_08022C64
.thumb_set func_08022C64, 0x08022c65
.endif
.ifndef OMIT_func_08022CD4
.global func_08022CD4
.thumb_set func_08022CD4, 0x08022cd5
.endif
.ifndef OMIT_func_08022DD0
.global func_08022DD0
.thumb_set func_08022DD0, 0x08022dd1
.endif
.ifndef OMIT_func_08022E24
.global func_08022E24
.thumb_set func_08022E24, 0x08022e25
.endif
.ifndef OMIT_func_08022E90
.global func_08022E90
.thumb_set func_08022E90, 0x08022e91
.endif
.ifndef OMIT_func_0802304C
.global func_0802304C
.thumb_set func_0802304C, 0x0802304d
.endif
.ifndef OMIT_func_080230A8
.global func_080230A8
.thumb_set func_080230A8, 0x080230a9
.endif
.ifndef OMIT_func_080231AC
.global func_080231AC
.thumb_set func_080231AC, 0x080231ad
.endif
.ifndef OMIT_func_080231C0
.global func_080231C0
.thumb_set func_080231C0, 0x080231c1
.endif
.ifndef OMIT_func_080231D8
.global func_080231D8
.thumb_set func_080231D8, 0x080231d9
.endif
.ifndef OMIT_func_080231E8
.global func_080231E8
.thumb_set func_080231E8, 0x080231e9
.endif
.ifndef OMIT_func_080231F4
.global func_080231F4
.thumb_set func_080231F4, 0x080231f5
.endif
.ifndef OMIT_func_0802321C
.global func_0802321C
.thumb_set func_0802321C, 0x0802321d
.endif
.ifndef OMIT_func_0802326C
.global func_0802326C
.thumb_set func_0802326C, 0x0802326d
.endif
.ifndef OMIT_func_080233A0
.global func_080233A0
.thumb_set func_080233A0, 0x080233a1
.endif
.ifndef OMIT_func_08023488
.global func_08023488
.thumb_set func_08023488, 0x08023489
.endif
.ifndef OMIT_func_08023560
.global func_08023560
.thumb_set func_08023560, 0x08023561
.endif
.ifndef OMIT_func_08023988
.global func_08023988
.thumb_set func_08023988, 0x08023989
.endif
.ifndef OMIT_func_08023A40
.global func_08023A40
.thumb_set func_08023A40, 0x08023a41
.endif
.ifndef OMIT_func_08023AA0
.global func_08023AA0
.thumb_set func_08023AA0, 0x08023aa1
.endif
.ifndef OMIT_func_08023AF4
.global func_08023AF4
.thumb_set func_08023AF4, 0x08023af5
.endif
.ifndef OMIT_func_08023E88
.global func_08023E88
.thumb_set func_08023E88, 0x08023e89
.endif
.ifndef OMIT_func_08024108
.global func_08024108
.thumb_set func_08024108, 0x08024109
.endif
.ifndef OMIT_func_080245DC
.global func_080245DC
.thumb_set func_080245DC, 0x080245dd
.endif
.ifndef OMIT_func_080247FC
.global func_080247FC
.thumb_set func_080247FC, 0x080247fd
.endif
.ifndef OMIT_func_08024814
.global func_08024814
.thumb_set func_08024814, 0x08024815
.endif
.ifndef OMIT_func_08024860
.global func_08024860
.thumb_set func_08024860, 0x08024861
.endif
.ifndef OMIT_func_08024ABC
.global func_08024ABC
.thumb_set func_08024ABC, 0x08024abd
.endif
.ifndef OMIT_func_08024AD8
.global func_08024AD8
.thumb_set func_08024AD8, 0x08024ad9
.endif
.ifndef OMIT_func_08025174
.global func_08025174
.thumb_set func_08025174, 0x08025175
.endif
.ifndef OMIT_func_08025324
.global func_08025324
.thumb_set func_08025324, 0x08025325
.endif
.ifndef OMIT_func_08025374
.global func_08025374
.thumb_set func_08025374, 0x08025375
.endif
.ifndef OMIT_func_080253B0
.global func_080253B0
.thumb_set func_080253B0, 0x080253b1
.endif
.ifndef OMIT_func_0802542C
.global func_0802542C
.thumb_set func_0802542C, 0x0802542d
.endif
.ifndef OMIT_func_08025448
.global func_08025448
.thumb_set func_08025448, 0x08025449
.endif
.ifndef OMIT_func_080254A0
.global func_080254A0
.thumb_set func_080254A0, 0x080254a1
.endif
.ifndef OMIT_func_08025560
.global func_08025560
.thumb_set func_08025560, 0x08025561
.endif
.ifndef OMIT_func_08025688
.global func_08025688
.thumb_set func_08025688, 0x08025689
.endif
.ifndef OMIT_func_08025758
.global func_08025758
.thumb_set func_08025758, 0x08025759
.endif
.ifndef OMIT_func_080258C4
.global func_080258C4
.thumb_set func_080258C4, 0x080258c5
.endif
.ifndef OMIT_func_080258F8
.global func_080258F8
.thumb_set func_080258F8, 0x080258f9
.endif
.ifndef OMIT_func_08025A28
.global func_08025A28
.thumb_set func_08025A28, 0x08025a29
.endif
.ifndef OMIT_func_08025B54
.global func_08025B54
.thumb_set func_08025B54, 0x08025b55
.endif
.ifndef OMIT_func_08025D14
.global func_08025D14
.thumb_set func_08025D14, 0x08025d15
.endif
.ifndef OMIT_func_08025D84
.global func_08025D84
.thumb_set func_08025D84, 0x08025d85
.endif
.ifndef OMIT_func_08025DAC
.global func_08025DAC
.thumb_set func_08025DAC, 0x08025dad
.endif
.ifndef OMIT_func_08025DC8
.global func_08025DC8
.thumb_set func_08025DC8, 0x08025dc9
.endif
.ifndef OMIT_func_08025F70
.global func_08025F70
.thumb_set func_08025F70, 0x08025f71
.endif
.ifndef OMIT_func_080267EC
.global func_080267EC
.thumb_set func_080267EC, 0x080267ed
.endif
.ifndef OMIT_func_080269D8
.global func_080269D8
.thumb_set func_080269D8, 0x080269d9
.endif
.ifndef OMIT_func_08026A30
.global func_08026A30
.thumb_set func_08026A30, 0x08026a31
.endif
.ifndef OMIT_func_08026B90
.global func_08026B90
.thumb_set func_08026B90, 0x08026b91
.endif
.ifndef OMIT_func_080273DC
.global func_080273DC
.thumb_set func_080273DC, 0x080273dd
.endif
.ifndef OMIT_func_08027AE8
.global func_08027AE8
.thumb_set func_08027AE8, 0x08027ae9
.endif
.ifndef OMIT_func_08027DA0
.global func_08027DA0
.thumb_set func_08027DA0, 0x08027da1
.endif
.ifndef OMIT_func_0802800C
.global func_0802800C
.thumb_set func_0802800C, 0x0802800d
.endif
.ifndef OMIT_func_080280F4
.global func_080280F4
.thumb_set func_080280F4, 0x080280f5
.endif
.ifndef OMIT_func_080282A4
.global func_080282A4
.thumb_set func_080282A4, 0x080282a5
.endif
.ifndef OMIT_func_080282D4
.global func_080282D4
.thumb_set func_080282D4, 0x080282d5
.endif
.ifndef OMIT_func_08028350
.global func_08028350
.thumb_set func_08028350, 0x08028351
.endif
.ifndef OMIT_func_0802839C
.global func_0802839C
.thumb_set func_0802839C, 0x0802839d
.endif
.ifndef OMIT_func_08028434
.global func_08028434
.thumb_set func_08028434, 0x08028435
.endif
.ifndef OMIT_func_080284A0
.global func_080284A0
.thumb_set func_080284A0, 0x080284a1
.endif
.ifndef OMIT_func_08028584
.global func_08028584
.thumb_set func_08028584, 0x08028585
.endif
.ifndef OMIT_func_08028708
.global func_08028708
.thumb_set func_08028708, 0x08028709
.endif
.ifndef OMIT_func_080287C4
.global func_080287C4
.thumb_set func_080287C4, 0x080287c5
.endif
.ifndef OMIT_func_080287F0
.global func_080287F0
.thumb_set func_080287F0, 0x080287f1
.endif
.ifndef OMIT_func_08028B20
.global func_08028B20
.thumb_set func_08028B20, 0x08028b21
.endif
.ifndef OMIT_func_08028B94
.global func_08028B94
.thumb_set func_08028B94, 0x08028b95
.endif
.ifndef OMIT_func_08028BA8
.global func_08028BA8
.thumb_set func_08028BA8, 0x08028ba9
.endif
.ifndef OMIT_func_08028BBC
.global func_08028BBC
.thumb_set func_08028BBC, 0x08028bbd
.endif
.ifndef OMIT_func_08028BDC
.global func_08028BDC
.thumb_set func_08028BDC, 0x08028bdd
.endif
.ifndef OMIT_func_08028C34
.global func_08028C34
.thumb_set func_08028C34, 0x08028c35
.endif
.ifndef OMIT_func_08028C84
.global func_08028C84
.thumb_set func_08028C84, 0x08028c85
.endif
.ifndef OMIT_func_08028CA4
.global func_08028CA4
.thumb_set func_08028CA4, 0x08028ca5
.endif
.ifndef OMIT_func_08028D88
.global func_08028D88
.thumb_set func_08028D88, 0x08028d89
.endif
.ifndef OMIT_func_08029188
.global func_08029188
.thumb_set func_08029188, 0x08029189
.endif
.ifndef OMIT_func_080292A0
.global func_080292A0
.thumb_set func_080292A0, 0x080292a1
.endif
.ifndef OMIT_func_080292E0
.global func_080292E0
.thumb_set func_080292E0, 0x080292e1
.endif
.ifndef OMIT_func_08029350
.global func_08029350
.thumb_set func_08029350, 0x08029351
.endif
.ifndef OMIT_func_080293DC
.global func_080293DC
.thumb_set func_080293DC, 0x080293dd
.endif
.ifndef OMIT_func_080294FC
.global func_080294FC
.thumb_set func_080294FC, 0x080294fd
.endif
.ifndef OMIT_func_08029528
.global func_08029528
.thumb_set func_08029528, 0x08029529
.endif
.ifndef OMIT_func_08029544
.global func_08029544
.thumb_set func_08029544, 0x08029545
.endif
.ifndef OMIT_func_0802966C
.global func_0802966C
.thumb_set func_0802966C, 0x0802966d
.endif
.ifndef OMIT_func_08029730
.global func_08029730
.thumb_set func_08029730, 0x08029731
.endif
.ifndef OMIT_func_0802979C
.global func_0802979C
.thumb_set func_0802979C, 0x0802979d
.endif
.ifndef OMIT_func_08029D20
.global func_08029D20
.thumb_set func_08029D20, 0x08029d21
.endif
.ifndef OMIT_func_08029D2C
.global func_08029D2C
.thumb_set func_08029D2C, 0x08029d2d
.endif
.ifndef OMIT_func_08029DD4
.global func_08029DD4
.thumb_set func_08029DD4, 0x08029dd5
.endif
.ifndef OMIT_func_08029E48
.global func_08029E48
.thumb_set func_08029E48, 0x08029e49
.endif
.ifndef OMIT_func_08029F18
.global func_08029F18
.thumb_set func_08029F18, 0x08029f19
.endif
.ifndef OMIT_func_0802A1FC
.global func_0802A1FC
.thumb_set func_0802A1FC, 0x0802a1fd
.endif
.ifndef OMIT_func_0802A290
.global func_0802A290
.thumb_set func_0802A290, 0x0802a291
.endif
.ifndef OMIT_func_0802A2C0
.global func_0802A2C0
.thumb_set func_0802A2C0, 0x0802a2c1
.endif
.ifndef OMIT_func_0802A370
.global func_0802A370
.thumb_set func_0802A370, 0x0802a371
.endif
.ifndef OMIT_func_0802A424
.global func_0802A424
.thumb_set func_0802A424, 0x0802a425
.endif
.ifndef OMIT_func_0802AB4C
.global func_0802AB4C
.thumb_set func_0802AB4C, 0x0802ab4d
.endif
.ifndef OMIT_func_0802AB54
.global func_0802AB54
.thumb_set func_0802AB54, 0x0802ab55
.endif
.ifndef OMIT_func_0802AB5C
.global func_0802AB5C
.thumb_set func_0802AB5C, 0x0802ab5d
.endif
.ifndef OMIT_func_0802AB64
.global func_0802AB64
.thumb_set func_0802AB64, 0x0802ab65
.endif
.ifndef OMIT_func_0802AC14
.global func_0802AC14
.thumb_set func_0802AC14, 0x0802ac15
.endif
.ifndef OMIT_func_0802ACA0
.global func_0802ACA0
.thumb_set func_0802ACA0, 0x0802aca1
.endif
.ifndef OMIT_func_0802AD54
.global func_0802AD54
.thumb_set func_0802AD54, 0x0802ad55
.endif
.ifndef OMIT_func_0802B048
.global func_0802B048
.thumb_set func_0802B048, 0x0802b049
.endif
.ifndef OMIT_func_0802B07C
.global func_0802B07C
.thumb_set func_0802B07C, 0x0802b07d
.endif
.ifndef OMIT_func_0802B108
.global func_0802B108
.thumb_set func_0802B108, 0x0802b109
.endif
.ifndef OMIT_func_0802B2A8
.global func_0802B2A8
.thumb_set func_0802B2A8, 0x0802b2a9
.endif
.ifndef OMIT_func_0802B2E8
.global func_0802B2E8
.thumb_set func_0802B2E8, 0x0802b2e9
.endif
.ifndef OMIT_func_0802B368
.global func_0802B368
.thumb_set func_0802B368, 0x0802b369
.endif
.ifndef OMIT_func_0802B3A8
.global func_0802B3A8
.thumb_set func_0802B3A8, 0x0802b3a9
.endif
.ifndef OMIT_func_0802B3D4
.global func_0802B3D4
.thumb_set func_0802B3D4, 0x0802b3d5
.endif
.ifndef OMIT_func_0802B430
.global func_0802B430
.thumb_set func_0802B430, 0x0802b431
.endif
.ifndef OMIT_func_0802B460
.global func_0802B460
.thumb_set func_0802B460, 0x0802b461
.endif
.ifndef OMIT_func_0802B4A8
.global func_0802B4A8
.thumb_set func_0802B4A8, 0x0802b4a9
.endif
.ifndef OMIT_func_0802B53C
.global func_0802B53C
.thumb_set func_0802B53C, 0x0802b53d
.endif
.ifndef OMIT_func_0802B554
.global func_0802B554
.thumb_set func_0802B554, 0x0802b555
.endif
.ifndef OMIT_func_0802B56C
.global func_0802B56C
.thumb_set func_0802B56C, 0x0802b56d
.endif
.ifndef OMIT_func_0802B63C
.global func_0802B63C
.thumb_set func_0802B63C, 0x0802b63d
.endif
.ifndef OMIT_func_0802B6A0
.global func_0802B6A0
.thumb_set func_0802B6A0, 0x0802b6a1
.endif
.ifndef OMIT_func_0802B6F0
.global func_0802B6F0
.thumb_set func_0802B6F0, 0x0802b6f1
.endif
.ifndef OMIT_func_0802B70C
.global func_0802B70C
.thumb_set func_0802B70C, 0x0802b70d
.endif
.ifndef OMIT_func_0802B880
.global func_0802B880
.thumb_set func_0802B880, 0x0802b881
.endif
.ifndef OMIT_func_0802B894
.global func_0802B894
.thumb_set func_0802B894, 0x0802b895
.endif
.ifndef OMIT_func_0802B8CC
.global func_0802B8CC
.thumb_set func_0802B8CC, 0x0802b8cd
.endif
.ifndef OMIT_func_0802B9B4
.global func_0802B9B4
.thumb_set func_0802B9B4, 0x0802b9b5
.endif
.ifndef OMIT_func_0802BA08
.global func_0802BA08
.thumb_set func_0802BA08, 0x0802ba09
.endif
.ifndef OMIT_func_0802C0E0
.global func_0802C0E0
.thumb_set func_0802C0E0, 0x0802c0e1
.endif
.ifndef OMIT_func_0802CEAC
.global func_0802CEAC
.thumb_set func_0802CEAC, 0x0802cead
.endif
.ifndef OMIT_func_0802D014
.global func_0802D014
.thumb_set func_0802D014, 0x0802d015
.endif
.ifndef OMIT_func_0802D05C
.global func_0802D05C
.thumb_set func_0802D05C, 0x0802d05d
.endif
.ifndef OMIT_func_0802D520
.global func_0802D520
.thumb_set func_0802D520, 0x0802d521
.endif
.ifndef OMIT_func_0802D704
.global func_0802D704
.thumb_set func_0802D704, 0x0802d705
.endif
.ifndef OMIT_func_0802D714
.global func_0802D714
.thumb_set func_0802D714, 0x0802d715
.endif
.ifndef OMIT_func_0802D72C
.global func_0802D72C
.thumb_set func_0802D72C, 0x0802d72d
.endif
.ifndef OMIT_func_0802D764
.global func_0802D764
.thumb_set func_0802D764, 0x0802d765
.endif
.ifndef OMIT_func_0802D824
.global func_0802D824
.thumb_set func_0802D824, 0x0802d825
.endif
.ifndef OMIT_func_0802D934
.global func_0802D934
.thumb_set func_0802D934, 0x0802d935
.endif
.ifndef OMIT_func_0802DA00
.global func_0802DA00
.thumb_set func_0802DA00, 0x0802da01
.endif
.ifndef OMIT_func_0802DC60
.global func_0802DC60
.thumb_set func_0802DC60, 0x0802dc61
.endif
.ifndef OMIT_func_0802DD58
.global func_0802DD58
.thumb_set func_0802DD58, 0x0802dd59
.endif
.ifndef OMIT_func_0802DE10
.global func_0802DE10
.thumb_set func_0802DE10, 0x0802de11
.endif
.ifndef OMIT_func_0802DF10
.global func_0802DF10
.thumb_set func_0802DF10, 0x0802df11
.endif
.ifndef OMIT_func_0802DF50
.global func_0802DF50
.thumb_set func_0802DF50, 0x0802df51
.endif
.ifndef OMIT_func_0802DF90
.global func_0802DF90
.thumb_set func_0802DF90, 0x0802df91
.endif
.ifndef OMIT_func_0802DFCC
.global func_0802DFCC
.thumb_set func_0802DFCC, 0x0802dfcd
.endif
.ifndef OMIT_func_0802E070
.global func_0802E070
.thumb_set func_0802E070, 0x0802e071
.endif
.ifndef OMIT_func_0802E08C
.global func_0802E08C
.thumb_set func_0802E08C, 0x0802e08d
.endif
.ifndef OMIT_func_0802E0DC
.global func_0802E0DC
.thumb_set func_0802E0DC, 0x0802e0dd
.endif
.ifndef OMIT_func_0802E338
.global func_0802E338
.thumb_set func_0802E338, 0x0802e339
.endif
.ifndef OMIT_func_0802E520
.global func_0802E520
.thumb_set func_0802E520, 0x0802e521
.endif
.ifndef OMIT_func_0802E890
.global func_0802E890
.thumb_set func_0802E890, 0x0802e891
.endif
.ifndef OMIT_func_0802EAE0
.global func_0802EAE0
.thumb_set func_0802EAE0, 0x0802eae1
.endif
.ifndef OMIT_func_0802EB58
.global func_0802EB58
.thumb_set func_0802EB58, 0x0802eb59
.endif
.ifndef OMIT_func_0802F100
.global func_0802F100
.thumb_set func_0802F100, 0x0802f101
.endif
.ifndef OMIT_func_0802F1D0
.global func_0802F1D0
.thumb_set func_0802F1D0, 0x0802f1d1
.endif
.ifndef OMIT_func_0802F254
.global func_0802F254
.thumb_set func_0802F254, 0x0802f255
.endif
.ifndef OMIT_func_0802F268
.global func_0802F268
.thumb_set func_0802F268, 0x0802f269
.endif
.ifndef OMIT_func_0802FF84
.global func_0802FF84
.thumb_set func_0802FF84, 0x0802ff85
.endif
.ifndef OMIT_func_08030044
.global func_08030044
.thumb_set func_08030044, 0x08030045
.endif
.ifndef OMIT_func_08030168
.global func_08030168
.thumb_set func_08030168, 0x08030169
.endif
.ifndef OMIT_func_08031264
.global func_08031264
.thumb_set func_08031264, 0x08031265
.endif
.ifndef OMIT_func_080312CC
.global func_080312CC
.thumb_set func_080312CC, 0x080312cd
.endif
.ifndef OMIT_func_080312F0
.global func_080312F0
.thumb_set func_080312F0, 0x080312f1
.endif
.ifndef OMIT_func_0803131C
.global func_0803131C
.thumb_set func_0803131C, 0x0803131d
.endif
.ifndef OMIT_func_080314C8
.global func_080314C8
.thumb_set func_080314C8, 0x080314c9
.endif
.ifndef OMIT_func_08031624
.global func_08031624
.thumb_set func_08031624, 0x08031625
.endif
.ifndef OMIT_func_08031708
.global func_08031708
.thumb_set func_08031708, 0x08031709
.endif
.ifndef OMIT_func_08034C94
.global func_08034C94
.thumb_set func_08034C94, 0x08034c95
.endif
.ifndef OMIT_func_08034E34
.global func_08034E34
.thumb_set func_08034E34, 0x08034e35
.endif
.ifndef OMIT_func_080354AC
.global func_080354AC
.thumb_set func_080354AC, 0x080354ad
.endif
.ifndef OMIT_func_08035578
.global func_08035578
.thumb_set func_08035578, 0x08035579
.endif
.ifndef OMIT_func_080355A0
.global func_080355A0
.thumb_set func_080355A0, 0x080355a1
.endif
.ifndef OMIT_func_080355E4
.global func_080355E4
.thumb_set func_080355E4, 0x080355e5
.endif
.ifndef OMIT_func_08035638
.global func_08035638
.thumb_set func_08035638, 0x08035639
.endif
.ifndef OMIT_func_08035678
.global func_08035678
.thumb_set func_08035678, 0x08035679
.endif
.ifndef OMIT_func_080356A0
.global func_080356A0
.thumb_set func_080356A0, 0x080356a1
.endif
.ifndef OMIT_func_08035720
.global func_08035720
.thumb_set func_08035720, 0x08035721
.endif
.ifndef OMIT_func_08035844
.global func_08035844
.thumb_set func_08035844, 0x08035845
.endif
.ifndef OMIT_func_0803591C
.global func_0803591C
.thumb_set func_0803591C, 0x0803591d
.endif
.ifndef OMIT_func_080359E4
.global func_080359E4
.thumb_set func_080359E4, 0x080359e5
.endif
.ifndef OMIT_func_08035A20
.global func_08035A20
.thumb_set func_08035A20, 0x08035a21
.endif
.ifndef OMIT_func_08035A44
.global func_08035A44
.thumb_set func_08035A44, 0x08035a45
.endif
.ifndef OMIT_func_08035BD4
.global func_08035BD4
.thumb_set func_08035BD4, 0x08035bd5
.endif
.ifndef OMIT_func_08035C80
.global func_08035C80
.thumb_set func_08035C80, 0x08035c81
.endif
.ifndef OMIT_func_08035E04
.global func_08035E04
.thumb_set func_08035E04, 0x08035e05
.endif
.ifndef OMIT_func_08035F8C
.global func_08035F8C
.thumb_set func_08035F8C, 0x08035f8d
.endif
.ifndef OMIT_func_08035FC4
.global func_08035FC4
.thumb_set func_08035FC4, 0x08035fc5
.endif
.ifndef OMIT_func_0803600C
.global func_0803600C
.thumb_set func_0803600C, 0x0803600d
.endif
.ifndef OMIT_func_080360F8
.global func_080360F8
.thumb_set func_080360F8, 0x080360f9
.endif
.ifndef OMIT_func_0803616C
.global func_0803616C
.thumb_set func_0803616C, 0x0803616d
.endif
.ifndef OMIT_func_08036284
.global func_08036284
.thumb_set func_08036284, 0x08036285
.endif
.ifndef OMIT_func_080362A4
.global func_080362A4
.thumb_set func_080362A4, 0x080362a5
.endif
.ifndef OMIT_func_080362DC
.global func_080362DC
.thumb_set func_080362DC, 0x080362dd
.endif
.ifndef OMIT_func_08036330
.global func_08036330
.thumb_set func_08036330, 0x08036331
.endif
.ifndef OMIT_func_08036350
.global func_08036350
.thumb_set func_08036350, 0x08036351
.endif
.ifndef OMIT_func_080363C0
.global func_080363C0
.thumb_set func_080363C0, 0x080363c1
.endif
.ifndef OMIT_func_08036424
.global func_08036424
.thumb_set func_08036424, 0x08036425
.endif
.ifndef OMIT_func_08036440
.global func_08036440
.thumb_set func_08036440, 0x08036441
.endif
.ifndef OMIT_func_08036584
.global func_08036584
.thumb_set func_08036584, 0x08036585
.endif
.ifndef OMIT_func_080366BC
.global func_080366BC
.thumb_set func_080366BC, 0x080366bd
.endif
.ifndef OMIT_func_0803687C
.global func_0803687C
.thumb_set func_0803687C, 0x0803687d
.endif
.ifndef OMIT_func_08037428
.global func_08037428
.thumb_set func_08037428, 0x08037429
.endif
.ifndef OMIT_func_080376AC
.global func_080376AC
.thumb_set func_080376AC, 0x080376ad
.endif
.ifndef OMIT_func_080379A8
.global func_080379A8
.thumb_set func_080379A8, 0x080379a9
.endif
.ifndef OMIT_func_08037A30
.global func_08037A30
.thumb_set func_08037A30, 0x08037a31
.endif
.ifndef OMIT_func_08037C84
.global func_08037C84
.thumb_set func_08037C84, 0x08037c85
.endif
.ifndef OMIT_func_08037DF0
.global func_08037DF0
.thumb_set func_08037DF0, 0x08037df1
.endif
.ifndef OMIT_func_08037F0C
.global func_08037F0C
.thumb_set func_08037F0C, 0x08037f0d
.endif
.ifndef OMIT_func_08037F74
.global func_08037F74
.thumb_set func_08037F74, 0x08037f75
.endif
.ifndef OMIT_func_08037FB0
.global func_08037FB0
.thumb_set func_08037FB0, 0x08037fb1
.endif
.ifndef OMIT_func_08037FF0
.global func_08037FF0
.thumb_set func_08037FF0, 0x08037ff1
.endif
.ifndef OMIT_func_08038014
.global func_08038014
.thumb_set func_08038014, 0x08038015
.endif
.ifndef OMIT_func_08038024
.global func_08038024
.thumb_set func_08038024, 0x08038025
.endif
.ifndef OMIT_func_08038028
.global func_08038028
.thumb_set func_08038028, 0x08038029
.endif
.ifndef OMIT_func_08038238
.global func_08038238
.thumb_set func_08038238, 0x08038239
.endif
.ifndef OMIT_func_080384F0
.global func_080384F0
.thumb_set func_080384F0, 0x080384f1
.endif
.ifndef OMIT_func_08038628
.global func_08038628
.thumb_set func_08038628, 0x08038629
.endif
.ifndef OMIT_func_08038694
.global func_08038694
.thumb_set func_08038694, 0x08038695
.endif
.ifndef OMIT_func_08038734
.global func_08038734
.thumb_set func_08038734, 0x08038735
.endif
.ifndef OMIT_func_08038858
.global func_08038858
.thumb_set func_08038858, 0x08038859
.endif
.ifndef OMIT_func_080388C8
.global func_080388C8
.thumb_set func_080388C8, 0x080388c9
.endif
.ifndef OMIT_func_0803890C
.global func_0803890C
.thumb_set func_0803890C, 0x0803890d
.endif
.ifndef OMIT_func_08038B00
.global func_08038B00
.thumb_set func_08038B00, 0x08038b01
.endif
.ifndef OMIT_func_08038B2C
.global func_08038B2C
.thumb_set func_08038B2C, 0x08038b2d
.endif
.ifndef OMIT_func_08038CDC
.global func_08038CDC
.thumb_set func_08038CDC, 0x08038cdd
.endif
.ifndef OMIT_func_08038CF0
.global func_08038CF0
.thumb_set func_08038CF0, 0x08038cf1
.endif
.ifndef OMIT_func_08038D10
.global func_08038D10
.thumb_set func_08038D10, 0x08038d11
.endif
.ifndef OMIT_func_08038D40
.global func_08038D40
.thumb_set func_08038D40, 0x08038d41
.endif
.ifndef OMIT_func_08038D80
.global func_08038D80
.thumb_set func_08038D80, 0x08038d81
.endif
.ifndef OMIT_func_080391C0
.global func_080391C0
.thumb_set func_080391C0, 0x080391c1
.endif
.ifndef OMIT_func_0803938C
.global func_0803938C
.thumb_set func_0803938C, 0x0803938d
.endif
.ifndef OMIT_func_0803A7C0
.global func_0803A7C0
.thumb_set func_0803A7C0, 0x0803a7c1
.endif
.ifndef OMIT_func_0803A7EC
.global func_0803A7EC
.thumb_set func_0803A7EC, 0x0803a7ed
.endif
.ifndef OMIT_func_0803A838
.global func_0803A838
.thumb_set func_0803A838, 0x0803a839
.endif
.ifndef OMIT_func_0803A8C0
.global func_0803A8C0
.thumb_set func_0803A8C0, 0x0803a8c1
.endif
.ifndef OMIT_func_0803A920
.global func_0803A920
.thumb_set func_0803A920, 0x0803a921
.endif
.ifndef OMIT_func_0803CA18
.global func_0803CA18
.thumb_set func_0803CA18, 0x0803ca19
.endif
.ifndef OMIT_func_0803CDAC
.global func_0803CDAC
.thumb_set func_0803CDAC, 0x0803cdad
.endif
.ifndef OMIT_func_0803D320
.global func_0803D320
.thumb_set func_0803D320, 0x0803d321
.endif
.ifndef OMIT_func_0803D3DC
.global func_0803D3DC
.thumb_set func_0803D3DC, 0x0803d3dd
.endif
.ifndef OMIT_func_0803D550
.global func_0803D550
.thumb_set func_0803D550, 0x0803d551
.endif
.ifndef OMIT_func_0803E1C0
.global func_0803E1C0
.thumb_set func_0803E1C0, 0x0803e1c1
.endif
.ifndef OMIT_func_0803E2E0
.global func_0803E2E0
.thumb_set func_0803E2E0, 0x0803e2e1
.endif
.ifndef OMIT_func_0803FB50
.global func_0803FB50
.thumb_set func_0803FB50, 0x0803fb51
.endif
.ifndef OMIT_func_0803FC20
.global func_0803FC20
.thumb_set func_0803FC20, 0x0803fc21
.endif
.ifndef OMIT_func_0803FF9C
.global func_0803FF9C
.thumb_set func_0803FF9C, 0x0803ff9d
.endif
.ifndef OMIT_func_0804018C
.global func_0804018C
.thumb_set func_0804018C, 0x0804018d
.endif
.ifndef OMIT_func_080401F4
.global func_080401F4
.thumb_set func_080401F4, 0x080401f5
.endif
.ifndef OMIT_func_08040264
.global func_08040264
.thumb_set func_08040264, 0x08040265
.endif
.ifndef OMIT_func_08040280
.global func_08040280
.thumb_set func_08040280, 0x08040281
.endif
.ifndef OMIT_func_080406D4
.global func_080406D4
.thumb_set func_080406D4, 0x080406d5
.endif
.ifndef OMIT_func_080407A4
.global func_080407A4
.thumb_set func_080407A4, 0x080407a5
.endif
.ifndef OMIT_func_0804082C
.global func_0804082C
.thumb_set func_0804082C, 0x0804082d
.endif
.ifndef OMIT_func_08040B70
.global func_08040B70
.thumb_set func_08040B70, 0x08040b71
.endif
.ifndef OMIT_func_08040D3C
.global func_08040D3C
.thumb_set func_08040D3C, 0x08040d3d
.endif
.ifndef OMIT_func_08040DA4
.global func_08040DA4
.thumb_set func_08040DA4, 0x08040da5
.endif
.ifndef OMIT_func_08040E14
.global func_08040E14
.thumb_set func_08040E14, 0x08040e15
.endif
.ifndef OMIT_func_08040E30
.global func_08040E30
.thumb_set func_08040E30, 0x08040e31
.endif
.ifndef OMIT_func_08040F38
.global func_08040F38
.thumb_set func_08040F38, 0x08040f39
.endif
.ifndef OMIT_func_080412D0
.global func_080412D0
.thumb_set func_080412D0, 0x080412d1
.endif
.ifndef OMIT_func_080413A0
.global func_080413A0
.thumb_set func_080413A0, 0x080413a1
.endif
.ifndef OMIT_func_08041848
.global func_08041848
.thumb_set func_08041848, 0x08041849
.endif
.ifndef OMIT_func_080418B4
.global func_080418B4
.thumb_set func_080418B4, 0x080418b5
.endif
.ifndef OMIT_func_08041988
.global func_08041988
.thumb_set func_08041988, 0x08041989
.endif
.ifndef OMIT_func_08041ABC
.global func_08041ABC
.thumb_set func_08041ABC, 0x08041abd
.endif
.ifndef OMIT_func_08041BB0
.global func_08041BB0
.thumb_set func_08041BB0, 0x08041bb1
.endif
.ifndef OMIT_func_08041FB4
.global func_08041FB4
.thumb_set func_08041FB4, 0x08041fb5
.endif
.ifndef OMIT_func_08042024
.global func_08042024
.thumb_set func_08042024, 0x08042025
.endif
.ifndef OMIT_func_08042030
.global func_08042030
.thumb_set func_08042030, 0x08042031
.endif
.ifndef OMIT_func_08042148
.global func_08042148
.thumb_set func_08042148, 0x08042149
.endif
.ifndef OMIT_func_080425F8
.global func_080425F8
.thumb_set func_080425F8, 0x080425f9
.endif
.ifndef OMIT_func_080426A4
.global func_080426A4
.thumb_set func_080426A4, 0x080426a5
.endif
.ifndef OMIT_func_08042774
.global func_08042774
.thumb_set func_08042774, 0x08042775
.endif
.ifndef OMIT_func_08042B70
.global func_08042B70
.thumb_set func_08042B70, 0x08042b71
.endif
.ifndef OMIT_func_08042C10
.global func_08042C10
.thumb_set func_08042C10, 0x08042c11
.endif
.ifndef OMIT_func_08042CB4
.global func_08042CB4
.thumb_set func_08042CB4, 0x08042cb5
.endif
.ifndef OMIT_func_08042D4C
.global func_08042D4C
.thumb_set func_08042D4C, 0x08042d4d
.endif
.ifndef OMIT_func_08042E48
.global func_08042E48
.thumb_set func_08042E48, 0x08042e49
.endif
.ifndef OMIT_func_08042EB8
.global func_08042EB8
.thumb_set func_08042EB8, 0x08042eb9
.endif
.ifndef OMIT_func_08042EC4
.global func_08042EC4
.thumb_set func_08042EC4, 0x08042ec5
.endif
.ifndef OMIT_func_08042FDC
.global func_08042FDC
.thumb_set func_08042FDC, 0x08042fdd
.endif
.ifndef OMIT_func_080430CC
.global func_080430CC
.thumb_set func_080430CC, 0x080430cd
.endif
.ifndef OMIT_func_08043120
.global func_08043120
.thumb_set func_08043120, 0x08043121
.endif
.ifndef OMIT_func_08043F90
.global func_08043F90
.thumb_set func_08043F90, 0x08043f91
.endif
.ifndef OMIT_func_08044038
.global func_08044038
.thumb_set func_08044038, 0x08044039
.endif
.ifndef OMIT_func_080445BC
.global func_080445BC
.thumb_set func_080445BC, 0x080445bd
.endif
.ifndef OMIT_func_080445DC
.global func_080445DC
.thumb_set func_080445DC, 0x080445dd
.endif
.ifndef OMIT_func_08044770
.global func_08044770
.thumb_set func_08044770, 0x08044771
.endif
.ifndef OMIT_func_080450DC
.global func_080450DC
.thumb_set func_080450DC, 0x080450dd
.endif
.ifndef OMIT_func_0804516C
.global func_0804516C
.thumb_set func_0804516C, 0x0804516d
.endif
.ifndef OMIT_func_08045390
.global func_08045390
.thumb_set func_08045390, 0x08045391
.endif
.ifndef OMIT_func_08045400
.global func_08045400
.thumb_set func_08045400, 0x08045401
.endif
.ifndef OMIT_func_08045424
.global func_08045424
.thumb_set func_08045424, 0x08045425
.endif
.ifndef OMIT_func_08045CF8
.global func_08045CF8
.thumb_set func_08045CF8, 0x08045cf9
.endif
.ifndef OMIT_func_08045D90
.global func_08045D90
.thumb_set func_08045D90, 0x08045d91
.endif
.ifndef OMIT_func_080469F8
.global func_080469F8
.thumb_set func_080469F8, 0x080469f9
.endif
.ifndef OMIT_func_08049ED0
.global func_08049ED0
.thumb_set func_08049ED0, 0x08049ed1
.endif
.ifndef OMIT_func_0804A2E4
.global func_0804A2E4
.thumb_set func_0804A2E4, 0x0804a2e5
.endif
.ifndef OMIT_func_0804A4CC
.global func_0804A4CC
.thumb_set func_0804A4CC, 0x0804a4cd
.endif
.ifndef OMIT_func_0804AD44
.global func_0804AD44
.thumb_set func_0804AD44, 0x0804ad45
.endif
.ifndef OMIT_func_0804ADC8
.global func_0804ADC8
.thumb_set func_0804ADC8, 0x0804adc9
.endif
.ifndef OMIT_func_0804B7E8
.global func_0804B7E8
.thumb_set func_0804B7E8, 0x0804b7e9
.endif
.ifndef OMIT_func_0804B95C
.global func_0804B95C
.thumb_set func_0804B95C, 0x0804b95d
.endif
.ifndef OMIT_func_0804BB10
.global func_0804BB10
.thumb_set func_0804BB10, 0x0804bb11
.endif
.ifndef OMIT_func_0804BB5C
.global func_0804BB5C
.thumb_set func_0804BB5C, 0x0804bb5d
.endif
.ifndef OMIT_func_0804BDB0
.global func_0804BDB0
.thumb_set func_0804BDB0, 0x0804bdb1
.endif
.ifndef OMIT_func_0804BDC4
.global func_0804BDC4
.thumb_set func_0804BDC4, 0x0804bdc5
.endif
.ifndef OMIT_func_0804BEE8
.global func_0804BEE8
.thumb_set func_0804BEE8, 0x0804bee9
.endif
.ifndef OMIT_func_0804C4D4
.global func_0804C4D4
.thumb_set func_0804C4D4, 0x0804c4d5
.endif
.ifndef OMIT_func_0804C524
.global func_0804C524
.thumb_set func_0804C524, 0x0804c525
.endif
.ifndef OMIT_func_0804C598
.global func_0804C598
.thumb_set func_0804C598, 0x0804c599
.endif
.ifndef OMIT_func_0804C5F8
.global func_0804C5F8
.thumb_set func_0804C5F8, 0x0804c5f9
.endif
.ifndef OMIT_func_0804C668
.global func_0804C668
.thumb_set func_0804C668, 0x0804c669
.endif
.ifndef OMIT_func_0804C6A0
.global func_0804C6A0
.thumb_set func_0804C6A0, 0x0804c6a1
.endif
.ifndef OMIT_func_0804C6E4
.global func_0804C6E4
.thumb_set func_0804C6E4, 0x0804c6e5
.endif
.ifndef OMIT_func_0804C740
.global func_0804C740
.thumb_set func_0804C740, 0x0804c741
.endif
.ifndef OMIT_func_0804C788
.global func_0804C788
.thumb_set func_0804C788, 0x0804c789
.endif
.ifndef OMIT_func_0804C7A0
.global func_0804C7A0
.thumb_set func_0804C7A0, 0x0804c7a1
.endif
.ifndef OMIT_func_0804C7C8
.global func_0804C7C8
.thumb_set func_0804C7C8, 0x0804c7c9
.endif
.ifndef OMIT_func_0804C7EC
.global func_0804C7EC
.thumb_set func_0804C7EC, 0x0804c7ed
.endif
.ifndef OMIT_func_0804C834
.global func_0804C834
.thumb_set func_0804C834, 0x0804c835
.endif
.ifndef OMIT_func_0804C858
.global func_0804C858
.thumb_set func_0804C858, 0x0804c859
.endif
.ifndef OMIT_func_0804C888
.global func_0804C888
.thumb_set func_0804C888, 0x0804c889
.endif
.ifndef OMIT_func_0804C8C4
.global func_0804C8C4
.thumb_set func_0804C8C4, 0x0804c8c5
.endif
.ifndef OMIT_func_0804C97C
.global func_0804C97C
.thumb_set func_0804C97C, 0x0804c97d
.endif
.ifndef OMIT_func_0804C9E4
.global func_0804C9E4
.thumb_set func_0804C9E4, 0x0804c9e5
.endif
.ifndef OMIT_func_0804CA00
.global func_0804CA00
.thumb_set func_0804CA00, 0x0804ca01
.endif
.ifndef OMIT_func_0804CA44
.global func_0804CA44
.thumb_set func_0804CA44, 0x0804ca45
.endif
.ifndef OMIT_func_0804CA58
.global func_0804CA58
.thumb_set func_0804CA58, 0x0804ca59
.endif
.ifndef OMIT_func_0804CA6C
.global func_0804CA6C
.thumb_set func_0804CA6C, 0x0804ca6d
.endif
.ifndef OMIT_func_0804CA80
.global func_0804CA80
.thumb_set func_0804CA80, 0x0804ca81
.endif
.ifndef OMIT_func_0804CA8C
.global func_0804CA8C
.thumb_set func_0804CA8C, 0x0804ca8d
.endif
.ifndef OMIT_func_0804CAB0
.global func_0804CAB0
.thumb_set func_0804CAB0, 0x0804cab1
.endif
.ifndef OMIT_func_0804CABC
.global func_0804CABC
.thumb_set func_0804CABC, 0x0804cabd
.endif
.ifndef OMIT_func_0804CAD0
.global func_0804CAD0
.thumb_set func_0804CAD0, 0x0804cad1
.endif
.ifndef OMIT_func_0804D5AC
.global func_0804D5AC
.thumb_set func_0804D5AC, 0x0804d5ad
.endif
.ifndef OMIT_func_0804D5F4
.global func_0804D5F4
.thumb_set func_0804D5F4, 0x0804d5f5
.endif
.ifndef OMIT_func_0804D658
.global func_0804D658
.thumb_set func_0804D658, 0x0804d659
.endif
.ifndef OMIT_func_0804D7E8
.global func_0804D7E8
.thumb_set func_0804D7E8, 0x0804d7e9
.endif
.ifndef OMIT_func_0804D814
.global func_0804D814
.thumb_set func_0804D814, 0x0804d815
.endif
.ifndef OMIT_func_0804D840
.global func_0804D840
.thumb_set func_0804D840, 0x0804d841
.endif
.ifndef OMIT_func_0804D91C
.global func_0804D91C
.thumb_set func_0804D91C, 0x0804d91d
.endif
.ifndef OMIT_func_0804E014
.global func_0804E014
.thumb_set func_0804E014, 0x0804e015
.endif
.ifndef OMIT_func_0804E05C
.global func_0804E05C
.thumb_set func_0804E05C, 0x0804e05d
.endif
.ifndef OMIT_func_0804E1B8
.global func_0804E1B8
.thumb_set func_0804E1B8, 0x0804e1b9
.endif
.ifndef OMIT_func_0804E1E0
.global func_0804E1E0
.thumb_set func_0804E1E0, 0x0804e1e1
.endif
.ifndef OMIT_func_0804E1F0
.global func_0804E1F0
.thumb_set func_0804E1F0, 0x0804e1f1
.endif
.ifndef OMIT_func_0804E358
.global func_0804E358
.thumb_set func_0804E358, 0x0804e359
.endif
.ifndef OMIT_func_0804E3BC
.global func_0804E3BC
.thumb_set func_0804E3BC, 0x0804e3bd
.endif
.ifndef OMIT_func_0804E408
.global func_0804E408
.thumb_set func_0804E408, 0x0804e409
.endif
.ifndef OMIT_func_0804E5CC
.global func_0804E5CC
.thumb_set func_0804E5CC, 0x0804e5cd
.endif
.ifndef OMIT_func_0804E858
.global func_0804E858
.thumb_set func_0804E858, 0x0804e859
.endif
.ifndef OMIT_func_0804E9A0
.global func_0804E9A0
.thumb_set func_0804E9A0, 0x0804e9a1
.endif
.ifndef OMIT_func_0804E9B0
.global func_0804E9B0
.thumb_set func_0804E9B0, 0x0804e9b1
.endif
.ifndef OMIT_func_0804E9D0
.global func_0804E9D0
.thumb_set func_0804E9D0, 0x0804e9d1
.endif
.ifndef OMIT_func_0804E9DC
.global func_0804E9DC
.thumb_set func_0804E9DC, 0x0804e9dd
.endif
.ifndef OMIT_func_0804EC74
.global func_0804EC74
.thumb_set func_0804EC74, 0x0804ec75
.endif
.ifndef OMIT_func_0804ED44
.global func_0804ED44
.thumb_set func_0804ED44, 0x0804ed45
.endif
.ifndef OMIT_func_0804ED6C
.global func_0804ED6C
.thumb_set func_0804ED6C, 0x0804ed6d
.endif
.ifndef OMIT_func_0804EF68
.global func_0804EF68
.thumb_set func_0804EF68, 0x0804ef69
.endif
.ifndef OMIT_func_0804EF90
.global func_0804EF90
.thumb_set func_0804EF90, 0x0804ef91
.endif
.ifndef OMIT_func_0804EFD0
.global func_0804EFD0
.thumb_set func_0804EFD0, 0x0804efd1
.endif
.ifndef OMIT_func_0804F060
.global func_0804F060
.thumb_set func_0804F060, 0x0804f061
.endif
.ifndef OMIT_func_0804F0F4
.global func_0804F0F4
.thumb_set func_0804F0F4, 0x0804f0f5
.endif
.ifndef OMIT_func_0804F14C
.global func_0804F14C
.thumb_set func_0804F14C, 0x0804f14d
.endif
.ifndef OMIT_func_0804F28C
.global func_0804F28C
.thumb_set func_0804F28C, 0x0804f28d
.endif
.ifndef OMIT_func_0804F370
.global func_0804F370
.thumb_set func_0804F370, 0x0804f371
.endif
.ifndef OMIT_func_0804F3B4
.global func_0804F3B4
.thumb_set func_0804F3B4, 0x0804f3b5
.endif
.ifndef OMIT_func_0804F470
.global func_0804F470
.thumb_set func_0804F470, 0x0804f471
.endif
.ifndef OMIT_func_0804F4D4
.global func_0804F4D4
.thumb_set func_0804F4D4, 0x0804f4d5
.endif
.ifndef OMIT_func_0804F5BC
.global func_0804F5BC
.thumb_set func_0804F5BC, 0x0804f5bd
.endif
.ifndef OMIT_func_0804F744
.global func_0804F744
.thumb_set func_0804F744, 0x0804f745
.endif
.ifndef OMIT_func_0804F8A4
.global func_0804F8A4
.thumb_set func_0804F8A4, 0x0804f8a5
.endif
.ifndef OMIT_func_0804F938
.global func_0804F938
.thumb_set func_0804F938, 0x0804f939
.endif
.ifndef OMIT_func_0804F948
.global func_0804F948
.thumb_set func_0804F948, 0x0804f949
.endif
.ifndef OMIT_func_0804FBB0
.global func_0804FBB0
.thumb_set func_0804FBB0, 0x0804fbb1
.endif
.ifndef OMIT_func_0804FDF4
.global func_0804FDF4
.thumb_set func_0804FDF4, 0x0804fdf5
.endif
.ifndef OMIT_func_0804FF48
.global func_0804FF48
.thumb_set func_0804FF48, 0x0804ff49
.endif
.ifndef OMIT_func_0804FFB8
.global func_0804FFB8
.thumb_set func_0804FFB8, 0x0804ffb9
.endif
.ifndef OMIT_func_0805005C
.global func_0805005C
.thumb_set func_0805005C, 0x0805005d
.endif
.ifndef OMIT_func_080500B0
.global func_080500B0
.thumb_set func_080500B0, 0x080500b1
.endif
.ifndef OMIT_func_080501CC
.global func_080501CC
.thumb_set func_080501CC, 0x080501cd
.endif
.ifndef OMIT_func_080502EC
.global func_080502EC
.thumb_set func_080502EC, 0x080502ed
.endif
.ifndef OMIT_func_0805033C
.global func_0805033C
.thumb_set func_0805033C, 0x0805033d
.endif
.ifndef OMIT_func_08050394
.global func_08050394
.thumb_set func_08050394, 0x08050395
.endif
.ifndef OMIT_func_080504BC
.global func_080504BC
.thumb_set func_080504BC, 0x080504bd
.endif
.ifndef OMIT_func_080505BC
.global func_080505BC
.thumb_set func_080505BC, 0x080505bd
.endif
.ifndef OMIT_func_0805064C
.global func_0805064C
.thumb_set func_0805064C, 0x0805064d
.endif
.ifndef OMIT_func_08050734
.global func_08050734
.thumb_set func_08050734, 0x08050735
.endif
.ifndef OMIT_func_08050844
.global func_08050844
.thumb_set func_08050844, 0x08050845
.endif
.ifndef OMIT_func_0805093C
.global func_0805093C
.thumb_set func_0805093C, 0x0805093d
.endif
.ifndef OMIT_func_08050A8C
.global func_08050A8C
.thumb_set func_08050A8C, 0x08050a8d
.endif
.ifndef OMIT_func_08050AF4
.global func_08050AF4
.thumb_set func_08050AF4, 0x08050af5
.endif
.ifndef OMIT_func_08050B9C
.global func_08050B9C
.thumb_set func_08050B9C, 0x08050b9d
.endif
.ifndef OMIT_func_08050BF0
.global func_08050BF0
.thumb_set func_08050BF0, 0x08050bf1
.endif
.ifndef OMIT_func_08050C74
.global func_08050C74
.thumb_set func_08050C74, 0x08050c75
.endif
.ifndef OMIT_func_08050CA4
.global func_08050CA4
.thumb_set func_08050CA4, 0x08050ca5
.endif
.ifndef OMIT_func_08050CDC
.global func_08050CDC
.thumb_set func_08050CDC, 0x08050cdd
.endif
.ifndef OMIT_func_08050CE8
.global func_08050CE8
.thumb_set func_08050CE8, 0x08050ce9
.endif
.ifndef OMIT_func_08050D50
.global func_08050D50
.thumb_set func_08050D50, 0x08050d51
.endif
.ifndef OMIT_func_08050DA0
.global func_08050DA0
.thumb_set func_08050DA0, 0x08050da1
.endif
.ifndef OMIT_func_08050DE8
.global func_08050DE8
.thumb_set func_08050DE8, 0x08050de9
.endif
.ifndef OMIT_func_08050E14
.global func_08050E14
.thumb_set func_08050E14, 0x08050e15
.endif
.ifndef OMIT_func_08050E1C
.global func_08050E1C
.thumb_set func_08050E1C, 0x08050e1d
.endif
.ifndef OMIT_func_08050E28
.global func_08050E28
.thumb_set func_08050E28, 0x08050e29
.endif
.ifndef OMIT_func_08050E34
.global func_08050E34
.thumb_set func_08050E34, 0x08050e35
.endif
.ifndef OMIT_func_08050E54
.global func_08050E54
.thumb_set func_08050E54, 0x08050e55
.endif
.ifndef OMIT_func_08050E74
.global func_08050E74
.thumb_set func_08050E74, 0x08050e75
.endif
.ifndef OMIT_func_08050E84
.global func_08050E84
.thumb_set func_08050E84, 0x08050e85
.endif
.ifndef OMIT_func_08050E94
.global func_08050E94
.thumb_set func_08050E94, 0x08050e95
.endif
.ifndef OMIT_func_08050EFC
.global func_08050EFC
.thumb_set func_08050EFC, 0x08050efd
.endif
.ifndef OMIT_func_08050F1C
.global func_08050F1C
.thumb_set func_08050F1C, 0x08050f1d
.endif
.ifndef OMIT_func_080510B0
.global func_080510B0
.thumb_set func_080510B0, 0x080510b1
.endif
.ifndef OMIT_func_080524C0
.global func_080524C0
.thumb_set func_080524C0, 0x080524c1
.endif
.ifndef OMIT_func_080524E8
.global func_080524E8
.thumb_set func_080524E8, 0x080524e9
.endif
.ifndef OMIT_func_08052790
.global func_08052790
.thumb_set func_08052790, 0x08052791
.endif
.ifndef OMIT_func_08052800
.global func_08052800
.thumb_set func_08052800, 0x08052801
.endif
.ifndef OMIT_func_080531F0
.global func_080531F0
.thumb_set func_080531F0, 0x080531f1
.endif
.ifndef OMIT_func_080534F4
.global func_080534F4
.thumb_set func_080534F4, 0x080534f5
.endif
.ifndef OMIT_func_08053568
.global func_08053568
.thumb_set func_08053568, 0x08053569
.endif
.ifndef OMIT_func_080535BC
.global func_080535BC
.thumb_set func_080535BC, 0x080535bd
.endif
.ifndef OMIT_func_080535E8
.global func_080535E8
.thumb_set func_080535E8, 0x080535e9
.endif
.ifndef OMIT_func_08053674
.global func_08053674
.thumb_set func_08053674, 0x08053675
.endif
.ifndef OMIT_func_080539B4
.global func_080539B4
.thumb_set func_080539B4, 0x080539b5
.endif
.ifndef OMIT_func_08053B34
.global func_08053B34
.thumb_set func_08053B34, 0x08053b35
.endif
.ifndef OMIT_func_08053C74
.global func_08053C74
.thumb_set func_08053C74, 0x08053c75
.endif
.ifndef OMIT_func_08053E4C
.global func_08053E4C
.thumb_set func_08053E4C, 0x08053e4d
.endif
.ifndef OMIT_func_08053F08
.global func_08053F08
.thumb_set func_08053F08, 0x08053f09
.endif
.ifndef OMIT_func_08053FE0
.global func_08053FE0
.thumb_set func_08053FE0, 0x08053fe1
.endif
.ifndef OMIT_func_0805417C
.global func_0805417C
.thumb_set func_0805417C, 0x0805417d
.endif
.ifndef OMIT_func_080541B0
.global func_080541B0
.thumb_set func_080541B0, 0x080541b1
.endif
.ifndef OMIT_func_08054204
.global func_08054204
.thumb_set func_08054204, 0x08054205
.endif
.ifndef OMIT_func_08054284
.global func_08054284
.thumb_set func_08054284, 0x08054285
.endif
.ifndef OMIT_func_08054314
.global func_08054314
.thumb_set func_08054314, 0x08054315
.endif
.ifndef OMIT_func_080543CC
.global func_080543CC
.thumb_set func_080543CC, 0x080543cd
.endif
.ifndef OMIT_func_080543DC
.global func_080543DC
.thumb_set func_080543DC, 0x080543dd
.endif
.ifndef OMIT_func_080543EC
.global func_080543EC
.thumb_set func_080543EC, 0x080543ed
.endif
.ifndef OMIT_func_0805463C
.global func_0805463C
.thumb_set func_0805463C, 0x0805463d
.endif
.ifndef OMIT_func_08054664
.global func_08054664
.thumb_set func_08054664, 0x08054665
.endif
.ifndef OMIT_func_08055DC4
.global func_08055DC4
.thumb_set func_08055DC4, 0x08055dc5
.endif
.ifndef OMIT_func_08055EC0
.global func_08055EC0
.thumb_set func_08055EC0, 0x08055ec1
.endif
.ifndef OMIT_func_08057270
.global func_08057270
.thumb_set func_08057270, 0x08057271
.endif
.ifndef OMIT_func_08057298
.global func_08057298
.thumb_set func_08057298, 0x08057299
.endif
.ifndef OMIT_func_08057388
.global func_08057388
.thumb_set func_08057388, 0x08057389
.endif
.ifndef OMIT_func_080573E8
.global func_080573E8
.thumb_set func_080573E8, 0x080573e9
.endif
.ifndef OMIT_func_08057B90
.global func_08057B90
.thumb_set func_08057B90, 0x08057b91
.endif
.ifndef OMIT_func_08057C88
.global func_08057C88
.thumb_set func_08057C88, 0x08057c89
.endif
.ifndef OMIT_func_08057CDC
.global func_08057CDC
.thumb_set func_08057CDC, 0x08057cdd
.endif
.ifndef OMIT_func_08058104
.global func_08058104
.thumb_set func_08058104, 0x08058105
.endif
.ifndef OMIT_func_08058348
.global func_08058348
.thumb_set func_08058348, 0x08058349
.endif
.ifndef OMIT_func_080583FC
.global func_080583FC
.thumb_set func_080583FC, 0x080583fd
.endif
.ifndef OMIT_func_08058608
.global func_08058608
.thumb_set func_08058608, 0x08058609
.endif
.ifndef OMIT_func_0805871C
.global func_0805871C
.thumb_set func_0805871C, 0x0805871d
.endif
.ifndef OMIT_func_0805872C
.global func_0805872C
.thumb_set func_0805872C, 0x0805872d
.endif
.ifndef OMIT_func_08058890
.global func_08058890
.thumb_set func_08058890, 0x08058891
.endif
.ifndef OMIT_func_08058C48
.global func_08058C48
.thumb_set func_08058C48, 0x08058c49
.endif
.ifndef OMIT_func_080593E0
.global func_080593E0
.thumb_set func_080593E0, 0x080593e1
.endif
.ifndef OMIT_func_0805AAA8
.global func_0805AAA8
.thumb_set func_0805AAA8, 0x0805aaa9
.endif
.ifndef OMIT_func_0805AB34
.global func_0805AB34
.thumb_set func_0805AB34, 0x0805ab35
.endif
.ifndef OMIT_func_0805C02C
.global func_0805C02C
.thumb_set func_0805C02C, 0x0805c02d
.endif
.ifndef OMIT_func_0805C4BC
.global func_0805C4BC
.thumb_set func_0805C4BC, 0x0805c4bd
.endif
.ifndef OMIT_func_0805C568
.global func_0805C568
.thumb_set func_0805C568, 0x0805c569
.endif
.ifndef OMIT_func_0805CF3C
.global func_0805CF3C
.thumb_set func_0805CF3C, 0x0805cf3d
.endif
.ifndef OMIT_func_0805CF5C
.global func_0805CF5C
.thumb_set func_0805CF5C, 0x0805cf5d
.endif
.ifndef OMIT_func_0805D0E0
.global func_0805D0E0
.thumb_set func_0805D0E0, 0x0805d0e1
.endif
.ifndef OMIT_func_0805D108
.global func_0805D108
.thumb_set func_0805D108, 0x0805d109
.endif
.ifndef OMIT_func_0805D13C
.global func_0805D13C
.thumb_set func_0805D13C, 0x0805d13d
.endif
.ifndef OMIT_func_0805D174
.global func_0805D174
.thumb_set func_0805D174, 0x0805d175
.endif
.ifndef OMIT_func_0805D1A4
.global func_0805D1A4
.thumb_set func_0805D1A4, 0x0805d1a5
.endif
.ifndef OMIT_func_0805D1C0
.global func_0805D1C0
.thumb_set func_0805D1C0, 0x0805d1c1
.endif
.ifndef OMIT_func_0805D4EC
.global func_0805D4EC
.thumb_set func_0805D4EC, 0x0805d4ed
.endif
.ifndef OMIT_func_0805D534
.global func_0805D534
.thumb_set func_0805D534, 0x0805d535
.endif
.ifndef OMIT_func_0805D784
.global func_0805D784
.thumb_set func_0805D784, 0x0805d785
.endif
.ifndef OMIT_func_0805D91C
.global func_0805D91C
.thumb_set func_0805D91C, 0x0805d91d
.endif
.ifndef OMIT_func_0805DD0C
.global func_0805DD0C
.thumb_set func_0805DD0C, 0x0805dd0d
.endif
.ifndef OMIT_func_0805DDC8
.global func_0805DDC8
.thumb_set func_0805DDC8, 0x0805ddc9
.endif
.ifndef OMIT_func_0805EAA8
.global func_0805EAA8
.thumb_set func_0805EAA8, 0x0805eaa9
.endif
.ifndef OMIT_func_0805EFEC
.global func_0805EFEC
.thumb_set func_0805EFEC, 0x0805efed
.endif
.ifndef OMIT_func_0805F2A8
.global func_0805F2A8
.thumb_set func_0805F2A8, 0x0805f2a9
.endif
.ifndef OMIT_func_0805F330
.global func_0805F330
.thumb_set func_0805F330, 0x0805f331
.endif
.ifndef OMIT_func_0805F3C4
.global func_0805F3C4
.thumb_set func_0805F3C4, 0x0805f3c5
.endif
.ifndef OMIT_func_0805F414
.global func_0805F414
.thumb_set func_0805F414, 0x0805f415
.endif
.ifndef OMIT_func_0805F4AC
.global func_0805F4AC
.thumb_set func_0805F4AC, 0x0805f4ad
.endif
.ifndef OMIT_func_0805F4D8
.global func_0805F4D8
.thumb_set func_0805F4D8, 0x0805f4d9
.endif
.ifndef OMIT_func_0805F540
.global func_0805F540
.thumb_set func_0805F540, 0x0805f541
.endif
.ifndef OMIT_func_0805F588
.global func_0805F588
.thumb_set func_0805F588, 0x0805f589
.endif
.ifndef OMIT_func_0805F604
.global func_0805F604
.thumb_set func_0805F604, 0x0805f605
.endif
.ifndef OMIT_func_0805F670
.global func_0805F670
.thumb_set func_0805F670, 0x0805f671
.endif
.ifndef OMIT_func_0805F708
.global func_0805F708
.thumb_set func_0805F708, 0x0805f709
.endif
.ifndef OMIT_func_0805F774
.global func_0805F774
.thumb_set func_0805F774, 0x0805f775
.endif
.ifndef OMIT_func_0805FA4C
.global func_0805FA4C
.thumb_set func_0805FA4C, 0x0805fa4d
.endif
.ifndef OMIT_func_0805FD04
.global func_0805FD04
.thumb_set func_0805FD04, 0x0805fd05
.endif
.ifndef OMIT_func_0805FEA8
.global func_0805FEA8
.thumb_set func_0805FEA8, 0x0805fea9
.endif
.ifndef OMIT_func_0805FFF0
.global func_0805FFF0
.thumb_set func_0805FFF0, 0x0805fff1
.endif
.ifndef OMIT_func_08060100
.global func_08060100
.thumb_set func_08060100, 0x08060101
.endif
.ifndef OMIT_func_08060154
.global func_08060154
.thumb_set func_08060154, 0x08060155
.endif
.ifndef OMIT_func_080601B4
.global func_080601B4
.thumb_set func_080601B4, 0x080601b5
.endif
.ifndef OMIT_func_0806025C
.global func_0806025C
.thumb_set func_0806025C, 0x0806025d
.endif
.ifndef OMIT_func_08060404
.global func_08060404
.thumb_set func_08060404, 0x08060405
.endif
.ifndef OMIT_func_08060450
.global func_08060450
.thumb_set func_08060450, 0x08060451
.endif
.ifndef OMIT_func_08060468
.global func_08060468
.thumb_set func_08060468, 0x08060469
.endif
.ifndef OMIT_func_08060544
.global func_08060544
.thumb_set func_08060544, 0x08060545
.endif
.ifndef OMIT_func_08060580
.global func_08060580
.thumb_set func_08060580, 0x08060581
.endif
.ifndef OMIT_func_08060828
.global func_08060828
.thumb_set func_08060828, 0x08060829
.endif
.ifndef OMIT_func_080608E0
.global func_080608E0
.thumb_set func_080608E0, 0x080608e1
.endif
.ifndef OMIT_func_08061028
.global func_08061028
.thumb_set func_08061028, 0x08061029
.endif
.ifndef OMIT_func_080610F8
.global func_080610F8
.thumb_set func_080610F8, 0x080610f9
.endif
.ifndef OMIT_func_08061188
.global func_08061188
.thumb_set func_08061188, 0x08061189
.endif
.ifndef OMIT_func_0806119C
.global func_0806119C
.thumb_set func_0806119C, 0x0806119d
.endif
.ifndef OMIT_func_080611B0
.global func_080611B0
.thumb_set func_080611B0, 0x080611b1
.endif
.ifndef OMIT_func_080611D0
.global func_080611D0
.thumb_set func_080611D0, 0x080611d1
.endif
.ifndef OMIT_func_080611F0
.global func_080611F0
.thumb_set func_080611F0, 0x080611f1
.endif
.ifndef OMIT_func_080612C8
.global func_080612C8
.thumb_set func_080612C8, 0x080612c9
.endif
.ifndef OMIT_func_0806130C
.global func_0806130C
.thumb_set func_0806130C, 0x0806130d
.endif
.ifndef OMIT_func_08061390
.global func_08061390
.thumb_set func_08061390, 0x08061391
.endif
.ifndef OMIT_func_0806144C
.global func_0806144C
.thumb_set func_0806144C, 0x0806144d
.endif
.ifndef OMIT_func_0806149C
.global func_0806149C
.thumb_set func_0806149C, 0x0806149d
.endif
.ifndef OMIT_func_08061518
.global func_08061518
.thumb_set func_08061518, 0x08061519
.endif
.ifndef OMIT_func_08061564
.global func_08061564
.thumb_set func_08061564, 0x08061565
.endif
.ifndef OMIT_func_080615B0
.global func_080615B0
.thumb_set func_080615B0, 0x080615b1
.endif
.ifndef OMIT_func_080617C4
.global func_080617C4
.thumb_set func_080617C4, 0x080617c5
.endif
.ifndef OMIT_func_08061BFC
.global func_08061BFC
.thumb_set func_08061BFC, 0x08061bfd
.endif
.ifndef OMIT_func_08061C24
.global func_08061C24
.thumb_set func_08061C24, 0x08061c25
.endif
.ifndef OMIT_func_08061C30
.global func_08061C30
.thumb_set func_08061C30, 0x08061c31
.endif
.ifndef OMIT_func_08061C9C
.global func_08061C9C
.thumb_set func_08061C9C, 0x08061c9d
.endif
.ifndef OMIT_func_08061DD0
.global func_08061DD0
.thumb_set func_08061DD0, 0x08061dd1
.endif
.ifndef OMIT_func_08061E70
.global func_08061E70
.thumb_set func_08061E70, 0x08061e71
.endif
.ifndef OMIT_func_08061F54
.global func_08061F54
.thumb_set func_08061F54, 0x08061f55
.endif
.ifndef OMIT_func_0806216C
.global func_0806216C
.thumb_set func_0806216C, 0x0806216d
.endif
.ifndef OMIT_func_08062224
.global func_08062224
.thumb_set func_08062224, 0x08062225
.endif
.ifndef OMIT_func_08062430
.global func_08062430
.thumb_set func_08062430, 0x08062431
.endif
.ifndef OMIT_func_080627EC
.global func_080627EC
.thumb_set func_080627EC, 0x080627ed
.endif
.ifndef OMIT_func_08062834
.global func_08062834
.thumb_set func_08062834, 0x08062835
.endif
.ifndef OMIT_func_0806297C
.global func_0806297C
.thumb_set func_0806297C, 0x0806297d
.endif
.ifndef OMIT_func_08062C14
.global func_08062C14
.thumb_set func_08062C14, 0x08062c15
.endif
.ifndef OMIT_func_08062D48
.global func_08062D48
.thumb_set func_08062D48, 0x08062d49
.endif
.ifndef OMIT_func_08062DD8
.global func_08062DD8
.thumb_set func_08062DD8, 0x08062dd9
.endif
.ifndef OMIT_func_08062FD8
.global func_08062FD8
.thumb_set func_08062FD8, 0x08062fd9
.endif
.ifndef OMIT_func_08063060
.global func_08063060
.thumb_set func_08063060, 0x08063061
.endif
.ifndef OMIT_func_080630F0
.global func_080630F0
.thumb_set func_080630F0, 0x080630f1
.endif
.ifndef OMIT_func_08063208
.global func_08063208
.thumb_set func_08063208, 0x08063209
.endif
.ifndef OMIT_func_080632A8
.global func_080632A8
.thumb_set func_080632A8, 0x080632a9
.endif
.ifndef OMIT_func_08063660
.global func_08063660
.thumb_set func_08063660, 0x08063661
.endif
.ifndef OMIT_func_080637A0
.global func_080637A0
.thumb_set func_080637A0, 0x080637a1
.endif
.ifndef OMIT_func_08063804
.global func_08063804
.thumb_set func_08063804, 0x08063805
.endif
.ifndef OMIT_func_08063868
.global func_08063868
.thumb_set func_08063868, 0x08063869
.endif
.ifndef OMIT_func_080638C8
.global func_080638C8
.thumb_set func_080638C8, 0x080638c9
.endif
.ifndef OMIT_func_08063ABC
.global func_08063ABC
.thumb_set func_08063ABC, 0x08063abd
.endif
.ifndef OMIT_func_08063B5C
.global func_08063B5C
.thumb_set func_08063B5C, 0x08063b5d
.endif
.ifndef OMIT_func_08063F18
.global func_08063F18
.thumb_set func_08063F18, 0x08063f19
.endif
.ifndef OMIT_func_08064004
.global func_08064004
.thumb_set func_08064004, 0x08064005
.endif
.ifndef OMIT_func_080641D4
.global func_080641D4
.thumb_set func_080641D4, 0x080641d5
.endif
.ifndef OMIT_func_08064278
.global func_08064278
.thumb_set func_08064278, 0x08064279
.endif
.ifndef OMIT_func_080642D8
.global func_080642D8
.thumb_set func_080642D8, 0x080642d9
.endif
.ifndef OMIT_func_08064354
.global func_08064354
.thumb_set func_08064354, 0x08064355
.endif
.ifndef OMIT_func_08064384
.global func_08064384
.thumb_set func_08064384, 0x08064385
.endif
.ifndef OMIT_func_080643BC
.global func_080643BC
.thumb_set func_080643BC, 0x080643bd
.endif
.ifndef OMIT_func_08064400
.global func_08064400
.thumb_set func_08064400, 0x08064401
.endif
.ifndef OMIT_func_0806444C
.global func_0806444C
.thumb_set func_0806444C, 0x0806444d
.endif
.ifndef OMIT_func_0806447C
.global func_0806447C
.thumb_set func_0806447C, 0x0806447d
.endif
.ifndef OMIT_func_080644A0
.global func_080644A0
.thumb_set func_080644A0, 0x080644a1
.endif
.ifndef OMIT_func_080644DC
.global func_080644DC
.thumb_set func_080644DC, 0x080644dd
.endif
.ifndef OMIT_func_08064774
.global func_08064774
.thumb_set func_08064774, 0x08064775
.endif
.ifndef OMIT_func_080647A8
.global func_080647A8
.thumb_set func_080647A8, 0x080647a9
.endif
.ifndef OMIT_func_08064870
.global func_08064870
.thumb_set func_08064870, 0x08064871
.endif
.ifndef OMIT_func_08064914
.global func_08064914
.thumb_set func_08064914, 0x08064915
.endif
.ifndef OMIT_func_080649A4
.global func_080649A4
.thumb_set func_080649A4, 0x080649a5
.endif
.ifndef OMIT_func_08064A60
.global func_08064A60
.thumb_set func_08064A60, 0x08064a61
.endif
.ifndef OMIT_func_08064BC4
.global func_08064BC4
.thumb_set func_08064BC4, 0x08064bc5
.endif
.ifndef OMIT_func_08064C2C
.global func_08064C2C
.thumb_set func_08064C2C, 0x08064c2d
.endif
.ifndef OMIT_func_08064E2C
.global func_08064E2C
.thumb_set func_08064E2C, 0x08064e2d
.endif
.ifndef OMIT_func_08064E54
.global func_08064E54
.thumb_set func_08064E54, 0x08064e55
.endif
.ifndef OMIT_func_08064E7C
.global func_08064E7C
.thumb_set func_08064E7C, 0x08064e7d
.endif
.ifndef OMIT_func_08064FA0
.global func_08064FA0
.thumb_set func_08064FA0, 0x08064fa1
.endif
.ifndef OMIT_func_08065028
.global func_08065028
.thumb_set func_08065028, 0x08065029
.endif
.ifndef OMIT_func_08065050
.global func_08065050
.thumb_set func_08065050, 0x08065051
.endif
.ifndef OMIT_func_08065060
.global func_08065060
.thumb_set func_08065060, 0x08065061
.endif
.ifndef OMIT_func_0806514C
.global func_0806514C
.thumb_set func_0806514C, 0x0806514d
.endif
.ifndef OMIT_func_0806517C
.global func_0806517C
.thumb_set func_0806517C, 0x0806517d
.endif
.ifndef OMIT_func_08065EF4
.global func_08065EF4
.thumb_set func_08065EF4, 0x08065ef5
.endif
.ifndef OMIT_func_08066018
.global func_08066018
.thumb_set func_08066018, 0x08066019
.endif
.ifndef OMIT_func_08066028
.global func_08066028
.thumb_set func_08066028, 0x08066029
.endif
.ifndef OMIT_func_0806603C
.global func_0806603C
.thumb_set func_0806603C, 0x0806603d
.endif
.ifndef OMIT_func_08066048
.global func_08066048
.thumb_set func_08066048, 0x08066049
.endif
.ifndef OMIT_func_08066120
.global func_08066120
.thumb_set func_08066120, 0x08066121
.endif
.ifndef OMIT_func_08066168
.global func_08066168
.thumb_set func_08066168, 0x08066169
.endif
.ifndef OMIT_func_080664C4
.global func_080664C4
.thumb_set func_080664C4, 0x080664c5
.endif
.ifndef OMIT_func_080664E0
.global func_080664E0
.thumb_set func_080664E0, 0x080664e1
.endif
.ifndef OMIT_func_08066570
.global func_08066570
.thumb_set func_08066570, 0x08066571
.endif
.ifndef OMIT_func_08066718
.global func_08066718
.thumb_set func_08066718, 0x08066719
.endif
.ifndef OMIT_func_080667E4
.global func_080667E4
.thumb_set func_080667E4, 0x080667e5
.endif
.ifndef OMIT_func_080669B4
.global func_080669B4
.thumb_set func_080669B4, 0x080669b5
.endif
.ifndef OMIT_func_08066A8C
.global func_08066A8C
.thumb_set func_08066A8C, 0x08066a8d
.endif
.ifndef OMIT_func_08066BC4
.global func_08066BC4
.thumb_set func_08066BC4, 0x08066bc5
.endif
.ifndef OMIT_func_08066C28
.global func_08066C28
.thumb_set func_08066C28, 0x08066c29
.endif
.ifndef OMIT_func_08066C98
.global func_08066C98
.thumb_set func_08066C98, 0x08066c99
.endif
.ifndef OMIT_func_08066D74
.global func_08066D74
.thumb_set func_08066D74, 0x08066d75
.endif
.ifndef OMIT_func_08066D98
.global func_08066D98
.thumb_set func_08066D98, 0x08066d99
.endif
.ifndef OMIT_func_08066DC4
.global func_08066DC4
.thumb_set func_08066DC4, 0x08066dc5
.endif
.ifndef OMIT_func_08066E08
.global func_08066E08
.thumb_set func_08066E08, 0x08066e09
.endif
.ifndef OMIT_func_08066EA0
.global func_08066EA0
.thumb_set func_08066EA0, 0x08066ea1
.endif
.ifndef OMIT_func_08066ED8
.global func_08066ED8
.thumb_set func_08066ED8, 0x08066ed9
.endif
.ifndef OMIT_func_0806707C
.global func_0806707C
.thumb_set func_0806707C, 0x0806707d
.endif
.ifndef OMIT_func_080670B4
.global func_080670B4
.thumb_set func_080670B4, 0x080670b5
.endif
.ifndef OMIT_func_080674B0
.global func_080674B0
.thumb_set func_080674B0, 0x080674b1
.endif
.ifndef OMIT_func_08067504
.global func_08067504
.thumb_set func_08067504, 0x08067505
.endif
.ifndef OMIT_func_08067528
.global func_08067528
.thumb_set func_08067528, 0x08067529
.endif
.ifndef OMIT_func_08067574
.global func_08067574
.thumb_set func_08067574, 0x08067575
.endif
.ifndef OMIT_func_080675A0
.global func_080675A0
.thumb_set func_080675A0, 0x080675a1
.endif
.ifndef OMIT_func_080676F8
.global func_080676F8
.thumb_set func_080676F8, 0x080676f9
.endif
.ifndef OMIT_func_0806779C
.global func_0806779C
.thumb_set func_0806779C, 0x0806779d
.endif
.ifndef OMIT_func_080678C4
.global func_080678C4
.thumb_set func_080678C4, 0x080678c5
.endif
.ifndef OMIT_func_08067994
.global func_08067994
.thumb_set func_08067994, 0x08067995
.endif
.ifndef OMIT_func_08067A40
.global func_08067A40
.thumb_set func_08067A40, 0x08067a41
.endif
.ifndef OMIT_func_08067B80
.global func_08067B80
.thumb_set func_08067B80, 0x08067b81
.endif
.ifndef OMIT_func_08067CF8
.global func_08067CF8
.thumb_set func_08067CF8, 0x08067cf9
.endif
.ifndef OMIT_func_08067D6C
.global func_08067D6C
.thumb_set func_08067D6C, 0x08067d6d
.endif
.ifndef OMIT_func_08067E48
.global func_08067E48
.thumb_set func_08067E48, 0x08067e49
.endif
.ifndef OMIT_func_08067E9C
.global func_08067E9C
.thumb_set func_08067E9C, 0x08067e9d
.endif
.ifndef OMIT_func_08067EE4
.global func_08067EE4
.thumb_set func_08067EE4, 0x08067ee5
.endif
.ifndef OMIT_func_08067FB0
.global func_08067FB0
.thumb_set func_08067FB0, 0x08067fb1
.endif
.ifndef OMIT_func_0806807C
.global func_0806807C
.thumb_set func_0806807C, 0x0806807d
.endif
.ifndef OMIT_func_080680E0
.global func_080680E0
.thumb_set func_080680E0, 0x080680e1
.endif
.ifndef OMIT_func_080680F8
.global func_080680F8
.thumb_set func_080680F8, 0x080680f9
.endif
.ifndef OMIT_func_08068110
.global func_08068110
.thumb_set func_08068110, 0x08068111
.endif
.ifndef OMIT_func_080681C4
.global func_080681C4
.thumb_set func_080681C4, 0x080681c5
.endif
.ifndef OMIT_func_080682E4
.global func_080682E4
.thumb_set func_080682E4, 0x080682e5
.endif
.ifndef OMIT_func_08068548
.global func_08068548
.thumb_set func_08068548, 0x08068549
.endif
.ifndef OMIT_func_080686C0
.global func_080686C0
.thumb_set func_080686C0, 0x080686c1
.endif
.ifndef OMIT_func_080686F4
.global func_080686F4
.thumb_set func_080686F4, 0x080686f5
.endif
.ifndef OMIT_func_080687D8
.global func_080687D8
.thumb_set func_080687D8, 0x080687d9
.endif
.ifndef OMIT_func_08068808
.global func_08068808
.thumb_set func_08068808, 0x08068809
.endif
.ifndef OMIT_func_08068810
.global func_08068810
.thumb_set func_08068810, 0x08068811
.endif
.ifndef OMIT_func_08068820
.global func_08068820
.thumb_set func_08068820, 0x08068821
.endif
.ifndef OMIT_func_08068848
.global func_08068848
.thumb_set func_08068848, 0x08068849
.endif
.ifndef OMIT_func_08068864
.global func_08068864
.thumb_set func_08068864, 0x08068865
.endif
.ifndef OMIT_func_080688D0
.global func_080688D0
.thumb_set func_080688D0, 0x080688d1
.endif
.ifndef OMIT_func_0806890C
.global func_0806890C
.thumb_set func_0806890C, 0x0806890d
.endif
.ifndef OMIT_func_08068954
.global func_08068954
.thumb_set func_08068954, 0x08068955
.endif
.ifndef OMIT_func_08068998
.global func_08068998
.thumb_set func_08068998, 0x08068999
.endif
.ifndef OMIT_func_08068AE0
.global func_08068AE0
.thumb_set func_08068AE0, 0x08068ae1
.endif
.ifndef OMIT_func_08068C10
.global func_08068C10
.thumb_set func_08068C10, 0x08068c11
.endif
.ifndef OMIT_func_0806B228
.global func_0806B228
.thumb_set func_0806B228, 0x0806b229
.endif
.ifndef OMIT_func_0806B4C4
.global func_0806B4C4
.thumb_set func_0806B4C4, 0x0806b4c5
.endif
.ifndef OMIT_func_0806D2B4
.global func_0806D2B4
.thumb_set func_0806D2B4, 0x0806d2b5
.endif
.ifndef OMIT_func_0806D300
.global func_0806D300
.thumb_set func_0806D300, 0x0806d301
.endif
.ifndef OMIT_func_0806E4E0
.global func_0806E4E0
.thumb_set func_0806E4E0, 0x0806e4e1
.endif
.ifndef OMIT_func_0806E528
.global func_0806E528
.thumb_set func_0806E528, 0x0806e529
.endif
.ifndef OMIT_func_0806E66C
.global func_0806E66C
.thumb_set func_0806E66C, 0x0806e66d
.endif
.ifndef OMIT_func_0806EB08
.global func_0806EB08
.thumb_set func_0806EB08, 0x0806eb09
.endif
.ifndef OMIT_func_0806EBF8
.global func_0806EBF8
.thumb_set func_0806EBF8, 0x0806ebf9
.endif
.ifndef OMIT_func_0806EC20
.global func_0806EC20
.thumb_set func_0806EC20, 0x0806ec21
.endif
.ifndef OMIT_func_0806EE98
.global func_0806EE98
.thumb_set func_0806EE98, 0x0806ee99
.endif
.ifndef OMIT_func_0806EFA8
.global func_0806EFA8
.thumb_set func_0806EFA8, 0x0806efa9
.endif
.ifndef OMIT_func_0806EFE4
.global func_0806EFE4
.thumb_set func_0806EFE4, 0x0806efe5
.endif
.ifndef OMIT_func_0806EFF0
.global func_0806EFF0
.thumb_set func_0806EFF0, 0x0806eff1
.endif
.ifndef OMIT_func_0806F028
.global func_0806F028
.thumb_set func_0806F028, 0x0806f029
.endif
.ifndef OMIT_func_0806F050
.global func_0806F050
.thumb_set func_0806F050, 0x0806f051
.endif
.ifndef OMIT_func_0806F0D4
.global func_0806F0D4
.thumb_set func_0806F0D4, 0x0806f0d5
.endif
.ifndef OMIT_func_0806F0D8
.global func_0806F0D8
.thumb_set func_0806F0D8, 0x0806f0d9
.endif
.ifndef OMIT_func_0806F0DC
.global func_0806F0DC
.thumb_set func_0806F0DC, 0x0806f0dd
.endif
.ifndef OMIT_func_0806F1EC
.global func_0806F1EC
.thumb_set func_0806F1EC, 0x0806f1ed
.endif
.ifndef OMIT_func_0806F2E0
.global func_0806F2E0
.thumb_set func_0806F2E0, 0x0806f2e1
.endif
.ifndef OMIT_func_0806F3C0
.global func_0806F3C0
.thumb_set func_0806F3C0, 0x0806f3c1
.endif
.ifndef OMIT_func_0806F3C4
.global func_0806F3C4
.thumb_set func_0806F3C4, 0x0806f3c5
.endif
.ifndef OMIT_func_0806F3C8
.global func_0806F3C8
.thumb_set func_0806F3C8, 0x0806f3c9
.endif
.ifndef OMIT_func_0806F568
.global func_0806F568
.thumb_set func_0806F568, 0x0806f569
.endif
.ifndef OMIT_func_0806F5FC
.global func_0806F5FC
.thumb_set func_0806F5FC, 0x0806f5fd
.endif
.ifndef OMIT_func_0806FE14
.global func_0806FE14
.thumb_set func_0806FE14, 0x0806fe15
.endif
.ifndef OMIT_func_0806FE18
.global func_0806FE18
.thumb_set func_0806FE18, 0x0806fe19
.endif
.ifndef OMIT_func_0806FE1C
.global func_0806FE1C
.thumb_set func_0806FE1C, 0x0806fe1d
.endif
.ifndef OMIT_func_0806FFAC
.global func_0806FFAC
.thumb_set func_0806FFAC, 0x0806ffad
.endif
.ifndef OMIT_func_0806FFE4
.global func_0806FFE4
.thumb_set func_0806FFE4, 0x0806ffe5
.endif
.ifndef OMIT_func_0806FFF8
.global func_0806FFF8
.thumb_set func_0806FFF8, 0x0806fff9
.endif
.ifndef OMIT_func_08070120
.global func_08070120
.thumb_set func_08070120, 0x08070121
.endif
.ifndef OMIT_func_08070170
.global func_08070170
.thumb_set func_08070170, 0x08070171
.endif
.ifndef OMIT_func_08070604
.global func_08070604
.thumb_set func_08070604, 0x08070605
.endif
.ifndef OMIT_func_08070C94
.global func_08070C94
.thumb_set func_08070C94, 0x08070c95
.endif
.ifndef OMIT_func_08071234
.global func_08071234
.thumb_set func_08071234, 0x08071235
.endif
.ifndef OMIT_func_08071704
.global func_08071704
.thumb_set func_08071704, 0x08071705
.endif
.ifndef OMIT_func_080717CC
.global func_080717CC
.thumb_set func_080717CC, 0x080717cd
.endif
.ifndef OMIT_func_08071DC8
.global func_08071DC8
.thumb_set func_08071DC8, 0x08071dc9
.endif
.ifndef OMIT_func_080748AC
.global func_080748AC
.thumb_set func_080748AC, 0x080748ad
.endif
.ifndef OMIT_func_08075E24
.global func_08075E24
.thumb_set func_08075E24, 0x08075e25
.endif
.ifndef OMIT_func_0807974C
.global func_0807974C
.thumb_set func_0807974C, 0x0807974d
.endif
.ifndef OMIT_func_0807B858
.global func_0807B858
.thumb_set func_0807B858, 0x0807b859
.endif
.ifndef OMIT_func_0807C7E8
.global func_0807C7E8
.thumb_set func_0807C7E8, 0x0807c7e9
.endif
.ifndef OMIT_func_0807D96C
.global func_0807D96C
.thumb_set func_0807D96C, 0x0807d96d
.endif
.ifndef OMIT_func_0807E2C4
.global func_0807E2C4
.thumb_set func_0807E2C4, 0x0807e2c5
.endif
.ifndef OMIT_func_08080D34
.global func_08080D34
.thumb_set func_08080D34, 0x08080d35
.endif
.ifndef OMIT_func_08080F68
.global func_08080F68
.thumb_set func_08080F68, 0x08080f69
.endif
.ifndef OMIT_func_08081078
.global func_08081078
.thumb_set func_08081078, 0x08081079
.endif
.ifndef OMIT_func_080812E8
.global func_080812E8
.thumb_set func_080812E8, 0x080812e9
.endif
.ifndef OMIT_func_080819F0
.global func_080819F0
.thumb_set func_080819F0, 0x080819f1
.endif
.ifndef OMIT_func_08081D28
.global func_08081D28
.thumb_set func_08081D28, 0x08081d29
.endif
.ifndef OMIT_func_0808286C
.global func_0808286C
.thumb_set func_0808286C, 0x0808286d
.endif
.ifndef OMIT_func_080835A4
.global func_080835A4
.thumb_set func_080835A4, 0x080835a5
.endif
.ifndef OMIT_func_080837AC
.global func_080837AC
.thumb_set func_080837AC, 0x080837ad
.endif
.ifndef OMIT_func_08085374
.global func_08085374
.thumb_set func_08085374, 0x08085375
.endif
.ifndef OMIT_func_0808537C
.global func_0808537C
.thumb_set func_0808537C, 0x0808537d
.endif
.ifndef OMIT_func_08085450
.global func_08085450
.thumb_set func_08085450, 0x08085451
.endif
.ifndef OMIT_func_080870E0
.global func_080870E0
.thumb_set func_080870E0, 0x080870e1
.endif
.ifndef OMIT_func_0808748C
.global func_0808748C
.thumb_set func_0808748C, 0x0808748d
.endif
.ifndef OMIT_func_08088CDC
.global func_08088CDC
.thumb_set func_08088CDC, 0x08088cdd
.endif
.ifndef OMIT_func_08088DF0
.global func_08088DF0
.thumb_set func_08088DF0, 0x08088df1
.endif
.ifndef OMIT_func_080891BC
.global func_080891BC
.thumb_set func_080891BC, 0x080891bd
.endif
.ifndef OMIT_func_08089248
.global func_08089248
.thumb_set func_08089248, 0x08089249
.endif
.ifndef OMIT_func_080892D8
.global func_080892D8
.thumb_set func_080892D8, 0x080892d9
.endif
.ifndef OMIT_func_08089600
.global func_08089600
.thumb_set func_08089600, 0x08089601
.endif
.ifndef OMIT_func_08089638
.global func_08089638
.thumb_set func_08089638, 0x08089639
.endif
.ifndef OMIT_func_080897C4
.global func_080897C4
.thumb_set func_080897C4, 0x080897c5
.endif
.ifndef OMIT_func_080899AC
.global func_080899AC
.thumb_set func_080899AC, 0x080899ad
.endif
.ifndef OMIT_func_08089B0C
.global func_08089B0C
.thumb_set func_08089B0C, 0x08089b0d
.endif
.ifndef OMIT_func_08089B48
.global func_08089B48
.thumb_set func_08089B48, 0x08089b49
.endif
.ifndef OMIT_func_08089EB4
.global func_08089EB4
.thumb_set func_08089EB4, 0x08089eb5
.endif
.ifndef OMIT_func_08089F20
.global func_08089F20
.thumb_set func_08089F20, 0x08089f21
.endif
.ifndef OMIT_func_08089F98
.global func_08089F98
.thumb_set func_08089F98, 0x08089f99
.endif
.ifndef OMIT_func_0808A008
.global func_0808A008
.thumb_set func_0808A008, 0x0808a009
.endif
.ifndef OMIT_func_0808A268
.global func_0808A268
.thumb_set func_0808A268, 0x0808a269
.endif
.ifndef OMIT_func_0808A424
.global func_0808A424
.thumb_set func_0808A424, 0x0808a425
.endif
.ifndef OMIT_func_0808A604
.global func_0808A604
.thumb_set func_0808A604, 0x0808a605
.endif
.ifndef OMIT_func_0808A830
.global func_0808A830
.thumb_set func_0808A830, 0x0808a831
.endif
.ifndef OMIT_func_0808A8C0
.global func_0808A8C0
.thumb_set func_0808A8C0, 0x0808a8c1
.endif
.ifndef OMIT_func_0808A948
.global func_0808A948
.thumb_set func_0808A948, 0x0808a949
.endif
.ifndef OMIT_func_0808B4FC
.global func_0808B4FC
.thumb_set func_0808B4FC, 0x0808b4fd
.endif
.ifndef OMIT_func_0808B768
.global func_0808B768
.thumb_set func_0808B768, 0x0808b769
.endif
.ifndef OMIT_func_0808B7C0
.global func_0808B7C0
.thumb_set func_0808B7C0, 0x0808b7c1
.endif
.ifndef OMIT_func_0808B80C
.global func_0808B80C
.thumb_set func_0808B80C, 0x0808b80d
.endif
.ifndef OMIT_func_0808B858
.global func_0808B858
.thumb_set func_0808B858, 0x0808b859
.endif
.ifndef OMIT_func_0808B8E4
.global func_0808B8E4
.thumb_set func_0808B8E4, 0x0808b8e5
.endif
.ifndef OMIT_func_0808B92C
.global func_0808B92C
.thumb_set func_0808B92C, 0x0808b92d
.endif
.ifndef OMIT_func_0808B950
.global func_0808B950
.thumb_set func_0808B950, 0x0808b951
.endif
.ifndef OMIT_func_0808BA08
.global func_0808BA08
.thumb_set func_0808BA08, 0x0808ba09
.endif
.ifndef OMIT_func_0808BE0C
.global func_0808BE0C
.thumb_set func_0808BE0C, 0x0808be0d
.endif
.ifndef OMIT_func_0808CBDC
.global func_0808CBDC
.thumb_set func_0808CBDC, 0x0808cbdd
.endif
.ifndef OMIT_func_0808EEE8
.global func_0808EEE8
.thumb_set func_0808EEE8, 0x0808eee9
.endif
.ifndef OMIT_func_0808EF90
.global func_0808EF90
.thumb_set func_0808EF90, 0x0808ef91
.endif
.ifndef OMIT_func_0808F638
.global func_0808F638
.thumb_set func_0808F638, 0x0808f639
.endif
.ifndef OMIT_func_0808F74C
.global func_0808F74C
.thumb_set func_0808F74C, 0x0808f74d
.endif
.ifndef OMIT_func_0808F770
.global func_0808F770
.thumb_set func_0808F770, 0x0808f771
.endif
.ifndef OMIT_func_0808F788
.global func_0808F788
.thumb_set func_0808F788, 0x0808f789
.endif
.ifndef OMIT_func_0808F79C
.global func_0808F79C
.thumb_set func_0808F79C, 0x0808f79d
.endif
.ifndef OMIT_func_0808F7CC
.global func_0808F7CC
.thumb_set func_0808F7CC, 0x0808f7cd
.endif
.ifndef OMIT_func_080901A8
.global func_080901A8
.thumb_set func_080901A8, 0x080901a9
.endif
.ifndef OMIT_func_08090214
.global func_08090214
.thumb_set func_08090214, 0x08090215
.endif
.ifndef OMIT_func_08090264
.global func_08090264
.thumb_set func_08090264, 0x08090265
.endif
.ifndef OMIT_func_08092084
.global func_08092084
.thumb_set func_08092084, 0x08092085
.endif
.ifndef OMIT_func_0809209C
.global func_0809209C
.thumb_set func_0809209C, 0x0809209d
.endif
.ifndef OMIT_func_080920BC
.global func_080920BC
.thumb_set func_080920BC, 0x080920bd
.endif
.ifndef OMIT_func_080920D0
.global func_080920D0
.thumb_set func_080920D0, 0x080920d1
.endif
.ifndef OMIT_func_080920DC
.global func_080920DC
.thumb_set func_080920DC, 0x080920dd
.endif
.ifndef OMIT_func_080921B4
.global func_080921B4
.thumb_set func_080921B4, 0x080921b5
.endif
.ifndef OMIT_func_08092210
.global func_08092210
.thumb_set func_08092210, 0x08092211
.endif
.ifndef OMIT_func_08092288
.global func_08092288
.thumb_set func_08092288, 0x08092289
.endif
.ifndef OMIT_func_080922A4
.global func_080922A4
.thumb_set func_080922A4, 0x080922a5
.endif
.ifndef OMIT_func_080922C4
.global func_080922C4
.thumb_set func_080922C4, 0x080922c5
.endif
.ifndef OMIT_func_080922CC
.global func_080922CC
.thumb_set func_080922CC, 0x080922cd
.endif
.ifndef OMIT_func_08092440
.global func_08092440
.thumb_set func_08092440, 0x08092441
.endif
.ifndef OMIT_func_080924F4
.global func_080924F4
.thumb_set func_080924F4, 0x080924f5
.endif
.ifndef OMIT_func_080925A4
.global func_080925A4
.thumb_set func_080925A4, 0x080925a5
.endif
.ifndef OMIT_func_08092784
.global func_08092784
.thumb_set func_08092784, 0x08092785
.endif
.ifndef OMIT_func_08096B2C
.global func_08096B2C
.thumb_set func_08096B2C, 0x08096b2d
.endif
.ifndef OMIT_func_08096BA0
.global func_08096BA0
.thumb_set func_08096BA0, 0x08096ba1
.endif
.ifndef OMIT_func_08096CB8
.global func_08096CB8
.thumb_set func_08096CB8, 0x08096cb9
.endif
.ifndef OMIT_func_08096D7C
.global func_08096D7C
.thumb_set func_08096D7C, 0x08096d7d
.endif
.ifndef OMIT_func_08096D88
.global func_08096D88
.thumb_set func_08096D88, 0x08096d89
.endif
.ifndef OMIT_func_08096DE4
.global func_08096DE4
.thumb_set func_08096DE4, 0x08096de5
.endif
.ifndef OMIT_func_08096E18
.global func_08096E18
.thumb_set func_08096E18, 0x08096e19
.endif
.ifndef OMIT_func_08096E78
.global func_08096E78
.thumb_set func_08096E78, 0x08096e79
.endif
.ifndef OMIT_func_08096ED4
.global func_08096ED4
.thumb_set func_08096ED4, 0x08096ed5
.endif
.ifndef OMIT_func_08096F3C
.global func_08096F3C
.thumb_set func_08096F3C, 0x08096f3d
.endif
.ifndef OMIT_func_08096F8C
.global func_08096F8C
.thumb_set func_08096F8C, 0x08096f8d
.endif
.ifndef OMIT_func_08096FD8
.global func_08096FD8
.thumb_set func_08096FD8, 0x08096fd9
.endif
.ifndef OMIT_func_08097000
.global func_08097000
.thumb_set func_08097000, 0x08097001
.endif
.ifndef OMIT_func_080970E8
.global func_080970E8
.thumb_set func_080970E8, 0x080970e9
.endif
.ifndef OMIT_func_080971F8
.global func_080971F8
.thumb_set func_080971F8, 0x080971f9
.endif
.ifndef OMIT_func_08097298
.global func_08097298
.thumb_set func_08097298, 0x08097299
.endif
.ifndef OMIT_func_08097478
.global func_08097478
.thumb_set func_08097478, 0x08097479
.endif
.ifndef OMIT_func_080975DC
.global func_080975DC
.thumb_set func_080975DC, 0x080975dd
.endif
.ifndef OMIT_func_08097704
.global func_08097704
.thumb_set func_08097704, 0x08097705
.endif
.ifndef OMIT_func_08097814
.global func_08097814
.thumb_set func_08097814, 0x08097815
.endif
.ifndef OMIT_func_0809801C
.global func_0809801C
.thumb_set func_0809801C, 0x0809801d
.endif
.ifndef OMIT_func_0809836C
.global func_0809836C
.thumb_set func_0809836C, 0x0809836d
.endif
.ifndef OMIT_func_080989AC
.global func_080989AC
.thumb_set func_080989AC, 0x080989ad
.endif
.ifndef OMIT_func_08098BB0
.global func_08098BB0
.thumb_set func_08098BB0, 0x08098bb1
.endif
.ifndef OMIT_func_08098C20
.global func_08098C20
.thumb_set func_08098C20, 0x08098c21
.endif
.ifndef OMIT_func_08098CE8
.global func_08098CE8
.thumb_set func_08098CE8, 0x08098ce9
.endif
.ifndef OMIT_func_08098E7C
.global func_08098E7C
.thumb_set func_08098E7C, 0x08098e7d
.endif
.ifndef OMIT_func_0809906C
.global func_0809906C
.thumb_set func_0809906C, 0x0809906d
.endif
.ifndef OMIT_func_080992E0
.global func_080992E0
.thumb_set func_080992E0, 0x080992e1
.endif
.ifndef OMIT_func_080993F4
.global func_080993F4
.thumb_set func_080993F4, 0x080993f5
.endif
.ifndef OMIT_func_08099494
.global func_08099494
.thumb_set func_08099494, 0x08099495
.endif
.ifndef OMIT_func_08099544
.global func_08099544
.thumb_set func_08099544, 0x08099545
.endif
.ifndef OMIT_func_08099560
.global func_08099560
.thumb_set func_08099560, 0x08099561
.endif
.ifndef OMIT_func_080995C0
.global func_080995C0
.thumb_set func_080995C0, 0x080995c1
.endif
.ifndef OMIT_func_0809961C
.global func_0809961C
.thumb_set func_0809961C, 0x0809961d
.endif
.ifndef OMIT_func_08099644
.global func_08099644
.thumb_set func_08099644, 0x08099645
.endif
.ifndef OMIT_func_0809966C
.global func_0809966C
.thumb_set func_0809966C, 0x0809966d
.endif
.ifndef OMIT_func_0809975C
.global func_0809975C
.thumb_set func_0809975C, 0x0809975d
.endif
.ifndef OMIT_func_08099790
.global func_08099790
.thumb_set func_08099790, 0x08099791
.endif
.ifndef OMIT_func_080997E8
.global func_080997E8
.thumb_set func_080997E8, 0x080997e9
.endif
.ifndef OMIT_func_0809993C
.global func_0809993C
.thumb_set func_0809993C, 0x0809993d
.endif
.ifndef OMIT_func_0809995C
.global func_0809995C
.thumb_set func_0809995C, 0x0809995d
.endif
.ifndef OMIT_func_08099BAC
.global func_08099BAC
.thumb_set func_08099BAC, 0x08099bad
.endif
.ifndef OMIT_func_08099BF4
.global func_08099BF4
.thumb_set func_08099BF4, 0x08099bf5
.endif
.ifndef OMIT_func_08099C04
.global func_08099C04
.thumb_set func_08099C04, 0x08099c05
.endif
.ifndef OMIT_func_08099C10
.global func_08099C10
.thumb_set func_08099C10, 0x08099c11
.endif
.ifndef OMIT_func_08099C14
.global func_08099C14
.thumb_set func_08099C14, 0x08099c15
.endif
.ifndef OMIT_func_08099C1C
.global func_08099C1C
.thumb_set func_08099C1C, 0x08099c1d
.endif
.ifndef OMIT_func_08099C30
.global func_08099C30
.thumb_set func_08099C30, 0x08099c31
.endif
.ifndef OMIT_func_08099C34
.global func_08099C34
.thumb_set func_08099C34, 0x08099c35
.endif
.ifndef OMIT_func_08099C64
.global func_08099C64
.thumb_set func_08099C64, 0x08099c65
.endif
.ifndef OMIT_func_08099C9C
.global func_08099C9C
.thumb_set func_08099C9C, 0x08099c9d
.endif
.ifndef OMIT_func_08099CB8
.global func_08099CB8
.thumb_set func_08099CB8, 0x08099cb9
.endif
.ifndef OMIT_func_08099CC4
.global func_08099CC4
.thumb_set func_08099CC4, 0x08099cc5
.endif
.ifndef OMIT_func_08099CD0
.global func_08099CD0
.thumb_set func_08099CD0, 0x08099cd1
.endif
.ifndef OMIT_func_08099CDC
.global func_08099CDC
.thumb_set func_08099CDC, 0x08099cdd
.endif
.ifndef OMIT_func_08099D08
.global func_08099D08
.thumb_set func_08099D08, 0x08099d09
.endif
.ifndef OMIT_func_08099D34
.global func_08099D34
.thumb_set func_08099D34, 0x08099d35
.endif
.ifndef OMIT_func_08099E68
.global func_08099E68
.thumb_set func_08099E68, 0x08099e69
.endif
.ifndef OMIT_func_08099EA0
.global func_08099EA0
.thumb_set func_08099EA0, 0x08099ea1
.endif
.ifndef OMIT_func_08099F00
.global func_08099F00
.thumb_set func_08099F00, 0x08099f01
.endif
.ifndef OMIT_func_08099FB0
.global func_08099FB0
.thumb_set func_08099FB0, 0x08099fb1
.endif
.ifndef OMIT_func_0809A09C
.global func_0809A09C
.thumb_set func_0809A09C, 0x0809a09d
.endif
.ifndef OMIT_func_0809A0F4
.global func_0809A0F4
.thumb_set func_0809A0F4, 0x0809a0f5
.endif
.ifndef OMIT_func_0809A244
.global func_0809A244
.thumb_set func_0809A244, 0x0809a245
.endif
.ifndef OMIT_func_0809A260
.global func_0809A260
.thumb_set func_0809A260, 0x0809a261
.endif
.ifndef OMIT_func_0809A27C
.global func_0809A27C
.thumb_set func_0809A27C, 0x0809a27d
.endif
.ifndef OMIT_func_0809A298
.global func_0809A298
.thumb_set func_0809A298, 0x0809a299
.endif
.ifndef OMIT_func_0809A2AC
.global func_0809A2AC
.thumb_set func_0809A2AC, 0x0809a2ad
.endif
.ifndef OMIT_func_0809A2D8
.global func_0809A2D8
.thumb_set func_0809A2D8, 0x0809a2d9
.endif
.ifndef OMIT_func_0809A304
.global func_0809A304
.thumb_set func_0809A304, 0x0809a305
.endif
.ifndef OMIT_func_0809A398
.global func_0809A398
.thumb_set func_0809A398, 0x0809a399
.endif
.ifndef OMIT_func_0809A3BC
.global func_0809A3BC
.thumb_set func_0809A3BC, 0x0809a3bd
.endif
.ifndef OMIT_func_0809A3F4
.global func_0809A3F4
.thumb_set func_0809A3F4, 0x0809a3f5
.endif
.ifndef OMIT_func_0809A48C
.global func_0809A48C
.thumb_set func_0809A48C, 0x0809a48d
.endif
.ifndef OMIT_func_0809A530
.global func_0809A530
.thumb_set func_0809A530, 0x0809a531
.endif
.ifndef OMIT_func_0809A53C
.global func_0809A53C
.thumb_set func_0809A53C, 0x0809a53d
.endif
.ifndef OMIT_func_0809A570
.global func_0809A570
.thumb_set func_0809A570, 0x0809a571
.endif
.ifndef OMIT_func_0809A5AC
.global func_0809A5AC
.thumb_set func_0809A5AC, 0x0809a5ad
.endif
.ifndef OMIT_func_0809A5C0
.global func_0809A5C0
.thumb_set func_0809A5C0, 0x0809a5c1
.endif
.ifndef OMIT_func_0809A5E0
.global func_0809A5E0
.thumb_set func_0809A5E0, 0x0809a5e1
.endif
.ifndef OMIT_func_0809A604
.global func_0809A604
.thumb_set func_0809A604, 0x0809a605
.endif
.ifndef OMIT_func_0809A624
.global func_0809A624
.thumb_set func_0809A624, 0x0809a625
.endif
.ifndef OMIT_func_0809A63C
.global func_0809A63C
.thumb_set func_0809A63C, 0x0809a63d
.endif
.ifndef OMIT_func_0809A68C
.global func_0809A68C
.thumb_set func_0809A68C, 0x0809a68d
.endif
.ifndef OMIT_func_0809A710
.global func_0809A710
.thumb_set func_0809A710, 0x0809a711
.endif
.ifndef OMIT_func_0809A740
.global func_0809A740
.thumb_set func_0809A740, 0x0809a741
.endif
.ifndef OMIT_func_0809A77C
.global func_0809A77C
.thumb_set func_0809A77C, 0x0809a77d
.endif
.ifndef OMIT_func_0809A7B8
.global func_0809A7B8
.thumb_set func_0809A7B8, 0x0809a7b9
.endif
.ifndef OMIT_func_0809A848
.global func_0809A848
.thumb_set func_0809A848, 0x0809a849
.endif
.ifndef OMIT_func_0809A8C8
.global func_0809A8C8
.thumb_set func_0809A8C8, 0x0809a8c9
.endif
.ifndef OMIT_func_0809A950
.global func_0809A950
.thumb_set func_0809A950, 0x0809a951
.endif
.ifndef OMIT_func_0809A9A8
.global func_0809A9A8
.thumb_set func_0809A9A8, 0x0809a9a9
.endif
.ifndef OMIT_func_0809A9BC
.global func_0809A9BC
.thumb_set func_0809A9BC, 0x0809a9bd
.endif
.ifndef OMIT_func_0809A9C0
.global func_0809A9C0
.thumb_set func_0809A9C0, 0x0809a9c1
.endif
.ifndef OMIT_func_0809A9F0
.global func_0809A9F0
.thumb_set func_0809A9F0, 0x0809a9f1
.endif
.ifndef OMIT_func_0809AA10
.global func_0809AA10
.thumb_set func_0809AA10, 0x0809aa11
.endif
.ifndef OMIT_func_0809AA94
.global func_0809AA94
.thumb_set func_0809AA94, 0x0809aa95
.endif
.ifndef OMIT_func_0809AB0C
.global func_0809AB0C
.thumb_set func_0809AB0C, 0x0809ab0d
.endif
.ifndef OMIT_func_0809AB14
.global func_0809AB14
.thumb_set func_0809AB14, 0x0809ab15
.endif
.ifndef OMIT_func_0809AB24
.global func_0809AB24
.thumb_set func_0809AB24, 0x0809ab25
.endif
.ifndef OMIT_func_0809AB3C
.global func_0809AB3C
.thumb_set func_0809AB3C, 0x0809ab3d
.endif
.ifndef OMIT_func_0809AB5C
.global func_0809AB5C
.thumb_set func_0809AB5C, 0x0809ab5d
.endif
.ifndef OMIT_func_0809AB7C
.global func_0809AB7C
.thumb_set func_0809AB7C, 0x0809ab7d
.endif
.ifndef OMIT_func_0809ABB0
.global func_0809ABB0
.thumb_set func_0809ABB0, 0x0809abb1
.endif
.ifndef OMIT_func_0809ABE8
.global func_0809ABE8
.thumb_set func_0809ABE8, 0x0809abe9
.endif
.ifndef OMIT_func_0809AC20
.global func_0809AC20
.thumb_set func_0809AC20, 0x0809ac21
.endif
.ifndef OMIT_func_0809AC30
.global func_0809AC30
.thumb_set func_0809AC30, 0x0809ac31
.endif
.ifndef OMIT_func_0809AC6C
.global func_0809AC6C
.thumb_set func_0809AC6C, 0x0809ac6d
.endif
.ifndef OMIT_func_0809AC88
.global func_0809AC88
.thumb_set func_0809AC88, 0x0809ac89
.endif
.ifndef OMIT_func_0809ACA4
.global func_0809ACA4
.thumb_set func_0809ACA4, 0x0809aca5
.endif
.ifndef OMIT_func_0809ACB4
.global func_0809ACB4
.thumb_set func_0809ACB4, 0x0809acb5
.endif
.ifndef OMIT_func_0809ACE4
.global func_0809ACE4
.thumb_set func_0809ACE4, 0x0809ace5
.endif
.ifndef OMIT_func_0809AD1C
.global func_0809AD1C
.thumb_set func_0809AD1C, 0x0809ad1d
.endif
.ifndef OMIT_func_0809AD48
.global func_0809AD48
.thumb_set func_0809AD48, 0x0809ad49
.endif
.ifndef OMIT_func_0809AD6C
.global func_0809AD6C
.thumb_set func_0809AD6C, 0x0809ad6d
.endif
.ifndef OMIT_func_0809AEF8
.global func_0809AEF8
.thumb_set func_0809AEF8, 0x0809aef9
.endif
.ifndef OMIT_func_0809B470
.global func_0809B470
.thumb_set func_0809B470, 0x0809b471
.endif
.ifndef OMIT_func_0809B818
.global func_0809B818
.thumb_set func_0809B818, 0x0809b819
.endif
.ifndef OMIT_func_0809C6B8
.global func_0809C6B8
.thumb_set func_0809C6B8, 0x0809c6b9
.endif
.ifndef OMIT_func_0809C8C8
.global func_0809C8C8
.thumb_set func_0809C8C8, 0x0809c8c9
.endif
.ifndef OMIT_func_0809CC3C
.global func_0809CC3C
.thumb_set func_0809CC3C, 0x0809cc3d
.endif
.ifndef OMIT_func_0809CCD4
.global func_0809CCD4
.thumb_set func_0809CCD4, 0x0809ccd5
.endif
.ifndef OMIT_func_0809D2F8
.global func_0809D2F8
.thumb_set func_0809D2F8, 0x0809d2f9
.endif
.ifndef OMIT_func_0809D3A8
.global func_0809D3A8
.thumb_set func_0809D3A8, 0x0809d3a9
.endif
.ifndef OMIT_func_0809D428
.global func_0809D428
.thumb_set func_0809D428, 0x0809d429
.endif
.ifndef OMIT_func_0809D458
.global func_0809D458
.thumb_set func_0809D458, 0x0809d459
.endif
.ifndef OMIT_func_0809D5E8
.global func_0809D5E8
.thumb_set func_0809D5E8, 0x0809d5e9
.endif
.ifndef OMIT_func_0809D614
.global func_0809D614
.thumb_set func_0809D614, 0x0809d615
.endif
.ifndef OMIT_func_0809D620
.global func_0809D620
.thumb_set func_0809D620, 0x0809d621
.endif
.ifndef OMIT_func_0809D638
.global func_0809D638
.thumb_set func_0809D638, 0x0809d639
.endif
.ifndef OMIT_func_0809D66C
.global func_0809D66C
.thumb_set func_0809D66C, 0x0809d66d
.endif
.ifndef OMIT_func_0809D6BC
.global func_0809D6BC
.thumb_set func_0809D6BC, 0x0809d6bd
.endif
.ifndef OMIT_func_0809D854
.global func_0809D854
.thumb_set func_0809D854, 0x0809d855
.endif
.ifndef OMIT_func_0809D86C
.global func_0809D86C
.thumb_set func_0809D86C, 0x0809d86d
.endif
.ifndef OMIT_func_0809D8B4
.global func_0809D8B4
.thumb_set func_0809D8B4, 0x0809d8b5
.endif
.ifndef OMIT_func_0809D8C4
.global func_0809D8C4
.thumb_set func_0809D8C4, 0x0809d8c5
.endif
.ifndef OMIT_func_0809D8D0
.global func_0809D8D0
.thumb_set func_0809D8D0, 0x0809d8d1
.endif
.ifndef OMIT_func_0809D8F0
.global func_0809D8F0
.thumb_set func_0809D8F0, 0x0809d8f1
.endif
.ifndef OMIT_func_0809D90C
.global func_0809D90C
.thumb_set func_0809D90C, 0x0809d90d
.endif
.ifndef OMIT_func_0809D938
.global func_0809D938
.thumb_set func_0809D938, 0x0809d939
.endif
.ifndef OMIT_func_0809D96C
.global func_0809D96C
.thumb_set func_0809D96C, 0x0809d96d
.endif
.ifndef OMIT_func_0809D9D8
.global func_0809D9D8
.thumb_set func_0809D9D8, 0x0809d9d9
.endif
.ifndef OMIT_func_0809DCC4
.global func_0809DCC4
.thumb_set func_0809DCC4, 0x0809dcc5
.endif
.ifndef OMIT_func_0809DE00
.global func_0809DE00
.thumb_set func_0809DE00, 0x0809de01
.endif
.ifndef OMIT_func_0809DF7C
.global func_0809DF7C
.thumb_set func_0809DF7C, 0x0809df7d
.endif
.ifndef OMIT_func_0809E05C
.global func_0809E05C
.thumb_set func_0809E05C, 0x0809e05d
.endif
.ifndef OMIT_func_0809EA60
.global func_0809EA60
.thumb_set func_0809EA60, 0x0809ea61
.endif
.ifndef OMIT_func_0809ED38
.global func_0809ED38
.thumb_set func_0809ED38, 0x0809ed39
.endif
.ifndef OMIT_func_0809F938
.global func_0809F938
.thumb_set func_0809F938, 0x0809f939
.endif
.ifndef OMIT_func_0809F9A8
.global func_0809F9A8
.thumb_set func_0809F9A8, 0x0809f9a9
.endif
.ifndef OMIT_func_0809F9C0
.global func_0809F9C0
.thumb_set func_0809F9C0, 0x0809f9c1
.endif
.ifndef OMIT_func_0809F9D0
.global func_0809F9D0
.thumb_set func_0809F9D0, 0x0809f9d1
.endif
.ifndef OMIT_func_0809F9D8
.global func_0809F9D8
.thumb_set func_0809F9D8, 0x0809f9d9
.endif
.ifndef OMIT_func_0809FA1C
.global func_0809FA1C
.thumb_set func_0809FA1C, 0x0809fa1d
.endif
.ifndef OMIT_func_0809FBF4
.global func_0809FBF4
.thumb_set func_0809FBF4, 0x0809fbf5
.endif
.ifndef OMIT_func_0809FDC0
.global func_0809FDC0
.thumb_set func_0809FDC0, 0x0809fdc1
.endif
.ifndef OMIT_func_080A0254
.global func_080A0254
.thumb_set func_080A0254, 0x080a0255
.endif
.ifndef OMIT_func_080A0468
.global func_080A0468
.thumb_set func_080A0468, 0x080a0469
.endif
.ifndef OMIT_func_080A04E8
.global func_080A04E8
.thumb_set func_080A04E8, 0x080a04e9
.endif
.ifndef OMIT_func_080A0DEC
.global func_080A0DEC
.thumb_set func_080A0DEC, 0x080a0ded
.endif
.ifndef OMIT_func_080A11DC
.global func_080A11DC
.thumb_set func_080A11DC, 0x080a11dd
.endif
.ifndef OMIT_func_080A1B58
.global func_080A1B58
.thumb_set func_080A1B58, 0x080a1b59
.endif
.ifndef OMIT_func_080A1D84
.global func_080A1D84
.thumb_set func_080A1D84, 0x080a1d85
.endif
.ifndef OMIT_func_080A21B4
.global func_080A21B4
.thumb_set func_080A21B4, 0x080a21b5
.endif
.ifndef OMIT_func_080A2210
.global func_080A2210
.thumb_set func_080A2210, 0x080a2211
.endif
.ifndef OMIT_func_080A3778
.global func_080A3778
.thumb_set func_080A3778, 0x080a3779
.endif
.ifndef OMIT_func_080A40A0
.global func_080A40A0
.thumb_set func_080A40A0, 0x080a40a1
.endif
.ifndef OMIT_func_080A52D4
.global func_080A52D4
.thumb_set func_080A52D4, 0x080a52d5
.endif
.ifndef OMIT_func_080A54E0
.global func_080A54E0
.thumb_set func_080A54E0, 0x080a54e1
.endif
.ifndef OMIT_func_080A5B98
.global func_080A5B98
.thumb_set func_080A5B98, 0x080a5b99
.endif
.ifndef OMIT_func_080A6F20
.global func_080A6F20
.thumb_set func_080A6F20, 0x080a6f21
.endif
.ifndef OMIT_func_080A7040
.global func_080A7040
.thumb_set func_080A7040, 0x080a7041
.endif
.ifndef OMIT_func_080A7138
.global func_080A7138
.thumb_set func_080A7138, 0x080a7139
.endif
.ifndef OMIT_func_080A7218
.global func_080A7218
.thumb_set func_080A7218, 0x080a7219
.endif
.ifndef OMIT_func_080A75BC
.global func_080A75BC
.thumb_set func_080A75BC, 0x080a75bd
.endif
.ifndef OMIT_func_080A780C
.global func_080A780C
.thumb_set func_080A780C, 0x080a780d
.endif
.ifndef OMIT_func_080A7A80
.global func_080A7A80
.thumb_set func_080A7A80, 0x080a7a81
.endif
.ifndef OMIT_func_080A7C9C
.global func_080A7C9C
.thumb_set func_080A7C9C, 0x080a7c9d
.endif
.ifndef OMIT_func_080A7D60
.global func_080A7D60
.thumb_set func_080A7D60, 0x080a7d61
.endif
.ifndef OMIT_func_080A7DE0
.global func_080A7DE0
.thumb_set func_080A7DE0, 0x080a7de1
.endif
.ifndef OMIT_func_080A7FC4
.global func_080A7FC4
.thumb_set func_080A7FC4, 0x080a7fc5
.endif
.ifndef OMIT_func_080A7FE8
.global func_080A7FE8
.thumb_set func_080A7FE8, 0x080a7fe9
.endif
.ifndef OMIT_func_080A8264
.global func_080A8264
.thumb_set func_080A8264, 0x080a8265
.endif
.ifndef OMIT_func_080A8270
.global func_080A8270
.thumb_set func_080A8270, 0x080a8271
.endif
.ifndef OMIT_func_080A8288
.global func_080A8288
.thumb_set func_080A8288, 0x080a8289
.endif
.ifndef OMIT_func_080A8390
.global func_080A8390
.thumb_set func_080A8390, 0x080a8391
.endif
.ifndef OMIT_func_080A83A4
.global func_080A83A4
.thumb_set func_080A83A4, 0x080a83a5
.endif
.ifndef OMIT_func_080A86BC
.global func_080A86BC
.thumb_set func_080A86BC, 0x080a86bd
.endif
.ifndef OMIT_func_080A86EC
.global func_080A86EC
.thumb_set func_080A86EC, 0x080a86ed
.endif
.ifndef OMIT_func_080A87B4
.global func_080A87B4
.thumb_set func_080A87B4, 0x080a87b5
.endif
.ifndef OMIT_func_080A87DC
.global func_080A87DC
.thumb_set func_080A87DC, 0x080a87dd
.endif
.ifndef OMIT_func_080A8800
.global func_080A8800
.thumb_set func_080A8800, 0x080a8801
.endif
.ifndef OMIT_func_080A880C
.global func_080A880C
.thumb_set func_080A880C, 0x080a880d
.endif
.ifndef OMIT_func_080A8810
.global func_080A8810
.thumb_set func_080A8810, 0x080a8811
.endif
.ifndef OMIT_func_080A8830
.global func_080A8830
.thumb_set func_080A8830, 0x080a8831
.endif
.ifndef OMIT_func_080A883C
.global func_080A883C
.thumb_set func_080A883C, 0x080a883d
.endif
.ifndef OMIT_func_080A8858
.global func_080A8858
.thumb_set func_080A8858, 0x080a8859
.endif
.ifndef OMIT_func_080A88EC
.global func_080A88EC
.thumb_set func_080A88EC, 0x080a88ed
.endif
.ifndef OMIT_func_080A88FC
.global func_080A88FC
.thumb_set func_080A88FC, 0x080a88fd
.endif
.ifndef OMIT_func_080A8934
.global func_080A8934
.thumb_set func_080A8934, 0x080a8935
.endif
.ifndef OMIT_func_080A8940
.global func_080A8940
.thumb_set func_080A8940, 0x080a8941
.endif
.ifndef OMIT_func_080A8958
.global func_080A8958
.thumb_set func_080A8958, 0x080a8959
.endif
.ifndef OMIT_func_080A8990
.global func_080A8990
.thumb_set func_080A8990, 0x080a8991
.endif
.ifndef OMIT_func_080A899C
.global func_080A899C
.thumb_set func_080A899C, 0x080a899d
.endif
.ifndef OMIT_func_080A89D8
.global func_080A89D8
.thumb_set func_080A89D8, 0x080a89d9
.endif
.ifndef OMIT_func_080A8A54
.global func_080A8A54
.thumb_set func_080A8A54, 0x080a8a55
.endif
.ifndef OMIT_func_080A8A64
.global func_080A8A64
.thumb_set func_080A8A64, 0x080a8a65
.endif
.ifndef OMIT_func_080A8A68
.global func_080A8A68
.thumb_set func_080A8A68, 0x080a8a69
.endif
.ifndef OMIT_func_080A8A80
.global func_080A8A80
.thumb_set func_080A8A80, 0x080a8a81
.endif
.ifndef OMIT_func_080A8A90
.global func_080A8A90
.thumb_set func_080A8A90, 0x080a8a91
.endif
.ifndef OMIT_func_080A8AAC
.global func_080A8AAC
.thumb_set func_080A8AAC, 0x080a8aad
.endif
.ifndef OMIT_func_080A8AB8
.global func_080A8AB8
.thumb_set func_080A8AB8, 0x080a8ab9
.endif
.ifndef OMIT_func_080A8DB8
.global func_080A8DB8
.thumb_set func_080A8DB8, 0x080a8db9
.endif
.ifndef OMIT_func_080A8E0C
.global func_080A8E0C
.thumb_set func_080A8E0C, 0x080a8e0d
.endif
.ifndef OMIT_func_080A8FBC
.global func_080A8FBC
.thumb_set func_080A8FBC, 0x080a8fbd
.endif
.ifndef OMIT_func_080A901C
.global func_080A901C
.thumb_set func_080A901C, 0x080a901d
.endif
.ifndef OMIT_func_080A925C
.global func_080A925C
.thumb_set func_080A925C, 0x080a925d
.endif
.ifndef OMIT_func_080A9298
.global func_080A9298
.thumb_set func_080A9298, 0x080a9299
.endif
.ifndef OMIT_func_080A92E4
.global func_080A92E4
.thumb_set func_080A92E4, 0x080a92e5
.endif
.ifndef OMIT_func_080A9420
.global func_080A9420
.thumb_set func_080A9420, 0x080a9421
.endif
.ifndef OMIT_func_080A946C
.global func_080A946C
.thumb_set func_080A946C, 0x080a946d
.endif
.ifndef OMIT_func_080A9478
.global func_080A9478
.thumb_set func_080A9478, 0x080a9479
.endif
.ifndef OMIT_func_080A9484
.global func_080A9484
.thumb_set func_080A9484, 0x080a9485
.endif
.ifndef OMIT_func_080A94B8
.global func_080A94B8
.thumb_set func_080A94B8, 0x080a94b9
.endif
.ifndef OMIT_func_080A94D4
.global func_080A94D4
.thumb_set func_080A94D4, 0x080a94d5
.endif
.ifndef OMIT_func_080A9528
.global func_080A9528
.thumb_set func_080A9528, 0x080a9529
.endif
.ifndef OMIT_func_080A9538
.global func_080A9538
.thumb_set func_080A9538, 0x080a9539
.endif
.ifndef OMIT_func_080A9548
.global func_080A9548
.thumb_set func_080A9548, 0x080a9549
.endif
.ifndef OMIT_func_080A9588
.global func_080A9588
.thumb_set func_080A9588, 0x080a9589
.endif
.ifndef OMIT_func_080A95B0
.global func_080A95B0
.thumb_set func_080A95B0, 0x080a95b1
.endif
.ifndef OMIT_func_080A9BB8
.global func_080A9BB8
.thumb_set func_080A9BB8, 0x080a9bb9
.endif
.ifndef OMIT_func_080A9C80
.global func_080A9C80
.thumb_set func_080A9C80, 0x080a9c81
.endif
.ifndef OMIT_func_080A9E6C
.global func_080A9E6C
.thumb_set func_080A9E6C, 0x080a9e6d
.endif
.ifndef OMIT_func_080B4294
.global func_080B4294
.thumb_set func_080B4294, 0x080b4295
.endif
.ifndef OMIT_func_080B42E4
.global func_080B42E4
.thumb_set func_080B42E4, 0x080b42e5
.endif
.ifndef OMIT_func_080B43EC
.global func_080B43EC
.thumb_set func_080B43EC, 0x080b43ed
.endif
.ifndef OMIT_func_080B44F8
.global func_080B44F8
.thumb_set func_080B44F8, 0x080b44f9
.endif
.ifndef OMIT_func_080B4C90
.global func_080B4C90
.thumb_set func_080B4C90, 0x080b4c91
.endif
.ifndef OMIT_func_080B5278
.global func_080B5278
.thumb_set func_080B5278, 0x080b5279
.endif
.ifndef OMIT_func_080B5880
.global func_080B5880
.thumb_set func_080B5880, 0x080b5881
.endif
.ifndef OMIT_func_080B5A08
.global func_080B5A08
.thumb_set func_080B5A08, 0x080b5a09
.endif
.ifndef OMIT_func_080B7C2C
.global func_080B7C2C
.thumb_set func_080B7C2C, 0x080b7c2d
.endif
.ifndef OMIT_func_080B7C50
.global func_080B7C50
.thumb_set func_080B7C50, 0x080b7c51
.endif
.ifndef OMIT_func_080B7C94
.global func_080B7C94
.thumb_set func_080B7C94, 0x080b7c95
.endif
.ifndef OMIT_func_080B7DC8
.global func_080B7DC8
.thumb_set func_080B7DC8, 0x080b7dc9
.endif
.ifndef OMIT_func_080B7E08
.global func_080B7E08
.thumb_set func_080B7E08, 0x080b7e09
.endif
.ifndef OMIT_func_080B7E1C
.global func_080B7E1C
.thumb_set func_080B7E1C, 0x080b7e1d
.endif
.ifndef OMIT_func_080B7E7C
.global func_080B7E7C
.thumb_set func_080B7E7C, 0x080b7e7d
.endif
.ifndef OMIT_func_080B7EA0
.global func_080B7EA0
.thumb_set func_080B7EA0, 0x080b7ea1
.endif
.ifndef OMIT_func_080B7EDC
.global func_080B7EDC
.thumb_set func_080B7EDC, 0x080b7edd
.endif
.ifndef OMIT_func_080B7EFC
.global func_080B7EFC
.thumb_set func_080B7EFC, 0x080b7efd
.endif
.ifndef OMIT_func_080B7F4C
.global func_080B7F4C
.thumb_set func_080B7F4C, 0x080b7f4d
.endif
.ifndef OMIT_func_080B7F74
.global func_080B7F74
.thumb_set func_080B7F74, 0x080b7f75
.endif
.ifndef OMIT_func_080BA6D0
.global func_080BA6D0
.thumb_set func_080BA6D0, 0x080ba6d1
.endif
.ifndef OMIT_func_080BA6E4
.global func_080BA6E4
.thumb_set func_080BA6E4, 0x080ba6e5
.endif
.ifndef OMIT_func_080BA728
.global func_080BA728
.thumb_set func_080BA728, 0x080ba729
.endif
.ifndef OMIT_func_080BA7D8
.global func_080BA7D8
.thumb_set func_080BA7D8, 0x080ba7d9
.endif
.ifndef OMIT_func_080BA8A4
.global func_080BA8A4
.thumb_set func_080BA8A4, 0x080ba8a5
.endif
.ifndef OMIT_func_080BAB90
.global func_080BAB90
.thumb_set func_080BAB90, 0x080bab91
.endif
.ifndef OMIT_func_080BACF0
.global func_080BACF0
.thumb_set func_080BACF0, 0x080bacf1
.endif
.ifndef OMIT_func_080BB370
.global func_080BB370
.thumb_set func_080BB370, 0x080bb371
.endif
.ifndef OMIT_func_080BB4F8
.global func_080BB4F8
.thumb_set func_080BB4F8, 0x080bb4f9
.endif
.ifndef OMIT_func_080BB5C4
.global func_080BB5C4
.thumb_set func_080BB5C4, 0x080bb5c5
.endif
.ifndef OMIT_func_080BBBB0
.global func_080BBBB0
.thumb_set func_080BBBB0, 0x080bbbb1
.endif
.ifndef OMIT_func_080BBC38
.global func_080BBC38
.thumb_set func_080BBC38, 0x080bbc39
.endif
.ifndef OMIT_func_080BBD34
.global func_080BBD34
.thumb_set func_080BBD34, 0x080bbd35
.endif
.ifndef OMIT_func_080BBE00
.global func_080BBE00
.thumb_set func_080BBE00, 0x080bbe01
.endif
.ifndef OMIT_func_080BC3B0
.global func_080BC3B0
.thumb_set func_080BC3B0, 0x080bc3b1
.endif
.ifndef OMIT_func_080BC4BC
.global func_080BC4BC
.thumb_set func_080BC4BC, 0x080bc4bd
.endif
.ifndef OMIT_func_080BC584
.global func_080BC584
.thumb_set func_080BC584, 0x080bc585
.endif
.ifndef OMIT_func_080BC780
.global func_080BC780
.thumb_set func_080BC780, 0x080bc781
.endif
.ifndef OMIT_func_080BC7AC
.global func_080BC7AC
.thumb_set func_080BC7AC, 0x080bc7ad
.endif
.ifndef OMIT_func_080BC7D4
.global func_080BC7D4
.thumb_set func_080BC7D4, 0x080bc7d5
.endif
.ifndef OMIT_func_080BC810
.global func_080BC810
.thumb_set func_080BC810, 0x080bc811
.endif
.ifndef OMIT_func_080BC878
.global func_080BC878
.thumb_set func_080BC878, 0x080bc879
.endif
.ifndef OMIT_func_080BC8C4
.global func_080BC8C4
.thumb_set func_080BC8C4, 0x080bc8c5
.endif
.ifndef OMIT_func_080BC8E8
.global func_080BC8E8
.thumb_set func_080BC8E8, 0x080bc8e9
.endif
.ifndef OMIT_func_080BC914
.global func_080BC914
.thumb_set func_080BC914, 0x080bc915
.endif
.ifndef OMIT_func_080BC934
.global func_080BC934
.thumb_set func_080BC934, 0x080bc935
.endif
.ifndef OMIT_func_080BC944
.global func_080BC944
.thumb_set func_080BC944, 0x080bc945
.endif
.ifndef OMIT_func_080BC950
.global func_080BC950
.thumb_set func_080BC950, 0x080bc951
.endif
.ifndef OMIT_func_080BC984
.global func_080BC984
.thumb_set func_080BC984, 0x080bc985
.endif
.ifndef OMIT_func_080BC994
.global func_080BC994
.thumb_set func_080BC994, 0x080bc995
.endif
.ifndef OMIT_func_080BC9CC
.global func_080BC9CC
.thumb_set func_080BC9CC, 0x080bc9cd
.endif
.ifndef OMIT_func_080BC9E4
.global func_080BC9E4
.thumb_set func_080BC9E4, 0x080bc9e5
.endif
.ifndef OMIT_func_080BCA24
.global func_080BCA24
.thumb_set func_080BCA24, 0x080bca25
.endif
.ifndef OMIT_func_080BCA40
.global func_080BCA40
.thumb_set func_080BCA40, 0x080bca41
.endif
.ifndef OMIT_func_080BCA54
.global func_080BCA54
.thumb_set func_080BCA54, 0x080bca55
.endif
.ifndef OMIT_func_080BCDF8
.global func_080BCDF8
.thumb_set func_080BCDF8, 0x080bcdf9
.endif
.ifndef OMIT_func_080BCED0
.global func_080BCED0
.thumb_set func_080BCED0, 0x080bced1
.endif
.ifndef OMIT_func_080BD02C
.global func_080BD02C
.thumb_set func_080BD02C, 0x080bd02d
.endif
.ifndef OMIT_func_080BD06C
.global func_080BD06C
.thumb_set func_080BD06C, 0x080bd06d
.endif
.ifndef OMIT_func_080BD11C
.global func_080BD11C
.thumb_set func_080BD11C, 0x080bd11d
.endif
.ifndef OMIT_func_080BD130
.global func_080BD130
.thumb_set func_080BD130, 0x080bd131
.endif
.ifndef OMIT_func_080BD14C
.global func_080BD14C
.thumb_set func_080BD14C, 0x080bd14d
.endif
.ifndef OMIT_func_080BD1EC
.global func_080BD1EC
.thumb_set func_080BD1EC, 0x080bd1ed
.endif
.ifndef OMIT_func_080BD328
.global func_080BD328
.thumb_set func_080BD328, 0x080bd329
.endif
.ifndef OMIT_func_080BD340
.global func_080BD340
.thumb_set func_080BD340, 0x080bd341
.endif
.ifndef OMIT_func_080BD34C
.global func_080BD34C
.thumb_set func_080BD34C, 0x080bd34d
.endif
.ifndef OMIT_func_080BD35C
.global func_080BD35C
.thumb_set func_080BD35C, 0x080bd35d
.endif
.ifndef OMIT_func_080BD8CC
.global func_080BD8CC
.thumb_set func_080BD8CC, 0x080bd8cd
.endif
.ifndef OMIT_func_080BDAFC
.global func_080BDAFC
.thumb_set func_080BDAFC, 0x080bdafd
.endif
.ifndef OMIT_func_080BDB18
.global func_080BDB18
.thumb_set func_080BDB18, 0x080bdb19
.endif
.ifndef OMIT_func_080BDB2C
.global func_080BDB2C
.thumb_set func_080BDB2C, 0x080bdb2d
.endif
.ifndef OMIT_func_080BDB60
.global func_080BDB60
.thumb_set func_080BDB60, 0x080bdb61
.endif
.ifndef OMIT_func_080BDB64
.global func_080BDB64
.thumb_set func_080BDB64, 0x080bdb65
.endif
.ifndef OMIT_func_080BDB68
.global func_080BDB68
.thumb_set func_080BDB68, 0x080bdb69
.endif
.ifndef OMIT_func_080BDB6C
.global func_080BDB6C
.thumb_set func_080BDB6C, 0x080bdb6d
.endif
.ifndef OMIT_func_080BDB74
.global func_080BDB74
.thumb_set func_080BDB74, 0x080bdb75
.endif
.ifndef OMIT_func_080BDB78
.global func_080BDB78
.thumb_set func_080BDB78, 0x080bdb79
.endif
.ifndef OMIT_func_080BDB9C
.global func_080BDB9C
.thumb_set func_080BDB9C, 0x080bdb9d
.endif
.ifndef OMIT_func_080BDBAC
.global func_080BDBAC
.thumb_set func_080BDBAC, 0x080bdbad
.endif
.ifndef OMIT_func_080BDBC4
.global func_080BDBC4
.thumb_set func_080BDBC4, 0x080bdbc5
.endif
.ifndef OMIT_func_080BDC20
.global func_080BDC20
.thumb_set func_080BDC20, 0x080bdc21
.endif
.ifndef OMIT_func_080BDC44
.global func_080BDC44
.thumb_set func_080BDC44, 0x080bdc45
.endif
.ifndef OMIT_func_080BDC98
.global func_080BDC98
.thumb_set func_080BDC98, 0x080bdc99
.endif
.ifndef OMIT_func_080BDCD0
.global func_080BDCD0
.thumb_set func_080BDCD0, 0x080bdcd1
.endif
.ifndef OMIT_func_080BDD40
.global func_080BDD40
.thumb_set func_080BDD40, 0x080bdd41
.endif
.ifndef OMIT_func_080BDD50
.global func_080BDD50
.thumb_set func_080BDD50, 0x080bdd51
.endif
.ifndef OMIT_func_080BDD5C
.global func_080BDD5C
.thumb_set func_080BDD5C, 0x080bdd5d
.endif
.ifndef OMIT_func_080BDD70
.global func_080BDD70
.thumb_set func_080BDD70, 0x080bdd71
.endif
.ifndef OMIT_func_080BDECC
.global func_080BDECC
.thumb_set func_080BDECC, 0x080bdecd
.endif
.ifndef OMIT_func_080BE3B8
.global func_080BE3B8
.thumb_set func_080BE3B8, 0x080be3b9
.endif
.ifndef OMIT_func_080BE494
.global func_080BE494
.thumb_set func_080BE494, 0x080be495
.endif
.ifndef OMIT_func_080C127C
.global func_080C127C
.thumb_set func_080C127C, 0x080c127d
.endif
.ifndef OMIT_func_080C1484
.global func_080C1484
.thumb_set func_080C1484, 0x080c1485
.endif
.ifndef OMIT_func_080C156C
.global func_080C156C
.thumb_set func_080C156C, 0x080c156d
.endif
.ifndef OMIT_func_080C15C0
.global func_080C15C0
.thumb_set func_080C15C0, 0x080c15c1
.endif
.ifndef OMIT_func_080C1B2C
.global func_080C1B2C
.thumb_set func_080C1B2C, 0x080c1b2d
.endif
.ifndef OMIT_func_080C2314
.global func_080C2314
.thumb_set func_080C2314, 0x080c2315
.endif
.ifndef OMIT_func_080C2618
.global func_080C2618
.thumb_set func_080C2618, 0x080c2619
.endif
.ifndef OMIT_func_080C286C
.global func_080C286C
.thumb_set func_080C286C, 0x080c286d
.endif
.ifndef OMIT_func_080C47FC
.global func_080C47FC
.thumb_set func_080C47FC, 0x080c47fd
.endif
.ifndef OMIT_func_080C4964
.global func_080C4964
.thumb_set func_080C4964, 0x080c4965
.endif
.ifndef OMIT_func_080C4A40
.global func_080C4A40
.thumb_set func_080C4A40, 0x080c4a41
.endif
.ifndef OMIT_func_080C4B20
.global func_080C4B20
.thumb_set func_080C4B20, 0x080c4b21
.endif
.ifndef OMIT_func_080C5320
.global func_080C5320
.thumb_set func_080C5320, 0x080c5321
.endif
.ifndef OMIT_func_080C5398
.global func_080C5398
.thumb_set func_080C5398, 0x080c5399
.endif
.ifndef OMIT_func_080C5420
.global func_080C5420
.thumb_set func_080C5420, 0x080c5421
.endif
.ifndef OMIT_func_080C5428
.global func_080C5428
.thumb_set func_080C5428, 0x080c5429
.endif
.ifndef OMIT_func_080C5434
.global func_080C5434
.thumb_set func_080C5434, 0x080c5435
.endif
.ifndef OMIT_func_080C5438
.global func_080C5438
.thumb_set func_080C5438, 0x080c5439
.endif
.ifndef OMIT_func_080C5448
.global func_080C5448
.thumb_set func_080C5448, 0x080c5449
.endif
.ifndef OMIT_func_080C55D8
.global func_080C55D8
.thumb_set func_080C55D8, 0x080c55d9
.endif
.ifndef OMIT_func_080C566C
.global func_080C566C
.thumb_set func_080C566C, 0x080c566d
.endif
.ifndef OMIT_func_080C56E8
.global func_080C56E8
.thumb_set func_080C56E8, 0x080c56e9
.endif
.ifndef OMIT_func_080C5774
.global func_080C5774
.thumb_set func_080C5774, 0x080c5775
.endif
.ifndef OMIT_func_080C586C
.global func_080C586C
.thumb_set func_080C586C, 0x080c586d
.endif
.ifndef OMIT_func_080C5D60
.global func_080C5D60
.thumb_set func_080C5D60, 0x080c5d61
.endif
.ifndef OMIT_func_080C5F94
.global func_080C5F94
.thumb_set func_080C5F94, 0x080c5f95
.endif
.ifndef OMIT_func_080C62CC
.global func_080C62CC
.thumb_set func_080C62CC, 0x080c62cd
.endif
.ifndef OMIT_func_080C6480
.global func_080C6480
.thumb_set func_080C6480, 0x080c6481
.endif
.ifndef OMIT_func_080C71B4
.global func_080C71B4
.thumb_set func_080C71B4, 0x080c71b5
.endif
.ifndef OMIT_func_080C7214
.global func_080C7214
.thumb_set func_080C7214, 0x080c7215
.endif
.ifndef OMIT_func_080C7240
.global func_080C7240
.thumb_set func_080C7240, 0x080c7241
.endif
.ifndef OMIT_func_080C7260
.global func_080C7260
.thumb_set func_080C7260, 0x080c7261
.endif
.ifndef OMIT_func_080C7284
.global func_080C7284
.thumb_set func_080C7284, 0x080c7285
.endif
.ifndef OMIT_func_080C72B0
.global func_080C72B0
.thumb_set func_080C72B0, 0x080c72b1
.endif
.ifndef OMIT_func_080C72E4
.global func_080C72E4
.thumb_set func_080C72E4, 0x080c72e5
.endif
.ifndef OMIT_func_080C72F8
.global func_080C72F8
.thumb_set func_080C72F8, 0x080c72f9
.endif
.ifndef OMIT_func_080C7378
.global func_080C7378
.thumb_set func_080C7378, 0x080c7379
.endif
.ifndef OMIT_func_080C738C
.global func_080C738C
.thumb_set func_080C738C, 0x080c738d
.endif
.ifndef OMIT_func_080C73C4
.global func_080C73C4
.thumb_set func_080C73C4, 0x080c73c5
.endif
.ifndef OMIT_func_080C73D8
.global func_080C73D8
.thumb_set func_080C73D8, 0x080c73d9
.endif
.ifndef OMIT_func_080C746C
.global func_080C746C
.thumb_set func_080C746C, 0x080c746d
.endif
.ifndef OMIT_func_080C7484
.global func_080C7484
.thumb_set func_080C7484, 0x080c7485
.endif
.ifndef OMIT_func_080C74B4
.global func_080C74B4
.thumb_set func_080C74B4, 0x080c74b5
.endif
.ifndef OMIT_func_080C7548
.global func_080C7548
.thumb_set func_080C7548, 0x080c7549
.endif
.ifndef OMIT_func_080C7610
.global func_080C7610
.thumb_set func_080C7610, 0x080c7611
.endif
.ifndef OMIT_func_080C779C
.global func_080C779C
.thumb_set func_080C779C, 0x080c779d
.endif
.ifndef OMIT_func_080C77C0
.global func_080C77C0
.thumb_set func_080C77C0, 0x080c77c1
.endif
.ifndef OMIT_func_080C780C
.global func_080C780C
.thumb_set func_080C780C, 0x080c780d
.endif
.ifndef OMIT_func_080C7858
.global func_080C7858
.thumb_set func_080C7858, 0x080c7859
.endif
.ifndef OMIT_func_080C7908
.global func_080C7908
.thumb_set func_080C7908, 0x080c7909
.endif
.ifndef OMIT_func_080C799C
.global func_080C799C
.thumb_set func_080C799C, 0x080c799d
.endif
.ifndef OMIT_func_080C79B4
.global func_080C79B4
.thumb_set func_080C79B4, 0x080c79b5
.endif
.ifndef OMIT_func_080C79E0
.global func_080C79E0
.thumb_set func_080C79E0, 0x080c79e1
.endif
.ifndef OMIT_func_080C7A34
.global func_080C7A34
.thumb_set func_080C7A34, 0x080c7a35
.endif
.ifndef OMIT_func_080C7A5C
.global func_080C7A5C
.thumb_set func_080C7A5C, 0x080c7a5d
.endif
.ifndef OMIT_func_080C7A74
.global func_080C7A74
.thumb_set func_080C7A74, 0x080c7a75
.endif
.ifndef OMIT_func_080C7AB4
.global func_080C7AB4
.thumb_set func_080C7AB4, 0x080c7ab5
.endif
.ifndef OMIT_func_080C7B08
.global func_080C7B08
.thumb_set func_080C7B08, 0x080c7b09
.endif
.ifndef OMIT_func_080C7B20
.global func_080C7B20
.thumb_set func_080C7B20, 0x080c7b21
.endif
.ifndef OMIT_func_080C7B74
.global func_080C7B74
.thumb_set func_080C7B74, 0x080c7b75
.endif
.ifndef OMIT_func_080C7B78
.global func_080C7B78
.thumb_set func_080C7B78, 0x080c7b79
.endif
.ifndef OMIT_func_080C7BF4
.global func_080C7BF4
.thumb_set func_080C7BF4, 0x080c7bf5
.endif
.ifndef OMIT_func_080C7C14
.global func_080C7C14
.thumb_set func_080C7C14, 0x080c7c15
.endif
.ifndef OMIT_func_080C7C40
.global func_080C7C40
.thumb_set func_080C7C40, 0x080c7c41
.endif
.ifndef OMIT_func_080C7CC0
.global func_080C7CC0
.thumb_set func_080C7CC0, 0x080c7cc1
.endif
.ifndef OMIT_func_080C7CE4
.global func_080C7CE4
.thumb_set func_080C7CE4, 0x080c7ce5
.endif
.ifndef OMIT_func_080C7D18
.global func_080C7D18
.thumb_set func_080C7D18, 0x080c7d19
.endif
.ifndef OMIT_func_080C7D70
.global func_080C7D70
.thumb_set func_080C7D70, 0x080c7d71
.endif
.ifndef OMIT_func_080C7DC8
.global func_080C7DC8
.thumb_set func_080C7DC8, 0x080c7dc9
.endif
.ifndef OMIT_func_080C7E78
.global func_080C7E78
.thumb_set func_080C7E78, 0x080c7e79
.endif
.ifndef OMIT_func_080C7EA4
.global func_080C7EA4
.thumb_set func_080C7EA4, 0x080c7ea5
.endif
.ifndef OMIT_func_080C817C
.global func_080C817C
.thumb_set func_080C817C, 0x080c817d
.endif
.ifndef OMIT_func_080C8194
.global func_080C8194
.thumb_set func_080C8194, 0x080c8195
.endif
.ifndef OMIT_func_080C81B0
.global func_080C81B0
.thumb_set func_080C81B0, 0x080c81b1
.endif
.ifndef OMIT_func_080C81C8
.global func_080C81C8
.thumb_set func_080C81C8, 0x080c81c9
.endif
.ifndef OMIT_func_080C81E0
.global func_080C81E0
.thumb_set func_080C81E0, 0x080c81e1
.endif
.ifndef OMIT_func_080C81F8
.global func_080C81F8
.thumb_set func_080C81F8, 0x080c81f9
.endif
.ifndef OMIT_func_080C8210
.global func_080C8210
.thumb_set func_080C8210, 0x080c8211
.endif
.ifndef OMIT_func_080C8228
.global func_080C8228
.thumb_set func_080C8228, 0x080c8229
.endif
.ifndef OMIT_func_080C8240
.global func_080C8240
.thumb_set func_080C8240, 0x080c8241
.endif
.ifndef OMIT_func_080C8260
.global func_080C8260
.thumb_set func_080C8260, 0x080c8261
.endif
.ifndef OMIT_func_080C8280
.global func_080C8280
.thumb_set func_080C8280, 0x080c8281
.endif
.ifndef OMIT_func_080C8298
.global func_080C8298
.thumb_set func_080C8298, 0x080c8299
.endif
.ifndef OMIT_func_080C82B8
.global func_080C82B8
.thumb_set func_080C82B8, 0x080c82b9
.endif
.ifndef OMIT_func_080C82D8
.global func_080C82D8
.thumb_set func_080C82D8, 0x080c82d9
.endif
.ifndef OMIT_func_080C82F4
.global func_080C82F4
.thumb_set func_080C82F4, 0x080c82f5
.endif
.ifndef OMIT_func_080C8310
.global func_080C8310
.thumb_set func_080C8310, 0x080c8311
.endif
.ifndef OMIT_func_080C832C
.global func_080C832C
.thumb_set func_080C832C, 0x080c832d
.endif
.ifndef OMIT_func_080C8348
.global func_080C8348
.thumb_set func_080C8348, 0x080c8349
.endif
.ifndef OMIT_func_080C8364
.global func_080C8364
.thumb_set func_080C8364, 0x080c8365
.endif
.ifndef OMIT_func_080C8384
.global func_080C8384
.thumb_set func_080C8384, 0x080c8385
.endif
.ifndef OMIT_func_080C83A4
.global func_080C83A4
.thumb_set func_080C83A4, 0x080c83a5
.endif
.ifndef OMIT_func_080C83CC
.global func_080C83CC
.thumb_set func_080C83CC, 0x080c83cd
.endif
.ifndef OMIT_func_080C841C
.global func_080C841C
.thumb_set func_080C841C, 0x080c841d
.endif
.ifndef OMIT_func_080C84C0
.global func_080C84C0
.thumb_set func_080C84C0, 0x080c84c1
.endif
.ifndef OMIT_func_080C84F4
.global func_080C84F4
.thumb_set func_080C84F4, 0x080c84f5
.endif
.ifndef OMIT_func_080C8530
.global func_080C8530
.thumb_set func_080C8530, 0x080c8531
.endif
.ifndef OMIT_func_080C8570
.global func_080C8570
.thumb_set func_080C8570, 0x080c8571
.endif
.ifndef OMIT_func_080C8A24
.global func_080C8A24
.thumb_set func_080C8A24, 0x080c8a25
.endif
.ifndef OMIT_func_080C8C24
.global func_080C8C24
.thumb_set func_080C8C24, 0x080c8c25
.endif
.ifndef OMIT_func_080C9078
.global func_080C9078
.thumb_set func_080C9078, 0x080c9079
.endif
.ifndef OMIT_func_080C9134
.global func_080C9134
.thumb_set func_080C9134, 0x080c9135
.endif
.ifndef OMIT_func_080C92F0
.global func_080C92F0
.thumb_set func_080C92F0, 0x080c92f1
.endif
.ifndef OMIT_func_080C9314
.global func_080C9314
.thumb_set func_080C9314, 0x080c9315
.endif
.ifndef OMIT_func_080C9340
.global func_080C9340
.thumb_set func_080C9340, 0x080c9341
.endif
.ifndef OMIT_func_080C93C8
.global func_080C93C8
.thumb_set func_080C93C8, 0x080c93c9
.endif
.ifndef OMIT_func_080C93F0
.global func_080C93F0
.thumb_set func_080C93F0, 0x080c93f1
.endif
.ifndef OMIT_func_080C9400
.global func_080C9400
.thumb_set func_080C9400, 0x080c9401
.endif
.ifndef OMIT_func_080C9428
.global func_080C9428
.thumb_set func_080C9428, 0x080c9429
.endif
.ifndef OMIT_func_080C9460
.global func_080C9460
.thumb_set func_080C9460, 0x080c9461
.endif
.ifndef OMIT_func_080C94D0
.global func_080C94D0
.thumb_set func_080C94D0, 0x080c94d1
.endif
.ifndef OMIT_func_080C9540
.global func_080C9540
.thumb_set func_080C9540, 0x080c9541
.endif
.ifndef OMIT_func_080C9574
.global func_080C9574
.thumb_set func_080C9574, 0x080c9575
.endif
.ifndef OMIT_func_080C95A8
.global func_080C95A8
.thumb_set func_080C95A8, 0x080c95a9
.endif
.ifndef OMIT_func_080C95C0
.global func_080C95C0
.thumb_set func_080C95C0, 0x080c95c1
.endif
.ifndef OMIT_func_080C95D8
.global func_080C95D8
.thumb_set func_080C95D8, 0x080c95d9
.endif
.ifndef OMIT_func_080C960C
.global func_080C960C
.thumb_set func_080C960C, 0x080c960d
.endif
.ifndef OMIT_func_080C9644
.global func_080C9644
.thumb_set func_080C9644, 0x080c9645
.endif
.ifndef OMIT_func_080C9B8C
.global func_080C9B8C
.thumb_set func_080C9B8C, 0x080c9b8d
.endif
.ifndef OMIT_func_080C9ED8
.global func_080C9ED8
.thumb_set func_080C9ED8, 0x080c9ed9
.endif
.ifndef OMIT_func_080C9F88
.global func_080C9F88
.thumb_set func_080C9F88, 0x080c9f89
.endif
.ifndef OMIT_func_080CA0BC
.global func_080CA0BC
.thumb_set func_080CA0BC, 0x080ca0bd
.endif
.ifndef OMIT_func_080CA0F8
.global func_080CA0F8
.thumb_set func_080CA0F8, 0x080ca0f9
.endif
.ifndef OMIT_func_080CA150
.global func_080CA150
.thumb_set func_080CA150, 0x080ca151
.endif
.ifndef OMIT_func_080CA1BC
.global func_080CA1BC
.thumb_set func_080CA1BC, 0x080ca1bd
.endif
.ifndef OMIT_func_080CA1F0
.global func_080CA1F0
.thumb_set func_080CA1F0, 0x080ca1f1
.endif
.ifndef OMIT_func_080CA268
.global func_080CA268
.thumb_set func_080CA268, 0x080ca269
.endif
.ifndef OMIT_func_080CA2E8
.global func_080CA2E8
.thumb_set func_080CA2E8, 0x080ca2e9
.endif
.ifndef OMIT_func_080CA394
.global func_080CA394
.thumb_set func_080CA394, 0x080ca395
.endif
.ifndef OMIT_func_080CA3EC
.global func_080CA3EC
.thumb_set func_080CA3EC, 0x080ca3ed
.endif
.ifndef OMIT_func_080CA400
.global func_080CA400
.thumb_set func_080CA400, 0x080ca401
.endif
.ifndef OMIT_func_080CA438
.global func_080CA438
.thumb_set func_080CA438, 0x080ca439
.endif
.ifndef OMIT_func_080CA478
.global func_080CA478
.thumb_set func_080CA478, 0x080ca479
.endif
.ifndef OMIT_func_080CA4B0
.global func_080CA4B0
.thumb_set func_080CA4B0, 0x080ca4b1
.endif
.ifndef OMIT_func_080CA4F0
.global func_080CA4F0
.thumb_set func_080CA4F0, 0x080ca4f1
.endif
.ifndef OMIT_func_080CA520
.global func_080CA520
.thumb_set func_080CA520, 0x080ca521
.endif
.ifndef OMIT_func_080CA538
.global func_080CA538
.thumb_set func_080CA538, 0x080ca539
.endif
.ifndef OMIT_func_080CA550
.global func_080CA550
.thumb_set func_080CA550, 0x080ca551
.endif
.ifndef OMIT_func_080CA568
.global func_080CA568
.thumb_set func_080CA568, 0x080ca569
.endif
.ifndef OMIT_func_080CA580
.global func_080CA580
.thumb_set func_080CA580, 0x080ca581
.endif
.ifndef OMIT_func_080CA5C4
.global func_080CA5C4
.thumb_set func_080CA5C4, 0x080ca5c5
.endif
.ifndef OMIT_func_080CA610
.global func_080CA610
.thumb_set func_080CA610, 0x080ca611
.endif
.ifndef OMIT_func_080CA624
.global func_080CA624
.thumb_set func_080CA624, 0x080ca625
.endif
.ifndef OMIT_func_080CA66C
.global func_080CA66C
.thumb_set func_080CA66C, 0x080ca66d
.endif
.ifndef OMIT_func_080CA6B4
.global func_080CA6B4
.thumb_set func_080CA6B4, 0x080ca6b5
.endif
.ifndef OMIT_func_080CA6FC
.global func_080CA6FC
.thumb_set func_080CA6FC, 0x080ca6fd
.endif
.ifndef OMIT_func_080CA744
.global func_080CA744
.thumb_set func_080CA744, 0x080ca745
.endif
.ifndef OMIT_func_080CA7A4
.global func_080CA7A4
.thumb_set func_080CA7A4, 0x080ca7a5
.endif
.ifndef OMIT_func_080CA900
.global func_080CA900
.thumb_set func_080CA900, 0x080ca901
.endif
.ifndef OMIT_func_080CA9E8
.global func_080CA9E8
.thumb_set func_080CA9E8, 0x080ca9e9
.endif
.ifndef OMIT_func_080CAA74
.global func_080CAA74
.thumb_set func_080CAA74, 0x080caa75
.endif
.ifndef OMIT_func_080CAB24
.global func_080CAB24
.thumb_set func_080CAB24, 0x080cab25
.endif
.ifndef OMIT_func_080CAE2C
.global func_080CAE2C
.thumb_set func_080CAE2C, 0x080cae2d
.endif
.ifndef OMIT_func_080CAF78
.global func_080CAF78
.thumb_set func_080CAF78, 0x080caf79
.endif
.ifndef OMIT_func_080CB0D8
.global func_080CB0D8
.thumb_set func_080CB0D8, 0x080cb0d9
.endif
.ifndef OMIT_func_080CB1F4
.global func_080CB1F4
.thumb_set func_080CB1F4, 0x080cb1f5
.endif
.ifndef OMIT_func_080CB210
.global func_080CB210
.thumb_set func_080CB210, 0x080cb211
.endif
.ifndef OMIT_func_080CB24C
.global func_080CB24C
.thumb_set func_080CB24C, 0x080cb24d
.endif
.ifndef OMIT_func_080CB27C
.global func_080CB27C
.thumb_set func_080CB27C, 0x080cb27d
.endif
.ifndef OMIT_func_080CB2B4
.global func_080CB2B4
.thumb_set func_080CB2B4, 0x080cb2b5
.endif
.ifndef OMIT_func_080CB388
.global func_080CB388
.thumb_set func_080CB388, 0x080cb389
.endif
.ifndef OMIT_func_080CB450
.global func_080CB450
.thumb_set func_080CB450, 0x080cb451
.endif
.ifndef OMIT_func_080CB48C
.global func_080CB48C
.thumb_set func_080CB48C, 0x080cb48d
.endif
.ifndef OMIT_func_080CB4A4
.global func_080CB4A4
.thumb_set func_080CB4A4, 0x080cb4a5
.endif
.ifndef OMIT_func_080CB4C0
.global func_080CB4C0
.thumb_set func_080CB4C0, 0x080cb4c1
.endif
.ifndef OMIT_func_080CB4E0
.global func_080CB4E0
.thumb_set func_080CB4E0, 0x080cb4e1
.endif
.ifndef OMIT_func_080CB524
.global func_080CB524
.thumb_set func_080CB524, 0x080cb525
.endif
.ifndef OMIT_func_080CB53C
.global func_080CB53C
.thumb_set func_080CB53C, 0x080cb53d
.endif
.ifndef OMIT_func_080CB54C
.global func_080CB54C
.thumb_set func_080CB54C, 0x080cb54d
.endif
.ifndef OMIT_func_080CB5A8
.global func_080CB5A8
.thumb_set func_080CB5A8, 0x080cb5a9
.endif
.ifndef OMIT_func_080CB644
.global func_080CB644
.thumb_set func_080CB644, 0x080cb645
.endif
.ifndef OMIT_func_080CB65C
.global func_080CB65C
.thumb_set func_080CB65C, 0x080cb65d
.endif
.ifndef OMIT_func_080CB714
.global func_080CB714
.thumb_set func_080CB714, 0x080cb715
.endif
.ifndef OMIT_func_080CB750
.global func_080CB750
.thumb_set func_080CB750, 0x080cb751
.endif
.ifndef OMIT_func_080CB7C0
.global func_080CB7C0
.thumb_set func_080CB7C0, 0x080cb7c1
.endif
.ifndef OMIT_func_080CB808
.global func_080CB808
.thumb_set func_080CB808, 0x080cb809
.endif
.ifndef OMIT_func_080CB84C
.global func_080CB84C
.thumb_set func_080CB84C, 0x080cb84d
.endif
.ifndef OMIT_func_080CB868
.global func_080CB868
.thumb_set func_080CB868, 0x080cb869
.endif
.ifndef OMIT_func_080CB8B4
.global func_080CB8B4
.thumb_set func_080CB8B4, 0x080cb8b5
.endif
.ifndef OMIT_func_080CB8D4
.global func_080CB8D4
.thumb_set func_080CB8D4, 0x080cb8d5
.endif
.ifndef OMIT_func_080CB928
.global func_080CB928
.thumb_set func_080CB928, 0x080cb929
.endif
.ifndef OMIT_func_080CB968
.global func_080CB968
.thumb_set func_080CB968, 0x080cb969
.endif
.ifndef OMIT_func_080CB980
.global func_080CB980
.thumb_set func_080CB980, 0x080cb981
.endif
.ifndef OMIT_func_080CB99C
.global func_080CB99C
.thumb_set func_080CB99C, 0x080cb99d
.endif
.ifndef OMIT_func_080CB9B0
.global func_080CB9B0
.thumb_set func_080CB9B0, 0x080cb9b1
.endif
.ifndef OMIT_func_080CB9CC
.global func_080CB9CC
.thumb_set func_080CB9CC, 0x080cb9cd
.endif
.ifndef OMIT_func_080CB9E0
.global func_080CB9E0
.thumb_set func_080CB9E0, 0x080cb9e1
.endif
.ifndef OMIT_func_080CBA14
.global func_080CBA14
.thumb_set func_080CBA14, 0x080cba15
.endif
.ifndef OMIT_func_080CBA3C
.global func_080CBA3C
.thumb_set func_080CBA3C, 0x080cba3d
.endif
.ifndef OMIT_func_080CBA84
.global func_080CBA84
.thumb_set func_080CBA84, 0x080cba85
.endif
.ifndef OMIT_func_080CBABC
.global func_080CBABC
.thumb_set func_080CBABC, 0x080cbabd
.endif
.ifndef OMIT_func_080CBB7C
.global func_080CBB7C
.thumb_set func_080CBB7C, 0x080cbb7d
.endif
.ifndef OMIT_func_080CBBC4
.global func_080CBBC4
.thumb_set func_080CBBC4, 0x080cbbc5
.endif
.ifndef OMIT_func_080CBC14
.global func_080CBC14
.thumb_set func_080CBC14, 0x080cbc15
.endif
.ifndef OMIT_func_080CBD34
.global func_080CBD34
.thumb_set func_080CBD34, 0x080cbd35
.endif
.ifndef OMIT_func_080CC198
.global func_080CC198
.thumb_set func_080CC198, 0x080cc199
.endif
.ifndef OMIT_func_080CC6F0
.global func_080CC6F0
.thumb_set func_080CC6F0, 0x080cc6f1
.endif
.ifndef OMIT_func_080CC7CC
.global func_080CC7CC
.thumb_set func_080CC7CC, 0x080cc7cd
.endif
.ifndef OMIT_func_080CC86C
.global func_080CC86C
.thumb_set func_080CC86C, 0x080cc86d
.endif
.ifndef OMIT_func_080CC8B4
.global func_080CC8B4
.thumb_set func_080CC8B4, 0x080cc8b5
.endif
.ifndef OMIT_func_080CC958
.global func_080CC958
.thumb_set func_080CC958, 0x080cc959
.endif
.ifndef OMIT_func_080CC9A0
.global func_080CC9A0
.thumb_set func_080CC9A0, 0x080cc9a1
.endif
.ifndef OMIT_func_080CC9F0
.global func_080CC9F0
.thumb_set func_080CC9F0, 0x080cc9f1
.endif
.ifndef OMIT_func_080CCA20
.global func_080CCA20
.thumb_set func_080CCA20, 0x080cca21
.endif
.ifndef OMIT_func_080CCA54
.global func_080CCA54
.thumb_set func_080CCA54, 0x080cca55
.endif
.ifndef OMIT_func_080CCA80
.global func_080CCA80
.thumb_set func_080CCA80, 0x080cca81
.endif
.ifndef OMIT_func_080CCAAC
.global func_080CCAAC
.thumb_set func_080CCAAC, 0x080ccaad
.endif
.ifndef OMIT_func_080CCAD8
.global func_080CCAD8
.thumb_set func_080CCAD8, 0x080ccad9
.endif
.ifndef OMIT_func_080CCAE8
.global func_080CCAE8
.thumb_set func_080CCAE8, 0x080ccae9
.endif
.ifndef OMIT_func_080CCB08
.global func_080CCB08
.thumb_set func_080CCB08, 0x080ccb09
.endif
.ifndef OMIT_func_080CCB28
.global func_080CCB28
.thumb_set func_080CCB28, 0x080ccb29
.endif
.ifndef OMIT_func_080CCB48
.global func_080CCB48
.thumb_set func_080CCB48, 0x080ccb49
.endif
.ifndef OMIT_func_080CCB68
.global func_080CCB68
.thumb_set func_080CCB68, 0x080ccb69
.endif
.ifndef OMIT_func_080CCB94
.global func_080CCB94
.thumb_set func_080CCB94, 0x080ccb95
.endif
.ifndef OMIT_func_080CCC1C
.global func_080CCC1C
.thumb_set func_080CCC1C, 0x080ccc1d
.endif
.ifndef OMIT_func_080CCC6C
.global func_080CCC6C
.thumb_set func_080CCC6C, 0x080ccc6d
.endif
.ifndef OMIT_func_080CCCF0
.global func_080CCCF0
.thumb_set func_080CCCF0, 0x080cccf1
.endif
.ifndef OMIT_func_080CCD50
.global func_080CCD50
.thumb_set func_080CCD50, 0x080ccd51
.endif
.ifndef OMIT_func_080CCE60
.global func_080CCE60
.thumb_set func_080CCE60, 0x080cce61
.endif
.ifndef OMIT_func_080CCF44
.global func_080CCF44
.thumb_set func_080CCF44, 0x080ccf45
.endif
.ifndef OMIT_func_080CD1FC
.global func_080CD1FC
.thumb_set func_080CD1FC, 0x080cd1fd
.endif
.ifndef OMIT_func_080CD428
.global func_080CD428
.thumb_set func_080CD428, 0x080cd429
.endif
.ifndef OMIT_func_080CD480
.global func_080CD480
.thumb_set func_080CD480, 0x080cd481
.endif
.ifndef OMIT_func_080CD4C0
.global func_080CD4C0
.thumb_set func_080CD4C0, 0x080cd4c1
.endif
.ifndef OMIT_func_080CD4D4
.global func_080CD4D4
.thumb_set func_080CD4D4, 0x080cd4d5
.endif
.ifndef OMIT_func_080CD50C
.global func_080CD50C
.thumb_set func_080CD50C, 0x080cd50d
.endif
.ifndef OMIT_func_080CD560
.global func_080CD560
.thumb_set func_080CD560, 0x080cd561
.endif
.ifndef OMIT_func_080CD584
.global func_080CD584
.thumb_set func_080CD584, 0x080cd585
.endif
.ifndef OMIT_func_080CD620
.global func_080CD620
.thumb_set func_080CD620, 0x080cd621
.endif
.ifndef OMIT_func_080CD654
.global func_080CD654
.thumb_set func_080CD654, 0x080cd655
.endif
.ifndef OMIT_func_080CD6A8
.global func_080CD6A8
.thumb_set func_080CD6A8, 0x080cd6a9
.endif
.ifndef OMIT_func_080CD70C
.global func_080CD70C
.thumb_set func_080CD70C, 0x080cd70d
.endif
.ifndef OMIT_func_080CD774
.global func_080CD774
.thumb_set func_080CD774, 0x080cd775
.endif
.ifndef OMIT_func_080CD7F0
.global func_080CD7F0
.thumb_set func_080CD7F0, 0x080cd7f1
.endif
.ifndef OMIT_func_080CD884
.global func_080CD884
.thumb_set func_080CD884, 0x080cd885
.endif
.ifndef OMIT_func_080CD8B4
.global func_080CD8B4
.thumb_set func_080CD8B4, 0x080cd8b5
.endif
.ifndef OMIT_func_080CD8CC
.global func_080CD8CC
.thumb_set func_080CD8CC, 0x080cd8cd
.endif
.ifndef OMIT_func_080CD8E4
.global func_080CD8E4
.thumb_set func_080CD8E4, 0x080cd8e5
.endif
.ifndef OMIT_func_080CD8FC
.global func_080CD8FC
.thumb_set func_080CD8FC, 0x080cd8fd
.endif
.ifndef OMIT_func_080CD914
.global func_080CD914
.thumb_set func_080CD914, 0x080cd915
.endif
.ifndef OMIT_func_080CD92C
.global func_080CD92C
.thumb_set func_080CD92C, 0x080cd92d
.endif
.ifndef OMIT_func_080CD944
.global func_080CD944
.thumb_set func_080CD944, 0x080cd945
.endif
.ifndef OMIT_func_080CD95C
.global func_080CD95C
.thumb_set func_080CD95C, 0x080cd95d
.endif
.ifndef OMIT_func_080CD974
.global func_080CD974
.thumb_set func_080CD974, 0x080cd975
.endif
.ifndef OMIT_func_080CD98C
.global func_080CD98C
.thumb_set func_080CD98C, 0x080cd98d
.endif
.ifndef OMIT_func_080CD9A4
.global func_080CD9A4
.thumb_set func_080CD9A4, 0x080cd9a5
.endif
.ifndef OMIT_func_080CD9BC
.global func_080CD9BC
.thumb_set func_080CD9BC, 0x080cd9bd
.endif
.ifndef OMIT_func_080CD9D4
.global func_080CD9D4
.thumb_set func_080CD9D4, 0x080cd9d5
.endif
.ifndef OMIT_func_080CD9EC
.global func_080CD9EC
.thumb_set func_080CD9EC, 0x080cd9ed
.endif
.ifndef OMIT_func_080CDA04
.global func_080CDA04
.thumb_set func_080CDA04, 0x080cda05
.endif
.ifndef OMIT_func_080CDA1C
.global func_080CDA1C
.thumb_set func_080CDA1C, 0x080cda1d
.endif
.ifndef OMIT_func_080CDA34
.global func_080CDA34
.thumb_set func_080CDA34, 0x080cda35
.endif
.ifndef OMIT_func_080CDA4C
.global func_080CDA4C
.thumb_set func_080CDA4C, 0x080cda4d
.endif
.ifndef OMIT_func_080CDA64
.global func_080CDA64
.thumb_set func_080CDA64, 0x080cda65
.endif
.ifndef OMIT_func_080CDA7C
.global func_080CDA7C
.thumb_set func_080CDA7C, 0x080cda7d
.endif
.ifndef OMIT_func_080CDA94
.global func_080CDA94
.thumb_set func_080CDA94, 0x080cda95
.endif
.ifndef OMIT_func_080CDAAC
.global func_080CDAAC
.thumb_set func_080CDAAC, 0x080cdaad
.endif
.ifndef OMIT_func_080CDAC4
.global func_080CDAC4
.thumb_set func_080CDAC4, 0x080cdac5
.endif
.ifndef OMIT_func_080CDADC
.global func_080CDADC
.thumb_set func_080CDADC, 0x080cdadd
.endif
.ifndef OMIT_func_080CDAF4
.global func_080CDAF4
.thumb_set func_080CDAF4, 0x080cdaf5
.endif
.ifndef OMIT_func_080CDB0C
.global func_080CDB0C
.thumb_set func_080CDB0C, 0x080cdb0d
.endif
.ifndef OMIT_func_080CDB24
.global func_080CDB24
.thumb_set func_080CDB24, 0x080cdb25
.endif
.ifndef OMIT_func_080CDB3C
.global func_080CDB3C
.thumb_set func_080CDB3C, 0x080cdb3d
.endif
.ifndef OMIT_func_080CDB54
.global func_080CDB54
.thumb_set func_080CDB54, 0x080cdb55
.endif
.ifndef OMIT_func_080CDB6C
.global func_080CDB6C
.thumb_set func_080CDB6C, 0x080cdb6d
.endif
.ifndef OMIT_func_080CDB84
.global func_080CDB84
.thumb_set func_080CDB84, 0x080cdb85
.endif
.ifndef OMIT_func_080CDB9C
.global func_080CDB9C
.thumb_set func_080CDB9C, 0x080cdb9d
.endif
.ifndef OMIT_func_080CDBB4
.global func_080CDBB4
.thumb_set func_080CDBB4, 0x080cdbb5
.endif
.ifndef OMIT_func_080CDBCC
.global func_080CDBCC
.thumb_set func_080CDBCC, 0x080cdbcd
.endif
.ifndef OMIT_func_080CDBE4
.global func_080CDBE4
.thumb_set func_080CDBE4, 0x080cdbe5
.endif
.ifndef OMIT_func_080CDBFC
.global func_080CDBFC
.thumb_set func_080CDBFC, 0x080cdbfd
.endif
.ifndef OMIT_func_080CDC14
.global func_080CDC14
.thumb_set func_080CDC14, 0x080cdc15
.endif
.ifndef OMIT_func_080CDC2C
.global func_080CDC2C
.thumb_set func_080CDC2C, 0x080cdc2d
.endif
.ifndef OMIT_func_080CDC44
.global func_080CDC44
.thumb_set func_080CDC44, 0x080cdc45
.endif
.ifndef OMIT_func_080CDC5C
.global func_080CDC5C
.thumb_set func_080CDC5C, 0x080cdc5d
.endif
.ifndef OMIT_func_080CDC74
.global func_080CDC74
.thumb_set func_080CDC74, 0x080cdc75
.endif
.ifndef OMIT_func_080CDC8C
.global func_080CDC8C
.thumb_set func_080CDC8C, 0x080cdc8d
.endif
.ifndef OMIT_func_080CDCA4
.global func_080CDCA4
.thumb_set func_080CDCA4, 0x080cdca5
.endif
.ifndef OMIT_func_080CDCBC
.global func_080CDCBC
.thumb_set func_080CDCBC, 0x080cdcbd
.endif
.ifndef OMIT_func_080CDCD4
.global func_080CDCD4
.thumb_set func_080CDCD4, 0x080cdcd5
.endif
.ifndef OMIT_func_080CDCEC
.global func_080CDCEC
.thumb_set func_080CDCEC, 0x080cdced
.endif
.ifndef OMIT_func_080CDD04
.global func_080CDD04
.thumb_set func_080CDD04, 0x080cdd05
.endif
.ifndef OMIT_func_080CDD1C
.global func_080CDD1C
.thumb_set func_080CDD1C, 0x080cdd1d
.endif
.ifndef OMIT_func_080CDD40
.global func_080CDD40
.thumb_set func_080CDD40, 0x080cdd41
.endif
.ifndef OMIT_func_080CDD64
.global func_080CDD64
.thumb_set func_080CDD64, 0x080cdd65
.endif
.ifndef OMIT_func_080CDD88
.global func_080CDD88
.thumb_set func_080CDD88, 0x080cdd89
.endif
.ifndef OMIT_func_080CDDAC
.global func_080CDDAC
.thumb_set func_080CDDAC, 0x080cddad
.endif
.ifndef OMIT_func_080CDDD0
.global func_080CDDD0
.thumb_set func_080CDDD0, 0x080cddd1
.endif
.ifndef OMIT_func_080CDDF4
.global func_080CDDF4
.thumb_set func_080CDDF4, 0x080cddf5
.endif
.ifndef OMIT_func_080CDE14
.global func_080CDE14
.thumb_set func_080CDE14, 0x080cde15
.endif
.ifndef OMIT_func_080CDE38
.global func_080CDE38
.thumb_set func_080CDE38, 0x080cde39
.endif
.ifndef OMIT_func_080CDE5C
.global func_080CDE5C
.thumb_set func_080CDE5C, 0x080cde5d
.endif
.ifndef OMIT_func_080CDE80
.global func_080CDE80
.thumb_set func_080CDE80, 0x080cde81
.endif
.ifndef OMIT_func_080CDEA4
.global func_080CDEA4
.thumb_set func_080CDEA4, 0x080cdea5
.endif
.ifndef OMIT_func_080CDEC8
.global func_080CDEC8
.thumb_set func_080CDEC8, 0x080cdec9
.endif
.ifndef OMIT_func_080CDEEC
.global func_080CDEEC
.thumb_set func_080CDEEC, 0x080cdeed
.endif
.ifndef OMIT_func_080CDF10
.global func_080CDF10
.thumb_set func_080CDF10, 0x080cdf11
.endif
.ifndef OMIT_func_080CDF30
.global func_080CDF30
.thumb_set func_080CDF30, 0x080cdf31
.endif
.ifndef OMIT_func_080CDF54
.global func_080CDF54
.thumb_set func_080CDF54, 0x080cdf55
.endif
.ifndef OMIT_func_080CDF78
.global func_080CDF78
.thumb_set func_080CDF78, 0x080cdf79
.endif
.ifndef OMIT_func_080CDF9C
.global func_080CDF9C
.thumb_set func_080CDF9C, 0x080cdf9d
.endif
.ifndef OMIT_func_080CDFC0
.global func_080CDFC0
.thumb_set func_080CDFC0, 0x080cdfc1
.endif
.ifndef OMIT_func_080CDFE4
.global func_080CDFE4
.thumb_set func_080CDFE4, 0x080cdfe5
.endif
.ifndef OMIT_func_080CE008
.global func_080CE008
.thumb_set func_080CE008, 0x080ce009
.endif
.ifndef OMIT_func_080CE02C
.global func_080CE02C
.thumb_set func_080CE02C, 0x080ce02d
.endif
.ifndef OMIT_func_080CE050
.global func_080CE050
.thumb_set func_080CE050, 0x080ce051
.endif
.ifndef OMIT_func_080CE070
.global func_080CE070
.thumb_set func_080CE070, 0x080ce071
.endif
.ifndef OMIT_func_080CE094
.global func_080CE094
.thumb_set func_080CE094, 0x080ce095
.endif
.ifndef OMIT_func_080CE0B8
.global func_080CE0B8
.thumb_set func_080CE0B8, 0x080ce0b9
.endif
.ifndef OMIT_func_080CE0DC
.global func_080CE0DC
.thumb_set func_080CE0DC, 0x080ce0dd
.endif
.ifndef OMIT_func_080CE100
.global func_080CE100
.thumb_set func_080CE100, 0x080ce101
.endif
.ifndef OMIT_func_080CE124
.global func_080CE124
.thumb_set func_080CE124, 0x080ce125
.endif
.ifndef OMIT_func_080CE148
.global func_080CE148
.thumb_set func_080CE148, 0x080ce149
.endif
.ifndef OMIT_func_080CE16C
.global func_080CE16C
.thumb_set func_080CE16C, 0x080ce16d
.endif
.ifndef OMIT_func_080CE18C
.global func_080CE18C
.thumb_set func_080CE18C, 0x080ce18d
.endif
.ifndef OMIT_func_080CE1B0
.global func_080CE1B0
.thumb_set func_080CE1B0, 0x080ce1b1
.endif
.ifndef OMIT_func_080CE1D4
.global func_080CE1D4
.thumb_set func_080CE1D4, 0x080ce1d5
.endif
.ifndef OMIT_func_080CE1F8
.global func_080CE1F8
.thumb_set func_080CE1F8, 0x080ce1f9
.endif
.ifndef OMIT_func_080CE21C
.global func_080CE21C
.thumb_set func_080CE21C, 0x080ce21d
.endif
.ifndef OMIT_func_080CE240
.global func_080CE240
.thumb_set func_080CE240, 0x080ce241
.endif
.ifndef OMIT_func_080CE264
.global func_080CE264
.thumb_set func_080CE264, 0x080ce265
.endif
.ifndef OMIT_func_080CE284
.global func_080CE284
.thumb_set func_080CE284, 0x080ce285
.endif
.ifndef OMIT_func_080CE2A8
.global func_080CE2A8
.thumb_set func_080CE2A8, 0x080ce2a9
.endif
.ifndef OMIT_func_080CE2CC
.global func_080CE2CC
.thumb_set func_080CE2CC, 0x080ce2cd
.endif
.ifndef OMIT_func_080CE2F0
.global func_080CE2F0
.thumb_set func_080CE2F0, 0x080ce2f1
.endif
.ifndef OMIT_func_080CE314
.global func_080CE314
.thumb_set func_080CE314, 0x080ce315
.endif
.ifndef OMIT_func_080CE338
.global func_080CE338
.thumb_set func_080CE338, 0x080ce339
.endif
.ifndef OMIT_func_080CE35C
.global func_080CE35C
.thumb_set func_080CE35C, 0x080ce35d
.endif
.ifndef OMIT_func_080CE380
.global func_080CE380
.thumb_set func_080CE380, 0x080ce381
.endif
.ifndef OMIT_func_080CE3A0
.global func_080CE3A0
.thumb_set func_080CE3A0, 0x080ce3a1
.endif
.ifndef OMIT_func_080CE3A8
.global func_080CE3A8
.thumb_set func_080CE3A8, 0x080ce3a9
.endif
.ifndef OMIT_func_080CE3B0
.global func_080CE3B0
.thumb_set func_080CE3B0, 0x080ce3b1
.endif
.ifndef OMIT_func_080CE3B8
.global func_080CE3B8
.thumb_set func_080CE3B8, 0x080ce3b9
.endif
.ifndef OMIT_func_080CE3C0
.global func_080CE3C0
.thumb_set func_080CE3C0, 0x080ce3c1
.endif
.ifndef OMIT_func_080CE3C8
.global func_080CE3C8
.thumb_set func_080CE3C8, 0x080ce3c9
.endif
.ifndef OMIT_func_080CE3D0
.global func_080CE3D0
.thumb_set func_080CE3D0, 0x080ce3d1
.endif
.ifndef OMIT_func_080CE3D8
.global func_080CE3D8
.thumb_set func_080CE3D8, 0x080ce3d9
.endif
.ifndef OMIT_func_080CE3E0
.global func_080CE3E0
.thumb_set func_080CE3E0, 0x080ce3e1
.endif
.ifndef OMIT_func_080CE3E8
.global func_080CE3E8
.thumb_set func_080CE3E8, 0x080ce3e9
.endif
.ifndef OMIT_func_080CE3F0
.global func_080CE3F0
.thumb_set func_080CE3F0, 0x080ce3f1
.endif
.ifndef OMIT_func_080CE3F8
.global func_080CE3F8
.thumb_set func_080CE3F8, 0x080ce3f9
.endif
.ifndef OMIT_func_080CE400
.global func_080CE400
.thumb_set func_080CE400, 0x080ce401
.endif
.ifndef OMIT_func_080CE408
.global func_080CE408
.thumb_set func_080CE408, 0x080ce409
.endif
.ifndef OMIT_func_080CE410
.global func_080CE410
.thumb_set func_080CE410, 0x080ce411
.endif
.ifndef OMIT_func_080CE418
.global func_080CE418
.thumb_set func_080CE418, 0x080ce419
.endif
.ifndef OMIT_func_080CE420
.global func_080CE420
.thumb_set func_080CE420, 0x080ce421
.endif
.ifndef OMIT_func_080CE428
.global func_080CE428
.thumb_set func_080CE428, 0x080ce429
.endif
.ifndef OMIT_func_080CE430
.global func_080CE430
.thumb_set func_080CE430, 0x080ce431
.endif
.ifndef OMIT_func_080CE438
.global func_080CE438
.thumb_set func_080CE438, 0x080ce439
.endif
.ifndef OMIT_func_080CE440
.global func_080CE440
.thumb_set func_080CE440, 0x080ce441
.endif
.ifndef OMIT_func_080CE448
.global func_080CE448
.thumb_set func_080CE448, 0x080ce449
.endif
.ifndef OMIT_func_080CE450
.global func_080CE450
.thumb_set func_080CE450, 0x080ce451
.endif
.ifndef OMIT_func_080CE458
.global func_080CE458
.thumb_set func_080CE458, 0x080ce459
.endif
.ifndef OMIT_func_080CE460
.global func_080CE460
.thumb_set func_080CE460, 0x080ce461
.endif
.ifndef OMIT_func_080CE468
.global func_080CE468
.thumb_set func_080CE468, 0x080ce469
.endif
.ifndef OMIT_func_080CE470
.global func_080CE470
.thumb_set func_080CE470, 0x080ce471
.endif
.ifndef OMIT_func_080CE478
.global func_080CE478
.thumb_set func_080CE478, 0x080ce479
.endif
.ifndef OMIT_func_080CE480
.global func_080CE480
.thumb_set func_080CE480, 0x080ce481
.endif
.ifndef OMIT_func_080CE488
.global func_080CE488
.thumb_set func_080CE488, 0x080ce489
.endif
.ifndef OMIT_func_080CE4DC
.global func_080CE4DC
.thumb_set func_080CE4DC, 0x080ce4dd
.endif
.ifndef OMIT_func_080CE8A8
.global func_080CE8A8
.thumb_set func_080CE8A8, 0x080ce8a9
.endif
.ifndef OMIT_func_080CEB34
.global func_080CEB34
.thumb_set func_080CEB34, 0x080ceb35
.endif
.ifndef OMIT_func_080CEBF8
.global func_080CEBF8
.thumb_set func_080CEBF8, 0x080cebf9
.endif
.ifndef OMIT_func_080CEC78
.global func_080CEC78
.thumb_set func_080CEC78, 0x080cec79
.endif
.ifndef OMIT_func_080CECF4
.global func_080CECF4
.thumb_set func_080CECF4, 0x080cecf5
.endif
.ifndef OMIT_func_080CED2C
.global func_080CED2C
.thumb_set func_080CED2C, 0x080ced2d
.endif
.ifndef OMIT_func_080CED34
.global func_080CED34
.thumb_set func_080CED34, 0x080ced35
.endif
.ifndef OMIT_func_080CED5C
.global func_080CED5C
.thumb_set func_080CED5C, 0x080ced5d
.endif
.ifndef OMIT_func_080D0AB0
.global func_080D0AB0
.thumb_set func_080D0AB0, 0x080d0ab1
.endif
.ifndef OMIT_func_080D1C94
.global func_080D1C94
.thumb_set func_080D1C94, 0x080d1c95
.endif
.ifndef OMIT_func_080D2114
.global func_080D2114
.thumb_set func_080D2114, 0x080d2115
.endif
.ifndef OMIT_func_080D2BF4
.global func_080D2BF4
.thumb_set func_080D2BF4, 0x080d2bf5
.endif
.ifndef OMIT_func_080D2DE0
.global func_080D2DE0
.thumb_set func_080D2DE0, 0x080d2de1
.endif
.ifndef OMIT_func_080D2E78
.global func_080D2E78
.thumb_set func_080D2E78, 0x080d2e79
.endif
.ifndef OMIT_func_080D2EB4
.global func_080D2EB4
.thumb_set func_080D2EB4, 0x080d2eb5
.endif
.ifndef OMIT_func_080D2F0C
.global func_080D2F0C
.thumb_set func_080D2F0C, 0x080d2f0d
.endif
.ifndef OMIT_func_080D2FB8
.global func_080D2FB8
.thumb_set func_080D2FB8, 0x080d2fb9
.endif
.ifndef OMIT_func_080D3508
.global func_080D3508
.thumb_set func_080D3508, 0x080d3509
.endif
.ifndef OMIT_func_080D35D8
.global func_080D35D8
.thumb_set func_080D35D8, 0x080d35d9
.endif
.ifndef OMIT_func_080D376C
.global func_080D376C
.thumb_set func_080D376C, 0x080d376d
.endif
.ifndef OMIT_func_080D37AC
.global func_080D37AC
.thumb_set func_080D37AC, 0x080d37ad
.endif
.ifndef OMIT_func_080D37C4
.global func_080D37C4
.thumb_set func_080D37C4, 0x080d37c5
.endif
.ifndef OMIT_func_080D37F8
.global func_080D37F8
.thumb_set func_080D37F8, 0x080d37f9
.endif
.ifndef OMIT_func_080D3864
.global func_080D3864
.thumb_set func_080D3864, 0x080d3865
.endif
.ifndef OMIT_func_080D3878
.global func_080D3878
.thumb_set func_080D3878, 0x080d3879
.endif
.ifndef OMIT_func_080D3888
.global func_080D3888
.thumb_set func_080D3888, 0x080d3889
.endif
.ifndef OMIT_func_080D38B4
.global func_080D38B4
.thumb_set func_080D38B4, 0x080d38b5
.endif
.ifndef OMIT_func_080D3904
.global func_080D3904
.thumb_set func_080D3904, 0x080d3905
.endif
.ifndef OMIT_func_080D3940
.global func_080D3940
.thumb_set func_080D3940, 0x080d3941
.endif
.ifndef OMIT_func_080D3958
.global func_080D3958
.thumb_set func_080D3958, 0x080d3959
.endif
.ifndef OMIT_func_080D3970
.global func_080D3970
.thumb_set func_080D3970, 0x080d3971
.endif
.ifndef OMIT_func_080D39B0
.global func_080D39B0
.thumb_set func_080D39B0, 0x080d39b1
.endif
.ifndef OMIT_func_080D39F0
.global func_080D39F0
.thumb_set func_080D39F0, 0x080d39f1
.endif
.ifndef OMIT_func_080D3A50
.global func_080D3A50
.thumb_set func_080D3A50, 0x080d3a51
.endif
.ifndef OMIT_func_080D3A88
.global func_080D3A88
.thumb_set func_080D3A88, 0x080d3a89
.endif
.ifndef OMIT_func_080D3AC0
.global func_080D3AC0
.thumb_set func_080D3AC0, 0x080d3ac1
.endif
.ifndef OMIT_func_080D3AF8
.global func_080D3AF8
.thumb_set func_080D3AF8, 0x080d3af9
.endif
.ifndef OMIT_func_080D3B38
.global func_080D3B38
.thumb_set func_080D3B38, 0x080d3b39
.endif
.ifndef OMIT_func_080D3B54
.global func_080D3B54
.thumb_set func_080D3B54, 0x080d3b55
.endif
.ifndef OMIT_func_080D3B98
.global func_080D3B98
.thumb_set func_080D3B98, 0x080d3b99
.endif
.ifndef OMIT_func_080D3E9C
.global func_080D3E9C
.thumb_set func_080D3E9C, 0x080d3e9d
.endif
.ifndef OMIT_func_080D3EFC
.global func_080D3EFC
.thumb_set func_080D3EFC, 0x080d3efd
.endif
.ifndef OMIT_func_080D3F08
.global func_080D3F08
.thumb_set func_080D3F08, 0x080d3f09
.endif
.ifndef OMIT_func_080D3F84
.global func_080D3F84
.thumb_set func_080D3F84, 0x080d3f85
.endif
.ifndef OMIT_func_080D3FF8
.global func_080D3FF8
.thumb_set func_080D3FF8, 0x080d3ff9
.endif
.ifndef OMIT_func_080D4020
.global func_080D4020
.thumb_set func_080D4020, 0x080d4021
.endif
.ifndef OMIT_func_080D4038
.global func_080D4038
.thumb_set func_080D4038, 0x080d4039
.endif
.ifndef OMIT_func_080D4224
.global func_080D4224
.thumb_set func_080D4224, 0x080d4225
.endif
.ifndef OMIT_func_080D4444
.global func_080D4444
.thumb_set func_080D4444, 0x080d4445
.endif
.ifndef OMIT_func_080D449C
.global func_080D449C
.thumb_set func_080D449C, 0x080d449d
.endif
.ifndef OMIT_func_080D45D0
.global func_080D45D0
.thumb_set func_080D45D0, 0x080d45d1
.endif
.ifndef OMIT_func_080D465C
.global func_080D465C
.thumb_set func_080D465C, 0x080d465d
.endif
.ifndef OMIT_func_080D46C4
.global func_080D46C4
.thumb_set func_080D46C4, 0x080d46c5
.endif
.ifndef OMIT_func_080D4704
.global func_080D4704
.thumb_set func_080D4704, 0x080d4705
.endif
.ifndef OMIT_func_080D4724
.global func_080D4724
.thumb_set func_080D4724, 0x080d4725
.endif
.ifndef OMIT_func_080D4768
.global func_080D4768
.thumb_set func_080D4768, 0x080d4769
.endif
.ifndef OMIT_func_080D4774
.global func_080D4774
.thumb_set func_080D4774, 0x080d4775
.endif
.ifndef OMIT_func_080D47A0
.global func_080D47A0
.thumb_set func_080D47A0, 0x080d47a1
.endif
.ifndef OMIT_func_080D47C8
.global func_080D47C8
.thumb_set func_080D47C8, 0x080d47c9
.endif
.ifndef OMIT_func_080D47DC
.global func_080D47DC
.thumb_set func_080D47DC, 0x080d47dd
.endif
.ifndef OMIT_func_080D4820
.global func_080D4820
.thumb_set func_080D4820, 0x080d4821
.endif
.ifndef OMIT_func_080D4870
.global func_080D4870
.thumb_set func_080D4870, 0x080d4871
.endif
.ifndef OMIT_func_080D48DC
.global func_080D48DC
.thumb_set func_080D48DC, 0x080d48dd
.endif
.ifndef OMIT_func_080D4938
.global func_080D4938
.thumb_set func_080D4938, 0x080d4939
.endif
.ifndef OMIT_func_080D4968
.global func_080D4968
.thumb_set func_080D4968, 0x080d4969
.endif
.ifndef OMIT_func_080D499C
.global func_080D499C
.thumb_set func_080D499C, 0x080d499d
.endif
.ifndef OMIT_func_080D49FC
.global func_080D49FC
.thumb_set func_080D49FC, 0x080d49fd
.endif
.ifndef OMIT_func_080D4A28
.global func_080D4A28
.thumb_set func_080D4A28, 0x080d4a29
.endif
.ifndef OMIT_func_080D4B64
.global func_080D4B64
.thumb_set func_080D4B64, 0x080d4b65
.endif
.ifndef OMIT_func_080D4BF8
.global func_080D4BF8
.thumb_set func_080D4BF8, 0x080d4bf9
.endif
.ifndef OMIT_func_080D4C9C
.global func_080D4C9C
.thumb_set func_080D4C9C, 0x080d4c9d
.endif
.ifndef OMIT_func_080D4D08
.global func_080D4D08
.thumb_set func_080D4D08, 0x080d4d09
.endif
.ifndef OMIT_func_080D4D14
.global func_080D4D14
.thumb_set func_080D4D14, 0x080d4d15
.endif
.ifndef OMIT_func_080D4D2C
.global func_080D4D2C
.thumb_set func_080D4D2C, 0x080d4d2d
.endif
.ifndef OMIT_func_080D5128
.global func_080D5128
.thumb_set func_080D5128, 0x080d5129
.endif
.ifndef OMIT_func_080D5594
.global func_080D5594
.thumb_set func_080D5594, 0x080d5595
.endif
.ifndef OMIT_func_080D5A60
.global func_080D5A60
.thumb_set func_080D5A60, 0x080d5a61
.endif
.ifndef OMIT_func_080D5CC0
.global func_080D5CC0
.thumb_set func_080D5CC0, 0x080d5cc1
.endif
.ifndef OMIT_func_080D5E80
.global func_080D5E80
.thumb_set func_080D5E80, 0x080d5e81
.endif
.ifndef OMIT_func_080D5F24
.global func_080D5F24
.thumb_set func_080D5F24, 0x080d5f25
.endif
.ifndef OMIT_func_080D5F74
.global func_080D5F74
.thumb_set func_080D5F74, 0x080d5f75
.endif
.ifndef OMIT_func_080D5FA4
.global func_080D5FA4
.thumb_set func_080D5FA4, 0x080d5fa5
.endif
.ifndef OMIT_func_080D6098
.global func_080D6098
.thumb_set func_080D6098, 0x080d6099
.endif
.ifndef OMIT_func_080D6128
.global func_080D6128
.thumb_set func_080D6128, 0x080d6129
.endif
.ifndef OMIT_func_080D6134
.global func_080D6134
.thumb_set func_080D6134, 0x080d6135
.endif
.ifndef OMIT_func_080D615C
.global func_080D615C
.thumb_set func_080D615C, 0x080d615d
.endif
.ifndef OMIT_func_080D6180
.global func_080D6180
.thumb_set func_080D6180, 0x080d6181
.endif
.ifndef OMIT_func_080D6194
.global func_080D6194
.thumb_set func_080D6194, 0x080d6195
.endif
.ifndef OMIT_func_080D61E4
.global func_080D61E4
.thumb_set func_080D61E4, 0x080d61e5
.endif
.ifndef OMIT_func_080D620C
.global func_080D620C
.thumb_set func_080D620C, 0x080d620d
.endif
.ifndef OMIT_func_080D63C8
.global func_080D63C8
.thumb_set func_080D63C8, 0x080d63c9
.endif
.ifndef OMIT_func_080D6524
.global func_080D6524
.thumb_set func_080D6524, 0x080d6525
.endif
.ifndef OMIT_func_080D6530
.global func_080D6530
.thumb_set func_080D6530, 0x080d6531
.endif
.ifndef OMIT_func_080D659C
.global func_080D659C
.thumb_set func_080D659C, 0x080d659d
.endif
.ifndef OMIT_func_080D65D4
.global func_080D65D4
.thumb_set func_080D65D4, 0x080d65d5
.endif
.ifndef OMIT_func_080D6950
.global func_080D6950
.thumb_set func_080D6950, 0x080d6951
.endif
.ifndef OMIT_func_080D6D0C
.global func_080D6D0C
.thumb_set func_080D6D0C, 0x080d6d0d
.endif
.ifndef OMIT_func_080D6E30
.global func_080D6E30
.thumb_set func_080D6E30, 0x080d6e31
.endif
.ifndef OMIT_func_080D6EEC
.global func_080D6EEC
.thumb_set func_080D6EEC, 0x080d6eed
.endif
.ifndef OMIT_func_080D6F64
.global func_080D6F64
.thumb_set func_080D6F64, 0x080d6f65
.endif
.ifndef OMIT_func_080D6FBC
.global func_080D6FBC
.thumb_set func_080D6FBC, 0x080d6fbd
.endif
.ifndef OMIT_func_080D702C
.global func_080D702C
.thumb_set func_080D702C, 0x080d702d
.endif
.ifndef OMIT_func_080D7080
.global func_080D7080
.thumb_set func_080D7080, 0x080d7081
.endif
.ifndef OMIT_func_080D70D8
.global func_080D70D8
.thumb_set func_080D70D8, 0x080d70d9
.endif
.ifndef OMIT_func_080D71A8
.global func_080D71A8
.thumb_set func_080D71A8, 0x080d71a9
.endif
.ifndef OMIT_func_080D7220
.global func_080D7220
.thumb_set func_080D7220, 0x080d7221
.endif
.ifndef OMIT_func_080D73AC
.global func_080D73AC
.thumb_set func_080D73AC, 0x080d73ad
.endif
.ifndef OMIT_func_080D7468
.global func_080D7468
.thumb_set func_080D7468, 0x080d7469
.endif
.ifndef OMIT_func_080D74E0
.global func_080D74E0
.thumb_set func_080D74E0, 0x080d74e1
.endif
.ifndef OMIT_func_080D758C
.global func_080D758C
.thumb_set func_080D758C, 0x080d758d
.endif
.ifndef OMIT_func_080D7A70
.global func_080D7A70
.thumb_set func_080D7A70, 0x080d7a71
.endif
.ifndef OMIT_func_080D7A9C
.global func_080D7A9C
.thumb_set func_080D7A9C, 0x080d7a9d
.endif
.ifndef OMIT_func_080D7AB0
.global func_080D7AB0
.thumb_set func_080D7AB0, 0x080d7ab1
.endif
.ifndef OMIT_func_080D7ABC
.global func_080D7ABC
.thumb_set func_080D7ABC, 0x080d7abd
.endif
.ifndef OMIT_func_080D82E0
.global func_080D82E0
.thumb_set func_080D82E0, 0x080d82e1
.endif
.ifndef OMIT_func_080D8384
.global func_080D8384
.thumb_set func_080D8384, 0x080d8385
.endif
.ifndef OMIT_func_080D8510
.global func_080D8510
.thumb_set func_080D8510, 0x080d8511
.endif
.ifndef OMIT_func_080D8858
.global func_080D8858
.thumb_set func_080D8858, 0x080d8859
.endif
.ifndef OMIT_func_080D8924
.global func_080D8924
.thumb_set func_080D8924, 0x080d8925
.endif
.ifndef OMIT_func_080D8AEC
.global func_080D8AEC
.thumb_set func_080D8AEC, 0x080d8aed
.endif
.ifndef OMIT_func_080D8B18
.global func_080D8B18
.thumb_set func_080D8B18, 0x080d8b19
.endif
.ifndef OMIT_func_080D8B4C
.global func_080D8B4C
.thumb_set func_080D8B4C, 0x080d8b4d
.endif
.ifndef OMIT_func_080D8B5C
.global func_080D8B5C
.thumb_set func_080D8B5C, 0x080d8b5d
.endif
.ifndef OMIT_func_080D8B7C
.global func_080D8B7C
.thumb_set func_080D8B7C, 0x080d8b7d
.endif
.ifndef OMIT_func_080D8C58
.global func_080D8C58
.thumb_set func_080D8C58, 0x080d8c59
.endif
.ifndef OMIT_func_080D8CD4
.global func_080D8CD4
.thumb_set func_080D8CD4, 0x080d8cd5
.endif
.ifndef OMIT_func_080D8D08
.global func_080D8D08
.thumb_set func_080D8D08, 0x080d8d09
.endif
.ifndef OMIT_func_080D8D78
.global func_080D8D78
.thumb_set func_080D8D78, 0x080d8d79
.endif
.ifndef OMIT_func_080D8D98
.global func_080D8D98
.thumb_set func_080D8D98, 0x080d8d99
.endif
.ifndef OMIT_func_080D8DC0
.global func_080D8DC0
.thumb_set func_080D8DC0, 0x080d8dc1
.endif
.ifndef OMIT_func_080D96F0
.global func_080D96F0
.thumb_set func_080D96F0, 0x080d96f1
.endif
.ifndef OMIT_func_080D979C
.global func_080D979C
.thumb_set func_080D979C, 0x080d979d
.endif
.ifndef OMIT_func_080D97D4
.global func_080D97D4
.thumb_set func_080D97D4, 0x080d97d5
.endif
.ifndef OMIT_func_080D987C
.global func_080D987C
.thumb_set func_080D987C, 0x080d987d
.endif
.ifndef OMIT_func_080D98D4
.global func_080D98D4
.thumb_set func_080D98D4, 0x080d98d5
.endif
.ifndef OMIT_func_080D9914
.global func_080D9914
.thumb_set func_080D9914, 0x080d9915
.endif
.ifndef OMIT_func_080D996C
.global func_080D996C
.thumb_set func_080D996C, 0x080d996d
.endif
.ifndef OMIT_func_080D997C
.global func_080D997C
.thumb_set func_080D997C, 0x080d997d
.endif
.ifndef OMIT_func_080D9A14
.global func_080D9A14
.thumb_set func_080D9A14, 0x080d9a15
.endif
.ifndef OMIT_func_080D9A88
.global func_080D9A88
.thumb_set func_080D9A88, 0x080d9a89
.endif
.ifndef OMIT_func_080D9ADC
.global func_080D9ADC
.thumb_set func_080D9ADC, 0x080d9add
.endif
.ifndef OMIT_func_080D9B08
.global func_080D9B08
.thumb_set func_080D9B08, 0x080d9b09
.endif
.ifndef OMIT_func_080D9B38
.global func_080D9B38
.thumb_set func_080D9B38, 0x080d9b39
.endif
.ifndef OMIT_func_080D9B58
.global func_080D9B58
.thumb_set func_080D9B58, 0x080d9b59
.endif
.ifndef OMIT_func_080D9B64
.global func_080D9B64
.thumb_set func_080D9B64, 0x080d9b65
.endif
.ifndef OMIT_func_080D9B98
.global func_080D9B98
.thumb_set func_080D9B98, 0x080d9b99
.endif
.ifndef OMIT_func_080D9BA8
.global func_080D9BA8
.thumb_set func_080D9BA8, 0x080d9ba9
.endif
.ifndef OMIT_func_080D9BCC
.global func_080D9BCC
.thumb_set func_080D9BCC, 0x080d9bcd
.endif
.ifndef OMIT_func_080D9C48
.global func_080D9C48
.thumb_set func_080D9C48, 0x080d9c49
.endif
.ifndef OMIT_func_080D9F60
.global func_080D9F60
.thumb_set func_080D9F60, 0x080d9f61
.endif
.ifndef OMIT_func_080DA1C4
.global func_080DA1C4
.thumb_set func_080DA1C4, 0x080da1c5
.endif
.ifndef OMIT_func_080DA3B8
.global func_080DA3B8
.thumb_set func_080DA3B8, 0x080da3b9
.endif
.ifndef OMIT_func_080DA598
.global func_080DA598
.thumb_set func_080DA598, 0x080da599
.endif
.ifndef OMIT_func_080DA77C
.global func_080DA77C
.thumb_set func_080DA77C, 0x080da77d
.endif
.ifndef OMIT_func_080DAA10
.global func_080DAA10
.thumb_set func_080DAA10, 0x080daa11
.endif
.ifndef OMIT_func_080DABB4
.global func_080DABB4
.thumb_set func_080DABB4, 0x080dabb5
.endif
.ifndef OMIT_func_080DABC4
.global func_080DABC4
.thumb_set func_080DABC4, 0x080dabc5
.endif
.ifndef OMIT_func_080DAC40
.global func_080DAC40
.thumb_set func_080DAC40, 0x080dac41
.endif
.ifndef OMIT_func_080DAD3C
.global func_080DAD3C
.thumb_set func_080DAD3C, 0x080dad3d
.endif
.ifndef OMIT_func_080DAD74
.global func_080DAD74
.thumb_set func_080DAD74, 0x080dad75
.endif
.ifndef OMIT_func_080DADE8
.global func_080DADE8
.thumb_set func_080DADE8, 0x080dade9
.endif
.ifndef OMIT_func_080DAE44
.global func_080DAE44
.thumb_set func_080DAE44, 0x080dae45
.endif
.ifndef OMIT_func_080DAE7C
.global func_080DAE7C
.thumb_set func_080DAE7C, 0x080dae7d
.endif
.ifndef OMIT_func_080DB6D0
.global func_080DB6D0
.thumb_set func_080DB6D0, 0x080db6d1
.endif
.ifndef OMIT_func_080DB838
.global func_080DB838
.thumb_set func_080DB838, 0x080db839
.endif
.ifndef OMIT_func_080DB944
.global func_080DB944
.thumb_set func_080DB944, 0x080db945
.endif
.ifndef OMIT_func_080DBA3C
.global func_080DBA3C
.thumb_set func_080DBA3C, 0x080dba3d
.endif
.ifndef OMIT_func_080DBA50
.global func_080DBA50
.thumb_set func_080DBA50, 0x080dba51
.endif
.ifndef OMIT_func_080DBA5C
.global func_080DBA5C
.thumb_set func_080DBA5C, 0x080dba5d
.endif
.ifndef OMIT_func_080DBA88
.global func_080DBA88
.thumb_set func_080DBA88, 0x080dba89
.endif
.ifndef OMIT_func_080DBAB8
.global func_080DBAB8
.thumb_set func_080DBAB8, 0x080dbab9
.endif
.ifndef OMIT_func_080DBB14
.global func_080DBB14
.thumb_set func_080DBB14, 0x080dbb15
.endif
.ifndef OMIT_func_080DBC08
.global func_080DBC08
.thumb_set func_080DBC08, 0x080dbc09
.endif
.ifndef OMIT_func_080DBC18
.global func_080DBC18
.thumb_set func_080DBC18, 0x080dbc19
.endif
.ifndef OMIT_func_080DBC2C
.global func_080DBC2C
.thumb_set func_080DBC2C, 0x080dbc2d
.endif
.ifndef OMIT_func_080DBC58
.global func_080DBC58
.thumb_set func_080DBC58, 0x080dbc59
.endif
.ifndef OMIT_func_080DBC88
.global func_080DBC88
.thumb_set func_080DBC88, 0x080dbc89
.endif
.ifndef OMIT_func_080DBC90
.global func_080DBC90
.thumb_set func_080DBC90, 0x080dbc91
.endif
.ifndef OMIT_func_080DBCD4
.global func_080DBCD4
.thumb_set func_080DBCD4, 0x080dbcd5
.endif
.ifndef OMIT_func_080DBD30
.global func_080DBD30
.thumb_set func_080DBD30, 0x080dbd31
.endif
.ifndef OMIT_func_080DBD48
.global func_080DBD48
.thumb_set func_080DBD48, 0x080dbd49
.endif
.ifndef OMIT_func_080DBD5C
.global func_080DBD5C
.thumb_set func_080DBD5C, 0x080dbd5d
.endif
.ifndef OMIT_func_080DBD70
.global func_080DBD70
.thumb_set func_080DBD70, 0x080dbd71
.endif
.ifndef OMIT_func_080DBD78
.global func_080DBD78
.thumb_set func_080DBD78, 0x080dbd79
.endif
.ifndef OMIT_func_080DBDA0
.global func_080DBDA0
.thumb_set func_080DBDA0, 0x080dbda1
.endif
.ifndef OMIT_func_080DBDC8
.global func_080DBDC8
.thumb_set func_080DBDC8, 0x080dbdc9
.endif
.ifndef OMIT_func_080DBEB4
.global func_080DBEB4
.thumb_set func_080DBEB4, 0x080dbeb5
.endif
.ifndef OMIT_func_080DBED4
.global func_080DBED4
.thumb_set func_080DBED4, 0x080dbed5
.endif
.ifndef OMIT_func_080DBFFC
.global func_080DBFFC
.thumb_set func_080DBFFC, 0x080dbffd
.endif
.ifndef OMIT_func_080DC014
.global func_080DC014
.thumb_set func_080DC014, 0x080dc015
.endif
.ifndef OMIT_func_080DC058
.global func_080DC058
.thumb_set func_080DC058, 0x080dc059
.endif
.ifndef OMIT_func_080DC0BC
.global func_080DC0BC
.thumb_set func_080DC0BC, 0x080dc0bd
.endif
.ifndef OMIT_func_080DC12C
.global func_080DC12C
.thumb_set func_080DC12C, 0x080dc12d
.endif
.ifndef OMIT_func_080DC1D0
.global func_080DC1D0
.thumb_set func_080DC1D0, 0x080dc1d1
.endif
.ifndef OMIT_func_080DC224
.global func_080DC224
.thumb_set func_080DC224, 0x080dc225
.endif
.ifndef OMIT_func_080DC498
.global func_080DC498
.thumb_set func_080DC498, 0x080dc499
.endif
.ifndef OMIT_func_080DC4E0
.global func_080DC4E0
.thumb_set func_080DC4E0, 0x080dc4e1
.endif
.ifndef OMIT_func_080DCD08
.global func_080DCD08
.thumb_set func_080DCD08, 0x080dcd09
.endif
.ifndef OMIT_func_080DCFE4
.global func_080DCFE4
.thumb_set func_080DCFE4, 0x080dcfe5
.endif
.ifndef OMIT_func_080DD214
.global func_080DD214
.thumb_set func_080DD214, 0x080dd215
.endif
.ifndef OMIT_func_080DD34C
.global func_080DD34C
.thumb_set func_080DD34C, 0x080dd34d
.endif
.ifndef OMIT_func_080DD350
.global func_080DD350
.thumb_set func_080DD350, 0x080dd351
.endif
.ifndef OMIT_func_080DD3C4
.global func_080DD3C4
.thumb_set func_080DD3C4, 0x080dd3c5
.endif
.ifndef OMIT_func_080DD3F0
.global func_080DD3F0
.thumb_set func_080DD3F0, 0x080dd3f1
.endif
.ifndef OMIT_func_080DD434
.global func_080DD434
.thumb_set func_080DD434, 0x080dd435
.endif
.ifndef OMIT_func_080DD478
.global func_080DD478
.thumb_set func_080DD478, 0x080dd479
.endif
.ifndef OMIT_func_080DD47C
.global func_080DD47C
.thumb_set func_080DD47C, 0x080dd47d
.endif
.ifndef OMIT_func_080DD488
.global func_080DD488
.thumb_set func_080DD488, 0x080dd489
.endif
.ifndef OMIT_func_080DD494
.global func_080DD494
.thumb_set func_080DD494, 0x080dd495
.endif
.ifndef OMIT_func_080DD4A4
.global func_080DD4A4
.thumb_set func_080DD4A4, 0x080dd4a5
.endif
.ifndef OMIT_func_080DD4B4
.global func_080DD4B4
.thumb_set func_080DD4B4, 0x080dd4b5
.endif
.ifndef OMIT_func_080DD4C4
.global func_080DD4C4
.thumb_set func_080DD4C4, 0x080dd4c5
.endif
.ifndef OMIT_func_080DD4D4
.global func_080DD4D4
.thumb_set func_080DD4D4, 0x080dd4d5
.endif
.ifndef OMIT_func_080DD56C
.global func_080DD56C
.thumb_set func_080DD56C, 0x080dd56d
.endif
.ifndef OMIT_func_080DD580
.global func_080DD580
.thumb_set func_080DD580, 0x080dd581
.endif
.ifndef OMIT_func_080DD598
.global func_080DD598
.thumb_set func_080DD598, 0x080dd599
.endif
.ifndef OMIT_func_080DD5A8
.global func_080DD5A8
.thumb_set func_080DD5A8, 0x080dd5a9
.endif
.ifndef OMIT_func_080DD5EC
.global func_080DD5EC
.thumb_set func_080DD5EC, 0x080dd5ed
.endif
.ifndef OMIT_func_080DD630
.global func_080DD630
.thumb_set func_080DD630, 0x080dd631
.endif
.ifndef OMIT_func_080DD650
.global func_080DD650
.thumb_set func_080DD650, 0x080dd651
.endif
.ifndef OMIT_func_080DD670
.global func_080DD670
.thumb_set func_080DD670, 0x080dd671
.endif
.ifndef OMIT_func_080DD684
.global func_080DD684
.thumb_set func_080DD684, 0x080dd685
.endif
.ifndef OMIT_func_080DD698
.global func_080DD698
.thumb_set func_080DD698, 0x080dd699
.endif
.ifndef OMIT_func_080DD6B8
.global func_080DD6B8
.thumb_set func_080DD6B8, 0x080dd6b9
.endif
.ifndef OMIT_func_080DD6E0
.global func_080DD6E0
.thumb_set func_080DD6E0, 0x080dd6e1
.endif
.ifndef OMIT_func_080DD6F4
.global func_080DD6F4
.thumb_set func_080DD6F4, 0x080dd6f5
.endif
.ifndef OMIT_func_080DD708
.global func_080DD708
.thumb_set func_080DD708, 0x080dd709
.endif
.ifndef OMIT_func_080DD71C
.global func_080DD71C
.thumb_set func_080DD71C, 0x080dd71d
.endif
.ifndef OMIT_func_080DD720
.global func_080DD720
.thumb_set func_080DD720, 0x080dd721
.endif
.ifndef OMIT_func_080DD730
.global func_080DD730
.thumb_set func_080DD730, 0x080dd731
.endif
.ifndef OMIT_func_080DD73C
.global func_080DD73C
.thumb_set func_080DD73C, 0x080dd73d
.endif
.ifndef OMIT_func_080DD748
.global func_080DD748
.thumb_set func_080DD748, 0x080dd749
.endif
.ifndef OMIT_func_080DD760
.global func_080DD760
.thumb_set func_080DD760, 0x080dd761
.endif
.ifndef OMIT_func_080DD7B0
.global func_080DD7B0
.thumb_set func_080DD7B0, 0x080dd7b1
.endif
.ifndef OMIT_func_080DD808
.global func_080DD808
.thumb_set func_080DD808, 0x080dd809
.endif
.ifndef OMIT_func_080DD8C4
.global func_080DD8C4
.thumb_set func_080DD8C4, 0x080dd8c5
.endif
.ifndef OMIT_func_080DDA94
.global func_080DDA94
.thumb_set func_080DDA94, 0x080dda95
.endif
.ifndef OMIT_func_080DDDA0
.global func_080DDDA0
.thumb_set func_080DDDA0, 0x080ddda1
.endif
.ifndef OMIT_func_080DDF68
.global func_080DDF68
.thumb_set func_080DDF68, 0x080ddf69
.endif
.ifndef OMIT_func_080DE10C
.global func_080DE10C
.thumb_set func_080DE10C, 0x080de10d
.endif
.ifndef OMIT_func_080DE12C
.global func_080DE12C
.thumb_set func_080DE12C, 0x080de12d
.endif
.ifndef OMIT_func_080DE150
.global func_080DE150
.thumb_set func_080DE150, 0x080de151
.endif
.ifndef OMIT_func_080DE168
.global func_080DE168
.thumb_set func_080DE168, 0x080de169
.endif
.ifndef OMIT_func_080DE188
.global func_080DE188
.thumb_set func_080DE188, 0x080de189
.endif
.ifndef OMIT_func_080DE1F0
.global func_080DE1F0
.thumb_set func_080DE1F0, 0x080de1f1
.endif
.ifndef OMIT_func_080DE200
.global func_080DE200
.thumb_set func_080DE200, 0x080de201
.endif
.ifndef OMIT_func_080DE210
.global func_080DE210
.thumb_set func_080DE210, 0x080de211
.endif
.ifndef OMIT_func_080DE244
.global func_080DE244
.thumb_set func_080DE244, 0x080de245
.endif
.ifndef OMIT_func_080DE268
.global func_080DE268
.thumb_set func_080DE268, 0x080de269
.endif
.ifndef OMIT_func_080DE278
.global func_080DE278
.thumb_set func_080DE278, 0x080de279
.endif
.ifndef OMIT_func_080DE2D0
.global func_080DE2D0
.thumb_set func_080DE2D0, 0x080de2d1
.endif
.ifndef OMIT_func_080DE328
.global func_080DE328
.thumb_set func_080DE328, 0x080de329
.endif
.ifndef OMIT_func_080DE33C
.global func_080DE33C
.thumb_set func_080DE33C, 0x080de33d
.endif
.ifndef OMIT_func_080DE390
.global func_080DE390
.thumb_set func_080DE390, 0x080de391
.endif
.ifndef OMIT_func_080DE3BC
.global func_080DE3BC
.thumb_set func_080DE3BC, 0x080de3bd
.endif
.ifndef OMIT_func_080DE3E0
.global func_080DE3E0
.thumb_set func_080DE3E0, 0x080de3e1
.endif
.ifndef OMIT_func_080DE464
.global func_080DE464
.thumb_set func_080DE464, 0x080de465
.endif
.ifndef OMIT_func_080DE488
.global func_080DE488
.thumb_set func_080DE488, 0x080de489
.endif
.ifndef OMIT_func_080DE4A0
.global func_080DE4A0
.thumb_set func_080DE4A0, 0x080de4a1
.endif
.ifndef OMIT_func_080DE4B0
.global func_080DE4B0
.thumb_set func_080DE4B0, 0x080de4b1
.endif
.ifndef OMIT_func_080DE4F4
.global func_080DE4F4
.thumb_set func_080DE4F4, 0x080de4f5
.endif
.ifndef OMIT_func_080DEBAC
.global func_080DEBAC
.thumb_set func_080DEBAC, 0x080debad
.endif
.ifndef OMIT_func_080DEF90
.global func_080DEF90
.thumb_set func_080DEF90, 0x080def91
.endif
.ifndef OMIT_func_080DF080
.global func_080DF080
.thumb_set func_080DF080, 0x080df081
.endif
.ifndef OMIT_func_080DF75C
.global func_080DF75C
.thumb_set func_080DF75C, 0x080df75d
.endif
.ifndef OMIT_func_080DF790
.global func_080DF790
.thumb_set func_080DF790, 0x080df791
.endif
.ifndef OMIT_func_080DF7A0
.global func_080DF7A0
.thumb_set func_080DF7A0, 0x080df7a1
.endif
.ifndef OMIT_func_080DF860
.global func_080DF860
.thumb_set func_080DF860, 0x080df861
.endif
.ifndef OMIT_func_080DF870
.global func_080DF870
.thumb_set func_080DF870, 0x080df871
.endif
.ifndef OMIT_func_080DF8B0
.global func_080DF8B0
.thumb_set func_080DF8B0, 0x080df8b1
.endif
.ifndef OMIT_func_080DF8CC
.global func_080DF8CC
.thumb_set func_080DF8CC, 0x080df8cd
.endif
.ifndef OMIT_func_080DF8E8
.global func_080DF8E8
.thumb_set func_080DF8E8, 0x080df8e9
.endif
.ifndef OMIT_func_080DF90C
.global func_080DF90C
.thumb_set func_080DF90C, 0x080df90d
.endif
.ifndef OMIT_func_080DF950
.global func_080DF950
.thumb_set func_080DF950, 0x080df951
.endif
.ifndef OMIT_func_080DF964
.global func_080DF964
.thumb_set func_080DF964, 0x080df965
.endif
.ifndef OMIT_func_080DF9E4
.global func_080DF9E4
.thumb_set func_080DF9E4, 0x080df9e5
.endif
.ifndef OMIT_func_080DFA70
.global func_080DFA70
.thumb_set func_080DFA70, 0x080dfa71
.endif
.ifndef OMIT_func_080DFAD0
.global func_080DFAD0
.thumb_set func_080DFAD0, 0x080dfad1
.endif
.ifndef OMIT_func_080DFD68
.global func_080DFD68
.thumb_set func_080DFD68, 0x080dfd69
.endif
.ifndef OMIT_func_080DFD8C
.global func_080DFD8C
.thumb_set func_080DFD8C, 0x080dfd8d
.endif
.ifndef OMIT_func_080DFDD8
.global func_080DFDD8
.thumb_set func_080DFDD8, 0x080dfdd9
.endif
.ifndef OMIT_func_080DFDF4
.global func_080DFDF4
.thumb_set func_080DFDF4, 0x080dfdf5
.endif
.ifndef OMIT_func_080DFE28
.global func_080DFE28
.thumb_set func_080DFE28, 0x080dfe29
.endif
.ifndef OMIT_func_080DFE74
.global func_080DFE74
.thumb_set func_080DFE74, 0x080dfe75
.endif
.ifndef OMIT_func_080DFECC
.global func_080DFECC
.thumb_set func_080DFECC, 0x080dfecd
.endif
.ifndef OMIT_func_080DFED8
.global func_080DFED8
.thumb_set func_080DFED8, 0x080dfed9
.endif
.ifndef OMIT_func_080E03F8
.global func_080E03F8
.thumb_set func_080E03F8, 0x080e03f9
.endif
.ifndef OMIT_func_080E051C
.global func_080E051C
.thumb_set func_080E051C, 0x080e051d
.endif
.ifndef OMIT_func_080E0540
.global func_080E0540
.thumb_set func_080E0540, 0x080e0541
.endif
.ifndef OMIT_func_080E0570
.global func_080E0570
.thumb_set func_080E0570, 0x080e0571
.endif
.ifndef OMIT_func_080E05DC
.global func_080E05DC
.thumb_set func_080E05DC, 0x080e05dd
.endif
.ifndef OMIT_func_080E0608
.global func_080E0608
.thumb_set func_080E0608, 0x080e0609
.endif
.ifndef OMIT_func_080E064C
.global func_080E064C
.thumb_set func_080E064C, 0x080e064d
.endif
.ifndef OMIT_func_080E0690
.global func_080E0690
.thumb_set func_080E0690, 0x080e0691
.endif
.ifndef OMIT_func_080E07F8
.global func_080E07F8
.thumb_set func_080E07F8, 0x080e07f9
.endif
.ifndef OMIT_func_080E0C88
.global func_080E0C88
.thumb_set func_080E0C88, 0x080e0c89
.endif
.ifndef OMIT_func_080E28A8
.global func_080E28A8
.thumb_set func_080E28A8, 0x080e28a9
.endif
.ifndef OMIT_func_080E2BDC
.global func_080E2BDC
.thumb_set func_080E2BDC, 0x080e2bdd
.endif
.ifndef OMIT_func_080E2C00
.global func_080E2C00
.thumb_set func_080E2C00, 0x080e2c01
.endif
.ifndef OMIT_func_080E2C54
.global func_080E2C54
.thumb_set func_080E2C54, 0x080e2c55
.endif
.ifndef OMIT_func_080E2CAC
.global func_080E2CAC
.thumb_set func_080E2CAC, 0x080e2cad
.endif
.ifndef OMIT_func_080E2D04
.global func_080E2D04
.thumb_set func_080E2D04, 0x080e2d05
.endif
.ifndef OMIT_func_080E2E24
.global func_080E2E24
.thumb_set func_080E2E24, 0x080e2e25
.endif
.ifndef OMIT_func_080E2FA4
.global func_080E2FA4
.thumb_set func_080E2FA4, 0x080e2fa5
.endif
.ifndef OMIT_func_080E35CC
.global func_080E35CC
.thumb_set func_080E35CC, 0x080e35cd
.endif
.ifndef OMIT_func_080E3788
.global func_080E3788
.thumb_set func_080E3788, 0x080e3789
.endif
.ifndef OMIT_func_080E3A10
.global func_080E3A10
.thumb_set func_080E3A10, 0x080e3a11
.endif
.ifndef OMIT_func_080E4628
.global func_080E4628
.thumb_set func_080E4628, 0x080e4629
.endif
.ifndef OMIT_func_080E5438
.global func_080E5438
.thumb_set func_080E5438, 0x080e5439
.endif
.ifndef OMIT_func_080E56B0
.global func_080E56B0
.thumb_set func_080E56B0, 0x080e56b1
.endif
.ifndef OMIT_func_080E5F50
.global func_080E5F50
.thumb_set func_080E5F50, 0x080e5f51
.endif
.ifndef OMIT_func_080E6A48
.global func_080E6A48
.thumb_set func_080E6A48, 0x080e6a49
.endif
.ifndef OMIT_func_080E6D54
.global func_080E6D54
.thumb_set func_080E6D54, 0x080e6d55
.endif
.ifndef OMIT_func_080E6FA0
.global func_080E6FA0
.thumb_set func_080E6FA0, 0x080e6fa1
.endif
.ifndef OMIT_func_080E93B4
.global func_080E93B4
.thumb_set func_080E93B4, 0x080e93b5
.endif
.ifndef OMIT_func_080E97F4
.global func_080E97F4
.thumb_set func_080E97F4, 0x080e97f5
.endif
.ifndef OMIT_func_080EA1F8
.global func_080EA1F8
.thumb_set func_080EA1F8, 0x080ea1f9
.endif
.ifndef OMIT_func_080EAB34
.global func_080EAB34
.thumb_set func_080EAB34, 0x080eab35
.endif
.ifndef OMIT_func_080EABE0
.global func_080EABE0
.thumb_set func_080EABE0, 0x080eabe1
.endif
.ifndef OMIT_func_080EB410
.global func_080EB410
.thumb_set func_080EB410, 0x080eb411
.endif
.ifndef OMIT_func_080EB514
.global func_080EB514
.thumb_set func_080EB514, 0x080eb515
.endif
.ifndef OMIT_func_080EBAA0
.global func_080EBAA0
.thumb_set func_080EBAA0, 0x080ebaa1
.endif
.ifndef OMIT_func_080EC6D8
.global func_080EC6D8
.thumb_set func_080EC6D8, 0x080ec6d9
.endif
.ifndef OMIT_func_080ECCDC
.global func_080ECCDC
.thumb_set func_080ECCDC, 0x080eccdd
.endif
.ifndef OMIT_func_080EDA00
.global func_080EDA00
.thumb_set func_080EDA00, 0x080eda01
.endif
.ifndef OMIT_func_080EDB80
.global func_080EDB80
.thumb_set func_080EDB80, 0x080edb81
.endif
.ifndef OMIT_func_080EDBDC
.global func_080EDBDC
.thumb_set func_080EDBDC, 0x080edbdd
.endif
.ifndef OMIT_func_080EDC08
.global func_080EDC08
.thumb_set func_080EDC08, 0x080edc09
.endif
.ifndef OMIT_func_080EDE64
.global func_080EDE64
.thumb_set func_080EDE64, 0x080ede65
.endif
.ifndef OMIT_func_080EDFF8
.global func_080EDFF8
.thumb_set func_080EDFF8, 0x080edff9
.endif
.ifndef OMIT_func_080EE2F4
.global func_080EE2F4
.thumb_set func_080EE2F4, 0x080ee2f5
.endif
.ifndef OMIT_func_080EE948
.global func_080EE948
.thumb_set func_080EE948, 0x080ee949
.endif
.ifndef OMIT_func_080EED88
.global func_080EED88
.thumb_set func_080EED88, 0x080eed89
.endif
.ifndef OMIT_func_080EEE50
.global func_080EEE50
.thumb_set func_080EEE50, 0x080eee51
.endif
.ifndef OMIT_func_080EEEF0
.global func_080EEEF0
.thumb_set func_080EEEF0, 0x080eeef1
.endif
.ifndef OMIT_func_080EEF30
.global func_080EEF30
.thumb_set func_080EEF30, 0x080eef31
.endif
.ifndef OMIT_func_080EEF6C
.global func_080EEF6C
.thumb_set func_080EEF6C, 0x080eef6d
.endif
.ifndef OMIT_func_080EEF98
.global func_080EEF98
.thumb_set func_080EEF98, 0x080eef99
.endif
.ifndef OMIT_func_080EF234
.global func_080EF234
.thumb_set func_080EF234, 0x080ef235
.endif
.ifndef OMIT_func_080EFCC0
.global func_080EFCC0
.thumb_set func_080EFCC0, 0x080efcc1
.endif
.ifndef OMIT_func_080F01E0
.global func_080F01E0
.thumb_set func_080F01E0, 0x080f01e1
.endif
.ifndef OMIT_func_080F03D0
.global func_080F03D0
.thumb_set func_080F03D0, 0x080f03d1
.endif
.ifndef OMIT_func_080F06A4
.global func_080F06A4
.thumb_set func_080F06A4, 0x080f06a5
.endif
.ifndef OMIT_func_080F082C
.global func_080F082C
.thumb_set func_080F082C, 0x080f082d
.endif
.ifndef OMIT_func_080F0AC0
.global func_080F0AC0
.thumb_set func_080F0AC0, 0x080f0ac1
.endif
.ifndef OMIT_func_080F0BFC
.global func_080F0BFC
.thumb_set func_080F0BFC, 0x080f0bfd
.endif
.ifndef OMIT_func_080F1184
.global func_080F1184
.thumb_set func_080F1184, 0x080f1185
.endif
.ifndef OMIT_func_080F11A8
.global func_080F11A8
.thumb_set func_080F11A8, 0x080f11a9
.endif
.ifndef OMIT_func_080F11CC
.global func_080F11CC
.thumb_set func_080F11CC, 0x080f11cd
.endif
.ifndef OMIT_func_080F1210
.global func_080F1210
.thumb_set func_080F1210, 0x080f1211
.endif
.ifndef OMIT_func_080F14D4
.global func_080F14D4
.thumb_set func_080F14D4, 0x080f14d5
.endif
.ifndef OMIT_func_080F173C
.global func_080F173C
.thumb_set func_080F173C, 0x080f173d
.endif
.ifndef OMIT_func_080F1858
.global func_080F1858
.thumb_set func_080F1858, 0x080f1859
.endif
.ifndef OMIT_func_080F1DEC
.global func_080F1DEC
.thumb_set func_080F1DEC, 0x080f1ded
.endif
.ifndef OMIT_func_080F2574
.global func_080F2574
.thumb_set func_080F2574, 0x080f2575
.endif
.ifndef OMIT_func_080F2874
.global func_080F2874
.thumb_set func_080F2874, 0x080f2875
.endif
.ifndef OMIT_func_080F2CDC
.global func_080F2CDC
.thumb_set func_080F2CDC, 0x080f2cdd
.endif
.ifndef OMIT_func_080F2E40
.global func_080F2E40
.thumb_set func_080F2E40, 0x080f2e41
.endif
.ifndef OMIT_func_080F2E78
.global func_080F2E78
.thumb_set func_080F2E78, 0x080f2e79
.endif
.ifndef OMIT_func_080F2FFC
.global func_080F2FFC
.thumb_set func_080F2FFC, 0x080f2ffd
.endif
.ifndef OMIT_func_080F33A4
.global func_080F33A4
.thumb_set func_080F33A4, 0x080f33a5
.endif
.ifndef OMIT_func_080F3B00
.global func_080F3B00
.thumb_set func_080F3B00, 0x080f3b01
.endif
.ifndef OMIT_func_080F3CCC
.global func_080F3CCC
.thumb_set func_080F3CCC, 0x080f3ccd
.endif
.ifndef OMIT_func_080F40DC
.global func_080F40DC
.thumb_set func_080F40DC, 0x080f40dd
.endif
.ifndef OMIT_func_080F4450
.global func_080F4450
.thumb_set func_080F4450, 0x080f4451
.endif
.ifndef OMIT_func_080F4614
.global func_080F4614
.thumb_set func_080F4614, 0x080f4615
.endif
.ifndef OMIT_func_080F488C
.global func_080F488C
.thumb_set func_080F488C, 0x080f488d
.endif
.ifndef OMIT_func_080F5208
.global func_080F5208
.thumb_set func_080F5208, 0x080f5209
.endif
.ifndef OMIT_func_080F543C
.global func_080F543C
.thumb_set func_080F543C, 0x080f543d
.endif
.ifndef OMIT_func_080F5F7C
.global func_080F5F7C
.thumb_set func_080F5F7C, 0x080f5f7d
.endif
.ifndef OMIT_func_080F6490
.global func_080F6490
.thumb_set func_080F6490, 0x080f6491
.endif
.ifndef OMIT_func_080F695C
.global func_080F695C
.thumb_set func_080F695C, 0x080f695d
.endif
.ifndef OMIT_func_080F7EC0
.global func_080F7EC0
.thumb_set func_080F7EC0, 0x080f7ec1
.endif
.ifndef OMIT_func_080F830C
.global func_080F830C
.thumb_set func_080F830C, 0x080f830d
.endif
.ifndef OMIT_func_080F8608
.global func_080F8608
.thumb_set func_080F8608, 0x080f8609
.endif
.ifndef OMIT_func_080F8C38
.global func_080F8C38
.thumb_set func_080F8C38, 0x080f8c39
.endif
.ifndef OMIT_func_080FACF8
.global func_080FACF8
.thumb_set func_080FACF8, 0x080facf9
.endif
.ifndef OMIT_func_080FB35C
.global func_080FB35C
.thumb_set func_080FB35C, 0x080fb35d
.endif
.ifndef OMIT_func_080FB75C
.global func_080FB75C
.thumb_set func_080FB75C, 0x080fb75d
.endif
.ifndef OMIT_func_080FB918
.global func_080FB918
.thumb_set func_080FB918, 0x080fb919
.endif
.ifndef OMIT_func_080FBC1C
.global func_080FBC1C
.thumb_set func_080FBC1C, 0x080fbc1d
.endif
.ifndef OMIT_func_080FBEA0
.global func_080FBEA0
.thumb_set func_080FBEA0, 0x080fbea1
.endif
.ifndef OMIT_func_080FC058
.global func_080FC058
.thumb_set func_080FC058, 0x080fc059
.endif
.ifndef OMIT_func_080FC444
.global func_080FC444
.thumb_set func_080FC444, 0x080fc445
.endif
.ifndef OMIT_func_080FD358
.global func_080FD358
.thumb_set func_080FD358, 0x080fd359
.endif
.ifndef OMIT_func_080FDE58
.global func_080FDE58
.thumb_set func_080FDE58, 0x080fde59
.endif
.ifndef OMIT_func_080FDEBC
.global func_080FDEBC
.thumb_set func_080FDEBC, 0x080fdebd
.endif
.ifndef OMIT_func_080FE234
.global func_080FE234
.thumb_set func_080FE234, 0x080fe235
.endif
.ifndef OMIT_func_080FE7BC
.global func_080FE7BC
.thumb_set func_080FE7BC, 0x080fe7bd
.endif
.ifndef OMIT_func_080FE920
.global func_080FE920
.thumb_set func_080FE920, 0x080fe921
.endif
.ifndef OMIT_func_080FF2C4
.global func_080FF2C4
.thumb_set func_080FF2C4, 0x080ff2c5
.endif
.ifndef OMIT_func_080FFCC0
.global func_080FFCC0
.thumb_set func_080FFCC0, 0x080ffcc1
.endif
.ifndef OMIT_func_080FFEC0
.global func_080FFEC0
.thumb_set func_080FFEC0, 0x080ffec1
.endif
.ifndef OMIT_func_081001F0
.global func_081001F0
.thumb_set func_081001F0, 0x081001f1
.endif
.ifndef OMIT_func_081007F0
.global func_081007F0
.thumb_set func_081007F0, 0x081007f1
.endif
.ifndef OMIT_func_0810163C
.global func_0810163C
.thumb_set func_0810163C, 0x0810163d
.endif
.ifndef OMIT_func_0810188C
.global func_0810188C
.thumb_set func_0810188C, 0x0810188d
.endif
.ifndef OMIT_func_08101CCC
.global func_08101CCC
.thumb_set func_08101CCC, 0x08101ccd
.endif
.ifndef OMIT_func_08101E1C
.global func_08101E1C
.thumb_set func_08101E1C, 0x08101e1d
.endif
.ifndef OMIT_func_0810205C
.global func_0810205C
.thumb_set func_0810205C, 0x0810205d
.endif
.ifndef OMIT_func_081021E8
.global func_081021E8
.thumb_set func_081021E8, 0x081021e9
.endif
.ifndef OMIT_func_08102B48
.global func_08102B48
.thumb_set func_08102B48, 0x08102b49
.endif
.ifndef OMIT_func_08102BA8
.global func_08102BA8
.thumb_set func_08102BA8, 0x08102ba9
.endif
.ifndef OMIT_func_08102BD4
.global func_08102BD4
.thumb_set func_08102BD4, 0x08102bd5
.endif
.ifndef OMIT_func_08102DC0
.global func_08102DC0
.thumb_set func_08102DC0, 0x08102dc1
.endif
.ifndef OMIT_func_08102FEC
.global func_08102FEC
.thumb_set func_08102FEC, 0x08102fed
.endif
.ifndef OMIT_func_081042C8
.global func_081042C8
.thumb_set func_081042C8, 0x081042c9
.endif
.ifndef OMIT_func_0810457C
.global func_0810457C
.thumb_set func_0810457C, 0x0810457d
.endif
.ifndef OMIT_func_0810471C
.global func_0810471C
.thumb_set func_0810471C, 0x0810471d
.endif
.ifndef OMIT_func_0810482C
.global func_0810482C
.thumb_set func_0810482C, 0x0810482d
.endif
.ifndef OMIT_func_0810493C
.global func_0810493C
.thumb_set func_0810493C, 0x0810493d
.endif
.ifndef OMIT_func_08105044
.global func_08105044
.thumb_set func_08105044, 0x08105045
.endif
.ifndef OMIT_func_0810522C
.global func_0810522C
.thumb_set func_0810522C, 0x0810522d
.endif
.ifndef OMIT_func_08105684
.global func_08105684
.thumb_set func_08105684, 0x08105685
.endif
.ifndef OMIT_func_08105D40
.global func_08105D40
.thumb_set func_08105D40, 0x08105d41
.endif
.ifndef OMIT_func_08105F64
.global func_08105F64
.thumb_set func_08105F64, 0x08105f65
.endif
.ifndef OMIT_func_081060FC
.global func_081060FC
.thumb_set func_081060FC, 0x081060fd
.endif
.ifndef OMIT_func_081062C4
.global func_081062C4
.thumb_set func_081062C4, 0x081062c5
.endif
.ifndef OMIT_func_081064A4
.global func_081064A4
.thumb_set func_081064A4, 0x081064a5
.endif
.ifndef OMIT_func_081065B4
.global func_081065B4
.thumb_set func_081065B4, 0x081065b5
.endif
.ifndef OMIT_func_08106778
.global func_08106778
.thumb_set func_08106778, 0x08106779
.endif
.ifndef OMIT_func_0810693C
.global func_0810693C
.thumb_set func_0810693C, 0x0810693d
.endif
.ifndef OMIT_func_08106AF4
.global func_08106AF4
.thumb_set func_08106AF4, 0x08106af5
.endif
.ifndef OMIT_func_08106C04
.global func_08106C04
.thumb_set func_08106C04, 0x08106c05
.endif
.ifndef OMIT_func_08106DA0
.global func_08106DA0
.thumb_set func_08106DA0, 0x08106da1
.endif
.ifndef OMIT_func_08107130
.global func_08107130
.thumb_set func_08107130, 0x08107131
.endif
.ifndef OMIT_func_081072B0
.global func_081072B0
.thumb_set func_081072B0, 0x081072b1
.endif
.ifndef OMIT_func_0810835C
.global func_0810835C
.thumb_set func_0810835C, 0x0810835d
.endif
.ifndef OMIT_func_08108630
.global func_08108630
.thumb_set func_08108630, 0x08108631
.endif
.ifndef OMIT_func_08108D9C
.global func_08108D9C
.thumb_set func_08108D9C, 0x08108d9d
.endif
.ifndef OMIT_func_08108F84
.global func_08108F84
.thumb_set func_08108F84, 0x08108f85
.endif
.ifndef OMIT_func_08109214
.global func_08109214
.thumb_set func_08109214, 0x08109215
.endif
.ifndef OMIT_func_08109664
.global func_08109664
.thumb_set func_08109664, 0x08109665
.endif
.ifndef OMIT_func_08109990
.global func_08109990
.thumb_set func_08109990, 0x08109991
.endif
.ifndef OMIT_func_0810A2A4
.global func_0810A2A4
.thumb_set func_0810A2A4, 0x0810a2a5
.endif
.ifndef OMIT_func_0810A55C
.global func_0810A55C
.thumb_set func_0810A55C, 0x0810a55d
.endif
.ifndef OMIT_func_0810A6E8
.global func_0810A6E8
.thumb_set func_0810A6E8, 0x0810a6e9
.endif
.ifndef OMIT_func_0810B0DC
.global func_0810B0DC
.thumb_set func_0810B0DC, 0x0810b0dd
.endif
.ifndef OMIT_func_0810B488
.global func_0810B488
.thumb_set func_0810B488, 0x0810b489
.endif
.ifndef OMIT_func_0810B754
.global func_0810B754
.thumb_set func_0810B754, 0x0810b755
.endif
.ifndef OMIT_func_0810B978
.global func_0810B978
.thumb_set func_0810B978, 0x0810b979
.endif
.ifndef OMIT_func_0810C244
.global func_0810C244
.thumb_set func_0810C244, 0x0810c245
.endif
.ifndef OMIT_func_0810C4D4
.global func_0810C4D4
.thumb_set func_0810C4D4, 0x0810c4d5
.endif
.ifndef OMIT_func_0810CB68
.global func_0810CB68
.thumb_set func_0810CB68, 0x0810cb69
.endif
.ifndef OMIT_func_0810D34C
.global func_0810D34C
.thumb_set func_0810D34C, 0x0810d34d
.endif
.ifndef OMIT_func_0810D590
.global func_0810D590
.thumb_set func_0810D590, 0x0810d591
.endif
.ifndef OMIT_func_0810E09C
.global func_0810E09C
.thumb_set func_0810E09C, 0x0810e09d
.endif
.ifndef OMIT_func_0810E264
.global func_0810E264
.thumb_set func_0810E264, 0x0810e265
.endif
.ifndef OMIT_func_0810E44C
.global func_0810E44C
.thumb_set func_0810E44C, 0x0810e44d
.endif
.ifndef OMIT_func_08111C7C
.global func_08111C7C
.thumb_set func_08111C7C, 0x08111c7d
.endif
.ifndef OMIT_func_08112360
.global func_08112360
.thumb_set func_08112360, 0x08112361
.endif
.ifndef OMIT_func_08112594
.global func_08112594
.thumb_set func_08112594, 0x08112595
.endif
.ifndef OMIT_func_08112A60
.global func_08112A60
.thumb_set func_08112A60, 0x08112a61
.endif
.ifndef OMIT_func_08112CCC
.global func_08112CCC
.thumb_set func_08112CCC, 0x08112ccd
.endif
.ifndef OMIT_func_08113C68
.global func_08113C68
.thumb_set func_08113C68, 0x08113c69
.endif
.ifndef OMIT_func_081154D8
.global func_081154D8
.thumb_set func_081154D8, 0x081154d9
.endif
.ifndef OMIT_func_08115ACC
.global func_08115ACC
.thumb_set func_08115ACC, 0x08115acd
.endif
.ifndef OMIT_func_08115B40
.global func_08115B40
.thumb_set func_08115B40, 0x08115b41
.endif
.ifndef OMIT_func_08115CE4
.global func_08115CE4
.thumb_set func_08115CE4, 0x08115ce5
.endif
.ifndef OMIT_func_08116480
.global func_08116480
.thumb_set func_08116480, 0x08116481
.endif
.ifndef OMIT_func_081164E8
.global func_081164E8
.thumb_set func_081164E8, 0x081164e9
.endif
.ifndef OMIT_func_08116CB0
.global func_08116CB0
.thumb_set func_08116CB0, 0x08116cb1
.endif
.ifndef OMIT_func_08118500
.global func_08118500
.thumb_set func_08118500, 0x08118501
.endif
.ifndef OMIT_func_081195F8
.global func_081195F8
.thumb_set func_081195F8, 0x081195f9
.endif
.ifndef OMIT_func_08119C88
.global func_08119C88
.thumb_set func_08119C88, 0x08119c89
.endif
.ifndef OMIT_func_0811A488
.global func_0811A488
.thumb_set func_0811A488, 0x0811a489
.endif
.ifndef OMIT_func_0811A66C
.global func_0811A66C
.thumb_set func_0811A66C, 0x0811a66d
.endif
.ifndef OMIT_func_0811A7C0
.global func_0811A7C0
.thumb_set func_0811A7C0, 0x0811a7c1
.endif
.ifndef OMIT_func_0811A97C
.global func_0811A97C
.thumb_set func_0811A97C, 0x0811a97d
.endif
.ifndef OMIT_func_0811B2A0
.global func_0811B2A0
.thumb_set func_0811B2A0, 0x0811b2a1
.endif
.ifndef OMIT_func_0811C50C
.global func_0811C50C
.thumb_set func_0811C50C, 0x0811c50d
.endif
.ifndef OMIT_func_0811C644
.global func_0811C644
.thumb_set func_0811C644, 0x0811c645
.endif
.ifndef OMIT_func_0811CD4C
.global func_0811CD4C
.thumb_set func_0811CD4C, 0x0811cd4d
.endif
.ifndef OMIT_func_0811D5FC
.global func_0811D5FC
.thumb_set func_0811D5FC, 0x0811d5fd
.endif
.ifndef OMIT_func_0811DBCC
.global func_0811DBCC
.thumb_set func_0811DBCC, 0x0811dbcd
.endif
.ifndef OMIT_func_0811E7E0
.global func_0811E7E0
.thumb_set func_0811E7E0, 0x0811e7e1
.endif
.ifndef OMIT_func_0811E890
.global func_0811E890
.thumb_set func_0811E890, 0x0811e891
.endif
.ifndef OMIT_func_0811E8E0
.global func_0811E8E0
.thumb_set func_0811E8E0, 0x0811e8e1
.endif
.ifndef OMIT_func_0811EA08
.global func_0811EA08
.thumb_set func_0811EA08, 0x0811ea09
.endif
.ifndef OMIT_func_0811EC30
.global func_0811EC30
.thumb_set func_0811EC30, 0x0811ec31
.endif
.ifndef OMIT_func_0811ECD0
.global func_0811ECD0
.thumb_set func_0811ECD0, 0x0811ecd1
.endif
.ifndef OMIT_func_0811ED14
.global func_0811ED14
.thumb_set func_0811ED14, 0x0811ed15
.endif
.ifndef OMIT_func_0811ED40
.global func_0811ED40
.thumb_set func_0811ED40, 0x0811ed41
.endif
.ifndef OMIT_func_0811EE48
.global func_0811EE48
.thumb_set func_0811EE48, 0x0811ee49
.endif
.ifndef OMIT_func_08120398
.global func_08120398
.thumb_set func_08120398, 0x08120399
.endif
.ifndef OMIT_func_08120DF0
.global func_08120DF0
.thumb_set func_08120DF0, 0x08120df1
.endif
.ifndef OMIT_func_08120FB8
.global func_08120FB8
.thumb_set func_08120FB8, 0x08120fb9
.endif
.ifndef OMIT_func_0812104C
.global func_0812104C
.thumb_set func_0812104C, 0x0812104d
.endif
.ifndef OMIT_func_081211B8
.global func_081211B8
.thumb_set func_081211B8, 0x081211b9
.endif
.ifndef OMIT_func_0812122C
.global func_0812122C
.thumb_set func_0812122C, 0x0812122d
.endif
.ifndef OMIT_func_08121B64
.global func_08121B64
.thumb_set func_08121B64, 0x08121b65
.endif
.ifndef OMIT_func_08121B78
.global func_08121B78
.thumb_set func_08121B78, 0x08121b79
.endif
.ifndef OMIT_func_08121B8C
.global func_08121B8C
.thumb_set func_08121B8C, 0x08121b8d
.endif
.ifndef OMIT_func_08121BB8
.global func_08121BB8
.thumb_set func_08121BB8, 0x08121bb9
.endif
.ifndef OMIT_func_08121BF4
.global func_08121BF4
.thumb_set func_08121BF4, 0x08121bf5
.endif
.ifndef OMIT_func_08121C18
.global func_08121C18
.thumb_set func_08121C18, 0x08121c19
.endif
.ifndef OMIT_func_08121C38
.global func_08121C38
.thumb_set func_08121C38, 0x08121c39
.endif
.ifndef OMIT_func_08121C58
.global func_08121C58
.thumb_set func_08121C58, 0x08121c59
.endif
.ifndef OMIT_func_08121C70
.global func_08121C70
.thumb_set func_08121C70, 0x08121c71
.endif
.ifndef OMIT_func_08121CB4
.global func_08121CB4
.thumb_set func_08121CB4, 0x08121cb5
.endif
.ifndef OMIT_func_08121D0C
.global func_08121D0C
.thumb_set func_08121D0C, 0x08121d0d
.endif
.ifndef OMIT_func_08121D20
.global func_08121D20
.thumb_set func_08121D20, 0x08121d21
.endif
.ifndef OMIT_func_08121D34
.global func_08121D34
.thumb_set func_08121D34, 0x08121d35
.endif
.ifndef OMIT_func_08121D40
.global func_08121D40
.thumb_set func_08121D40, 0x08121d41
.endif
.ifndef OMIT_func_08121D80
.global func_08121D80
.thumb_set func_08121D80, 0x08121d81
.endif
.ifndef OMIT_func_08121D9C
.global func_08121D9C
.thumb_set func_08121D9C, 0x08121d9d
.endif
.ifndef OMIT_func_08121DA8
.global func_08121DA8
.thumb_set func_08121DA8, 0x08121da9
.endif
.ifndef OMIT_func_08121DBC
.global func_08121DBC
.thumb_set func_08121DBC, 0x08121dbd
.endif
.ifndef OMIT_func_08121DD0
.global func_08121DD0
.thumb_set func_08121DD0, 0x08121dd1
.endif
.ifndef OMIT_func_08121E1C
.global func_08121E1C
.thumb_set func_08121E1C, 0x08121e1d
.endif
.ifndef OMIT_func_08121E48
.global func_08121E48
.thumb_set func_08121E48, 0x08121e49
.endif
.ifndef OMIT_func_08121EF0
.global func_08121EF0
.thumb_set func_08121EF0, 0x08121ef1
.endif
.ifndef OMIT_func_08121F38
.global func_08121F38
.thumb_set func_08121F38, 0x08121f39
.endif
.ifndef OMIT_func_08121F80
.global func_08121F80
.thumb_set func_08121F80, 0x08121f81
.endif
.ifndef OMIT_func_08121FB8
.global func_08121FB8
.thumb_set func_08121FB8, 0x08121fb9
.endif
.ifndef OMIT_func_08122160
.global func_08122160
.thumb_set func_08122160, 0x08122161
.endif
.ifndef OMIT_func_081223C8
.global func_081223C8
.thumb_set func_081223C8, 0x081223c9
.endif
.ifndef OMIT_func_08122404
.global func_08122404
.thumb_set func_08122404, 0x08122405
.endif
.ifndef OMIT_func_08122454
.global func_08122454
.thumb_set func_08122454, 0x08122455
.endif
.ifndef OMIT_func_08122484
.global func_08122484
.thumb_set func_08122484, 0x08122485
.endif
.ifndef OMIT_func_08122770
.global func_08122770
.thumb_set func_08122770, 0x08122771
.endif
.ifndef OMIT_func_081228D4
.global func_081228D4
.thumb_set func_081228D4, 0x081228d5
.endif
.ifndef OMIT_func_08122984
.global func_08122984
.thumb_set func_08122984, 0x08122985
.endif
.ifndef OMIT_func_08122ABC
.global func_08122ABC
.thumb_set func_08122ABC, 0x08122abd
.endif
.ifndef OMIT_func_08122B14
.global func_08122B14
.thumb_set func_08122B14, 0x08122b15
.endif
.ifndef OMIT_func_08122B50
.global func_08122B50
.thumb_set func_08122B50, 0x08122b51
.endif
.ifndef OMIT_func_08122BA4
.global func_08122BA4
.thumb_set func_08122BA4, 0x08122ba5
.endif
.ifndef OMIT_func_08122BC8
.global func_08122BC8
.thumb_set func_08122BC8, 0x08122bc9
.endif
.ifndef OMIT_func_08122BFC
.global func_08122BFC
.thumb_set func_08122BFC, 0x08122bfd
.endif
.ifndef OMIT_func_08122CA8
.global func_08122CA8
.thumb_set func_08122CA8, 0x08122ca9
.endif
.ifndef OMIT_func_08122D04
.global func_08122D04
.thumb_set func_08122D04, 0x08122d05
.endif
.ifndef OMIT_func_08122E90
.global func_08122E90
.thumb_set func_08122E90, 0x08122e91
.endif
.ifndef OMIT_func_08122EA8
.global func_08122EA8
.thumb_set func_08122EA8, 0x08122ea9
.endif
.ifndef OMIT_func_08122EC0
.global func_08122EC0
.thumb_set func_08122EC0, 0x08122ec1
.endif
.ifndef OMIT_func_08122EF8
.global func_08122EF8
.thumb_set func_08122EF8, 0x08122ef9
.endif
.ifndef OMIT_func_08122F24
.global func_08122F24
.thumb_set func_08122F24, 0x08122f25
.endif
.ifndef OMIT_func_08122F58
.global func_08122F58
.thumb_set func_08122F58, 0x08122f59
.endif
.ifndef OMIT_func_08122F8C
.global func_08122F8C
.thumb_set func_08122F8C, 0x08122f8d
.endif
.ifndef OMIT_func_08122FB8
.global func_08122FB8
.thumb_set func_08122FB8, 0x08122fb9
.endif
.ifndef OMIT_func_08122FCC
.global func_08122FCC
.thumb_set func_08122FCC, 0x08122fcd
.endif
.ifndef OMIT_func_08122FE8
.global func_08122FE8
.thumb_set func_08122FE8, 0x08122fe9
.endif
.ifndef OMIT_func_08122FFC
.global func_08122FFC
.thumb_set func_08122FFC, 0x08122ffd
.endif
.ifndef OMIT_func_08123010
.global func_08123010
.thumb_set func_08123010, 0x08123011
.endif
.ifndef OMIT_func_0812302C
.global func_0812302C
.thumb_set func_0812302C, 0x0812302d
.endif
.ifndef OMIT_func_08123044
.global func_08123044
.thumb_set func_08123044, 0x08123045
.endif
.ifndef OMIT_func_08123064
.global func_08123064
.thumb_set func_08123064, 0x08123065
.endif
.ifndef OMIT_func_08123080
.global func_08123080
.thumb_set func_08123080, 0x08123081
.endif
.ifndef OMIT_func_08123098
.global func_08123098
.thumb_set func_08123098, 0x08123099
.endif
.ifndef OMIT_func_081230A8
.global func_081230A8
.thumb_set func_081230A8, 0x081230a9
.endif
.ifndef OMIT_func_081230C4
.global func_081230C4
.thumb_set func_081230C4, 0x081230c5
.endif
.ifndef OMIT_func_081230DC
.global func_081230DC
.thumb_set func_081230DC, 0x081230dd
.endif
.ifndef OMIT_func_0812310C
.global func_0812310C
.thumb_set func_0812310C, 0x0812310d
.endif
.ifndef OMIT_func_0812314C
.global func_0812314C
.thumb_set func_0812314C, 0x0812314d
.endif
.ifndef OMIT_func_081231B0
.global func_081231B0
.thumb_set func_081231B0, 0x081231b1
.endif
.ifndef OMIT_func_081231FC
.global func_081231FC
.thumb_set func_081231FC, 0x081231fd
.endif
.ifndef OMIT_func_08123224
.global func_08123224
.thumb_set func_08123224, 0x08123225
.endif
.ifndef OMIT_func_08123234
.global func_08123234
.thumb_set func_08123234, 0x08123235
.endif
.ifndef OMIT_func_08123294
.global func_08123294
.thumb_set func_08123294, 0x08123295
.endif
.ifndef OMIT_func_081232A4
.global func_081232A4
.thumb_set func_081232A4, 0x081232a5
.endif
.ifndef OMIT_func_081232C8
.global func_081232C8
.thumb_set func_081232C8, 0x081232c9
.endif
.ifndef OMIT_func_08123320
.global func_08123320
.thumb_set func_08123320, 0x08123321
.endif
.ifndef OMIT_func_081234B4
.global func_081234B4
.thumb_set func_081234B4, 0x081234b5
.endif
.ifndef OMIT_func_081234FC
.global func_081234FC
.thumb_set func_081234FC, 0x081234fd
.endif
.ifndef OMIT_func_08123564
.global func_08123564
.thumb_set func_08123564, 0x08123565
.endif
.ifndef OMIT_func_08123580
.global func_08123580
.thumb_set func_08123580, 0x08123581
.endif
.ifndef OMIT_func_081235A8
.global func_081235A8
.thumb_set func_081235A8, 0x081235a9
.endif
.ifndef OMIT_func_081235C0
.global func_081235C0
.thumb_set func_081235C0, 0x081235c1
.endif
.ifndef OMIT_func_081235E4
.global func_081235E4
.thumb_set func_081235E4, 0x081235e5
.endif
.ifndef OMIT_func_08123670
.global func_08123670
.thumb_set func_08123670, 0x08123671
.endif
.ifndef OMIT_func_08123694
.global func_08123694
.thumb_set func_08123694, 0x08123695
.endif
.ifndef OMIT_func_08123770
.global func_08123770
.thumb_set func_08123770, 0x08123771
.endif
.ifndef OMIT_func_081237D0
.global func_081237D0
.thumb_set func_081237D0, 0x081237d1
.endif
.ifndef OMIT_func_08123814
.global func_08123814
.thumb_set func_08123814, 0x08123815
.endif
.ifndef OMIT_func_08123834
.global func_08123834
.thumb_set func_08123834, 0x08123835
.endif
.ifndef OMIT_func_08123848
.global func_08123848
.thumb_set func_08123848, 0x08123849
.endif
.ifndef OMIT_func_08123898
.global func_08123898
.thumb_set func_08123898, 0x08123899
.endif
.ifndef OMIT_func_08123900
.global func_08123900
.thumb_set func_08123900, 0x08123901
.endif
.ifndef OMIT_func_0812391C
.global func_0812391C
.thumb_set func_0812391C, 0x0812391d
.endif
.ifndef OMIT_func_08123938
.global func_08123938
.thumb_set func_08123938, 0x08123939
.endif
.ifndef OMIT_func_08123948
.global func_08123948
.thumb_set func_08123948, 0x08123949
.endif
.ifndef OMIT_func_08123958
.global func_08123958
.thumb_set func_08123958, 0x08123959
.endif
.ifndef OMIT_func_08123968
.global func_08123968
.thumb_set func_08123968, 0x08123969
.endif
.ifndef OMIT_func_0812397C
.global func_0812397C
.thumb_set func_0812397C, 0x0812397d
.endif
.ifndef OMIT_func_08123994
.global func_08123994
.thumb_set func_08123994, 0x08123995
.endif
.ifndef OMIT_func_081239C4
.global func_081239C4
.thumb_set func_081239C4, 0x081239c5
.endif
.ifndef OMIT_func_081239DC
.global func_081239DC
.thumb_set func_081239DC, 0x081239dd
.endif
.ifndef OMIT_func_081239F8
.global func_081239F8
.thumb_set func_081239F8, 0x081239f9
.endif
.ifndef OMIT_func_08123A08
.global func_08123A08
.thumb_set func_08123A08, 0x08123a09
.endif
.ifndef OMIT_func_08123A1C
.global func_08123A1C
.thumb_set func_08123A1C, 0x08123a1d
.endif
.ifndef OMIT_func_08123A2C
.global func_08123A2C
.thumb_set func_08123A2C, 0x08123a2d
.endif
.ifndef OMIT_func_08123A60
.global func_08123A60
.thumb_set func_08123A60, 0x08123a61
.endif
.ifndef OMIT_func_08123A7C
.global func_08123A7C
.thumb_set func_08123A7C, 0x08123a7d
.endif
.ifndef OMIT_func_08123A8C
.global func_08123A8C
.thumb_set func_08123A8C, 0x08123a8d
.endif
.ifndef OMIT_func_08123ACC
.global func_08123ACC
.thumb_set func_08123ACC, 0x08123acd
.endif
.ifndef OMIT_func_08123AFC
.global func_08123AFC
.thumb_set func_08123AFC, 0x08123afd
.endif
.ifndef OMIT_func_08123B34
.global func_08123B34
.thumb_set func_08123B34, 0x08123b35
.endif
.ifndef OMIT_func_08123B68
.global func_08123B68
.thumb_set func_08123B68, 0x08123b69
.endif
.ifndef OMIT_func_08123BC8
.global func_08123BC8
.thumb_set func_08123BC8, 0x08123bc9
.endif
.ifndef OMIT_func_08123C0C
.global func_08123C0C
.thumb_set func_08123C0C, 0x08123c0d
.endif
.ifndef OMIT_func_08123C50
.global func_08123C50
.thumb_set func_08123C50, 0x08123c51
.endif
.ifndef OMIT_func_08123C58
.global func_08123C58
.thumb_set func_08123C58, 0x08123c59
.endif
.ifndef OMIT_func_08123CC0
.global func_08123CC0
.thumb_set func_08123CC0, 0x08123cc1
.endif
.ifndef OMIT_func_08123CFC
.global func_08123CFC
.thumb_set func_08123CFC, 0x08123cfd
.endif
.ifndef OMIT_func_08123D28
.global func_08123D28
.thumb_set func_08123D28, 0x08123d29
.endif
.ifndef OMIT_func_08123E00
.global func_08123E00
.thumb_set func_08123E00, 0x08123e01
.endif
.ifndef OMIT_func_081242A0
.global func_081242A0
.thumb_set func_081242A0, 0x081242a1
.endif
.ifndef OMIT_func_08124480
.global func_08124480
.thumb_set func_08124480, 0x08124481
.endif
.ifndef OMIT_func_08124560
.global func_08124560
.thumb_set func_08124560, 0x08124561
.endif
.ifndef OMIT_func_08124648
.global func_08124648
.thumb_set func_08124648, 0x08124649
.endif
.ifndef OMIT_func_08124710
.global func_08124710
.thumb_set func_08124710, 0x08124711
.endif
.ifndef OMIT_func_081247B4
.global func_081247B4
.thumb_set func_081247B4, 0x081247b5
.endif
.ifndef OMIT_func_08124850
.global func_08124850
.thumb_set func_08124850, 0x08124851
.endif
.ifndef OMIT_func_08124974
.global func_08124974
.thumb_set func_08124974, 0x08124975
.endif
.ifndef OMIT_func_08124ACC
.global func_08124ACC
.thumb_set func_08124ACC, 0x08124acd
.endif
.ifndef OMIT_func_08124BB4
.global func_08124BB4
.thumb_set func_08124BB4, 0x08124bb5
.endif
.ifndef OMIT_func_08124CE8
.global func_08124CE8
.thumb_set func_08124CE8, 0x08124ce9
.endif
.ifndef OMIT_func_08124D58
.global func_08124D58
.thumb_set func_08124D58, 0x08124d59
.endif
.ifndef OMIT_func_08124DF0
.global func_08124DF0
.thumb_set func_08124DF0, 0x08124df1
.endif
.ifndef OMIT_func_08124FD0
.global func_08124FD0
.thumb_set func_08124FD0, 0x08124fd1
.endif
.ifndef OMIT_func_081253CC
.global func_081253CC
.thumb_set func_081253CC, 0x081253cd
.endif
.ifndef OMIT_func_08125444
.global func_08125444
.thumb_set func_08125444, 0x08125445
.endif
.ifndef OMIT_func_08125578
.global func_08125578
.thumb_set func_08125578, 0x08125579
.endif
.ifndef OMIT_func_081255C8
.global func_081255C8
.thumb_set func_081255C8, 0x081255c9
.endif
.ifndef OMIT_func_08125624
.global func_08125624
.thumb_set func_08125624, 0x08125625
.endif
.ifndef OMIT_func_081256BC
.global func_081256BC
.thumb_set func_081256BC, 0x081256bd
.endif
.ifndef OMIT_func_081256C8
.global func_081256C8
.thumb_set func_081256C8, 0x081256c9
.endif
.ifndef OMIT_func_081256D4
.global func_081256D4
.thumb_set func_081256D4, 0x081256d5
.endif
.ifndef OMIT_func_08125760
.global func_08125760
.thumb_set func_08125760, 0x08125761
.endif
.ifndef OMIT_func_081257D0
.global func_081257D0
.thumb_set func_081257D0, 0x081257d1
.endif
.ifndef OMIT_func_081258AC
.global func_081258AC
.thumb_set func_081258AC, 0x081258ad
.endif
.ifndef OMIT_func_08125938
.global func_08125938
.thumb_set func_08125938, 0x08125939
.endif
.ifndef OMIT_func_08126AA8
.global func_08126AA8
.thumb_set func_08126AA8, 0x08126aa9
.endif
.ifndef OMIT_func_08126B08
.global func_08126B08
.thumb_set func_08126B08, 0x08126b09
.endif
.ifndef OMIT_func_08126B3C
.global func_08126B3C
.thumb_set func_08126B3C, 0x08126b3d
.endif
.ifndef OMIT_func_08126B6C
.global func_08126B6C
.thumb_set func_08126B6C, 0x08126b6d
.endif
.ifndef OMIT_func_08126B9C
.global func_08126B9C
.thumb_set func_08126B9C, 0x08126b9d
.endif
.ifndef OMIT_func_08126BFC
.global func_08126BFC
.thumb_set func_08126BFC, 0x08126bfd
.endif
.ifndef OMIT_func_08126D34
.global func_08126D34
.thumb_set func_08126D34, 0x08126d35
.endif
.ifndef OMIT_func_08126DFC
.global func_08126DFC
.thumb_set func_08126DFC, 0x08126dfd
.endif
.ifndef OMIT_func_08126E34
.global func_08126E34
.thumb_set func_08126E34, 0x08126e35
.endif
.ifndef OMIT_func_08126EA4
.global func_08126EA4
.thumb_set func_08126EA4, 0x08126ea5
.endif
.ifndef OMIT_func_08127458
.global func_08127458
.thumb_set func_08127458, 0x08127459
.endif
.ifndef OMIT_func_08127594
.global func_08127594
.thumb_set func_08127594, 0x08127595
.endif
.ifndef OMIT_func_081276D8
.global func_081276D8
.thumb_set func_081276D8, 0x081276d9
.endif
.ifndef OMIT_func_08127990
.global func_08127990
.thumb_set func_08127990, 0x08127991
.endif
.ifndef OMIT_func_08127AF8
.global func_08127AF8
.thumb_set func_08127AF8, 0x08127af9
.endif
.ifndef OMIT_func_08127B40
.global func_08127B40
.thumb_set func_08127B40, 0x08127b41
.endif
.ifndef OMIT_func_08127B80
.global func_08127B80
.thumb_set func_08127B80, 0x08127b81
.endif
.ifndef OMIT_func_08127BC4
.global func_08127BC4
.thumb_set func_08127BC4, 0x08127bc5
.endif
.ifndef OMIT_func_08127C10
.global func_08127C10
.thumb_set func_08127C10, 0x08127c11
.endif
.ifndef OMIT_func_08127C54
.global func_08127C54
.thumb_set func_08127C54, 0x08127c55
.endif
.ifndef OMIT_func_08127C94
.global func_08127C94
.thumb_set func_08127C94, 0x08127c95
.endif
.ifndef OMIT_func_08127D0C
.global func_08127D0C
.thumb_set func_08127D0C, 0x08127d0d
.endif
.ifndef OMIT_func_081286DC
.global func_081286DC
.thumb_set func_081286DC, 0x081286dd
.endif
.ifndef OMIT_func_08128898
.global func_08128898
.thumb_set func_08128898, 0x08128899
.endif
.ifndef OMIT_func_081288C8
.global func_081288C8
.thumb_set func_081288C8, 0x081288c9
.endif
.ifndef OMIT_func_0812A440
.global func_0812A440
.thumb_set func_0812A440, 0x0812a441
.endif
.ifndef OMIT_func_0812A5BC
.global func_0812A5BC
.thumb_set func_0812A5BC, 0x0812a5bd
.endif
.ifndef OMIT_func_0812A818
.global func_0812A818
.thumb_set func_0812A818, 0x0812a819
.endif
.ifndef OMIT_func_0812A878
.global func_0812A878
.thumb_set func_0812A878, 0x0812a879
.endif
.ifndef OMIT_func_0812A91C
.global func_0812A91C
.thumb_set func_0812A91C, 0x0812a91d
.endif
.ifndef OMIT_func_0812AAC8
.global func_0812AAC8
.thumb_set func_0812AAC8, 0x0812aac9
.endif
.ifndef OMIT_func_0812AC08
.global func_0812AC08
.thumb_set func_0812AC08, 0x0812ac09
.endif
.ifndef OMIT_func_0812ADDC
.global func_0812ADDC
.thumb_set func_0812ADDC, 0x0812addd
.endif
.ifndef OMIT_func_0812AE8C
.global func_0812AE8C
.thumb_set func_0812AE8C, 0x0812ae8d
.endif
.ifndef OMIT_func_0812AF1C
.global func_0812AF1C
.thumb_set func_0812AF1C, 0x0812af1d
.endif
.ifndef OMIT_func_0812B094
.global func_0812B094
.thumb_set func_0812B094, 0x0812b095
.endif
.ifndef OMIT_func_0812B384
.global func_0812B384
.thumb_set func_0812B384, 0x0812b385
.endif
.ifndef OMIT_func_0812B3CC
.global func_0812B3CC
.thumb_set func_0812B3CC, 0x0812b3cd
.endif
.ifndef OMIT_func_0812B41C
.global func_0812B41C
.thumb_set func_0812B41C, 0x0812b41d
.endif
.ifndef OMIT_func_0812B44C
.global func_0812B44C
.thumb_set func_0812B44C, 0x0812b44d
.endif
.ifndef OMIT_func_0812B468
.global func_0812B468
.thumb_set func_0812B468, 0x0812b469
.endif
.ifndef OMIT_func_0812B4E0
.global func_0812B4E0
.thumb_set func_0812B4E0, 0x0812b4e1
.endif
.ifndef OMIT_func_0812B538
.global func_0812B538
.thumb_set func_0812B538, 0x0812b539
.endif
.ifndef OMIT_func_0812B570
.global func_0812B570
.thumb_set func_0812B570, 0x0812b571
.endif
.ifndef OMIT_func_0812B59C
.global func_0812B59C
.thumb_set func_0812B59C, 0x0812b59d
.endif
.ifndef OMIT_func_0812B5D4
.global func_0812B5D4
.thumb_set func_0812B5D4, 0x0812b5d5
.endif
.ifndef OMIT_func_0812B7D0
.global func_0812B7D0
.thumb_set func_0812B7D0, 0x0812b7d1
.endif
.ifndef OMIT_func_0812B980
.global func_0812B980
.thumb_set func_0812B980, 0x0812b981
.endif
.ifndef OMIT_func_0812BCE4
.global func_0812BCE4
.thumb_set func_0812BCE4, 0x0812bce5
.endif
.ifndef OMIT_func_0812BD0C
.global func_0812BD0C
.thumb_set func_0812BD0C, 0x0812bd0d
.endif
.ifndef OMIT_func_0812BD2C
.global func_0812BD2C
.thumb_set func_0812BD2C, 0x0812bd2d
.endif
.ifndef OMIT_func_0812C4E4
.global func_0812C4E4
.thumb_set func_0812C4E4, 0x0812c4e5
.endif
.ifndef OMIT_func_0812C530
.global func_0812C530
.thumb_set func_0812C530, 0x0812c531
.endif
.ifndef OMIT_func_0812C56C
.global func_0812C56C
.thumb_set func_0812C56C, 0x0812c56d
.endif
.ifndef OMIT_func_0812C5CC
.global func_0812C5CC
.thumb_set func_0812C5CC, 0x0812c5cd
.endif
.ifndef OMIT_func_0812C610
.global func_0812C610
.thumb_set func_0812C610, 0x0812c611
.endif
.ifndef OMIT_func_0812C634
.global func_0812C634
.thumb_set func_0812C634, 0x0812c635
.endif
.ifndef OMIT_func_0812C670
.global func_0812C670
.thumb_set func_0812C670, 0x0812c671
.endif
.ifndef OMIT_func_0812C684
.global func_0812C684
.thumb_set func_0812C684, 0x0812c685
.endif
.ifndef OMIT_func_0812C7B8
.global func_0812C7B8
.thumb_set func_0812C7B8, 0x0812c7b9
.endif
.ifndef OMIT_func_0812C7F4
.global func_0812C7F4
.thumb_set func_0812C7F4, 0x0812c7f5
.endif
.ifndef OMIT_func_0812C8DC
.global func_0812C8DC
.thumb_set func_0812C8DC, 0x0812c8dd
.endif
.ifndef OMIT_func_0812C960
.global func_0812C960
.thumb_set func_0812C960, 0x0812c961
.endif
.ifndef OMIT_func_0812CB64
.global func_0812CB64
.thumb_set func_0812CB64, 0x0812cb65
.endif
.ifndef OMIT_func_0812D07C
.global func_0812D07C
.thumb_set func_0812D07C, 0x0812d07d
.endif
.ifndef OMIT_func_0812D1B8
.global func_0812D1B8
.thumb_set func_0812D1B8, 0x0812d1b9
.endif
.ifndef OMIT_func_0812D1DC
.global func_0812D1DC
.thumb_set func_0812D1DC, 0x0812d1dd
.endif
.ifndef OMIT_func_0812D2F0
.global func_0812D2F0
.thumb_set func_0812D2F0, 0x0812d2f1
.endif
.ifndef OMIT_func_0812D358
.global func_0812D358
.thumb_set func_0812D358, 0x0812d359
.endif
.ifndef OMIT_func_0812D388
.global func_0812D388
.thumb_set func_0812D388, 0x0812d389
.endif
.ifndef OMIT_func_0812D398
.global func_0812D398
.thumb_set func_0812D398, 0x0812d399
.endif
.ifndef OMIT_func_0812D424
.global func_0812D424
.thumb_set func_0812D424, 0x0812d425
.endif
.ifndef OMIT_func_0812D474
.global func_0812D474
.thumb_set func_0812D474, 0x0812d475
.endif
.ifndef OMIT_func_0812D5A0
.global func_0812D5A0
.thumb_set func_0812D5A0, 0x0812d5a1
.endif
.ifndef OMIT_func_0812D5F4
.global func_0812D5F4
.thumb_set func_0812D5F4, 0x0812d5f5
.endif
.ifndef OMIT_func_0812D99C
.global func_0812D99C
.thumb_set func_0812D99C, 0x0812d99d
.endif
.ifndef OMIT_func_0812DA0C
.global func_0812DA0C
.thumb_set func_0812DA0C, 0x0812da0d
.endif
.ifndef OMIT_func_0812DAB8
.global func_0812DAB8
.thumb_set func_0812DAB8, 0x0812dab9
.endif
.ifndef OMIT_func_0812DAEC
.global func_0812DAEC
.thumb_set func_0812DAEC, 0x0812daed
.endif
.ifndef OMIT_func_0812DB5C
.global func_0812DB5C
.thumb_set func_0812DB5C, 0x0812db5d
.endif
.ifndef OMIT_func_0812DBA8
.global func_0812DBA8
.thumb_set func_0812DBA8, 0x0812dba9
.endif
.ifndef OMIT_func_0812E0BC
.global func_0812E0BC
.thumb_set func_0812E0BC, 0x0812e0bd
.endif
.ifndef OMIT_func_0812E0FC
.global func_0812E0FC
.thumb_set func_0812E0FC, 0x0812e0fd
.endif
.ifndef OMIT_func_0812E1A8
.global func_0812E1A8
.thumb_set func_0812E1A8, 0x0812e1a9
.endif
.ifndef OMIT_func_0812E368
.global func_0812E368
.thumb_set func_0812E368, 0x0812e369
.endif
.ifndef OMIT_func_0812E3E8
.global func_0812E3E8
.thumb_set func_0812E3E8, 0x0812e3e9
.endif
.ifndef OMIT_func_0812E470
.global func_0812E470
.thumb_set func_0812E470, 0x0812e471
.endif
.ifndef OMIT_func_0812E4A8
.global func_0812E4A8
.thumb_set func_0812E4A8, 0x0812e4a9
.endif
.ifndef OMIT_func_0812E4F4
.global func_0812E4F4
.thumb_set func_0812E4F4, 0x0812e4f5
.endif
.ifndef OMIT_func_0812E55C
.global func_0812E55C
.thumb_set func_0812E55C, 0x0812e55d
.endif
.ifndef OMIT_func_0812E5B4
.global func_0812E5B4
.thumb_set func_0812E5B4, 0x0812e5b5
.endif
.ifndef OMIT_func_0812E6A4
.global func_0812E6A4
.thumb_set func_0812E6A4, 0x0812e6a5
.endif
.ifndef OMIT_func_0812E6E0
.global func_0812E6E0
.thumb_set func_0812E6E0, 0x0812e6e1
.endif
.ifndef OMIT_func_0812EA44
.global func_0812EA44
.thumb_set func_0812EA44, 0x0812ea45
.endif
.ifndef OMIT_func_0812EB4C
.global func_0812EB4C
.thumb_set func_0812EB4C, 0x0812eb4d
.endif
.ifndef OMIT_func_0812EBD0
.global func_0812EBD0
.thumb_set func_0812EBD0, 0x0812ebd1
.endif
.ifndef OMIT_func_0812ED04
.global func_0812ED04
.thumb_set func_0812ED04, 0x0812ed05
.endif
.ifndef OMIT_func_0812ED98
.global func_0812ED98
.thumb_set func_0812ED98, 0x0812ed99
.endif
.ifndef OMIT_func_0812EED0
.global func_0812EED0
.thumb_set func_0812EED0, 0x0812eed1
.endif
.ifndef OMIT_func_0812EF94
.global func_0812EF94
.thumb_set func_0812EF94, 0x0812ef95
.endif
.ifndef OMIT_func_0812F008
.global func_0812F008
.thumb_set func_0812F008, 0x0812f009
.endif
.ifndef OMIT_func_0812F054
.global func_0812F054
.thumb_set func_0812F054, 0x0812f055
.endif
.ifndef OMIT_func_0812F068
.global func_0812F068
.thumb_set func_0812F068, 0x0812f069
.endif
.ifndef OMIT_func_0812F080
.global func_0812F080
.thumb_set func_0812F080, 0x0812f081
.endif
.ifndef OMIT_func_0812F090
.global func_0812F090
.thumb_set func_0812F090, 0x0812f091
.endif
.ifndef OMIT_func_0812F0CC
.global func_0812F0CC
.thumb_set func_0812F0CC, 0x0812f0cd
.endif
.ifndef OMIT_func_0812F0D8
.global func_0812F0D8
.thumb_set func_0812F0D8, 0x0812f0d9
.endif
.ifndef OMIT_func_0812F0E4
.global func_0812F0E4
.thumb_set func_0812F0E4, 0x0812f0e5
.endif
.ifndef OMIT_func_0812F124
.global func_0812F124
.thumb_set func_0812F124, 0x0812f125
.endif
.ifndef OMIT_func_0812F154
.global func_0812F154
.thumb_set func_0812F154, 0x0812f155
.endif
.ifndef OMIT_func_0812F17C
.global func_0812F17C
.thumb_set func_0812F17C, 0x0812f17d
.endif
.ifndef OMIT_func_0812F1AC
.global func_0812F1AC
.thumb_set func_0812F1AC, 0x0812f1ad
.endif
.ifndef OMIT_func_0812F230
.global func_0812F230
.thumb_set func_0812F230, 0x0812f231
.endif
.ifndef OMIT_func_0812F2A4
.global func_0812F2A4
.thumb_set func_0812F2A4, 0x0812f2a5
.endif
.ifndef OMIT_func_0812F2CC
.global func_0812F2CC
.thumb_set func_0812F2CC, 0x0812f2cd
.endif
.ifndef OMIT_func_0812F328
.global func_0812F328
.thumb_set func_0812F328, 0x0812f329
.endif
.ifndef OMIT_func_0812F34C
.global func_0812F34C
.thumb_set func_0812F34C, 0x0812f34d
.endif
.ifndef OMIT_func_0812F358
.global func_0812F358
.thumb_set func_0812F358, 0x0812f359
.endif
.ifndef OMIT_func_0812F39C
.global func_0812F39C
.thumb_set func_0812F39C, 0x0812f39d
.endif
.ifndef OMIT_func_0812F3CC
.global func_0812F3CC
.thumb_set func_0812F3CC, 0x0812f3cd
.endif
.ifndef OMIT_func_0812F410
.global func_0812F410
.thumb_set func_0812F410, 0x0812f411
.endif
.ifndef OMIT_func_0812F48C
.global func_0812F48C
.thumb_set func_0812F48C, 0x0812f48d
.endif
.ifndef OMIT_func_0812F528
.global func_0812F528
.thumb_set func_0812F528, 0x0812f529
.endif
.ifndef OMIT_func_0812F5E0
.global func_0812F5E0
.thumb_set func_0812F5E0, 0x0812f5e1
.endif
.ifndef OMIT_func_0812F690
.global func_0812F690
.thumb_set func_0812F690, 0x0812f691
.endif
.ifndef OMIT_func_0812F6E0
.global func_0812F6E0
.thumb_set func_0812F6E0, 0x0812f6e1
.endif
.ifndef OMIT_func_0812F704
.global func_0812F704
.thumb_set func_0812F704, 0x0812f705
.endif
.ifndef OMIT_func_0812F770
.global func_0812F770
.thumb_set func_0812F770, 0x0812f771
.endif
.ifndef OMIT_func_0812F798
.global func_0812F798
.thumb_set func_0812F798, 0x0812f799
.endif
.ifndef OMIT_func_0812F874
.global func_0812F874
.thumb_set func_0812F874, 0x0812f875
.endif
.ifndef OMIT_func_0812F8A4
.global func_0812F8A4
.thumb_set func_0812F8A4, 0x0812f8a5
.endif
.ifndef OMIT_func_0812F8E8
.global func_0812F8E8
.thumb_set func_0812F8E8, 0x0812f8e9
.endif
.ifndef OMIT_func_0812F914
.global func_0812F914
.thumb_set func_0812F914, 0x0812f915
.endif
.ifndef OMIT_func_0812FA90
.global func_0812FA90
.thumb_set func_0812FA90, 0x0812fa91
.endif
.ifndef OMIT_func_0812FD44
.global func_0812FD44
.thumb_set func_0812FD44, 0x0812fd45
.endif
.ifndef OMIT_func_0812FDDC
.global func_0812FDDC
.thumb_set func_0812FDDC, 0x0812fddd
.endif
.ifndef OMIT_func_0812FE28
.global func_0812FE28
.thumb_set func_0812FE28, 0x0812fe29
.endif
.ifndef OMIT_func_0812FE38
.global func_0812FE38
.thumb_set func_0812FE38, 0x0812fe39
.endif
.ifndef OMIT_func_08130150
.global func_08130150
.thumb_set func_08130150, 0x08130151
.endif
.ifndef OMIT_func_0813034C
.global func_0813034C
.thumb_set func_0813034C, 0x0813034d
.endif
.ifndef OMIT_func_081303FC
.global func_081303FC
.thumb_set func_081303FC, 0x081303fd
.endif
.ifndef OMIT_func_08130454
.global func_08130454
.thumb_set func_08130454, 0x08130455
.endif
.ifndef OMIT_func_081304E0
.global func_081304E0
.thumb_set func_081304E0, 0x081304e1
.endif
.ifndef OMIT_func_0813054C
.global func_0813054C
.thumb_set func_0813054C, 0x0813054d
.endif
.ifndef OMIT_func_08130654
.global func_08130654
.thumb_set func_08130654, 0x08130655
.endif
.ifndef OMIT_func_08130688
.global func_08130688
.thumb_set func_08130688, 0x08130689
.endif
.ifndef OMIT_func_0813079C
.global func_0813079C
.thumb_set func_0813079C, 0x0813079d
.endif
.ifndef OMIT_func_081307C8
.global func_081307C8
.thumb_set func_081307C8, 0x081307c9
.endif
.ifndef OMIT_func_081307F4
.global func_081307F4
.thumb_set func_081307F4, 0x081307f5
.endif
.ifndef OMIT_func_08130834
.global func_08130834
.thumb_set func_08130834, 0x08130835
.endif
.ifndef OMIT_func_08130868
.global func_08130868
.thumb_set func_08130868, 0x08130869
.endif
.ifndef OMIT_func_081308F4
.global func_081308F4
.thumb_set func_081308F4, 0x081308f5
.endif
.ifndef OMIT_func_08130FBC
.global func_08130FBC
.thumb_set func_08130FBC, 0x08130fbd
.endif
.ifndef OMIT_func_08131024
.global func_08131024
.thumb_set func_08131024, 0x08131025
.endif
.ifndef OMIT_func_08131030
.global func_08131030
.thumb_set func_08131030, 0x08131031
.endif
.ifndef OMIT_func_08131048
.global func_08131048
.thumb_set func_08131048, 0x08131049
.endif
.ifndef OMIT_func_08131088
.global func_08131088
.thumb_set func_08131088, 0x08131089
.endif
.ifndef OMIT_func_0813109C
.global func_0813109C
.thumb_set func_0813109C, 0x0813109d
.endif
.ifndef OMIT_func_081310B4
.global func_081310B4
.thumb_set func_081310B4, 0x081310b5
.endif
.ifndef OMIT_func_081310CC
.global func_081310CC
.thumb_set func_081310CC, 0x081310cd
.endif
.ifndef OMIT_func_081310E4
.global func_081310E4
.thumb_set func_081310E4, 0x081310e5
.endif
.ifndef OMIT_func_081310FC
.global func_081310FC
.thumb_set func_081310FC, 0x081310fd
.endif
.ifndef OMIT_func_08131114
.global func_08131114
.thumb_set func_08131114, 0x08131115
.endif
.ifndef OMIT_func_0813112C
.global func_0813112C
.thumb_set func_0813112C, 0x0813112d
.endif
.ifndef OMIT_func_0813114C
.global func_0813114C
.thumb_set func_0813114C, 0x0813114d
.endif
.ifndef OMIT_func_08131160
.global func_08131160
.thumb_set func_08131160, 0x08131161
.endif
.ifndef OMIT_func_08131174
.global func_08131174
.thumb_set func_08131174, 0x08131175
.endif
.ifndef OMIT_func_08131188
.global func_08131188
.thumb_set func_08131188, 0x08131189
.endif
.ifndef OMIT_func_081311A4
.global func_081311A4
.thumb_set func_081311A4, 0x081311a5
.endif
.ifndef OMIT_func_081311C0
.global func_081311C0
.thumb_set func_081311C0, 0x081311c1
.endif
.ifndef OMIT_func_08131204
.global func_08131204
.thumb_set func_08131204, 0x08131205
.endif
.ifndef OMIT_func_08131220
.global func_08131220
.thumb_set func_08131220, 0x08131221
.endif
.ifndef OMIT_func_08131260
.global func_08131260
.thumb_set func_08131260, 0x08131261
.endif
.ifndef OMIT_func_08131278
.global func_08131278
.thumb_set func_08131278, 0x08131279
.endif
.ifndef OMIT_func_08131290
.global func_08131290
.thumb_set func_08131290, 0x08131291
.endif
.ifndef OMIT_func_081312B0
.global func_081312B0
.thumb_set func_081312B0, 0x081312b1
.endif
.ifndef OMIT_func_081312EC
.global func_081312EC
.thumb_set func_081312EC, 0x081312ed
.endif
.ifndef OMIT_func_0813130C
.global func_0813130C
.thumb_set func_0813130C, 0x0813130d
.endif
.ifndef OMIT_func_08131378
.global func_08131378
.thumb_set func_08131378, 0x08131379
.endif
.ifndef OMIT_func_08131484
.global func_08131484
.thumb_set func_08131484, 0x08131485
.endif
.ifndef OMIT_func_0813156C
.global func_0813156C
.thumb_set func_0813156C, 0x0813156d
.endif
.ifndef OMIT_func_08131804
.global func_08131804
.thumb_set func_08131804, 0x08131805
.endif
.ifndef OMIT_func_0813189C
.global func_0813189C
.thumb_set func_0813189C, 0x0813189d
.endif
.ifndef OMIT_func_08131960
.global func_08131960
.thumb_set func_08131960, 0x08131961
.endif
.ifndef OMIT_func_08131988
.global func_08131988
.thumb_set func_08131988, 0x08131989
.endif
.ifndef OMIT_func_081319C4
.global func_081319C4
.thumb_set func_081319C4, 0x081319c5
.endif
.ifndef OMIT_func_08131A78
.global func_08131A78
.thumb_set func_08131A78, 0x08131a79
.endif
.ifndef OMIT_func_08131B20
.global func_08131B20
.thumb_set func_08131B20, 0x08131b21
.endif
.ifndef OMIT_func_08131BB8
.global func_08131BB8
.thumb_set func_08131BB8, 0x08131bb9
.endif
.ifndef OMIT_func_08131BE0
.global func_08131BE0
.thumb_set func_08131BE0, 0x08131be1
.endif
.ifndef OMIT_func_08131C28
.global func_08131C28
.thumb_set func_08131C28, 0x08131c29
.endif
.ifndef OMIT_func_08131C58
.global func_08131C58
.thumb_set func_08131C58, 0x08131c59
.endif
.ifndef OMIT_func_08131DA4
.global func_08131DA4
.thumb_set func_08131DA4, 0x08131da5
.endif
.ifndef OMIT_func_08131DD4
.global func_08131DD4
.thumb_set func_08131DD4, 0x08131dd5
.endif
.ifndef OMIT_func_08131DF0
.global func_08131DF0
.thumb_set func_08131DF0, 0x08131df1
.endif
.ifndef OMIT_func_08131EC8
.global func_08131EC8
.thumb_set func_08131EC8, 0x08131ec9
.endif
.ifndef OMIT_func_08131EF0
.global func_08131EF0
.thumb_set func_08131EF0, 0x08131ef1
.endif
.ifndef OMIT_func_08131F44
.global func_08131F44
.thumb_set func_08131F44, 0x08131f45
.endif
.ifndef OMIT_func_08131FD4
.global func_08131FD4
.thumb_set func_08131FD4, 0x08131fd5
.endif
.ifndef OMIT_func_08132040
.global func_08132040
.thumb_set func_08132040, 0x08132041
.endif
.ifndef OMIT_func_08132160
.global func_08132160
.thumb_set func_08132160, 0x08132161
.endif
.ifndef OMIT_func_081321B4
.global func_081321B4
.thumb_set func_081321B4, 0x081321b5
.endif
.ifndef OMIT_func_0813255C
.global func_0813255C
.thumb_set func_0813255C, 0x0813255d
.endif
.ifndef OMIT_func_081329EC
.global func_081329EC
.thumb_set func_081329EC, 0x081329ed
.endif
.ifndef OMIT_func_08132A38
.global func_08132A38
.thumb_set func_08132A38, 0x08132a39
.endif
.ifndef OMIT_func_08132A98
.global func_08132A98
.thumb_set func_08132A98, 0x08132a99
.endif
.ifndef OMIT_func_08132DDC
.global func_08132DDC
.thumb_set func_08132DDC, 0x08132ddd
.endif
.ifndef OMIT_func_08132E2C
.global func_08132E2C
.thumb_set func_08132E2C, 0x08132e2d
.endif
.ifndef OMIT_func_08133244
.global func_08133244
.thumb_set func_08133244, 0x08133245
.endif
.ifndef OMIT_func_0813325C
.global func_0813325C
.thumb_set func_0813325C, 0x0813325d
.endif
.ifndef OMIT_func_08133598
.global func_08133598
.thumb_set func_08133598, 0x08133599
.endif
.ifndef OMIT_func_0813363C
.global func_0813363C
.thumb_set func_0813363C, 0x0813363d
.endif
.ifndef OMIT_func_08133668
.global func_08133668
.thumb_set func_08133668, 0x08133669
.endif
.ifndef OMIT_func_081336B8
.global func_081336B8
.thumb_set func_081336B8, 0x081336b9
.endif
.ifndef OMIT_func_08133724
.global func_08133724
.thumb_set func_08133724, 0x08133725
.endif
.ifndef OMIT_func_0813388C
.global func_0813388C
.thumb_set func_0813388C, 0x0813388d
.endif
.ifndef OMIT_func_08133970
.global func_08133970
.thumb_set func_08133970, 0x08133971
.endif
.ifndef OMIT_func_081339A8
.global func_081339A8
.thumb_set func_081339A8, 0x081339a9
.endif
.ifndef OMIT_func_081339CC
.global func_081339CC
.thumb_set func_081339CC, 0x081339cd
.endif
.ifndef OMIT_func_081339F0
.global func_081339F0
.thumb_set func_081339F0, 0x081339f1
.endif
.ifndef OMIT_func_08133A38
.global func_08133A38
.thumb_set func_08133A38, 0x08133a39
.endif
.ifndef OMIT_func_08133A58
.global func_08133A58
.thumb_set func_08133A58, 0x08133a59
.endif
.ifndef OMIT_func_08133ADC
.global func_08133ADC
.thumb_set func_08133ADC, 0x08133add
.endif
.ifndef OMIT_func_08133B24
.global func_08133B24
.thumb_set func_08133B24, 0x08133b25
.endif
.ifndef OMIT_func_08133B3C
.global func_08133B3C
.thumb_set func_08133B3C, 0x08133b3d
.endif
.ifndef OMIT_func_08133B84
.global func_08133B84
.thumb_set func_08133B84, 0x08133b85
.endif
.ifndef OMIT_func_08133BB4
.global func_08133BB4
.thumb_set func_08133BB4, 0x08133bb5
.endif
.ifndef OMIT_func_08133BC4
.global func_08133BC4
.thumb_set func_08133BC4, 0x08133bc5
.endif
.ifndef OMIT_func_08133BE0
.global func_08133BE0
.thumb_set func_08133BE0, 0x08133be1
.endif
.ifndef OMIT_func_08133C00
.global func_08133C00
.thumb_set func_08133C00, 0x08133c01
.endif
.ifndef OMIT_func_08133CC8
.global func_08133CC8
.thumb_set func_08133CC8, 0x08133cc9
.endif
.ifndef OMIT_func_08133F48
.global func_08133F48
.thumb_set func_08133F48, 0x08133f49
.endif
.ifndef OMIT_func_08133F70
.global func_08133F70
.thumb_set func_08133F70, 0x08133f71
.endif
.ifndef OMIT_func_0813413C
.global func_0813413C
.thumb_set func_0813413C, 0x0813413d
.endif
.ifndef OMIT_func_081341BC
.global func_081341BC
.thumb_set func_081341BC, 0x081341bd
.endif
.ifndef OMIT_func_081342A8
.global func_081342A8
.thumb_set func_081342A8, 0x081342a9
.endif
.ifndef OMIT_func_081342B4
.global func_081342B4
.thumb_set func_081342B4, 0x081342b5
.endif
.ifndef OMIT_func_081342C0
.global func_081342C0
.thumb_set func_081342C0, 0x081342c1
.endif
.ifndef OMIT_func_081343C8
.global func_081343C8
.thumb_set func_081343C8, 0x081343c9
.endif
.ifndef OMIT_func_08134A10
.global func_08134A10
.thumb_set func_08134A10, 0x08134a11
.endif
.ifndef OMIT_func_08134AFC
.global func_08134AFC
.thumb_set func_08134AFC, 0x08134afd
.endif
.ifndef OMIT_func_08134B38
.global func_08134B38
.thumb_set func_08134B38, 0x08134b39
.endif
.ifndef OMIT_func_08134B5C
.global func_08134B5C
.thumb_set func_08134B5C, 0x08134b5d
.endif
.ifndef OMIT_func_0813522C
.global func_0813522C
.thumb_set func_0813522C, 0x0813522d
.endif
.ifndef OMIT_func_08135550
.global func_08135550
.thumb_set func_08135550, 0x08135551
.endif
.ifndef OMIT_func_0813569C
.global func_0813569C
.thumb_set func_0813569C, 0x0813569d
.endif
.ifndef OMIT_func_08135750
.global func_08135750
.thumb_set func_08135750, 0x08135751
.endif
.ifndef OMIT_func_081357E8
.global func_081357E8
.thumb_set func_081357E8, 0x081357e9
.endif
.ifndef OMIT_func_08135FA0
.global func_08135FA0
.thumb_set func_08135FA0, 0x08135fa1
.endif
.ifndef OMIT_func_08135FFC
.global func_08135FFC
.thumb_set func_08135FFC, 0x08135ffd
.endif
.ifndef OMIT_func_08136028
.global func_08136028
.thumb_set func_08136028, 0x08136029
.endif
.ifndef OMIT_func_08136538
.global func_08136538
.thumb_set func_08136538, 0x08136539
.endif
.ifndef OMIT_func_08136868
.global func_08136868
.thumb_set func_08136868, 0x08136869
.endif
.ifndef OMIT_func_08136944
.global func_08136944
.thumb_set func_08136944, 0x08136945
.endif
.ifndef OMIT_func_081369EC
.global func_081369EC
.thumb_set func_081369EC, 0x081369ed
.endif
.ifndef OMIT_func_08137040
.global func_08137040
.thumb_set func_08137040, 0x08137041
.endif
.ifndef OMIT_func_08137194
.global func_08137194
.thumb_set func_08137194, 0x08137195
.endif
.ifndef OMIT_func_081371DC
.global func_081371DC
.thumb_set func_081371DC, 0x081371dd
.endif
.ifndef OMIT_func_081374DC
.global func_081374DC
.thumb_set func_081374DC, 0x081374dd
.endif
.ifndef OMIT_func_08137774
.global func_08137774
.thumb_set func_08137774, 0x08137775
.endif
.ifndef OMIT_func_0813777C
.global func_0813777C
.thumb_set func_0813777C, 0x0813777d
.endif
.ifndef OMIT_func_081378EC
.global func_081378EC
.thumb_set func_081378EC, 0x081378ed
.endif
.ifndef OMIT_func_081379C8
.global func_081379C8
.thumb_set func_081379C8, 0x081379c9
.endif
.ifndef OMIT_func_08137A7C
.global func_08137A7C
.thumb_set func_08137A7C, 0x08137a7d
.endif
.ifndef OMIT_func_08137A80
.global func_08137A80
.thumb_set func_08137A80, 0x08137a81
.endif
.ifndef OMIT_func_08137A9C
.global func_08137A9C
.thumb_set func_08137A9C, 0x08137a9d
.endif
.ifndef OMIT_func_08137AD0
.global func_08137AD0
.thumb_set func_08137AD0, 0x08137ad1
.endif
.ifndef OMIT_func_08137AEC
.global func_08137AEC
.thumb_set func_08137AEC, 0x08137aed
.endif
.ifndef OMIT_func_08137B00
.global func_08137B00
.thumb_set func_08137B00, 0x08137b01
.endif
.ifndef OMIT_func_08137C48
.global func_08137C48
.thumb_set func_08137C48, 0x08137c49
.endif
.ifndef OMIT_func_08137C4C
.global func_08137C4C
.thumb_set func_08137C4C, 0x08137c4d
.endif
.ifndef OMIT_func_08138014
.global func_08138014
.thumb_set func_08138014, 0x08138015
.endif
.ifndef OMIT_func_081380A8
.global func_081380A8
.thumb_set func_081380A8, 0x081380a9
.endif
.ifndef OMIT_func_081385CC
.global func_081385CC
.thumb_set func_081385CC, 0x081385cd
.endif
.ifndef OMIT_func_08138D60
.global func_08138D60
.thumb_set func_08138D60, 0x08138d61
.endif
.ifndef OMIT_func_08138DA4
.global func_08138DA4
.thumb_set func_08138DA4, 0x08138da5
.endif
.ifndef OMIT_func_0813AE30
.global func_0813AE30
.thumb_set func_0813AE30, 0x0813ae31
.endif
.ifndef OMIT_func_0813AF98
.global func_0813AF98
.thumb_set func_0813AF98, 0x0813af99
.endif
.ifndef OMIT_func_0813B0D4
.global func_0813B0D4
.thumb_set func_0813B0D4, 0x0813b0d5
.endif
.ifndef OMIT_func_0813B2A8
.global func_0813B2A8
.thumb_set func_0813B2A8, 0x0813b2a9
.endif
.ifndef OMIT_func_0813B480
.global func_0813B480
.thumb_set func_0813B480, 0x0813b481
.endif
.ifndef OMIT_func_0813B57C
.global func_0813B57C
.thumb_set func_0813B57C, 0x0813b57d
.endif
.ifndef OMIT_func_0813B9B8
.global func_0813B9B8
.thumb_set func_0813B9B8, 0x0813b9b9
.endif
.ifndef OMIT_func_0813B9F8
.global func_0813B9F8
.thumb_set func_0813B9F8, 0x0813b9f9
.endif
.ifndef OMIT_func_0813BB04
.global func_0813BB04
.thumb_set func_0813BB04, 0x0813bb05
.endif
.ifndef OMIT_func_0813BBB8
.global func_0813BBB8
.thumb_set func_0813BBB8, 0x0813bbb9
.endif
.ifndef OMIT_func_0813BC30
.global func_0813BC30
.thumb_set func_0813BC30, 0x0813bc31
.endif
.ifndef OMIT_func_0813BC7C
.global func_0813BC7C
.thumb_set func_0813BC7C, 0x0813bc7d
.endif
.ifndef OMIT_func_0813BCF0
.global func_0813BCF0
.thumb_set func_0813BCF0, 0x0813bcf1
.endif
.ifndef OMIT_func_0813BDD0
.global func_0813BDD0
.thumb_set func_0813BDD0, 0x0813bdd1
.endif
.ifndef OMIT_func_0813BEEC
.global func_0813BEEC
.thumb_set func_0813BEEC, 0x0813beed
.endif
.ifndef OMIT_func_0813BF5C
.global func_0813BF5C
.thumb_set func_0813BF5C, 0x0813bf5d
.endif
.ifndef OMIT_func_0813C064
.global func_0813C064
.thumb_set func_0813C064, 0x0813c065
.endif
.ifndef OMIT_func_0813C0A8
.global func_0813C0A8
.thumb_set func_0813C0A8, 0x0813c0a9
.endif
.ifndef OMIT_func_0813C0C4
.global func_0813C0C4
.thumb_set func_0813C0C4, 0x0813c0c5
.endif
.ifndef OMIT_func_0813C0D8
.global func_0813C0D8
.thumb_set func_0813C0D8, 0x0813c0d9
.endif
.ifndef OMIT_func_0813C0EC
.global func_0813C0EC
.thumb_set func_0813C0EC, 0x0813c0ed
.endif
.ifndef OMIT_func_0813D4A0
.global func_0813D4A0
.thumb_set func_0813D4A0, 0x0813d4a1
.endif
.ifndef OMIT_func_0813DAFC
.global func_0813DAFC
.thumb_set func_0813DAFC, 0x0813dafd
.endif
.ifndef OMIT_func_0813DB34
.global func_0813DB34
.thumb_set func_0813DB34, 0x0813db35
.endif
.ifndef OMIT_func_0813DB44
.global func_0813DB44
.thumb_set func_0813DB44, 0x0813db45
.endif
.ifndef OMIT_func_0813DC3C
.global func_0813DC3C
.thumb_set func_0813DC3C, 0x0813dc3d
.endif
.ifndef OMIT_func_0813DF5C
.global func_0813DF5C
.thumb_set func_0813DF5C, 0x0813df5d
.endif
.ifndef OMIT_func_0813E030
.global func_0813E030
.thumb_set func_0813E030, 0x0813e031
.endif
.ifndef OMIT_func_0813E1DC
.global func_0813E1DC
.thumb_set func_0813E1DC, 0x0813e1dd
.endif
.ifndef OMIT_func_0813E750
.global func_0813E750
.thumb_set func_0813E750, 0x0813e751
.endif
.ifndef OMIT_func_0813E9F4
.global func_0813E9F4
.thumb_set func_0813E9F4, 0x0813e9f5
.endif
.ifndef OMIT_func_0813EBC0
.global func_0813EBC0
.thumb_set func_0813EBC0, 0x0813ebc1
.endif
.ifndef OMIT_func_0813EC04
.global func_0813EC04
.thumb_set func_0813EC04, 0x0813ec05
.endif
.ifndef OMIT_func_0813EC28
.global func_0813EC28
.thumb_set func_0813EC28, 0x0813ec29
.endif
.ifndef OMIT_func_0813EC5C
.global func_0813EC5C
.thumb_set func_0813EC5C, 0x0813ec5d
.endif
.ifndef OMIT_func_0813EC64
.global func_0813EC64
.thumb_set func_0813EC64, 0x0813ec65
.endif
.ifndef OMIT_func_0813EDFC
.global func_0813EDFC
.thumb_set func_0813EDFC, 0x0813edfd
.endif
.ifndef OMIT_func_0813EE18
.global func_0813EE18
.thumb_set func_0813EE18, 0x0813ee19
.endif
.ifndef OMIT_func_0813EE20
.global func_0813EE20
.thumb_set func_0813EE20, 0x0813ee21
.endif
.ifndef OMIT_func_0813EEF8
.global func_0813EEF8
.thumb_set func_0813EEF8, 0x0813eef9
.endif
.ifndef OMIT_func_0813EF2C
.global func_0813EF2C
.thumb_set func_0813EF2C, 0x0813ef2d
.endif
.ifndef OMIT_func_0813EF34
.global func_0813EF34
.thumb_set func_0813EF34, 0x0813ef35
.endif
.ifndef OMIT_func_0813EF38
.global func_0813EF38
.thumb_set func_0813EF38, 0x0813ef39
.endif
.ifndef OMIT_func_0813EF4C
.global func_0813EF4C
.thumb_set func_0813EF4C, 0x0813ef4d
.endif
.ifndef OMIT_func_0813EFDC
.global func_0813EFDC
.thumb_set func_0813EFDC, 0x0813efdd
.endif
.ifndef OMIT_func_0813F080
.global func_0813F080
.thumb_set func_0813F080, 0x0813f081
.endif
.ifndef OMIT_func_0813F124
.global func_0813F124
.thumb_set func_0813F124, 0x0813f125
.endif
.ifndef OMIT_func_0813F12C
.global func_0813F12C
.thumb_set func_0813F12C, 0x0813f12d
.endif
.ifndef OMIT_func_0813F134
.global func_0813F134
.thumb_set func_0813F134, 0x0813f135
.endif
.ifndef OMIT_func_0813F13C
.global func_0813F13C
.thumb_set func_0813F13C, 0x0813f13d
.endif
.ifndef OMIT_func_0813F19C
.global func_0813F19C
.thumb_set func_0813F19C, 0x0813f19d
.endif
.ifndef OMIT_func_0813F1D8
.global func_0813F1D8
.thumb_set func_0813F1D8, 0x0813f1d9
.endif
.ifndef OMIT_func_0813FB0C
.global func_0813FB0C
.thumb_set func_0813FB0C, 0x0813fb0d
.endif
.ifndef OMIT_func_0813FBD4
.global func_0813FBD4
.thumb_set func_0813FBD4, 0x0813fbd5
.endif
.ifndef OMIT_func_0814011C
.global func_0814011C
.thumb_set func_0814011C, 0x0814011d
.endif
.ifndef OMIT_func_08140A20
.global func_08140A20
.thumb_set func_08140A20, 0x08140a21
.endif
.ifndef OMIT_func_08141474
.global func_08141474
.thumb_set func_08141474, 0x08141475
.endif
.ifndef OMIT_func_08141500
.global func_08141500
.thumb_set func_08141500, 0x08141501
.endif
.ifndef OMIT_func_08141520
.global func_08141520
.thumb_set func_08141520, 0x08141521
.endif
.ifndef OMIT_func_08141540
.global func_08141540
.thumb_set func_08141540, 0x08141541
.endif
.ifndef OMIT_func_08141570
.global func_08141570
.thumb_set func_08141570, 0x08141571
.endif
.ifndef OMIT_func_081415C0
.global func_081415C0
.thumb_set func_081415C0, 0x081415c1
.endif
.ifndef OMIT_func_08141620
.global func_08141620
.thumb_set func_08141620, 0x08141621
.endif
.ifndef OMIT_func_0814164C
.global func_0814164C
.thumb_set func_0814164C, 0x0814164d
.endif
.ifndef OMIT_func_0814168C
.global func_0814168C
.thumb_set func_0814168C, 0x0814168d
.endif
.ifndef OMIT_func_081416DC
.global func_081416DC
.thumb_set func_081416DC, 0x081416dd
.endif
.ifndef OMIT_func_08141708
.global func_08141708
.thumb_set func_08141708, 0x08141709
.endif
.ifndef OMIT_func_08141728
.global func_08141728
.thumb_set func_08141728, 0x08141729
.endif
.ifndef OMIT_func_08141780
.global func_08141780
.thumb_set func_08141780, 0x08141781
.endif
.ifndef OMIT_func_0814180C
.global func_0814180C
.thumb_set func_0814180C, 0x0814180d
.endif
.ifndef OMIT_func_08141838
.global func_08141838
.thumb_set func_08141838, 0x08141839
.endif
.ifndef OMIT_func_08141860
.global func_08141860
.thumb_set func_08141860, 0x08141861
.endif
.ifndef OMIT_func_08141868
.global func_08141868
.thumb_set func_08141868, 0x08141869
.endif
.ifndef OMIT_func_0814186C
.global func_0814186C
.thumb_set func_0814186C, 0x0814186d
.endif
.ifndef OMIT_func_08141870
.global func_08141870
.thumb_set func_08141870, 0x08141871
.endif
.ifndef OMIT_func_08141874
.global func_08141874
.thumb_set func_08141874, 0x08141875
.endif
.ifndef OMIT_func_08141890
.global func_08141890
.thumb_set func_08141890, 0x08141891
.endif
.ifndef OMIT_func_08141898
.global func_08141898
.thumb_set func_08141898, 0x08141899
.endif
.ifndef OMIT_func_08141AF0
.global func_08141AF0
.thumb_set func_08141AF0, 0x08141af1
.endif
.ifndef OMIT_func_08141BB0
.global func_08141BB0
.thumb_set func_08141BB0, 0x08141bb1
.endif
.ifndef OMIT_func_0814220C
.global func_0814220C
.thumb_set func_0814220C, 0x0814220d
.endif
.ifndef OMIT_func_08142248
.global func_08142248
.thumb_set func_08142248, 0x08142249
.endif
.ifndef OMIT_func_08142280
.global func_08142280
.thumb_set func_08142280, 0x08142281
.endif
.ifndef OMIT_func_08142750
.global func_08142750
.thumb_set func_08142750, 0x08142751
.endif
.ifndef OMIT_func_0814278C
.global func_0814278C
.thumb_set func_0814278C, 0x0814278d
.endif
.ifndef OMIT_func_08142950
.global func_08142950
.thumb_set func_08142950, 0x08142951
.endif
.ifndef OMIT_func_08142A20
.global func_08142A20
.thumb_set func_08142A20, 0x08142a21
.endif
.ifndef OMIT_func_08142A94
.global func_08142A94
.thumb_set func_08142A94, 0x08142a95
.endif
.ifndef OMIT_func_08143528
.global func_08143528
.thumb_set func_08143528, 0x08143529
.endif
.ifndef OMIT_func_081439C8
.global func_081439C8
.thumb_set func_081439C8, 0x081439c9
.endif
.ifndef OMIT_func_08143A84
.global func_08143A84
.thumb_set func_08143A84, 0x08143a85
.endif
.ifndef OMIT_func_08143B04
.global func_08143B04
.thumb_set func_08143B04, 0x08143b05
.endif
.ifndef OMIT_func_08143F44
.global func_08143F44
.thumb_set func_08143F44, 0x08143f45
.endif
.ifndef OMIT_func_08144378
.global func_08144378
.thumb_set func_08144378, 0x08144379
.endif
.ifndef OMIT_func_081443B0
.global func_081443B0
.thumb_set func_081443B0, 0x081443b1
.endif
.ifndef OMIT_func_081443FC
.global func_081443FC
.thumb_set func_081443FC, 0x081443fd
.endif
.ifndef OMIT_func_08144460
.global func_08144460
.thumb_set func_08144460, 0x08144461
.endif
.ifndef OMIT_func_081444B8
.global func_081444B8
.thumb_set func_081444B8, 0x081444b9
.endif
.ifndef OMIT_func_08144500
.global func_08144500
.thumb_set func_08144500, 0x08144501
.endif
.ifndef OMIT_func_08144510
.global func_08144510
.thumb_set func_08144510, 0x08144511
.endif
.ifndef OMIT_func_08144D94
.global func_08144D94
.thumb_set func_08144D94, 0x08144d95
.endif
.ifndef OMIT_func_08145098
.global func_08145098
.thumb_set func_08145098, 0x08145099
.endif
.ifndef OMIT_func_0814511C
.global func_0814511C
.thumb_set func_0814511C, 0x0814511d
.endif
.ifndef OMIT_func_081451B4
.global func_081451B4
.thumb_set func_081451B4, 0x081451b5
.endif
.ifndef OMIT_func_081451C0
.global func_081451C0
.thumb_set func_081451C0, 0x081451c1
.endif
.ifndef OMIT_func_081452C0
.global func_081452C0
.thumb_set func_081452C0, 0x081452c1
.endif
.ifndef OMIT_func_081452F4
.global func_081452F4
.thumb_set func_081452F4, 0x081452f5
.endif
.ifndef OMIT_func_08145358
.global func_08145358
.thumb_set func_08145358, 0x08145359
.endif
.ifndef OMIT_func_08145388
.global func_08145388
.thumb_set func_08145388, 0x08145389
.endif
.ifndef OMIT_func_08145798
.global func_08145798
.thumb_set func_08145798, 0x08145799
.endif
.ifndef OMIT_func_081457FC
.global func_081457FC
.thumb_set func_081457FC, 0x081457fd
.endif
.ifndef OMIT_func_081458AC
.global func_081458AC
.thumb_set func_081458AC, 0x081458ad
.endif
.ifndef OMIT_func_08145990
.global func_08145990
.thumb_set func_08145990, 0x08145991
.endif
.ifndef OMIT_func_08145B4C
.global func_08145B4C
.thumb_set func_08145B4C, 0x08145b4d
.endif
.ifndef OMIT_func_08146120
.global func_08146120
.thumb_set func_08146120, 0x08146121
.endif
.ifndef OMIT_func_081464C4
.global func_081464C4
.thumb_set func_081464C4, 0x081464c5
.endif
.ifndef OMIT_func_081465E8
.global func_081465E8
.thumb_set func_081465E8, 0x081465e9
.endif
.ifndef OMIT_func_08146BB0
.global func_08146BB0
.thumb_set func_08146BB0, 0x08146bb1
.endif
.ifndef OMIT_func_08146C8C
.global func_08146C8C
.thumb_set func_08146C8C, 0x08146c8d
.endif
.ifndef OMIT_func_08146D38
.global func_08146D38
.thumb_set func_08146D38, 0x08146d39
.endif
.ifndef OMIT_func_08146DC8
.global func_08146DC8
.thumb_set func_08146DC8, 0x08146dc9
.endif
.ifndef OMIT_func_08146FB8
.global func_08146FB8
.thumb_set func_08146FB8, 0x08146fb9
.endif
.ifndef OMIT_func_08147068
.global func_08147068
.thumb_set func_08147068, 0x08147069
.endif
.ifndef OMIT_func_081471E0
.global func_081471E0
.thumb_set func_081471E0, 0x081471e1
.endif
.ifndef OMIT_func_08147288
.global func_08147288
.thumb_set func_08147288, 0x08147289
.endif
.ifndef OMIT_func_081477DC
.global func_081477DC
.thumb_set func_081477DC, 0x081477dd
.endif
.ifndef OMIT_func_08147830
.global func_08147830
.thumb_set func_08147830, 0x08147831
.endif
.ifndef OMIT_func_081478DC
.global func_081478DC
.thumb_set func_081478DC, 0x081478dd
.endif
.ifndef OMIT_func_08147958
.global func_08147958
.thumb_set func_08147958, 0x08147959
.endif
.ifndef OMIT_func_081479DC
.global func_081479DC
.thumb_set func_081479DC, 0x081479dd
.endif
.ifndef OMIT_func_08147A7C
.global func_08147A7C
.thumb_set func_08147A7C, 0x08147a7d
.endif
.ifndef OMIT_func_08147AD0
.global func_08147AD0
.thumb_set func_08147AD0, 0x08147ad1
.endif
.ifndef OMIT_func_08147B28
.global func_08147B28
.thumb_set func_08147B28, 0x08147b29
.endif
.ifndef OMIT_func_08147D2C
.global func_08147D2C
.thumb_set func_08147D2C, 0x08147d2d
.endif
.ifndef OMIT_func_08147D94
.global func_08147D94
.thumb_set func_08147D94, 0x08147d95
.endif
.ifndef OMIT_func_08148104
.global func_08148104
.thumb_set func_08148104, 0x08148105
.endif
.ifndef OMIT_func_0814814C
.global func_0814814C
.thumb_set func_0814814C, 0x0814814d
.endif
.ifndef OMIT_func_081481AC
.global func_081481AC
.thumb_set func_081481AC, 0x081481ad
.endif
.ifndef OMIT_func_08148214
.global func_08148214
.thumb_set func_08148214, 0x08148215
.endif
.ifndef OMIT_func_08148274
.global func_08148274
.thumb_set func_08148274, 0x08148275
.endif
.ifndef OMIT_func_081482D4
.global func_081482D4
.thumb_set func_081482D4, 0x081482d5
.endif
.ifndef OMIT_func_08148318
.global func_08148318
.thumb_set func_08148318, 0x08148319
.endif
.ifndef OMIT_func_0814835C
.global func_0814835C
.thumb_set func_0814835C, 0x0814835d
.endif
.ifndef OMIT_func_08148384
.global func_08148384
.thumb_set func_08148384, 0x08148385
.endif
.ifndef OMIT_func_081483EC
.global func_081483EC
.thumb_set func_081483EC, 0x081483ed
.endif
.ifndef OMIT_func_0814846C
.global func_0814846C
.thumb_set func_0814846C, 0x0814846d
.endif
.ifndef OMIT_func_08148498
.global func_08148498
.thumb_set func_08148498, 0x08148499
.endif
.ifndef OMIT_func_081484CC
.global func_081484CC
.thumb_set func_081484CC, 0x081484cd
.endif
.ifndef OMIT_func_08148518
.global func_08148518
.thumb_set func_08148518, 0x08148519
.endif
.ifndef OMIT_func_0814852C
.global func_0814852C
.thumb_set func_0814852C, 0x0814852d
.endif
.ifndef OMIT_func_08148540
.global func_08148540
.thumb_set func_08148540, 0x08148541
.endif
.ifndef OMIT_func_08148588
.global func_08148588
.thumb_set func_08148588, 0x08148589
.endif
.ifndef OMIT_func_081485AC
.global func_081485AC
.thumb_set func_081485AC, 0x081485ad
.endif
.ifndef OMIT_func_081485D4
.global func_081485D4
.thumb_set func_081485D4, 0x081485d5
.endif
.ifndef OMIT_func_081485E8
.global func_081485E8
.thumb_set func_081485E8, 0x081485e9
.endif
.ifndef OMIT_func_08148600
.global func_08148600
.thumb_set func_08148600, 0x08148601
.endif
.ifndef OMIT_func_0814863C
.global func_0814863C
.thumb_set func_0814863C, 0x0814863d
.endif
.ifndef OMIT_func_08148684
.global func_08148684
.thumb_set func_08148684, 0x08148685
.endif
.ifndef OMIT_func_081486C8
.global func_081486C8
.thumb_set func_081486C8, 0x081486c9
.endif
.ifndef OMIT_func_08148704
.global func_08148704
.thumb_set func_08148704, 0x08148705
.endif
.ifndef OMIT_func_08148738
.global func_08148738
.thumb_set func_08148738, 0x08148739
.endif
.ifndef OMIT_func_0814873C
.global func_0814873C
.thumb_set func_0814873C, 0x0814873d
.endif
.ifndef OMIT_func_08148740
.global func_08148740
.thumb_set func_08148740, 0x08148741
.endif
.ifndef OMIT_func_08148788
.global func_08148788
.thumb_set func_08148788, 0x08148789
.endif
.ifndef OMIT_func_08148830
.global func_08148830
.thumb_set func_08148830, 0x08148831
.endif
.ifndef OMIT_func_08148860
.global func_08148860
.thumb_set func_08148860, 0x08148861
.endif
.ifndef OMIT_func_08148914
.global func_08148914
.thumb_set func_08148914, 0x08148915
.endif
.ifndef OMIT_func_0814913C
.global func_0814913C
.thumb_set func_0814913C, 0x0814913d
.endif
.ifndef OMIT_func_0814914C
.global func_0814914C
.thumb_set func_0814914C, 0x0814914d
.endif
.ifndef OMIT_func_081491C0
.global func_081491C0
.thumb_set func_081491C0, 0x081491c1
.endif
.ifndef OMIT_func_08149230
.global func_08149230
.thumb_set func_08149230, 0x08149231
.endif
.ifndef OMIT_func_081492A8
.global func_081492A8
.thumb_set func_081492A8, 0x081492a9
.endif
.ifndef OMIT_func_08149368
.global func_08149368
.thumb_set func_08149368, 0x08149369
.endif
.ifndef OMIT_func_081493AC
.global func_081493AC
.thumb_set func_081493AC, 0x081493ad
.endif
.ifndef OMIT_func_081493C0
.global func_081493C0
.thumb_set func_081493C0, 0x081493c1
.endif
.ifndef OMIT_func_0814941C
.global func_0814941C
.thumb_set func_0814941C, 0x0814941d
.endif
.global data_02001EE4
.set data_02001EE4, 0x02001ee4
.global data_02001F1C
.set data_02001F1C, 0x02001f1c
.global data_02001F30
.set data_02001F30, 0x02001f30
.global data_02001F3C
.set data_02001F3C, 0x02001f3c
.global data_0200216A
.set data_0200216A, 0x0200216a
.global data_02002190
.set data_02002190, 0x02002190
.global data_02002194
.set data_02002194, 0x02002194
.global data_020021B4
.set data_020021B4, 0x020021b4
.global data_02002948
.set data_02002948, 0x02002948
.global data_02002E64
.set data_02002E64, 0x02002e64
.global data_02002E78
.set data_02002E78, 0x02002e78
.global data_02003C3C
.set data_02003C3C, 0x02003c3c
.global data_02003CB0
.set data_02003CB0, 0x02003cb0
.global data_02004270
.set data_02004270, 0x02004270
.global data_02004EB0
.set data_02004EB0, 0x02004eb0
.global data_020078B0
.set data_020078B0, 0x020078b0
.global data_02007CB0
.set data_02007CB0, 0x02007cb0
.global data_02007F10
.set data_02007F10, 0x02007f10
.global data_02007F20
.set data_02007F20, 0x02007f20
.global data_02007F74
.set data_02007F74, 0x02007f74
.global data_02008158
.set data_02008158, 0x02008158
.global data_0200815C
.set data_0200815C, 0x0200815c
.global data_02008168
.set data_02008168, 0x02008168
.global data_02008390
.set data_02008390, 0x02008390
.global data_020084D8
.set data_020084D8, 0x020084d8
.global data_02008FF8
.set data_02008FF8, 0x02008ff8
.global data_02009024
.set data_02009024, 0x02009024
.global data_02009140
.set data_02009140, 0x02009140
.global data_02009148
.set data_02009148, 0x02009148
.global data_02009160
.set data_02009160, 0x02009160
.global data_02009168
.set data_02009168, 0x02009168
.global data_02009170
.set data_02009170, 0x02009170
.global data_02009174
.set data_02009174, 0x02009174
.global data_02009178
.set data_02009178, 0x02009178
.global data_0200917C
.set data_0200917C, 0x0200917c
.global data_02009180
.set data_02009180, 0x02009180
.global data_0200918C
.set data_0200918C, 0x0200918c
.global data_02009190
.set data_02009190, 0x02009190
.global data_02009198
.set data_02009198, 0x02009198
.global data_020091A0
.set data_020091A0, 0x020091a0
.global data_0200D1A0
.set data_0200D1A0, 0x0200d1a0
.global data_0200F1D0
.set data_0200F1D0, 0x0200f1d0
.global data_0200F1D8
.set data_0200F1D8, 0x0200f1d8
.global data_0200F23A
.set data_0200F23A, 0x0200f23a
.global data_0200F23B
.set data_0200F23B, 0x0200f23b
.global data_0200F2A0
.set data_0200F2A0, 0x0200f2a0
.global data_0200F2E0
.set data_0200F2E0, 0x0200f2e0
.global data_0200F320
.set data_0200F320, 0x0200f320
.global data_0200F37C
.set data_0200F37C, 0x0200f37c
.global data_0200F3A0
.set data_0200F3A0, 0x0200f3a0
.global data_0200F3AC
.set data_0200F3AC, 0x0200f3ac
.global data_0200F3B0
.set data_0200F3B0, 0x0200f3b0
.global data_0200F3B4
.set data_0200F3B4, 0x0200f3b4
.global data_0200F3B8
.set data_0200F3B8, 0x0200f3b8
.global data_0200F3BC
.set data_0200F3BC, 0x0200f3bc
.global data_0200F3C4
.set data_0200F3C4, 0x0200f3c4
.global data_0200F3C8
.set data_0200F3C8, 0x0200f3c8
.global data_0200F3F0
.set data_0200F3F0, 0x0200f3f0
.global data_0200F428
.set data_0200F428, 0x0200f428
.global data_0200F430
.set data_0200F430, 0x0200f430
.global data_0200F434
.set data_0200F434, 0x0200f434
.global data_0200F438
.set data_0200F438, 0x0200f438
.global data_0200F440
.set data_0200F440, 0x0200f440
.global data_0200F444
.set data_0200F444, 0x0200f444
.global data_0200F448
.set data_0200F448, 0x0200f448
.global data_0200F44C
.set data_0200F44C, 0x0200f44c
.global data_0200F450
.set data_0200F450, 0x0200f450
.global data_0200F454
.set data_0200F454, 0x0200f454
.global data_0200F458
.set data_0200F458, 0x0200f458
.global data_0200F47C
.set data_0200F47C, 0x0200f47c
.global data_0200F4A8
.set data_0200F4A8, 0x0200f4a8
.global data_0200F4AC
.set data_0200F4AC, 0x0200f4ac
.global data_0200F4C0
.set data_0200F4C0, 0x0200f4c0
.global data_0200F4E8
.set data_0200F4E8, 0x0200f4e8
.global data_0200F6A0
.set data_0200F6A0, 0x0200f6a0
.global data_0200F770
.set data_0200F770, 0x0200f770
.global data_0200F898
.set data_0200F898, 0x0200f898
.global data_0200F8A8
.set data_0200F8A8, 0x0200f8a8
.global data_0200F8C0
.set data_0200F8C0, 0x0200f8c0
.global data_0200F9E8
.set data_0200F9E8, 0x0200f9e8
.global data_0200FFC8
.set data_0200FFC8, 0x0200ffc8
.global data_02010050
.set data_02010050, 0x02010050
.global data_02010060
.set data_02010060, 0x02010060
.global data_020100C8
.set data_020100C8, 0x020100c8
.global data_02010130
.set data_02010130, 0x02010130
.global data_020101F0
.set data_020101F0, 0x020101f0
.global data_020101F8
.set data_020101F8, 0x020101f8
.global data_020156C4
.set data_020156C4, 0x020156c4
.global data_02015738
.set data_02015738, 0x02015738
.global data_02015744
.set data_02015744, 0x02015744
.global data_020158B0
.set data_020158B0, 0x020158b0
.global data_02015970
.set data_02015970, 0x02015970
.global data_020159C0
.set data_020159C0, 0x020159c0
.global data_020159C4
.set data_020159C4, 0x020159c4
.global data_020159C8
.set data_020159C8, 0x020159c8
.global data_020159CC
.set data_020159CC, 0x020159cc
.global data_0201C3C8
.set data_0201C3C8, 0x0201c3c8
.global data_0201F488
.set data_0201F488, 0x0201f488
.global data_0201F489
.set data_0201F489, 0x0201f489
.global data_0201F48A
.set data_0201F48A, 0x0201f48a
.global data_0201F48B
.set data_0201F48B, 0x0201f48b
.global data_0201F53A
.set data_0201F53A, 0x0201f53a
.global data_0201F53B
.set data_0201F53B, 0x0201f53b
.global data_0201F53C
.set data_0201F53C, 0x0201f53c
.global data_0201F540
.set data_0201F540, 0x0201f540
.global data_0201F544
.set data_0201F544, 0x0201f544
.global data_0201F548
.set data_0201F548, 0x0201f548
.global data_0201F54C
.set data_0201F54C, 0x0201f54c
.global data_0201F550
.set data_0201F550, 0x0201f550
.global data_03000000
.set data_03000000, 0x03000000
.global data_03000020
.set data_03000020, 0x03000020
.global data_03000028
.set data_03000028, 0x03000028
.global data_03000030
.set data_03000030, 0x03000030
.global data_030008B0
.set data_030008B0, 0x030008b0
.global data_03000930
.set data_03000930, 0x03000930
.global data_03000942
.set data_03000942, 0x03000942
.global data_03000990
.set data_03000990, 0x03000990
.global data_030009C4
.set data_030009C4, 0x030009c4
.global data_030009E0
.set data_030009E0, 0x030009e0
.global data_03000E10
.set data_03000E10, 0x03000e10
.global data_03000E30
.set data_03000E30, 0x03000e30
.global data_03000E54
.set data_03000E54, 0x03000e54
.global data_03000E60
.set data_03000E60, 0x03000e60
.global data_03000E80
.set data_03000E80, 0x03000e80
.global data_03000E98
.set data_03000E98, 0x03000e98
.global data_03000EB4
.set data_03000EB4, 0x03000eb4
.global data_03000ED0
.set data_03000ED0, 0x03000ed0
.global data_03002710
.set data_03002710, 0x03002710
.global data_03002730
.set data_03002730, 0x03002730
.global data_03002740
.set data_03002740, 0x03002740
.global data_03002778
.set data_03002778, 0x03002778
.global data_030027A4
.set data_030027A4, 0x030027a4
.global data_030027B0
.set data_030027B0, 0x030027b0
.global data_030027D4
.set data_030027D4, 0x030027d4
.global data_030027D8
.set data_030027D8, 0x030027d8
.global data_030027E0
.set data_030027E0, 0x030027e0
.global data_030027F0
.set data_030027F0, 0x030027f0
.global data_030027F4
.set data_030027F4, 0x030027f4
.global data_0300280C
.set data_0300280C, 0x0300280c
.global data_03002818
.set data_03002818, 0x03002818
.global data_0300284C
.set data_0300284C, 0x0300284c
.global data_03002892
.set data_03002892, 0x03002892
.global data_030028A0
.set data_030028A0, 0x030028a0
.global data_03002BB0
.set data_03002BB0, 0x03002bb0
.global data_03002BB4
.set data_03002BB4, 0x03002bb4
.global data_03002BB8
.set data_03002BB8, 0x03002bb8
.global data_03002BC0
.set data_03002BC0, 0x03002bc0
.global data_03002BC8
.set data_03002BC8, 0x03002bc8
.global data_03002BCC
.set data_03002BCC, 0x03002bcc
.global data_03002BD0
.set data_03002BD0, 0x03002bd0
.global data_03002C10
.set data_03002C10, 0x03002c10
.global data_03002C50
.set data_03002C50, 0x03002c50
.global data_03002C58
.set data_03002C58, 0x03002c58
.global data_03002F58
.set data_03002F58, 0x03002f58
.global data_03002F60
.set data_03002F60, 0x03002f60
.global data_03002F68
.set data_03002F68, 0x03002f68
.global data_03003168
.set data_03003168, 0x03003168
.global data_03003170
.set data_03003170, 0x03003170
.global data_030034B8
.set data_030034B8, 0x030034b8
.global data_030034C0
.set data_030034C0, 0x030034c0
.global data_030034D0
.set data_030034D0, 0x030034d0
.global data_030034D1
.set data_030034D1, 0x030034d1
.global data_030034D2
.set data_030034D2, 0x030034d2
.global data_030034D4
.set data_030034D4, 0x030034d4
.global data_03003860
.set data_03003860, 0x03003860
.global data_030039C8
.set data_030039C8, 0x030039c8
.global data_03003A60
.set data_03003A60, 0x03003a60
.global data_03003A62
.set data_03003A62, 0x03003a62
.global data_03003BA4
.set data_03003BA4, 0x03003ba4
.global data_03003C60
.set data_03003C60, 0x03003c60
.global data_03003C68
.set data_03003C68, 0x03003c68
.global data_03003E68
.set data_03003E68, 0x03003e68
.global data_03005668
.set data_03005668, 0x03005668
.global data_03005E68
.set data_03005E68, 0x03005e68
.global data_03005F28
.set data_03005F28, 0x03005f28
.global data_03005F2C
.set data_03005F2C, 0x03005f2c
.global data_04000004
.set data_04000004, 0x04000004
.global data_04000040
.set data_04000040, 0x04000040
.global data_040000D4
.set data_040000D4, 0x040000d4
.global data_0500018C
.set data_0500018C, 0x0500018c
.global data_06005000
.set data_06005000, 0x06005000
.global data_06005800
.set data_06005800, 0x06005800
.global data_06006000
.set data_06006000, 0x06006000
.global data_06007000
.set data_06007000, 0x06007000
.global data_06008000
.set data_06008000, 0x06008000
.global data_06008A40
.set data_06008A40, 0x06008a40
.global data_06009960
.set data_06009960, 0x06009960
.global data_0600A280
.set data_0600A280, 0x0600a280
.global data_0600AFE0
.set data_0600AFE0, 0x0600afe0
.global data_0600F9E0
.set data_0600F9E0, 0x0600f9e0
.global data_06010980
.set data_06010980, 0x06010980
.global data_06012400
.set data_06012400, 0x06012400
.global data_06013800
.set data_06013800, 0x06013800
.global data_06013840
.set data_06013840, 0x06013840
.global data_06016300
.set data_06016300, 0x06016300
.global data_08149890
.set data_08149890, 0x08149890
.global data_081498D0
.set data_081498D0, 0x081498d0
.global data_081498F0
.set data_081498F0, 0x081498f0
.global data_0836D128
.set data_0836D128, 0x0836d128
.global data_0836D1DC
.set data_0836D1DC, 0x0836d1dc
.global data_0836D224
.set data_0836D224, 0x0836d224
.global data_0836D2A8
.set data_0836D2A8, 0x0836d2a8
.global data_0836D2C0
.set data_0836D2C0, 0x0836d2c0
.global data_0836D340
.set data_0836D340, 0x0836d340
.global data_0836D470
.set data_0836D470, 0x0836d470
.global data_0836D4BC
.set data_0836D4BC, 0x0836d4bc
.global data_0836D4C0
.set data_0836D4C0, 0x0836d4c0
.global data_0836D62C
.set data_0836D62C, 0x0836d62c
.global data_0836D6E4
.set data_0836D6E4, 0x0836d6e4
.global data_0836D768
.set data_0836D768, 0x0836d768
.global data_0836DA1C
.set data_0836DA1C, 0x0836da1c
.global data_08391224
.set data_08391224, 0x08391224
.global data_08391530
.set data_08391530, 0x08391530
.global data_08391544
.set data_08391544, 0x08391544
.global data_08391576
.set data_08391576, 0x08391576
.global data_08391584
.set data_08391584, 0x08391584
.global data_0839168C
.set data_0839168C, 0x0839168c
.global data_0839176A
.set data_0839176A, 0x0839176a
.global data_08391772
.set data_08391772, 0x08391772
.global data_083917FA
.set data_083917FA, 0x083917fa
.global data_08391800
.set data_08391800, 0x08391800
.global data_08391803
.set data_08391803, 0x08391803
.global data_08391850
.set data_08391850, 0x08391850
.global data_08391960
.set data_08391960, 0x08391960
.global data_08391A48
.set data_08391A48, 0x08391a48
.global data_08391A5C
.set data_08391A5C, 0x08391a5c
.global data_08391A64
.set data_08391A64, 0x08391a64
.global data_08391A6C
.set data_08391A6C, 0x08391a6c
.global data_08391B20
.set data_08391B20, 0x08391b20
.global data_08391B48
.set data_08391B48, 0x08391b48
.global data_08391B50
.set data_08391B50, 0x08391b50
.global data_08391B58
.set data_08391B58, 0x08391b58
.global data_08391BBC
.set data_08391BBC, 0x08391bbc
.global data_08391BD0
.set data_08391BD0, 0x08391bd0
.global data_08391BE8
.set data_08391BE8, 0x08391be8
.global data_08391C08
.set data_08391C08, 0x08391c08
.global data_08391CA4
.set data_08391CA4, 0x08391ca4
.global data_08391D1C
.set data_08391D1C, 0x08391d1c
.global data_08391DE4
.set data_08391DE4, 0x08391de4
.global data_08391E02
.set data_08391E02, 0x08391e02
.global data_08391E40
.set data_08391E40, 0x08391e40
.global data_083937CE
.set data_083937CE, 0x083937ce
.global data_083937F8
.set data_083937F8, 0x083937f8
.global data_08393890
.set data_08393890, 0x08393890
.global data_08393918
.set data_08393918, 0x08393918
.global data_08393ADE
.set data_08393ADE, 0x08393ade
.global data_08393B00
.set data_08393B00, 0x08393b00
.global data_08393B40
.set data_08393B40, 0x08393b40
.global data_08393C6A
.set data_08393C6A, 0x08393c6a
.global data_08394030
.set data_08394030, 0x08394030
.global data_08394034
.set data_08394034, 0x08394034
.global data_08394038
.set data_08394038, 0x08394038
.global data_0839403C
.set data_0839403C, 0x0839403c
.global data_08394040
.set data_08394040, 0x08394040
.global data_08394048
.set data_08394048, 0x08394048
.global data_08394054
.set data_08394054, 0x08394054
.global data_08394354
.set data_08394354, 0x08394354
.global data_0839454C
.set data_0839454C, 0x0839454c
.global data_08394650
.set data_08394650, 0x08394650
.global data_0839465C
.set data_0839465C, 0x0839465c
.global data_0839469C
.set data_0839469C, 0x0839469c
.global data_083946A0
.set data_083946A0, 0x083946a0
.global data_083946C0
.set data_083946C0, 0x083946c0
.global data_0839470C
.set data_0839470C, 0x0839470c
.global data_0839471C
.set data_0839471C, 0x0839471c
.global data_08394734
.set data_08394734, 0x08394734
.global data_0839474C
.set data_0839474C, 0x0839474c
.global data_08394754
.set data_08394754, 0x08394754
.global data_083947D8
.set data_083947D8, 0x083947d8
.global data_0839554C
.set data_0839554C, 0x0839554c
.global data_08395574
.set data_08395574, 0x08395574
.global data_08395618
.set data_08395618, 0x08395618
.global data_08395E9C
.set data_08395E9C, 0x08395e9c
.global data_08395EC0
.set data_08395EC0, 0x08395ec0
.global data_08395ED8
.set data_08395ED8, 0x08395ed8
.global data_0839612C
.set data_0839612C, 0x0839612c
.global data_08396144
.set data_08396144, 0x08396144
.global data_0839639C
.set data_0839639C, 0x0839639c
.global data_083963C0
.set data_083963C0, 0x083963c0
.global data_083963E4
.set data_083963E4, 0x083963e4
.global data_083963ED
.set data_083963ED, 0x083963ed
.global data_083963F8
.set data_083963F8, 0x083963f8
.global data_0839641C
.set data_0839641C, 0x0839641c
.global data_08396440
.set data_08396440, 0x08396440
.global data_08396452
.set data_08396452, 0x08396452
.global data_0839646C
.set data_0839646C, 0x0839646c
.global data_08396474
.set data_08396474, 0x08396474
.global data_08396498
.set data_08396498, 0x08396498
.global data_08396B3C
.set data_08396B3C, 0x08396b3c
.global data_08396B78
.set data_08396B78, 0x08396b78
.global data_08396C08
.set data_08396C08, 0x08396c08
.global data_08396FF4
.set data_08396FF4, 0x08396ff4
.global data_08397030
.set data_08397030, 0x08397030
.global data_08397060
.set data_08397060, 0x08397060
.global data_08397078
.set data_08397078, 0x08397078
.global data_08397280
.set data_08397280, 0x08397280
.global data_083972BC
.set data_083972BC, 0x083972bc
.global data_0839731C
.set data_0839731C, 0x0839731c
.global data_0839756C
.set data_0839756C, 0x0839756c
.global data_083975CC
.set data_083975CC, 0x083975cc
.global data_08397614
.set data_08397614, 0x08397614
.global data_08397674
.set data_08397674, 0x08397674
.global data_083976A4
.set data_083976A4, 0x083976a4
.global data_083976BC
.set data_083976BC, 0x083976bc
.global data_083976D0
.set data_083976D0, 0x083976d0
.global data_08398EDC
.set data_08398EDC, 0x08398edc
.global data_08398F24
.set data_08398F24, 0x08398f24
.global data_08398FCC
.set data_08398FCC, 0x08398fcc
.global data_08398FE4
.set data_08398FE4, 0x08398fe4
.global data_083993CC
.set data_083993CC, 0x083993cc
.global data_083993D4
.set data_083993D4, 0x083993d4
.global data_0839945C
.set data_0839945C, 0x0839945c
.global data_08399480
.set data_08399480, 0x08399480
.global data_08399528
.set data_08399528, 0x08399528
.global data_0839953C
.set data_0839953C, 0x0839953c
.global data_083995B8
.set data_083995B8, 0x083995b8
.global data_08399600
.set data_08399600, 0x08399600
.global data_08399614
.set data_08399614, 0x08399614
.global data_08399978
.set data_08399978, 0x08399978
.global data_08399A04
.set data_08399A04, 0x08399a04
.global data_08399A1C
.set data_08399A1C, 0x08399a1c
.global data_08399A54
.set data_08399A54, 0x08399a54
.global data_08399A68
.set data_08399A68, 0x08399a68
.global data_08399C1C
.set data_08399C1C, 0x08399c1c
.global data_0839A358
.set data_0839A358, 0x0839a358
.global data_0839A378
.set data_0839A378, 0x0839a378
.global data_0839A380
.set data_0839A380, 0x0839a380
.global data_0839A398
.set data_0839A398, 0x0839a398
.global data_0839A3A0
.set data_0839A3A0, 0x0839a3a0
.global data_0839A3B8
.set data_0839A3B8, 0x0839a3b8
.global data_0839A3C0
.set data_0839A3C0, 0x0839a3c0
.global data_0839A4D4
.set data_0839A4D4, 0x0839a4d4
.global data_0839A880
.set data_0839A880, 0x0839a880
.global data_0839A8D8
.set data_0839A8D8, 0x0839a8d8
.global data_0839A8E0
.set data_0839A8E0, 0x0839a8e0
.global data_0839A94C
.set data_0839A94C, 0x0839a94c
.global data_0839A97C
.set data_0839A97C, 0x0839a97c
.global data_0839A9F4
.set data_0839A9F4, 0x0839a9f4
.global data_0839AA08
.set data_0839AA08, 0x0839aa08
.global data_0839AA10
.set data_0839AA10, 0x0839aa10
.global data_0839AA30
.set data_0839AA30, 0x0839aa30
.global data_0839AA48
.set data_0839AA48, 0x0839aa48
.global data_0839AA68
.set data_0839AA68, 0x0839aa68
.global data_0839AA70
.set data_0839AA70, 0x0839aa70
.global data_0839AA90
.set data_0839AA90, 0x0839aa90
.global data_0839AAA4
.set data_0839AAA4, 0x0839aaa4
.global data_0839AAB4
.set data_0839AAB4, 0x0839aab4
.global data_0839AABC
.set data_0839AABC, 0x0839aabc
.global data_0839AAC4
.set data_0839AAC4, 0x0839aac4
.global data_0839AACC
.set data_0839AACC, 0x0839aacc
.global data_0839AE74
.set data_0839AE74, 0x0839ae74
.global data_0839AE7C
.set data_0839AE7C, 0x0839ae7c
.global data_0839AEAC
.set data_0839AEAC, 0x0839aeac
.global data_0839AED4
.set data_0839AED4, 0x0839aed4
.global data_0839AEDC
.set data_0839AEDC, 0x0839aedc
.global data_0839B1A8
.set data_0839B1A8, 0x0839b1a8
.global data_0839B1C0
.set data_0839B1C0, 0x0839b1c0
.global data_0839B724
.set data_0839B724, 0x0839b724
.global data_0839B76C
.set data_0839B76C, 0x0839b76c
.global data_0839B7B0
.set data_0839B7B0, 0x0839b7b0
.global data_0839CC74
.set data_0839CC74, 0x0839cc74
.global data_0839CC7C
.set data_0839CC7C, 0x0839cc7c
.global data_0839CC80
.set data_0839CC80, 0x0839cc80
.global data_0839CEEC
.set data_0839CEEC, 0x0839ceec
.global data_0839CF10
.set data_0839CF10, 0x0839cf10
.global data_0839CF24
.set data_0839CF24, 0x0839cf24
.global data_0839CF28
.set data_0839CF28, 0x0839cf28
.global data_0839CF9C
.set data_0839CF9C, 0x0839cf9c
.global data_0839D014
.set data_0839D014, 0x0839d014
.global data_0839D0B4
.set data_0839D0B4, 0x0839d0b4
.global data_0839D0D8
.set data_0839D0D8, 0x0839d0d8
.global data_0839D150
.set data_0839D150, 0x0839d150
.global data_0839D164
.set data_0839D164, 0x0839d164
.global data_0839D168
.set data_0839D168, 0x0839d168
.global data_0839D288
.set data_0839D288, 0x0839d288
.global data_0839D2B8
.set data_0839D2B8, 0x0839d2b8
.global data_0839D2E0
.set data_0839D2E0, 0x0839d2e0
.global data_0839D394
.set data_0839D394, 0x0839d394
.global data_0839D3D0
.set data_0839D3D0, 0x0839d3d0
.global data_0839D5C8
.set data_0839D5C8, 0x0839d5c8
.global data_0839D5E0
.set data_0839D5E0, 0x0839d5e0
.global data_0839D640
.set data_0839D640, 0x0839d640
.global data_0839D654
.set data_0839D654, 0x0839d654
.global data_0839D874
.set data_0839D874, 0x0839d874
.global data_0839D8A4
.set data_0839D8A4, 0x0839d8a4
.global data_0839D8C0
.set data_0839D8C0, 0x0839d8c0
.global data_0839DC84
.set data_0839DC84, 0x0839dc84
.global data_0839DCB4
.set data_0839DCB4, 0x0839dcb4
.global data_0839DCFC
.set data_0839DCFC, 0x0839dcfc
.global data_0839DD10
.set data_0839DD10, 0x0839dd10
.global data_0839DD18
.set data_0839DD18, 0x0839dd18
.global data_0839DDC8
.set data_0839DDC8, 0x0839ddc8
.global data_0839DDD0
.set data_0839DDD0, 0x0839ddd0
.global data_0839DDD4
.set data_0839DDD4, 0x0839ddd4
.global data_0839DDEC
.set data_0839DDEC, 0x0839ddec
.global data_0839DE00
.set data_0839DE00, 0x0839de00
.global data_0839DE08
.set data_0839DE08, 0x0839de08
.global data_0839DE0C
.set data_0839DE0C, 0x0839de0c
.global data_0839E2F8
.set data_0839E2F8, 0x0839e2f8
.global data_0839E358
.set data_0839E358, 0x0839e358
.global data_0839E388
.set data_0839E388, 0x0839e388
.global data_0839E38C
.set data_0839E38C, 0x0839e38c
.global data_0839E39C
.set data_0839E39C, 0x0839e39c
.global data_0839E3A2
.set data_0839E3A2, 0x0839e3a2
.global data_0839E540
.set data_0839E540, 0x0839e540
.global data_0839E564
.set data_0839E564, 0x0839e564
.global data_0839E5C4
.set data_0839E5C4, 0x0839e5c4
.global data_0839E5D8
.set data_0839E5D8, 0x0839e5d8
.global data_0839E5DC
.set data_0839E5DC, 0x0839e5dc
.global data_0839E60C
.set data_0839E60C, 0x0839e60c
.global data_0839E630
.set data_0839E630, 0x0839e630
.global data_0839E678
.set data_0839E678, 0x0839e678
.global data_0839E68C
.set data_0839E68C, 0x0839e68c
.global data_0839E690
.set data_0839E690, 0x0839e690
.global data_0839E698
.set data_0839E698, 0x0839e698
.global data_0839E6D0
.set data_0839E6D0, 0x0839e6d0
.global data_0839E6F4
.set data_0839E6F4, 0x0839e6f4
.global data_0839E724
.set data_0839E724, 0x0839e724
.global data_0839E754
.set data_0839E754, 0x0839e754
.global data_0839E76C
.set data_0839E76C, 0x0839e76c
.global data_0839E774
.set data_0839E774, 0x0839e774
.global data_0839E77C
.set data_0839E77C, 0x0839e77c
.global data_0839E784
.set data_0839E784, 0x0839e784
.global data_0839E8B8
.set data_0839E8B8, 0x0839e8b8
.global data_0839E8DC
.set data_0839E8DC, 0x0839e8dc
.global data_0839E93C
.set data_0839E93C, 0x0839e93c
.global data_0839E950
.set data_0839E950, 0x0839e950
.global data_0839E954
.set data_0839E954, 0x0839e954
.global data_0839EB94
.set data_0839EB94, 0x0839eb94
.global data_0839EBC4
.set data_0839EBC4, 0x0839ebc4
.global data_0839EC24
.set data_0839EC24, 0x0839ec24
.global data_0839EC38
.set data_0839EC38, 0x0839ec38
.global data_0839EC80
.set data_0839EC80, 0x0839ec80
.global data_0839ECB0
.set data_0839ECB0, 0x0839ecb0
.global data_0839ECE0
.set data_0839ECE0, 0x0839ece0
.global data_0839ECF4
.set data_0839ECF4, 0x0839ecf4
.global data_0839EDC8
.set data_0839EDC8, 0x0839edc8
.global data_0839EDEC
.set data_0839EDEC, 0x0839edec
.global data_0839EE1C
.set data_0839EE1C, 0x0839ee1c
.global data_0839EE30
.set data_0839EE30, 0x0839ee30
.global data_0839EE60
.set data_0839EE60, 0x0839ee60
.global data_0839EE84
.set data_0839EE84, 0x0839ee84
.global data_0839EE9C
.set data_0839EE9C, 0x0839ee9c
.global data_0839EEE4
.set data_0839EEE4, 0x0839eee4
.global data_0839EF14
.set data_0839EF14, 0x0839ef14
.global data_0839EF44
.set data_0839EF44, 0x0839ef44
.global data_0839EF5C
.set data_0839EF5C, 0x0839ef5c
.global data_0839EF70
.set data_0839EF70, 0x0839ef70
.global data_0839F014
.set data_0839F014, 0x0839f014
.global data_0839F02C
.set data_0839F02C, 0x0839f02c
.global data_0839F044
.set data_0839F044, 0x0839f044
.global data_0839F058
.set data_0839F058, 0x0839f058
.global data_0839F05C
.set data_0839F05C, 0x0839f05c
.global data_0839F094
.set data_0839F094, 0x0839f094
.global data_0839F0C4
.set data_0839F0C4, 0x0839f0c4
.global data_0839F0DC
.set data_0839F0DC, 0x0839f0dc
.global data_0839F0F0
.set data_0839F0F0, 0x0839f0f0
.global data_0839F0F4
.set data_0839F0F4, 0x0839f0f4
.global data_0839F11C
.set data_0839F11C, 0x0839f11c
.global data_0839F134
.set data_0839F134, 0x0839f134
.global data_0839F194
.set data_0839F194, 0x0839f194
.global data_0839F1A8
.set data_0839F1A8, 0x0839f1a8
.global data_0839F4F8
.set data_0839F4F8, 0x0839f4f8
.global data_0839F528
.set data_0839F528, 0x0839f528
.global data_0839F5A0
.set data_0839F5A0, 0x0839f5a0
.global data_0839F5B4
.set data_0839F5B4, 0x0839f5b4
.global data_0839F5E4
.set data_0839F5E4, 0x0839f5e4
.global data_0839F5FC
.set data_0839F5FC, 0x0839f5fc
.global data_0839F644
.set data_0839F644, 0x0839f644
.global data_0839F658
.set data_0839F658, 0x0839f658
.global data_0839F690
.set data_0839F690, 0x0839f690
.global data_0839F6B4
.set data_0839F6B4, 0x0839f6b4
.global data_0839F6E4
.set data_0839F6E4, 0x0839f6e4
.global data_0839F6F8
.set data_0839F6F8, 0x0839f6f8
.global data_0839F75C
.set data_0839F75C, 0x0839f75c
.global data_0839F764
.set data_0839F764, 0x0839f764
.global data_0839F78C
.set data_0839F78C, 0x0839f78c
.global data_0839F7B4
.set data_0839F7B4, 0x0839f7b4
.global data_0839F7E4
.set data_0839F7E4, 0x0839f7e4
.global data_0839F808
.set data_0839F808, 0x0839f808
.global data_0839F880
.set data_0839F880, 0x0839f880
.global data_0839F890
.set data_0839F890, 0x0839f890
.global data_0839F8C0
.set data_0839F8C0, 0x0839f8c0
.global data_0839F8E4
.set data_0839F8E4, 0x0839f8e4
.global data_0839F98C
.set data_0839F98C, 0x0839f98c
.global data_0839F9A0
.set data_0839F9A0, 0x0839f9a0
.global data_0839FD8C
.set data_0839FD8C, 0x0839fd8c
.global data_0839FDAC
.set data_0839FDAC, 0x0839fdac
.global data_0839FDCC
.set data_0839FDCC, 0x0839fdcc
.global data_0839FDE0
.set data_0839FDE0, 0x0839fde0
.global data_0839FEBC
.set data_0839FEBC, 0x0839febc
.global data_0839FEC8
.set data_0839FEC8, 0x0839fec8
.global data_0839FF14
.set data_0839FF14, 0x0839ff14
.global data_0839FFF8
.set data_0839FFF8, 0x0839fff8
.global data_083A0004
.set data_083A0004, 0x083a0004
.global data_083A0008
.set data_083A0008, 0x083a0008
.global data_083A0030
.set data_083A0030, 0x083a0030
.global data_083A0064
.set data_083A0064, 0x083a0064
.global data_083A00B8
.set data_083A00B8, 0x083a00b8
.global data_083A0100
.set data_083A0100, 0x083a0100
.global data_083A0148
.set data_083A0148, 0x083a0148
.global data_083A015C
.set data_083A015C, 0x083a015c
.global data_083A01AC
.set data_083A01AC, 0x083a01ac
.global data_083A01E8
.set data_083A01E8, 0x083a01e8
.global data_083A0230
.set data_083A0230, 0x083a0230
.global data_083A0240
.set data_083A0240, 0x083a0240
.global data_083A0268
.set data_083A0268, 0x083a0268
.global data_083A02C0
.set data_083A02C0, 0x083a02c0
.global data_083A0308
.set data_083A0308, 0x083a0308
.global data_083A0368
.set data_083A0368, 0x083a0368
.global data_083A0390
.set data_083A0390, 0x083a0390
.global data_083A03C0
.set data_083A03C0, 0x083a03c0
.global data_083A03E4
.set data_083A03E4, 0x083a03e4
.global data_083A042C
.set data_083A042C, 0x083a042c
.global data_083A0440
.set data_083A0440, 0x083a0440
.global data_083A0488
.set data_083A0488, 0x083a0488
.global data_083A04B8
.set data_083A04B8, 0x083a04b8
.global data_083A04E8
.set data_083A04E8, 0x083a04e8
.global data_083A04FC
.set data_083A04FC, 0x083a04fc
.global data_083A054C
.set data_083A054C, 0x083a054c
.global data_083A0588
.set data_083A0588, 0x083a0588
.global data_083A05D0
.set data_083A05D0, 0x083a05d0
.global data_083A05E4
.set data_083A05E4, 0x083a05e4
.global data_083A0634
.set data_083A0634, 0x083a0634
.global data_083A067C
.set data_083A067C, 0x083a067c
.global data_083A06C4
.set data_083A06C4, 0x083a06c4
.global data_083A06D8
.set data_083A06D8, 0x083a06d8
.global data_083A0720
.set data_083A0720, 0x083a0720
.global data_083A0750
.set data_083A0750, 0x083a0750
.global data_083A0798
.set data_083A0798, 0x083a0798
.global data_083A07AC
.set data_083A07AC, 0x083a07ac
.global data_083A07FC
.set data_083A07FC, 0x083a07fc
.global data_083A0838
.set data_083A0838, 0x083a0838
.global data_083A0868
.set data_083A0868, 0x083a0868
.global data_083A087C
.set data_083A087C, 0x083a087c
.global data_083A08CC
.set data_083A08CC, 0x083a08cc
.global data_083A0908
.set data_083A0908, 0x083a0908
.global data_083A0938
.set data_083A0938, 0x083a0938
.global data_083A094C
.set data_083A094C, 0x083a094c
.global data_083A0A38
.set data_083A0A38, 0x083a0a38
.global data_083A0A5C
.set data_083A0A5C, 0x083a0a5c
.global data_083A0B1C
.set data_083A0B1C, 0x083a0b1c
.global data_083A0B30
.set data_083A0B30, 0x083a0b30
.global data_083A0B34
.set data_083A0B34, 0x083a0b34
.global data_083A0BB4
.set data_083A0BB4, 0x083a0bb4
.global data_083A0BF0
.set data_083A0BF0, 0x083a0bf0
.global data_083A0C08
.set data_083A0C08, 0x083a0c08
.global data_083A0C38
.set data_083A0C38, 0x083a0c38
.global data_083A0C4C
.set data_083A0C4C, 0x083a0c4c
.global data_083A0C54
.set data_083A0C54, 0x083a0c54
.global data_083A0F20
.set data_083A0F20, 0x083a0f20
.global data_083A107C
.set data_083A107C, 0x083a107c
.global data_083A11E0
.set data_083A11E0, 0x083a11e0
.global data_083A1204
.set data_083A1204, 0x083a1204
.global data_083A120C
.set data_083A120C, 0x083a120c
.global data_083A1210
.set data_083A1210, 0x083a1210
.global data_083A1224
.set data_083A1224, 0x083a1224
.global data_083A1254
.set data_083A1254, 0x083a1254
.global data_083A1278
.set data_083A1278, 0x083a1278
.global data_083A1290
.set data_083A1290, 0x083a1290
.global data_083A12A4
.set data_083A12A4, 0x083a12a4
.global data_083A12AC
.set data_083A12AC, 0x083a12ac
.global data_083A16D4
.set data_083A16D4, 0x083a16d4
.global data_083A16EC
.set data_083A16EC, 0x083a16ec
.global data_083A1708
.set data_083A1708, 0x083a1708
.global data_083A17C4
.set data_083A17C4, 0x083a17c4
.global data_083A1810
.set data_083A1810, 0x083a1810
.global data_083A1858
.set data_083A1858, 0x083a1858
.global data_083A1870
.set data_083A1870, 0x083a1870
.global data_083A18B8
.set data_083A18B8, 0x083a18b8
.global data_083A18CC
.set data_083A18CC, 0x083a18cc
.global data_083A18D0
.set data_083A18D0, 0x083a18d0
.global data_083A1AD4
.set data_083A1AD4, 0x083a1ad4
.global data_083A1B1C
.set data_083A1B1C, 0x083a1b1c
.global data_083A1B9C
.set data_083A1B9C, 0x083a1b9c
.global data_083A1BC0
.set data_083A1BC0, 0x083a1bc0
.global data_083A1C20
.set data_083A1C20, 0x083a1c20
.global data_083A1C34
.set data_083A1C34, 0x083a1c34
.global data_083A1C38
.set data_083A1C38, 0x083a1c38
.global data_083A1C78
.set data_083A1C78, 0x083a1c78
.global data_083A1CAC
.set data_083A1CAC, 0x083a1cac
.global data_083A1E48
.set data_083A1E48, 0x083a1e48
.global data_083A1E60
.set data_083A1E60, 0x083a1e60
.global data_083A1E78
.set data_083A1E78, 0x083a1e78
.global data_083A1E8C
.set data_083A1E8C, 0x083a1e8c
.global data_083A1E94
.set data_083A1E94, 0x083a1e94
.global data_083A1F5C
.set data_083A1F5C, 0x083a1f5c
.global data_083A1F8C
.set data_083A1F8C, 0x083a1f8c
.global data_083A1FA4
.set data_083A1FA4, 0x083a1fa4
.global data_083A1FB8
.set data_083A1FB8, 0x083a1fb8
.global data_083A1FC0
.set data_083A1FC0, 0x083a1fc0
.global data_083A1FC8
.set data_083A1FC8, 0x083a1fc8
.global data_083A2000
.set data_083A2000, 0x083a2000
.global data_083A203C
.set data_083A203C, 0x083a203c
.global data_083A2084
.set data_083A2084, 0x083a2084
.global data_083A209C
.set data_083A209C, 0x083a209c
.global data_083A20B0
.set data_083A20B0, 0x083a20b0
.global data_083A20B8
.set data_083A20B8, 0x083a20b8
.global data_083A20C0
.set data_083A20C0, 0x083a20c0
.global data_083A20F0
.set data_083A20F0, 0x083a20f0
.global data_083A2114
.set data_083A2114, 0x083a2114
.global data_083A215C
.set data_083A215C, 0x083a215c
.global data_083A21A4
.set data_083A21A4, 0x083a21a4
.global data_083A21B8
.set data_083A21B8, 0x083a21b8
.global data_083A21C0
.set data_083A21C0, 0x083a21c0
.global data_083A21C8
.set data_083A21C8, 0x083a21c8
.global data_083A2310
.set data_083A2310, 0x083a2310
.global data_083A2334
.set data_083A2334, 0x083a2334
.global data_083A23AC
.set data_083A23AC, 0x083a23ac
.global data_083A23B0
.set data_083A23B0, 0x083a23b0
.global data_083A23B8
.set data_083A23B8, 0x083a23b8
.global data_083A23C0
.set data_083A23C0, 0x083a23c0
.global data_083A23C8
.set data_083A23C8, 0x083a23c8
.global data_083A2400
.set data_083A2400, 0x083a2400
.global data_083A2424
.set data_083A2424, 0x083a2424
.global data_083A24B4
.set data_083A24B4, 0x083a24b4
.global data_083A24C8
.set data_083A24C8, 0x083a24c8
.global data_083A24CC
.set data_083A24CC, 0x083a24cc
.global data_083A24D4
.set data_083A24D4, 0x083a24d4
.global data_083A24DC
.set data_083A24DC, 0x083a24dc
.global data_083A24E4
.set data_083A24E4, 0x083a24e4
.global data_083A2650
.set data_083A2650, 0x083a2650
.global data_083A2668
.set data_083A2668, 0x083a2668
.global data_083A267C
.set data_083A267C, 0x083a267c
.global data_083A2718
.set data_083A2718, 0x083a2718
.global data_083A272C
.set data_083A272C, 0x083a272c
.global data_083A275C
.set data_083A275C, 0x083a275c
.global data_083A278C
.set data_083A278C, 0x083a278c
.global data_083A27A4
.set data_083A27A4, 0x083a27a4
.global data_083A27B8
.set data_083A27B8, 0x083a27b8
.global data_083A29B0
.set data_083A29B0, 0x083a29b0
.global data_083A29D4
.set data_083A29D4, 0x083a29d4
.global data_083A29EC
.set data_083A29EC, 0x083a29ec
.global data_083A2A00
.set data_083A2A00, 0x083a2a00
.global data_083A2A38
.set data_083A2A38, 0x083a2a38
.global data_083A2A68
.set data_083A2A68, 0x083a2a68
.global data_083A2B28
.set data_083A2B28, 0x083a2b28
.global data_083A2B50
.set data_083A2B50, 0x083a2b50
.global data_083A2BA8
.set data_083A2BA8, 0x083a2ba8
.global data_083A2BF0
.set data_083A2BF0, 0x083a2bf0
.global data_083A2C08
.set data_083A2C08, 0x083a2c08
.global data_083A2C1C
.set data_083A2C1C, 0x083a2c1c
.global data_083A2C24
.set data_083A2C24, 0x083a2c24
.global data_083A33D4
.set data_083A33D4, 0x083a33d4
.global data_083A33DC
.set data_083A33DC, 0x083a33dc
.global data_083A34D8
.set data_083A34D8, 0x083a34d8
.global data_083A35C0
.set data_083A35C0, 0x083a35c0
.global data_083A37A0
.set data_083A37A0, 0x083a37a0
.global data_083A4D1C
.set data_083A4D1C, 0x083a4d1c
.global data_083A4D64
.set data_083A4D64, 0x083a4d64
.global data_083A4EB4
.set data_083A4EB4, 0x083a4eb4
.global data_083A4FD4
.set data_083A4FD4, 0x083a4fd4
.global data_083A4FE4
.set data_083A4FE4, 0x083a4fe4
.global data_083A4FF4
.set data_083A4FF4, 0x083a4ff4
.global data_083A4FF8
.set data_083A4FF8, 0x083a4ff8
.global data_083A500C
.set data_083A500C, 0x083a500c
.global data_083A5014
.set data_083A5014, 0x083a5014
.global data_083A501C
.set data_083A501C, 0x083a501c
.global data_083A6348
.set data_083A6348, 0x083a6348
.global data_083A6390
.set data_083A6390, 0x083a6390
.global data_083A63A8
.set data_083A63A8, 0x083a63a8
.global data_083A63AC
.set data_083A63AC, 0x083a63ac
.global data_083A63C0
.set data_083A63C0, 0x083a63c0
.global data_083A6530
.set data_083A6530, 0x083a6530
.global data_083A6548
.set data_083A6548, 0x083a6548
.global data_083A6564
.set data_083A6564, 0x083a6564
.global data_083A6650
.set data_083A6650, 0x083a6650
.global data_083A6674
.set data_083A6674, 0x083a6674
.global data_083A6688
.set data_083A6688, 0x083a6688
.global data_083A6690
.set data_083A6690, 0x083a6690
.global data_083A66C8
.set data_083A66C8, 0x083a66c8
.global data_083A66F8
.set data_083A66F8, 0x083a66f8
.global data_083A6740
.set data_083A6740, 0x083a6740
.global data_083A6754
.set data_083A6754, 0x083a6754
.global data_083A6774
.set data_083A6774, 0x083a6774
.global data_083A678C
.set data_083A678C, 0x083a678c
.global data_083A67B4
.set data_083A67B4, 0x083a67b4
.global data_083A67CC
.set data_083A67CC, 0x083a67cc
.global data_083A67E0
.set data_083A67E0, 0x083a67e0
.global data_083A67E8
.set data_083A67E8, 0x083a67e8
.global data_083A6A08
.set data_083A6A08, 0x083a6a08
.global data_083A6CE4
.set data_083A6CE4, 0x083a6ce4
.global data_083A70AC
.set data_083A70AC, 0x083a70ac
.global data_083A711C
.set data_083A711C, 0x083a711c
.global data_083A7170
.set data_083A7170, 0x083a7170
.global data_083A7200
.set data_083A7200, 0x083a7200
.global data_083A7218
.set data_083A7218, 0x083a7218
.global data_083A736C
.set data_083A736C, 0x083a736c
.global data_083A7530
.set data_083A7530, 0x083a7530
.global data_083A7546
.set data_083A7546, 0x083a7546
.global data_083A755C
.set data_083A755C, 0x083a755c
.global data_083A7572
.set data_083A7572, 0x083a7572
.global data_083A7588
.set data_083A7588, 0x083a7588
.global data_083A75A8
.set data_083A75A8, 0x083a75a8
.global data_083A75E8
.set data_083A75E8, 0x083a75e8
.global data_083A7628
.set data_083A7628, 0x083a7628
.global data_083A7668
.set data_083A7668, 0x083a7668
.global data_083A796C
.set data_083A796C, 0x083a796c
.global data_083A7EE4
.set data_083A7EE4, 0x083a7ee4
.global data_083A8284
.set data_083A8284, 0x083a8284
.global data_083A8295
.set data_083A8295, 0x083a8295
.global data_083A8298
.set data_083A8298, 0x083a8298
.global data_083A82AC
.set data_083A82AC, 0x083a82ac
.global data_083A82BA
.set data_083A82BA, 0x083a82ba
.global data_083A82C8
.set data_083A82C8, 0x083a82c8
.global data_083A82DC
.set data_083A82DC, 0x083a82dc
.global data_083A82E4
.set data_083A82E4, 0x083a82e4
.global data_083A82EC
.set data_083A82EC, 0x083a82ec
.global data_083A8320
.set data_083A8320, 0x083a8320
.global data_083A844C
.set data_083A844C, 0x083a844c
.global data_083A8472
.set data_083A8472, 0x083a8472
.global data_083A8604
.set data_083A8604, 0x083a8604
.global data_083A8678
.set data_083A8678, 0x083a8678
.global data_083A87B0
.set data_083A87B0, 0x083a87b0
.global data_083A8C54
.set data_083A8C54, 0x083a8c54
.global data_083A8C9E
.set data_083A8C9E, 0x083a8c9e
.global data_083A8CAC
.set data_083A8CAC, 0x083a8cac
.global data_083A8CC0
.set data_083A8CC0, 0x083a8cc0
.global data_083A8D60
.set data_083A8D60, 0x083a8d60
.global data_083A8DAC
.set data_083A8DAC, 0x083a8dac
.global data_083A8DF8
.set data_083A8DF8, 0x083a8df8
.global data_083A8DFA
.set data_083A8DFA, 0x083a8dfa
.global data_083A8E44
.set data_083A8E44, 0x083a8e44
.global data_083A9058
.set data_083A9058, 0x083a9058
.global data_083A93AC
.set data_083A93AC, 0x083a93ac
.global data_083A94CC
.set data_083A94CC, 0x083a94cc
.global data_083A9CA4
.set data_083A9CA4, 0x083a9ca4
.global data_083AB42C
.set data_083AB42C, 0x083ab42c
.global data_083AEEA4
.set data_083AEEA4, 0x083aeea4
.global data_083AF504
.set data_083AF504, 0x083af504
.global data_083AF62C
.set data_083AF62C, 0x083af62c
.global data_083AF6CC
.set data_083AF6CC, 0x083af6cc
.global data_083B8F50
.set data_083B8F50, 0x083b8f50
.global data_083C3954
.set data_083C3954, 0x083c3954
.global data_083C4AD8
.set data_083C4AD8, 0x083c4ad8
.global data_083C5454
.set data_083C5454, 0x083c5454
.global data_083D5A1C
.set data_083D5A1C, 0x083d5a1c
.global data_083D965C
.set data_083D965C, 0x083d965c
.global data_083DD360
.set data_083DD360, 0x083dd360
.global data_083E105C
.set data_083E105C, 0x083e105c
.global data_08417F88
.set data_08417F88, 0x08417f88
.global data_08418F14
.set data_08418F14, 0x08418f14
.global data_084199E0
.set data_084199E0, 0x084199e0
.global data_08419BE0
.set data_08419BE0, 0x08419be0
.global data_08419C60
.set data_08419C60, 0x08419c60
.global data_08419CE0
.set data_08419CE0, 0x08419ce0
.global data_08419D60
.set data_08419D60, 0x08419d60
.global data_0841A560
.set data_0841A560, 0x0841a560
.global data_0841A860
.set data_0841A860, 0x0841a860
.global data_0841B060
.set data_0841B060, 0x0841b060
.global data_0841B340
.set data_0841B340, 0x0841b340
.global data_0841BB40
.set data_0841BB40, 0x0841bb40
.global data_0841CE4C
.set data_0841CE4C, 0x0841ce4c
.global data_0841CE9C
.set data_0841CE9C, 0x0841ce9c
.global data_08422894
.set data_08422894, 0x08422894
.global data_084229B8
.set data_084229B8, 0x084229b8
.global data_08425104
.set data_08425104, 0x08425104
.global data_08433330
.set data_08433330, 0x08433330
.global data_084966B0
.set data_084966B0, 0x084966b0
.global data_08497418
.set data_08497418, 0x08497418
.global data_084A002C
.set data_084A002C, 0x084a002c
.global data_084AADFC
.set data_084AADFC, 0x084aadfc
.global data_084B83A0
.set data_084B83A0, 0x084b83a0
.global data_084C3798
.set data_084C3798, 0x084c3798
.global data_084C3D50
.set data_084C3D50, 0x084c3d50
.global data_084EF3F4
.set data_084EF3F4, 0x084ef3f4
.global data_084F6130
.set data_084F6130, 0x084f6130
.global data_084F7B24
.set data_084F7B24, 0x084f7b24
.global data_084FA3B0
.set data_084FA3B0, 0x084fa3b0
.global data_084FE8B0
.set data_084FE8B0, 0x084fe8b0
.global data_084FF2AC
.set data_084FF2AC, 0x084ff2ac
.global data_084FF654
.set data_084FF654, 0x084ff654
.global data_08502CF0
.set data_08502CF0, 0x08502cf0
.global data_08502ED8
.set data_08502ED8, 0x08502ed8
.global data_08504D8C
.set data_08504D8C, 0x08504d8c
.global data_08505D34
.set data_08505D34, 0x08505d34
.global data_08505D4C
.set data_08505D4C, 0x08505d4c
.global data_08506E80
.set data_08506E80, 0x08506e80
.global data_0850875C
.set data_0850875C, 0x0850875c
.global data_085087D8
.set data_085087D8, 0x085087d8
.global data_08509094
.set data_08509094, 0x08509094
.global data_0850939C
.set data_0850939C, 0x0850939c
.global data_0851BA52
.set data_0851BA52, 0x0851ba52
.global data_0851BA5A
.set data_0851BA5A, 0x0851ba5a
.global data_0851BA62
.set data_0851BA62, 0x0851ba62
.global data_0851BA72
.set data_0851BA72, 0x0851ba72
.global data_0851BA7A
.set data_0851BA7A, 0x0851ba7a
.global data_0851D0F4
.set data_0851D0F4, 0x0851d0f4
.global data_0851FAA4
.set data_0851FAA4, 0x0851faa4
.global data_085231A4
.set data_085231A4, 0x085231a4
.global data_08526CD8
.set data_08526CD8, 0x08526cd8
.global data_08527D5C
.set data_08527D5C, 0x08527d5c
.global data_08527E1C
.set data_08527E1C, 0x08527e1c
.global data_08528968
.set data_08528968, 0x08528968
.global data_0852A13E
.set data_0852A13E, 0x0852a13e
.global data_0852A212
.set data_0852A212, 0x0852a212
.global data_0855187C
.set data_0855187C, 0x0855187c
.global data_08553E70
.set data_08553E70, 0x08553e70
.global data_085668B0
.set data_085668B0, 0x085668b0
.global data_08569034
.set data_08569034, 0x08569034
.global data_08569104
.set data_08569104, 0x08569104
.global data_0869B89C
.set data_0869B89C, 0x0869b89c
.global data_08852E7C
.set data_08852E7C, 0x08852e7c
.global data_088E9C70
.set data_088E9C70, 0x088e9c70
.global data_088EA4C4
.set data_088EA4C4, 0x088ea4c4
.global data_088EA550
.set data_088EA550, 0x088ea550
.global data_088EA7F0
.set data_088EA7F0, 0x088ea7f0
.global data_088EB4A4
.set data_088EB4A4, 0x088eb4a4
.global data_088ED3F0
.set data_088ED3F0, 0x088ed3f0
.global data_088ED4A4
.set data_088ED4A4, 0x088ed4a4
.global data_088ED5BC
.set data_088ED5BC, 0x088ed5bc
.global data_088ED7EC
.set data_088ED7EC, 0x088ed7ec
.global data_088EDC04
.set data_088EDC04, 0x088edc04
.global data_088EE8B0
.set data_088EE8B0, 0x088ee8b0
.global data_088EF09C
.set data_088EF09C, 0x088ef09c
.global data_088EF35C
.set data_088EF35C, 0x088ef35c
.global data_088EF398
.set data_088EF398, 0x088ef398
.global data_088EF6CC
.set data_088EF6CC, 0x088ef6cc
.global data_088F06B0
.set data_088F06B0, 0x088f06b0
.global data_088F0800
.set data_088F0800, 0x088f0800
.global data_088F0A30
.set data_088F0A30, 0x088f0a30
.global data_088F162C
.set data_088F162C, 0x088f162c
.global data_088F1670
.set data_088F1670, 0x088f1670
.global data_088F1870
.set data_088F1870, 0x088f1870
.global data_088F1B54
.set data_088F1B54, 0x088f1b54
.global data_088F2070
.set data_088F2070, 0x088f2070
.global data_088F25C0
.set data_088F25C0, 0x088f25c0
.global data_088F2BF0
.set data_088F2BF0, 0x088f2bf0
.global data_088F2D60
.set data_088F2D60, 0x088f2d60
.global data_088F2DFC
.set data_088F2DFC, 0x088f2dfc
.global data_088F3334
.set data_088F3334, 0x088f3334
.global data_088F3604
.set data_088F3604, 0x088f3604
.global data_088F38BC
.set data_088F38BC, 0x088f38bc
.global data_088F4680
.set data_088F4680, 0x088f4680
.global data_088F468C
.set data_088F468C, 0x088f468c
.global data_088F469C
.set data_088F469C, 0x088f469c
.global data_088F46AC
.set data_088F46AC, 0x088f46ac
.global data_088F46C0
.set data_088F46C0, 0x088f46c0
.global data_088F46F0
.set data_088F46F0, 0x088f46f0
.global data_088F4E9C
.set data_088F4E9C, 0x088f4e9c
.global data_088F4F80
.set data_088F4F80, 0x088f4f80
.global data_088F58BC
.set data_088F58BC, 0x088f58bc
.global data_088F5A48
.set data_088F5A48, 0x088f5a48
.global data_088F5A94
.set data_088F5A94, 0x088f5a94
.global data_088F668C
.set data_088F668C, 0x088f668c
.global data_088F66B4
.set data_088F66B4, 0x088f66b4
.global data_088F66D4
.set data_088F66D4, 0x088f66d4
.global data_0894848C
.set data_0894848C, 0x0894848c
.global data_08948684
.set data_08948684, 0x08948684
.global data_089486D4
.set data_089486D4, 0x089486d4
.global data_08948834
.set data_08948834, 0x08948834
.global data_08948C38
.set data_08948C38, 0x08948c38
.global data_08948C7C
.set data_08948C7C, 0x08948c7c
.global data_08948CC4
.set data_08948CC4, 0x08948cc4
.global data_08948D00
.set data_08948D00, 0x08948d00
.global data_08949374
.set data_08949374, 0x08949374
.global data_08949474
.set data_08949474, 0x08949474
.global data_0894968C
.set data_0894968C, 0x0894968c
.global data_08949714
.set data_08949714, 0x08949714
.global data_08949728
.set data_08949728, 0x08949728
.global data_0894973C
.set data_0894973C, 0x0894973c
.global data_089497C0
.set data_089497C0, 0x089497c0
.global data_08949AA0
.set data_08949AA0, 0x08949aa0
.global data_08949AB4
.set data_08949AB4, 0x08949ab4
.global data_08949AC8
.set data_08949AC8, 0x08949ac8
.global data_08949D30
.set data_08949D30, 0x08949d30
.global data_08949DD8
.set data_08949DD8, 0x08949dd8
.global data_08949F18
.set data_08949F18, 0x08949f18
.global data_0894A0E8
.set data_0894A0E8, 0x0894a0e8
.global data_0894A490
.set data_0894A490, 0x0894a490
.global data_0894A5F0
.set data_0894A5F0, 0x0894a5f0
.global data_0894A81C
.set data_0894A81C, 0x0894a81c
.global data_0894AAB0
.set data_0894AAB0, 0x0894aab0
.global data_0894AB50
.set data_0894AB50, 0x0894ab50
.global data_0894ABA0
.set data_0894ABA0, 0x0894aba0
.global data_0894AC40
.set data_0894AC40, 0x0894ac40
.global data_0894AC90
.set data_0894AC90, 0x0894ac90
.global data_0894AD30
.set data_0894AD30, 0x0894ad30
.global data_0894AD80
.set data_0894AD80, 0x0894ad80
.global data_0894AD94
.set data_0894AD94, 0x0894ad94
.global data_0894B1F0
.set data_0894B1F0, 0x0894b1f0
.global data_0894B914
.set data_0894B914, 0x0894b914
.global data_0894B964
.set data_0894B964, 0x0894b964
.global data_0894C424
.set data_0894C424, 0x0894c424
.global data_0894C528
.set data_0894C528, 0x0894c528
.global data_0894C578
.set data_0894C578, 0x0894c578
.global data_0894C6BC
.set data_0894C6BC, 0x0894c6bc
.global data_0894C7A4
.set data_0894C7A4, 0x0894c7a4
.global data_0894C898
.set data_0894C898, 0x0894c898
.global data_0894C9B0
.set data_0894C9B0, 0x0894c9b0
.global data_0894CB14
.set data_0894CB14, 0x0894cb14
.global data_0894CB4C
.set data_0894CB4C, 0x0894cb4c
.global data_0894CC1C
.set data_0894CC1C, 0x0894cc1c
.global data_0894CCC0
.set data_0894CCC0, 0x0894ccc0
.global data_0894CEC0
.set data_0894CEC0, 0x0894cec0
.global data_0894CF34
.set data_0894CF34, 0x0894cf34
.global data_0894D5D0
.set data_0894D5D0, 0x0894d5d0
.global data_0894D690
.set data_0894D690, 0x0894d690
.global data_0894D69C
.set data_0894D69C, 0x0894d69c
.global data_0894D6A8
.set data_0894D6A8, 0x0894d6a8
.global data_0894D6B4
.set data_0894D6B4, 0x0894d6b4
.global data_0894D6C4
.set data_0894D6C4, 0x0894d6c4
.global data_0894D7CC
.set data_0894D7CC, 0x0894d7cc
.global data_0894D7E4
.set data_0894D7E4, 0x0894d7e4
.global data_0894D7F0
.set data_0894D7F0, 0x0894d7f0
.global data_0894D8EC
.set data_0894D8EC, 0x0894d8ec
.global data_0894D900
.set data_0894D900, 0x0894d900
.global data_0894D90C
.set data_0894D90C, 0x0894d90c
.global data_0894D95C
.set data_0894D95C, 0x0894d95c
.global data_0894DA1C
.set data_0894DA1C, 0x0894da1c
.global data_0894DA44
.set data_0894DA44, 0x0894da44
.global data_0894DAA0
.set data_0894DAA0, 0x0894daa0
.global data_0894DAB0
.set data_0894DAB0, 0x0894dab0
.global data_0894DB6C
.set data_0894DB6C, 0x0894db6c
.global data_0894DC00
.set data_0894DC00, 0x0894dc00
.global data_0894DC2C
.set data_0894DC2C, 0x0894dc2c
.global data_0894DC44
.set data_0894DC44, 0x0894dc44
.global data_0894DD30
.set data_0894DD30, 0x0894dd30
.global data_0894DDD0
.set data_0894DDD0, 0x0894ddd0
.global data_0894DE04
.set data_0894DE04, 0x0894de04
.global data_0894DE14
.set data_0894DE14, 0x0894de14
.global data_0894DE24
.set data_0894DE24, 0x0894de24
.global data_0894DE44
.set data_0894DE44, 0x0894de44
.global data_0894DE6C
.set data_0894DE6C, 0x0894de6c
.global data_0894DE80
.set data_0894DE80, 0x0894de80
.global data_0894DE94
.set data_0894DE94, 0x0894de94
.global data_0894DEA8
.set data_0894DEA8, 0x0894dea8
.global data_0894F95C
.set data_0894F95C, 0x0894f95c
.global data_08950000
.set data_08950000, 0x08950000
.global data_08950258
.set data_08950258, 0x08950258
.global data_08950D38
.set data_08950D38, 0x08950d38
.global data_08950F4C
.set data_08950F4C, 0x08950f4c
.global data_089511A4
.set data_089511A4, 0x089511a4
.global data_089514F4
.set data_089514F4, 0x089514f4
.global data_089551F4
.set data_089551F4, 0x089551f4
.global data_08955230
.set data_08955230, 0x08955230
.global data_089A031C
.set data_089A031C, 0x089a031c
.global data_089A033C
.set data_089A033C, 0x089a033c
.global data_089A0390
.set data_089A0390, 0x089a0390
.global data_089A040C
.set data_089A040C, 0x089a040c
.global data_089A5CF8
.set data_089A5CF8, 0x089a5cf8
.global data_08A19D18
.set data_08A19D18, 0x08a19d18
.global data_08A38ADC
.set data_08A38ADC, 0x08a38adc
.global data_08A3991C
.set data_08A3991C, 0x08a3991c

/* Additional pinned upstream data aliases; addresses only. */
.global data_020021B6
.set data_020021B6, 0x20021b6
.global data_020021C8
.set data_020021C8, 0x20021c8
.global data_02002C08
.set data_02002C08, 0x2002c08
.global data_02002E58
.set data_02002E58, 0x2002e58
.global data_02003C32
.set data_02003C32, 0x2003c32
.global data_02003C33
.set data_02003C33, 0x2003c33
.global data_02003C34
.set data_02003C34, 0x2003c34
.global data_020080AC
.set data_020080AC, 0x20080ac
.global data_0200F360
.set data_0200F360, 0x200f360
.global data_0200F364
.set data_0200F364, 0x200f364
.global data_0200F368
.set data_0200F368, 0x200f368
.global data_0200F36C
.set data_0200F36C, 0x200f36c
.global data_0200F370
.set data_0200F370, 0x200f370
.global data_0200F378
.set data_0200F378, 0x200f378
.global data_0200F380
.set data_0200F380, 0x200f380
.global data_0200F3A4
.set data_0200F3A4, 0x200f3a4
.global data_0200F3C0
.set data_0200F3C0, 0x200f3c0
.global data_0200F3D4
.set data_0200F3D4, 0x200f3d4
.global data_0200F498
.set data_0200F498, 0x200f498
.global data_0200F49C
.set data_0200F49C, 0x200f49c
.global data_0200F4A0
.set data_0200F4A0, 0x200f4a0
.global data_0200F4A4
.set data_0200F4A4, 0x200f4a4
.global data_0200F6F8
.set data_0200F6F8, 0x200f6f8
.global data_020159B8
.set data_020159B8, 0x20159b8
.global data_020159BC
.set data_020159BC, 0x20159bc
.global data_0201F48D
.set data_0201F48D, 0x201f48d
.global data_0201F48E
.set data_0201F48E, 0x201f48e
.global data_0201F48F
.set data_0201F48F, 0x201f48f
.global data_0201F490
.set data_0201F490, 0x201f490
.global data_0201F4A0
.set data_0201F4A0, 0x201f4a0
.global data_0201F4E5
.set data_0201F4E5, 0x201f4e5
.global data_0201F536
.set data_0201F536, 0x201f536
.global data_0201F537
.set data_0201F537, 0x201f537
.global data_0201F538
.set data_0201F538, 0x201f538
.global data_0201F539
.set data_0201F539, 0x201f539
.global data_03000830
.set data_03000830, 0x3000830
.global data_03000880
.set data_03000880, 0x3000880
.global data_030009A8
.set data_030009A8, 0x30009a8
.global data_03000E4C
.set data_03000E4C, 0x3000e4c
.global data_03000EA0
.set data_03000EA0, 0x3000ea0
.global data_03000EB8
.set data_03000EB8, 0x3000eb8
.global data_03000EE0
.set data_03000EE0, 0x3000ee0
.global data_030027D0
.set data_030027D0, 0x30027d0
.global data_03002800
.set data_03002800, 0x3002800
.global data_03002860
.set data_03002860, 0x3002860
.global data_03002884
.set data_03002884, 0x3002884
.global data_03002B44
.set data_03002B44, 0x3002b44
.global data_03002B60
.set data_03002B60, 0x3002b60
.global data_03002BBC
.set data_03002BBC, 0x3002bbc
.global data_03003270
.set data_03003270, 0x3003270
.global data_030032B0
.set data_030032B0, 0x30032b0
.global data_03003920
.set data_03003920, 0x3003920
.global data_030039F8
.set data_030039F8, 0x30039f8
.global data_03003A64
.set data_03003A64, 0x3003a64
.global data_03003B20
.set data_03003B20, 0x3003b20
.global data_03005E40
.set data_03005E40, 0x3005e40
.global data_03005E42
.set data_03005E42, 0x3005e42
.global data_03005E44
.set data_03005E44, 0x3005e44
.global data_03006168
.set data_03006168, 0x3006168
.global data_0300616C
.set data_0300616C, 0x300616c
.global data_03007FF0
.set data_03007FF0, 0x3007ff0
.global data_04000008
.set data_04000008, 0x4000008
.global data_04000050
.set data_04000050, 0x4000050
.global data_04000060
.set data_04000060, 0x4000060
.global data_04000061
.set data_04000061, 0x4000061
.global data_04000062
.set data_04000062, 0x4000062
.global data_04000063
.set data_04000063, 0x4000063
.global data_04000068
.set data_04000068, 0x4000068
.global data_04000069
.set data_04000069, 0x4000069
.global data_04000070
.set data_04000070, 0x4000070
.global data_04000071
.set data_04000071, 0x4000071
.global data_04000072
.set data_04000072, 0x4000072
.global data_04000073
.set data_04000073, 0x4000073
.global data_04000078
.set data_04000078, 0x4000078
.global data_04000079
.set data_04000079, 0x4000079
.global data_04000080
.set data_04000080, 0x4000080
.global data_04000081
.set data_04000081, 0x4000081
.global data_04000089
.set data_04000089, 0x4000089
.global data_04000090
.set data_04000090, 0x4000090
.global data_040000B0
.set data_040000B0, 0x40000b0
.global data_04000100
.set data_04000100, 0x4000100
.global data_0400010E
.set data_0400010E, 0x400010e
.global data_04000128
.set data_04000128, 0x4000128
.global data_04000134
.set data_04000134, 0x4000134
.global data_04000200
.set data_04000200, 0x4000200
.global data_04000202
.set data_04000202, 0x4000202
.global data_04000204
.set data_04000204, 0x4000204
.global data_06007800
.set data_06007800, 0x6007800
.global data_060099E0
.set data_060099E0, 0x60099e0
.global data_0600A160
.set data_0600A160, 0x600a160
.global data_0600E000
.set data_0600E000, 0x600e000
.global data_06010000
.set data_06010000, 0x6010000
.global data_07FFFFFF
.set data_07FFFFFF, 0x7ffffff
.global data_080000FC
.set data_080000FC, 0x80000fc
.global data_0800023C
.set data_0800023C, 0x800023c
.global data_0836CE38
.set data_0836CE38, 0x836ce38
.global data_0836D2FC
.set data_0836D2FC, 0x836d2fc
.global data_0836D30C
.set data_0836D30C, 0x836d30c
.global data_0836D480
.set data_0836D480, 0x836d480
.global data_0836D634
.set data_0836D634, 0x836d634
.global data_08391448
.set data_08391448, 0x8391448
.global data_08391784
.set data_08391784, 0x8391784
.global data_08391787
.set data_08391787, 0x8391787
.global data_083917B8
.set data_083917B8, 0x83917b8
.global data_083917C1
.set data_083917C1, 0x83917c1
.global data_0839191C
.set data_0839191C, 0x839191c
.global data_083919C6
.set data_083919C6, 0x83919c6
.global data_083919CE
.set data_083919CE, 0x83919ce
.global data_083919EE
.set data_083919EE, 0x83919ee
.global data_083931B0
.set data_083931B0, 0x83931b0
.global data_08394352
.set data_08394352, 0x8394352
.global data_083943BC
.set data_083943BC, 0x83943bc
.global data_0839475C
.set data_0839475C, 0x839475c
.global data_08395544
.set data_08395544, 0x8395544
.global data_08395548
.set data_08395548, 0x8395548
.global data_08399B2C
.set data_08399B2C, 0x8399b2c
.global data_0839D71C
.set data_0839D71C, 0x839d71c
.global data_0839D740
.set data_0839D740, 0x839d740
.global data_0839D744
.set data_0839D744, 0x839d744
.global data_0839D758
.set data_0839D758, 0x839d758
.global data_083A2F10
.set data_083A2F10, 0x83a2f10
.global data_083A2FD8
.set data_083A2FD8, 0x83a2fd8
.global data_083A30F0
.set data_083A30F0, 0x83a30f0
.global data_083A33C4
.set data_083A33C4, 0x83a33c4
.global data_083A33F8
.set data_083A33F8, 0x83a33f8
.global data_083A6BDC
.set data_083A6BDC, 0x83a6bdc
.global data_083A8306
.set data_083A8306, 0x83a8306
.global data_083C11BC
.set data_083C11BC, 0x83c11bc
.global data_083C15B4
.set data_083C15B4, 0x83c15b4
.global data_083C16F4
.set data_083C16F4, 0x83c16f4
.global data_083C4B10
.set data_083C4B10, 0x83c4b10
.global data_083C4B44
.set data_083C4B44, 0x83c4b44
.global data_08427A04
.set data_08427A04, 0x8427a04
.global data_0842CC80
.set data_0842CC80, 0x842cc80
.global data_084B64A4
.set data_084B64A4, 0x84b64a4
.global data_08501DB0
.set data_08501DB0, 0x8501db0
.global data_08501E68
.set data_08501E68, 0x8501e68
.global data_0852736C
.set data_0852736C, 0x852736c
.global data_08527E62
.set data_08527E62, 0x8527e62
.global data_08528256
.set data_08528256, 0x8528256
.global data_08528C24
.set data_08528C24, 0x8528c24
.global data_088ED8CC
.set data_088ED8CC, 0x88ed8cc
.global data_088F46CC
.set data_088F46CC, 0x88f46cc
.global data_088F5ADC
.set data_088F5ADC, 0x88f5adc
.global data_089492DC
.set data_089492DC, 0x89492dc
.global data_0894AA18
.set data_0894AA18, 0x894aa18
.global data_0894D804
.set data_0894D804, 0x894d804
.global data_0894D97C
.set data_0894D97C, 0x894d97c
.global data_0894D9D0
.set data_0894D9D0, 0x894d9d0
.global data_0894DA74
.set data_0894DA74, 0x894da74
.global data_08950320
.set data_08950320, 0x8950320
.global data_08950508
.set data_08950508, 0x8950508
.global data_089506F0
.set data_089506F0, 0x89506f0
.global data_08950D98
.set data_08950D98, 0x8950d98
.global data_08951220
.set data_08951220, 0x8951220
.global data_089512E0
.set data_089512E0, 0x89512e0
.global data_089513A0
.set data_089513A0, 0x89513a0
.global data_08951550
.set data_08951550, 0x8951550
.global gUnknown_083992B8
.set gUnknown_083992B8, 0x83992b8
.global g_callbacks_0836D4B8
.set g_callbacks_0836D4B8, 0x836d4b8
.global g_control_flags_03000940
.set g_control_flags_03000940, 0x3000940
.global g_count_0854D1B4
.set g_count_0854D1B4, 0x854d1b4
.global g_event_parameters_08399418
.set g_event_parameters_08399418, 0x8399418
.global g_events_083990EC
.set g_events_083990EC, 0x83990ec
.global g_events_083992F8
.set g_events_083992F8, 0x83992f8
.global g_offsets_0839941B
.set g_offsets_0839941B, 0x839941b
.global g_records_02009000
.set g_records_02009000, 0x2009000
.global g_resources_0839999C
.set g_resources_0839999C, 0x839999c
.global g_state_02000000
.set g_state_02000000, 0x2000000
.global g_state_02000080
.set g_state_02000080, 0x2000080
.global g_state_02001940
.set g_state_02001940, 0x2001940
.global g_state_02001F6C
.set g_state_02001F6C, 0x2001f6c
.global g_state_020020D0
.set g_state_020020D0, 0x20020d0
.global g_state_020021A0
.set g_state_020021A0, 0x20021a0
.global g_state_02002B08
.set g_state_02002B08, 0x2002b08
.global g_state_02002C10
.set g_state_02002C10, 0x2002c10
.global g_state_02002CB4
.set g_state_02002CB4, 0x2002cb4
.global g_state_02002CC0
.set g_state_02002CC0, 0x2002cc0
.global g_state_02002E34
.set g_state_02002E34, 0x2002e34
.global g_state_02002FC4
.set g_state_02002FC4, 0x2002fc4
.global g_state_02007F40
.set g_state_02007F40, 0x2007f40
.global g_state_0200F1D4
.set g_state_0200F1D4, 0x200f1d4
.global g_state_0200F390
.set g_state_0200F390, 0x200f390
.global g_state_03002810
.set g_state_03002810, 0x3002810
.global g_state_030034B0
.set g_state_030034B0, 0x30034b0
.global g_state_03005F30
.set g_state_03005F30, 0x3005f30
.global g_table_08149568
.set g_table_08149568, 0x8149568
.global g_table_08149B88
.set g_table_08149B88, 0x8149b88
.global g_table_0814BB24
.set g_table_0814BB24, 0x814bb24
.global g_table_0814BB48
.set g_table_0814BB48, 0x814bb48
.global g_table_0836D4D4
.set g_table_0836D4D4, 0x836d4d4
.global g_table_0836D5A4
.set g_table_0836D5A4, 0x836d5a4
.global g_table_08390E44
.set g_table_08390E44, 0x8390e44
.global g_table_08394778
.set g_table_08394778, 0x8394778
.global g_table_08398C78
.set g_table_08398C78, 0x8398c78
.global g_table_08398D68
.set g_table_08398D68, 0x8398d68
.global g_table_0839918C
.set g_table_0839918C, 0x839918c
.global g_table_083A8190
.set g_table_083A8190, 0x83a8190
.global g_table_083A86F8
.set g_table_083A86F8, 0x83a86f8
.global g_table_084E8FD4
.set g_table_084E8FD4, 0x84e8fd4
.global g_table_0851BA4E
.set g_table_0851BA4E, 0x851ba4e
.global g_table_0851BA84
.set g_table_0851BA84, 0x851ba84
.global g_table_0851D180
.set g_table_0851D180, 0x851d180
.global g_table_08520080
.set g_table_08520080, 0x8520080
.global g_table_08521214
.set g_table_08521214, 0x8521214
.global g_table_08521A14
.set g_table_08521A14, 0x8521a14
.global g_table_085231F4
.set g_table_085231F4, 0x85231f4
.global g_table_08526680
.set g_table_08526680, 0x8526680
.global g_table_085273D8
.set g_table_085273D8, 0x85273d8
.global g_table_0852790C
.set g_table_0852790C, 0x852790c
.global g_table_08527E4A
.set g_table_08527E4A, 0x8527e4a
.global g_table_08528556
.set g_table_08528556, 0x8528556
.global g_table_08528984
.set g_table_08528984, 0x8528984
.global g_table_08528E1C
.set g_table_08528E1C, 0x8528e1c
.global g_table_08528F34
.set g_table_08528F34, 0x8528f34
.global g_table_08529EE4
.set g_table_08529EE4, 0x8529ee4
.global g_table_0854CD54
.set g_table_0854CD54, 0x854cd54
.global g_table_0854CD7C
.set g_table_0854CD7C, 0x854cd7c
.global g_table_085516D0
.set g_table_085516D0, 0x85516d0
.global g_table_085567F0
.set g_table_085567F0, 0x85567f0
.global g_table_085573F4
.set g_table_085573F4, 0x85573f4
.global g_table_0855A64C
.set g_table_0855A64C, 0x855a64c
.global g_table_0855AE4C
.set g_table_0855AE4C, 0x855ae4c
.global g_table_08563A4C
.set g_table_08563A4C, 0x8563a4c
.global g_table_08563A50
.set g_table_08563A50, 0x8563a50
.global g_table_08563A70
.set g_table_08563A70, 0x8563a70
.global g_table_085644FC
.set g_table_085644FC, 0x85644fc
.global g_table_08564670
.set g_table_08564670, 0x8564670
.global g_table_085653F0
.set g_table_085653F0, 0x85653f0
.global g_table_08565416
.set g_table_08565416, 0x8565416
.global g_table_08565F14
.set g_table_08565F14, 0x8565f14
.global g_table_085680DC
.set g_table_085680DC, 0x85680dc
.global g_table_089C1484
.set g_table_089C1484, 0x89c1484
.global g_table_08A19970
.set g_table_08A19970, 0x8a19970
.global g_table_08A1A908
.set g_table_08A1A908, 0x8a1a908

/* Authenticated original runtime call targets. */
.ifndef OMIT___subdf3
.global __subdf3
.thumb_set __subdf3, 0x81430b5
.endif
.ifndef OMIT___divdf3
.global __divdf3
.thumb_set __divdf3, 0x814339d
.endif
.ifndef OMIT___muldf3
.global __muldf3
.thumb_set __muldf3, 0x81430f1
.endif
.ifndef OMIT___adddf3
.global __adddf3
.thumb_set __adddf3, 0x8143081
.endif
.ifndef OMIT___ltdf2
.global __ltdf2
.thumb_set __ltdf2, 0x814379d
.endif
.ifndef OMIT___ashldi3
.global __ashldi3
.thumb_set __ashldi3, 0x814220d
.endif
.ifndef OMIT___umodsi3
.global __umodsi3
.thumb_set __umodsi3, 0x8142b29
.endif
.ifndef OMIT___udivsi3
.global __udivsi3
.thumb_set __udivsi3, 0x8142ab1
.endif
.ifndef OMIT___divsi3
.global __divsi3
.thumb_set __divsi3, 0x81426b9
.endif
.ifndef OMIT___floatsidf
.global __floatsidf
.thumb_set __floatsidf, 0x814383d
.endif
.ifndef OMIT___fixdfsi
.global __fixdfsi
.thumb_set __fixdfsi, 0x81438bd
.endif
.ifndef OMIT___modsi3
.global __modsi3
.thumb_set __modsi3, 0x8142951
.endif
.ifndef OMIT___truncdfsf2
.global __truncdfsf2
.thumb_set __truncdfsf2, 0x8143981
.endif
.ifndef OMIT___mulsf3
.global __mulsf3
.thumb_set __mulsf3, 0x8143ced
.endif
.ifndef OMIT___fixunssfsi
.global __fixunssfsi
.thumb_set __fixunssfsi, 0x81428ad
.endif
.ifndef OMIT___extendsfdf2
.global __extendsfdf2
.thumb_set __extendsfdf2, 0x814432d
.endif
.ifndef OMIT___fixunsdfdi
.global __fixunsdfdi
.thumb_set __fixunsdfdi, 0x814278d
.endif
.ifndef OMIT___negdf2
.global __negdf2
.thumb_set __negdf2, 0x8143931
.endif
.ifndef OMIT___negdi2
.global __negdi2
.thumb_set __negdi2, 0x8142a95
.endif
.ifndef OMIT___fixunsdfsi
.global __fixunsdfsi
.thumb_set __fixunsdfsi, 0x8142865
.endif
.ifndef OMIT___cmpdi2
.global __cmpdi2
.thumb_set __cmpdi2, 0x814435d
.endif
.ifndef OMIT___floatdidf
.global __floatdidf
.thumb_set __floatdidf, 0x81428e5
.endif
.ifndef OMIT__call_via_r9
.global _call_via_r9
.thumb_set _call_via_r9, 0x8142269
.endif
