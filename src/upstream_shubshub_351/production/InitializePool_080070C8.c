/* Upstream import provenance: https://github.com/shubshub/fftadecomp
 * Commit: c9e042201cbff2afeb0108cda849e8eb036ee382
 * Original file: src/080070C8.c
 * Adapted to local symbol bindings; original authorship/notices retained.
 * No additional license grant inferred. See data/upstream-imports.json.
 */
/* Byte-identical upstream C import: c9e042201cbff2afeb0108cda849e8eb036ee382.
 * Linkage aliases only; no emitted instructions or helper implementations. */
asm(".global func_08006ADC\n.thumb_set func_08006ADC,0x08006add\n.global func_0800BC08\n.thumb_set func_0800BC08,0x0800bc09\n.global func_0800BC28\n.thumb_set func_0800BC28,0x0800bc29\n.global func_08011040\n.thumb_set func_08011040,0x08011041\n.global func_080112D4\n.thumb_set func_080112D4,0x080112d5\n.global func_08017514\n.thumb_set func_08017514,0x08017515\n.global func_08017AC4\n.thumb_set func_08017AC4,0x08017ac5\n.global func_0801CD4C\n.thumb_set func_0801CD4C,0x0801cd4d\n.global func_0801E68C\n.thumb_set func_0801E68C,0x0801e68d\n.global func_0804C524\n.thumb_set func_0804C524,0x0804c525\n.global func_0804C5F8\n.thumb_set func_0804C5F8,0x0804c5f9\n.global func_0804C788\n.thumb_set func_0804C788,0x0804c789\n.global func_08063F18\n.thumb_set func_08063F18,0x08063f19\n.global func_08064004\n.thumb_set func_08064004,0x08064005\n.global func_08064278\n.thumb_set func_08064278,0x08064279\n.global func_08092084\n.thumb_set func_08092084,0x08092085\n.global func_0809D620\n.thumb_set func_0809D620,0x0809d621\n.global func_080DBD5C\n.thumb_set func_080DBD5C,0x080dbd5d\n.global func_0814860C\n.thumb_set func_0814860C,0x0814860d\n.global g_state_02001940\n.set g_state_02001940,0x02001940\n.global g_state_020020D0\n.set g_state_020020D0,0x020020D0\n.global g_table_0854CD54\n.set g_table_0854CD54,0x0854CD54\n.global g_table_08563A70\n.set g_table_08563A70,0x08563A70\n.global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n.global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n.global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n.global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n.global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n.global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
#define func_080070C8 InitializePool_080070C8
// func_080070C8 - 0x080070C8, 112 bytes (0x080070C8 .. 0x08007138).
//
// target  70b50c1c061c114d2a6808213bf1baf8083ca408b471240af471341c08342a68
//         201c0c213bf1aef87020207173206071b179f079000208430338a071000ae071
//         002c05d0a01b8003010c02e0b8d436080021ff20084000223070090a7170b070
//         f1700012030717271301c70bc02bc0847
//
// The indexed span stops at 0x080070D6, in the middle of the first call, so
// the body has to be read out of the ROM: it ends at the interworking return
// `pop {r1}; bx r1` at 0x08007136.
//
// The function works on a 16-byte object made of two 8-byte records.  The
// first record gets the index of the second record inside the object (in
// units of four bytes, so 2 here) in both of its halfwords, a flag pair 1/0
// and a count; the second record gets the pair 0x70/0x73 and the count minus
// three.  A callback taken from a table in the cartridge ROM is invoked once
// for each record, with the record pointer and the constant 8 or 12.
//
// The literal pool holds one word, 0x0836D4B8, at 0x08007114 - agbcc flushes
// it there because the branch at 0x08007112 skips over it.  The word it points
// at is the callback address 0x03005E79, so the table is read for a function
// pointer and the call goes through the `bx r2` thunk at 0x0814224C.
/* Upstream import redirect; originals remain byte-identical under vendor/. */
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



typedef void (*ObjectFunc)(void *, u32);

typedef struct {
    u8 unknown_00;      /* +0 - low byte of the index halfword */
    u8 unknown_01;      /* +1 - high byte of the index halfword */
    u8 unknown_02;      /* +2 - low byte of the second index halfword */
    u8 unknown_03;      /* +3 - high byte of the second index halfword */
    u8 unknown_04;      /* +4 - set to 1 */
    u8 unknown_05;      /* +5 - set to 0 */
    u8 unknown_06;      /* +6 - low byte of the count halfword */
    u8 unknown_07;      /* +7 - high byte of the count halfword */
} Record080070C8;

u8 *func_080070C8(u8 *a, u32 b)
{
    Record080070C8 *object = (Record080070C8 *)a;
    // plausible: a read-only table in the cartridge ROM, holding a callback
    u32 *table = (u32 *)0x0836D4B8;
    u8 *second;
    u16 count;
    u32 value;
    u32 index;
    u32 low;
    u32 byte;

    ((ObjectFunc)(*table))(object, 8);

    count = (b - 8) >> 2;
    object->unknown_06 = count;
    object->unknown_07 = count >> 8;

    second = a + 8;
    ((ObjectFunc)(*table))(second, 12);

    second[4] = 0x70;
    second[5] = 0x73;

    byte = object->unknown_06;
    value = (object->unknown_07 << 8) | byte;
    value -= 3;
    second[6] = value;
    second[7] = value >> 8;

    index = second ? ((u32)(second - a) << 14) >> 16 : 0;
    low = index & 0xff;
    object->unknown_00 = low;
    object->unknown_01 = index >> 8;
    object->unknown_02 = low;
    object->unknown_03 = index >> 8;
    object->unknown_04 = 1;
    object->unknown_05 = 0;

    return (u8 *)object;
}

