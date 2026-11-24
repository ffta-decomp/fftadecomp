/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct UnitRecord {void *unit;};
struct EffectRecord {struct UnitRecord *record;u8 gap[8];u16 flags;u8 tail[30];};
struct State {struct UnitRecord *record;u8 gap[12];u16 first;u16 second;u8 gap2[12];struct EffectRecord effects[15];u8 gap3[12];u8 count;};
extern u8 gContext[];
extern void *gTargets[2];
extern void PrepareEffects(u16,u16,u8);
extern u8 Check8240(void *);
extern int ReadA740(void *);
extern int ReadA77C(void *);
extern void SelectEffect(u8);
extern u8 ResolveEffect(void);

asm(".global gContext\n.set gContext,0x0200f390\n.global gTargets\n.set gTargets,0x0200f3f0\n.global PrepareEffects\n.thumb_set PrepareEffects,0x812f2a5\n.global Check8240\n.thumb_set Check8240,0x80c8241\n.global ReadA740\n.thumb_set ReadA740,0x809a741\n.global ReadA77C\n.thumb_set ReadA77C,0x809a77d\n.global SelectEffect\n.thumb_set SelectEffect,0x812f329\n.global ResolveEffect\n.thumb_set ResolveEffect,0x8131025\n");
void AppendFirstQualifyingEffectRecord(struct State *state, void *context, u8 option)
{
    int index = 0;
    int count;
    struct UnitRecord *record;
    struct EffectRecord *effect;
    if (index < state->count) {
        record = state->record;
        count = state->count;
        effect = state->effects;
        do {
            if (record == effect->record) return;
            effect++;
            index++;
        } while (index < count);
    }
    PrepareEffects(state->first,state->second,option);
    if (Check8240(state->record->unit)) gContext[132] = ReadA740(context);
    else gContext[132] = ReadA77C(context);
    for (index = 0; index <= 2; index++) {
        gTargets[1] = gTargets[0] = state->record->unit;
        SelectEffect(index);
        if (index && !state->count) return;
        if (ResolveEffect() == 6) {
            state->effects[state->count].record = state->record;
            state->effects[state->count].flags |= 64;
            state->count++;
            return;
        }
    }
}
