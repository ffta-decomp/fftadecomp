/* Upstream import provenance: https://github.com/shubshub/fftadecomp
 * Commit: c9e042201cbff2afeb0108cda849e8eb036ee382
 * Original file: src/08010FEC.c
 * Adapted to local symbol bindings; original authorship/notices retained.
 * No additional license grant inferred. See data/upstream-imports.json.
 */
/* Byte-identical upstream C import: c9e042201cbff2afeb0108cda849e8eb036ee382.
 * Linkage aliases only; no emitted instructions or helper implementations. */
asm(".global func_08006ADC\n.thumb_set func_08006ADC,0x08006add\n.global func_0800BC08\n.thumb_set func_0800BC08,0x0800bc09\n.global func_0800BC28\n.thumb_set func_0800BC28,0x0800bc29\n.global func_08011040\n.thumb_set func_08011040,0x08011041\n.global func_080112D4\n.thumb_set func_080112D4,0x080112d5\n.global func_08017514\n.thumb_set func_08017514,0x08017515\n.global func_08017AC4\n.thumb_set func_08017AC4,0x08017ac5\n.global func_0801CD4C\n.thumb_set func_0801CD4C,0x0801cd4d\n.global func_0801E68C\n.thumb_set func_0801E68C,0x0801e68d\n.global func_0804C524\n.thumb_set func_0804C524,0x0804c525\n.global func_0804C5F8\n.thumb_set func_0804C5F8,0x0804c5f9\n.global func_0804C788\n.thumb_set func_0804C788,0x0804c789\n.global func_08063F18\n.thumb_set func_08063F18,0x08063f19\n.global func_08064004\n.thumb_set func_08064004,0x08064005\n.global func_08064278\n.thumb_set func_08064278,0x08064279\n.global func_08092084\n.thumb_set func_08092084,0x08092085\n.global func_0809D620\n.thumb_set func_0809D620,0x0809d621\n.global func_080DBD5C\n.thumb_set func_080DBD5C,0x080dbd5d\n.global func_0814860C\n.thumb_set func_0814860C,0x0814860d\n.global g_state_02001940\n.set g_state_02001940,0x02001940\n.global g_state_020020D0\n.set g_state_020020D0,0x020020D0\n.global g_table_0854CD54\n.set g_table_0854CD54,0x0854CD54\n.global g_table_08563A70\n.set g_table_08563A70,0x08563A70\n.global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n.global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n.global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n.global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n.global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n.global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
#define func_08010FEC CoreFrontier_00010FEC
/* 0x08010FEC: 4 bytes, adds r0, #0x18; bx lr. */
unsigned char *func_08010FEC(unsigned char *object)
{
    return object + 0x18;
}

