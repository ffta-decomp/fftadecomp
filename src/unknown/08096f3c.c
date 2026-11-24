typedef signed short s16;
struct CoordinateTransition;
extern struct CoordinateTransition gBattleCoordinateTransition;
extern void ConfigureCoordinateTransition(struct CoordinateTransition *, int, int, int, int, int, unsigned int, unsigned int);
void BeginBattleCoordinateTransition(s16 first_coordinate, s16 second_coordinate, s16 third_coordinate)
{
    /* Fixed projection offsets and full-word state parameters from retail. */
    ConfigureCoordinateTransition(&gBattleCoordinateTransition, first_coordinate,
        second_coordinate, third_coordinate, -120, -86, 4, 100);
}
asm(".global gBattleCoordinateTransition\n.set gBattleCoordinateTransition,0x0200F4C0\n.global ConfigureCoordinateTransition\n.thumb_set ConfigureCoordinateTransition,0x080922cd\n");
