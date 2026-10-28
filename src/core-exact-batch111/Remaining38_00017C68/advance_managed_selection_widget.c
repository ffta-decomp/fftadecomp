typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct SelectionWidget {
    void *callback;
    void *data;
    u16 animated_value;
    u16 unknown_0a;
    u16 counter;
    u16 unknown_0e;
    u8 flags;
    u8 unknown_11;
    u8 phase;
    u8 unknown_13;
};

extern const u8 SelectionPhaseDurations[];
extern const u8 SelectionPhaseSteps[];
extern u32 SelectionWidgetUnsignedRemainder(u32, u32);
extern void DispatchSelectionWidget(struct SelectionWidget *, void *);

/* The broader role of halfword8 is tentative; retain its observed arithmetic. */
void AdvanceManagedSelectionWidget(struct SelectionWidget *widget)
{
    if (widget->callback != 0) {
        u32 flags;
        u32 animation_enabled;
        {
            register u32 initial_flags asm("r1") = widget->flags;
            register u32 initial_mask asm("r0") = initial_flags & 2;
            /* Preserve the original mask/capture boundary with initialized values. */
            asm("" : "+r" (initial_flags), "+r" (initial_mask));
            flags = initial_flags;
            animation_enabled = initial_mask;
        }
        if (animation_enabled != 0) {
            if ((flags & 4) != 0) {
                if (widget->counter++ >= (u32)SelectionPhaseDurations[widget->phase]) {
                    if ((u32)++widget->phase > 2)
                        widget->phase = 0;
                    widget->counter = 0;
                }
            } else {
                u32 next_value;
                if ((flags & 8) != 0) {
                    const s8 *steps;
                    u8 phase;
                    s32 step;
                    {
                        register const s8 *base asm("r2") = (const s8 *)SelectionPhaseSteps;
                        /* Only the initial base capture has a fixed register. */
                        asm("" : "+r" (base));
                        steps = base;
                    }
                    phase = widget->phase++;
                    {
                        register u32 address asm("r0") = phase;
                        /* Keep index first in the original address addition. */
                        asm("" : "+r" (address));
                        address += (u32)steps;
                        asm("" : "+r" (address));
                        step = *(const s8 *)address;
                    }
                    next_value = widget->animated_value - step;
                } else {
                    const u8 *steps;
                    u8 phase;
                    u32 positioned_step;
                    {
                        register const u8 *base asm("r2") = SelectionPhaseSteps;
                        asm("" : "+r" (base));
                        steps = base;
                    }
                    phase = widget->phase++;
                    {
                        register u32 address asm("r0") = phase;
                        asm("" : "+r" (address));
                        address += (u32)steps;
                        asm("" : "+r" (address));
                        positioned_step = (u32)*(const u8 *)address << 24;
                    }
                    /* Keep the unsigned load separate from the sign extension. */
                    asm("" : "+r" (positioned_step));
                    next_value = widget->animated_value + ((s32)positioned_step >> 24);
                }
                widget->animated_value = next_value;
                widget->phase = SelectionWidgetUnsignedRemainder(widget->phase, 48);
            }
        }
        {
            u32 callback_enabled = flags & 1;
            /* Keep the captured flags live through the final nondestructive test. */
            asm("" : "+r" (flags), "+r" (callback_enabled));
            if (callback_enabled != 0)
                DispatchSelectionWidget(widget, widget->callback);
        }
    }
}

asm(".global SelectionPhaseDurations\n.set SelectionPhaseDurations, 0x0836d674\n"
    ".global SelectionPhaseSteps\n.set SelectionPhaseSteps, 0x0836d644\n"
    ".global SelectionWidgetUnsignedRemainder\n"
    ".thumb_set SelectionWidgetUnsignedRemainder, 0x08142b29\n"
    ".global DispatchSelectionWidget\n.thumb_set DispatchSelectionWidget, 0x08142249\n");
