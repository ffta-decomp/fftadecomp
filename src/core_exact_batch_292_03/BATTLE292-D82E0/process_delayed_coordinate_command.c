typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

struct CommandRecord {
    u16 state;
    u16 reserved2;
    const u16 *coordinates;
    u8 reserved8[12];
    u16 delay;
    u16 options;
};
struct CoordinateStage {
    s16 x;
    s16 y;
    s16 z;
    u16 reserved6;
    u16 remaining;
    u16 options;
};
extern void RequestCoordinateCommand(u32, s32, s32, s32, u32);
extern void DispatchEnabledDefinition(u16);
extern void RouteDefinitionRequest(s32, s32);
asm(".global RequestCoordinateCommand\n.thumb_set RequestCoordinateCommand,0x080a92e5\n"
    ".global DispatchEnabledDefinition\n.thumb_set DispatchEnabledDefinition,0x08141521\n"
    ".global RouteDefinitionRequest\n.thumb_set RouteDefinitionRequest,0x08141571\n");

int ProcessDelayedCoordinateCommand(void *unused, struct CommandRecord *record,
                                   struct CoordinateStage *stage)
    __asm__("RemainingBand43_000D82E0");
int ProcessDelayedCoordinateCommand(void *unused, struct CommandRecord *record,
                                   struct CoordinateStage *stage)
{
    const u16 *coordinates;
    u32 options;
    u32 selector;
    switch (record->state) {
    case 0:
        coordinates = record->coordinates;
        stage->x = coordinates[0];
        stage->y = coordinates[1];
        stage->z = coordinates[2];
        stage->remaining = record->delay + 1;
        stage->options = record->options;
        break;
    case 1:
        break;
    case 256:
        stage->remaining--;
        if (stage->remaining == 0) {
            RequestCoordinateCommand(0, stage->x, stage->y, stage->z, 21);
            options = stage->options;
            selector = 0;
            if (!(options & 1)) {
                if (options & 2)
                    selector = 1;
                else {
                    if (options & 4)
                        selector = 2;
                    if (selector == 0)
                        goto default_definition;
                }
                RouteDefinitionRequest(selector, 141);
                goto completed;
            default_definition:
                DispatchEnabledDefinition(141);
            }
        completed:
            record->state = 3;
        }
        break;
    }
    return 0;
}
