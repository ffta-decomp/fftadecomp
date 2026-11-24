typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Parameters { u16 x0,y0,z0,x1,y1,z1,mode,count; void *x,*y,*z; };
struct Event {u16 state; unsigned char pad2[2]; struct Parameters *parameters; unsigned char rest[20];};
extern u32 CoordinateTask(struct Task *,struct Event *,void *);
extern struct Task *CreateTask(u32 (*)(struct Task *,struct Event *,void *),u16,struct Event *,struct Task *);
__asm__(".global CoordinateTask\n.thumb_set CoordinateTask, 0x080e0241\n.global CreateTask\n.thumb_set CreateTask, 0x08005b6d");
struct Task *RemainingBand43_000E077C(u16 x0,u16 y0,u16 z0,u16 x1,u16 y1,u16 z1,u16 mode,u16 count,void *x,void *y,void *z,struct Task *parent)
{
 struct Event event;
 struct Parameters parameters;
 parameters.x0=x0; parameters.y0=y0; parameters.z0=z0;
 parameters.x1=x1; parameters.y1=y1; parameters.z1=z1;
 parameters.mode=mode; parameters.count=count;
 parameters.x=x; parameters.y=y; parameters.z=z;
 event.parameters=&parameters;
 return CreateTask(CoordinateTask,76,&event,parent);
}
