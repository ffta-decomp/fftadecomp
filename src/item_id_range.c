typedef unsigned char bool8;
typedef unsigned short u16;

/* This predicate establishes only the contiguous numeric range 1 through 252. */
bool8 IsItemIdInRange1To252(u16 item_id)
{
    return (u16)(item_id - 1) <= 251;
}
