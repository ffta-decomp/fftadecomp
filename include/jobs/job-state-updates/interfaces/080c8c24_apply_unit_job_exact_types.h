typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {u8 unknown52;u8 primary;u8 secondary;u8 kind24;} JobTraits;
typedef struct {u8 unknown[4];u8 kind;u8 primary_job;u8 unknown6;u8 current_job;u8 secondary_job;u8 unknown9[2];u8 property13;u8 initialized;u8 property14;u8 property15;u8 property16;u8 property17;u8 property18;u8 property19;u8 property20;u8 property21;u8 unknown21[31];JobTraits traits;} Unit;
void ClearEquipment(Unit*) __asm__("ClearUnitEquipmentForJobChange");
u32 JobProperty(u32,u32,u32) __asm__("GetJobProperty");
u32 ReadField(Unit*,u32) __asm__("RetailCall_080c7ea4");
u32 IsKind24(Unit*) __asm__("UnitField04Equals24");
void UpdateDerived(Unit*) __asm__("UnitModelCall_CA2E8");
