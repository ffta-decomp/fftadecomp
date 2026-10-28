/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D96F0.c
 * Original SHA-256: 5bd9996ed3876af595c8fb3ea3326ca50a06d7023972c7f1945fa03aebb274f9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
    u8 fifth;
    u8 sixth;
    u8 unknown_6[2];
} ObjectEntry;

typedef struct {
    u16 state;
    u16 unknown_2;
    const ObjectEntry *entries;
    u8 unknown_8[0xC];
    u8 first;
    u8 unknown_15;
    u8 second;
    u8 unknown_17;
    u8 count;
} ObjectCommand;

typedef struct {
    u8 active;
    u8 unknown_1[3];
    void *object;
} ObjectState;

extern void *func_0800D61C(u8 first, u8 second);
extern void func_0800DB0C(void *object, u8 first, u8 second, u8 third,
                         u8 fourth, u8 fifth, u8 sixth);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);

/* 0x080D96F0: 170 bytes. Configure an object and advance its command state. */
u32 func_080D96F0(void *task, ObjectCommand *command, ObjectState *state)
{
    switch (command->state) {
    case 0: {
        const ObjectEntry *entries;
        u8 count;

        state->object = func_0800D61C(command->first, command->second);
        entries = command->entries;
        count = command->count;
        if (entries && count) {
            u8 i;

            for (i = 0; i < count; i++) {
                func_0800DB0C(state->object, entries[i].first, entries[i].second,
                    entries[i].third, entries[i].fourth, entries[i].fifth,
                    entries[i].sixth);
            }
        }
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100:
        if (state->active) {
            func_0800C6C0(state->object);
            command->state++;
        }
        break;
    case 0x101:
        command->state = 2;
        break;
    }
    return 0;
}
