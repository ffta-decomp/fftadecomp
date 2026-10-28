/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 gRecordControllerWorkspace[];
extern void AdvanceRecordController_080C5908(void *record);
extern unsigned ReadSaveByte(unsigned index);
extern void ProcessRecordState_080C586C(void *record);
extern void DrawRecordState_080C5448(void *record);
/* Verified original literals and direct BL entries; no instructions emitted. */
asm(".global gRecordControllerWorkspace\n.set gRecordControllerWorkspace,0x02015738\n.global AdvanceRecordController_080C5908\n.thumb_set AdvanceRecordController_080C5908,0x080c5909\n.global ProcessRecordState_080C586C\n.thumb_set ProcessRecordState_080C586C,0x080c586d\n.global DrawRecordState_080C5448\n.thumb_set DrawRecordState_080C5448,0x080c5449");


/* Byte14 is read after both helpers; a zero save mode skips both subrecord calls. */
void AdvanceSaveGatedRecordState(void)
{
    u8 *record = gRecordControllerWorkspace;
    AdvanceRecordController_080C5908(record);
    if ((u8)ReadSaveByte(13) != 0 && record[14] != 0) {
        record += 12;
        ProcessRecordState_080C586C(record);
        DrawRecordState_080C5448(record);
    }
}
