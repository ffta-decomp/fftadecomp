/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
struct Context { void *unit; u8 middle[124]; void *owner; };
extern u8 ReadSaveByte(unsigned key);
extern u8 CoreFrontier_0009AA10(void *object);
extern u8 BattleDependency_00133BC4(void *unit);
extern void *CoreFrontier_000970E8(void *owner, void *unit);
extern u8 contextFlags;
asm(".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n.global CoreFrontier_0009AA10\n.thumb_set CoreFrontier_0009AA10,0x0809aa11\n.global BattleDependency_00133BC4\n.thumb_set BattleDependency_00133BC4,0x08133bc5\n.global CoreFrontier_000970E8\n.thumb_set CoreFrontier_000970E8,0x080970e9\n.global contextFlags\n.set contextFlags,0x030028a0\n");

int ContextPassesRelatedUnitRule(struct Context *context)
{
    void *related;
    if (!ReadSaveByte(13) || CoreFrontier_0009AA10(context))
        return 0;
    if (!BattleDependency_00133BC4(context->unit))
        goto check_related;
allowed:
    return 1;
check_related:
    related = CoreFrontier_000970E8(context->owner, context->unit);
    if (related) {
        if (CoreFrontier_0009AA10(related))
            goto denied;
        else
            goto allowed;
    } else if (contextFlags & 8)
        goto allowed;
denied:
    return 0;
}
