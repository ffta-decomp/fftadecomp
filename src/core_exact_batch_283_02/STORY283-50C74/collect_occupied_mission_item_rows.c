typedef unsigned char u8;
typedef unsigned int u32;
u32 CoreRegion_00050C74(u32 *output) {
 register u32 base __asm__("r3") = (u32)output;
 u8 *row = (u8 *)0x02002b08;
 u32 cursor;
 u32 count = 0;
 int remaining = 63;
 __asm__("" : "+r"(base));
 cursor = base;
 do {
  if (row[0] != 0) {
   if (base != 0) *(u32 *)cursor = (u32)row;
   cursor += 4;
   ++count;
  }
  --remaining;
  row += 4;
 } while (remaining >= 0);
 return count;
}
