typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct Particle Particle;
typedef struct {u16 phase;}Event;
typedef struct {Particle **slot;u32 x_q8,y_q8;s32 velocity_x,velocity_y;}Motion;
typedef struct {u16 time,spawned;u8 angle,unknown5;u16 angle_step;Particle *handles[30];Motion motions[30];}Work;
typedef struct {u8 kind,velocity;u16 time;s16 x,y;}SpawnRow;
typedef struct {s16 x,y;}Velocity;
extern const SpawnRow SpawnRows[] asm("0x08398c78");
extern const Velocity Velocities[] asm("0x08398d68");
extern void RemoveParticles(Particle**,u32) asm("0x080d5f75");
extern u32 FindParticleSlot(Particle**,u32) asm("0x080d5fa5");
extern Particle *CreateParticle(const void*,u32,s32,s32,u32,u32,u32,u32) asm("0x080d5cc1");
extern u32 SineValue(u8) asm("0x08007a4d");
extern void SetParticlePosition(Particle*,s16,s16,u32) asm("0x080107d5");

s32 RemainingBand43_000EABE0(void *unused,Event *event,Work *work)
{
 s32 phase=event->phase;
 switch(phase){
 case 0:work->angle_step=2;break;
 case 1:RemoveParticles(work->handles,30);break;
 case 256:{
  u8 index;
  u16 wobble;
  if(work->spawned<=29){
   for(index=0;index<=29;index++){
    register const SpawnRow *table asm("r0")=SpawnRows;
    const SpawnRow *row;
    asm volatile("" : "+r"(table));
    row=(const SpawnRow*)((u32)index*8+(u32)table);
    if(row->time==work->time){
     u16 raw_slot=(u16)FindParticleSlot(work->handles,30);
     s32 slot;
     Particle *particle;
     register Motion *motion asm("r3");
     particle=CreateParticle((void*)0x084f7174,row->kind,row->x,row->y,1017,6,1,0);
     slot=(s16)raw_slot;
     work->handles[slot]=particle;
     motion=&work->motions[slot];
     asm volatile("" : "+r"(motion));
     motion->slot=&work->handles[slot];
     motion->x_q8=(u32)(s32)row->x<<8;
     motion->y_q8=(u32)(s32)row->y<<8;
     motion->velocity_x=Velocities[((volatile const u8*)row)[1]].x;
     motion->velocity_y=Velocities[((volatile const u8*)row)[1]].y;
     ++work->spawned;
    }
   }
  }
  wobble=(s16)SineValue(work->angle)>>4;
  work->angle+= ((u8*)&work->angle_step)[0];
  for(index=0;index<=29 && work->handles[index]!=0;index++){
   Motion *motion=&work->motions[index];
   u16 x,y;
   motion->x_q8+=motion->velocity_x;
   motion->y_q8+=motion->velocity_y;
   x=(motion->x_q8<<8)>>16;
   y=(motion->y_q8<<8)>>16;
   x=(u16)(x+(work->time>>8));
   if((s16)x>239){motion->x_q8=(u32)-2048;x=(u16)-8;}
   if((s16)y>159){motion->y_q8=(u32)-2048;y=(u16)-8;}
   {
    Particle *particle=work->handles[index];
    s32 screen_x=(s16)x;
    s32 displacement=(s16)wobble;
    asm volatile("" : "+r"(screen_x), "+r"(displacement) : "r"(particle));
    SetParticlePosition(particle,(s16)(screen_x+displacement),(s16)y,0);
   }
  }
  ++work->time;
  break;
 }
 }
 return 0;
}
