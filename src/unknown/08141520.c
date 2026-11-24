typedef unsigned char u8;
typedef unsigned short u16;
extern void DispatchIndexedDefinition(u16 index);
__asm__(".global DispatchIndexedDefinition\n.thumb_set DispatchIndexedDefinition, 0x081451c1");

/* Preserve the real lower service; the wider meaning of flag bit one is unknown. */
void DispatchEnabledDefinition(u16 index)
    __asm__("BattleRuntimeDependency_00141520");
void DispatchEnabledDefinition(u16 index)
{
    if ((*(u8 *)0x020084d8 & 2) != 0)
        DispatchIndexedDefinition(index);
}
