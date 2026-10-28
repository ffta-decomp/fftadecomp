typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActorRecord { u32 actor; u32 unknown4; u16 x; u16 attribute; u16 y; };
struct CoordinateCapture { struct ActorRecord *source; u8 *output; u32 count; u16 action; u16 slot; };
extern u32 HasPendingBattleEffect(u32,u32,u32,u32);
__asm__(".global HasPendingBattleEffect\n.thumb_set HasPendingBattleEffect,0x080b4c91");
u32 CaptureBattleEffectCoordinates(struct ActorRecord *record,struct CoordinateCapture *capture) __asm__("CoreRegion30_000B7F74");
u32 CaptureBattleEffectCoordinates(struct ActorRecord *record,struct CoordinateCapture *capture)
{
    if ((u8)HasPendingBattleEffect(capture->source->actor,record->actor,capture->action,capture->slot)) {
        capture->output[capture->count*4] = record->x >> 5;
        capture->output[capture->count*4+2] = record->attribute >> 4;
        capture->output[capture->count*4+1] = record->y >> 5;
        capture->count++;
    }
    return 1;
}
