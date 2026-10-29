typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad2;void *owner;u8 pad8[12];u16 command,pad22;u32 pad24;}Event;
typedef struct {void *owner;u32 pad4;void *allocation;u8 timer,pad13,command,saved_flags;u8 copy[84];u8 display[80];}Work;
extern void *Allocate(u32) asm("0x08121b65");
extern void Release(void*) asm("0x08121b79");
extern void CopyBytes(void*,const void*,u32) asm("0x081443fd");
extern u32 ReadFlag(u32) asm("0x080c9541");
extern void WriteFlag(u32,u32) asm("0x080c9575");
extern void OpenDialog(void*,u32,u32,void*,void*,s32,s32,u32,u32,u32) asm("0x0801174d");
extern u32 PollDialog(void) asm("0x08011861");
extern void StartCopy(void*,u32,void*,u32) asm("0x08000b21");

typedef struct {volatile u16 control;u8 pad2[72];volatile u8 display_mode;u8 pad75[5];}Display;
extern Display DisplayShadow asm("0x03000940");
typedef struct {volatile u8 low:3;volatile u8 dialog_bits:2;volatile u8 high:3;}DialogFlags;
typedef struct {u8 pad0[0x2174];u16 pending;u8 pad2176[0xe4a];DialogFlags flags;}GameState;
extern GameState GameData asm("0x02000000");
typedef struct {u8 pad0[20];void *buffer;}DialogContext;
extern DialogContext DialogState asm("0x030008b0");
s32 AdvanceSceneModalCommand(void *,Event *,Work *) asm("CoreRegion_00125DE8");
s32 AdvanceSceneModalCommand(void *unused,Event *event,Work *work)
{
 s32 phase=event->phase;
 switch(phase){
 case 1:
  if(work->allocation){Release(work->allocation);work->allocation=0;}break;
 case 0:{
  Display *display;
  work->owner=event->owner;work->command=event->command;
  display=&DisplayShadow;
  CopyBytes(work->display,display,80);
  /* CONTROL |= 0x0c00 through the original read, mask and result carriers. */
  asm volatile("ldrh r1,[%1]\n\tmov r2,#192\n\tlsl r2,r2,#4\n\tmov r0,r2\n\torr r0,r1\n\tstrh r0,[%1]"
   : "+m"(*(volatile u16*)display) : "l"(display) : "r0", "r1", "r2", "cc");
  display->display_mode=display->display_mode&0xf3;
  if((u8)ReadFlag(594)){
   work->saved_flags=GameData.flags.dialog_bits;
   GameData.flags.dialog_bits=0;
  }
  break;
 }
 case 256:
  work->allocation=Allocate(1940);
  OpenDialog(work->allocation,5,work->command,(void*)0x030008b0,(void*)0x03000990,-1,-1,0,6,576);
  event->phase=257;break;
 case 257:
  if((u16)PollDialog()){
   register u32 flag_setup asm("r2")=594;
   register u32 flag_id asm("r8");
   asm("" : "+r"(flag_setup));
   flag_id=flag_setup;
   asm("" : "+r"(flag_id));
   if((u8)ReadFlag(flag_id)){
    GameState *game=&GameData;
    register DialogFlags *target asm("r3");
    asm volatile("" : "+r"(game));
    target=&game->flags;
    asm volatile("" : "+r"(target));
    /* Restore bits 3..4: (old & ~24U) | ((saved_flags & 3U) << 3). */
    asm volatile("mov r0,#3\n\tldrb r1,%1\n\tand r1,r0\n\tlsl r1,r1,#3\n\tldrb r2,[%2]\n\tmov r0,#25\n\tneg r0,r0\n\tand r0,r2\n\torr r0,r1\n\tstrb r0,[%2]"
     : "+m"(*(volatile u8*)target)
     : "m"(work->saved_flags), "l"(target) : "r0", "r1", "r2", "cc");
    WriteFlag(flag_id,0);
    {
     register u32 pending_offset asm("r2")=0x2174;
     asm("" : "+r"(pending_offset));
     *(u16*)((u8*)game+pending_offset)=0;
    }
   }
   StartCopy(work->copy,0,DialogState.buffer,640);
   work->timer=30;event->phase=258;
  }
  break;
 case 258:
  if(work->timer){work->timer--;if(work->timer)break;}
  Release(work->allocation);work->allocation=0;event->phase=259;break;
 case 259:{
  Display *display=&DisplayShadow;
  *(volatile u16*)display=*(u16*)work->display;
  display->display_mode=work->display[74];
  ((u8*)work->owner)[6]=1;event->phase=3;break;
 }
 }
 return 0;
}
