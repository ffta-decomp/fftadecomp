typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct Task Task;
typedef struct {u16 phase;}Event;
typedef struct {u16 time,unknown2;u32 x_q8,y_q8;u8 angle,unknown13;u16 angle_step;Task *auxiliary;}Work;
extern void PlaceResource(const void*,u32,u32,u32,s32,u32) asm("0x080d7221");
extern Task *CreateAuxiliary(const void*,Task*) asm("0x080d3e9d");
extern Task *PollAuxiliary(Task*) asm("0x080d3f09");
extern u32 SineValue(u8) asm("0x08007a4d");
extern void ScrollX(s16,u8) asm("0x08003509");
extern void ScrollY(s16,u8) asm("0x08003559");

s32 RemainingBand43_000EAB34(Task *parent,Event *event,Work *work)
{
 s32 phase=event->phase;
 switch(phase){
 case 0:
  PlaceResource((void*)0x088f4d48,1,3,0,0,0);
  work->auxiliary=CreateAuxiliary((void*)0x0894d6e8,parent);
  work->angle_step=2;break;
 case 1:break;
 case 256:{
  register u32 sine_work asm("r1");
  u32 x_q8,y_q8,x_bits;
  u16 y;
  s32 x,wobble;
  work->auxiliary=PollAuxiliary(work->auxiliary);
  ++work->time;
  sine_work=SineValue(work->angle);
  asm volatile("" : "+r"(sine_work));
  sine_work<<=16;
  work->angle+=((u8*)&work->angle_step)[0];
  x_q8=work->x_q8-332U;work->x_q8=x_q8;
  y_q8=work->y_q8-166U;work->y_q8=y_q8;
  x_bits=x_q8<<8;
  y=(y_q8<<8)>>16;
  x=(s32)x_bits>>16;
  wobble=(s32)sine_work>>20;
  asm volatile("" : "+r"(x), "+r"(wobble));
  ScrollX((s16)(x-wobble),3);
  ScrollY((s16)y,3);
  break;
 }
 }
 return 0;
}
