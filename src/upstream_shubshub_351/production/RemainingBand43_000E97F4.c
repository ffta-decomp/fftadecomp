/* Upstream import provenance: https://github.com/shubshub/fftadecomp
 * Commit: c9e042201cbff2afeb0108cda849e8eb036ee382
 * Original file: src/080E97F4.c
 * Adapted to local symbol bindings; original authorship/notices retained.
 * No additional license grant inferred. See data/upstream-imports.json.
 */
/* Byte-identical upstream C import: c9e042201cbff2afeb0108cda849e8eb036ee382.
 * Linkage aliases only; no emitted instructions or helper implementations. */
asm(".global func_08006ADC\n.thumb_set func_08006ADC,0x08006add\n.global func_0800BC08\n.thumb_set func_0800BC08,0x0800bc09\n.global func_0800BC28\n.thumb_set func_0800BC28,0x0800bc29\n.global func_08011040\n.thumb_set func_08011040,0x08011041\n.global func_080112D4\n.thumb_set func_080112D4,0x080112d5\n.global func_08017514\n.thumb_set func_08017514,0x08017515\n.global func_08017AC4\n.thumb_set func_08017AC4,0x08017ac5\n.global func_0801CD4C\n.thumb_set func_0801CD4C,0x0801cd4d\n.global func_0801E68C\n.thumb_set func_0801E68C,0x0801e68d\n.global func_0804C524\n.thumb_set func_0804C524,0x0804c525\n.global func_0804C5F8\n.thumb_set func_0804C5F8,0x0804c5f9\n.global func_0804C788\n.thumb_set func_0804C788,0x0804c789\n.global func_08063F18\n.thumb_set func_08063F18,0x08063f19\n.global func_08064004\n.thumb_set func_08064004,0x08064005\n.global func_08064278\n.thumb_set func_08064278,0x08064279\n.global func_08092084\n.thumb_set func_08092084,0x08092085\n.global func_0809D620\n.thumb_set func_0809D620,0x0809d621\n.global func_080D6098\n.thumb_set func_080D6098,0x080d6099\n.global func_080D6134\n.thumb_set func_080D6134,0x080d6135\n.global func_080DBA5C\n.thumb_set func_080DBA5C,0x080dba5d\n.global func_080DBB14\n.thumb_set func_080DBB14,0x080dbb15\n.global func_080DBD5C\n.thumb_set func_080DBD5C,0x080dbd5d\n.global func_080DBDC8\n.thumb_set func_080DBDC8,0x080dbdc9\n.global func_080DCFE4\n.thumb_set func_080DCFE4,0x080dcfe5\n.global func_080DD580\n.thumb_set func_080DD580,0x080dd581\n.global func_080DD748\n.thumb_set func_080DD748,0x080dd749\n.global func_080DE268\n.thumb_set func_080DE268,0x080de269\n.global func_080DFD8C\n.thumb_set func_080DFD8C,0x080dfd8d\n.global func_0814860C\n.thumb_set func_0814860C,0x0814860d\n.global g_state_02001940\n.set g_state_02001940,0x02001940\n.global g_state_020020D0\n.set g_state_020020D0,0x020020D0\n.global g_table_0854CD54\n.set g_table_0854CD54,0x0854CD54\n.global g_table_08563A70\n.set g_table_08563A70,0x08563A70\n.global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n.global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n.global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n.global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n.global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n.global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
#define func_080E97F4 RemainingBand43_000E97F4
/* Target 0x080E97F4, complete [0x080E97F4, 0x080E991E), 298 bytes:
70b584b0061c0d1c141c2988012900d186e0012902dc002908d081e08020400081421dd0013081426cd079e0a88a2070e88a60700006002809d06868e060211da21df2f7c7fae068f4f714fd68e06868a060211da21d0023f3f77cffe0605fe02178012008400221002800d004210b1c6278002a0cd1a06804490093019602920c220023f3f7b4fb09e00000fc863908e06800960a210c220023f2f741f9e0616078002805d1a068f3f770fe0006002820d00421605e0622a15e02220092221c103201920d4a0292039600220123ecf7e9fba0612178012008400822002800d01022074804210a43009601210023f6f753fa20622888013011e00000cc86390818873908a069ecf71bfca061002807d1e069f2f7a9f8e061002801d102202880002004b070bc02bc0847
*/
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



typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 input_mode;
} Descriptor080E97F4;

typedef struct {
    u8 selector;
    u8 input_mode;
    u8 unknown_02[2];
    s16 coordinate_x;
    s16 coordinate_y;
    void *wrapper;
    void *underlying;
    u8 unknown_10[8];
    void *coordinate_task;
    void *object_task;
    void *record_task;
} Payload080E97F4;

extern void func_080DBDC8(void *object, s16 *coordinate_x, s16 *coordinate_y);
extern void func_080DE268(void *object);
extern void *func_080DD748(void *wrapper, s16 *coordinate_x,
                          s16 *coordinate_y, s16 *coordinate_z);
extern void *func_080DCFE4(void *wrapper, const void *record, u8 count,
                          u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DBB14(void *object, u8 first, u8 second, u16 value,
                          void *parent);
extern u32 func_080DD580(const void *wrapper);
extern void *func_080D6098(s16 coordinate_x, s16 coordinate_y,
                          s16 coordinate_z, u8 mode, u16 count,
                          void *storage, const void *record, void *parent);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080E97F4(void *task, Descriptor080E97F4 *descriptor,
                  Payload080E97F4 *payload)
{
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->input_mode = descriptor->input_mode;
        if (payload->input_mode != 0) {
            payload->underlying = descriptor->object;
            func_080DBDC8(payload->underlying, &payload->coordinate_x,
                         &payload->coordinate_y);
            func_080DE268(payload->underlying);
        } else {
            payload->wrapper = descriptor->object;
            payload->underlying = func_080DD748(payload->wrapper,
                &payload->coordinate_x, &payload->coordinate_y, 0);
        }
        break;
    case 1:
        break;
    case 0x100:
        flags = (payload->selector & 1) ? 4 : 2;
        if (payload->input_mode == 0)
            payload->object_task = func_080DCFE4(payload->wrapper,
                (const void *)0x083986FC, 12, 0, flags, task, 0);
        else
            payload->object_task = func_080DBB14(payload->underlying,
                                               10, 12, 0, task);
        if (payload->input_mode != 0 || (u8)func_080DD580(payload->wrapper) != 0) {
            payload->coordinate_task = func_080D6098(payload->coordinate_x,
                payload->coordinate_y, 0, 1, 2, payload->unknown_10,
                (const void *)0x083986CC, task);
            flags = (payload->selector & 1) ? 16 : 8;
            payload->record_task = func_080DFD8C((const void *)0x08398718,
                1, flags | 4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}

