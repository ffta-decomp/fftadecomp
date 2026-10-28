typedef unsigned char u8;
typedef unsigned int u32;

/* This object's bit18 meaning is unconfirmed; the setter tests only low8. */
void SetOperationObjectFlag(u32 *object_flags, u8 set_flag)
{
    if (set_flag)
        *object_flags |= 0x40000;
    else
        *object_flags &= 0xfffbffff;
}
