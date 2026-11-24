/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Unit {u8 gap[4];u8 active;u8 gap2[35];u16 flags;u8 tail[222];};
extern struct Unit gUnits[];
extern u8 Check8348(struct Unit *);
extern u8 Check82D8(struct Unit *);
extern u8 Check832C(struct Unit *);
extern void PrepareUnit(struct Unit *);
extern int ReadProperty(struct Unit *,int);
extern void SetGameFlag(int,int);

asm(".global gUnits\n.set gUnits,0x02000080\n.global Check8348\n.thumb_set Check8348,0x80c8349\n.global Check82D8\n.thumb_set Check82D8,0x80c82d9\n.global Check832C\n.thumb_set Check832C,0x80c832d\n.global PrepareUnit\n.thumb_set PrepareUnit,0x80cb4c1\n.global ReadProperty\n.thumb_set ReadProperty,0x80c7ea5\n.global SetGameFlag\n.thumb_set SetGameFlag,0x80c9575\n");
void UpdateRosterProgressFlags(void)
{
    struct Unit *unit = gUnits;
    int remaining = 23;
    u8 value;
    do {
        if (unit->active) {
            if (Check8348(unit)) {
                unit->flags &= 0xffdf;
                if (Check82D8(unit)) {
                    PrepareUnit(unit);
                    value = ReadProperty(unit,1);
                    switch (value) {
                    case 8: SetGameFlag(56,1); break;
                    case 94: SetGameFlag(70,1); break;
                    case 4: SetGameFlag(71,1); break;
                    case 12: SetGameFlag(72,1); break;
                    case 9: SetGameFlag(73,1); break;
                    }
                    SetGameFlag(0x5ac,1);
                }
            }
            if (Check832C(unit)) unit->flags &= 0xffbf;
        }
        remaining--;
        unit++;
    } while (remaining >= 0);
    unit = (void *)((u8 *)gUnits+0x2f44);
    remaining = 11;
    do {
        if (unit->active) {
            if (Check8348(unit)) unit->flags &= 0xffdf;
            if (Check832C(unit)) unit->flags &= 0xffbf;
        }
        remaining--;
        unit++;
    } while (remaining >= 0);
}
