typedef unsigned char u8;

/* These predicates operate on the low byte of the caller's argument. */
#if defined(CLASS_ALNUM)
int IsAsciiAlphanumeric(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - 'a') <= 25 ||
        (u8)(character - 'A') <= 25 ||
        (u8)(character - '0') <= 9)
        return 1;
    return 0;
}
#elif defined(CLASS_ALPHA)
int IsAsciiLetter(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - 'a') <= 25 ||
        (u8)(character - 'A') <= 25)
        return 1;
    return 0;
}
#elif defined(CLASS_SEVEN_BIT)
int IsAsciiSevenBit(int value)
{
    /* The sign of the low byte is its ASCII high-bit test. */
    if ((signed char)value >= 0)
        return 1;
    return 0;
}
#elif defined(CLASS_CONTROL)
int IsAsciiControlOrDelete(int value)
{
    u8 character = (u8)value;
    if (character <= 0x1f || character == 0x7f)
        return 1;
    return 0;
}
#elif defined(CLASS_DIGIT)
int IsAsciiDigit(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - '0') <= 9)
        return 1;
    return 0;
}
#elif defined(CLASS_LOWER)
int IsAsciiLowercase(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - 'a') <= 25)
        return 1;
    return 0;
}
#elif defined(CLASS_PRINTABLE)
int IsAsciiPrintable(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - ' ') <= 0x5e)
        return 1;
    return 0;
}
#elif defined(CLASS_NONLETTER_NONCONTROL)
int IsAsciiNonLetterNonControl(int value)
{
    u8 character = (u8)value;
    register int predicate __asm__("r0");

    if ((u8)(character - 'a') <= 25 || (u8)(character - 'A') <= 25)
        predicate = 1;
    else
        predicate = 0;
    /* Keep the two materialized booleans in the retail result register. */
    __asm__ volatile("" : "+r" (predicate));
    if (predicate != 0)
        goto reject;

    if (character <= 0x1f || character == 0x7f)
        predicate = 1;
    else
        predicate = 0;
    __asm__ volatile("" : "+r" (predicate));
    if (predicate == 0)
        goto accept;

reject:
    return 0;
accept:
    return 1;
}
#elif defined(CLASS_WHITESPACE)
int IsAsciiWhitespace(int value)
{
    u8 character = (u8)value;
    if (character == ' ' || character == '\t' ||
        character == '\r' || character == '\n' || character == '\f')
        return 1;
    return 0;
}
#elif defined(CLASS_UPPER)
int IsAsciiUppercase(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - 'A') <= 25)
        return 1;
    return 0;
}
#elif defined(CLASS_TO_LOWER)
int ToAsciiLowercase(int value)
{
    u8 character = (u8)value;
    if ((u8)(character - 'A') <= 25)
        return (u8)(character + ('a' - 'A'));
    else
        return character;
}
#elif defined(CLASS_TO_UPPER)
int ToAsciiUppercase(int value)
{
    u8 character = (u8)value;
    register u8 result __asm__("r2") = character;
    /* Preserve retail's r2 result before forming the range check in r0. */
    __asm__ volatile("" : "+r" (result));
    if ((u8)(character - 'a') <= 25) {
        result = character - ('a' - 'A');
    }
    return result;
}
#else
#error Select one character class
#endif
