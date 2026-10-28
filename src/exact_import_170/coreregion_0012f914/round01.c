#include "interfaces.h"

u32 SelectItemResponseCode(u16 group, u16 code_a, u16 code_b)
    __asm__("CoreRegion_0012F914");
u32 SelectItemResponseCode(u16 group, u16 code_a, u16 code_b)
{
    u32 result = 0;
    if (code_a == 0)
        code_a = code_b;
    if (code_b == 0)
        code_b = code_a;
    switch (group) {
    case 1:
        if ((u16)(code_a - 1) <= 3 &&
            code_b > 0 && code_b <= 4) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 1) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 1) <= 3) {
            result = code_b;
        }
        break;
    case 2:
        if ((u16)(code_a - 6) <= 3 &&
            code_b > 5 && code_b <= 9) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 6) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 6) <= 3) {
            result = code_b;
        }
        break;
    case 3:
        if ((u16)(code_a - 11) <= 3 &&
            code_b > 10 && code_b <= 14) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 11) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 11) <= 3) {
            result = code_b;
        }
        break;
    case 4:
        if ((u16)(code_a - 16) <= 3 &&
            code_b > 15 && code_b <= 19) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 16) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 16) <= 3) {
            result = code_b;
        }
        break;
    case 5:
        if ((u16)(code_a - 21) <= 3 &&
            code_b > 20 && code_b <= 24) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 21) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 21) <= 3) {
            result = code_b;
        }
        break;
    case 6:
        if ((u16)(code_a - 26) <= 3 &&
            code_b > 25 && code_b <= 29) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 26) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 26) <= 3) {
            result = code_b;
        }
        break;
    case 7:
        if ((u16)(code_a - 31) <= 3 &&
            code_b > 30 && code_b <= 34) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 31) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 31) <= 3) {
            result = code_b;
        }
        break;
    case 8:
        if ((u16)(code_a - 36) <= 3 &&
            code_b > 35 && code_b <= 39) {
            result = code_b;
            if (code_a <= code_b)
                result = code_a;
        } else if ((u16)(code_a - 36) <= 3) {
            result = code_a;
        } else if ((u16)(code_b - 36) <= 3) {
            result = code_b;
        }
        break;
    default:
        return 0;
    }
    return result;
}
