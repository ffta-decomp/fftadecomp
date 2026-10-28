typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern u8 *gSelectionRuntimeWords[];
extern u8 *gNativeMenuRoot;

extern u32 GetManagedSelectionTileOffset(void *view, u32 row);
extern void ClearManagedSelectionTextCells(void *destination, u16 count);
extern u32 GetManagedSelectionIndex(void *view, u32 row);
extern const u8 *GetNativeMenuRowText(void *object, s16 index, u8 *mode);
extern u8 *PrepareNativeMenuRowGraphic(void *object, u8 *destination,
                                     u16 index);
extern u32 ProcessEncodedTextStream(void *context, u32 destination,
                                   const u8 *text, u32 mode, u32 flags);
extern void FinishNativeMenuRow(void *object, u8 *destination, u16 index);

void DrawNativeMenuRow(void *object, s8 input_row)
{
    u8 mode;
    u8 *view = (u8 *)object + 60;
    s32 row;
    u8 *destination;
    u16 index;
    const u8 *text;

    mode = 0;
    row = input_row;
    destination = gSelectionRuntimeWords[4]
        + ((u32)(u16)GetManagedSelectionTileOffset(view, row) << 5);
    ClearManagedSelectionTextCells(destination, (u16)(view[21] * 2));
    index = (u16)GetManagedSelectionIndex(view, row);
    text = GetNativeMenuRowText(object, (s16)index, &mode);
    destination = PrepareNativeMenuRowGraphic(object, destination, index);
    ProcessEncodedTextStream(gNativeMenuRoot + 328, (u32)destination,
                             text, mode, 1);
    FinishNativeMenuRow(object, destination, index);
}

asm(".set gSelectionRuntimeWords, 0x030008B0\n"
    ".set gNativeMenuRoot, 0x0200F44C\n"
    ".thumb_set GetManagedSelectionTileOffset, 0x08017B9D\n"
    ".thumb_set ClearManagedSelectionTextCells, 0x08013A89\n"
    ".thumb_set GetManagedSelectionIndex, 0x08017B69\n"
    ".thumb_set GetNativeMenuRowText, 0x0805FD39\n"
    ".thumb_set PrepareNativeMenuRowGraphic, 0x0805FEA9\n"
    ".thumb_set ProcessEncodedTextStream, 0x08015111\n"
    ".thumb_set FinishNativeMenuRow, 0x0805FFF1\n");
