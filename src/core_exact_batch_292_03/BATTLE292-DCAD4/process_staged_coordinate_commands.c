typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

struct CommandSeed {
    const u16 *unit_record;
    u8 command;
    u8 post_wait;
    s16 mode;
    u16 remaining;
};
struct CommandControl {
    u16 state;
    u16 reserved2;
    const struct CommandSeed *seed;
    u8 reserved8[12];
    u16 options;
};
struct CommandStage {
    const u16 *unit_record;
    u8 command;
    u8 post_wait;
    s16 mode;
    u16 remaining;
    u16 options;
};
extern void RequestRecordMode0(const u16 *,s32);
extern void RequestRecordMode1(const u16 *,s32);
extern void RequestRecordCommand21(const u16 *);
extern void RequestRecordCommand(const u16 *,u32);
extern void DispatchEnabledDefinition(u16);
extern void RouteDefinitionRequest(s32,s32);
asm(".global RequestRecordMode0\n.thumb_set RequestRecordMode0,0x080dd249\n"
    ".global RequestRecordMode1\n.thumb_set RequestRecordMode1,0x080dd289\n"
    ".global RequestRecordCommand21\n.thumb_set RequestRecordCommand21,0x080dd305\n"
    ".global RequestRecordCommand\n.thumb_set RequestRecordCommand,0x080dd2c9\n"
    ".global DispatchEnabledDefinition\n.thumb_set DispatchEnabledDefinition,0x08141521\n"
    ".global RouteDefinitionRequest\n.thumb_set RouteDefinitionRequest,0x08141571\n");
int ProcessStagedCoordinateCommands(void *unused,struct CommandControl *control,
                                    struct CommandStage *stage)
    __asm__("RemainingBand43_000DCAD4");
int ProcessStagedCoordinateCommands(void *unused,struct CommandControl *control,
                                    struct CommandStage *stage)
{
    const struct CommandSeed *seed;
    s32 command;
    register u32 selector __asm__("r6");
    u32 options;
    register u32 mask __asm__("r0");
    switch(control->state) {
    case 0:
        seed=control->seed;
        stage->unit_record=seed->unit_record;
        stage->command=seed->command;
        stage->mode=seed->mode;
        stage->remaining=seed->remaining;
        stage->post_wait=seed->post_wait;
        stage->options=control->options;
        break;
    case 1:
        break;
    case 256:
        if(stage->remaining) {
            stage->remaining--;
            break;
        }
        command=stage->command;
        switch(command) {
        case 0:
            RequestRecordMode0(stage->unit_record,stage->mode);
            break;
        case 1:
            RequestRecordMode1(stage->unit_record,stage->mode);
            break;
        case 21:
            selector=0;
            /* Actual DCB50 initializes the preserved selector in R6 before
             * command submission; retain that initialized live value. */
            asm("" : "+r" (selector));
            RequestRecordCommand21(stage->unit_record);
            options=stage->options;
            if(!(options&1)) {
                if(options&2)
                    selector=1;
                else {
                    /* DCB6E/70 defines mask4 then destructively ANDs R0. */
                    mask=4;
                    asm("" : "+r" (mask));
                    mask &= options;
                    asm("" : "+r" (mask));
                    if(mask)
                        selector=2;
                    if(selector==0)
                        goto default_definition;
                }
                RouteDefinitionRequest(selector,141);
                break;
            default_definition:
                DispatchEnabledDefinition(141);
            }
            break;
        default:
            RequestRecordCommand(stage->unit_record,command);
            break;
        }
        if(stage->post_wait) {
            /* DCB9A is a second physical byte read, distinct from DCB94.
             * Retain that observed read here; RAM, not an MMIO assertion. */
            stage->remaining=*(volatile u8 *)&stage->post_wait;
            control->state++;
            break;
        }
        goto completed;
    case 257:
        stage->remaining--;
        if(stage->remaining)
            break;
    completed:
        control->state=2;
        break;
    }
    return 0;
}
