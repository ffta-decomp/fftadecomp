#ifndef FFTA_SAVE_STATE_TRANSACTION_06_H
#define FFTA_SAVE_STATE_TRANSACTION_06_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define ImageByte(p, n) (*((u8 *)(p) + (n)))
#define ImageHalf(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define ImageWord(p, n) (*(u32 *)((u8 *)(p) + (n)))
#define ImagePointer(p, n) (*(u8 **)((u8 *)(p) + (n)))
#define ReferenceMode (*(u8 *)0x03000ed5)
#define TransactionImage ((u8 *)0x02003cb0)
#define CopyImageBytes(destination, source, size) \
    ((void (*)(void *, const void *, u32))(*(u32 *)0x0836d4bc))(destination, source, size)

#define SaveCall_CA1BC ResolveContextRecordTextPointer
#define SaveCall_14186C BiosCpuSet
#define SaveCall_1452F4 PrepareRomRestartB
#define SaveCall_145798 PrepareRomRestartA
#define SaveCall_1443FC RetailCopyBytes
#define SaveCall_121B64 EntityHelper_08121B64
#define SaveCall_121B78 EntityHelper_08121B78
#define SaveCall_1174C SceneTaskDependency_0001174C
#define SaveCall_11860 CoreMutationDependency_00011860
#define SaveCall_141540 PlayNameEditorSound
#define SaveCall_13364 sub_08013364
#define SaveCall_11B30 IT01_Message

u32 ReadDecodedGameImage(u8 slot, u8 *image);
u32 WriteEncodedGameImage(u8 slot, u8 *image);
void PrepareTransitionGameImage(void);
void PrepareGameImageHeader(u8 slot, u8 *image);

u32 SaveCall_CA0F8(const u8 *record);
u32 SaveCall_CA1BC(const u8 *record);
u32 SaveCall_CA150(const u8 *record);
u32 SaveCall_CA1F0(const u8 *record);
u32 SaveCall_13B57C(u8 slot, u8 *image);
u32 SaveCall_13B2A8(u8 slot, u8 *image);
void SaveCall_13BC7C(u8 slot);
u8 SaveCall_C95D8(u16 flag, const u8 *image);
void SaveCall_C960C(u16 flag, u16 value, u8 *image);
void SaveCall_12C030(u8 *state, u8 *record);
void SaveCall_14186C(const void *source, void *destination, u32 control);
void SaveCall_1452F4(void);
void SaveCall_145798(void);
void SaveCall_1457FC(void);
void SaveCall_33C8(u32 mode);
void SaveCall_1443FC(void *destination, const void *source, u32 size);
u8 *SaveCall_121B64(u32 kind);
void SaveCall_121B78(u8 *window);
void SaveCall_1DB78(void);
void SaveCall_1174C(u8 *window, u32 mode, u32 text, u8 *argument,
                   u8 *palette, u32 x, u32 y, u32 width, u32 height, u32 tile);
void SaveCall_1339C(u32 mode);
u32 SaveCall_11860(void);
void SaveCall_141540(u32 sound);
void SaveCall_13364(void);
void SaveCall_11B30(u32 mode, u32 message);
void SaveCall_231C0(void);
u32 SaveCall_13B9F8(u8 *image);
u32 SaveCall_13BA5C(u8 *image, u8 selector);

#endif
