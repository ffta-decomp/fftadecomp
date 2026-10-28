/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit;
struct WorkRamView {u8 unknown[0x2190];u8 state;};
#define OFF(T,M) ((u32)&((T *)0)->M)
typedef char StateOffset[(OFF(struct WorkRamView,state)==0x2190)?1:-1];
extern struct WorkRamView WorkRam;
extern u8 SaveByte(u16 index);
extern u32 UnitField(const struct Unit *,u8 selector);
__asm__(".global WorkRam\n.set WorkRam,0x02000000");
__asm__(".thumb_set SaveByte,0x080c95a9");
__asm__(".thumb_set UnitField,0x080c7ea5");


/* The state numbers are preserved; their gameplay labels are not inferred. */
int UnitPassesWorkStateRule(const struct Unit *unit)
{
    u8 state;
    if ((u8)SaveByte(13) == 1)
        goto reject;
    state = WorkRam.state;
    if (state != 22 && state != 26)
        goto reject;
    if (UnitField(unit, 1) != 13)
        goto reject;
    return 1;
reject:
    return 0;
}
