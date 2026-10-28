#include "apply_unit_job_exact_types.h"
void ApplyUnitJob(Unit *unit,u8 job)
{
 JobTraits *traits;
 u8 zero;
 u8 one;
 u8 kind24;
 ClearEquipment(unit);
 if (unit->kind==1) unit->primary_job=job;
 zero=0;
 unit->current_job=job;
 if (unit->secondary_job==job) unit->secondary_job=zero;
 unit->property13=JobProperty(unit->primary_job,unit->current_job,13);
 one=1;
 unit->initialized=one;
 unit->property14=JobProperty(unit->primary_job,unit->current_job,14);
 unit->property15=JobProperty(unit->primary_job,unit->current_job,15);
 unit->property16=JobProperty(unit->primary_job,unit->current_job,16);
 unit->property17=JobProperty(unit->primary_job,unit->current_job,17);
 unit->property18=JobProperty(unit->primary_job,unit->current_job,18);
 unit->property19=JobProperty(unit->primary_job,unit->current_job,19);
 unit->property20=JobProperty(unit->primary_job,unit->current_job,20);
 unit->property21=JobProperty(unit->primary_job,unit->current_job,21);
 traits=&unit->traits;
 traits->primary=JobProperty(unit->primary_job,unit->current_job,12);
 if (ReadField(unit,5)!=0) traits->secondary=JobProperty(unit->secondary_job,unit->secondary_job,12);
 if (traits->primary==traits->secondary) {
  traits->secondary=zero;
  unit->secondary_job=zero;
 }
 kind24=(u8)IsKind24(unit);
 if (kind24!=0) {
  traits->kind24=one;
  if (traits->secondary==1) {
   traits->secondary=zero;
   unit->secondary_job=zero;
  }
 } else traits->kind24=kind24;
 UpdateDerived(unit);
}
