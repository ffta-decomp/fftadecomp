#include "interfaces.h"

typedef struct {
    u16 result_word_0;
    u16 result_word_2;
    u8 unclassified_bytes_004_031[28];
    void *unit_pointer_at_032;
    u32 mode_word_at_036;
    u16 x_offset_low16_at_040;
    u16 y_offset_low16_at_042;
    u8 unclassified_bytes_044_047[4];
} BattleMovementContextRecord;

typedef struct {
    u16 output_word_0;
    u16 output_word_2;
} HelperOutputWords;

void InitializeBattleMovementContext(void *unit_pointer, u32 mode_word,
                                     s32 x_offset, s32 y_offset)
    __asm__("CoreFrontier_0009D7E4");

void InitializeBattleMovementContext(void *unit_pointer, u32 mode_word,
                                     s32 x_offset, s32 y_offset)
{
    BattleMovementContextRecord *context;
    ClearFunction clear_callback;
    ClearFunction const *clear_callback_cell;
    u16 x_offset_low16;
    u16 y_offset_low16;
    HelperOutputWords output_words;
    u16 *first_output_word;
    /* Retail retains this interior output pointer in callee-saved r5 across the helper. */
    register u16 *second_output_word asm("r5");

    x_offset_low16 = (u16)x_offset;
    y_offset_low16 = (u16)y_offset;
    clear_callback_cell = &gMovementContextClear;
    context = (BattleMovementContextRecord *)0x0200F740;
    clear_callback = *clear_callback_cell;

    ClearRecordThroughCallback((u32)context, 48, (u32)clear_callback);
    context->unit_pointer_at_032 = unit_pointer;
    context->mode_word_at_036 = mode_word;
    context->x_offset_low16_at_040 = x_offset_low16;
    context->y_offset_low16_at_042 = y_offset_low16;
    first_output_word = &output_words.output_word_0;
    second_output_word = &output_words.output_word_2;
    ComputeMovementContextWords(first_output_word, second_output_word);
    context->result_word_0 = *first_output_word;
    context->result_word_2 = *second_output_word;
}
