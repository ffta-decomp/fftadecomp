typedef unsigned char u8; typedef unsigned short u16;
struct Actor;
struct Record {struct Actor *actor;u8 unknown4[36];u8 animation;};
int QueryIndex(struct Actor *) __asm__("RetailCall_0809a53c");
unsigned int RemapPhase(struct Record *) __asm__("RetailCall_0809b120");
void SetFlags(struct Actor *,u16,u16) __asm__("RetailCall_0809a570");
void SetCursor(struct Actor *,unsigned int) __asm__("RetailCall_0809a530");
void CoreStateDirect_0009B7C0(struct Record *record)
{
    int index=QueryIndex(record->actor);
    record->animation=index;
    if((u8)index) record->animation=index-1;
    RemapPhase(record);
    SetFlags(record->actor,0,256);
    switch(record->animation) {
    case 0:case 1: record->animation=2; break;
    case 2:case 3: record->animation=0; break;
    }
    SetCursor(record->actor,record->animation);
}
asm(".global RetailCall_0809a53c\n.thumb_set RetailCall_0809a53c,0x0809a53d\n.global RetailCall_0809b120\n.thumb_set RetailCall_0809b120,0x0809b121\n.global RetailCall_0809a570\n.thumb_set RetailCall_0809a570,0x0809a571\n.global RetailCall_0809a530\n.thumb_set RetailCall_0809a530,0x0809a531\n");
