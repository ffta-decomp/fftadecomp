#ifndef SOURCE233_9D7E4_INTERFACES_H
#define SOURCE233_9D7E4_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef void (*ClearFunction)(void *, u32);

extern ClearFunction const gMovementContextClear;
extern void ClearRecordThroughCallback(u32 destination, u32 byte_count,
                                       u32 callback_address);
extern void ComputeMovementContextWords(u16 *output_word_0,
                                        u16 *output_word_2);

__asm__(".global gMovementContextClear\n"
        ".set gMovementContextClear,0x0836d4b8\n"
        ".global ClearRecordThroughCallback\n"
        ".thumb_set ClearRecordThroughCallback,0x0814224d\n"
        ".global ComputeMovementContextWords\n"
        ".thumb_set ComputeMovementContextWords,0x0801e6f1\n");

#endif
