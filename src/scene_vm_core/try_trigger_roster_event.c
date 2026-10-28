/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit {u8 gap[40];u16 flags;};
struct Game {u8 gap[0x3c24];u32 flags;};
extern struct Unit gUnits[];
extern struct Game gGame;
extern u8 GetGameFlag(int);
extern void SetGameFlag(int,int);
extern u8 CheckOption(int);
extern u8 Check8280(struct Unit *);
extern u8 Check8364(struct Unit *);
extern u8 Check8348(struct Unit *);
extern u8 CheckD92C(struct Unit *);
extern struct Unit * FindUnit(int);
extern void TriggerEvent(int);

asm(".global gUnits\n.set gUnits,0x02000080\n.global gGame\n.set gGame,0x02000000\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global SetGameFlag\n.thumb_set SetGameFlag,0x80c9575\n.global CheckOption\n.thumb_set CheckOption,0x80ced5d\n.global Check8280\n.thumb_set Check8280,0x80c8281\n.global Check8364\n.thumb_set Check8364,0x80c8365\n.global Check8348\n.thumb_set Check8348,0x80c8349\n.global CheckD92C\n.thumb_set CheckD92C,0x80cd92d\n.global FindUnit\n.thumb_set FindUnit,0x80c83cd\n.global TriggerEvent\n.thumb_set TriggerEvent,0x8009afd\n");
u8 TryTriggerRosterEvent170(void)
{
    struct Unit *unit;
    if (GetGameFlag(64)) return 0;
    if (!CheckOption(0)) return 0;
    unit = gUnits;
    if ((unit->flags & 129) && (Check8280(unit) || Check8364(unit))) {
        if (Check8280(unit) && !CheckD92C(unit) && !Check8364(unit) && !Check8348(unit)) SetGameFlag(0x256,1);
        TriggerEvent(170);
        gGame.flags |= 4;
        return 1;
    }
    unit = FindUnit(8);
    if (unit && (unit->flags & 129) && Check8280(unit) && !CheckD92C(unit) && !Check8364(unit)) SetGameFlag(0x257,1);
    return 0;
}
