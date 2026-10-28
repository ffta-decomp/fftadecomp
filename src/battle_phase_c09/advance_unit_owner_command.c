/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct OwnerRecord { void *unit; u8 prefix[27]; s8 value; };
struct Controller { struct OwnerRecord *owner; void *command; u16 state; u16 depth; u16 stack[0]; };
extern void BeginController(void);
extern u8 ControllerReady(void);
extern u32 PollControllerFirst(void);
extern void BeginControllerFinal(void);
extern u32 PollControllerFinal(void);
extern void *CreateControllerCommand(u32 id, u32 zero, u32 argument);
extern u8 CommandReady(void *command);
extern void ReleaseCommand(void *command);
extern void SetUnitState(void *unit, u8 value);
extern void ApplyOwnerState(struct OwnerRecord *owner, u32 mode, int value, u32 zero);

asm(".global BeginController\n.thumb_set BeginController,0x80d376d\n.global ControllerReady\n.thumb_set ControllerReady,0x80d37f9\n.global PollControllerFirst\n.thumb_set PollControllerFirst,0x80d39b1\n.global BeginControllerFinal\n.thumb_set BeginControllerFinal,0x80d37ad\n.global PollControllerFinal\n.thumb_set PollControllerFinal,0x80d37c5\n.global CreateControllerCommand\n.thumb_set CreateControllerCommand,0x80d3509\n.global CommandReady\n.thumb_set CommandReady,0x80d3879\n.global ReleaseCommand\n.thumb_set ReleaseCommand,0x80d3865\n.global SetUnitState\n.thumb_set SetUnitState,0x80cdfc1\n.global ApplyOwnerState\n.thumb_set ApplyOwnerState,0x809836d");
u32 AdvanceUnitOwnerCommandController(struct Controller *controller)
{
    u32 ready;
    switch (controller->state) {
    case 0:
        BeginController();
        controller->state = 1;
        break;
    case 1:
        if (!ControllerReady()) break;
        ready = PollControllerFirst();
        goto test_completion;
    case 4:
        controller->command = CreateControllerCommand(360, 0, (u32)controller->owner);
        goto command_created;
    case 2:
        controller->command = CreateControllerCommand(342, 0, 1);
        goto command_created;
    case 3:
        controller->command = CreateControllerCommand(343, 0, 1);
    command_created:
        controller->state = 7;
        break;
    case 7:
        if (!CommandReady(controller->command)) break;
        ReleaseCommand(controller->command);
        controller->command = 0;
        goto pop_state;
    case 5:
        BeginControllerFinal();
        controller->state = 6;
        break;
    case 6:
        ready = PollControllerFinal();
    test_completion:
        if (!(u8)ready) break;
    pop_state:
        controller->state = controller->stack[--controller->depth];
        break;
    case 8:
        SetUnitState(controller->owner->unit, 0);
        ApplyOwnerState(controller->owner, 10, controller->owner->value, 0);
        return 0;
    }
    return 1;
}
