typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern void CopyDefinitionRecordCoordinates(const u16*,u16*,u16*,u16*);
extern void RequestCoordinateCommand(u32,s32,s32,s32,u32);
asm(".global CopyDefinitionRecordCoordinates\n.thumb_set CopyDefinitionRecordCoordinates,0x080dbd5d\n.global RequestCoordinateCommand\n.thumb_set RequestCoordinateCommand,0x080a92e5\n");
void RequestRecordCoordinateMode1(const u16 *record, u32 mode) __asm__("RemainingBand43_000DD288");
void RequestRecordCoordinateMode1(const u16 *record, u32 mode)
{
    u16 saved_mode;
    s32 signed_mode;
    u16 z;
    u16 y;
    u16 x;
    saved_mode = mode;
    CopyDefinitionRecordCoordinates(record,&x,&y,&z);
    signed_mode = (s16)saved_mode;
    RequestCoordinateCommand(signed_mode,(s16)x,(s16)(y+56),(s16)z,1);
}
