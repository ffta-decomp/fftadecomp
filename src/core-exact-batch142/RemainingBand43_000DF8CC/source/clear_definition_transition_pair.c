typedef unsigned short u16;
extern void ApplyDefinitionRecordTransition(void *record, u16 selector, u16 value);

void ClearDefinitionTransitionPair(void *record)
{
    ApplyDefinitionRecordTransition(record, 10, 0);
    ApplyDefinitionRecordTransition(record, 9, 0);
}

asm(".global ApplyDefinitionRecordTransition\n.thumb_set ApplyDefinitionRecordTransition,0x080DE151\n");
