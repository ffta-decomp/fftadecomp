/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Unit {u8 gap[4];u8 active;u8 gap2[35];u16 flags;u8 gap3[198];u8 byte240;u8 tail[23];};
extern struct Unit gUnits[];
extern u8 GetGameFlag(int);
extern u8 Check8348(struct Unit *);
extern u8 Check82D8(struct Unit *);
extern u8 Check8364(struct Unit *);
extern u8 Check832C(struct Unit *);

asm(".global gUnits\n.set gUnits,0x02000080\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global Check8348\n.thumb_set Check8348,0x80c8349\n.global Check82D8\n.thumb_set Check82D8,0x80c82d9\n.global Check8364\n.thumb_set Check8364,0x80c8365\n.global Check832C\n.thumb_set Check832C,0x80c832d\n");
void ClearFlaggedRosterStatuses(void)
{
    struct Unit *unit;
    int remaining;
    unsigned int cleanup_mask;
    int stride;
    if (GetGameFlag(64)) {
        unit = gUnits;
        remaining = 23;
        do {
            if (unit->active) {
                if (Check8348(unit)) {
                    unit->flags &= 0xffdf;
                    if (Check82D8(unit)) unit->flags &= 0xfff7;
                    if (Check8364(unit)) unit->flags &= 0xfeff;
                    unit->byte240 = 0;
                }
                if (Check832C(unit)) unit->flags &= 0xffbf;
            }
            remaining--;
            unit++;
        } while (remaining >= 0);
        unit = (void *)((u8 *)gUnits + 0x2f44);
        cleanup_mask = 0xfe97;
        stride = 264;
        remaining = 11;
        do {
            if (unit->active) unit->flags &= cleanup_mask;
            remaining--;
            unit = (void *)((u8 *)unit + stride);
        } while (remaining >= 0);
    }
}
