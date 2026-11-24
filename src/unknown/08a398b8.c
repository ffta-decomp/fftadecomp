typedef unsigned char u8;
typedef unsigned short u16;

void Embedded42_00A398B8(u16 *object, u8 value)
{
    if (value != 0) {
        register u16 old_word asm("r1") = *object;
        register u16 mask asm("r0") = 4;
        *object = mask | old_word;
    } else {
        *object = *object & 0xFFFB;
    }
}
