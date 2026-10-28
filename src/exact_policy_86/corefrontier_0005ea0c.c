/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionController {
    u8 unknown00[0x1199];
    u8 phase, state, unknown119b, fee_timer;
    u8 unknown119d[7];
    u16 fee_amount;
};
struct CurrencyState { u8 unknown00[0x1f64]; u32 currency; };
struct NumericFeedbackContext { u8 unknown00[20]; u16 *tiles; };
typedef char FeeTimerOffset[(u32)&((struct MissionController*)0)->fee_timer==0x119c?1:-1];
typedef char FeeAmountOffset[(u32)&((struct MissionController*)0)->fee_amount==0x11a4?1:-1];
typedef char CurrencyOffset[(u32)&((struct CurrencyState*)0)->currency==0x1f64?1:-1];
extern struct MissionController *gMissionController;
extern struct CurrencyState gMissionCurrencyState;
extern struct NumericFeedbackContext gMissionNumericFeedback;
/* The original caller passes full registers. The existing ASM helper consumes
 * low16 of column/row; it does not require caller extension of these constants. */
extern void BeginCurrencyFeedback(s32,struct NumericFeedbackContext*,void*,u32,u32);
extern void CloseCurrencyFeedback(void);
__asm__(".global gMissionController\n.set gMissionController,0x0200f448");
__asm__(".global gMissionCurrencyState\n.set gMissionCurrencyState,0x02000000");
__asm__(".global gMissionNumericFeedback\n.set gMissionNumericFeedback,0x030008b0");
__asm__(".global BeginCurrencyFeedback\n.thumb_set BeginCurrencyFeedback,0x08029f19");
__asm__(".global CloseCurrencyFeedback\n.thumb_set CloseCurrencyFeedback,0x08013365");

void AdvanceMissionFeeCommit(void);
void AdvanceMissionFeeCommit(void)
{
    if (++gMissionController->fee_timer == 1) {
        BeginCurrencyFeedback(-gMissionController->fee_amount,
            &gMissionNumericFeedback, 0, 20, 17);
    } else if (gMissionController->fee_timer > 10) {
        gMissionController->fee_timer = 0;
        gMissionCurrencyState.currency -= gMissionController->fee_amount;
        CloseCurrencyFeedback();
        gMissionController->state = 17;
        gMissionController->phase = 2;
    }
}
