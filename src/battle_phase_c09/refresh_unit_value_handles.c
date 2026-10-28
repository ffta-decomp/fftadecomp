/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitDisplay { void *unit; u8 before_style[26]; u8 style; u8 before_id[21]; u16 id; u8 before_owner[10]; void *owner; u8 gap[8]; int handles[2]; };
extern const u8 gDisplayCodes[];
extern u32 GetUnitProperty(void *unit, u32 selector);
extern int UpdateHandle(void *owner, int handle, int enabled, u8 code, u16 id, int value, int index);
extern void ApplyHandleStyle(int handle, u8 style);
extern void ReleaseHandle(void *owner, int handle);

asm(".global gDisplayCodes\n.set gDisplayCodes,0x08394352\n.global UpdateHandle\n.thumb_set UpdateHandle,0x08021619\n.global ApplyHandleStyle\n.thumb_set ApplyHandleStyle,0x08021e65\n.global ReleaseHandle\n.thumb_set ReleaseHandle,0x08021bd5");
static inline u8 HasUnitProperty40Bit1(void *unit)
{
    if (GetUnitProperty(unit, 40) & 2)
        return 1;
    return 0;
}
void RefreshUnitValueHandles(struct UnitDisplay *record, u16 value, u8 delta)
{
    int count;
    int index;
    int *handle;
    int adjusted;
    if (HasUnitProperty40Bit1(record->unit))
        delta = 0;
    count = 3;
    index = 1;
    adjusted = value + (s8)delta;
    handle = record->handles;
    do {
        void *owner = record->owner;
        int code_index = index - 1;
        int result = UpdateHandle(owner, *handle, 1, gDisplayCodes[code_index], record->id, adjusted, index);
        if (result != -1) {
            *handle = result;
            ApplyHandleStyle(result, record->style);
        } else if (*handle) {
            ReleaseHandle(record->owner, *handle);
            *handle = 0;
        }
        handle++;
        index++;
    } while (index < count);
}
