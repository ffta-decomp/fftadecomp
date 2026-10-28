/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CB868.c
 * Original SHA-256: cc0fbed64953d78f89b6c5c7278344da9d72a898cfc743cf2d7b762cfce70446
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Object {
    u8 unknown_00[4];
    u8 index;
};

struct NameEntry {
    u8 unknown_00[0xB];
    u8 name;
};

extern const u8 data_083E105C[];
extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(void *object);
extern u32 func_080C92F0(void *object, u32 selector);
extern const u8 *func_080071A8(const u8 *table, u16 index);
extern u8 *func_0800543C(void *destination, const void *source);

/* Target: 080CB868..080CB8B4, 76 bytes. */
u8 *func_080CB868(u8 *buffer, struct Object *object)
{
    const u8 *names = data_083E105C;
    u32 name;

    if (func_080C817C(object))
        name = ((const struct NameEntry *)g_table_085273D8[object->index])->name;
    else
        name = func_080C92F0(object, 9);

    return func_0800543C(buffer, func_080071A8(names, (u8)name));
}
