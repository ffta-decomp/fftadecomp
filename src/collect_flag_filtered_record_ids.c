/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 RetailCall_080c9540(u16);
asm(".global RetailCall_080c9540
.thumb_set RetailCall_080c9540,0x080c9541");

u32 CollectFlagFilteredRecordIds(u32 *output)
{
    u32 count=0;
    const u16 *entry=(const u16 *)0x083937b2;
    u32 *cursor=output;
    int remaining=5;
    do {
        if (*entry != 79 || (u8)RetailCall_080c9540(0x207)) {
            *cursor++ = *entry;
            count++;
        }
        entry++;
        remaining--;
    } while (remaining >= 0);
    return count;
}
