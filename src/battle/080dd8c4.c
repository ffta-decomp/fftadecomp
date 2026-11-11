typedef unsigned char u8;
typedef unsigned short u16;
typedef struct {void *record;u8 parameter,a,b,c;const void *descriptor;} Init;
typedef struct {unsigned unknown0;Init *data;unsigned unknown8[3];u16 delay,flags;unsigned unknown24;} Event;
extern void *CreateTask(void*,unsigned,const void*,void*);
extern void EffectTimelineCallback(void);
void *CreateBattleEffectTimeline(void *record,const void *descriptor,u8 parameter,u16 delay,u16 flags,void *parent)
{
 Init init;
 Event event;
 init.record=record;
 init.parameter=parameter;
 init.a=6;
 init.b=4;
 init.c=6;
 init.descriptor=descriptor;
 event.delay=delay;
 event.flags=flags;
 /* Original real W4 write: pinned frame40 places event.data at SP+16.
    The memory output names the exact field; input is initialized init address. */
 __asm__("str %1, [sp, #16]" : "=m"(event.data) : "l"(&init));
 return CreateTask(EffectTimelineCallback,56,&event,parent);
}
__asm__(".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n.global EffectTimelineCallback\n.thumb_set EffectTimelineCallback,0x080dc55d\n");
