typedef unsigned char u8;
typedef unsigned int u32;
extern u32 AdvanceTargetCandidateEnumeration(void *context);
u32 CoreRegion30_000C47FC(void *context)
{
    return (u8)AdvanceTargetCandidateEnumeration(context);
}
asm(".global AdvanceTargetCandidateEnumeration\n.thumb_set AdvanceTargetCandidateEnumeration,0x080c286d\n");
