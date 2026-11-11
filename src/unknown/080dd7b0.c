typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*HandleRoutine)(void *,u32,u32,u32,u32,u32);
struct RecordHandles { u8 unknown0[84]; void *primary; void *secondary; };
extern HandleRoutine const gHandleRoutine;
void RemainingBand43_000DD7B0(struct RecordHandles *record,u8 mode,u8 include_secondary)
{
    void *primary=record->primary;
    void *secondary=record->secondary;
    if(primary) gHandleRoutine(primary,mode,0,0,0,0);
    if(include_secondary && secondary) gHandleRoutine(secondary,mode,0,0,0,0);
}
asm(".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n.global gHandleRoutine\n.set gHandleRoutine,0x08394034\n");
