typedef unsigned int u32;
extern void PopulateEligibleMissionQueue(u32 refresh);
asm(".global PopulateEligibleMissionQueue\n.thumb_set PopulateEligibleMissionQueue,0x080cfcd1");

/* The original entry explicitly requests progress/offer/queue refresh first. */
void RefreshEligibleMissionQueue(void)
{
    PopulateEligibleMissionQueue(1);
}
