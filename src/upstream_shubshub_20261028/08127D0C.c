/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08127D0C.c
 * Original SHA-256: b60c39bbffbe032940a3921624ac542df6ca55a9882cdf6bff2791993dcc9a10
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08127D0C .. 0812800C: 768 bytes. */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Completion;

typedef struct {
    u16 value;
    u8 unknown_02[22];
} Ramp;

typedef struct {
    u16 opcode;
    u16 unknown_02;
    Completion *completion;
    u32 target;
    u8 unknown_0C[8];
    u16 duration;
    u16 channels;
} Command;

typedef struct {
    Completion *completion;
    u32 target;
    s16 duration;
    u8 channels;
    u8 unknown_0B;
    Ramp first;
    Ramp second;
    Ramp third;
} Transition;

extern u32 func_08121D34(void);
extern void func_08121D40(u32 value, u8 selected);
extern u16 func_0814180C(void);
extern u32 func_0814168C(u16 selector);
extern void func_08007620(Ramp *ramp, u16 first, u16 second, u16 target,
                          s16 duration);
extern void func_080076F4(Ramp *ramp);
extern u32 func_08007894(const void *ramp);
extern void func_08141780(float volume);
extern void func_081415C0(u16 selector, float volume);
extern void func_081452F4(void);
extern void func_08141708(void);
extern void func_0814164C(u16 channel);

s32 func_08127D0C(void *context, Command *command, Transition *transition)
{
    switch (command->opcode) {
    case 0:
        transition->completion = command->completion;
        transition->target = command->target;
        transition->duration = command->duration;
        transition->channels = command->channels;
        break;
    case 256:
        {
            u32 current = func_08121D34();

            if ((transition->channels & 1) && (u8)func_0814180C())
                func_08007620(&transition->first, current & 0xFF, 0,
                              (u8)transition->target,
                              transition->duration);
            if ((transition->channels & 2) && (u8)func_0814168C(1))
                func_08007620(&transition->second, (current >> 8) & 0xFF, 0,
                              (transition->target >> 8) & 0xFF,
                              transition->duration);
            if ((transition->channels & 4) && (u8)func_0814168C(2))
                func_08007620(&transition->third, (current >> 16) & 0xFF, 0,
                              (transition->target >> 16) & 0xFF,
                              transition->duration);
            command->opcode = 257;
        }
    case 257:
        {
            u8 selected = 0;
            u8 finished = 0;
            u8 inactive = 0;
            u32 packed = 0;
            u8 value;

            if (transition->channels & 1) {
                if ((u8)func_0814180C()) {
                    Ramp *ramp = &transition->first;

                    func_080076F4(ramp);
                    value = transition->first.value;
                    if (value > 9)
                        func_08141780((float)(value / 100.0));
                    packed = value;
                    finished = func_08007894(ramp);
                } else {
                    packed = (u8)transition->target;
                    inactive = 1;
                }
                selected |= 1;
            } else {
                inactive = 1;
            }
            if (transition->channels & 2) {
                if ((u8)func_0814168C(1)) {
                    Ramp *ramp = &transition->second;

                    func_080076F4(ramp);
                    value = transition->second.value;
                    if (value > 9)
                        func_081415C0(1, (float)(value / 100.0));
                    packed |= value << 8;
                    finished = func_08007894(ramp);
                } else {
                    packed |= (u8)transition->target << 8;
                    inactive |= 2;
                }
                selected |= 2;
            } else {
                inactive |= 2;
            }
            if (transition->channels & 4) {
                if ((u8)func_0814168C(2)) {
                    Ramp *ramp = &transition->third;

                    func_080076F4(ramp);
                    value = transition->third.value;
                    if (value > 9)
                        func_081415C0(2, (float)(value / 100.0));
                    packed |= value << 16;
                    finished = func_08007894(ramp);
                } else {
                    packed |= (u8)transition->target << 16;
                    inactive |= 4;
                }
                selected |= 4;
            } else {
                inactive |= 4;
            }
            inactive |= 8;
            if (selected)
                func_08121D40(packed, selected);
            if (finished || inactive == 15)
                command->opcode = 258;
        }
        break;
    case 258:
        {
            u32 current = func_08121D34();

            if (current == 0) {
                func_081452F4();
            } else {
                if ((transition->channels & 1) && !(current & 0xFF))
                    func_08141708();
                if ((transition->channels & 2) && !(current & 0xFF00))
                    func_0814164C(1);
                if ((transition->channels & 4) && !(current & 0xFF0000))
                    func_0814164C(2);
            }
            transition->completion->complete = 1;
            command->opcode = 3;
        }
        break;
    }
    return 0;
}
