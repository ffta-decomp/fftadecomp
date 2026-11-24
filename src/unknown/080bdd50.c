struct BattleRecordWorkset;
extern void FreeGlobalPoolBytes(void *);
void ReleaseBattleRecordWorkset(struct BattleRecordWorkset *workset)
{
    FreeGlobalPoolBytes(workset);
}
asm(".global FreeGlobalPoolBytes\n.thumb_set FreeGlobalPoolBytes,0x08022855\n");
