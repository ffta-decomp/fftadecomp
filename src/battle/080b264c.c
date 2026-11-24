#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
struct Actor {u8 pad0[8];u16 x,height,z;u8 pad14[17];s8 direction;u8 pad32[16];u32 flags;u8 pad52[32];void *primary;};
struct Particle {s32 target_x,target_y,x,y,angle,remaining,threshold;void *sprite;u16 scale_x,scale_y,attribute;u8 mode,flags;};
struct Vertical {s32 velocity,current,target;};
struct Action {
    struct Actor *actor;s32 velocity,height,target;u8 pad16[12];struct Particle *pool;u16 capacity,countdown;
    u8 pad36[22];u16 hit_sound;u8 pad60[2];s8 direction,cooldown;u8 flags,pad65[179];
    s16 effect_x,effect_height,effect_z;u8 pad250[2],effect_a,effect_b,pad254[2];
    u16 feedback_x,feedback_y,feedback_z;u8 feedback_mode,pad263[43];s8 dx,dz;u8 pad308[2];s16 target_x,target_z;u8 pad314[2];u16 state;
};
typedef void (*HandleRoutine)(void*,u32,u32,u32,u32,u32);
extern HandleRoutine const gHandleRoutine;
extern void AdvanceStep(struct Particle*);
extern u32 Random(void);
extern s32 SignedRemainder(s32,s32);
extern void Draw(void*,s32,s32,u32,s32,s32,u32,s32,u32,s32,s32,u32,s32);
extern void Project(s16,s16,s16,s16*,s16*);
extern void Emit(void*,s16,s16,s16,u32,u32);
extern void Cue(u32);
extern void Animate(struct Actor*,u16,s8,u16);
extern void ChangeFlags(struct Actor*,u16,u16);
extern u32 PollTask(void*);
extern void PublishCoordinates(void*,void*);
extern void DirectionStep(s8,s8*,s8*);
extern void *Allocate(u32);
extern void Free(void*);
extern void Clear(void*,u32,void*);
extern s32 MoveActor(void*,s32);
extern s32 PendingCode(struct Actor*);
extern u32 PollHandles(struct Actor*);
extern struct Particle *AdmitParticle(struct Particle*,s32,s32,s32,s32);
extern struct Particle *AdmitDirectedParticle(struct Particle*,s32,s32,s32,s32,s32);
extern s32 CellPolicy(struct Actor*,s32,s32);
#define RANDOM_MOD(n) SignedRemainder((s16)Random(),(n))
#define SHADOW ((volatile u8*)0x03000940)
#define CLEAR_CALLBACK (*(void**)0x0836D4B8)
int CoreRegion_000B264C(struct Action *action,struct Actor *other,void *task,void *sink)
{
    int pending=0;
    u8 *flags;
    register u32 countdown_snapshot asm("r1");
    if(action->pool!=0) {
        u16 capacity=action->capacity;
        struct Particle *particle=action->pool;
        s8 *cooldown=&action->cooldown;
        if(pending<capacity) {
            register int remaining asm("r10")=capacity;
            asm("" : "+h"(remaining));
            do {
            if(particle->remaining==0)particle->sprite=0;
            else if(particle->sprite!=0) {
                int x,y,target_x,target_y,dx,dy;
                register int alpha asm("r5");
                u32 scale_x;
                AdvanceStep(particle);
                x=particle->x>>8;y=particle->y>>8;
                target_x=particle->target_x>>8;target_y=particle->target_y>>8;
                if(target_x<0 || target_y<0 || target_x>239 || target_y>159) {
                    if(x< -8 || y< -8 || x>239 || y>159){particle->sprite=0;goto next_particle;}
                } else {
                    dx=target_x-x;if(dx<0)dx=-dx;
                    dy=target_y-y;if(dy<0)dy=-dy;
                    {
                        register int distance asm("r1")=dx;
                        register int shifted asm("r0")=dy;
                        asm volatile("add %0, %0, %1\n\tlsl %1, %0, #8\n\tasr %0, %1, #1"
                                     : "+l"(distance), "+l"(shifted) : : "cc");
                        if(distance<=particle->threshold)particle->remaining=0;
                    }
                }
                {
                    x=particle->x>>8;y=particle->y>>8;
                    scale_x=particle->scale_x-32;
                    particle->scale_x=scale_x;particle->scale_y-=32;
                    if((u16)scale_x<=127)particle->scale_x=128;
                    if(particle->scale_y<=255)particle->scale_y=256;
                    alpha=particle->angle;asm("" : "+l"(alpha));alpha=-alpha;if(alpha>255)alpha-=255;
                    Draw(particle->sprite,x,y,particle->flags,0,0,particle->attribute,2,particle->mode,(s16)particle->scale_x,(s16)particle->scale_y,({register u32 angle_arg asm("r1");asm volatile("lsl %0, %1, #24\n\tlsr %0, %0, #16" : "=l"(angle_arg) : "l"(alpha) : "cc");angle_arg;}),1);
                }
            }
        next_particle:
            remaining--;particle++;
            }while(remaining!=0);
        }
        if(*cooldown>0){(*cooldown)--;pending=1;}
        else {
            s16 projected_x,projected_y;
            register struct Particle *scan_particle asm("r5");
            register int index asm("r6");
            goto scan_particles;
        hit_particle:
            action->effect_x=other->x+RANDOM_MOD(17);
            action->effect_height=other->height+RANDOM_MOD(17)+16;
            action->effect_z=other->z+RANDOM_MOD(17);
            action->effect_a=(u8)pending;action->effect_b=(u8)pending;
            Emit(sink,action->effect_x,action->effect_height,action->effect_z,action->effect_a,pending);
            *cooldown=8;Cue(action->hit_sound);action->flags|=16;
            Animate(other,5,other->direction,0);ChangeFlags(other,0,32768);
            goto pool_done;
        scan_particles:
            Project(other->x,other->height,other->z,&projected_x,&projected_y);
            projected_y-=8;
            scan_particle=action->pool;
            asm("" : "+l"(scan_particle));
            index=0;
            asm("" : "+l"(index));
            if(index<action->capacity)do {
                if(scan_particle->sprite) {
                    register int dx asm("r2");
                    register int dy asm("r0");
                    register s32 scaled_x asm("r1");
                    register u32 shifted_y asm("r0");
                    register u32 projected_y_high asm("r3");
                    register int hit_pending asm("r2");
                    scaled_x=(s32)((u32)scan_particle->x<<8);
                    shifted_y=(u32)scan_particle->y<<8;
                    asm("" : "+l"(shifted_y));
                    projected_y_high=shifted_y>>16;
                    asm("" : "+l"(scaled_x), "+l"(projected_y_high));
                    hit_pending=1;
                    asm("" : "+l"(hit_pending));
                    pending=hit_pending;
                    dx=(scaled_x>>16)-({
                        register int x_address asm("r0")=(int)&projected_x;
                        register int zero_offset asm("r2")=0;
                        asm volatile("ldrsh %0, [%0, %2]" : "+l"(x_address) : "m"(*(const s16*)x_address), "l"(zero_offset));
                        x_address;
                    });
                    asm("" : "+l"(dx));
                    if(dx<0)dx=-dx;
                    dy=(s32)(projected_y_high<<16);
                    asm("" : "+l"(dy));
                    dy=dy>>16;
                    asm("" : "+l"(dy));
                    dy=dy-projected_y;
                    asm("" : "+l"(dy));
                    if(dy<0)dy=-dy;
                    if(dx+dy<=15)goto hit_particle;
                }
                {
                    register u32 shifted_index asm("r0")=(u32)index<<16;
                    register u32 increment asm("r6")=0x10000;
                    asm("" : "+l"(shifted_index), "+l"(increment));
                    shifted_index+=increment;
                    scan_particle++;
                    index=shifted_index>>16;
                }
            }while((s16)index<action->capacity);
        }
    }
  pool_done:
    {
        register u8 *flags_base asm("r2")=&action->flags;
        register u32 flags_byte asm("r1");
        register u32 flags_mask asm("r0");
        flags_byte=*flags_base;
        asm("" : "+l"(flags_byte));
        flags_mask=flags_byte&16;
        asm("" : "+l"(flags_base), "+l"(flags_mask));
        flags=flags_base;
        if(flags_mask && (u8)PollTask(task)) {
        action->feedback_x=2;action->feedback_y=2;action->feedback_z=2;action->feedback_mode=6;
            PublishCoordinates(task,&action->feedback_x);*flags&=239;
        }
    }
    switch(action->state) {
    case 0: {
        int height;
        {
            register u32 old_flags asm("r1")=*flags;
            register u32 flag_bit asm("r0")=2;
            asm("" : "+l"(old_flags), "+l"(flag_bit));
            flag_bit|=old_flags;
            asm("" : "+l"(flag_bit));
            *flags=flag_bit;
        }
        action->actor->flags&=~1;
        DirectionStep(action->direction,&action->dx,&action->dz);
        action->actor->x=((((s16)other->x>>5)-action->dx)<<5)+16;
        action->actor->z=((((s16)other->z>>5)-action->dz)<<5)+16;
        action->target_x=((((s16)other->x>>5)-action->dx*4)<<5)+16;
        action->target_z=((((s16)other->z>>5)-action->dz*4)<<5)+16;
        action->dx=({register s32 signed_dx asm("r0")=action->dx;asm("" : "+l"(signed_dx));-signed_dx;});action->dz=({register s32 signed_dz asm("r0")=action->dz;asm("" : "+l"(signed_dz));-signed_dz;});
        action->target=(s16)other->height<<8;
        height=((s16)other->height-48)<<8;
        action->height=height;action->velocity=2304;action->actor->height=height>>8;
        action->pool=Allocate(2560);Clear(action->pool,2560,CLEAR_CALLBACK);action->capacity=64;
        Animate(action->actor,3,action->direction,0);action->cooldown=0;action->state=1;
        break;
    }
    case 1: {
        struct Vertical *vertical=(struct Vertical*)&action->velocity;
        int velocity,limit,falling;
        /* Actual context+4 base/owner alias graph; AE7D8 cause2 restored this
         * complete native read/store/reload sequence. */
        asm("" : "+r"(vertical));
        vertical->current+=action->velocity;
        velocity=action->velocity-153;action->velocity=velocity;limit=vertical->target;
        if(limit>=vertical->current && velocity<=0){vertical->current=limit;falling=0;}else falling=1;
        action->actor->height=action->height>>8;
        if(falling==1)MoveActor(action,2);
        else {
            Animate(action->actor,4,action->direction,0);
            gHandleRoutine(action->actor->primary,1,0,0,0,0);
            action->state=2;*flags&=253;
            {
                register volatile u8 *shadow_base asm("r2")=SHADOW;
                register volatile u8 *shadow_cursor asm("r1");
                asm("" : "+l"(shadow_base));
                shadow_cursor=shadow_base+74;
                asm("" : "+l"(shadow_cursor));
                (void)*shadow_cursor;*shadow_cursor=64;
                shadow_cursor++;
                (void)*shadow_cursor;*shadow_cursor=63;
                shadow_cursor++;
                (void)*shadow_cursor;*shadow_cursor=16;
                {
                    register volatile u8 *shadow_last asm("r0")=shadow_base+77;
                    asm("" : "+l"(shadow_last));
                    (void)*shadow_last;
                    asm("" : "+l"(shadow_last));
                    *shadow_last=0;
                }
            }
            action->effect_x=action->actor->x;action->effect_height=action->actor->height;action->effect_z=action->actor->z;
            action->effect_a=7;action->effect_b=0;
            Emit(sink,action->effect_x,action->effect_height,action->effect_z,action->effect_a,0);
            action->countdown=24;Cue(292);
        }
        break;
    }
    case 2: {
        register volatile u8 *shadow_base asm("r8")=SHADOW;
        register volatile u8 *shadow_cursor asm("r6");
        asm("" : "+h"(shadow_base));
        shadow_cursor=shadow_base+77;
        asm("" : "+l"(shadow_cursor));
        if(*shadow_cursor<=15) {
            u32 next=*shadow_cursor+1;
            (void)*shadow_cursor;*shadow_cursor=next;
        } else if(({register int offset asm("r2");register int signed_count asm("r0");countdown_snapshot=action->countdown;asm("" : "+l"(countdown_snapshot));offset=34;asm volatile("ldrsh %0, [%2, %3]" : "=l"(signed_count) : "m"(action->countdown), "l"(action), "l"(offset));signed_count;})>0)goto decrement_countdown;
        else {
            Animate(action->actor,3,action->direction,0);Cue(224);Cue(242);
            gHandleRoutine(action->actor->primary,0,0,0,0,0);
            action->countdown=64;
            {
                register volatile u8 *shadow_76 asm("r1")=shadow_base+76;
                asm("" : "+l"(shadow_76));
                (void)*shadow_76;
                asm("" : "+l"(shadow_76));
                *shadow_76=12;
            }
            (void)*shadow_cursor;*shadow_cursor=6;
            action->state=3;
            {
                register u32 old_flags asm("r1")=*flags;
                register u32 flag_bit asm("r0")=16;
                asm("" : "+l"(old_flags), "+l"(flag_bit));
                flag_bit|=old_flags;
                asm("" : "+l"(flag_bit));
                *flags=flag_bit;
            }
            action->hit_sound=137;action->cooldown=0;
        }
        break;
    }
    case 3: {
        struct Actor *actor=action->actor;
        u32 bits=actor->flags^1;
        actor->flags=bits;
        if((s16)action->countdown>0) {
            register u32 first asm("r4");
            register u32 second asm("r5");
            int x,y,z;
            action->countdown--;
            first=Random();asm("" : "+l"(first));second=Random();asm("" : "+l"(second));x=(s16)action->actor->x;
            x+=(s16)SignedRemainder(({first=(s16)first;asm("" : "+l"(first));(s32)first;}),17);x-=(s16)SignedRemainder(({second=(s16)second;asm("" : "+l"(second));(s32)second;}),17);
            first=Random();asm("" : "+l"(first));second=Random();asm("" : "+l"(second));y=(s16)action->actor->height;
            y+=(s16)SignedRemainder(({first=(s16)first;asm("" : "+l"(first));(s32)first;}),17);y-=(s16)SignedRemainder(({second=(s16)second;asm("" : "+l"(second));(s32)second;}),17);y+=16;
            first=Random();asm("" : "+l"(first));second=Random();asm("" : "+l"(second));z=(s16)action->actor->z;
            z+=(s16)SignedRemainder(({first=(s16)first;asm("" : "+l"(first));(s32)first;}),17);z-=(s16)SignedRemainder(({second=(s16)second;asm("" : "+l"(second));(s32)second;}),17);
            AdmitParticle(action->pool,action->capacity,x,y,z);
        } else {
            actor->flags=bits&~1;action->countdown=32;Cue(243);action->state=4;
        }
        break;
    }
    case 4:
        /* The second real H34 observation needs a low-register displacement.
         * Pass that actual constant to reload instead of defining a fixed R5
         * local before it: the emitted LDRSH still performs the same read. */
        if(({register int signed_count asm("r0");countdown_snapshot=action->countdown;asm("" : "+l"(countdown_snapshot));asm volatile("ldrsh %0, [%2, %3]" : "=l"(signed_count) : "m"(action->countdown), "l"(action), "l"(34));signed_count;})>0)goto decrement_countdown;
        Animate(action->actor,7,action->direction,0);action->state=5;
        break;
    case 5:
        if(PendingCode(action->actor)==0) {
            Cue(221);Cue(242);action->state=6;action->countdown=64;action->hit_sound=123;
        }
        break;
    case 6:
        action->actor->flags^=1;
        if(PollHandles(action->actor))action->actor->flags|=1;
        if((s16)action->countdown>0) {
            action->countdown--;
            AdmitDirectedParticle(action->pool,action->capacity,(s16)other->x,(s16)other->height+16,(s16)other->z,0);
        } else {Cue(243);action->state=7;action->countdown=32;}
        break;
    case 7:
        if(pending==0) {
            if(({register int offset asm("r3");register int signed_count asm("r0");countdown_snapshot=action->countdown;asm("" : "+l"(countdown_snapshot));offset=34;asm volatile("ldrsh %0, [%2, %3]" : "=l"(signed_count) : "m"(action->countdown), "l"(action), "l"(offset));signed_count;})>0) {
            decrement_countdown:
                {
                    register u32 decremented asm("r0")=countdown_snapshot-1;
                    asm("" : "+l"(decremented));
                    action->countdown=decremented;
                }
                return 1;
            }
            {
                /* The real low read base is a compiler-visible copy of the
                 * ordinary caller object, not an opaque ASM-returned pointer.
                 * Each MEM operand names precisely the halfword read here;
                 * it is not a second instruction or a blanket memory effect. */
                register struct Actor *read_parent asm("r4")=other;
                register u32 coordinate asm("r0");
                asm("ldrh %0, [%1, #8]" : "=l"(coordinate)
                    : "l"(read_parent), "m"(other->x));
                action->effect_x=coordinate;
                asm("ldrh %0, [%1, #10]" : "=l"(coordinate)
                    : "l"(read_parent), "m"(other->height));
                action->effect_height=coordinate+80;
                asm("ldrh %0, [%1, #12]" : "=l"(coordinate)
                    : "l"(read_parent), "m"(other->z));
                action->effect_z=coordinate;
            }
            action->effect_a=4;action->effect_b=0;
            Emit(sink,action->effect_x,action->effect_height,action->effect_z,action->effect_a,pending);
            action->hit_sound=224;Cue(221);
            AdmitDirectedParticle(action->pool,action->capacity,(s16)other->x,(s16)other->height+16,(s16)other->z,1);
            action->state=9;
        }
        break;
    case 9:
        if(pending==0) {
            Free(action->pool);action->pool=0;
            action->target=CellPolicy(other,(s32)(other->x<<19)>>24,(s32)(other->z<<19)>>24)<<12;
            action->height=(s16)other->height<<8;action->velocity=-1024;action->state=8;
        }
        break;
    case 8: {
        struct Vertical *vertical=(struct Vertical*)&action->velocity;
        int velocity,limit,falling;
        asm("" : "+r"(vertical));
        vertical->current+=action->velocity;
        velocity=action->velocity-153;action->velocity=velocity;limit=vertical->target;
        if(limit>=vertical->current && velocity<=0){vertical->current=limit;falling=0;}else falling=1;
        other->height=action->height>>8;
        if(falling==0) {
            Animate(other,5,other->direction,0);
            {
                register volatile u8 *shadow_base asm("r0")=SHADOW;
                register volatile u8 *shadow_74 asm("r2");
                asm("" : "+l"(shadow_base));
                shadow_74=shadow_base+74;
                asm("" : "+l"(shadow_74));
                (void)*shadow_74;
                asm("" : "+l"(shadow_74));
                *shadow_74=0;
                shadow_base+=75;
                asm("" : "+l"(shadow_base));
                (void)*shadow_base;
                asm("" : "+l"(shadow_base));
                *shadow_base=0;
            }
            action->effect_x=other->x;action->effect_height=other->height;action->effect_z=other->z;
            action->effect_a=2;action->effect_b=0;
            Emit(sink,action->effect_x,action->effect_height,action->effect_z,action->effect_a,falling);
            return 0;
        }
        break;
    }
    }
    return 1;
}
asm(".global AdvanceStep\n.thumb_set AdvanceStep,0x08007ad1\n");
asm(".global Random\n.thumb_set Random,0x08002805\n");
asm(".global SignedRemainder\n.thumb_set SignedRemainder,0x08142951\n");
asm(".global Draw\n.thumb_set Draw,0x080018a1\n");
asm(".global Project\n.thumb_set Project,0x0801c985\n");
asm(".global Emit\n.thumb_set Emit,0x080e2c01\n");
asm(".global Cue\n.thumb_set Cue,0x08141521\n");
asm(".global Animate\n.thumb_set Animate,0x0809836d\n");
asm(".global ChangeFlags\n.thumb_set ChangeFlags,0x0809a571\n");
asm(".global PollTask\n.thumb_set PollTask,0x080d3879\n");
asm(".global PublishCoordinates\n.thumb_set PublishCoordinates,0x080e2849\n");
asm(".global DirectionStep\n.thumb_set DirectionStep,0x0809d66d\n");
asm(".global Allocate\n.thumb_set Allocate,0x08022841\n");
asm(".global Free\n.thumb_set Free,0x08022855\n");
asm(".global Clear\n.thumb_set Clear,0x0814224d\n");
asm(".global MoveActor\n.thumb_set MoveActor,0x080a9e6d\n");
asm(".global PendingCode\n.thumb_set PendingCode,0x08099c35\n");
asm(".global PollHandles\n.thumb_set PollHandles,0x08099c65\n");
asm(".global AdmitParticle\n.thumb_set AdmitParticle,0x080a96b1\n");
asm(".global AdmitDirectedParticle\n.thumb_set AdmitDirectedParticle,0x080a97ed\n");
asm(".global CellPolicy\n.thumb_set CellPolicy,0x08099c1d\n");
asm(".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n");
asm(".global gHandleRoutine\n.set gHandleRoutine,0x08394034\n");
