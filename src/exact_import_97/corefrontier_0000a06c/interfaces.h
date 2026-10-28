#ifndef NESTED_GROUP_POLICY_H
#define NESTED_GROUP_POLICY_H
typedef unsigned char u8;
typedef unsigned int u32;
extern void BeginNestedGroupPolicy(void);
/* Register carriers stay full width; narrowing belongs to the existing
 * implementation or the explicit outcome-byte observation in this caller. */
extern u32 RunNestedGroup(u32 group, u32 variant);
extern u32 ResolveGroupOutcome(u32 eligible);
__asm__(".global BeginNestedGroupPolicy\n.thumb_set BeginNestedGroupPolicy,0x0800a0b5\n.global RunNestedGroup\n.thumb_set RunNestedGroup,0x0800a0b9\n.global ResolveGroupOutcome\n.thumb_set ResolveGroupOutcome,0x08009e9d");
#endif
