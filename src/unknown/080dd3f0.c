typedef unsigned char u8;
typedef unsigned int u32;
extern u32 *AllocateRecordWorkspace(unsigned);
extern void FreeRecordWorkspace(void *);
extern void *GetActorRecordRegistry(void);
extern unsigned CaptureActorRecordAddresses(void *,u32 *);
unsigned CopyBattleRegistryRecords(u32 *output) {
 u32 *temporary=AllocateRecordWorkspace(96);
 u8 count=CaptureActorRecordAddresses(GetActorRecordRegistry(),temporary);
 u8 index;
 for(index=0;index<count;index++) output[index]=temporary[index];
 FreeRecordWorkspace(temporary);
 return count;
}
__asm__(".global AllocateRecordWorkspace\n.thumb_set AllocateRecordWorkspace,0x0800a655\n.global FreeRecordWorkspace\n.thumb_set FreeRecordWorkspace,0x0800a669\n.global GetActorRecordRegistry\n.thumb_set GetActorRecordRegistry,0x08096d7d\n.global CaptureActorRecordAddresses\n.thumb_set CaptureActorRecordAddresses,0x08099d09");
