typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct Task;
struct LegEvent {
    u16 state, unknown02;
    const u16 *first_point, *second_point;
    u8 *status;
    u32 unknown16;
    u16 ordinal, unknown22;
    u32 unknown24;
};
struct LegPayload {
    u16 delay;
    u8 direction, ordinal;
    u8 *status;
    void *primary, *secondary;
    u16 horizontal_values[10], vertical_values[10];
    u16 start_x, start_y, end_x, end_y;
    struct Task *transition, *auxiliary;
};
/* Only x/y/z are read by the synchronous transition initialization. */
struct Point3 {
    u32 x:16, y:16;
    u32 z:16, reserved:16;
};
typedef char PayloadSize72[sizeof(struct LegPayload)==72?1:-1];
typedef char EventSize28[sizeof(struct LegEvent)==28?1:-1];
typedef char PointSize8[sizeof(struct Point3)==8?1:-1];
typedef char EndOffset60[(u32)&((struct LegPayload*)0)->end_x==60?1:-1];
extern u32 GetDeltaAngle(s16,s16);
/* Full register arguments at these sites; the retained creator consumes LOW16/8. */
extern void *CreateLegResource(const void*,u32,s32,s32,u32,u32,u32);
extern void SetLegOption(void*,u8);
extern void SetLegSecondaryOption(void*,u8);
extern void SetLegHidden(void*,u8);
extern void SetLegAnimation(void*,u32);
extern void ClearLegResourceFlag(void*);
extern struct Task *CreatePointTransition(void*,const struct Point3*,const struct Point3*,u32,void*,void*,void*,u16,struct Task*);
extern u32 IsTransitionReady(struct Task*);
extern u32 IsTransitionComplete(struct Task*);
extern u32 RequestTransitionAdvance(struct Task*);
extern struct Task *PollTransition(struct Task*);
extern struct Task *CreateLegAuxiliary(const void*,u8,u16,u16,struct Task*);
extern void *PollLegResource(void*);
extern void RemoveLegResource(void*);
extern const u8 gLegPrimaryDefinition[],gLegSecondaryDefinition[],gLegAuxiliarySequence[];
extern const u8 gLegOptions[],gLegSecondaryOptions[],gLegAnimations[];

u32 AdvanceAbility222Leg(struct Task *task,struct LegEvent *event,struct LegPayload *leg)
{
    struct Point3 first_point, second_point;
    switch(event->state) {
    case 0: {
        const u16 *point=event->first_point;
        u8 *status;
        leg->start_x=point[0];
        leg->start_y=point[1];
        point=event->second_point;
        leg->end_x=point[0];
        leg->end_y=point[1];
        status=event->status;
        leg->status=status;
        leg->ordinal=event->ordinal;
        *status=0;
        break;
    }
    case 1:
        break;
    case 256: {
        s32 delta_x=leg->end_x-leg->start_x;
        s32 delta_y=leg->end_y-leg->start_y;
        u32 angle=GetDeltaAngle((s16)delta_x,(s16)delta_y);
        leg->direction=(u16)angle>>12;
        leg->primary=CreateLegResource(gLegPrimaryDefinition,0,(s16)leg->start_x,
                                      (s16)leg->start_y,915,6,0);
        SetLegOption(leg->primary,gLegOptions[leg->direction]);
        SetLegSecondaryOption(leg->primary,gLegSecondaryOptions[leg->direction]);
        SetLegHidden(leg->primary,0);
        ++event->state;
        break;
    }
    case 257: {
        u32 duration;
        first_point.x=leg->start_x;
        first_point.y=leg->start_y;
        first_point.z=0;
        second_point.x=leg->end_x;
        second_point.y=leg->end_y;
        second_point.z=0;
        duration=10;
        if(leg->ordinal==0 || leg->ordinal==3)
            duration=5;
        leg->transition=CreatePointTransition(&leg->primary,&first_point,&second_point,
                          duration,leg->horizontal_values,leg->vertical_values,0,1,task);
        ++event->state;
        break;
    }
    case 258:
        if((u8)IsTransitionReady(leg->transition)!=0) {
            *leg->status=1;
            ++event->state;
        }
        break;
    case 259:
        if(*leg->status!=2)
            break;
        SetLegHidden(leg->primary,1);
        SetLegAnimation(leg->primary,gLegAnimations[leg->direction]);
        RequestTransitionAdvance(leg->transition);
        ++event->state;
        break;
    case 260: {
        u32 flags, parity;
        u8 ordinal;
        if((u8)IsTransitionComplete(leg->transition)==0)
            break;
        SetLegAnimation(leg->primary,gLegAnimations[leg->direction]+5);
        ordinal=leg->ordinal;
        parity=ordinal&1;
        flags=8;
        if(parity)
            flags=16;
        if(ordinal!=3) {
            leg->secondary=CreateLegResource(gLegSecondaryDefinition,2,
                            (s16)(leg->end_x-1),(s16)(leg->end_y+4),873,6,0);
            leg->auxiliary=CreateLegAuxiliary(gLegAuxiliarySequence,1,flags|4,0,task);
        }
        leg->delay=2;
        ++event->state;
        break;
    }
    case 261:
        --leg->delay;
        if(leg->delay!=0)
            break;
        SetLegAnimation(leg->primary,0);
        ClearLegResourceFlag(leg->primary);
        *leg->status=3;
        leg->delay=2;
        ++event->state;
        break;
    case 262:
        if(leg->delay!=0) {
            --leg->delay;
            if(leg->delay!=0)
                break;
        }
        leg->transition=PollTransition(leg->transition);
        if(leg->transition!=0)
            break;
        leg->secondary=PollLegResource(leg->secondary);
        if(leg->secondary!=0)
            break;
        RemoveLegResource(leg->primary);
        leg->primary=0;
        *leg->status=4;
        event->state=2;
        break;
    }
    return 0;
}
asm(".global GetDeltaAngle\n.thumb_set GetDeltaAngle,0x8141861\n");
asm(".global CreateLegResource\n.thumb_set CreateLegResource,0x80d5dd5\n");
asm(".global SetLegOption\n.thumb_set SetLegOption,0x8011119\n");
asm(".global SetLegSecondaryOption\n.thumb_set SetLegSecondaryOption,0x8011121\n");
asm(".global SetLegHidden\n.thumb_set SetLegHidden,0x801115d\n");
asm(".global SetLegAnimation\n.thumb_set SetLegAnimation,0x8011015\n");
asm(".global ClearLegResourceFlag\n.thumb_set ClearLegResourceFlag,0x8011199\n");
asm(".global CreatePointTransition\n.thumb_set CreatePointTransition,0x80d6285\n");
asm(".global IsTransitionReady\n.thumb_set IsTransitionReady,0x80d63c9\n");
asm(".global IsTransitionComplete\n.thumb_set IsTransitionComplete,0x80d6479\n");
asm(".global RequestTransitionAdvance\n.thumb_set RequestTransitionAdvance,0x80d5c21\n");
asm(".global PollTransition\n.thumb_set PollTransition,0x80d6531\n");
asm(".global CreateLegAuxiliary\n.thumb_set CreateLegAuxiliary,0x80dfd8d\n");
asm(".global PollLegResource\n.thumb_set PollLegResource,0x8011485\n");
asm(".global RemoveLegResource\n.thumb_set RemoveLegResource,0x8011429\n");
asm(".global gLegPrimaryDefinition\n.set gLegPrimaryDefinition,0x8502a10\n");
asm(".global gLegSecondaryDefinition\n.set gLegSecondaryDefinition,0x84ff654\n");
asm(".global gLegAuxiliarySequence\n.set gLegAuxiliarySequence,0x839f26c\n");
asm(".global gLegOptions\n.set gLegOptions,0x839f2a4\n");
asm(".global gLegSecondaryOptions\n.set gLegSecondaryOptions,0x839f2b4\n");
asm(".global gLegAnimations\n.set gLegAnimations,0x839f294\n");
