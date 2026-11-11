typedef unsigned short u16;
struct Halfword18Object { unsigned char unknown0[18]; u16 value18; };
u16 BattleStateDependency_00021C8C(struct Halfword18Object *object)
{
    return object->value18;
}
