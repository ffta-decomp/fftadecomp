#include "interfaces.h"
/* Filter input actors into observed 808-byte groups; field roles remain provisional. */
void CoreRegion30_000C1B8C(struct Actor *source, struct TargetGroups *output,
    struct Actor **cursor, s32 count)
{
    u32 ability;
    if ((u8)HasStatus12(source->unit) != 0)
        ability = 14;
    else
        ability = (u8)ReadSlotB(source->unit);
    output->count = 0;
    if (count > 0) {
        u16 *output_count;
        s32 remaining;
        /* Native C1BC8..BCC regenerates the count address before copying the
         * countdown. The original terminal literal is owned by this complete
         * 172-byte envelope at entry+168; whole-range comparison guards it.
         * Low outputs and the high-base ADD form impose no hard-register name. */
        __asm__("ldr %0, CoreRegion30_000C1B8C + 168\n\t"
                "add %0, %2\n\t"
                "add %1, %3, #0"
                : "=&l"(output_count), "=l"(remaining)
                : "h"(output), "l"(count)
                : "cc");
        do {
        s32 source_state = HasStatus15(source->unit);
        s32 target_state = HasStatus15((*cursor)->unit);
        if ((u8)source_state != (u8)target_state && ability != 14 &&
            (u8)HasE94((*cursor)->unit) != 0)
            goto next;
        if ((u8)HasED6((*cursor)->unit) == 0) {
            output->groups[*output_count].actor = *cursor;
            (*output_count)++;
        }
next:
        cursor++;
        remaining--;
        } while (remaining != 0);
    }
}
