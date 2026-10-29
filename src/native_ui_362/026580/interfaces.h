#ifndef SOURCE52_00026580_INTERFACES_H
#define SOURCE52_00026580_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 GetSelectedIndex(const void *);
extern void CollectStageBytes(u16, u8 *);
extern u32 GetJobProperty(u8, u8, u8);
extern u32 SelectedPredicateOne(const void *);
extern u32 SelectedPredicateTwo(const void *);
extern u32 ContentMetric(const void *);
__asm__(".global GetSelectedIndex\n.thumb_set GetSelectedIndex,0x080ce411\n"
        ".global CollectStageBytes\n.thumb_set CollectStageBytes,0x080c9209\n"
        ".global GetJobProperty\n.thumb_set GetJobProperty,0x080c8571\n"
        ".global SelectedPredicateOne\n.thumb_set SelectedPredicateOne,0x080cdbb5\n"
        ".global SelectedPredicateTwo\n.thumb_set SelectedPredicateTwo,0x080cd95d\n"
        ".global ContentMetric\n.thumb_set ContentMetric,0x080161bd");
#endif
