#ifndef FFTA_H
#define FFTA_H

/* Base types.  Everything here matched byte-for-byte with:
 *     agbcc -mthumb-interwork -O2
 * which is gcc 2.9-arm-000512 for Thumb/elf (see docs/toolchain.md).
 */

typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef signed short   s16;
typedef unsigned int   u32;
typedef signed int     s32;

/* 0x08017514 - 18 bytes - MATCH */
void func_08017514(u8 *p, u8 a, u8 b, u8 c, u8 d);

/* 0x080112D4 - 20 bytes - MATCH
 * The three fields are at +0x32, +0x34, +0x36.  What lives in front of them is
 * not identified yet, so it is named `unknown_*` rather than filled in with
 * invented members - these offsets come from the instructions, not from
 * knowledge of the struct. */
typedef struct {
    u8 unknown_32[0x32];
    s16 x, y, z;
} Vec3;

void func_080112D4(Vec3 *src, s16 *a, s16 *b, s16 *c);

/* 0x08006ADC - 26 bytes - MATCH
 * The two pointers are at +8 and +0xC, so eight bytes precede them; again the
 * real members there are unknown, not padding we chose for convenience. */
typedef struct {
    u32 unknown_0;
    u32 unknown_1;
    u32 *words;
    u8  *flags;
} Table;

void func_08006ADC(Table *t, u8 index, u32 value);

/* 0x0801CD4C - 26 bytes + literal pool - MATCH.
 * NB: keep the 0x02007F10 address in a variable in the function body - as a
 * macro the compiler folds each access into its own literal pool entry. */
void func_0801CD4C(u8 *a, u8 *b, u8 *c, u8 *d);

typedef struct {
    u8 unknown_00[0x1D];
    u8 value;
    u16 fields[3];
} Struct08011040;

u8 func_08011040(Struct08011040 *source, u16 *first, u16 *second, u16 *third);

typedef struct {
    u32 first;
    u32 second;
    u8 unknown_08[8];
    u16 flags;
} Struct08017AC4;

void func_08017AC4(Struct08017AC4 *state, u32 first, u32 second);
void func_0801E68C(u32 *first, u32 *second, u32 *third);

/* 0x080DBD5C - a s16 triple at +8; same shape as the +0x1e one, different
 * struct, so its own type rather than a shared one. */
typedef struct {
    u8  unknown_00[8];
    s16 x, y, z;
} Struct080DBD5C;

void func_080DBD5C(Struct080DBD5C *source, s16 *first, s16 *second, s16 *third);

/* batch 2 */
typedef struct {
    u16 unknown_00[2];   /* +0x0C, +0x0E */
    u16 cleared_a;       /* +0x10 */
    u16 cleared_b;       /* +0x14 */
    u16 tail;            /* +0x16 */
    u32 value;           /* +0x18 */
} HdrTail;

typedef struct {
    u16 id;                  /* +0x00 */
    u8  unknown_02[10];      /* +0x02 .. +0x0B */
    HdrTail tail_block;      /* +0x0C */
} Hdr;

/* 0x0809D620 - five s16 fields at +0x1C..+0x24 */
typedef struct {
    u8  unknown_00[0x1c];
    s16 f1, f2, f3, f4, f5;
} Rec5;

u16 func_0814860C(Hdr *h, u32 value, u16 tail);
void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
void func_08092084(u8 *base, s16 index, u8 lo, u8 hi);
void func_0809D620(Rec5 *rec, u16 a, u16 b, u16 c, u16 d);

/* 0x0804C5F8 - one 28-byte table entry */
typedef struct {
    u32 field_00;        /* +0x00, row + 2 */
    u8  unknown_04[4];
    u16 field_08;
    u16 field_0a;
    u8  field_0c;
    u8  field_0d;
    u8  field_0e;
    u8  field_0f;
    u8  field_10;
    u8  field_11;
    u8  field_12;         /* +0x12, written by func_0804C524 */
    u8  field_13;
    u8  unknown_14[2];
    u16 field_16;
    u32 field_18;
} Entry;                 /* 28 bytes */

void func_0804C5F8(Entry *base, u16 index, u32 selector, u8 a4,
                     u8 a5, u32 a6, u8 a7, u32 a8, u8 *row, u16 a10);

/* 0x0800BC08 / 0x0800BC28 - 40-byte records at 0x02009000, x/y s16 pair at
 * +0x18 / +0x1A */
typedef struct {
    u8  unknown_00[0x18];
    s16 x;
    s16 y;
} Rec40;                  /* 40 bytes */

void func_0800BC08(u32 index, s16 a, s16 b);
void func_0800BC28(u32 index, s16 *a, s16 *b);

/* The opcode script state, reached through the pointer at 0x0200F450.  Three
 * functions name this object: func_08064278 (current/count/entries),
 * func_08064004 (+0x4D, +0x51, +0x5C and the record at 0x020020D0) and
 * func_08063F18 (the fullest view: +0x4E..+0x50, +0x64, +0x66).  Their views
 * are offset-compatible, so this is the merged form - offsets are the code's,
 * not a recovered layout, and entries[] is sized to cover the whole run list.
 */
typedef struct {
    u16 current;         /* +0x00 */
    u16 count;           /* +0x02 */
    u16 entries[34];     /* +0x04 .. +0x47 */
    u8  unknown_48[5];   /* +0x48 .. +0x4C */
    u8  unknown_4d;      /* +0x4D */
    u16 field_4e;        /* +0x4E */
    u8  unknown_50;      /* +0x50 */
    u8  unknown_51;      /* +0x51 */
    u8  unknown_52[10];  /* +0x52 .. +0x5B */
    u32 unknown_5c;      /* +0x5C */
    u8  unknown_60[4];   /* +0x60 .. +0x63 */
    u16 field_64;        /* +0x64 */
    u16 field_66;        /* +0x66 */
} ScriptState;          /* 0x68 bytes */

/* The record at 0x020020D0.  func_08064004 writes a halfword at +0x0C and
 * copies the state's +0x5C into +0x04; func_08063F18 only reads +0x04.  Keep
 * field_0c as the u16 at +0x0C that func_08064004's own struct had - widening
 * it slides the field and changes the generated offsets.
 */
typedef struct {
    u32 unknown_00;      /* +0x00 */
    u32 field_04;        /* +0x04 */
    u16 unknown_08;      /* +0x08 */
    u16 unknown_0a;      /* +0x0A */
    u16 field_0c;        /* +0x0C */
} Record;

#endif
