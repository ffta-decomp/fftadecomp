#ifndef FFTA_JOB_MODEL_C05_H
#define FFTA_JOB_MODEL_C05_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct JobChangeEquipmentView {
    u8 unit_prefix[0x2a];
    u16 equipment_slots[5];
} JobChangeEquipmentView;

typedef char JobChangeEquipmentViewSizeMustBe52[
    (sizeof(JobChangeEquipmentView) == 0x34) ? 1 : -1];

void ReplaceEquipmentSlotForScan(JobChangeEquipmentView *unit,
                                 u16 replacement_item_id,
                                 u8 slot_index);
u32 GetJobProperty(u8 job_id, u8 fallback_job_id, u8 property_id);
u32 ReadUnitField(const u8 *unit, u32 field_id);
u8 UnitField04Equals24(const u8 *unit);
/* Existing external alias already resolves to the selected C implementation. */
void UnitModelCall_CA2E8(u8 *unit);
#define UpdateUnitDerivedBytes UnitModelCall_CA2E8

void ClearUnitEquipmentForJobChange(u8 *unit);
void ClearUnitEquipmentForJobChangeBody(u8 *unit);
void ApplyUnitJob(u8 *unit, u8 requested_job_id);

#endif
