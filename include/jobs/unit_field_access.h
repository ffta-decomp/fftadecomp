#ifndef FFTA_JOBS_UNIT_FIELD_ACCESS_H
#define FFTA_JOBS_UNIT_FIELD_ACCESS_H

/* ReadUnitField selectors for the live unit record. */
#define UNIT_FIELD_LEVEL 6
#define UNIT_FIELD_EXPERIENCE 7
#define UNIT_FIELD_CURRENT_HP 19
#define UNIT_FIELD_MAX_HP 20
#define UNIT_FIELD_CURRENT_MP 21
#define UNIT_FIELD_MAX_MP 22

/* Keep each caller's existing declaration of ReadUnitField. */
#define ReadUnitLevel(unit) ReadUnitField(unit, UNIT_FIELD_LEVEL)
#define ReadUnitExperience(unit) ReadUnitField(unit, UNIT_FIELD_EXPERIENCE)
#define ReadUnitCurrentHp(unit) ReadUnitField(unit, UNIT_FIELD_CURRENT_HP)
#define ReadUnitMaxHp(unit) ReadUnitField(unit, UNIT_FIELD_MAX_HP)
#define ReadUnitCurrentMp(unit) ReadUnitField(unit, UNIT_FIELD_CURRENT_MP)
#define ReadUnitMaxMp(unit) ReadUnitField(unit, UNIT_FIELD_MAX_MP)

#endif
