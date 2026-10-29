typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Unit {
    u8 unknown_000[252];
    u8 field_252, field_253;
} Unit;
typedef struct Actor {
    Unit *unit;
    u32 unknown_004;
    u16 x, height, y;
    u8 unknown_014[17];
    s8 direction;
} Actor;
typedef struct Motion {
    Actor *actor;
    s16 target_x, target_y, effect;
    s8 step_x, step_y;
    u8 flags;
    s8 countdown;
    u16 unknown_014;
    s32 target_height, current_height, velocity;
    u16 phase, depth;
    /* Capacity belongs to the producer. The native consumer adds no guard. */
    u16 saved_phase[0];
} Motion;

extern u8 RetailCall_080cd92c(Unit *);
extern u8 RetailCall_080cdadc(Unit *);
extern s32 RetailCall_08099c1c(Actor *, s32, s32);
extern void RetailCall_0809836c(Actor *, u32, s32, u32);
extern void RetailCall_0809a570(Actor *, u32, u32);
extern void RetailCall_080a92e4(s32, s32, s32, s32, u32);
extern void RetailCall_08141520(u32);
extern u32 RetailCall_08099c64(Actor *);

/* These are actual observed stores, including repeated phase assignments.
 * Do not replace the continuation stack with an inferred bounded container. */
#define PUSH_PHASE(m) do { \
    u16 old_depth = (m)->depth++; \
    (m)->saved_phase[old_depth] = (m)->phase; \
} while (0)
#define NEXT_PHASE(m, value) do { PUSH_PHASE(m); (m)->phase = (value); } while (0)
#define PUSH_PHASE_VALUE(m, value) do { \
    u16 old_depth = (m)->depth++; \
    (m)->saved_phase[old_depth] = (value); \
} while (0)
#define CELL_COMPONENT(value) ((s32)((u32)(value) << 19) >> 24)

s32 CoreFrontier_0009CCD4(Motion *motion)
{
    motion->flags &= 254;
    switch (motion->phase) {
    case 0:
        motion->flags |= 1;
        motion->phase = 1;
        /* Native state zero executes state one in this same invocation. */
    case 1: {
        Actor *actor;
        s32 x_pending, y_pending;
        {
            s32 target_x = motion->target_x;
            u16 *position;
            u16 old_position, after;
            s32 next_position;
            s16 before;
            register s32 x_result asm("r0");
            register u32 late_after asm("r5");
            /* Native captures the signed target before the actor/cell phase. */
            asm("" : "+r"(target_x));
            actor = motion->actor;
            position = &actor->x;
            /* This same derived address is consumed again by the clamp store. */
            asm("" : "+r"(position));
            old_position = actor->x;
            next_position = motion->step_x;
            next_position += old_position;
            actor->x = next_position;
            {
                register s32 difference_target asm("r1") = target_x;
                s32 previous;
                /* Native keeps the clamp target distinct from the R1
                 * working value consumed by both coordinate differences. */
                asm("" : "+r"(difference_target));
                previous = (s16)old_position;
                /* Native promotes the captured pre-store halfword before
                 * the difference, then narrows the difference separately. */
                asm("" : "+r"(previous));
                before = difference_target - previous;
                after = difference_target - next_position;
                late_after = after;
                /* The first comparison consumes normalized R1; this real
                 * saved copy is consumed only by the later positive test. */
                asm("" : "+r"(late_after));
            }
            if (before <= 0) {
                if ((s16)after >= 0)
                    goto reached_x;
                if (before < 0)
                    goto moving_x;
            }
            {
                register s32 later_sign asm("r0") = (s32)(late_after << 16);
                /* The projected sign is a distinct real working value;
                 * the original retained remainder stays in R5. */
                asm("" : "+r"(later_sign));
                if (later_sign > 0)
                    goto moving_x;
            }
reached_x:
            *position = target_x;
            x_result = 0;
            goto done_x;
moving_x:
            x_result = 1;
done_x:
            /* Native joins the real 0/1 result in R0 before retaining it. */
            asm("" : "+r"(x_result));
            x_pending = x_result;
        }
        {
            s32 target_y = motion->target_y;
            register u16 *position asm("r6");
            u16 old_position, after;
            s32 next_position;
            s16 before;
            asm("" : "+r"(target_y));
            position = &actor->y;
            asm("" : "+r"(position));
            old_position = actor->y;
            next_position = motion->step_y;
            next_position += old_position;
            actor->y = next_position;
            {
                register s32 difference_target asm("r1") = target_y;
                s32 previous;
                /* Native keeps the clamp target distinct from the R1
                 * working value consumed by both coordinate differences. */
                asm("" : "+r"(difference_target));
                previous = (s16)old_position;
                /* Native promotes the captured pre-store halfword before
                 * the difference, then narrows the difference separately. */
                asm("" : "+r"(previous));
                before = difference_target - previous;
                after = difference_target - next_position;
            }
            if (before <= 0) {
                if ((s16)after >= 0)
                    goto reached_y;
                if (before < 0)
                    goto moving_y;
            }
            if ((s16)after > 0)
                goto moving_y;
reached_y:
            *position = target_y;
            y_pending = 0;
            goto done_y;
moving_y:
            y_pending = 1;
done_y:
            ;
        }
        if (x_pending || y_pending)
            break;
        {
            Unit *unit = motion->actor->unit;
            if ((unit->field_252 == 2 || unit->field_253 == 4)
                && !(u8)RetailCall_080cd92c(unit)
                && !(u8)RetailCall_080cdadc(motion->actor->unit)) {
                s32 height;
                {
                    register Actor *cell_actor asm("r0") = motion->actor;
                    register s32 cell_x asm("r1");
                    s32 cell_y;
                    asm("" : "+r"(cell_actor));
                    cell_x = CELL_COMPONENT(cell_actor->x);
                    /* Finalize X before consuming the retained actor for Y. */
                    asm("" : "+r"(cell_x), "+r"(cell_actor));
                    cell_y = CELL_COMPONENT(cell_actor->y);
                    height = RetailCall_08099c1c(cell_actor,
                        cell_x, cell_y) * 16;
                }
                actor = motion->actor;
                if (height == (s16)actor->height) {
                    RetailCall_0809836c(actor, 4, actor->direction, 0);
                    {
                        register u32 sequence_phase asm("r3") = 11;
                        asm("" : "+r"(sequence_phase));
                        motion->phase = sequence_phase;
                        PUSH_PHASE_VALUE(motion, sequence_phase);
                        sequence_phase = 8;
                        asm("" : "+r"(sequence_phase));
                        motion->phase = sequence_phase;
                        motion->countdown = 16;
                        PUSH_PHASE_VALUE(motion, sequence_phase);
                        motion->phase = 7;
                    }
                } else {
                    s32 distance;
                    motion->target_height = height + (((s16)actor->height - height) >> 1);
                    distance = motion->target_height - (s16)actor->height;
                    if (distance < 0)
                        distance = -distance;
                    motion->current_height = distance;
                    if (actor->unit->field_252 == 2)
                        RetailCall_0809836c(actor, 2, actor->direction, 0);
                    else
                        RetailCall_0809836c(actor, 1, actor->direction, 0);
                    RetailCall_0809a570(motion->actor, 256, 2);
                    motion->phase = 3;
                }
            } else {
                {
                    register Actor *cell_actor asm("r0") = motion->actor;
                    register s32 cell_x asm("r1");
                    s32 cell_y;
                    asm("" : "+r"(cell_actor));
                    cell_x = CELL_COMPONENT(cell_actor->x);
                    /* Finalize X before consuming the retained actor for Y. */
                    asm("" : "+r"(cell_x), "+r"(cell_actor));
                    cell_y = CELL_COMPONENT(cell_actor->y);
                    motion->target_height = RetailCall_08099c1c(cell_actor,
                        cell_x, cell_y) << 12;
                }
                motion->current_height = (s16)motion->actor->height * 256;
                motion->velocity = 0;
                motion->phase = 2;
            }
        }
        break;
    }
    case 2: {
        s32 current = motion->current_height + motion->velocity;
        s32 velocity, target, pending;
        register u32 sequence_phase asm("r3");
        motion->current_height = current;
        velocity = motion->velocity - 153;
        motion->velocity = velocity;
        target = motion->target_height;
        if (target >= current && velocity <= 0) {
            motion->current_height = target;
            pending = 0;
        } else {
            pending = 1;
        }
        motion->actor->height = motion->current_height >> 8;
        if (pending)
            break;
        sequence_phase = 11;
        asm("" : "+r"(sequence_phase));
        motion->phase = sequence_phase;
        if (motion->effect != 0) {
            Actor *actor;
            u32 disabled;
            {
                register Actor *animation_actor asm("r0") = motion->actor;
                asm("" : "+r"(animation_actor));
                RetailCall_0809836c(animation_actor, 5, animation_actor->direction, 0);
            }
            disabled = (u8)(motion->flags & 2);
            if (!disabled) {
                s32 effect = motion->effect;
                actor = motion->actor;
                RetailCall_080a92e4(effect, (s16)actor->x,
                    (s16)(actor->height + 48), (s16)actor->y, disabled);
            }
            RetailCall_08141520(137);
            PUSH_PHASE(motion);
            motion->phase = 9;
        } else {
            PUSH_PHASE_VALUE(motion, sequence_phase);
            sequence_phase = 7;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            motion->countdown = 16;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            motion->phase = sequence_phase;
        }
        break;
    }
    case 3: {
        Actor *actor = motion->actor;
        register s32 distance asm("r1") = (s16)actor->height;
        s32 step;
        register s32 amount asm("r1");
        /* Native R1 first holds signed height, then its distance, then the
         * division numerator. Each definition consumes the preceding phase. */
        asm("" : "+r"(distance));
        distance = motion->target_height - distance;
        asm("" : "+r"(distance));
        if (distance < 0)
            distance = -distance;
        amount = motion->current_height - distance;
        /* Native retains this numerator in R1 before forming call R0. */
        asm("" : "+r"(amount));
        step = amount / 6;
        if (step <= 0)
            step = 1;
        actor->height -= step;
        {
            register Actor *actor_after asm("r2") = motion->actor;
            /* The updated root is a new value after the observed height store. */
            asm("" : "+r"(actor_after));
            if (motion->target_height < (s16)actor_after->height)
                break;
            actor_after->height = motion->target_height;
        }
        {
            register Actor *cell_actor asm("r0") = motion->actor;
            register s32 cell_x asm("r1");
            s32 cell_y;
            asm("" : "+r"(cell_actor));
            cell_x = CELL_COMPONENT(cell_actor->x);
            asm("" : "+r"(cell_x), "+r"(cell_actor));
            cell_y = CELL_COMPONENT(cell_actor->y);
            motion->target_height = RetailCall_08099c1c(cell_actor,
                cell_x, cell_y) * 16;
        }
        motion->phase = 4;
        break;
    }
    case 4: {
        Actor *actor = motion->actor;
        s32 distance = motion->target_height - (s16)actor->height;
        s32 step;
        register u32 saved_six asm("r6");
        if (distance < 0)
            distance = -distance;
        saved_six = 6;
        /* This actual phase value survives the original division/flag calls;
         * its later phase/stack stores consume the same R6 carrier. */
        asm("" : "+r"(saved_six));
        step = distance / 6;
        if (!step)
            step = 1;
        actor->height -= step;
        {
            register Actor *actor_after asm("r2") = motion->actor;
            /* The updated root is a new value after the observed height store. */
            asm("" : "+r"(actor_after));
            if (motion->target_height < (s16)actor_after->height)
                break;
            actor_after->height = motion->target_height;
        }
        RetailCall_0809a570(motion->actor, 2, 0);
        {
            register u32 sequence_phase asm("r2") = 11;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            motion->countdown = 3;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            sequence_phase = 8;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            sequence_phase = 10;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            motion->phase = saved_six;
            PUSH_PHASE_VALUE(motion, saved_six);
            sequence_phase = 7;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            sequence_phase = 5;
            asm("" : "+r"(sequence_phase));
            motion->phase = sequence_phase;
            PUSH_PHASE_VALUE(motion, sequence_phase);
            motion->phase = 9;
        }
        break;
    }
    case 7:
        if (motion->countdown <= 0)
            goto pop_phase;
        motion->countdown = (u8)motion->countdown - 1;
        break;
    case 8: {
        register Actor *actor asm("r0") = motion->actor;
        register s32 direction asm("r2") = actor->direction;
        register u32 action asm("r1") = 0;
        register u32 trailing_zero asm("r3") = 0;
        /* These are the four actual initialized native outgoing arguments.
         * Keep the last zero definition in its original case-owned block. */
        asm("" : "+r"(trailing_zero)
            : "r"(actor), "r"(action), "r"(direction));
        RetailCall_0809836c(actor, action, direction, trailing_zero);
        goto pop_phase;
    }
    case 5: {
        register Actor *actor asm("r0") = motion->actor;
        register s32 direction asm("r2") = actor->direction;
        register u32 action asm("r1") = 3;
        register u32 trailing_zero asm("r3") = 0;
        /* These are the four actual initialized native outgoing arguments.
         * Keep the last zero definition in its original case-owned block. */
        asm("" : "+r"(trailing_zero)
            : "r"(actor), "r"(action), "r"(direction));
        RetailCall_0809836c(actor, action, direction, trailing_zero);
        goto pop_phase;
    }
    case 6: {
        register Actor *actor asm("r0") = motion->actor;
        register s32 direction asm("r2") = actor->direction;
        register u32 action asm("r1") = 4;
        register u32 trailing_zero asm("r3") = 0;
        /* These are the four actual initialized native outgoing arguments.
         * Keep the last zero definition in its original case-owned block. */
        asm("" : "+r"(trailing_zero)
            : "r"(actor), "r"(action), "r"(direction));
        RetailCall_0809836c(actor, action, direction, trailing_zero);
        goto pop_phase;
    }
    case 9:
        if (!RetailCall_08099c64(motion->actor))
            break;
    case 10:
pop_phase:
        {
            u16 new_depth = --motion->depth;
            motion->phase = motion->saved_phase[new_depth];
        }
        break;
    case 11:
        return 0;
    }
    return 1;
}

asm(".global RetailCall_080cd92c\n.thumb_set RetailCall_080cd92c,0x080cd92d\n"
    ".global RetailCall_080cdadc\n.thumb_set RetailCall_080cdadc,0x080cdadd\n"
    ".global RetailCall_08099c1c\n.thumb_set RetailCall_08099c1c,0x08099c1d\n"
    ".global RetailCall_0809836c\n.thumb_set RetailCall_0809836c,0x0809836d\n"
    ".global RetailCall_0809a570\n.thumb_set RetailCall_0809a570,0x0809a571\n"
    ".global RetailCall_080a92e4\n.thumb_set RetailCall_080a92e4,0x080a92e5\n"
    ".global RetailCall_08141520\n.thumb_set RetailCall_08141520,0x08141521\n"
    ".global RetailCall_08099c64\n.thumb_set RetailCall_08099c64,0x08099c65\n");

/* Standard signed-division runtime, bound to the original Thumb callee. */
asm(".global __divsi3\n.thumb_set __divsi3,0x081426b9\n");
