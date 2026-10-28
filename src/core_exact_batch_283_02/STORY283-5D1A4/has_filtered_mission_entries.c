typedef unsigned char u8;
extern u8 *gMissionContext __asm__("0x0200f448");
unsigned int CoreFrontier_0005D1A4(void) {
 unsigned int count = gMissionContext[0x11a9];
 return ((0u - count) | count) >> 31;
}
