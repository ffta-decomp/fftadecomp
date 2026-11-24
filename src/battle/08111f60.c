typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;void **holder;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 tick;u8 pad2[4];u16 owner_index,echo_a,echo_b;s16 y_values[8];void **holder;void *echo;} Work;
void RetailCall_08011040(void*,u16*,u16*,u16*);void *RetailCall_080d5cc0(const void*,u32,s32,s32,u16,u8,u8,u8);void RetailCall_08011058(void*,s32);
void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);u32 RetailCall_080e0690(const Ramp*);
void RetailCall_080107d4(void*,s32,s32,s32);void RetailCall_08011428(void*);
typedef char WorkAccessedExtent36[(sizeof(Work)==36)?1:-1];
s32 RemainingBand43_00111F60(void *parent,Event *event,Work *work)
{
    Ramp path_ramp;
    u16 x,y,z;
    switch(event->phase) {
    case 0:
        work->holder=event->holder;
        break;
    case 1:
        break;
    case 256: {
        u8 index;
        s16 *path;
        RetailCall_08011040(*work->holder,&x,&y,&z);
        work->echo=RetailCall_080d5cc0((const void*)0x08504c6c,0,(s16)x,(s16)y,911,6,1,0);
        RetailCall_08011058(work->echo,1);
        RetailCall_080e0608(&path_ramp,(s16)y,-64,7);
        index=0;
        work->y_values[0]=path_ramp.value;
        path=work->y_values;
        do {
            index++;
            RetailCall_080e064c(&path_ramp);
            {
                register u32 slot_address asm("r1")=(u32)index*2;
                /* Actual byte offset becomes the actual path-slot address. */
                asm("add %0,%1,%0" : "+l"(slot_address) : "l"(path) : "cc");
                *(s16*)slot_address=path_ramp.value;
            }
        } while((u8)RetailCall_080e0690(&path_ramp)==0);
        work->owner_index=0;
        work->echo_a=0xfffd;
        work->echo_b=0xfffa;
        event->phase++;
        break;
    }
    case 257: {
        u32 owner=work->owner_index+1;
        s16 selected;
        work->owner_index=owner;
        work->echo_a++;
        work->echo_b++;
        work->tick++;
        if((s16)owner<=7)
            RetailCall_080107d4(*work->holder,120,work->y_values[(s16)work->owner_index],0);
        selected=work->echo_a;
        if(work->tick&1) selected=work->echo_b;
        if((u16)selected<=7)
            RetailCall_080107d4(work->echo,120,work->y_values[(s16)selected],0);
        if((s16)work->owner_index>7 && (s16)work->echo_a>7 && (s16)work->echo_b>7) {
            RetailCall_08011428(*work->holder);
            *work->holder=0;
            RetailCall_08011428(work->echo);
            work->echo=0;
            event->phase=2;
        }
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080107d4\n.thumb_set RetailCall_080107d4,0x080107d5\n.global RetailCall_08011040\n.thumb_set RetailCall_08011040,0x08011041\n.global RetailCall_08011058\n.thumb_set RetailCall_08011058,0x08011059\n.global RetailCall_08011428\n.thumb_set RetailCall_08011428,0x08011429\n.global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
