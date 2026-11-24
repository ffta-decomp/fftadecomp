typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u32 opaque4[6];} Event;
typedef struct Work {u8 source[512],expanded[1024];} Work;
typedef struct AffineSource {s32 texture_x,texture_y;s16 screen_x,screen_y,scale_x,scale_y;u16 angle;} AffineSource;
typedef struct AffineMatrix {s16 pa,pb,pc,pd;s32 dx,dy;} AffineMatrix;
void RetailCall_0814186c(const void*,void*,u32);void RetailCall_08141864(const AffineSource*,AffineMatrix*,u32);
void *RetailCall_080d3af8(void);void RetailCall_08000a98(void*,const void*,void*,u32);void RetailCall_0801db78(void);u32 RetailCall_08003620(u32);
u32 RetailCall_08003a74(const void*);u32 RetailCall_08003a80(const void*);void RetailCall_080034b8(u16,u32);void RetailCall_080032f8(const AffineMatrix*,u32);void RetailCall_0801e610(u8*,u8*);u32 RetailCall_080035d0(u32);
s32 RemainingBand43_001102F4(void*,Event*,Work*);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
typedef char SourceMustBe20[sizeof(AffineSource)==20?1:-1];
typedef char MatrixMustBe16[sizeof(AffineMatrix)==16?1:-1];
typedef char WorkMustBe1536[sizeof(Work)==1536?1:-1];
s32 RemainingBand43_001102F4(void *parent,Event *event,Work *work)
{
    volatile u16 fill;
    AffineSource affine;
    AffineMatrix matrix;
    u8 layer_a,layer_b;
    u16 phase;
    register u32 next_phase asm("r0");
    register Event *event_root asm("r6")=event;
    register Work *work_root asm("r5")=work;
    asm("" : "+r"(event_root), "+r"(work_root));
    phase=event_root->phase;
    switch(phase) {
    case 0:
        fill=0xffff;
        RetailCall_0814186c((const void*)&fill,work_root->expanded,0x01000200);
        break;
    case 1:
        break;
    case 256:
        RetailCall_0801db78();
        *(volatile u16*)0x03003860=0;
        RetailCall_08000a98(RetailCall_080d3af8(),(const void*)0x06005000,work_root,phase);
        next_phase=event_root->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    case 257: {
        u32 i=0;
        do {
            RetailCall_0814186c(work_root->source+(i<<5),work_root->expanded+(i<<6),6);
            i=(u8)(i+1);
        } while(i<=15);
        next_phase=event_root->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    }
    case 258: {
        void *slot=RetailCall_080d3af8();
        register u32 count asm("r4");
        const void *data;
        count=512;
        asm("" : "+r"(count));
        data=(u8*)work_root+count;
        RetailCall_08000a98(slot,data,(void*)0x06005000,count);
        RetailCall_08000a98(RetailCall_080d3af8(),data,(void*)0x06005400,count);
        next_phase=event_root->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    }
    case 259: {
        register u32 character asm("r4");
        register u32 screen asm("r0");
        u32 masks;
        register u32 blend asm("r8");
        {
            void *slot=RetailCall_080d3af8();
            register u32 count asm("r4");
            const void *data;
            count=512;
            asm("" : "+r"(count));
            data=(u8*)work_root+count;
            RetailCall_08000a98(slot,data,(void*)0x06005800,count);
            RetailCall_08000a98(RetailCall_080d3af8(),data,(void*)0x06005c00,count);
        }
        RetailCall_08003620(1);
        character=RetailCall_08003a74((const void*)0x06005000);
        screen=RetailCall_08003a80((const void*)0x0600c000);
        asm volatile("mov r2, #128\n\tlsl r2, r2, #8\n\tadd r1, r2, #0\n\torr %0, r1\n\torr %0, %1\n\tmov r1, #128\n\torr %0, r1"
                     : "+l"(screen) : "l"(character) : "r1", "r2", "cc");
        RetailCall_080034b8((u16)screen,2);
        affine.texture_x=12288;
        affine.texture_y=12288;
        affine.screen_x=120;
        affine.screen_y=80;
        affine.scale_x=256;
        affine.scale_y=256;
        affine.angle=0;
        RetailCall_08141864(&affine,&matrix,1);
        RetailCall_080032f8(&matrix,2);
        display_shadow[74]=132;
        {
            u8 discarded=display_shadow[78];
            (void)discarded;
            blend=16;
            asm("" : "+r"(blend));
            ((u8 *)display_shadow)[78]=blend;
        }
        RetailCall_0801e610(&layer_a,&layer_b);
        masks=RetailCall_080035d0(layer_a);
        masks|=RetailCall_080035d0(layer_b);
        display_shadow[66]=63&~masks;
        asm("" : "+r"(blend));
        {
            register u8 *byte_address asm("r0")=(u8 *)display_shadow+68;
            register u32 stored_value asm("r1");
            asm("" : "+r"(byte_address));
            (void)*(volatile u8 *)byte_address;
            stored_value=blend;
            asm("" : "+r"(stored_value));
            *byte_address=stored_value;
        }
        next_phase=event_root->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    }
    case 260:
        next_phase=2;
    store_phase:
        event_root->phase=next_phase;
        break;
    }
    return 0;
}
asm(".global RetailCall_08000a98\n.thumb_set RetailCall_08000a98, 0x08000a99\n.global RetailCall_080032f8\n.thumb_set RetailCall_080032f8, 0x080032f9\n.global RetailCall_080034b8\n.thumb_set RetailCall_080034b8, 0x080034b9\n.global RetailCall_080035d0\n.thumb_set RetailCall_080035d0, 0x080035d1\n.global RetailCall_08003620\n.thumb_set RetailCall_08003620, 0x08003621\n.global RetailCall_08003a74\n.thumb_set RetailCall_08003a74, 0x08003a75\n.global RetailCall_08003a80\n.thumb_set RetailCall_08003a80, 0x08003a81\n.global RetailCall_0801db78\n.thumb_set RetailCall_0801db78, 0x0801db79\n.global RetailCall_0801e610\n.thumb_set RetailCall_0801e610, 0x0801e611\n.global RetailCall_080d3af8\n.thumb_set RetailCall_080d3af8, 0x080d3af9\n.global RetailCall_08141864\n.thumb_set RetailCall_08141864, 0x08141865\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c, 0x0814186d\n");
