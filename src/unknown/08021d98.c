typedef unsigned int u32;
struct HandlePrimaryWord { u32 value; };
/* The wider handle role is tentative; this entry writes one complete word. */
void StoreHandlePrimaryWord(struct HandlePrimaryWord *slot, u32 value)
{
    slot->value = value;
}
