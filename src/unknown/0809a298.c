typedef unsigned short u16;
typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;
struct BattleActorVisual;
/* Raw call-register view: the existing implementation re-narrows direction to
   low8. This wrapper explicitly sign-extends it before entering that body. */
extern void ApplyActorVisualRegisters_080975DC(struct BattleActorVisual *, u16, s32, u32);
void ApplyAutomaticBattleActorVisual(struct BattleActorVisual *actor, u16 resource, s8 direction)
{
    ApplyActorVisualRegisters_080975DC(actor, resource, direction, 1);
}
asm(".thumb_set ApplyActorVisualRegisters_080975DC,0x080975dd\n");
