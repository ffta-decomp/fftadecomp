typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u32 opaque4[6];} Event;
typedef struct Work {void *background,*sequence,*window,*extra;} Work;
void *RetailCall_080d3e9c(const void*,void*);void *RetailCall_080d3f08(void*);void *RetailCall_080d4704(const void*,void*);void *RetailCall_080d4774(void*);void *RetailCall_080dad94(u32,u32,u32,void*);void *RetailCall_080dae44(void*);void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);

extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
s32 RemainingBand43_001101DC(void *parent,Event *event,Work *work)
{
    u16 phase=event->phase;
    switch(phase) {
    case 0:
        work->background=RetailCall_080d3e9c((const void*)0x0894d97c,parent);
        work->window=RetailCall_080dad94(120,80,0,parent);
        display_shadow[66]=63;
        display_shadow[67]=63;
        display_shadow[68]=31;
        display_shadow[59]=phase;
        display_shadow[58]=phase;
        display_shadow[63]=phase;
        ((u8*)display_shadow)[62]=255;
        display_shadow[61]=phase;
        display_shadow[60]=phase;
        display_shadow[65]=phase;
        (void)display_shadow[64];
        {
            register s32 all_bits asm("r0")=-1;
            asm("" : "+r"(all_bits));
            ((s8*)display_shadow)[64]=all_bits;
        }
        {
            register volatile u8 *base asm("r2")=display_shadow;
            asm volatile("ldrh r1,[%0]\nmov r3,#192\nlsl r3,r3,#7\nmov r0,r3\norr r0,r1\nstrh r0,[%0]" : : "r"(base) : "r0","r1","r3","cc","memory");
        }
        work->extra=RetailCall_080dfd8c((const void*)0x083a2ef8,1,4,0,parent);
        work->sequence=RetailCall_080d4704((const void*)0x0894a9c8,parent);
        break;
    case 1:
        break;
    case 256:
        work->background=RetailCall_080d3f08(work->background);
        if(work->background!=0) break;
        work->sequence=RetailCall_080d4774(work->sequence);
        if(work->sequence!=0) break;
        work->window=RetailCall_080dae44(work->window);
        if(work->window!=0) break;
        {
            register volatile u8 *base asm("r1")=display_shadow;
            register u32 final_control asm("r0");
            register u32 prior_control asm("r2");
            register u32 clear asm("r2");
            prior_control=*(volatile u16*)base;
            asm("" : "+r"(prior_control) : "r"(base));
            final_control=0x9fff&prior_control;
            clear=0;
            asm("" : "+r"(clear) : "r"(final_control));
            *(volatile u16*)base=final_control;
            base+=74;
            (void)*base;
            *base=clear;
        }
        event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080dad94\n.thumb_set RetailCall_080dad94, 0x080dad95\n.global RetailCall_080dae44\n.thumb_set RetailCall_080dae44, 0x080dae45\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
