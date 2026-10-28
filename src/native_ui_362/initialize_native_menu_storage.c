/* Original native menu header and task-arena setup. Generic backends stay native. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*NativeClearBytes)(u8 *destination, s32 count);
struct NativeMenuStorage {
    void *task_group;
    u8 *allocation;
};
extern struct NativeMenuStorage *NativeMenuRoot;
extern NativeClearBytes NativeMenuClear;
extern u8 *AllocateNativeMenuStorage(u32 bytes);
extern void *CreateNativeTaskGroupStorage(u8 *storage, u32 bytes);

void InitializeNativeMenuStorage(u32 bytes)
{
    u8 *allocation = AllocateNativeMenuStorage(bytes);
    void *group;
    NativeMenuRoot = (struct NativeMenuStorage *)allocation;
    NativeMenuClear(allocation, 0x1108);
    NativeMenuRoot->allocation = allocation;
    group = CreateNativeTaskGroupStorage(allocation + 0x1108, bytes - 0x1108);
    NativeMenuRoot->task_group = group;
}

/* Original object/callback addresses and declaration-only native linkage. */
asm(".global NativeMenuRoot\n.set NativeMenuRoot, 0x0200f44c\n"
    ".global NativeMenuClear\n.set NativeMenuClear, 0x0836d4b8\n"
    ".global AllocateNativeMenuStorage\n.thumb_set AllocateNativeMenuStorage, 0x08022841\n"
    ".global CreateNativeTaskGroupStorage\n.thumb_set CreateNativeTaskGroupStorage, 0x08005c15\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");
