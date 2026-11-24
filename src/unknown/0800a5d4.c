typedef unsigned char u8;
typedef unsigned int u32;

extern u32 ResolveNestedGroupPolicy(u32 group);
/* Linkage for the existing exact C helper; emits no instructions. */
__asm__(".global ResolveNestedGroupPolicy\n.thumb_set ResolveNestedGroupPolicy,0x0800a06d");

/* Mission continuation uses the full policy result, not its low byte. */
u32 ResolveMissionEventGroupPolicy(u8 mode)
{
    u32 group = 0;
    if (mode == 0)
        group = 1;
    return ResolveNestedGroupPolicy(group);
}
