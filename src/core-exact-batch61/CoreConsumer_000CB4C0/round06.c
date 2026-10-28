#include "../../../src/job_model_c05/job_model_c05.h"

void ClearUnitEquipmentForJobChangeBody(u8 *unit)
{
    int slot_index;

    for (slot_index = 0; slot_index <= 4; ++slot_index) {
        ReplaceEquipmentSlotForScan((JobChangeEquipmentView *)unit,
                                    0,
                                    (u8)slot_index);
    }
}

/* Emit the original two zero bytes after the 30-byte instruction body. */
__asm__(".byte 0, 0");
