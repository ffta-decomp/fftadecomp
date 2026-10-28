/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08065EF4.c
 * Original SHA-256: a8b178ddd83428d2cfa46d0743d3b67e88b3c18a2787733ff13c41bb76315887
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Command {
    u16 state;
    u16 unknown_02;
    void *argument_04;
    void *argument_08;
};

struct CommandContext {
    void *global;
    void *argument_04;
    u8 unknown_08;
    u8 flags;
    u8 unknown_0A[6];
    void *resources;
    void *graphics;
    u8 unknown_18[0xA0];
    void *argument_B8;
};

extern void *data_0200F454;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_08066C98(struct CommandContext *context);
extern void func_08068998(struct CommandContext *context);
extern void func_0806890C(struct CommandContext *context);
extern u8 func_08066D98(struct CommandContext *context);
extern void func_08068954(struct CommandContext *context);
extern u8 func_08066DC4(struct CommandContext *context);
extern void func_08061390(void);
extern void func_08066D74(struct CommandContext *context);

int func_08065EF4(void *owner, struct Command *command, struct CommandContext *context)
{
    switch (command->state) {
    case 0:
        context->argument_04 = command->argument_08;
        context->argument_B8 = command->argument_04;
        context->global = data_0200F454;
        context->resources = data_030008B0;
        context->graphics = data_03000990;
        break;
    case 1:
        break;
    case 0x100:
        func_08066C98(context);
        command->state = 0x101;
        break;
    case 0x101:
        if (context->flags & 2)
            command->state = 0x107;
        else if (context->flags & 4)
            func_08068998(context);
        break;
    case 0x102:
        func_0806890C(context);
        command->state = 0x103;
        break;
    case 0x103:
        if (func_08066D98(context))
            command->state = 0x101;
        break;
    case 0x104:
        func_08068954(context);
        command->state = 0x105;
        break;
    case 0x105:
        if (func_08066DC4(context)) {
            func_08061390();
            command->state = 0x101;
        }
        break;
    case 0x106:
        func_08066D74(context);
        command->state = 0x107;
        break;
    case 0x107:
        command->state = 2;
        break;
    }
    return 0;
}
