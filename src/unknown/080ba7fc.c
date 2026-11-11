typedef unsigned char u8;
typedef unsigned int u32;
void ResetBattleFrameMarkerState(void *state)
{
    u32 cursor;
    u8 cleared_active;
    *(void **)state = 0;
    cleared_active = 0;
    cursor = (u32)state + 144;
    do {
        *(u8 *)(cursor + 8) = cleared_active;
        cursor -= 12;
    } while ((int)cursor >= (int)state);
}
