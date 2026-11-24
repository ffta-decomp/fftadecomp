typedef unsigned int u32;
extern u32 ResolveNestedGroupPolicy(u32 group);
asm(".global ResolveNestedGroupPolicy\n.thumb_set ResolveNestedGroupPolicy,0x0800a06d");
u32 ResolveBattleNestedGroup(u32 group)
{
    return ResolveNestedGroupPolicy(group);
}
