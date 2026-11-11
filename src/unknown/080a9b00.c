typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
struct Trail {u8 unknown0[46];s16 x,y,z;u8 unknown52[4];u16 property;u8 unknown58[4];s16 slot_x[3];s16 slot_z[3];u16 slot_property[3];s16 age[3];};
void ProjectPosition(s16,s16,s16,s16*,s16*) __asm__("RetailCall_0801c984");
void BattleRuntimeDependency_000A9B00(struct Trail *trail)
{
    s16 x,z;
    int i;
    ProjectPosition(trail->x,trail->y,trail->z,&x,&z);
    for (i=0;i<3;i++) {
        if (trail->age[i]>6) return;
        if (trail->age[i]>0 && trail->slot_x[i]==x && trail->slot_z[i]==z) return;
    }
    for (i=0;i<3;i++) {
        if (trail->age[i]<=0) {
            trail->age[i]=8;
            trail->slot_x[i]=x;
            trail->slot_z[i]=z;
            trail->slot_property[i]=trail->property;
            return;
        }
    }
}
asm(".global RetailCall_0801c984\n.thumb_set RetailCall_0801c984,0x0801c985\n");
