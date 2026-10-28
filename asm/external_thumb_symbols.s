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
