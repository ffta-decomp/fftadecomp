#include "interfaces.h"
void EraseConfirmedCollectionRecord(u8 collection) __asm__("SceneTaskDependency_000CC510");
void EraseConfirmedCollectionRecord(u8 collection)
{
    gCollectionSave.records[collection].field_00 = 0;
    gCollectionSave.records[collection].field_02 = 0;
    gCollectionSave.records[collection].byte_05 = 0;
    gCollectionSave.records[collection].byte_06 = 0;
    gCollectionSave.records[collection].count = 0;
    gCollectionSave.records[collection].field_08 = 0;
    gCollectionSave.records[collection].field_0a = 0;
    gCollectionSave.records[collection].field_0c = 0;
    gCollectionSave.records[collection].field_0e = 0;
}
