typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ResourceDuration {u8 unknown0[20];u16 flags;u16 duration;};
void Source52_0001121C(struct ResourceDuration *resource,u32 duration)
{
    u32 normalized, working;
    struct ResourceDuration *target;
    register struct ResourceDuration *value asm("r0")=resource;
    register u32 shifted asm("r1")=duration;
    /* Original LSL precedes the resource capture. The resource operand remains
       unchanged, and its defined output keeps that capture after the LSL. */
    asm(".syntax unified\n lsls %1,%1,#16\n.syntax divided"
        : "+r"(value), "+r"(shifted) : : "cc");
    target=value;
    working=shifted;
    normalized=working>>16;
    if(working == 0)target->flags &= 0xF7FF;
    else target->flags |= 0x800;
    target->duration=normalized;
}
