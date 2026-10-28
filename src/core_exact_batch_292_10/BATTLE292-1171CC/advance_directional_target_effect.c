typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[2];void *record,*action;u8 unused12[8];u16 mode,delay;u8 unused24[4];};
struct Work {u8 mode,direction;u16 delay;s16 x,y;void *actor,*record,*object;struct Task *effect;void *action;};
typedef char WorkSize[sizeof(struct Work)==28?1:-1];
extern void *ResolveRecordPosition(void*,s16*,s16*,u32);
extern void *CopyMemory(void*,const void*,u32);
extern void ReadActionPosition(void*,s16*,s16*);
extern void ProjectActor(void*,s16*,s16*,s16*);
extern void *CreatePositionedObject(const void*,u16,s16,s16,u16,u8,u8,u8);
extern void SetObjectAnimation(void*,u16);
extern struct Task *CreateRecordEffect(void*,u8,u16,struct Task*);
extern void *PollObject(void*);
extern struct Task *PollRecordEffect(struct Task*);
extern const u8 gDirectionFrames[],gDirectionAnimations[],gObjectResource[];
u32 AdvanceDirectionalTargetEffect(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_001171CC");
u32 AdvanceDirectionalTargetEffect(struct Task *task,struct Event *event,struct Work *work)
{
    u8 frames[4];
    u8 animations[4];
    s16 source_x,source_y;
    s16 actor_x,actor_y,actor_z;
    switch(event->state) {
    case 0:
        work->mode=event->mode;
        work->delay=event->delay+1;
        work->record=event->record;
        work->action=event->action;
        work->actor=ResolveRecordPosition(work->record,&work->x,&work->y,0);
        break;
    case 1:break;
    case 256:
        CopyMemory(frames,gDirectionFrames,4);
        CopyMemory(animations,gDirectionAnimations,4);
        work->delay--;
        if(work->delay!=0)break;
        ReadActionPosition(work->action,&source_x,&source_y);
        ProjectActor(work->actor,&actor_x,&actor_y,&actor_z);
        if(source_x==actor_x) {
            if(source_y<actor_z)work->direction=0;
            else work->direction=2;
        } else {
            if(source_x>actor_x)work->direction=1;
            else work->direction=3;
        }
        work->object=CreatePositionedObject(gObjectResource,frames[work->direction],work->x,work->y,942,6,1,1);
        SetObjectAnimation(work->object,animations[work->direction]);
        work->effect=CreateRecordEffect(work->record,2,0,task);
        event->state++;
        break;
    case 257:
        work->object=PollObject(work->object);
        if(work->object==0) {
            work->effect=PollRecordEffect(work->effect);
            if(work->effect==0)event->state=2;
        }
        break;
    }
    return 0;
}
__asm__(".global gDirectionFrames\n.set gDirectionFrames,0x8149f6c\n.global gDirectionAnimations\n.set gDirectionAnimations,0x8149f70\n.global gObjectResource\n.set gObjectResource,0x8502560\n.global ResolveRecordPosition\n.thumb_set ResolveRecordPosition,0x80dd749\n.global CopyMemory\n.thumb_set CopyMemory,0x81443fd\n.global ReadActionPosition\n.thumb_set ReadActionPosition,0x80d8b5d\n.global ProjectActor\n.thumb_set ProjectActor,0x80dbd79\n.global CreatePositionedObject\n.thumb_set CreatePositionedObject,0x80d5cc1\n.global SetObjectAnimation\n.thumb_set SetObjectAnimation,0x8011119\n.global CreateRecordEffect\n.thumb_set CreateRecordEffect,0x80df9e5\n.global PollObject\n.thumb_set PollObject,0x8011485\n.global PollRecordEffect\n.thumb_set PollRecordEffect,0x80dba5d\n");
