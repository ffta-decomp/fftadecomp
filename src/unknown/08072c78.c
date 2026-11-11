/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08072C78.c
 * Original SHA-256: 9a47cd22f5664ca04f9de7e4a4ad6866ea84c4935446b8a86ed7046a76f65238
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct Unit08072C78 {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit08072C78;

typedef struct Entry08072C78 {
    u16 unit;
    u8 unknown_02[18];
} Entry08072C78;

typedef struct Entries08072C78 {
    u8 unknown_00[0x9F0];
    Entry08072C78 entries[0];
} Entries08072C78;

typedef union Control08072C78 {
    struct {
        u8 flags;
        u8 column;
        u8 row;
        u8 unknown_03;
    } bytes;
    struct {
        u8 unknown_0 : 1;
        u8 moving : 1;
        u32 unknown_2 : 30;
    } bits;
} Control08072C78;

typedef struct State08072C78 {
    u8 unknown_00[0x25];
    u8 input_flash;
    u8 unknown_26[0x936];
    u8 item_count;
    u8 unknown_95D[0x13];
    Control08072C78 control;
    u8 unknown_974[4];
    s16 current_x;
    s16 current_y;
    s16 step_x;
    s16 step_y;
    s16 target_x;
    s16 target_y;
    u8 remaining_x;
    u8 remaining_y;
    u8 selected_entry;
    u8 selected_unit;
    u8 previous_unit;
    u8 unknown_989;
    u8 row_count;
    u8 unknown_98B;
    u8 camera_count;
    u8 unknown_98D[3];
    u16 camera_target;
    s16 camera_step;
    s16 camera_position;
    u8 unknown_996[0x1373];
    u8 selected_category;
    u8 unknown_1D0A[2];
    Unit08072C78 *selected_record;
} State08072C78;

extern State08072C78 *data_03002818;
extern Unit08072C78 g_state_02000080[];
extern void func_08141540(u16 sound);

/* Complete target [0x08072C78, 0x08073254), 1500 bytes. */
void func_08072C78(u16 keys, int fast)
{
    u8 last_column = (data_03002818->item_count + 3) % 4;
    u8 last_row = data_03002818->row_count - 1;
    int position;

    if (keys != 0xFFFF) {
        if ((data_03002818->control.bytes.flags & 3) != 1)
            return;

        if (keys & 0x2000) {
            if (data_03002818->control.bytes.column)
                data_03002818->control.bytes.column--;
            else if (data_03002818->control.bytes.row) {
                data_03002818->control.bytes.row--;
                if (data_03002818->control.bytes.row != last_row)
                    data_03002818->control.bytes.column = 3;
                else
                    data_03002818->control.bytes.column = last_column;
            } else {
                data_03002818->control.bytes.row = last_row;
                data_03002818->control.bytes.column = last_column;
            }
        } else if (keys & 0x1000) {
            if (data_03002818->control.bytes.row != last_row) {
                if (data_03002818->control.bytes.column > 2) {
                    data_03002818->control.bytes.row++;
                    data_03002818->control.bytes.column = 0;
                } else
                    data_03002818->control.bytes.column++;
            } else {
                if (data_03002818->control.bytes.column < last_column)
                    data_03002818->control.bytes.column++;
                else {
                    data_03002818->control.bytes.column = 0;
                    data_03002818->control.bytes.row = 0;
                }
            }
        }

        if (!(data_03002818->control.bytes.flags & 2)) {
            if (keys & 0x20) {
                data_03002818->input_flash = 15;
                func_08141540(0x72);
                data_03002818->control.bits.moving = 1;
                if (data_03002818->control.bytes.column)
                    data_03002818->control.bytes.column--;
                else if (data_03002818->control.bytes.row != last_row)
                    data_03002818->control.bytes.column = 3;
                else
                    data_03002818->control.bytes.column = last_column;
            } else if (keys & 0x10) {
                data_03002818->input_flash = 15;
                func_08141540(0x72);
                data_03002818->control.bits.moving = 1;
                if (data_03002818->control.bytes.row != last_row) {
                    if (data_03002818->control.bytes.column <= 2)
                        data_03002818->control.bytes.column++;
                    else
                        data_03002818->control.bytes.column = 0;
                } else {
                    if (data_03002818->control.bytes.column < last_column)
                        data_03002818->control.bytes.column++;
                    else
                        data_03002818->control.bytes.column = 0;
                }
            }

            if (keys & 0x40) {
                data_03002818->input_flash = 15;
                func_08141540(0x72);
                data_03002818->control.bits.moving = 1;
                if (data_03002818->control.bytes.row)
                    data_03002818->control.bytes.row--;
                else {
                    data_03002818->control.bytes.row = last_row;
                    if (data_03002818->control.bytes.column >= last_column)
                        data_03002818->control.bytes.column = last_column;
                }
            } else if (keys & 0x80) {
                data_03002818->input_flash = 15;
                func_08141540(0x72);
                data_03002818->control.bits.moving = 1;
                if (data_03002818->control.bytes.row != last_row) {
                    data_03002818->control.bytes.row++;
                    if (data_03002818->control.bytes.row == last_row &&
                        data_03002818->control.bytes.column >= last_column)
                        data_03002818->control.bytes.column = last_column;
                } else
                    data_03002818->control.bytes.row = 0;
            }
        }
    }

    data_03002818->previous_unit = data_03002818->selected_unit;
    data_03002818->selected_entry = data_03002818->control.bytes.row * 4 + data_03002818->control.bytes.column;
    data_03002818->selected_unit = ((Entries08072C78 *)data_03002818)->entries[
        data_03002818->selected_entry].unit;
    data_03002818->selected_record = &g_state_02000080[data_03002818->selected_unit];
    data_03002818->selected_category = data_03002818->selected_record->flags & 0x1C;
    data_03002818->target_x = data_03002818->control.bytes.column * 48 +
        ((data_03002818->control.bytes.row & 1) ? 24 : 48);
    data_03002818->target_y = data_03002818->control.bytes.row * 40 + 8;

    if (data_03002818->target_x != data_03002818->current_x) {
        data_03002818->step_x = (data_03002818->target_x - data_03002818->current_x) / 8;
        data_03002818->remaining_x = 8;
    } else {
        data_03002818->step_x = 0;
        data_03002818->remaining_x = 0;
    }
    if (data_03002818->target_y != data_03002818->current_y) {
        data_03002818->step_y = (data_03002818->target_y - data_03002818->current_y) / 8;
        data_03002818->remaining_y = 8;
    } else {
        data_03002818->step_y = 0;
        data_03002818->remaining_y = 0;
    }

    position = data_03002818->target_y - data_03002818->camera_position + 44;
    if (!fast) {
        if (position <= 47) {
            data_03002818->control.bits.moving = 1;
            data_03002818->camera_target = data_03002818->target_y - 4;
            position = data_03002818->camera_target;
            if (position != data_03002818->camera_position) {
                position -= data_03002818->camera_position;
                data_03002818->camera_step = position / 12;
                data_03002818->camera_count = 13;
            } else {
                data_03002818->camera_count = 0;
                data_03002818->camera_step = 0;
            }
        } else if (position > 139) {
            data_03002818->control.bits.moving = 1;
            data_03002818->camera_target = data_03002818->target_y - 96;
            position = data_03002818->camera_target;
            if (position != data_03002818->camera_position) {
                position -= data_03002818->camera_position;
                data_03002818->camera_step = position / 12;
                data_03002818->camera_count = 13;
            } else {
                data_03002818->camera_count = 0;
                data_03002818->camera_step = 0;
            }
        }
    } else {
        if (position <= 47) {
            data_03002818->control.bits.moving = 1;
            data_03002818->camera_target = data_03002818->target_y - 4;
            position = data_03002818->camera_target;
            if (position != data_03002818->camera_position) {
                position -= data_03002818->camera_position;
                data_03002818->camera_step = position;
                data_03002818->camera_count = 1;
            } else {
                data_03002818->camera_count = 0;
                data_03002818->camera_step = 0;
            }
        } else if (position > 139) {
            data_03002818->control.bits.moving = 1;
            data_03002818->camera_target = data_03002818->target_y - 96;
            position = data_03002818->camera_target;
            if (position != data_03002818->camera_position) {
                position -= data_03002818->camera_position;
                data_03002818->camera_step = position;
                data_03002818->camera_count = 1;
            } else {
                data_03002818->camera_count = 0;
                data_03002818->camera_step = 0;
            }
        }
    }
}
