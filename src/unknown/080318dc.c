/* Contributed by gg; original source and attribution follow. */
/* CoreRegion_000318DC
   entry 0x080318DC, 12 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned int u32;
extern void PopulateEligibleMissionQueue(u32 refresh);
asm(".global PopulateEligibleMissionQueue\n.thumb_set PopulateEligibleMissionQueue,0x8031709");

/* The original entry explicitly requests progress/offer/queue refresh first. */
void RefreshEligibleMissionQueue(void)
{
    PopulateEligibleMissionQueue(254);
}
