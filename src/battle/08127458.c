typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef signed long long s64;typedef unsigned long long u64;
struct Actor {u8 unknown0[8];s16 x;u16 y;s16 z;};
struct Step {s16 value; s16 unused; s16 target;u8 unknown6[18];};
struct State {void *owner;struct Actor *actor;s16 dx,dz;u16 parameter;u8 mode,sequence;s8 direction_x,direction_z;u16 target[3];struct Step x,z;s64 rate;};
extern u32 IntegerSqrt(u32);extern s32 DivideSigned(s32,s32);extern s64 DivideWide(s64,s64);
extern void InitStep(struct Step*,s32,s32,s32,s32);
extern void SetActorMode(struct Actor*,u32,s32,u32);extern void ConfigureActorSequence(struct Actor*,u32,u32);extern s32 QueryActorSequence(struct Actor*);
void InitializeUnitCoordinateTransition(struct State*) __asm__("CoreRegion_00127458");
void InitializeUnitCoordinateTransition(struct State *state)
{
    u32 duration_mode=state->mode>>7;
    s32 start_x,start_z,dx,dz,end_x,end_z;
    u32 distance,time;
    register s64 rate __asm__("r0");
    register s32 step_duration __asm__("r4");
    register struct Step *first_output __asm__("r0");
    register s32 first_start __asm__("r1");
    register s32 first_end __asm__("r3");
    state->mode&=127;
    start_x=state->actor->x;
    dx=state->dx;
    start_z=state->actor->z;
    dz=state->dz;
    end_x=start_x+dx;
    end_z=start_z+dz;
    distance=(u16)IntegerSqrt((u32)(dx*dx)+(u32)(dz*dz));
    if(duration_mode) {
        u32 parameter=state->parameter;
        register u64 branch_rate __asm__("r0");
        time=(u16)DivideSigned(distance,parameter);
        /* Fullword parameter zero-extended then shifted into the actual ABI pair. */
        __asm__ volatile("add %Q0,%1,#0\n\tmov %R0,#0\n\tlsr r3,%Q0,#16\n\tlsl r2,%R0,#16\n\tadd %R0,r3,#0\n\torr %R0,r2\n\tlsl %Q0,%Q0,#16"
                         : "=&r"(branch_rate) : "l"(parameter) : "r2","r3","cc");
        __asm__("" : "+r"(branch_rate));
        rate=branch_rate;
    }else {
        register u64 numerator __asm__("r0");
        register u64 denominator __asm__("r2");
        u64 shift_input;
        time=state->parameter;
        numerator=(u64)distance<<16;
        __asm__("" : "+r"(numerator));
        shift_input=numerator;
        __asm__("" : "+r"(shift_input));
        numerator=shift_input<<16;
        denominator=(u64)time<<16;
        __asm__("" : "+r"(numerator), "+r"(denominator));
        rate=DivideWide(numerator,denominator);
    }
    __asm__("" : "+r"(rate));
    state->rate=rate;
    first_output=&state->x;
    first_start=start_x;
    first_end=(s16)end_x;
    __asm__("" : "+r"(first_output), "+r"(first_start), "+r"(first_end));
    step_duration=(s16)time;
    __asm__("" : "+r"(step_duration));
    InitStep(first_output,first_start,0,first_end,step_duration);
    first_output=&state->z;
    first_start=start_z;
    __asm__("" : "+r"(first_output), "+r"(first_start));
    InitStep(first_output,first_start,0,(s16)end_z,step_duration);
    state->direction_x=state->x.target-state->x.value<0?-1:1;
    state->direction_z=state->z.target-state->z.value<0?-1:1;
    SetActorMode(state->actor,1,(s8)state->mode,0);
    ConfigureActorSequence(state->actor,0,2);
    {
        s32 sequence=QueryActorSequence(state->actor);
        state->sequence=sequence;
        if((u8)sequence)state->sequence=sequence-1;
    }
}
__asm__(".global IntegerSqrt\n.thumb_set IntegerSqrt,0x08141899\n.global DivideSigned\n.thumb_set DivideSigned,0x081426b9\n.global DivideWide\n.thumb_set DivideWide,0x08142281\n.global InitStep\n.thumb_set InitStep,0x08007621\n.global SetActorMode\n.thumb_set SetActorMode,0x0809836d\n.global ConfigureActorSequence\n.thumb_set ConfigureActorSequence,0x0809a571\n.global QueryActorSequence\n.thumb_set QueryActorSequence,0x0809a53d");
