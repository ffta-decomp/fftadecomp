typedef unsigned short u16;
extern void *GetPayload(void *) __asm__("RetailCall_08005bfc");
void CoreFrontier_00066028(void *object) {
 u16 *payload = GetPayload(object);
 payload[3] = 0;
 payload[2] = 64;
}
__asm__(".global RetailCall_08005bfc\n.thumb_set RetailCall_08005bfc,0x08005bfd");
