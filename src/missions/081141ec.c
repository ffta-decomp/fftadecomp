typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void **first_cell,**second_cell;u32 opaque12[4];} Event;
typedef struct Ramp {u16 value; s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u32 unknown0[2];void **first_cell,**second_cell;Ramp first,second;u32 unknown40;} Work;
void *RetailCall_080d5cc0(const void*,u16,u16,u16,u16,u8,u8,u8);
void RetailCall_08011058(void*,s16);
void RetailCall_080e0608(Ramp*,u16,u16,u16);
void RetailCall_080e064c(Ramp*);
u32 RetailCall_080e0690(const Ramp*);
void RetailCall_080107d4(void*,s32,u16,u16);
s32 AdvanceAuthoredDualSpriteEntry(void*,Event*,Work*) asm("RemainingBand43_001141EC");

#define DISPLAY AuthoredDualSpriteDisplay
extern volatile u8 AuthoredDualSpriteDisplay[];
#define CONTROL (*(volatile u16*)AuthoredDualSpriteDisplay)
/* Authored paired-sprite convergence; preserve fresh cells and native window writes. */
s32 AdvanceAuthoredDualSpriteEntry(void *unused,Event *event,Work *work)
{
    switch((s32)event->phase) {
    case 0:
        work->first_cell=event->first_cell;
        work->second_cell=event->second_cell;
        break;
    case 1: break;
    case 256: {
        void *second;
        *work->first_cell=RetailCall_080d5cc0((const void*)0x08506970,0,352,160,930,6,1,0);
        second=RetailCall_080d5cc0((const void*)0x085070e4,0,352,160,650,6,1,0);
        *work->second_cell=second;
        RetailCall_08011058(second,-1);
        RetailCall_080e0608(&work->first,360,240,40);
        RetailCall_080e0608(&work->second,352,240,40);
        DISPLAY[59]=0;
        DISPLAY[58]=120;
        DISPLAY[63]=0;
        DISPLAY[62]=160;
        DISPLAY[66]=47;
        DISPLAY[68]=63;
        {
            register u32 previous_control asm("r1")=CONTROL;
            /* Actual full-word snapshot after six byte writes; dies at this OR. */
            asm("" : "+r"(previous_control));
            {
                u32 control_mask;
                register u32 next_control asm("r0");
                /* Actual mask materialization and merge. These outputs are
                   defined by MOV/LSL/ADD/OR and consumed inside the island or
                   the following C halfword store; no value is fabricated. */
                asm("mov %1, #128\n\t"
                    "lsl %1, %1, #6\n\t"
                    "add %0, %1, #0\n\t"
                    "orr %0, %2"
                    : "=&l"(next_control), "=&l"(control_mask)
                    : "l"(previous_control)
                    : "cc");
                CONTROL=next_control;
            }
        }
        event->phase++;
        break;
    }
    case 257:
        RetailCall_080e064c(&work->first);
        RetailCall_080e064c(&work->second);
        /* Native x carrier is sign-extended; callee stores/compares its low16. */
        RetailCall_080107d4(*work->first_cell,(s16)work->first.value,160,0);
        RetailCall_080107d4(*work->second_cell,(s16)work->second.value,160,0);
        if((u8)RetailCall_080e0690(&work->first)==0) break;
        CONTROL&=0xdfff;
        event->phase++;
        break;
    case 258:
        event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_080107d4\n.thumb_set RetailCall_080107d4,0x080107d5\n");
asm(".global RetailCall_08011058\n.thumb_set RetailCall_08011058,0x08011059\n");
asm(".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n");
asm(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n");
asm(".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n");
asm(".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
asm(".global AuthoredDualSpriteDisplay\n.set AuthoredDualSpriteDisplay,0x03000940\n");
