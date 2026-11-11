#include "ffta/unsigned_types.h"
typedef struct {u32 unknown0;void *output;u32 unknown8,unknown12,unknown16;u16 h20,h22,h24,h26;} Event;
typedef struct {u16 flags;u8 unknown2[6];u8 variant,signal;u16 unknown10;void *handle;void *objects[4];void *entry_child;void *children[4];void *step_child,*script,*sync;} Work;
typedef struct {u16 control;u8 reserved2[66];volatile u8 byte68,byte69;} Shadow;
extern Shadow DisplayShadow __asm__("0x03000940");
extern const void *VariantScripts[] __asm__("0x083A7A20");
extern const u8 VariantOffsets[] __asm__("0x083A7A0C");
extern void *CreateSync(const void *,u32,void *) __asm__("0x080D7A70");
extern void *PollSync(void *) __asm__("0x080D7ABC");
extern void *CreateTask(u32,u32,Event *,void *) __asm__("0x08005B6C");
extern void RunVariant(const void *,u32,u32,u32,u32) __asm__("0x080D45D0");
extern void DestroyObjects(void **,u32) __asm__("0x080D5F74");
extern void *PollChild(void *) __asm__("0x080E051C");
extern u32 PollChildren(void **,u32) __asm__("0x080E0570");
extern void *CreateScript(const void *,void *) __asm__("0x080D3E9C");
extern void *PollScript(void *) __asm__("0x080D3F08");
extern void Fade(u32,u32,u32,u32,u32,u32) __asm__("0x080D4A28");
extern void *CreateResource(u32,const void *,u32,u32) __asm__("0x080D4B64");
extern void PrepareResource(void) __asm__("0x0800BD7C");
extern void SetResourceMode(void *,u32) __asm__("0x0800BDF8");
extern u32 LayerMask(u32) __asm__("0x080035A8");
extern void ReleaseResource(void *,u32) __asm__("0x080D4D14");
#define SHADOW_CONTROL (*(volatile u16 *)&DisplayShadow.control)
#define ADVANCE() do { store_event=event; __asm__("" : "+r"(store_event)); next=(u32)*store_event+1; __asm__ volatile("" : "+r"(next)); goto store_phase; } while(0)
u32 AdvanceFiveVariantSceneSequence(void *parent,u16 *event,Work *work)
{
    Event first,step;
    register u32 flags __asm__("r1")=work->flags;
    u32 high_mask=0x8000;
    register u32 masked_working __asm__("r0");
    register u32 clear __asm__("r4");
    u32 next,phase;
    register u16 *store_event __asm__("r1");
    register u32 repeat_phase __asm__("r6");
    register u32 upper_phase __asm__("r0");
    __asm__("" : "+r"(high_mask));
    masked_working=high_mask;
    __asm__("" : "+r"(masked_working));
    masked_working&=flags;
    __asm__("" : "+r"(masked_working));
    clear=(u16)masked_working;
    __asm__("" : "+r"(clear));
    if(clear!=0)return 0;
    /* The native carries this actual zero across calls to its later clears. */
    __asm__("" : "+r"(clear));
    phase=*event;
    repeat_phase=257;
    __asm__("" : "+r"(repeat_phase) : "r"(phase));
    if(phase==repeat_phase)goto phase_257;
    if((int)phase>(int)repeat_phase)goto dispatch_upper;
    if(phase==1)goto done;
    if((int)phase>1)goto dispatch_lower_high;
    if(phase==0)goto phase_0;
    goto done;
dispatch_lower_high:
    if(phase==256)goto phase_256;
    goto done;
dispatch_upper:
    upper_phase=259;
    __asm__("" : "+r"(upper_phase));
    if(phase==upper_phase)goto phase_259;
    if((int)phase<(int)upper_phase)goto phase_258;
    ++upper_phase;
    if(phase==upper_phase)goto phase_260;
    ++upper_phase;
    if(phase==upper_phase)goto phase_261;
    goto done;
phase_0:
        work->sync=CreateSync((const void *)0x083A7498,9,parent);
        goto done;
phase_1:goto done;
phase_256: {
        u32 control;
        work->sync=PollSync(work->sync);
        if(work->sync)goto done;
        work->flags|=1;
        DisplayShadow.byte68=63;
        DisplayShadow.byte69=47;
        control=SHADOW_CONTROL;
        {
            register u32 mask_working __asm__("r0")=high_mask;
            __asm__("" : "+r"(mask_working) : "r"(control));
            mask_working|=control;
            SHADOW_CONTROL=(u16)mask_working;
        }
        ADVANCE();
    }
phase_257:
        first.h20=work->variant;
        first.output=&work->signal;
        work->entry_child=CreateTask(0x0811F95D,4156,&first,parent);
        ADVANCE();
phase_258: {
        u8 i;
        void **children;
        if(work->signal) {
            RunVariant(VariantScripts[work->variant],6,1,0,1);
            DestroyObjects(work->objects,4);
            work->signal=clear;
        }
        work->entry_child=PollChild(work->entry_child);
        if(work->entry_child)goto done;
        step.h20=work->variant;
        work->step_child=CreateTask(0x0811FFD9,68,&step,parent);
        i=0;
        {
            register void **initial_children __asm__("r0");
            /* Actual work+36 address; offset first, as in the native. */
            __asm__ volatile("mov %0,#36\n\tadd %0,%0,%1"
                             : "=&l"(initial_children) : "l"(work) : "cc");
            children=initial_children;
        }
        for(;i<4;++i) {
            step.h20=work->variant;
            step.h22=i;
            step.h24=80+VariantOffsets[i+work->variant*4];
            step.output=&work->objects[i];
            children[i]=CreateTask(0x08120399,24,&step,parent);
        }
        ADVANCE();
    }
phase_259:
        work->step_child=PollChild(work->step_child);
        if(work->step_child)goto done;
        if(!(u8)PollChildren(work->children,4))goto done;
        ++work->variant;
        if(work->variant<=4) {*event=(u16)repeat_phase;goto done;}
        SHADOW_CONTROL&=0x7FFF;
        work->script=CreateScript((const void *)0x0894DF44,parent);
        ADVANCE();
phase_260: {
        u32 mask;
        work->script=PollScript(work->script);
        if(work->script)goto done;
        DestroyObjects(work->objects,4);
        Fade(0,2,0,0,clear,1);
        work->handle=CreateResource(0,(const void *)0x088F3D90,412,8);
        PrepareResource();
        SetResourceMode(work->handle,5);
        mask=LayerMask(2);
        {
            register u32 control __asm__("r1")=SHADOW_CONTROL;
            __asm__("" : "+r"(control));
            control|=mask;
            SHADOW_CONTROL=(u16)control;
        }
        ADVANCE();
    }
phase_261:
        ReleaseResource(work->handle,0);
        work->handle=(void *)clear;
        next=2;__asm__ volatile("" : "+r"(next));
        store_event=event;__asm__("" : "+r"(store_event));
        goto store_phase;
done:
    return 0;
store_phase:
    *store_event=(u16)next;
    return 0;
}
