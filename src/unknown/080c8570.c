#include "ffta/unsigned_types.h"
#include "jobs/property_access.h"

/* Packed 52-byte record at 0x08521a14. Unidentified fields use selector numbers. */
struct JobDefinition {
    u16 p00;
    u8 unknown_at_02[2];
    u8 p01;
    u8 inherit;
    u8 p03;
    u16 p04;
    u16 p05;
    u32 p06 : 4;
    u32 p07 : 4;
    u8 p08;
    u8 p09;
    u8 p10;
    u8 p11;
    u8 p12;
    u8 p13;
    u32 unknown_at_18 : 3;
    u32 p14 : 3;
    u32 p15 : 3;
    u32 p16 : 3;
    u32 p17 : 3;
    u32 p18 : 3;
    u32 p19 : 3;
    u32 p20 : 3;
    u32 p21 : 3;
    u32 unknown_at_21 : 5;
    u8 p22;
    u8 base_hp;
    u8 base_mp;
    u8 p25;
    u32 base_weapon_attack : 12;
    u32 base_weapon_defense : 12;
    u32 base_magic_power : 12;
    u32 base_magic_resistance : 12;
    u8 hp_growth_tenths;
    u8 mp_growth_tenths;
    u8 speed_growth_tenths;
    u8 weapon_attack_growth_tenths;
    u8 weapon_defense_growth_tenths;
    u8 magic_power_growth_tenths;
    u8 magic_resistance_growth_tenths;
    u8 unknown_at_27;
    u8 p30;
    u8 p31;
    u8 p32;
    u32 p34 : 4;
    u32 p35 : 4;
    u8 p33;
    u8 equipment_class_mask_index;
    u8 first_ability_index;
    u8 last_ability_index;
    u8 p39;
    u8 p40;
    u8 unknown_at_32[2];
} __attribute__((packed));

typedef char JobDefinitionSizeMustBe52[(sizeof(struct JobDefinition) == 52) ? 1 : -1];

extern const struct JobDefinition gJobDefinitions[];

/* Nonzero inheritance redirects. Invalid selectors and cycles intentionally loop. */
#define READ_JOB_PROPERTY(selector, field) \
    case selector: \
        if (job->inherit == 255) \
            job = &gJobDefinitions[fallback_job]; \
        else if (job->inherit != 0) \
            job = &gJobDefinitions[job->inherit]; \
        else \
            return job->field; \
        break

u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 property)
{
    const struct JobDefinition *job = &gJobDefinitions[job_id];

    for (;;) {
        switch (property) {
        READ_JOB_PROPERTY(0, p00);
        READ_JOB_PROPERTY(1, p01);
        case 2: return job->inherit;
        READ_JOB_PROPERTY(3, p03);
        READ_JOB_PROPERTY(4, p04);
        READ_JOB_PROPERTY(5, p05);
        READ_JOB_PROPERTY(6, p06);
        READ_JOB_PROPERTY(7, p07);
        READ_JOB_PROPERTY(8, p08);
        READ_JOB_PROPERTY(9, p09);
        READ_JOB_PROPERTY(10, p10);
        READ_JOB_PROPERTY(11, p11);
        READ_JOB_PROPERTY(12, p12);
        READ_JOB_PROPERTY(13, p13);
        READ_JOB_PROPERTY(14, p14);
        READ_JOB_PROPERTY(15, p15);
        READ_JOB_PROPERTY(16, p16);
        READ_JOB_PROPERTY(17, p17);
        READ_JOB_PROPERTY(18, p18);
        READ_JOB_PROPERTY(19, p19);
        READ_JOB_PROPERTY(20, p20);
        READ_JOB_PROPERTY(21, p21);
        READ_JOB_PROPERTY(22, p22);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_HP, base_hp);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_MP, base_mp);
        READ_JOB_PROPERTY(25, p25);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_WEAPON_ATTACK, base_weapon_attack);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_WEAPON_DEFENSE, base_weapon_defense);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_MAGIC_POWER, base_magic_power);
        READ_JOB_PROPERTY(JOB_PROPERTY_BASE_MAGIC_RESISTANCE, base_magic_resistance);
        READ_JOB_PROPERTY(30, p30);
        READ_JOB_PROPERTY(31, p31);
        READ_JOB_PROPERTY(32, p32);
        READ_JOB_PROPERTY(34, p34);
        READ_JOB_PROPERTY(35, p35);
        READ_JOB_PROPERTY(33, p33);
        READ_JOB_PROPERTY(JOB_PROPERTY_EQUIPMENT_CLASS_MASK_INDEX, equipment_class_mask_index);
        READ_JOB_PROPERTY(JOB_PROPERTY_FIRST_ABILITY_INDEX, first_ability_index);
        READ_JOB_PROPERTY(JOB_PROPERTY_LAST_ABILITY_INDEX, last_ability_index);
        READ_JOB_PROPERTY(39, p39);
        READ_JOB_PROPERTY(40, p40);
        READ_JOB_PROPERTY(JOB_PROPERTY_HP_GROWTH_TENTHS, hp_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_MP_GROWTH_TENTHS, mp_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_SPEED_GROWTH_TENTHS, speed_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_WEAPON_ATTACK_GROWTH_TENTHS, weapon_attack_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_WEAPON_DEFENSE_GROWTH_TENTHS, weapon_defense_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_MAGIC_POWER_GROWTH_TENTHS, magic_power_growth_tenths);
        READ_JOB_PROPERTY(JOB_PROPERTY_MAGIC_RESISTANCE_GROWTH_TENTHS, magic_resistance_growth_tenths);
        }
    }
}

#undef READ_JOB_PROPERTY
