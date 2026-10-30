/* Contributed by gg; original source and attribution follow. */
/* Scene51_00127B80
   entry 0x08127B80, 68 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
struct Task;struct Command {u8 unknown0[6];u8 completed;u8 unknown7;struct Task *task;};
struct Event {u16 phase,reserved2;struct Command *owner;s32 dx,dz;u32 reserved16;u16 unit,mode,parameter,reserved26;};
typedef u32(*Callback)(struct Task*,struct Event*,void*);
extern u32 AdvanceUnitCoordinateTransition(struct Task*,struct Event*,void*);
extern struct Task *CreateUnitTransitionTask(Callback,u32,struct Event*,struct Task*);
void StartUnitCoordinateTransitionByDuration(struct Command*,s32,u32) __asm__("f_target");
void StartUnitCoordinateTransitionByDuration(struct Command *command,s32 packed_x,u32 packed_z)
{
    struct Event event;
    command->completed=0;
    event.owner=command;
    event.dx=packed_x>>16;
    event.dz=(s16)packed_z;
    event.unit=(u8)packed_x;
    event.mode=(u8)((u32)packed_x>>8);
    event.parameter=packed_z>>16;
    /* Preserve both original packed argument lifetimes across the projections. */
    __asm__("" : : "r"(packed_x), "r"(packed_z));
    CreateUnitTransitionTask(AdvanceUnitCoordinateTransition,320,&event,command->task);
}
__asm__(".global AdvanceUnitCoordinateTransition\n.thumb_set AdvanceUnitCoordinateTransition,0x8127229\n.global CreateUnitTransitionTask\n.thumb_set CreateUnitTransitionTask,0x08121b8d");
