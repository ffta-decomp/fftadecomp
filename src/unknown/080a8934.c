struct UnitProgressResult;
extern struct UnitProgressResult *BuildUnitProgressResults(void *first_context,
                                                          void *second_context);
/* The native entry selects the existing single-input growth transaction. */
struct UnitProgressResult *BuildSingleContextProgressResults(void *context)
{
    return BuildUnitProgressResults(context, 0);
}
asm(".global BuildUnitProgressResults\n.thumb_set BuildUnitProgressResults,0x080A7139\n");
