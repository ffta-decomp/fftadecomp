/* Contributed by gg; original source and attribution follow. */
/* TaskConstructor45_0002BAF8
   entry 0x0802BAF8, 120 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*CopyBytes)(void *, const void *, u32);
extern CopyBytes PairBlockCopyCell;
void f_target(u8 *destination_arg, const u8 *source_arg)
{
    register u8 *destination asm("sl") = destination_arg;
    register const u8 *source asm("r9") = source_arg;
    int group = 0;
    do {
        int saved_group;
        const u8 *second_source;
        u8 *second_destination;
        const u8 *first_source;
        u8 *first_destination;
        register int column asm("r8");
        ++group;
        /* The original spills this initialized snapshot across copy calls.
           The preceding counter value is dead until reloaded at the latch. */
        saved_group = group;
        asm("" : "+m" (saved_group));
        second_source = source + 32;
        second_destination = destination + 128;
        first_source = source;
        first_destination = destination;
        column = 3;
        do {
            register CopyBytes *first_cell asm("r1") = &PairBlockCopyCell;
            register CopyBytes first_callback asm("r3");
            register int step asm("r1");
            asm("" : "+r" (first_cell));
            first_callback = *first_cell;
            asm("" : "+r" (first_callback));
            first_callback(first_destination, first_source, 32);
            PairBlockCopyCell(second_destination, second_source, 32);
            second_source += 64;
            second_destination += 32;
            first_source += 64;
            first_destination += 32;
            step = -1;
            asm("" : "+r" (step));
            column += step;
        } while (column >= 0);
        source += 256;
        destination += 256;
        group = saved_group;
    } while (group <= 2);
}
asm(".set PairBlockCopyCell,0x0836d4bc\n.thumb_set _call_via_r3,0x08142251\n");
