typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 kind;u8 untouched[26];} EventPacket;
extern u8 *gOwner asm("Owner");
extern u32 GetSelection(void *,int) asm("RetailCall_08017b68");
extern u8 *GetChildData(void *) asm("RetailCall_08005bfc");
extern void SendChildEvent(void *,const EventPacket *) asm("RetailCall_08005c04");
void PublishSelectedMenuContent(u8 *object) asm("CoreRegion30_0005F69C");
void PublishSelectedMenuContent(u8 *object) {
 EventPacket packet;
 register u8 *owner asm("r4")=gOwner;
 register u32 offset asm("r0");
 void *content;
 u8 *child;
 offset=4*(u32)(u16)GetSelection(object+60,(s8)object[109]);
 asm("" : "+r"(offset), "+r"(owner));
 owner+=32;
 owner+=offset;
 asm("" : "+r"(owner));
 content=*(void **)owner;
 child=GetChildData(*(void **)(object+12));
 *(void **)(child+0x108c)=content;
 packet.kind=258;
 SendChildEvent(*(void **)(object+12),&packet);
}
asm(".global Owner\n.set Owner,0x0200f44c\n.global RetailCall_08017b68\n.thumb_set RetailCall_08017b68,0x08017b69\n.global RetailCall_08005bfc\n.thumb_set RetailCall_08005bfc,0x08005bfd\n.global RetailCall_08005c04\n.thumb_set RetailCall_08005c04,0x08005c05\n");
