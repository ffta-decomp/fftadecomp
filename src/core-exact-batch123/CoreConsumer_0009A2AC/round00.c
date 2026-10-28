typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
struct BattleActor;
/* These call-site declarations retain the original full signed projection;
 * the existing implementations consume the low byte of direction. */
extern void ApplyExistingActorVisual(struct BattleActor *, u16, s32, u32);
extern void RefreshExistingActorValues(struct BattleActor *, u16, s32);
void UpdateBattleActorAction(struct BattleActor *actor, u16 value,
                             s8 direction, u8 automatic)
{
    ApplyExistingActorVisual(actor, value, direction, automatic);
    RefreshExistingActorValues(actor, value, direction);
}
asm(".global ApplyExistingActorVisual\n.thumb_set ApplyExistingActorVisual,0x080975dd\n"
    ".global RefreshExistingActorValues\n.thumb_set RefreshExistingActorValues,0x08097705\n");
