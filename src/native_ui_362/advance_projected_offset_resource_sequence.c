typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;u8 pad8[12];u16 mode;} Event;
typedef struct Work {u16 unknown0;s16 x,y;u8 mode,pad7;void *record,*coordinate_child;u8 opaque16[24];void *window,*secondary,*aux;} Work;
u32 RemainingBand43_000E7B04(void *,Event *,Work *);
void *RetailCall_080dd748(void *,s16 *,s16 *,s16 *);void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);
void RetailCall_080dbda0(void *,u16 *,u16 *,u16 *);void RetailCall_080d620c(void *,s32);
void *RetailCall_080dcfe4(void *,const void *,u32,u32,u32,void *,u32);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d6134(void *);void *RetailCall_080dba5c(void *);

u32 RemainingBand43_000E7B04(void *parent,Event *event,Work *work) {
    s32 phase=event->phase;
    s32 next_phase;
    switch(phase) {
    case 0:
        work->record=event->record;work->mode=event->mode;
        work->coordinate_child=RetailCall_080dd748(work->record,&work->x,&work->y,0);
        break;
    case 1:break;
    case 256: {
        u16 out_x,out_y,out_z;
        u32 flags;
        work->window=RetailCall_080d6098(work->x,work->y,0,1,6,work->opaque16,(void*)0x08397A68,parent);
        RetailCall_080dbda0(work->coordinate_child,&out_x,&out_y,&out_z);
        RetailCall_080d620c(work->window,(s16)(-out_z));
        flags=(work->mode&1)?4:2;
        work->secondary=RetailCall_080dcfe4(work->record,(void*)0x08397AF8,12,85,flags,parent,85);
        flags=(work->mode&1)?16:8;
        work->aux=RetailCall_080dfd8c((void*)0x08397B0C,1,flags|4,0,parent);
        next_phase=event->phase+1;
        goto store_phase;
    }
    case 257: {
        void *child=RetailCall_080d6134(work->window);work->window=child;if(child)break;
        child=RetailCall_080dba5c(work->secondary);work->secondary=child;if(child)break;
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080d620c\n.thumb_set RetailCall_080d620c, 0x080d620d\n.global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c, 0x080dba5d\n.global RetailCall_080dbda0\n.thumb_set RetailCall_080dbda0, 0x080dbda1\n.global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4, 0x080dcfe5\n.global RetailCall_080dd748\n.thumb_set RetailCall_080dd748, 0x080dd749\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
