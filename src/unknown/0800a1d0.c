typedef unsigned char u8;
typedef unsigned short u16;
extern void WriteSaveByte(u16 index,u8 value);
/* Original nested-script opcode3: packed little-endian save index, then value.
 * Existing save writer is reused; no clamp/flag interpretation is invented. */
void OriginalOpcode309_0000A1D0(void *context,const u8 *command)
{
 WriteSaveByte(command[1] | (command[2]<<8),command[3]);
}
asm(".global WriteSaveByte\n.thumb_set WriteSaveByte, 0x080C95C1");
