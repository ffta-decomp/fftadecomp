typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u8 *completion;void **sprite_cell;u16 **coordinate_pair;u32 opaque16[3];} Event;
typedef struct Rect {u16 x,y,opaque4,opaque6,width,height;} Rect;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 timer;u8 pad2[6];u16 *out_x,*out_y;u16 view_value,pad18;u8 *completion;void **sprite_cell;void *raster,*background,*view,*extra;} Work;
void RetailCall_0801e6f0(u16*,u16*);void RetailCall_0801ba20(s32,s32,u32);u32 RetailCall_0801bdb0(void);
void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*);void RetailCall_0801e610(u8*,u8*);u32 RetailCall_080035a8(u32);
void RetailCall_080d49fc(u32,u32,u32,u32,u32);void RetailCall_0800bc90(u32,u32,u32);void RetailCall_0800bd24(u32,u32);
void *RetailCall_080d4b64(u32,const void*,u32,u32);void RetailCall_080d4d14(void*,u32);void RetailCall_0800bd7c(void*);void RetailCall_0800bd90(void*);
void RetailCall_080dbed4(u32,u32,u32,u32);void RetailCall_0801cae0(Rect*);
void *RetailCall_080d89d0(u32,u8,u8,u8,u32,u32,void*,void*,u32,u8,u8,u8,u8,void*);
void RetailCall_080d8b18(void*,u16*);void *RetailCall_080d8aec(void*);void *RetailCall_080d3e9c(const void*,void*);void *RetailCall_080d3f08(void*);void RetailCall_080d3efc(void*);
void RetailCall_080d72c8(const void*,u32,u32,u32,u32,u32,u32);
void *RetailCall_080d5cc0(const void*,u32,s32,s32,u16,u8,u8,u32);
void *RetailCall_080d3af8(void);void RetailCall_08000b20(void*,u32,void*,u32);
void RetailCall_08115a1c(u32,u32,u32,u16*,u16*);u16 *RetailCall_0801dc5c(void);
void RetailCall_0814186c(const void*,void*,u32);void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
typedef union StageScratch {Rect rect;struct {Ramp red,green,blue;u16 zero,color;} palette;} StageScratch;
typedef char ScratchMustBe40[(sizeof(StageScratch)==40)?1:-1];
typedef char WorkMustBe44[(sizeof(Work)==44)?1:-1];
s32 RemainingBand43_001112A0(void *parent,Event *event,Work *work)
{
    u16 camera_x,camera_y;
    u8 layer_a,layer_b;
    u32 next_phase;
    register Event *store_event __asm__("r2");
    switch(event->phase) {
    case 0:
        work->completion=event->completion;
        work->sprite_cell=event->sprite_cell;
        work->out_x=event->coordinate_pair[0];
        work->out_y=event->coordinate_pair[1];
        break;
    case 1:
        break;
    case 256: {
        register s32 camera_target __asm__("r1");
        void *created;
        RetailCall_0801e6f0(&camera_x,&camera_y);
        camera_target=-192;
        __asm__("" : "+r"(camera_target));
        camera_y=camera_target;
        RetailCall_0801ba20((s16)camera_x,camera_target,8);
        created=RetailCall_080dfd8c((const void*)0x083a33ac,1,4,0,parent);
        work->extra=created;
        __asm__ volatile("" : : "r"(created));
        goto advance_phase;
    }
    case 257:
        if((u8)RetailCall_0801bdb0()!=0) break;
        RetailCall_080d49fc(1,3,0,0,0);
        RetailCall_0800bc90(1,0,3);
        RetailCall_0800bd24(1,0);
        work->raster=RetailCall_080d4b64(1,(const void*)0x088f11d0,930,7);
        work->background=RetailCall_080d3e9c((const void*)0x0894dbc0,parent);
        {u32 mask=RetailCall_080035a8(3);
         register u32 control __asm__("r1")=CONTROL;
         __asm__("" : "+r"(control));
         control|=mask;
         __asm__("" : "+r"(control));
         CONTROL=control;}
        store_event=event;
        __asm__("" : "+r"(store_event));
        next_phase=store_event->phase+1;
        __asm__("" : "+r"(next_phase));
        goto store_phase;
    case 258:
        RetailCall_0801e610(&layer_a,&layer_b);
        CONTROL&=~RetailCall_080035a8(layer_a);
        CONTROL&=~RetailCall_080035a8(layer_b);
        RetailCall_080dbed4(0,0,0,0);
        {
            StageScratch scratch;
            register Rect *rect_fields __asm__("r1")=&scratch.rect;
            __asm__ volatile("add r0, sp, #48\n\tbl RetailCall_0801cae0" : : : "r0", "r1", "r2", "r3", "r12", "lr", "cc", "memory");
            work->view=RetailCall_080d89d0(4,4,0,0,608,285,(void*)0x0600cc00,(void*)0x06007000,1023,
                (u8)((s16)({register Rect *first_rect __asm__("r1"); __asm__ volatile("add %0, sp, #48" : "=r"(first_rect)); first_rect->x;})>>3),(u8)((s16)rect_fields->y>>3),(u8)(rect_fields->width>>3),(u8)(rect_fields->height>>3),parent);
            RetailCall_080d8b18(work->view,&work->view_value);
        work->timer=30;
        goto advance_phase;
    case 259: {
        register u32 raw_timer __asm__("r0")=work->timer-1;
        u16 remaining;
        work->timer=raw_timer;
        __asm__("" : "+r"(raw_timer));
        remaining=(u16)raw_timer;
        if(remaining!=0) break;
        RetailCall_080d3efc(work->background);
        work->background=(void*)(u32)remaining;
        RetailCall_0800bd7c(work->raster);
        store_event=event;
        __asm__("" : "+r"(store_event));
        next_phase=store_event->phase+1;
        __asm__("" : "+r"(next_phase));
        goto store_phase;
    }
    case 260: {
        u32 completed=(u32)RetailCall_080d8aec(work->view);
        work->view=(void*)completed;
        if(completed!=0) break;
        RetailCall_08115a1c(120,106,work->view_value,work->out_x,work->out_y);
        RetailCall_0800bd90(work->raster);
        work->background=RetailCall_080d3e9c((const void*)0x083a33e4,parent);
        RetailCall_080d72c8((const void*)0x088f5d28,0,2,0,completed,completed,3);
        *work->sprite_cell=RetailCall_080d5cc0((const void*)0x08504c6c,0,120,64,911,6,1,completed);
        RetailCall_08000b20(RetailCall_080d3af8(),1023,(void*)0x06007800,1024);
        work->extra=RetailCall_080dfd8c((const void*)0x083a33b4,1,4,0,parent);
        goto advance_phase;
    }
    case 261: {
        register u16 *palette __asm__("r9")=RetailCall_0801dc5c();
        u16 index;
        register u16 *zero_ptr __asm__("r0");
        register u16 *color_ptr __asm__("r10");
        register Ramp *red_ptr __asm__("r6");
        register Ramp *green_ptr __asm__("r5");
        register Ramp *blue_ptr __asm__("r4");
        __asm__("" : "+r"(palette));
        zero_ptr=&scratch.palette.zero;
        __asm__("" : "+r"(zero_ptr));
        *zero_ptr=0;
        RetailCall_0814186c(zero_ptr,palette,0x01000040);
        __asm__ volatile("add %0, sp, #48" : "=r"(red_ptr));
        RetailCall_080e0608(red_ptr,0,4,72);
        green_ptr=&scratch.palette.green; __asm__("" : "+r"(green_ptr));
        RetailCall_080e0608(green_ptr,0,14,72);
        blue_ptr=&scratch.palette.blue; __asm__("" : "+r"(blue_ptr));
        RetailCall_080e0608(blue_ptr,0,19,72);
        index=0;
        {register u16 *color_address __asm__("r2");
         __asm__("movs %0, #86\n\tadd %0, sp" : "=r"(color_address));
         color_ptr=color_address;}
        __asm__("" : "+r"(color_ptr));
        do {
            RetailCall_080e064c(red_ptr);
            RetailCall_080e064c(green_ptr);
            RetailCall_080e064c(blue_ptr);
            palette[64+index]=red_ptr->value|(green_ptr->value<<5)|(blue_ptr->value<<10);
            index++;
        } while(index<=71);
        {register u32 color_literal __asm__("r1")=0x4dc4;
         register u32 color_value __asm__("r0");
         register u16 *color_destination __asm__("r2");
         __asm__("" : "+r"(color_literal));
         color_value=color_literal; __asm__("" : "+r"(color_value));
         color_destination=color_ptr; __asm__("" : "+r"(color_destination));
         *color_destination=color_value;}
        RetailCall_0814186c(color_ptr,palette+136,0x01000018);
        goto advance_phase;
    }
        }
    case 262:
        work->background=RetailCall_080d3f08(work->background);
        if(work->background!=0) break;
        work->background=RetailCall_080d3e9c((const void*)0x083a33ee,parent);
        store_event=event;
        __asm__("" : "+r"(store_event));
        next_phase=store_event->phase+1;
        goto store_phase;
    case 263:
        work->background=RetailCall_080d3f08(work->background);
        if(work->background!=0) break;
        work->timer=7;
advance_phase:
        event->phase++;
        break;
    case 264:
        if(work->timer!=0) {
            register u32 raw_timer __asm__("r0")=work->timer-1;
            u16 remaining;
            work->timer=raw_timer;
            __asm__("" : "+r"(raw_timer));
            remaining=(u16)raw_timer;
            if(remaining!=0) break;
            RetailCall_080d4d14(work->raster,1);
            work->raster=(void*)(u32)remaining;
            *work->completion=1;
            if(work->timer!=0) break;
        }
        next_phase=2;
        store_event=event;
        __asm__("" : "+r"(store_event));
store_phase:
        store_event->phase=next_phase;
        break;
    }
    return 0;
}
asm(".global RetailCall_08000b20\n.thumb_set RetailCall_08000b20,0x08000b21\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n.global RetailCall_0800bc90\n.thumb_set RetailCall_0800bc90,0x0800bc91\n.global RetailCall_0800bd24\n.thumb_set RetailCall_0800bd24,0x0800bd25\n.global RetailCall_0800bd7c\n.thumb_set RetailCall_0800bd7c,0x0800bd7d\n.global RetailCall_0800bd90\n.thumb_set RetailCall_0800bd90,0x0800bd91\n.global RetailCall_0801ba20\n.thumb_set RetailCall_0801ba20,0x0801ba21\n.global RetailCall_0801bdb0\n.thumb_set RetailCall_0801bdb0,0x0801bdb1\n.global RetailCall_0801cae0\n.thumb_set RetailCall_0801cae0,0x0801cae1\n.global RetailCall_0801dc5c\n.thumb_set RetailCall_0801dc5c,0x0801dc5d\n.global RetailCall_0801e610\n.thumb_set RetailCall_0801e610,0x0801e611\n.global RetailCall_0801e6f0\n.thumb_set RetailCall_0801e6f0,0x0801e6f1\n.global RetailCall_080d3af8\n.thumb_set RetailCall_080d3af8,0x080d3af9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n.global RetailCall_080d3efc\n.thumb_set RetailCall_080d3efc,0x080d3efd\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n.global RetailCall_080d49fc\n.thumb_set RetailCall_080d49fc,0x080d49fd\n.global RetailCall_080d4b64\n.thumb_set RetailCall_080d4b64,0x080d4b65\n.global RetailCall_080d4d14\n.thumb_set RetailCall_080d4d14,0x080d4d15\n.global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n.global RetailCall_080d72c8\n.thumb_set RetailCall_080d72c8,0x080d72c9\n.global RetailCall_080d89d0\n.thumb_set RetailCall_080d89d0,0x080d89d1\n.global RetailCall_080d8aec\n.thumb_set RetailCall_080d8aec,0x080d8aed\n.global RetailCall_080d8b18\n.thumb_set RetailCall_080d8b18,0x080d8b19\n.global RetailCall_080dbed4\n.thumb_set RetailCall_080dbed4,0x080dbed5\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n.global RetailCall_08115a1c\n.thumb_set RetailCall_08115a1c,0x08115a1d\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n");
