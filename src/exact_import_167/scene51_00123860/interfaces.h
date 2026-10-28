typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct StoryCleanupState {
    u8 unknown_prefix[180];
    /* Role tentative; native opcode clears this byte before unit cleanup. */
    u8 cleanup_flag;
};
extern struct StoryCleanupState gStoryCleanup;
extern void ClearStoryUnitFlags(void);
extern void CommitStoryUnitPropertyFlags(void);
extern void CommitOccupiedUnitCountFlag(void);
extern void RefreshStoryUnitValues(void *,s32);
__asm__(".global gStoryCleanup\n.set gStoryCleanup,0x20020d0");
__asm__(".global ClearStoryUnitFlags\n.thumb_set ClearStoryUnitFlags,0x802d935");
__asm__(".global CommitStoryUnitPropertyFlags\n.thumb_set CommitStoryUnitPropertyFlags,0x802d825");
__asm__(".global CommitOccupiedUnitCountFlag\n.thumb_set CommitOccupiedUnitCountFlag,0x80d2f2d");
__asm__(".global RefreshStoryUnitValues\n.thumb_set RefreshStoryUnitValues,0x809a951");
