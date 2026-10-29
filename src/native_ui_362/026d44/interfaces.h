#ifndef SOURCE52_00026D44_INTERFACES_H
#define SOURCE52_00026D44_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StageContext {
    u8 unknown_0_127[128];
    u8 terminal_bytes[16];
    u8 unknown_144_147[4];
    u32 *stage_words;
    u8 *stage_bytes;
} StageContext;

typedef struct StageState {
    u8 *record_base;
    u8 first_ordinal;
    u8 last_ordinal;
    u8 mode_marker;
    u8 maximum_metric;
    u8 status;
    u8 stage_count;
} StageState;

#define OFFSET_OF(T, M) ((u32)&(((T *)0)->M))
typedef char CheckWords[OFFSET_OF(StageContext, stage_words) == 148 ? 1 : -1];
typedef char CheckBytes[OFFSET_OF(StageContext, stage_bytes) == 152 ? 1 : -1];
typedef char CheckFirst[OFFSET_OF(StageState, first_ordinal) == 4 ? 1 : -1];
typedef char CheckLast[OFFSET_OF(StageState, last_ordinal) == 5 ? 1 : -1];
typedef char CheckStatus[OFFSET_OF(StageState, status) == 8 ? 1 : -1];

extern u32 QualifiesRecord(const void *, u8);
extern u8 ReadSaveByte(u16);
extern u32 GetAbilityProperty(u16, u8);
extern u32 IsSelectedContextActive(const void *);
extern u32 MeasureDefinitionValue(const void *, u8);
extern u32 SelectedContextCondition(const void *);
extern u32 MetricFromContent(const void *);
extern u32 SelectedContextFlag(const void *);
extern u32 TestDefinitionClass(void);
extern u32 TestDefinitionValue(const void *, u8);
extern u32 TestDefinitionCode(const void *);
extern u32 TestDefinitionRange(u16);
extern u32 TestSpecialContext(const void *);

__asm__(".global QualifiesRecord\n.thumb_set QualifiesRecord,0x080cd561\n"
        ".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n"
        ".global GetAbilityProperty\n.thumb_set GetAbilityProperty,0x080ccd51\n"
        ".global IsSelectedContextActive\n.thumb_set IsSelectedContextActive,0x080cdb3d\n"
        ".global MeasureDefinitionValue\n.thumb_set MeasureDefinitionValue,0x080258c5\n"
        ".global SelectedContextCondition\n.thumb_set SelectedContextCondition,0x080cd95d\n"
        ".global MetricFromContent\n.thumb_set MetricFromContent,0x080161bd\n"
        ".global SelectedContextFlag\n.thumb_set SelectedContextFlag,0x080cd95d\n"
        ".global TestDefinitionClass\n.thumb_set TestDefinitionClass,0x08026a7d\n"
        ".global TestDefinitionValue\n.thumb_set TestDefinitionValue,0x080267ed\n"
        ".global TestDefinitionCode\n.thumb_set TestDefinitionCode,0x08026839\n"
        ".global TestDefinitionRange\n.thumb_set TestDefinitionRange,0x080268dd\n"
        ".global TestSpecialContext\n.thumb_set TestSpecialContext,0x08026ab9");

#endif
