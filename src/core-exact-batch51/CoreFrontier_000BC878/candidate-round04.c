#include "interfaces.h"

void InitializeBattleRecordCallbackContext(void *current_node,
                                           const void *selected_record,
                                           u32 state_word, u32 option_word)
    __asm__("CoreFrontier_000BC878");

void InitializeBattleRecordCallbackContext(void *current_node,
                                           const void *selected_record,
                                           u32 state_word, u32 option_word)
{
    u8 *context;
    u8 state_byte;
    u8 option_byte;
    BattleContextClearFunction const *clear_callback_cell;

    state_byte = (u8)state_word;
    option_byte = (u8)option_word;
    clear_callback_cell = &gBattleCallbackContextClear;
    context = (u8 *)0x02010130;

    (*clear_callback_cell)(context, 192);
    InitializeBattleCallbackContextBody(
        context, selected_record, (u32)state_byte, (u32)option_byte);
    *(void **)(context + 116) = current_node;
}
