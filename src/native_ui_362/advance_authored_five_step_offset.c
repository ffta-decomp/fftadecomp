typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
struct Event {u16 phase,unknown2;void **holder;u32 opaque8[5];};
struct Work {u16 counter;u8 unknown2[6];void **holder;u32 unknown12;};
extern void CopyStepOffsets(void*,const void*,u32);
extern void ReadObjectCoordinates(void*,u16*,u16*,u16*);
extern void WriteObjectCoordinates(void*,s32,s32,s32);
__asm__(".global CopyStepOffsets\n.thumb_set CopyStepOffsets,0x081443fd\n.global ReadObjectCoordinates\n.thumb_set ReadObjectCoordinates,0x08011041\n.global WriteObjectCoordinates\n.thumb_set WriteObjectCoordinates,0x080107d5");
u32 RemainingBand43_00111D50(void *parent,struct Event *event,struct Work *work)
{
    u16 offsets[5];
    u16 x,y,z;
    switch(event->phase) {
    case 0:
        work->holder=event->holder;
        break;
    case 1:
        break;
    case 256: {
        u32 counter;
        CopyStepOffsets(offsets,(const void*)0x08149f40,10);
        ReadObjectCoordinates(*work->holder,&x,&y,&z);
        y-=offsets[work->counter];
        WriteObjectCoordinates(*work->holder,(s16)x,(s16)y,(s16)z);
        counter=work->counter+1;
        work->counter=counter;
        if((u16)counter>4) event->phase=2;
        break;
    }
    }
    return 0;
}
