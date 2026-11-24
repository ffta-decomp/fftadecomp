typedef unsigned char u8;
typedef unsigned int u32;
struct Record {u8 unknown0[48];u32 flags;};
void sub_080DBEB4(struct Record *record,u8 mode)
{
    if(mode)record->flags &= ~1u;
    else record->flags |= 1;
}
