typedef unsigned char u8;
extern u8 gPrimaryBattleRecordBuffer[];
extern void ProcessBattleRecordsWithBuffer(void *context, void *buffer);
/* The scene-mode restore path selects this fixed buffer; direction stays
 * with the existing record-transfer implementation. */
void UsePrimaryBattleRecordBuffer(void *context)
{
    ProcessBattleRecordsWithBuffer(context, gPrimaryBattleRecordBuffer);
}
asm(".global ProcessBattleRecordsWithBuffer\n.thumb_set ProcessBattleRecordsWithBuffer,0x080992e1\n");
asm(".global gPrimaryBattleRecordBuffer\n.set gPrimaryBattleRecordBuffer,0x02000000\n");
