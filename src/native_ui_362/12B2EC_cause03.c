typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*CopyRoutine)(void *,const void *,u32);
extern u8 NamePageWorkspace[];
extern u8 NamePageShadow[];
extern CopyRoutine NamePageCopyRoutine;
extern u32 DecodeRecordAsset(void *,const void *);
extern void CopyHalfwords(const void *,void *,u32);
extern u32 LoadRecordSlot(const void *,u32);
extern void CopyRecordTable(void *,u32);
void UploadOriginalNamePage(const void *) asm("CoreRegion_0012B2EC");
void UploadOriginalNamePage(const void *record)
{
    u32 count=DecodeRecordAsset(NamePageWorkspace,record);
    CopyHalfwords(NamePageWorkspace,(void *)0x06014800,(count<<10)>>11);
    CopyRecordTable(NamePageWorkspace,(u8)LoadRecordSlot(record,1));
    NamePageCopyRoutine(NamePageShadow,NamePageWorkspace,96);
}
asm(".global NamePageWorkspace\n.set NamePageWorkspace,0x02003CB0\n.global NamePageShadow\n.set NamePageShadow,0x03003B20\n.global NamePageCopyRoutine\n.set NamePageCopyRoutine,0x0836D4BC\n.global DecodeRecordAsset\n.thumb_set DecodeRecordAsset,0x080CB869\n.global CopyHalfwords\n.thumb_set CopyHalfwords,0x0814186D\n.global LoadRecordSlot\n.thumb_set LoadRecordSlot,0x080CB7C1\n.global CopyRecordTable\n.thumb_set CopyRecordTable,0x080CB8D5\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
