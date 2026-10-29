typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *volatile JobMenuOwner;
extern void *JobMenuResources[];
extern const u8 JobRowFrames[];
extern const u8 JobRowGraphics[];
extern void PrepareJobRow(void *, u16);
extern s32 SignedRemainder(s32, s32);
extern void SortJobRowKeys(u16 *, s32, s32);
extern void ConfigureJobRow(void *, u16, u32, u8, u8, u32, u32,
                            const u8 *, const u8 *, u16, s8);
__asm__(".global JobMenuOwner\n.set JobMenuOwner,0x03002818\n"
        ".global JobMenuResources\n.set JobMenuResources,0x03000e30\n"
        ".global JobRowFrames\n.set JobRowFrames,0x0894eae0\n"
        ".global JobRowGraphics\n.set JobRowGraphics,0x0894eb6c\n"
        ".global PrepareJobRow\n.thumb_set PrepareJobRow,0x0804c7a1\n"
        ".global SignedRemainder\n.thumb_set SignedRemainder,0x08142951\n"
        ".global SortJobRowKeys\n.thumb_set SortJobRowKeys,0x0808a159\n"
        ".global ConfigureJobRow\n.thumb_set ConfigureJobRow,0x0804c525");
#define WORD_AT(p,o) (*(s32 *)((u8 *)(p)+(o)))
u32 UpdateJobRowsAndSlide(void) __asm__("CoreScene34_00085820");
u32 UpdateJobRowsAndSlide(void)
{
    u16 keys[12]; /* Real24B local buffer at originalSP28;28B outgoing words. */
    register s32 index __asm__("r6");
    index = 0;
    while (index < WORD_AT(JobMenuOwner, 0x1270)) {
        PrepareJobRow(JobMenuResources[1], (u16)index);
        index++;
    }
    index = 0;
    {
        register u8 *volatile *cell_working __asm__("r1") = &JobMenuOwner;
        register s32 initial_count __asm__("r0");
        register u32 count_offset __asm__("r2");
        register u8 *count_owner __asm__("r0");
        register u8 *volatile *owner_cell __asm__("r8");
        __asm__("" : "+r"(cell_working));
        count_owner = *cell_working;
        __asm__("" : "+r"(count_owner));
        count_offset = 0x1270;
        __asm__("" : "+r"(count_offset));
        initial_count = WORD_AT(count_owner, count_offset);
        __asm__("" : "+r"(initial_count));
        owner_cell = cell_working;
        __asm__("" : "+r"(owner_cell) : "r"(initial_count));
        if (index < initial_count) {
            u16 *key = keys;
            do {
                u8 *owner = *cell_working;
                s32 count;
                register u8 *count_address __asm__("r1");
                register s32 numerator __asm__("r0") = index + owner[0x1275];
                register s32 row __asm__("r1");
                register s32 phase __asm__("r1");
                register u32 y __asm__("r2");
                /* Capture argument0 before loading the actual denominator. */
                __asm__("" : "+r"(numerator));
                count_address = owner + count_offset;
                __asm__("" : "+r"(count_address));
                count = WORD_AT(count_address, 0);
                row = SignedRemainder(numerator, count);
                __asm__("" : "+r"(row));
                {
                    register u8 *wrap_slide __asm__("r2");
                    register u32 last_row_offset __asm__("r0");
                    if (row == 0) {
                        wrap_slide = owner + 0x1276;
                        __asm__("" : "+r"(wrap_slide));
                        if (*(s8 *)wrap_slide < 0)
                            goto key_wrapped;
                    }
                    phase = row * 8 + *(s8 *)(owner + 0x1276);
                    goto key_phase_ready;
                key_wrapped:
                    last_row_offset = ((u32)count - 1) << 3;
                    __asm__("" : "+r"(last_row_offset));
                    phase = *(s8 *)wrap_slide;
                    __asm__("" : "+r"(phase));
                    phase = (s32)((u32)phase + last_row_offset);
                    __asm__("" : "+r"(phase));
                    phase = (s32)((u32)phase + 7);
                key_phase_ready:
                    ;
                }
                /* Original phase becomes a wrapping full-word byte offset in R1. */
                phase = (s32)((u32)phase << 3);
                __asm__("" : "+r"(phase));
                {
                    register u8 *y_field_base __asm__("r0") = owner + 0x13E8;
                    __asm__("" : "+r"(y_field_base));
                    y = WORD_AT(y_field_base, phase);
                    __asm__("" : "+r"(y));
                }
                {
                    register u32 mask __asm__("r0") = 255;
                    __asm__("" : "+r"(mask));
                    y ^= mask;
                    __asm__("" : "+r"(y));
                }
                {
                    register u32 packed_key __asm__("r0") = y << 8;
                    __asm__("" : "+r"(packed_key));
                    *key = packed_key | (u32)index;
                }
                key++;
                index++;
                /* R1 was call-clobbered; redefine it from the preserved cell. */
                cell_working = owner_cell;
                __asm__("" : "+r"(cell_working));
                count_owner = *cell_working;
                __asm__("" : "+r"(count_owner));
                count_offset = 0x1270;
                __asm__("" : "+r"(count_offset));
            } while (index < WORD_AT(count_owner, count_offset));
        }
    }
    SortJobRowKeys(keys, 0, WORD_AT(JobMenuOwner, 0x1270) - 1);
    index = 0;
    __asm__("" : "+r"(index));
    {
        register s32 draw_ordinal __asm__("r8") = index;
        /* R8 changes role only after the key-cell pointer dies and sorting returns. */
        __asm__("" : "+r"(draw_ordinal));
    while (draw_ordinal < WORD_AT(JobMenuOwner, 0x1270)) {
        register s32 ordinal_working __asm__("r1") = draw_ordinal;
        register s32 selected __asm__("r6");
        register u32 key_byte_offset __asm__("r0");
        register u8 *draw_field_address __asm__("r0");
        register u8 *owner __asm__("r4");
        register s32 count __asm__("r5");
        register u32 draw_count_offset __asm__("r2");
        register u32 cursor_offset __asm__("r1");
        s32 mirror;
        register s32 row __asm__("r1");
        register s32 phase __asm__("r1");
        s32 x, y;
        /* The low ordinal is consumed by the key address before selected exists. */
        __asm__("" : "+r"(ordinal_working));
        key_byte_offset = (u32)ordinal_working << 1;
        __asm__("" : "+r"(key_byte_offset));
        selected = ((u8 *)keys)[key_byte_offset];
        /* These three captured values really survive both remainder calls. */
        __asm__("" : "+r"(selected));
        owner = JobMenuOwner;
        __asm__("" : "+r"(owner));
        draw_count_offset = 0x1270;
        __asm__("" : "+r"(draw_count_offset));
        draw_field_address = owner + draw_count_offset;
        __asm__("" : "+r"(draw_field_address));
        count = WORD_AT(draw_field_address, 0);
        __asm__("" : "+r"(count));
        mirror = SignedRemainder(count - selected, count);
        cursor_offset = 0x1275;
        __asm__("" : "+r"(cursor_offset));
        draw_field_address = owner + cursor_offset;
        __asm__("" : "+r"(draw_field_address));
        row = SignedRemainder(selected + *draw_field_address, count);
        __asm__("" : "+r"(row));
        {
            register u8 *wrap_slide __asm__("r2");
            register u32 last_row_offset __asm__("r0");
            if (row == 0) {
                wrap_slide = owner + 0x1276;
                __asm__("" : "+r"(wrap_slide));
                if (*(s8 *)wrap_slide < 0)
                    goto draw_wrapped;
            }
            phase = row * 8 + *(s8 *)(owner + 0x1276);
            goto draw_phase_ready;
        draw_wrapped:
            last_row_offset = ((u32)count - 1) << 3;
            __asm__("" : "+r"(last_row_offset));
            phase = *(s8 *)wrap_slide;
            __asm__("" : "+r"(phase));
            phase = (s32)((u32)phase + last_row_offset);
                    __asm__("" : "+r"(phase));
                    phase = (s32)((u32)phase + 7);
        draw_phase_ready:
            ;
        }
        phase = (s32)((u32)phase << 3);
        __asm__("" : "+r"(phase));
        {
            register u32 field_offset __asm__("r2") = 0x13E4;
            register u8 *field_base __asm__("r0");
            /* Original field address is formed before adding the row byte offset. */
            __asm__("" : "+r"(field_offset));
            field_base = owner + field_offset;
            __asm__("" : "+r"(field_base));
            x = WORD_AT(field_base, phase);
            field_offset += 4;
            __asm__("" : "+r"(field_offset));
            field_base = owner + field_offset;
            __asm__("" : "+r"(field_base));
            y = WORD_AT(field_base, phase);
        }
        if ((u32)(y - 1) <= 190 && x > -16 && x <= 219) {
            u32 tile;
            u32 style;
            register u32 rows_address __asm__("r1");
            u32 selected_address;
            if (selected <= 7)
                tile = selected * 20 + 128;
            else
                tile = (selected - 8) * 20 + 664;
            rows_address = (u32)JobMenuOwner;
            selected_address = rows_address + (u32)selected * 28u;
            style = *(u8 *)(selected_address + 0x1289);
            /* Root becomes the actual mirror-record partial base only after that read. */
            rows_address += (u32)mirror * 28u;
            __asm__("" : "+r"(rows_address));
            if (!*(u8 *)(rows_address + 0x1284))
                style += 3;
            ConfigureJobRow(JobMenuResources[1], (u16)draw_ordinal, 0, (u8)x, (u8)y,
                            0, 1, JobRowFrames, JobRowGraphics, (u16)tile, (s8)style);
        }
        draw_ordinal++;
    }
    }
    {
        register u8 *volatile *slide_cell __asm__("r3") = &JobMenuOwner;
        register u32 slide_offset __asm__("r4");
        register u8 *slide_owner __asm__("r0");
        register u8 *slide __asm__("r2");
        register u32 raw_slide __asm__("r0");
        register s32 signed_slide __asm__("r1");
        /* Both original address components remain live to the fresh-root clear. */
        __asm__("" : "+r"(slide_cell));
        slide_owner = *slide_cell;
        __asm__("" : "+r"(slide_owner));
        slide_offset = 0x1276;
        slide = slide_owner + slide_offset;
        __asm__("" : "+r"(slide_offset), "+r"(slide));
        raw_slide = *slide;
        __asm__("" : "+r"(raw_slide) : : "memory");
        signed_slide = *(s8 *)slide;
        __asm__("" : "+r"(signed_slide));
        if (!signed_slide)
            goto inactive;
        if (signed_slide > 0) {
            raw_slide++;
            *slide = raw_slide;
            if ((s8)raw_slide <= 8)
                goto active;
        clear_slide:
            (*slide_cell)[slide_offset] = 0;
            goto inactive;
        } else {
            raw_slide--;
            *slide = raw_slide;
            if ((s8)raw_slide < -8)
                goto clear_slide;
        }
    active:
        return 1;
    inactive:
        return 0;
    }
}
