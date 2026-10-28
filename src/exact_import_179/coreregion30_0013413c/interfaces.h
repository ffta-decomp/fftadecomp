typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define OFFSET_OF(type, field) ((u32)&(((type *)0)->field))
struct JobChanceDefinition {
    u8 fields_before_chance[50];
    u8 chance;
    u8 final_field;
};
struct AbilityChanceDefinition {
    u8 fields_before_chance[26];
    u8 chance;
    u8 final_field;
};
typedef char job_stride[(sizeof(struct JobChanceDefinition) == 52) ? 1 : -1];
typedef char job_chance_offset[(OFFSET_OF(struct JobChanceDefinition, chance) == 50) ? 1 : -1];
typedef char ability_stride[(sizeof(struct AbilityChanceDefinition) == 28) ? 1 : -1];
typedef char ability_chance_offset[(OFFSET_OF(struct AbilityChanceDefinition, chance) == 26) ? 1 : -1];
extern const struct JobChanceDefinition JobChanceDefinitions[];
extern const struct AbilityChanceDefinition AbilityChanceDefinitions[];
__asm__(".set JobChanceDefinitions, 0x08521A14\n.set AbilityChanceDefinitions, 0x0855187C");
