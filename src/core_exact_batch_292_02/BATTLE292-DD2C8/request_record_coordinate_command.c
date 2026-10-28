typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern void CopyDefinitionRecordCoordinates(const u16*,u16*,u16*,u16*);
extern void RequestCoordinateCommand(u32,s32,s32,s32,u32);
asm(".global CopyDefinitionRecordCoordinates\n.thumb_set CopyDefinitionRecordCoordinates,0x080dbd5d\n.global RequestCoordinateCommand\n.thumb_set RequestCoordinateCommand,0x080a92e5\n");
void RequestRecordCoordinateCommand(const u16 *record, u32 command) __asm__("RemainingBand43_000DD2C8");
void RequestRecordCoordinateCommand(const u16 *record, u32 command)
{
    u8 saved_command;
    u16 z;
    u16 y;
    u16 x;
    saved_command = command;
    CopyDefinitionRecordCoordinates(record,&x,&y,&z);
    RequestCoordinateCommand(0,(s16)x,(s16)(y+56),(s16)z,saved_command);
}
