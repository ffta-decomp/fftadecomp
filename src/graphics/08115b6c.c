typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad2;void *record;u8 *ready;u8 unknown12[16];} Event;
typedef struct Work {s16 x,y;u16 unknown4;u8 phase,pad7;u8 *ready;void *sprite,*resource,*palette,*effect,*record;} Work;
s32 RemainingBand43_00115B6C(void*,Event*,Work*);
void *RetailCall_080dd4a4(void*,u32);void *RetailCall_080dd748(void*,s16*,s16*,u32);void RetailCall_080dbc18(void*,u32);void RetailCall_08011428(void*);u32 RetailCall_080de488(void*);u32 RetailCall_080dbc58(void*,u32);
void *RetailCall_08147d94(u32,u32,u32,u32,u32,u32);void *RetailCall_080d4704(const void*,void*);void *RetailCall_081484cc(void*);
const void *RetailCall_080dbd30(void*,u8*,u8*);u32 RetailCall_080dbd48(void*);
void *RetailCall_08011348(const void*,u32,u32,u32,s32,s32,u32,s32,u32,u32);
void RetailCall_08011118(void*,u32);void RetailCall_08011120(void*,u32);void RetailCall_08011138(void*,u32);
void *RetailCall_08147d2c(u32,u32,u32,const void*);void *RetailCall_080d4774(void*);
typedef char WorkSize32[sizeof(Work)==32?1:-1];
s32 RemainingBand43_00115B6C(void *parent,Event *event,Work *work)
{
    u8 variant_a,variant_b;
    switch(event->phase) {
    case 0:
        work->record=event->record;
        work->ready=event->ready;
        *work->ready=0;
        work->resource=RetailCall_080dd748(RetailCall_080dd4a4(work->record,0),&work->x,&work->y,0);
        break;
    case 1:
        if(work->resource)RetailCall_080dbc18(work->resource,work->phase);
        if(work->sprite) {
            RetailCall_08011428(work->sprite);
            work->sprite=0;
        }
        break;
    case 256:
        if(!(u8)RetailCall_080de488(work->resource))break;
        work->phase=RetailCall_080dbc58(work->resource,7);
        work->palette=RetailCall_08147d94(368,16,12,0x7fff,16,16);
        work->effect=RetailCall_080d4704((const void*)0x0894ac90,parent);
        goto advance;
    case 257: {
        void *completed=RetailCall_081484cc(work->palette);
        const void *descriptor;
        u32 depth;
        work->palette=completed;
        if(completed)break;
        descriptor=RetailCall_080dbd30(work->resource,&variant_a,&variant_b);
        depth=RetailCall_080dbd48(work->resource);
        work->sprite=RetailCall_08011348(descriptor,0,0,0,work->x,(s16)(work->y+8),(u32)completed,(s16)depth,7,6);
        RetailCall_08011118(work->sprite,variant_a);
        RetailCall_08011120(work->sprite,variant_b);
        RetailCall_08011138(work->sprite,1);
        work->palette=RetailCall_08147d2c(368,16,20,(const void*)(0x03003a60+(work->phase<<5)));
        *work->ready=1;
        asm volatile("mov r1, %0\n\tldrh r0, [r1]\n\tadd r0, r0, #1\n\tstrh r0, [r1]" : : "h" (event) : "r0", "r1", "cc", "memory");
        break;
    }
    case 258:
        work->palette=RetailCall_081484cc(work->palette);
        if(work->palette)break;
        work->effect=RetailCall_080d4774(work->effect);
        if(work->effect)break;
    advance:
        asm volatile("mov r2, %0\n\tldrh r0, [r2]\n\tadd r0, r0, #1\n\tstrh r0, [r2]" : : "h" (event) : "r0", "r2", "cc", "memory");
        break;
    case 259:
        break;
    }
    return 0;
}
asm(".global RetailCall_08011118\n.thumb_set RetailCall_08011118, 0x08011119\n.global RetailCall_08011120\n.thumb_set RetailCall_08011120, 0x08011121\n.global RetailCall_08011138\n.thumb_set RetailCall_08011138, 0x08011139\n.global RetailCall_08011348\n.thumb_set RetailCall_08011348, 0x08011349\n.global RetailCall_08011428\n.thumb_set RetailCall_08011428, 0x08011429\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080dbc18\n.thumb_set RetailCall_080dbc18, 0x080dbc19\n.global RetailCall_080dbc58\n.thumb_set RetailCall_080dbc58, 0x080dbc59\n.global RetailCall_080dbd30\n.thumb_set RetailCall_080dbd30, 0x080dbd31\n.global RetailCall_080dbd48\n.thumb_set RetailCall_080dbd48, 0x080dbd49\n.global RetailCall_080dd4a4\n.thumb_set RetailCall_080dd4a4, 0x080dd4a5\n.global RetailCall_080dd748\n.thumb_set RetailCall_080dd748, 0x080dd749\n.global RetailCall_080de488\n.thumb_set RetailCall_080de488, 0x080de489\n.global RetailCall_08147d2c\n.thumb_set RetailCall_08147d2c, 0x08147d2d\n.global RetailCall_08147d94\n.thumb_set RetailCall_08147d94, 0x08147d95\n.global RetailCall_081484cc\n.thumb_set RetailCall_081484cc, 0x081484cd\n");
