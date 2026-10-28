typedef unsigned int u32;

/* The caller supplies its node+68 object. Individual flag meanings are unknown. */
void PrepareOperationObjectFlags(u32 *object_flags)
{
    u32 flags = *object_flags;
    flags &= 0xfffdff7f;
    flags |= 0x90000;
    *object_flags = flags;
}
