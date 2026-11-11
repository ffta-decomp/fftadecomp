/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct Unit {u8 gap[4];u8 active;};
struct Game {u8 gap[0x2190];u8 mode;u8 gap2[0x2fc4-0x2191];struct Unit unit;u8 gap3[0x3c24-0x2fc4-sizeof(struct Unit)];u32 flags;u8 gap4[2];u8 scene;};
extern struct Game gGame;
extern u8 GetGameFlag(u32);
extern struct Unit * FindUnit(int);
extern u8 Check8348(struct Unit *);
extern u8 Check8364(struct Unit *);
extern void TriggerEvent(int);
extern u8 Check8280(struct Unit *);
extern u8 CheckD8CC(struct Unit *);
extern u8 CheckD92C(struct Unit *);

asm(".global gGame\n.set gGame,0x02000000\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global FindUnit\n.thumb_set FindUnit,0x8125579\n.global Check8348\n.thumb_set Check8348,0x80c8349\n.global Check8364\n.thumb_set Check8364,0x80c8365\n.global TriggerEvent\n.thumb_set TriggerEvent,0x8009afd\n.global Check8280\n.thumb_set Check8280,0x80c8281\n.global CheckD8CC\n.thumb_set CheckD8CC,0x80cd8cd\n.global CheckD92C\n.thumb_set CheckD92C,0x80cd92d\n");
u8 TryTriggerContextEvent170(void)
{
    struct Game *game;
    struct Unit *unit;
    if (GetGameFlag(64)) goto unavailable;
    game = &gGame;
    if (game->mode == 8) {
        unit = FindUnit(10);
        if (!Check8348(unit) && !Check8364(unit)) goto unavailable;
        TriggerEvent(170);
        game->flags |= 4;
        return 1;
    } else {
        if (game->scene != 49 && game->scene != 57) goto unavailable;
        unit = &game->unit;
        if (unit->active) {
            if (Check8280(unit) && !CheckD8CC(unit)) goto trigger;
            if (!CheckD92C(unit) && !Check8364(unit) && !Check8348(unit)) goto unavailable;
        }
trigger:
        TriggerEvent(170);
        return 1;
    }
unavailable:
    return 0;
}
