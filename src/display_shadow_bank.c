typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u16 control[4];
    u32 packed_pair[2];
} DisplayShadowBank;

/* Read the previous shadow value before every write, as the retail routine does. */
#define WRITE_SHADOW_HALFWORD(index, value) do { \
    u32 next_value = (value);                      \
    (void)shadow[(index)];                         \
    shadow[(index)] = next_value;                  \
} while (0)

/* Keep the packed pair in r1 through its low and high halfword stores. */
#define COPY_DISPLAY_BANK(first_index) do {                              \
    register u32 pair __asm__("r1");                                     \
    WRITE_SHADOW_HALFWORD((first_index) + 0, source->control[0]);        \
    WRITE_SHADOW_HALFWORD((first_index) + 1, source->control[1]);        \
    WRITE_SHADOW_HALFWORD((first_index) + 2, source->control[2]);        \
    WRITE_SHADOW_HALFWORD((first_index) + 3, source->control[3]);        \
    pair = source->packed_pair[0];                                        \
    (void)shadow[(first_index) + 4];                                     \
    shadow[(first_index) + 4] = pair;                                     \
    pair = (s32)pair >> 16;                                               \
    (void)shadow[(first_index) + 5];                                     \
    shadow[(first_index) + 5] = pair;                                     \
    pair = source->packed_pair[1];                                        \
    (void)shadow[(first_index) + 6];                                     \
    shadow[(first_index) + 6] = pair;                                     \
    pair = (s32)pair >> 16;                                               \
    (void)shadow[(first_index) + 7];                                     \
    shadow[(first_index) + 7] = pair;                                     \
} while (0)

/* Select one of two eight-halfword banks in the display register shadow. */
void SetDisplayShadowBank(const volatile DisplayShadowBank *source, u32 bank)
{
    /* The fixed pointer register preserves the retail Thumb layout. */
    switch (bank) {
    case 2: {
        register volatile u16 *shadow __asm__("r0") = (volatile u16 *)0x03000940;
        COPY_DISPLAY_BANK(13);
        break;
    }
    case 3: {
        register volatile u16 *shadow __asm__("r0") = (volatile u16 *)0x03000940;
        COPY_DISPLAY_BANK(21);
        break;
    }
    default:
        break;
    }
}
