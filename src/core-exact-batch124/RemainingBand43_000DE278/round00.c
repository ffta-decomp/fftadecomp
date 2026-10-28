typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct BattleActorView { u8 unknown_00[48]; u32 flags; };
extern struct BattleActorView *ResolveEffectActor(struct BattleActorView *);
extern void UpdateActorActionAutomatic(struct BattleActorView *, u16, s32);
extern void ApplyActorMotionState(struct BattleActorView *, u32, s32, u32);
extern void ApplyActorFlagMasks(struct BattleActorView *, u16, u16);
extern void RefreshActorPresentation(struct BattleActorView *, u8);
/* The flags are a single entry snapshot; the returned actor is used only
 * on the bit-8 path. Existing visual and motion implementations remain real. */
void RefreshActorDirectionForFlags(struct BattleActorView *owner, u8 direction)
{
    u32 flags = owner->flags;
    if ((flags & 16) == 0) {
        if ((flags & 8) != 0) {
            s32 saved_direction = (s8)direction;
            struct BattleActorView *actor = ResolveEffectActor(owner);
            UpdateActorActionAutomatic(actor, 12, saved_direction);
        } else {
            ApplyActorMotionState(owner, 1, (s8)direction, 0);
            ApplyActorFlagMasks(owner, 0, 256);
            RefreshActorPresentation(owner, 1);
        }
    }
}
asm(".global ResolveEffectActor\n.thumb_set ResolveEffectActor,0x080dd351\n"
    ".global UpdateActorActionAutomatic\n.thumb_set UpdateActorActionAutomatic,0x0809a2d9\n"
    ".global ApplyActorMotionState\n.thumb_set ApplyActorMotionState,0x0809836d\n"
    ".global ApplyActorFlagMasks\n.thumb_set ApplyActorFlagMasks,0x0809a571\n"
    ".global RefreshActorPresentation\n.thumb_set RefreshActorPresentation,0x0809a531\n");
