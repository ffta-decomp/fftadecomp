typedef unsigned short u16;

/* Each OAM entry has three attributes and one interleaved affine parameter. */
#define WRITE_HIDDEN_ENTRY(matrix_value) do { \
    *cursor++ = hidden_attribute;                \
    *cursor++ = zero;                            \
    *cursor++ = zero;                            \
    *cursor++ = (matrix_value);                  \
} while (0)

/* Hide all 128 objects and initialize all 32 affine matrices to identity. */
void ResetOamAndAffineMatrices(void)
{
    u16 *cursor = (u16 *)0x07000000;
    /* Reuse the seed registers for zero and the loop counter as retail does. */
    register u16 hidden_seed __asm__("r1") = 0x0200;
    register u16 hidden_attribute __asm__("r2") = hidden_seed;
    register u16 zero __asm__("r1") = 0;
    register u16 identity_seed __asm__("r3") = 0x0100;
    register u16 identity __asm__("r4") = identity_seed;
    register int matrix __asm__("r3") = 31;
    do {
        WRITE_HIDDEN_ENTRY(identity);
        WRITE_HIDDEN_ENTRY(zero);
        WRITE_HIDDEN_ENTRY(zero);
        WRITE_HIDDEN_ENTRY(identity);
    } while (--matrix >= 0);
}

/* Retail alignment halfword after the function body. */
__asm__(".hword 0");
