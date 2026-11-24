typedef unsigned char u8;
u8 Remaining38_00013BEC(u8 token)
{
    u8 result = 0;
    if (token == 128 || token == 135 || token == 19 || token == 137 ||
        token == 85 || token == 86 || (u8)(token + 112) <= 28)
        result = 1;
    return result;
}
