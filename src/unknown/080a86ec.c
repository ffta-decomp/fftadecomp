typedef signed short s16;
struct BattleContext;
struct ContextSelection { unsigned char unknown[78]; s16 selected; };
struct BattleContext *CoreRegion30_000A86EC(struct ContextSelection *selection)
{
    register struct ContextSelection *base asm("r0") = selection;
    register int offset asm("r1") = base->selected * 4;
    /* Original input base stays unchanged while the signed selector is read. */
    asm("" : "+r"(offset) : "r"(base));
    base = (struct ContextSelection *)((unsigned char *)base + 8);
    /* Preserve the separately formed slot base before the indexed word load. */
    asm("" : "+r"(base) : "r"(offset));
    return *(struct BattleContext **)((unsigned int)base + offset);
}
