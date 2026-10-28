typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectEvent {u32 unknown0;void *record;u32 parameter;u32 unknown12,unknown16;u16 first,second;u32 unknown24;};
extern unsigned TestRecordEffectGate(void *);
extern void *CreateEffectTask(void *,u16,const struct EffectEvent *,void *);
void *CreateRecordEffectContinuation(void *record,u8 first,u8 second,u32 parameter,void *parent) {
 struct EffectEvent event;
 if((u8)TestRecordEffectGate(record)) return 0;
 event.first=first;
 event.second=second;
 event.record=record;
 event.parameter=parameter;
 return CreateEffectTask((void *)0x080fdb99,84,&event,parent);
}
__asm__(".global TestRecordEffectGate\n.thumb_set TestRecordEffectGate,0x080d3b55\n.global CreateEffectTask\n.thumb_set CreateEffectTask,0x08005b6d");
