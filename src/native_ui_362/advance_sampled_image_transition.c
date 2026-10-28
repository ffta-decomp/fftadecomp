typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;u8 pad8[12];u16 variant,mode;} Event;
typedef struct Work {u8 variant,mode,sample,pad3;u16 timer;s16 x,y;u16 angle;void *record,*coordinate_child;u8 opaque20[8];void *window,*blend,*secondary,*aux;} Work;
typedef struct AuthoredRecord {u8 data[20];} AuthoredRecord;
extern const s16 Samples[] __asm__("0x08398444");extern const AuthoredRecord SecondaryRecords[] __asm__("0x08398484");extern const void *const AuxiliaryDefinitions[] __asm__("0x083984BC");extern const u8 ImageAsset[] __asm__("0x088F4ED0");
u32 RemainingBand43_000E8F3C(void *,Event *,Work *);
void *RetailCall_080dd748(void *,s16 *,s16 *,s16 *);u32 RetailCall_080dd580(void *);
void RetailCall_080d73ac(const void *,u32,u32,s32,s32,u32);void RetailCall_080d6e30(const void *,u32,s32,s32,s32,s32,u32);
u32 RetailCall_080035a8(u32);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080dcfe4(void *,const void *,u32,u32,u32,void *,u32);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);void *RetailCall_080d3f08(void *);void *RetailCall_080d6134(void *);void *RetailCall_080dba5c(void *);

u32 RemainingBand43_000E8F3C(void *parent,Event *event,Work *work) {
    s32 phase=event->phase,next_phase;
    switch(phase) {
    case 0:
        work->variant=event->variant;work->mode=event->mode;
        work->record=event->record;
        work->coordinate_child=RetailCall_080dd748(work->record,&work->x,&work->y,0);
        break;
    case 256: {
        const void *asset=ImageAsset;
        u32 zero;
        u32 secondary_flags,aux_flags;
        register s32 advanced_phase asm("r0");
        RetailCall_080d73ac(asset,0,2,work->x,(s16)((u16)work->y-16),({zero=0;asm("" : "+r"(zero));zero;}));
        RetailCall_080d6e30(asset,2,work->x,(s16)((u16)work->y-16),Samples[work->sample],Samples[work->sample],zero);
        ++work->sample;
        if(work->variant==1)work->angle+=2048;
        {
            u32 mask=RetailCall_080035a8(2);
            register u32 control asm("r1")=*(u16*)0x03000940;
            asm("" : "+r"(control));
            control|=mask;
            *(u16*)0x03000940=control;
        }
        work->blend=RetailCall_080d3e9c((void*)0x0894D730,parent);
        secondary_flags=(work->mode&1)?4:2;
        work->secondary=RetailCall_080dcfe4(work->record,&SecondaryRecords[work->variant],12,55,secondary_flags,parent,60);
        work->timer=35;
        aux_flags=(work->mode&1)?16:8;
        work->aux=RetailCall_080dfd8c(AuxiliaryDefinitions[work->variant],1,aux_flags|4,0,parent);
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;goto store_phase;
    }
    case 257: {
        u32 remaining;
        if(work->sample<=31) {
            RetailCall_080d6e30(ImageAsset,2,work->x,(s16)((u16)work->y-16),Samples[work->sample],Samples[work->sample],work->angle);
            ++work->sample;
            if(work->variant==1)work->angle+=2048;
        } else if(work->sample==32) {
            RetailCall_080d6e30(ImageAsset,2,work->x,(s16)((u16)work->y-16),256,256,0);
        }
        remaining=work->timer-1;work->timer=remaining;
        if(!(u16)remaining) {
            if((u8)RetailCall_080dd580(work->record))
                work->window=RetailCall_080d6098(work->x,work->y,0,1,2,work->opaque20,(void*)0x08398414,parent);
            work->timer=5;work->sample=31;
            next_phase=event->phase+1;goto store_phase;
        }
        break;
    }
    case 258: {
        u32 had_blend=1;
        void *before,*blend;
        if(!work->timer) {
            if(work->variant==0) {
                if(work->sample)--work->sample;
            } else work->angle+=4096;
        } else --work->timer;
        RetailCall_080d6e30(ImageAsset,2,work->x,(s16)((u16)work->y-16),Samples[work->sample],Samples[work->sample],work->angle);
        before=work->blend;
        if(!before)had_blend=0;
        blend=RetailCall_080d3f08(before);work->blend=blend;if(blend)break;
        if(had_blend)*(u16*)0x03000940 &= ~RetailCall_080035a8(2);
        {
            void *window=RetailCall_080d6134(work->window);work->window=window;if(window)break;
            {
                void *secondary=RetailCall_080dba5c(work->secondary);work->secondary=secondary;if(secondary)break;
                next_phase=2;
store_phase:
                event->phase=next_phase;
            }
        }
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080d6e30\n.thumb_set RetailCall_080d6e30, 0x080d6e31\n.global RetailCall_080d73ac\n.thumb_set RetailCall_080d73ac, 0x080d73ad\n.global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c, 0x080dba5d\n.global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4, 0x080dcfe5\n.global RetailCall_080dd580\n.thumb_set RetailCall_080dd580, 0x080dd581\n.global RetailCall_080dd748\n.thumb_set RetailCall_080dd748, 0x080dd749\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
