/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u32 GetUnitProperty(const void *,u32);
extern u32 DivideUnsignedValues(u32,u32);
extern u32 UnitStateEAHasBit0(const void *);
asm(".global DivideUnsignedValues\n.thumb_set DivideUnsignedValues,0x08142ab1");
asm(".global UnitStateEAHasBit0\n.thumb_set UnitStateEAHasBit0,0x080cda1d");

s32 GetClampedUnitEffectRate(const void *unit)
{
    s32 amount=DivideUnsignedValues(GetUnitProperty(unit,32),10);
    if((u8)UnitStateEAHasBit0(unit)) amount+=30;
    if(amount<0) amount=0;
    if(amount>100) amount=100;
    return amount;
}
