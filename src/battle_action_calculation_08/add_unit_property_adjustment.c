/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern u8 UnitStateE9HasBit0(void *unit);
extern int CoreConsumer_000CA4F0(void *unit, unsigned property);
asm(".global CoreConsumer_000CA4F0\n.thumb_set CoreConsumer_000CA4F0, 0x080ca4f1\n");

/* A unit status bit suppresses either property 11 or property 13 adjustment. */
int AddUnitPropertyAdjustment(void *unit, int value, u8 alternate)
{
    if (!UnitStateE9HasBit0(unit)) {
        value += !alternate ? CoreConsumer_000CA4F0(unit, 11) : CoreConsumer_000CA4F0(unit, 13);
    }
    return value;
}
