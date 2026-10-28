/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ContentRule {
    u8 active;
    u8 selector;
    u8 required_low, required_high, required_value;
    u8 excluded_low, excluded_high, excluded_value;
} __attribute__((packed));
typedef char ContentRuleSize[(sizeof(struct ContentRule)==8)?1:-1];
typedef void (*ClearRuleOutput)(void *, u32);
extern u8 GetGameFlag(u16 flag);
extern u8 ReadSaveByte(u16 index);
extern const struct ContentRule ContentRules[127] __asm__("0x085573f4");
#define CLEAR_RULE_OUTPUT (*(ClearRuleOutput *)0x0836d4b8)


/* Required and excluded flag tests are deliberately asymmetric. */
u32 CollectEligibleContentRules(const struct ContentRule **output, u32 capacity,
                         u32 selector)
{
    u32 accepted = 0;
    const struct ContentRule *rule;
    u32 remaining;
    s32 ordinal;
    CLEAR_RULE_OUTPUT(output, capacity << 2);
    rule = ContentRules;
    remaining = capacity;
    for (ordinal = 1; ordinal <= 127; ordinal++, rule++) {
        u16 code;
        u8 value;
        u32 low_byte;
        if (!rule->active)
            continue;
        if (rule->selector && rule->selector != selector)
            continue;
        low_byte = rule->required_low;
        code = rule->required_high << 8;
        code |= low_byte;
        if (code > 1535) {
            code = code - 1536;
            if (ReadSaveByte(code) < rule->required_value)
                continue;
        } else {
            if (GetGameFlag(code) == 1 && rule->required_value == 0)
                continue;
            if (!GetGameFlag(code) && rule->required_value == 1)
                continue;
        }
        low_byte = rule->excluded_low;
        code = rule->excluded_high << 8;
        code |= low_byte;
        if (code > 1535) {
            code = code - 1536;
            if (ReadSaveByte(code) >= rule->excluded_value)
                continue;
        } else if (code != 0) {
            value = GetGameFlag(code);
            if (value == 1 && rule->excluded_value == 1)
                continue;
            if (value == 0 && rule->excluded_value == 0)
                continue;
        }
        *output++ = rule;
        accepted++;
        remaining--;
        if (remaining == 0)
            break;
    }
    return accepted;
}
