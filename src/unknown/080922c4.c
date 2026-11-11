typedef unsigned short u16;

void MarkBattleRecordPhaseThree(void *record)
{
    /* This object field is separate from the owning controller selector. */
    *(u16 *)((unsigned char *)record + 100) = 3;
}
