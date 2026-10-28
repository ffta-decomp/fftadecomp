typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct Actor;
struct ActorActionRecord { struct Actor *actor; };
extern u32 QueryActionRecord(struct ActorActionRecord *, u8 selector);
extern struct Actor *ResolveRecordActor(struct Actor *);
extern u32 ReadActorFlags(struct Actor *);
extern struct Actor *ResolveActionActor(struct Actor *);
extern void UpdateActorActionAutomatic(struct Actor *, u16, s32);
extern void ApplyDefaultActorAction(struct Actor *, s32, u32);
/* Query priority and each fresh record-word read follow separate original paths. */
void ApplyRecordActorActionOverride(struct ActorActionRecord *record, u8 direction)
{
    u16 action = 0;
    u16 flags;
    if ((u8)QueryActionRecord(record, 1) != 0)
        goto choose_twelve;
    if ((u8)QueryActionRecord(record, 2) != 0) {
        action = 36;
        goto apply_selected;
    }
    flags = (u16)ReadActorFlags(ResolveRecordActor(record->actor));
    if ((flags & 8) == 0)
        goto check_flag_800;
choose_twelve:
    action = 12;
    goto apply_selected;
check_flag_800:
    if ((flags & 0x800) != 0)
        action = 36;
    if (action == 0)
        goto use_default;
apply_selected:
    {
        struct Actor *actor = ResolveRecordActor(record->actor);
        s32 saved_direction = (s8)direction;
        actor = ResolveActionActor(actor);
        UpdateActorActionAutomatic(actor, action, saved_direction);
    }
    goto finished;
use_default:
    ApplyDefaultActorAction(record->actor, (s8)direction, 0);
finished:
    return;
}
asm(".global QueryActionRecord\n.thumb_set QueryActionRecord,0x080dd685\n"
    ".global ResolveRecordActor\n.thumb_set ResolveRecordActor,0x080dd34d\n"
    ".global ReadActorFlags\n.thumb_set ReadActorFlags,0x080dd71d\n"
    ".global ResolveActionActor\n.thumb_set ResolveActionActor,0x080dd351\n"
    ".global UpdateActorActionAutomatic\n.thumb_set UpdateActorActionAutomatic,0x0809a2d9\n"
    ".global ApplyDefaultActorAction\n.thumb_set ApplyDefaultActorAction,0x080de33d\n");
