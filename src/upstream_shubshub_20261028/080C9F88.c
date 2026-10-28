/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C9F88.c
 * Original SHA-256: 5405b1b500cd607bc215341e2c1bdf697ee5e4127581d4122390a26d133ce547
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Source {
    u8 unknown_00[4];
    u8 kind;
    u8 unknown_05[3];
    u8 id;
};

struct Record {
    u8 count;
    u8 value;
    u8 related_value;
    u8 enabled;
    u8 state;
    u8 mode;
    u8 override_first;
    u8 override_second;
    u8 category;
    u8 unknown_09[3];
    u8 statuses[256];
};

struct Configuration {
    u8 unknown_00[0x14];
    u8 status_bits[0x14];
    u8 override_first;
    u8 override_second;
};

extern u32 func_080C7EA4(struct Source *source, int key);
extern u8 func_080C9ED8(u8 value);
extern int func_080C92F0(struct Source *source, int key);
extern u8 func_080C8570(u8 first, u8 second, int key);
extern u8 func_080C8228(struct Source *source);
extern void func_080CD620(struct Source *source, u8 index);

static inline u8 status_bit_is_set(const struct Configuration *configuration, u16 index)
{
    const u8 *byte = &configuration->status_bits[index / 8];
    u8 mask = 1 << (index % 8);

    if (*byte & mask)
        return 1;
    return 0;
}

/* Target: 080C9F88..080CA078, 240 bytes. */
void func_080C9F88(struct Source *source, struct Configuration *configuration)
{
    struct Record *record = (struct Record *)func_080C7EA4(source, 0x22);
    int i;

    record->count = func_080C9ED8(func_080C7EA4(source, 3));
    if (record->count == 0)
        return;

    record->value = func_080C92F0(source, 12);
    if (func_080C7EA4(source, 5))
        record->related_value = func_080C8570(source->id, source->id, 12);
    if (func_080C8228(source))
        record->enabled = 1;

    for (i = 1; i < record->count; i++) {
        if (status_bit_is_set(configuration, i - 1)) {
            record->statuses[i] = 0xE4;
            func_080CD620(source, i);
        }
    }

    record->mode = 0;
    record->state = 0;
    if (configuration->override_first)
        record->override_first = configuration->override_first;
    if (configuration->override_second)
        record->override_second = configuration->override_second;
    if (source->kind == 2)
        record->category = 11;
}
