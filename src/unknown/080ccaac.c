typedef unsigned char u8;
typedef unsigned short u16;

extern u16 gPendingCollectionHalfwords[];

/* Place a value in the first empty halfword; a full queue is unchanged. */
void AddCollectionHalfword(u16 value)
{
    u8 index = 0;

    do {
        u16 *entry = &gPendingCollectionHalfwords[index];
        if (*entry == 0) {
            *entry = value;
            break;
        }
        index++;
    } while (index < 20);
}
