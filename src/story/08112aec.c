typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u16 *out_x,*out_y;u32 opaque[4];} Event;
typedef struct Rect {u16 x,y,opaque4,opaque6,width,height;} Rect;
typedef struct Work {u8 opaque0[6];u16 child_value;u16 *out_x,*out_y;void *background,*tile_stage,*extra;} Work;
void RetailCall_0801e6f0(u16*,u16*);void RetailCall_0801ba20(s32,s32,u32);u32 RetailCall_0801bdb0(void);
void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*);void RetailCall_0801e610(u8*,u8*);u32 RetailCall_080035a8(u32);
void RetailCall_080dbed4(u32,u32,u32,u32);void RetailCall_0801cae0(Rect*);
void *RetailCall_080d89d0(u32,u8,u8,u8,u32,u32,void*,void*,u32,u8,u8,u8,u8,void*);
void RetailCall_080d8b18(void*,u16*);void *RetailCall_080d8aec(void*);void *RetailCall_080d3e9c(const void*,void*);void *RetailCall_080d3f08(void*);
const u16 *RetailCall_0801dc7c(s32);const u16 *RetailCall_0801dc5c(void);void RetailCall_0801dcb8(const u16*);
void RetailCall_08148318(const u16*,u16*,u16,u8);void *RetailCall_080d3af8(void);void RetailCall_08000b20(void*,u32,void*,u32);
void RetailCall_08115a1c(u32,u32,u32,u16*,u16*);


void RetailCall_080d7220(const void*,u32,u32,u32,u32,u32);void RetailCall_0801db78(void);

extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
s32 RemainingBand43_00112AEC(void *parent,Event *event,Work *work)
{
    u16 camera_x,camera_y;
    u8 layer_a,layer_b;
    switch(event->phase) {
    case 0:
        work->out_x=event->out_x;
        work->out_y=event->out_y;
        break;
    case 1:
        break;
    case 256: {
        register s32 camera_target __asm__("r1");
        RetailCall_0801e6f0(&camera_x,&camera_y);
        camera_target=-192;
        __asm__("" : "+r"(camera_target));
        camera_y=camera_target;
        RetailCall_0801ba20((s16)camera_x,camera_target,8);
        work->extra=RetailCall_080dfd8c((const void*)0x083a3798,1,4,0,parent);
        event->phase++;
        return 0;
    }
    case 257: {
        u32 pending=(u8)RetailCall_0801bdb0();
        if(pending!=0) break;
        RetailCall_080d7220((const void*)0x088f5f08,0,2,0,pending,pending);
        work->background=RetailCall_080d3e9c((const void*)0x0894dbf4,parent);
        RetailCall_0801e610(&layer_a,&layer_b);
        CONTROL&=~RetailCall_080035a8(layer_a);
        CONTROL&=~RetailCall_080035a8(layer_b);
        RetailCall_080dbed4(0,0,0,0);
        {
            Rect rect;
            void *tile;
            register Rect *rect_fields __asm__("r1")=&rect;
            __asm__ volatile("add r0, sp, #48\n\tbl RetailCall_0801cae0" : : : "r0", "r1", "r2", "r3", "r12", "lr", "cc", "memory");
            tile=RetailCall_080d89d0(4,4,0,0,608,310,(void*)0x0600cc00,(void*)0x06007000,1023,
                (u8)((s16)({register Rect *first_rect __asm__("r1"); __asm__ volatile("add %0, sp, #48" : "=r"(first_rect)); first_rect->x;})>>3),
                (u8)((s16)rect_fields->y>>3),(u8)(rect_fields->width>>3),(u8)(rect_fields->height>>3),parent);
            work->tile_stage=tile;
            RetailCall_080d8b18(tile,&work->child_value);
        }
        event->phase++;
        return 0;
    }
    case 258:
        work->background=RetailCall_080d3f08(work->background);
        if(work->background!=0) break;
        work->tile_stage=RetailCall_080d8aec(work->tile_stage);
        if(work->tile_stage!=0) break;
        RetailCall_08115a1c(120,112,work->child_value,work->out_x,work->out_y);
        RetailCall_08000b20(RetailCall_080d3af8(),1023,(void*)0x06007800,1024);
        RetailCall_0801db78();
        event->phase++;
        return 0;
    case 259:
        *(volatile u16*)0x03003860=({register u32 final_word __asm__("r0")=0x65c9; __asm__("" : "+r"(final_word)); final_word;});
        CONTROL&=~RetailCall_080035a8(2);
        event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_08000b20\n.thumb_set RetailCall_08000b20, 0x08000b21\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_0801ba20\n.thumb_set RetailCall_0801ba20, 0x0801ba21\n.global RetailCall_0801bdb0\n.thumb_set RetailCall_0801bdb0, 0x0801bdb1\n.global RetailCall_0801cae0\n.thumb_set RetailCall_0801cae0, 0x0801cae1\n.global RetailCall_0801db78\n.thumb_set RetailCall_0801db78, 0x0801db79\n.global RetailCall_0801e610\n.thumb_set RetailCall_0801e610, 0x0801e611\n.global RetailCall_0801e6f0\n.thumb_set RetailCall_0801e6f0, 0x0801e6f1\n.global RetailCall_080d3af8\n.thumb_set RetailCall_080d3af8, 0x080d3af9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d7220\n.thumb_set RetailCall_080d7220, 0x080d7221\n.global RetailCall_080d89d0\n.thumb_set RetailCall_080d89d0, 0x080d89d1\n.global RetailCall_080d8aec\n.thumb_set RetailCall_080d8aec, 0x080d8aed\n.global RetailCall_080d8b18\n.thumb_set RetailCall_080d8b18, 0x080d8b19\n.global RetailCall_080dbed4\n.thumb_set RetailCall_080dbed4, 0x080dbed5\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n.global RetailCall_08115a1c\n.thumb_set RetailCall_08115a1c, 0x08115a1d\n");
