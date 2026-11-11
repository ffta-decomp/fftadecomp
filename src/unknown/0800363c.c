typedef unsigned char u8;

/* Preserve the retail volatile reads before resetting three shadow bytes. */
void ResetDisplayShadowControlBytes(void)
{
    volatile u8 *shadow = (volatile u8 *)0x03000940;
    (void)shadow[0x4a];
    shadow[0x4a] = 0xff;
    (void)shadow[0x4b];
    shadow[0x4b] = 0;
    (void)shadow[0x4e];
    shadow[0x4e] = 0x10;
}
