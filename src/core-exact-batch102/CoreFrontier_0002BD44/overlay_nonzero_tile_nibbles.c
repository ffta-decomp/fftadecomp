typedef unsigned int u32;
void CoreFrontier_0002BD44(u32 *destination, const u32 *source)
{
    register const u32 *input __asm__("r3") = source;
    u32 *output = destination;
    register int word __asm__("r0") = 0;
    /* Native outer-loop address and counter lifetimes begin with real inputs. */
    __asm__("" : "+r"(input), "+r"(output), "+r"(word));
    do {
        register u32 pixels __asm__("r5") = *input++;
        register u32 overwrite __asm__("r4") = 0;
        register u32 nibble __asm__("r1") = 15;
        register u32 *next __asm__("r6") = output;
        register u32 previous __asm__("r2") = *next++;
        register const u32 *saved_input __asm__("ip") = input;
        register int saved_word __asm__("r8") = word + 1;
        register int position __asm__("r3") = 7;
        /* Preserve loaded words and the postincrement cursor across nibble work. */
        __asm__("" : "+r"(pixels), "+r"(overwrite), "+r"(nibble), "+r"(next), "+r"(previous));
        /* The source cursor and incremented count survive the inner r3 loop. */
        __asm__("" : "+r"(saved_input), "+r"(saved_word), "+r"(position));
        do {
            if (pixels & nibble)
                overwrite |= nibble;
            --position;
            nibble <<= 4;
        } while (position >= 0);
        *output = (previous & ~overwrite) | pixels;
        input = saved_input;
        output = next;
        word = saved_word;
    } while (word <= 7);
    /* agbcc must preserve the native callee-saved r7 used by the bound cursor. */
    __asm__("" : : : "r7");
}
