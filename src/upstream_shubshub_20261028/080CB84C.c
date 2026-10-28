/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CB84C.c
 * Original SHA-256: 5e013d550933ceeb9c903e7ccbdaac74c94934bdf9bad581286ab3c9f4ecf93c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const u8 data_083E105C[];
extern const u8 *func_080071A8(const u8 *table, u16 index);
extern u32 func_0800588C(const u8 *bytes);

/* Target: 080CB84C..080CB868, 28 bytes. */
u32 func_080CB84C(u8 index)
{
    return func_0800588C(func_080071A8(data_083E105C, index));
}
