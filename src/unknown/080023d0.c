typedef unsigned char u8;
typedef unsigned short u16;
void sub_080023D0(u8 *state)
{
    if (state[7] & 128)
        state[14] = state[11];
    *(u16 *)(state + 4) = 0;
}
