#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
extern void ProjectRecord(s32,s32,s32,s16*,s16*) __asm__("0x0801C984");
extern void SubmitRecord(void*,s32,s32,u32,u32,u32,u32,u32,u32,u32,u32) __asm__("0x08001F34");
extern void SubmitAffineRecord(void*,s32,s32,u32,u32,u32,s32,u32,s32,u32,u32,u32,u32) __asm__("0x080018A0");
extern void UpdateRecord(void*) __asm__("0x080A9A48");
extern void ContinueRecord(void*) __asm__("0x080A9C80");
#define H(p,n) (*(u16*)((p)+(n)))
#define S(p,n) (*(s16*)((p)+(n)))
void UpdateBattleRecordViews(u8 *root)
{
    register s32 index __asm__("r5")=0;
    do {
        __asm__("" : "+r"(index));
        {
        u8 *record=(u8*)((u32)(index*396)+(u32)root);
        u8 *flags=record+64;
        u32 active=*flags&1;
        s32 next=index+1;
        if(active) {
            s32 view=0;
            u8 *view_flags=flags;
            __asm__("" : "+r"(view_flags) : "r"(view));
            do {
                if(*view_flags&4) {
                    s32 displacement=view*88;
                    u8 *object_base=record+68;
                    void **object;
                    __asm__("" : "+r"(object_base));
                    object=(void**)(object_base+displacement);
                    if(*object) {
                        u8 *window=record+displacement;
                        s32 input_x=S(window,114);
                        s32 input_y=S(window,116);
                        s32 input_z=S(window,118);
                        u8 *outputs=record+(displacement+68);
                        u32 control;
                        u32 one;
                        u32 working;
                        ProjectRecord(input_x,input_y,input_z,
                                      (s16*)(outputs+52),(s16*)(outputs+54));
                        control=H(window,112);
                        one=1;
                        __asm__ volatile("" : "+r"(one) : "r"(control));
                        working=one&control;
                        if(working==0) {
                            SubmitRecord(*object,S(window,120),S(window,122),0,
                                         working,working,working,working,working,working,working);
                        } else {
                            SubmitAffineRecord(*object,S(window,120),S(window,122),0,0,0,
                                               S(window,126),0,S(window,128),256,256,H(window,124),one);
                        }
                    }
                }
                ++view;
            } while(view<=1);
        }
        index=next;
        }
    } while(index<=12);
    if(!(H(root,5436)&2)) {
        u8 *record=root;
        s32 remaining=12;
        do {
            UpdateRecord(record);
            ContinueRecord(record);
            record+=396;
        } while(--remaining>=0);
    }
}
