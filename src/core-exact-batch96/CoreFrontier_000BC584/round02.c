typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct UnitFlagView { u32 identity_word; u8 unknown4[36]; u16 flags; };
struct BattleActorView {
    struct UnitFlagView *unit;
    u32 unknown4;
    s16 x, y, z;
    u8 unknown14[34];
    u32 flags;
};
struct ActorDisposalSequence;
struct ActorListProgression {
    u32 unknown0;
    struct BattleActorView *records[13];
    u8 cursor;
    u8 total;
    u16 ticks;
    struct ActorDisposalSequence *subsequence;
    u16 phase;
    u16 stack_count;
    u16 stack[0];
};
extern void ResetBattleActorAndLinkedStateBits(struct BattleActorView *);
extern void *DisposeBattleContentActor(struct BattleActorView *);
extern void InitializeActorDisposalSequence(struct ActorDisposalSequence *, struct BattleActorView *);
extern u32 AdvanceActorDisposalSequence(struct ActorDisposalSequence *);
extern void BeginBattleCoordinateTransition(s16, s16, s16);
extern u32 PollBattleCoordinateTransition(void);
extern void BeginManagedRecordRequest(u16, u16, u32);
extern int ServiceManagedRecordResult(void);
extern void SetManagedRecordHalfwords(void);
__asm__(".global ResetBattleActorAndLinkedStateBits\n.thumb_set ResetBattleActorAndLinkedStateBits,0x08099bad\n.global DisposeBattleContentActor\n.thumb_set DisposeBattleContentActor,0x080995c1\n.global InitializeActorDisposalSequence\n.thumb_set InitializeActorDisposalSequence,0x080bc3b1\n.global AdvanceActorDisposalSequence\n.thumb_set AdvanceActorDisposalSequence,0x080bc40d\n.global BeginBattleCoordinateTransition\n.thumb_set BeginBattleCoordinateTransition,0x08096f3d\n.global PollBattleCoordinateTransition\n.thumb_set PollBattleCoordinateTransition,0x08096f7d\n.global BeginManagedRecordRequest\n.thumb_set BeginManagedRecordRequest,0x08025689\n.global ServiceManagedRecordResult\n.thumb_set ServiceManagedRecordResult,0x08025465\n.global SetManagedRecordHalfwords\n.thumb_set SetManagedRecordHalfwords,0x08029515");
typedef char phase_offset_check[(u32)&((struct ActorListProgression *)0)->phase==64?1:-1];
typedef char stack_offset_check[(u32)&((struct ActorListProgression *)0)->stack==68?1:-1];
/* Keep physical case order, live cursor reloads and the shared pop tail. */
u32 AdvanceBattleActorList(struct ActorListProgression *state, u16 input)
{
    register struct BattleActorView **selected_slot __asm__("r1");
    register u32 record_offset __asm__("r0");
    struct UnitFlagView *unit;
    u32 incremented_ticks;
    switch (state->phase) {
    case 0:
        if (state->cursor >= state->total)
            goto pop_phase;
        state->stack[state->stack_count++] = state->phase;
        state->phase = 8;
        state->stack[state->stack_count++] = state->phase;
        state->phase = 5;
        state->stack[state->stack_count++] = state->phase;
        state->phase = 3;
        state->stack[state->stack_count++] = state->phase;
        state->phase = 1;
        break;
    case 8:
        ResetBattleActorAndLinkedStateBits(state->records[state->cursor]);
        DisposeBattleContentActor(state->records[state->cursor]);
        ++state->cursor;
        goto pop_phase;
    case 3:
        record_offset = (u32)state->cursor << 2;
        selected_slot = state->records;
        /* Original keeps byte offset R0 separate from array base R1. */
        __asm__("" : "+r"(record_offset), "+r"(selected_slot));
        selected_slot = (struct BattleActorView **)((u8 *)selected_slot + record_offset);
        /* Original constructs this R1 address before loading argument R0. */
        __asm__("" : "+r"(selected_slot));
        InitializeActorDisposalSequence(state->subsequence, *selected_slot);
        state->phase = 4;
        break;
    case 4:
        if ((u8)AdvanceActorDisposalSequence(state->subsequence) != 0)
            break;
        unit = state->records[state->cursor]->unit;
        unit->flags |= 0x100;
        state->records[state->cursor]->flags |= 5;
        goto pop_phase;
    case 1:
        BeginBattleCoordinateTransition(state->records[state->cursor]->x,
                                        state->records[state->cursor]->y,
                                        state->records[state->cursor]->z);
        state->phase = 2;
        break;
    case 2:
        if (PollBattleCoordinateTransition() != 0)
            break;
        goto pop_phase;
    case 5:
        BeginManagedRecordRequest(47, 0, state->records[state->cursor]->unit->identity_word);
        state->ticks = 0;
        state->phase = 6;
        break;
    case 6:
        incremented_ticks = (u32)state->ticks + 1;
        state->ticks = incremented_ticks;
        if ((input & 3) != 0 && (s16)incremented_ticks > 15)
            state->ticks = 120;
        ServiceManagedRecordResult();
        if ((s16)state->ticks > 119) {
            state->ticks = 0;
            SetManagedRecordHalfwords();
            state->phase = 7;
        }
        break;
    case 7:
        if ((u16)ServiceManagedRecordResult() == 0)
            break;
pop_phase:
        state->phase = state->stack[--state->stack_count];
        break;
    case 9:
        return 0;
    default:
        break;
    }
    return 1;
}
