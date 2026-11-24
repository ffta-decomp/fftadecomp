typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;u8 pad8[12];u16 variant,mode;} Event;
typedef struct Work {u8 variant,mode;s16 x,y;u16 unknown6;void *record,*coordinate_child,*model;u8 opaque20[8];void *window,*blend,*scripts[2],*secondary,*aux;} Work;
u32 RemainingBand43_000E7D20(void *,Event *,Work *);
void *RetailCall_080dd748(void *,s16 *,s16 *,s16 *);void RetailCall_080d45d0(const void *,u32,u32,u32,u32);
void RetailCall_080d49fc(u32,u32,u32,s32,s32);void *RetailCall_080d4b64(u32,const void *,u32,u32);u32 RetailCall_080035a8(u32);
void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080d4704(const void *,void *);void *RetailCall_080d4724(const void *,void *,u32);
void *RetailCall_080dcfe4(void *,const void *,u32,u32,u32,void *,u32);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d4d2c(void *,u32);void *RetailCall_080d6134(void *);void *RetailCall_080d3f08(void *);u32 RetailCall_080d48dc(void **,u32);void *RetailCall_080dba5c(void *);
#define PTRS(addr) ((const void **)(addr))
#define BYTES(addr) ((const u8 *)(addr))
#define HALVES(addr) ((const u16 *)(addr))

extern const void *const VariantModels[] __asm__("0x08397CC0");
extern const u16 VariantTiles[] __asm__("0x08397CCC");
extern const u8 WindowModes[] __asm__("0x08397CA0");
extern const void *const WindowResources[] __asm__("0x08397C94");
extern const void *const BlendResources[] __asm__("0x08397CD4");
extern const void *const FirstScripts[] __asm__("0x08397CA4");
extern const void *const SecondScripts[] __asm__("0x08397CB0");
extern const u8 SecondScriptParameters[] __asm__("0x08397CBC");
extern const u8 SecondaryDurations[] __asm__("0x08397CF8");
extern const void *const AuxiliaryDefinitions[] __asm__("0x08397D1C");
u32 RemainingBand43_000E7D20(void *parent,Event *event,Work *work) {
    s32 phase=event->phase,next_phase;
    switch(phase) {
    case 0:
        work->variant=event->variant;work->mode=event->mode;
        work->record=event->record;
        work->coordinate_child=RetailCall_080dd748(work->record,&work->x,&work->y,0);
        RetailCall_080d45d0((void*)0x088E9C0C,6,0,0,1);
        break;
    case 256: {
        u32 flags,aux_flags;
        register s32 advanced_phase asm("r0");
        RetailCall_080d49fc(0,2,0,work->x,work->y);
        work->model=RetailCall_080d4b64(0,VariantModels[work->variant],VariantTiles[work->variant],6);
        {
            u32 mask=RetailCall_080035a8(2);
            register u32 control asm("r1")=*(u16*)0x03000940;
            asm("" : "+r"(control));
            control|=mask;
            *(u16*)0x03000940=control;
        }
        work->window=RetailCall_080d6098(work->x,work->y,0,1,WindowModes[work->variant],work->opaque20,WindowResources[work->variant],parent);
        work->blend=RetailCall_080d3e9c(BlendResources[work->variant],parent);
        work->scripts[0]=RetailCall_080d4704(FirstScripts[work->variant],parent);
        work->scripts[1]=RetailCall_080d4724(SecondScripts[work->variant],parent,SecondScriptParameters[work->variant]);
        flags=(work->mode&1)?4:2;
        work->secondary=RetailCall_080dcfe4(work->record,(void*)0x08397CE4,12,SecondaryDurations[work->variant],flags,parent,SecondaryDurations[work->variant]);
        aux_flags=(work->mode&1)?16:8;
        work->aux=RetailCall_080dfd8c(AuxiliaryDefinitions[work->variant],1,aux_flags|4,0,parent);
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;
        goto store_phase;
    }
    case 257: {
        void *previous_model=work->model;
        u32 previous_bits=(u32)previous_model;
        u32 previously_active=((0U-previous_bits)|previous_bits)>>31;
        void *model=RetailCall_080d4d2c(previous_model,0);
        work->model=model;
        if(previously_active) {
            if(model)break;
            *(u16*)0x03000940 &= ~RetailCall_080035a8(2);
        }
        if(work->model)break;
        {
            void *window=RetailCall_080d6134(work->window);work->window=window;if(window)break;
            {
                void *blend=RetailCall_080d3f08(work->blend);work->blend=blend;if(blend)break;
                if(!(u8)RetailCall_080d48dc(work->scripts,2))break;
                next_phase=event->phase+1;goto store_phase;
            }
        }
        break;
    }
    case 258: {
        void *child=RetailCall_080dba5c(work->secondary);work->secondary=child;if(child)break;
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d45d0\n.thumb_set RetailCall_080d45d0, 0x080d45d1\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4724\n.thumb_set RetailCall_080d4724, 0x080d4725\n.global RetailCall_080d48dc\n.thumb_set RetailCall_080d48dc, 0x080d48dd\n.global RetailCall_080d49fc\n.thumb_set RetailCall_080d49fc, 0x080d49fd\n.global RetailCall_080d4b64\n.thumb_set RetailCall_080d4b64, 0x080d4b65\n.global RetailCall_080d4d2c\n.thumb_set RetailCall_080d4d2c, 0x080d4d2d\n.global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c, 0x080dba5d\n.global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4, 0x080dcfe5\n.global RetailCall_080dd748\n.thumb_set RetailCall_080dd748, 0x080dd749\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
