typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionResultSet { u8 prefix[0x145c]; u16 entries[16]; };
extern struct MissionResultSet *gMissionResults __asm__("0x0200f448");
u32 HasMissionOperationResult(void) __asm__("CoreFrontier_0005D174");
u32 HasMissionOperationResult(void)
{
    int slot = 0;
    const u16 *entries = gMissionResults->entries;
    for (; slot < 16; slot++) {
        if (entries[slot] != 0)
            return 1;
    }
    return 0;
}
