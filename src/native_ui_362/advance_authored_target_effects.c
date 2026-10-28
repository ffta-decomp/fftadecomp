typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void *record;u32 word8,word12,word16;u16 mode,unknown22;u32 word24;} Event;
typedef struct Config {u16 unknown0,value;u8 unknown4[5];u8 flag;u8 unknown10[10];} Config;
typedef struct Work {u8 mode,delay,count,index;void *record,*actor,*handles[4];Config configuration;} Work;
typedef void *(*CopyFunction)(void*,const void*,u32);
u32 RetailCall_080d8858(void*,u16);
void *RetailCall_08142250(void*,const void*,u32,CopyFunction);
void *RetailCall_080dd4b4(void*,u8);
u32 RetailCall_080db838(const void*);
u32 RetailCall_080d8b4c(void);
void *RetailCall_080dba5c(void*);
void *RetailCall_080dd4a4(void*,u8);
void *RetailCall_080dcfe4(void*,const void*,u8,u16,u16,void*,u16);

s32 RemainingBand43_0011584C(void *parent,Event *event,Work *work)
{
    switch((s32)event->phase) {
    case 0:
        work->mode=event->mode;
        work->record=event->record;
        work->count=RetailCall_080d8858(work->record,0);
        if(work->count==0) break;
        (*(CopyFunction*)0x0836d4bc)(&work->configuration,(const void*)0x083a3d20,20);
        switch(work->mode) {
        case 0: break;
        case 1: work->configuration.value=7;break;
        case 2: work->configuration.value=6;goto set_flag;
        case 3:
            work->configuration.value=2;
        set_flag:
            work->configuration.flag=1;
            break;
        case 4: work->configuration.value=4;break;
        }
        work->actor=RetailCall_080dd4b4(work->record,work->index);
        RetailCall_080db838(work->actor);
        break;
    case 1: break;
    case 256: {
        u8 index;
        u32 variant,next,parity;
        register u32 target_index asm("r2");
        void *cell,*child;
        if(work->count==0) {event->phase=259;break;}
        if((u8)RetailCall_080d8b4c()!=0) break;
        index=0;
        do {
            work->handles[index]=RetailCall_080dba5c(work->handles[index]);
            index++;
        } while(index<=3);
        cell=RetailCall_080dd4a4(work->record,work->index);
        target_index=work->index;
        /* Actual post-call index; short R2 lifetime ends at mask consumption. */
        asm("" : "+r"(target_index));
        parity=target_index&1;
        variant=2;
        if(parity!=0) variant=4;
        child=RetailCall_080dcfe4(cell,&work->configuration,12-(target_index&6),0,variant|8,parent,0);
        work->handles[work->index&3]=child;
        next=work->index+1;
        work->index=next;
        if((u8)next==work->count) event->phase=259;
        else {work->delay=30;event->phase++;}
        break;
    }
    case 257: {
        u32 remaining=work->delay-1;
        work->delay=remaining;
        if((u8)remaining!=0) break;
        work->actor=RetailCall_080dd4b4(work->record,work->index);
        RetailCall_080db838(work->actor);
        event->phase=256;
        break;
    }
    case 258: event->phase++;break;
    case 259: {
        u32 all_done=1;
        u8 index=0;
        do {
            void *child=RetailCall_080dba5c(work->handles[index]);
            work->handles[index]=child;
            if(child!=0) all_done=0;
            index++;
        } while(index<=3);
        if(all_done!=0) event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080d8858\n.thumb_set RetailCall_080d8858,0x080d8859\n");
asm(".global RetailCall_080d8b4c\n.thumb_set RetailCall_080d8b4c,0x080d8b4d\n");
asm(".global RetailCall_080db838\n.thumb_set RetailCall_080db838,0x080db839\n");
asm(".global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c,0x080dba5d\n");
asm(".global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4,0x080dcfe5\n");
asm(".global RetailCall_080dd4a4\n.thumb_set RetailCall_080dd4a4,0x080dd4a5\n");
asm(".global RetailCall_080dd4b4\n.thumb_set RetailCall_080dd4b4,0x080dd4b5\n");
asm(".global RetailCall_08142250\n.thumb_set RetailCall_08142250,0x08142251\n");
asm(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
