typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *first,*second;u8 opaque[8];u16 flag;} Event;
typedef struct {u8 flag,pad;s16 index,delay,x[60],y[60];u16 pad246;void *transition,*first,*second,*primary,*remnants[3],*palette;} Work;
extern void *RetailCall_080dd4c4(void*) __asm__("0x080dd4c5");
extern void RetailCall_080dbda0(void*,u16*,u16*,u16*) __asm__("0x080dbda1");
extern void *RetailCall_080d62cc(void**,const u16*,const u16*,u32,u32,u16,s16*,s16*,u16,void*) __asm__("0x080d62cd");
extern void *RetailCall_080d5dd4(const void*,u32,s32,s32,u32,u32,u32) __asm__("0x080d5dd5");
extern void RetailCall_0801121c(void*,u32) __asm__("0x0801121d");
extern void *RetailCall_080d4704(const void*,void*) __asm__("0x080d4705");
extern void RetailCall_0801bb0c(s32,s32,u32) __asm__("0x0801bb0d"),RetailCall_080d5c20(void*) __asm__("0x080d5c21");
extern void *RetailCall_081443fc(void*,const void*,u32) __asm__("0x081443fd");
extern void *RetailCall_080d6530(void*) __asm__("0x080d6531");
extern void RetailCall_08011428(void*) __asm__("0x08011429");
extern u32 RetailCall_080d5f24(void**,u32) __asm__("0x080d5f25");
extern void *RetailCall_080d4774(void*) __asm__("0x080d4775");

extern const u8 SpawnTimes[3] __asm__("0x08149ca0");
s32 RemainingBand43_000E6B10(void *parent,Event *event,Work *work)
{
 struct {
  u16 first_z,second_z;
  u16 target_x,target_y,target_z;
  u32 times_storage;
  u16 first_point[2],second_point[2];
 } scratch;
 s32 phase=event->phase,next_phase;
 register u32 raw_delay __asm__("r1");
 switch(phase){
 case 1:
  break;
 case 0:
  work->flag=event->flag;
  work->first=RetailCall_080dd4c4(event->first);
  work->second=RetailCall_080dd4c4(event->second);
  break;
 case 256:
  RetailCall_080dbda0(work->first,&scratch.first_point[0],&scratch.first_point[1],&scratch.first_z);
  RetailCall_080dbda0(work->second,&scratch.second_point[0],&scratch.second_point[1],&scratch.second_z);
  work->transition=RetailCall_080d62cc(&work->primary,scratch.first_point,scratch.second_point,-28,-28,60,work->x,work->y,0,parent);
  work->delay=62;
  {register u32 fresh_phase __asm__("r0")=event->phase; __asm__("" : "+l"(fresh_phase)); next_phase=fresh_phase+1;goto store_phase;}
 case 257:{
  s32 delay=work->delay;
  raw_delay=*(volatile u16 *)&work->delay;
  __asm__("" : "+l"(raw_delay));
  if(delay!=0)goto decrement;
  work->primary=RetailCall_080d5dd4((void*)0x084fba40,2,work->x[0],work->y[0],994,6,delay);
  RetailCall_0801121c(work->primary,1);
  if(work->flag==0)work->palette=RetailCall_080d4704((void*)0x08949764,parent);
  else work->palette=RetailCall_080d4704((void*)0x0894a384,parent);
  {
   register void *actor __asm__("r0");
   register u16 *target_x_ptr __asm__("r4");
   register u16 *target_y_ptr __asm__("r5");
   actor=work->second;
   __asm__("" : "+l"(actor));
   target_x_ptr=&scratch.target_x;
   target_y_ptr=&scratch.target_y;
   __asm__("" : "+l"(target_x_ptr), "+l"(target_y_ptr));
   RetailCall_080dbda0(actor,target_x_ptr,target_y_ptr,&scratch.target_z);
   RetailCall_0801bb0c((s16)(*target_x_ptr-120),(s16)(*target_y_ptr-96),60);
  }
  RetailCall_080d5c20(work->transition);
  work->index=0;
  {register u32 fresh_phase __asm__("r0")=event->phase; __asm__("" : "+l"(fresh_phase)); next_phase=fresh_phase+1;goto store_phase;}
 }
 case 258:{
  register u8 *times_ptr __asm__("r4")=(u8 *)&scratch.times_storage;
  u8 i;
  void *transition;
  __asm__("" : "+l"(times_ptr));
  RetailCall_081443fc(times_ptr,SpawnTimes,3);
  i=0;
  do{
   s32 index=work->index;
   if(index==times_ptr[i])work->remnants[i]=RetailCall_080d5dd4((void*)0x084fba40,3,work->x[index],work->y[index],994,6,0);
   i++;
  }while(i<=2);
  work->index=(u16)work->index+1;
  transition=RetailCall_080d6530(work->transition);
  work->transition=transition;
  if(transition==0){
   RetailCall_08011428(work->primary);
   work->primary=transition;
   {register u32 fresh_phase __asm__("r0")=event->phase; __asm__("" : "+l"(fresh_phase)); next_phase=fresh_phase+1;goto store_phase;}
  }
  break;
 }
 case 259:
  if((u8)RetailCall_080d5f24(work->remnants,3)){
   void *palette=RetailCall_080d4774(work->palette);
   work->palette=palette;
   if(palette==0){
    next_phase=2;
store_phase:
    event->phase=next_phase;
   }
  }
  break;
 }
 {
  s32 checked_delay=work->delay;
  raw_delay=*(volatile u16 *)&work->delay;
  __asm__("" : "+l"(raw_delay));
  if(checked_delay!=0){
decrement:
   {
    register u32 decremented __asm__("r0")=raw_delay-1;
    __asm__("" : "+l"(decremented));
    work->delay=decremented;
   }
  }
 }
 return 0;
}
