/* Upstream import provenance: https://github.com/shubshub/fftadecomp
 * Commit: c9e042201cbff2afeb0108cda849e8eb036ee382
 * Original file: src/080E5438.c
 * Adapted to local symbol bindings; original authorship/notices retained.
 * No additional license grant inferred. See data/upstream-imports.json.
 */
/* Byte-identical upstream C import: c9e042201cbff2afeb0108cda849e8eb036ee382.
 * Linkage aliases only; no emitted instructions or helper implementations. */
asm(".global func_08006ADC\n.thumb_set func_08006ADC,0x08006add\n.global func_0800BC08\n.thumb_set func_0800BC08,0x0800bc09\n.global func_0800BC28\n.thumb_set func_0800BC28,0x0800bc29\n.global func_08011040\n.thumb_set func_08011040,0x08011041\n.global func_080112D4\n.thumb_set func_080112D4,0x080112d5\n.global func_08017514\n.thumb_set func_08017514,0x08017515\n.global func_08017AC4\n.thumb_set func_08017AC4,0x08017ac5\n.global func_0801CD4C\n.thumb_set func_0801CD4C,0x0801cd4d\n.global func_0801E68C\n.thumb_set func_0801E68C,0x0801e68d\n.global func_0804C524\n.thumb_set func_0804C524,0x0804c525\n.global func_0804C5F8\n.thumb_set func_0804C5F8,0x0804c5f9\n.global func_0804C788\n.thumb_set func_0804C788,0x0804c789\n.global func_08063F18\n.thumb_set func_08063F18,0x08063f19\n.global func_08064004\n.thumb_set func_08064004,0x08064005\n.global func_08064278\n.thumb_set func_08064278,0x08064279\n.global func_08092084\n.thumb_set func_08092084,0x08092085\n.global func_0809D620\n.thumb_set func_0809D620,0x0809d621\n.global func_080DBA5C\n.thumb_set func_080DBA5C,0x080dba5d\n.global func_080DBD5C\n.thumb_set func_080DBD5C,0x080dbd5d\n.global func_080DCFE4\n.thumb_set func_080DCFE4,0x080dcfe5\n.global func_080DD748\n.thumb_set func_080DD748,0x080dd749\n.global func_0814860C\n.thumb_set func_0814860C,0x0814860d\n.global g_state_02001940\n.set g_state_02001940,0x02001940\n.global g_state_020020D0\n.set g_state_020020D0,0x020020D0\n.global g_table_0854CD54\n.set g_table_0854CD54,0x0854CD54\n.global g_table_08563A70\n.set g_table_08563A70,0x08563A70\n.global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n.global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n.global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n.global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n.global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n.global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
#define func_080E5438 RemainingBand43_000E5438
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



/* Target [0x080E5438, 0x080E54C6):
70b583b0061c0d1c141c2988012939d0012902dc002908d034e08020400081420ed00130814225d02ce06868e060a98a2171a21c211c0023f8f76af9a06021e02179012008400223002800d00423e06807490822134300930196002202920c220023f7f7a3fd20612888013009e00000906f39082069f6f7d5fa2061002801d102202880002003b070bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
} EffectDescriptor;

typedef struct {
    s16 x;
    s16 y;
    u8 selector;
    u8 unknown_05[3];
    void *underlying;
    void *object;
    void *child;
} EffectWork;

extern void *func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DBA5C(void *child);

u32 func_080E5438(void *task, void *descriptor_arg, void *payload_arg)
{
    EffectDescriptor *descriptor = descriptor_arg;
    EffectWork *work = payload_arg;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        work->object = descriptor->object;
        work->selector = descriptor->selector;
        work->underlying = func_080DD748(work->object, &work->x, &work->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        flags = (work->selector & 1) ? 4 : 2;
        work->child = func_080DCFE4(work->object, (const void *)0x08396F90,
                                  12, 0, flags | 8, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        work->child = func_080DBA5C(work->child);
        if (work->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}

