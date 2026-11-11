#include "graphics/interfaces/0810ef0c_signed_ramp_start_view.h"

/* A fixed, game-authored sequence; the specific scene/ability name is unknown.
 * The task work is allocated as 488 bytes by its original registering caller.
 * Graphics/task/tween backends retain their existing implementations. */
typedef char WorkSizeIs488[sizeof(struct FixedSceneWork) == 488 ? 1 : -1];
typedef char RampSizeIs12[sizeof(struct SceneRamp) == 12 ? 1 : -1];
typedef char EventSizeIs28[sizeof(struct SceneEvent) == 28 ? 1 : -1];

#define SH8(n) (*(volatile u8 *)(0x03000940u + (n)))
#define SH16(n) (*(volatile u16 *)(0x03000940u + (n)))
#define STORE_SHADOW_BYTE(n,v) do { (void)SH8(n); SH8(n) = (v); } while (0)
#define STORE_BASE_BYTE(base,n,v) do { (void)(base)[n]; (base)[n] = (v); } while (0)
#define ADVANCE_SCROLL() do { \
    s16 *scroll_x = &work->scroll_x; \
    s16 *scroll_y = &work->scroll_y; \
    asm("" : "+r" (scroll_x), "+r" (scroll_y)); \
    --work->scroll_phase; \
    if (work->scroll_phase == 0) { \
        work->scroll_phase = 1; \
        --*scroll_x; \
        ++*scroll_y; \
        RetailCall_080d7468((const void *)0x088f5d1c, 2, \
                            *scroll_x, *scroll_y); \
    } \
} while (0)

u32 RemainingBand43_0010EF0C(TaskNode *parent, struct SceneEvent *event,
                            struct FixedSceneWork *work)
{
    struct SceneBounds bounds;
    u32 child_event[7];
    u16 position_offsets[5];
    u16 sprite_x, sprite_y, sprite_z;
    s32 state = event->state;

    switch (state) {
    case 0:
        work->event_payload = event->payload;
        RetailCall_0801cae0(&bounds);
        work->center_x = (bounds.left + (bounds.width >> 1)) >> 2;
        work->center_y = (bounds.top + (bounds.height >> 1)) >> 2;
        break;

    case 1:
        /* The retail dispatcher explicitly retains this inert selector edge. */
        break;
    case 256:
        child_event[1] = (u32)&work->child_flag;
        work->coordinate_child = RetailCall_08005b6c((void *)0x0810ec05,
                                            760, child_event, parent);
        RetailCall_0814186c((const u16 *)0x03003862, work->saved_palette, 95);
        RetailCall_0814186c(RetailCall_080d3904(), (u16 *)0x03003862, 95);
        work->timer = 33;
        ++event->state;
        break;

    case 257:
        --work->timer;
        if (work->timer != 0)
            break;
        RetailCall_080e0608(&work->x_ramp, 224, 80, 80);
        RetailCall_080d74e0(1, 2, 2, (s16)(work->center_x - 120),
                            (s16)(work->center_y - work->x_ramp.value),
                            (void *)0x06008000, (void *)0x06007000);
        {
            u32 mask = ReadAuthoredDisplayMaskHigh(1);
            register u32 shadow asm("r1") = SH16(0);
            /* The freshly loaded H0 is the real fullword OR accumulator. */
            asm("" : "+r" (shadow));
            shadow |= mask;
            SH16(0) = shadow;
        }
        work->timer = 20;
        ++event->state;
        break;

    case 258:
        if ((u8)RetailCall_080e0690(&work->x_ramp) == 0) {
            RetailCall_080e064c(&work->x_ramp);
            ApplyAuthoredSignedOffsetY((s16)(work->center_y - work->x_ramp.value), 1);
            break;
        }
        if (work->child_flag == 0)
            break;
        if (work->timer != 0) {
            --work->timer;
            if (work->timer != 0)
                break;
        }
        RetailCall_080e0608(&work->x_ramp, 120, 56, 56);
        RetailCall_080e0608(&work->y_ramp, 80, 112, 56);
        InitializeAuthoredSignedRamp(&work->sprite_y_ramp, -32, 70, 56);
        work->sprite = RetailCall_080d5cc0((const void *)0x08504b98,
                            0, 186, work->sprite_y_ramp.value, 908, 6, 2, 0);
        work->sound = RetailCall_080dfd8c((const void *)0x083a2e08,
                                         1, 4, 0, parent);
        work->child_flag = 2;
        ++event->state;
        break;

    case 259:
        RetailCall_080e064c(&work->x_ramp);
        RetailCall_080e064c(&work->y_ramp);
        RetailCall_080e064c(&work->sprite_y_ramp);
        ApplyAuthoredSignedOffsetX((s16)(work->center_x - work->x_ramp.value), 1);
        ApplyAuthoredSignedOffsetY((s16)(work->center_y - work->y_ramp.value), 1);
        RetailCall_080107d4(work->sprite, 186, work->sprite_y_ramp.value, 0);
        if ((u8)RetailCall_080e0690(&work->x_ramp) == 0)
            break;
        if ((u8)RetailCall_080e0690(&work->y_ramp) == 0)
            break;
        if ((u8)RetailCall_080e0690(&work->sprite_y_ramp) == 0)
            break;
        work->timer = 1;
        ++event->state;
        break;

    case 260:
        {
            volatile u8 *shadow;
            TaskNode **created_layer_slot;
        work->coordinate_child = RetailCall_080e051c(work->coordinate_child);
        if (work->coordinate_child != 0)
            break;
        --work->timer;
        if (work->timer != 0)
            break;
        created_layer_slot = &work->first_layer;
        /* This real pair base precedes both creators and later reloads. */
        asm("" : "+r" (created_layer_slot));
        *created_layer_slot = RetailCall_080dab84(1, 0, 0, parent);
        *(TaskNode **)((u32)created_layer_slot + 4) =
            RetailCall_080dab84(0, 0, 0, parent);
        shadow = (volatile u8 *)0x03000940u;
        /* Original shared base survives the mask queries below. */
        asm("" : "+r" (shadow));
        STORE_BASE_BYTE(shadow, 59, 0);
        STORE_BASE_BYTE(shadow, 58, 0);
        STORE_BASE_BYTE(shadow, 63, 0);
        {
            register u32 horizontal_extent asm("r1");
            (void)shadow[62];
            horizontal_extent = 160;
            /* One actual extent value survives the following byte writes. */
            asm("" : "+r" (horizontal_extent));
            shadow[62] = horizontal_extent;
        STORE_BASE_BYTE(shadow, 61, 0);
        STORE_BASE_BYTE(shadow, 60, 0);
        STORE_BASE_BYTE(shadow, 65, 0);
        STORE_BASE_BYTE(shadow, 64, horizontal_extent);
        }
        {
            u32 retained_plane_mask;
            (void)shadow[66];
            retained_plane_mask = 63;
            /* Separate the long-lived mask from the byte-store value. */
            asm("" : "+r" (retained_plane_mask));
            shadow[66] = 63;
            {
                u32 other;
                {
                    register u32 mask asm("r0") =
                        retained_plane_mask & ~ReadAuthoredDisplayMaskLow(3);
                    /* Actual fullword masked byte, dead after the following RMW. */
                    asm("" : "+r" (mask));
                    STORE_BASE_BYTE(shadow, 67, mask);
                }
                other = ReadAuthoredDisplayMaskLow(2);
                other |= ReadAuthoredDisplayMaskLow(3);
                {
                    register u32 combined_mask asm("r4") = other | 32;
                    /* This real combined result dies at the following mask update. */
                    asm("" : "+r" (combined_mask));
                    retained_plane_mask &= ~combined_mask;
                }
                STORE_BASE_BYTE(shadow, 68, retained_plane_mask);
            }
        }
        (*(volatile u16 *)shadow) |= 0x6000;
        work->palette_effect = RetailCall_080d3e9c((const void *)0x0894db94, parent);
        RetailCall_080dac40(*created_layer_slot, 130, 48, work->layer_ramp.value);
        RetailCall_080d9b98(*created_layer_slot);
        work->timer = 30;
        RetailCall_080e0608(&work->layer_ramp, 210, 10, 37);
        ++event->state;
        break;
        }

    case 261:
        if (work->timer != 0) {
            --work->timer;
            if (work->timer != 0)
                break;
            work->sound = RetailCall_080dfd8c((const void *)0x083a2e10,
                                             1, 4, 0, parent);
        }
        RetailCall_080e064c(&work->layer_ramp);
        RetailCall_080dadfc(work->first_layer);
        RetailCall_080dac40(work->first_layer, 130, 48,
                            work->layer_ramp.value);
        RetailCall_080d9b98(work->first_layer);
        if ((u8)RetailCall_080e0690(&work->layer_ramp) == 0)
            break;
        RetailCall_080d3ff8(work->palette_effect, 1);
        work->sound = RetailCall_080dfd8c((const void *)0x083a2e18,
                                         1, 4, 50, parent);
        work->timer = 60;
        work->x_phase = 11;
        work->y_phase = 13;
        RetailCall_080e0608(&work->layer_ramp, 10, 3, 30);
        {
            volatile u8 *phase_shadow = (volatile u8 *)0x03000940u;
            asm("" : "+r" (phase_shadow));
            (void)phase_shadow[78];
            phase_shadow[78] = 12;
        }
        ++event->state;
        break;

    case 262:
        {
            u8 value;
            u8 x_phase_now;
            s32 y_phase_now;
            u16 x, y;
            if (work->timer <= 30)
                RetailCall_080e064c(&work->layer_ramp);
            value = work->layer_ramp.value;
            if (work->timer & 2)
                value -= 3;
            --work->x_phase;
            --work->y_phase;
            x_phase_now = *(volatile u8 *)&work->x_phase;
            x = 130;
            if (x_phase_now == 1) x = 131;
            else if (x_phase_now == 3) x = 129;
            else if (x_phase_now == 6) x = 132;
            else if (x_phase_now == 9) x = 128;
            y_phase_now = *(volatile u8 *)&work->y_phase;
            y = 48;
            if (y_phase_now == 0) y = 47;
            else if (y_phase_now == 2) y = 49;
            else if (y_phase_now == 5) y = 50;
            else if (y_phase_now == 8) y = 46;
            if (*(volatile u8 *)&work->x_phase == 0) work->x_phase = 11;
            if (*(volatile u8 *)&work->y_phase == 0) work->y_phase = 13;
            RetailCall_080dadfc(work->first_layer);
            RetailCall_080dac40(work->first_layer, x, y, value);
            RetailCall_080d9b98(work->first_layer);
            --work->timer;
            if (work->timer != 0)
                break;
            RetailCall_080d3ff8(work->palette_effect, 0);
            RetailCall_080e0608(&work->layer_ramp, 3, 0, 3);
            ++event->state;
            break;
        }

    case 263:
        RetailCall_080e064c(&work->layer_ramp);
        RetailCall_080dadfc(work->first_layer);
        RetailCall_080dac40(work->first_layer, 130, 48, work->layer_ramp.value);
        RetailCall_080d9b98(work->first_layer);
        if ((u8)RetailCall_080e0690(&work->layer_ramp) == 0)
            break;
        work->palette_effect = RetailCall_080d3f08(work->palette_effect);
        if (work->palette_effect != 0)
            break;
        work->first_layer = RetailCall_080d9b64(work->first_layer);
        if (work->first_layer != 0)
            break;
        work->second_layer = RetailCall_080d9b64(work->second_layer);
        if (work->second_layer != 0)
            break;
        work->first_layer = RetailCall_080dad94(130, 48, 1, parent);
        RetailCall_080dade8(work->first_layer, 1);
        work->palette_effect = RetailCall_080d3e9c((const void *)0x0894d97c, parent);
        work->timer = 28;
        ++event->state;
        break;

    case 264:
        {
            TaskNode **palette_slot;
            TaskNode **layer_slot;
            volatile u8 *shadow;
            if (work->timer != 0) {
                --work->timer;
                if (work->timer == 0) {
                    volatile u8 *control_shadow = (volatile u8 *)0x03000940u;
                    asm("" : "+r" (control_shadow));
                    (*(volatile u16 *)control_shadow) &= 0x9fff;
                    (void)control_shadow[74];
                    control_shadow[74] = 0;
                }
            }
            palette_slot = &work->palette_effect;
            /* This actual field address survives the following callbacks. */
            asm("" : "+r" (palette_slot));
            (*palette_slot) = RetailCall_080d3f08((*palette_slot));
            if ((*palette_slot) != 0)
                break;
            {
                register TaskNode **initial_layer_slot asm("r2") = &work->first_layer;
                TaskNode *polled_layer;
                layer_slot = initial_layer_slot;
                /* Both initialized address values feed separate real consumers. */
                asm("" : "+r" (layer_slot), "+r" (initial_layer_slot));
                polled_layer = RetailCall_080dae44(*initial_layer_slot);
                {
                    register TaskNode **completed_layer_slot asm("r3") = layer_slot;
                    asm("" : : "r" (completed_layer_slot));
                    *completed_layer_slot = polled_layer;
                }
                /* Native tests the same fresh result that was just published. */
                if (polled_layer != 0)
                    break;
            }
            /* Calls produce R0 before these short output-address definitions. */
            *({
                register TaskNode **created_slot asm("r1") = layer_slot;
                asm("" : : "r" (created_slot));
                created_slot;
            }) = RetailCall_080dab84(1, 0, 0, parent);
            *(({
                register TaskNode **created_slot asm("r2") = layer_slot;
                asm("" : : "r" (created_slot));
                created_slot;
            }) + 1) = RetailCall_080dab84(0, 0, 0, parent);
            shadow = (volatile u8 *)0x03000940u;
        /* Original shared base survives the mask queries below. */
        asm("" : "+r" (shadow));
        STORE_BASE_BYTE(shadow, 59, 0);
            STORE_BASE_BYTE(shadow, 58, 0);
            STORE_BASE_BYTE(shadow, 63, 0);
            {
            register u32 horizontal_extent asm("r1");
            (void)shadow[62];
            horizontal_extent = 160;
            /* One actual extent value survives the following byte writes. */
            asm("" : "+r" (horizontal_extent));
            shadow[62] = horizontal_extent;
            STORE_BASE_BYTE(shadow, 61, 0);
            STORE_BASE_BYTE(shadow, 60, 0);
            STORE_BASE_BYTE(shadow, 65, 0);
            STORE_BASE_BYTE(shadow, 64, horizontal_extent);
        }
            {
                u32 retained_plane_mask;
                (void)shadow[66];
                retained_plane_mask = 63;
                /* Separate the long-lived mask from the byte-store value. */
                asm("" : "+r" (retained_plane_mask));
                shadow[66] = 63;
                {
                    u32 other;
                    {
                        register u32 working_mask asm("r3") =
                            retained_plane_mask & ~ReadAuthoredDisplayMaskLow(3);
                        register u32 mask asm("r0") = working_mask;
                        /* Keep the actual masked working value through its final copy. */
                        asm("" : "+r" (mask) : "r" (working_mask));
                        STORE_BASE_BYTE(shadow, 67, mask);
                    }
                    other = ReadAuthoredDisplayMaskLow(2);
                    other |= ReadAuthoredDisplayMaskLow(3);
                    {
                        register u32 combined_mask asm("r4") = other | 32;
                        /* This real combined result dies at the following mask update. */
                        asm("" : "+r" (combined_mask));
                        retained_plane_mask &= ~combined_mask;
                    }
                    STORE_BASE_BYTE(shadow, 68, retained_plane_mask);
                }
            }
            {
                /* Here H0 is an input; the constant is the OR accumulator. */
                register u32 display_value asm("r1") = *(volatile u16 *)shadow;
                {
                    register u32 enabled_planes asm("r2") = 0x6000u;
                    /* Both real inputs remain live at this single production point. */
                    asm("" : "+r" (enabled_planes) : "r" (display_value));
                    {
                        register u32 display_result asm("r0") = enabled_planes | display_value;
                        asm("" : "+r" (display_result));
                        *(volatile u16 *)shadow = display_result;
                    }
                }
            }
            RetailCall_080d72c8((const void *)0x088f5d1c, 0, 2, 0, 0, 0, 1);
            *({
                register TaskNode **created_slot asm("r3") = palette_slot;
                asm("" : : "r" (created_slot));
                created_slot;
            }) = RetailCall_080d3e9c((const void *)0x0894d79c, parent);
            {
                u32 pair_index = work->palette_step;
                TaskNode *layer;
                {
                    register TaskNode **produced_slot asm("r1") = layer_slot;
                    TaskNode *produced_layer;
                    /* Mixed: one real 2-byte word load; matching operands share R1.
                     * The memory input tracks exactly the slot read by this load. */
                    asm("ldr %0, [%1]"
                        : "=l" (produced_layer)
                        : "0" (produced_slot), "m" (*produced_slot));
                    layer = produced_layer;
                }
                {
                register const u8 *const *pair_table asm("r1") =
                    (const u8 *const *)0x083a2ddc;
                /* Actual table base is produced before scaling the saved index. */
                asm("" : "+r" (pair_table));
                {
                const u8 *pairs = pair_table[pair_index];
                u8 *resource = (u8 *)RetailCall_080dabb4(layer);
                register u32 ordinal asm("r5") = 0;
                u32 low;
                u32 count;
                asm("" : "+r" (ordinal));
                low = pairs[0];
                count = (u32)pairs[1] << 8;
                count |= low;
                if (ordinal < count) {
                    const u8 *first_bytes = pairs + 2;
                    const u8 *second_bytes = pairs + 3;
                    /* Native loop keeps both actual payload bases separately. */
                    asm("" : "+r" (first_bytes), "+r" (second_bytes));
                    do {
                        u32 byte_offset = ordinal * 2;
                        volatile u8 *entry = (volatile u8 *)(byte_offset + (u32)resource + 64);
                        u8 source_byte = first_bytes[byte_offset];
                        (void)entry[1];
                        entry[1] = source_byte;
                        source_byte = second_bytes[byte_offset];
                        (void)entry[0];
                        entry[0] = source_byte;
                        {
                            register u32 next_ordinal asm("r0") = ordinal + 1;
                            /* Raw fullword addition precedes the actual low16 counter update. */
                            asm("" : "+r" (next_ordinal));
                            ordinal = (u16)next_ordinal;
                        }
                        low = pairs[0];
                        count = (u32)pairs[1] << 8;
                        count |= low;
                    } while (ordinal < count);
                }
                RetailCall_080d9b98(layer);
                }
                }
            }
            work->sound = RetailCall_080dfd8c((const void *)0x083a2e20,
                                             1, 4, 0, parent);
            work->timer = 3;
            work->scroll_phase = 1;
            work->x_phase = 0;
            ++event->state;
            break;

        }

    case 265:
        RetailCall_081443fc(position_offsets, (const void *)0x08149f34, 10);
        ADVANCE_SCROLL();
        if (work->x_phase <= 4) {
            RetailCall_08011040(work->sprite, &sprite_x, &sprite_y, &sprite_z);
            sprite_x += position_offsets[work->x_phase];
            sprite_y -= position_offsets[work->x_phase];
            RetailCall_080107d4(work->sprite, (s16)sprite_x, (s16)sprite_y, 0);
            ++work->x_phase;
        }
        --work->timer;
        if (work->timer != 0)
            break;
        ++work->palette_step;
        if (work->palette_step <= 5) {
            u32 pair_index = work->palette_step;
            TaskNode *layer = work->first_layer;
            register const u8 *const *pair_table asm("r1") =
                (const u8 *const *)0x083a2ddc;
            /* Actual table base is produced before scaling the saved index. */
            asm("" : "+r" (pair_table));
            {
            const u8 *pairs = pair_table[pair_index];
            u8 *resource = (u8 *)RetailCall_080dabb4(layer);
            register u32 ordinal asm("r5") = 0;
            u32 low;
            u32 count;
            asm("" : "+r" (ordinal));
            low = pairs[0];
            count = (u32)pairs[1] << 8;
            count |= low;
            if (ordinal < count) {
                const u8 *first_bytes = pairs + 2;
                const u8 *second_bytes = pairs + 3;
                /* Native loop keeps both actual payload bases separately. */
                asm("" : "+r" (first_bytes), "+r" (second_bytes));
                do {
                    u32 byte_offset = ordinal * 2;
                    volatile u8 *entry = (volatile u8 *)(byte_offset + (u32)resource + 64);
                    u8 source_byte = first_bytes[byte_offset];
                    (void)entry[1];
                    entry[1] = source_byte;
                    source_byte = second_bytes[byte_offset];
                    (void)entry[0];
                    entry[0] = source_byte;
                    {
                        register u32 next_ordinal asm("r0") = ordinal + 1;
                        /* Raw fullword addition precedes the actual low16 counter update. */
                        asm("" : "+r" (next_ordinal));
                        ordinal = (u16)next_ordinal;
                    }
                    low = pairs[0];
                    count = (u32)pairs[1] << 8;
                    count |= low;
                } while (ordinal < count);
            }
            RetailCall_080d9b98(layer);
            }
            work->timer = 3;
            break;
        }
        work->timer = 12;
        ++event->state;
        break;

    case 266:
        ADVANCE_SCROLL();
        --work->timer;
        if (work->timer != 0)
            break;
        work->final_motion = RetailCall_080d6098(64, 112, 0, 1, 1,
                                &work->output_parameter,
                                (const void *)0x083a2dc4, parent);
        work->final_effect = RetailCall_080d4704((const void *)0x0894b9dc, parent);
        work->timer = 60;
        ++event->state;
        break;

    case 267:
        ADVANCE_SCROLL();
        --work->timer;
        if (work->timer != 0)
            break;
        {
            volatile u8 *palette_control = (volatile u8 *)0x03003860u;
            /* Original forms this store from the shared palette-control base. */
            asm("" : "+r" (palette_control));
            palette_control += 226;
            /* The actual destination is formed before the stored constant. */
            asm("" : "+r" (palette_control));
            {
                register u32 control_value asm("r1") = 0x7fff;
                asm("" : "+r" (control_value) : "r" (palette_control));
                *(volatile u16 *)palette_control = control_value;
            }
        }
        RetailCall_080d72c8((const void *)0x088f46cc, 1, 3, 0, 0, 0, 0);
        RetailCall_080e0608(&work->layer_ramp, 0, 210, 60);
        {
            /* Retail reloads this event pointer in R3 only for this update. */
            register struct SceneEvent *advance_event asm("r3") = event;
            asm("" : "+r" (advance_event));
            ++advance_event->state;
        }
        break;

    case 268:
        ADVANCE_SCROLL();
        RetailCall_080e064c(&work->layer_ramp);
        RetailCall_080dac40(work->second_layer, 64, 112, work->layer_ramp.value);
        RetailCall_080d9b98(work->second_layer);
        if ((u8)RetailCall_080e0690(&work->layer_ramp) == 0)
            break;
        {
            u32 mask = ReadAuthoredDisplayMaskHigh(2);
            u32 shadow = SH16(0);
            shadow &= ~mask;
            shadow &= 0x9fff;
            SH16(0) = shadow;
        }
        ++event->state;
        break;

    case 269:
        work->palette_effect = RetailCall_080d3f08(work->palette_effect);
        if (work->palette_effect != 0) break;
        work->final_effect = RetailCall_080d4774(work->final_effect);
        if (work->final_effect != 0) break;
        work->final_motion = RetailCall_080d6134(work->final_motion);
        if (work->final_motion != 0) break;
        work->first_layer = RetailCall_080d9b64(work->first_layer);
        if (work->first_layer != 0) break;
        work->second_layer = RetailCall_080d9b64(work->second_layer);
        if (work->second_layer != 0) break;
        RetailCall_08011428(work->sprite);
        work->sprite = 0;
        RetailCall_0814186c(work->saved_palette, (u16 *)0x03003862, 95);
        event->state = 2;
        break;

    }
    return 0;
}

/* Existing typed helper bindings; directives emit no instructions. */
asm(
    ".global InitializeAuthoredSignedRamp\n.thumb_set InitializeAuthoredSignedRamp,0x080e0609\n"
    ".global ReadAuthoredDisplayMaskHigh\n.thumb_set ReadAuthoredDisplayMaskHigh,0x080035a9\n"
    ".global ReadAuthoredDisplayMaskLow\n.thumb_set ReadAuthoredDisplayMaskLow,0x080035d1\n"
    ".global ApplyAuthoredSignedOffsetX\n.thumb_set ApplyAuthoredSignedOffsetX,0x08003509\n"
    ".global ApplyAuthoredSignedOffsetY\n.thumb_set ApplyAuthoredSignedOffsetY,0x08003559\n"
    ".global RetailCall_08003508\n.thumb_set RetailCall_08003508,0x08003509\n"
    ".global RetailCall_08003558\n.thumb_set RetailCall_08003558,0x08003559\n"
    ".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n"
    ".global RetailCall_080035d0\n.thumb_set RetailCall_080035d0,0x080035d1\n"
    ".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n"
    ".global RetailCall_080107d4\n.thumb_set RetailCall_080107d4,0x080107d5\n"
    ".global RetailCall_08011040\n.thumb_set RetailCall_08011040,0x08011041\n"
    ".global RetailCall_08011428\n.thumb_set RetailCall_08011428,0x08011429\n"
    ".global RetailCall_0801cae0\n.thumb_set RetailCall_0801cae0,0x0801cae1\n"
    ".global RetailCall_080d3904\n.thumb_set RetailCall_080d3904,0x080d3905\n"
    ".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n"
    ".global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n"
    ".global RetailCall_080d3ff8\n.thumb_set RetailCall_080d3ff8,0x080d3ff9\n"
    ".global RetailCall_080d4704\n.thumb_set RetailCall_080d4704,0x080d4705\n"
    ".global RetailCall_080d4774\n.thumb_set RetailCall_080d4774,0x080d4775\n"
    ".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n"
    ".global RetailCall_080d6098\n.thumb_set RetailCall_080d6098,0x080d6099\n"
    ".global RetailCall_080d6134\n.thumb_set RetailCall_080d6134,0x080d6135\n"
    ".global RetailCall_080d72c8\n.thumb_set RetailCall_080d72c8,0x080d72c9\n"
    ".global RetailCall_080d7468\n.thumb_set RetailCall_080d7468,0x080d7469\n"
    ".global RetailCall_080d74e0\n.thumb_set RetailCall_080d74e0,0x080d74e1\n"
    ".global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64,0x080d9b65\n"
    ".global RetailCall_080d9b98\n.thumb_set RetailCall_080d9b98,0x080d9b99\n"
    ".global RetailCall_080dab84\n.thumb_set RetailCall_080dab84,0x080dab85\n"
    ".global RetailCall_080dabb4\n.thumb_set RetailCall_080dabb4,0x080dabb5\n"
    ".global RetailCall_080dac40\n.thumb_set RetailCall_080dac40,0x080dac41\n"
    ".global RetailCall_080dad94\n.thumb_set RetailCall_080dad94,0x080dad95\n"
    ".global RetailCall_080dade8\n.thumb_set RetailCall_080dade8,0x080dade9\n"
    ".global RetailCall_080dadfc\n.thumb_set RetailCall_080dadfc,0x080dadfd\n"
    ".global RetailCall_080dae44\n.thumb_set RetailCall_080dae44,0x080dae45\n"
    ".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n"
    ".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n"
    ".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n"
    ".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n"
    ".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n"
    ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
    ".global RetailCall_081443fc\n.thumb_set RetailCall_081443fc,0x081443fd\n"
);
