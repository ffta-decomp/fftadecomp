/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080210E4.c
 * Original SHA-256: 665bb3ed70afb3eb793f915d958d0c5abde418aa30f7d9323aa333acf0abd921
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u32 source_offset;
    u32 list_offset;
    u8 duration;
    u8 command;
    u8 value;
    u8 setting;
    u16 first;
    u16 second;
    u8 unknown_10;
    u8 flip_x;
    u8 flip_y;
    u8 unknown_13;
} Frame080210E4;

typedef struct Animation080210E4 {
    u32 flags;
    u8 unknown_04[6];
    s16 timer;
    s16 frame_index;
    s16 frame_count;
    u8 setting;
    s8 half_speed_timer;
    u16 tile;
    u16 saved_tile;
    u8 unknown_16[2];
    u16 first;
    u16 second;
    u8 unknown_1C[2];
    u8 changed;
    u8 unknown_1F;
    u32 source_offset;
    u16 tile_count;
    u8 unknown_26[2];
    const u8 *pending_list;
    const u8 *list;
    u8 unknown_30[4];
    const Frame080210E4 *first_frame;
    const Frame080210E4 *current_frame;
} Animation080210E4;

typedef struct Transfer080210E4 {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct Transfer080210E4 *next;
} Transfer080210E4;

typedef struct {
    Transfer080210E4 records[4][4];
    u16 used_tiles[4];
    s16 current;
    s16 count;
    s16 capacity;
    u16 unknown_1CE;
    Animation080210E4 *pending;
} Context080210E4;

extern const u8 *func_08021044(void);
extern const u8 *func_0802104C(void);
extern s32 func_08021064(const u8 *list);
extern void func_08000ADC(Transfer080210E4 *record, const void *source, void *destination, u16 words);
extern u8 data_06010000[];

/* Complete target [0x080210E4, 0x08021290), 428 bytes. */
void func_080210E4(Animation080210E4 *animation, Context080210E4 *context)
{
    switch (animation->current_frame->command) {
    case 1:
        animation->flags &= ~0x18;
        if ((animation->flags & 0x18000) != 0x18000) {
            u32 count;
            animation->list = func_0802104C() + animation->current_frame->list_offset;
            count = func_08021064(animation->list);
            if (animation->source_offset != animation->current_frame->source_offset ||
                animation->tile_count < count) {
                animation->tile_count = count;
                animation->source_offset = animation->current_frame->source_offset;
                if (animation->list != 0) {
                    if ((u16)(context->used_tiles[context->current] + count) > 24) {
                        animation->flags |= 0x100000;
                    } else if (context->count >= context->capacity) {
                        if (context->pending == 0)
                            context->pending = animation;
                        animation->flags |= 0x100000;
                    } else {
                        Transfer080210E4 *record;
                        const u8 *source;
                        animation->flags &= ~0x100000;
                        if (animation->flags & 0x80)
                            animation->tile = animation->saved_tile;
                        animation->flags = (animation->flags & ~0x20080) | 0x90000;
                        animation->flags |= 0x20000;
                        animation->pending_list = animation->list;
                        record = &context->records[context->current][context->count];
                        source = func_08021044() + animation->source_offset;
                        func_08000ADC(record, source, data_06010000 + animation->tile * 32,
                                      (u16)(animation->tile_count << 3));
                        context->count++;
                    }
                }
            }
        } else {
            if (!(animation->flags & 0x8000))
                animation->timer = 0;
        }
        animation->setting = animation->current_frame->setting;
        animation->flags |= animation->current_frame->flip_x ? 8 : 0;
        animation->flags |= animation->current_frame->flip_y ? 16 : 0;
    case 2:
        animation->first = animation->current_frame->first;
        animation->second = animation->current_frame->second;
        break;
    case 3:
        animation->flags ^= 8;
        break;
    case 4:
        animation->flags ^= 16;
        break;
    case 6:
        animation->pending_list = 0;
        break;
    case 8:
        animation->changed = 0x80;
        animation->changed |= animation->current_frame->value;
        break;
    }
}
