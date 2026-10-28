typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern void LayoutGlyph(void *, u32);
extern void AdjustText(void *, s32);
extern void PlayTextSound(u32, u32);
u32 AdvanceSceneEncodedText(u8 *) asm("Remaining47_00128B4C");
u32 AdvanceSceneEncodedText(u8 *context)
{
    register u8 *delay asm("r1") = context + 934;
    register u32 wait asm("r6");
    register u32 timer_input asm("r0");
    u8 **stream;
    register u32 stream_offset asm("r3");
    register u8 *current asm("r1");
    register u32 token asm("r2");
    asm("" : "+r"(delay));
    timer_input = *delay;
    asm("" : "+r"(timer_input));
    wait = timer_input;
    asm("" : "+r"(wait));
    if (wait != 0) {
        *delay = timer_input - 1;
        return 0;
    }
    *delay = 10;
    stream_offset = 704;
    asm("" : "+r"(stream_offset));
    stream = (u8 **)(context + stream_offset);
    current = *stream;
    asm("" : "+r"(current));
    token = current[0];
    asm("" : "+r"(token));
    if (token == 0)
        return 1;
    if (token & 128) {
        u16 *count;
        u16 old;
        register u32 sound_offset asm("r3");
        register void *glyph_context asm("r0");
        register u32 glyph asm("r1");
        register u32 mask asm("r3");
        register u32 working_mask asm("r2");
        glyph_context = context + 40;
        asm("" : "+r"(glyph_context));
        glyph = (token << 8) | current[1];
        asm("" : "+r"(glyph));
        mask = 0x7fff;
        asm("" : "+r"(mask));
        working_mask = mask;
        asm("" : "+r"(working_mask));
        LayoutGlyph(glyph_context, glyph & working_mask);
        *stream = *stream + 2;
        count = (u16 *)(context + 982);
        old = *count;
        *count = old + 1;
        sound_offset = 0x1dd;
        asm("" : "+r"(sound_offset));
        PlayTextSound(1, (u16)(old + sound_offset));
        if (*count > 2)
            *count = wait;
        return 0;
    }
    if (token == 64) {
        s32 code = current[1];
        switch (code) {
        case 115:
            AdjustText(context + 40, 6);
            *stream = *stream + 2;
            break;
        case 60:
        case 62: {
            register u8 **reloaded_stream asm("r4") = (u8 **)(context + 704);
            u8 *item;
            s16 amount;
            asm("" : "+r"(reloaded_stream));
            item = *reloaded_stream;
            amount = item[2];
            if (item[1] == 60)
                amount = -amount;
            AdjustText(context + 40, amount);
            *reloaded_stream = *reloaded_stream + 3;
            break;
        }
        }
        {
            register u32 reset_offset asm("r3") = 934;
            register u8 *reset_delay asm("r1");
            asm("" : "+r"(reset_offset));
            reset_delay = context + reset_offset;
            asm("" : "+r"(reset_delay));
            *reset_delay = 0;
        }
        AdvanceSceneEncodedText(context);
    }
    return 0;
}
asm(".thumb_set LayoutGlyph,0x0801360d\n.thumb_set AdjustText,0x08013729\n.thumb_set PlayTextSound,0x08141571\n");
