/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitEffectView {u8 unknown00[40];u32 status;};
struct EffectProgress {u16 current,count;u16 history[0];};
struct EffectSequence {const struct UnitEffectView *unit;u8 unknown04[96];u32 random_seed;u8 unknown68[100];struct EffectProgress progress;};
typedef char SeedOffset[(u32)&((struct EffectSequence*)0)->random_seed==100?1:-1];
typedef char ProgressOffset[(u32)&((struct EffectSequence*)0)->progress==204?1:-1];
typedef char HistoryOffset[(u32)&((struct EffectSequence*)0)->progress.history==208?1:-1];
extern void (*const ClearEffectSequence)(void *,int);
extern volatile u32 *GetRandomSeedAddress(void);
extern u32 ReadSaveByte(u16);
__asm__(".global ClearEffectSequence\n.set ClearEffectSequence,0x0836d4b8\n.global GetRandomSeedAddress\n.thumb_set GetRandomSeedAddress,0x08002831\n.global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");

static inline void SaveEffectState(struct EffectSequence *sequence)
{
    struct EffectProgress *progress=&sequence->progress;
    progress->history[progress->count++]=progress->current;
}
void InitializeBattleEffectSequence(struct EffectSequence *sequence,const struct UnitEffectView *unit);
void InitializeBattleEffectSequence(struct EffectSequence *sequence,const struct UnitEffectView *unit)
{
    ClearEffectSequence(sequence,276);
    sequence->random_seed=*GetRandomSeedAddress();
    sequence->unit=unit;
    sequence->progress.current=39;
    SaveEffectState(sequence);
    sequence->progress.current=31;
    SaveEffectState(sequence);
    sequence->progress.current=38;
    SaveEffectState(sequence);
    sequence->progress.current=26;
    SaveEffectState(sequence);
    sequence->progress.current=24;
    SaveEffectState(sequence);
    sequence->progress.current=6;
    SaveEffectState(sequence);
    sequence->progress.current=4;
    SaveEffectState(sequence);
    sequence->progress.current=5;
    SaveEffectState(sequence);
    sequence->progress.current=2;
    SaveEffectState(sequence);
    sequence->progress.current=6;
    SaveEffectState(sequence);
    sequence->progress.current=0;
    if (sequence->unit->status&6) {
        SaveEffectState(sequence);
        sequence->progress.current=10;
    }
    if (sequence->unit->status&8) {
        SaveEffectState(sequence);
        sequence->progress.current=11;
    }
    if (sequence->unit->status&16) {
        SaveEffectState(sequence);
        sequence->progress.current=12;
    }
    if (sequence->unit->status&32) {
        SaveEffectState(sequence);
        sequence->progress.current=13;
    }
    if (sequence->unit->status&64) {
        SaveEffectState(sequence);
        sequence->progress.current=14;
    }
    if (sequence->unit->status&128) {
        SaveEffectState(sequence);
        sequence->progress.current=15;
    }
    if (sequence->unit->status&768) {
        SaveEffectState(sequence);
        sequence->progress.current=16;
    }
    if (sequence->unit->status&1024) {
        SaveEffectState(sequence);
        sequence->progress.current=17;
    }
    if (sequence->unit->status&2048) {
        SaveEffectState(sequence);
        sequence->progress.current=18;
    }
    if (sequence->unit->status&4096) {
        SaveEffectState(sequence);
        sequence->progress.current=19;
    }
    if (sequence->unit->status&8192) {
        SaveEffectState(sequence);
        sequence->progress.current=8;
        SaveEffectState(sequence);
        sequence->progress.current=22;
    }
    if (sequence->unit->status&16384) {
        SaveEffectState(sequence);
        sequence->progress.current=20;
    }
    if (sequence->unit->status&32768) {
        SaveEffectState(sequence);
        sequence->progress.current=32;
    }
    SaveEffectState(sequence);
    sequence->progress.current=36;
    if ((u8)ReadSaveByte(13)) {
        SaveEffectState(sequence);
        sequence->progress.current=40;
    }
}
