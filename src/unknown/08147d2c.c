typedef unsigned short u16;
typedef unsigned int u32;
struct RangeTransition;
struct SavedRangeRow { u16 value; unsigned char remaining[10]; };
extern struct SavedRangeRow gSavedRangeRows[512];
extern struct RangeTransition *BeginRangeTransition(u32 first, u32 last,
                                                   u32 duration, u32 mode);
__asm__(".set gSavedRangeRows,0x03003e68\n"
        ".thumb_set BeginRangeTransition,0x08146e55");
struct RangeTransition *BeginSavedRangeTransition(u32 first_word, u32 count_word,
                                                  u32 duration_word,
                                                  const u16 *saved_values)
    __asm__("CoreFrontier_00147D2C");
struct RangeTransition *BeginSavedRangeTransition(u32 first_word, u32 count_word,
                                                  u32 duration_word,
                                                  const u16 *saved_values)
{
    u16 first = first_word;
    u16 count = count_word;
    u16 duration = duration_word;
    u16 last = first + count - 1;
    u16 current;
    u16 source_index;
    if (last > 511)
        last = 511;
    current = first;
    source_index = 0;
    /* Keep the original wrapped count/end and per-element alias-visible copy. */
    for (; current <= last; current++, source_index++)
        gSavedRangeRows[current].value = saved_values[source_index];
    return BeginRangeTransition(first, last, duration, 0);
}
