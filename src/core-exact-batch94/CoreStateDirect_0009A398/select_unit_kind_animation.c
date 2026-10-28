struct UnitKindObject {unsigned char unknown0[4];unsigned char kind;};
unsigned int CoreStateDirect_0009A398(struct UnitKindObject *unit)
{
    switch (unit->kind) {
    case 29: case 32: case 72: case 73: return 4;
    default: return 0;
    }
}
