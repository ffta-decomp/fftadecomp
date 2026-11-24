typedef unsigned char u8;
typedef unsigned short u16;

#if defined(DISPLAY_SHADOW_SET_A)
#define SETTER_NAME SetDisplayShadowGroupA
#define SLOT_0 1
#define SLOT_1 2
#define SLOT_2 3
#define SLOT_OTHER 4
#elif defined(DISPLAY_SHADOW_SET_B)
#define SETTER_NAME SetDisplayShadowGroupB
#define SLOT_0 5
#define SLOT_1 7
#define SLOT_2 9
#define SLOT_OTHER 11
#elif defined(DISPLAY_SHADOW_SET_C)
#define SETTER_NAME SetDisplayShadowGroupC
#define SLOT_0 6
#define SLOT_1 8
#define SLOT_2 10
#define SLOT_OTHER 12
#else
#error Select one display-shadow setter
#endif

/* Separate pointer loads preserve the retail literal pools in each branch. */
/* Select one halfword in the group's four display-shadow positions. */
void SETTER_NAME(u16 value, u8 selector)
{
    if (selector == 0) {
        volatile u16 *shadow = (volatile u16 *)0x03000940;
        (void)shadow[SLOT_0];
        shadow[SLOT_0] = value;
    } else if (selector == 1) {
        volatile u16 *shadow = (volatile u16 *)0x03000940;
        (void)shadow[SLOT_1];
        shadow[SLOT_1] = value;
    } else if (selector == 2) {
        volatile u16 *shadow = (volatile u16 *)0x03000940;
        (void)shadow[SLOT_2];
        shadow[SLOT_2] = value;
    } else {
        volatile u16 *shadow = (volatile u16 *)0x03000940;
        (void)shadow[SLOT_OTHER];
        shadow[SLOT_OTHER] = value;
    }
}
