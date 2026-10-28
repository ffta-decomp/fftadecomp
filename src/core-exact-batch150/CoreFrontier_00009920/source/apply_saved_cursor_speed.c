typedef unsigned char u8;
struct CursorKeyState { u8 prefix[10]; u8 initial_delay; u8 repeat_delay; };
#define CURSOR_KEYS (&gSavedCursorKeys)
extern struct CursorKeyState gSavedCursorKeys;
__asm__(".global gSavedCursorKeys\n.set gSavedCursorKeys,0x03000000");

/* Saved Cursor Spd mode selects two ordered key timing bytes. */
void ApplySavedCursorSpeed(u8 mode)
{
    switch (mode) {
    case 2:
        CURSOR_KEYS->initial_delay = 25;
        CURSOR_KEYS->repeat_delay = 8;
        break;
    case 1:
        CURSOR_KEYS->initial_delay = 15;
        CURSOR_KEYS->repeat_delay = 4;
        break;
    case 0:
    default:
        CURSOR_KEYS->initial_delay = 10;
        CURSOR_KEYS->repeat_delay = 2;
        break;
    }
}
