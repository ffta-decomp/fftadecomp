typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Parameters {u16 x0,y0,x1,y1,height;u8 direction;u8 pad11;u16 count;u8 pad14[2];void *x,*y;};
struct Event {u16 state;u8 pad2[2];struct Parameters *parameters;u8 rest[20];};
extern u32 ArcTask(struct Task *,struct Event *,void *);
extern struct Task *CreateTask(u32 (*)(struct Task *,struct Event *,void *),u16,struct Event *,struct Task *);
__asm__(".global ArcTask\n.thumb_set ArcTask, 0x080dff8d\n.global CreateTask\n.thumb_set CreateTask, 0x08005b6d");
struct Task *RemainingBand43_000E0730(u16 x0,u16 y0,u16 x1,u16 y1,u16 height,u8 direction,u16 count,void *x,void *y,struct Task *parent)
{
 struct Event event;struct Parameters parameters;
 parameters.x0=x0;parameters.y0=y0;parameters.x1=x1;parameters.y1=y1;
 parameters.height=height;parameters.direction=direction;parameters.count=count;
 parameters.x=x;parameters.y=y;event.parameters=&parameters;
 return CreateTask(ArcTask,96,&event,parent);
}
