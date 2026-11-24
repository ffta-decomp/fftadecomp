typedef signed short s16;
struct SequenceRange {unsigned char unknown0[12];s16 index,limit;};
int Remaining38_00021E3C(struct SequenceRange *object)
{
    register struct SequenceRange *base __asm__("r2") = object;
    register struct SequenceRange *reload __asm__("r3") = base;
    register int index __asm__("r1");
    int result;
    /* Native retains two defined aliases through the signed comparison and
     * reloads the second alias only on the subtract-one path. */
    asm("" : "+r" (base), "+r" (reload));
    index=base->index;
    if(index<base->limit)
        result = index;
    else
        result = reload->index-1;
    /* Original comparison snapshot remains live in r1 at the shared exit. */
    asm("" : : "r" (index), "r" (base));
    return result;
}
