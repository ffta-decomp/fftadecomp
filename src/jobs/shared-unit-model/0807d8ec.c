/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 RetailCall_080c9078(void *);
extern void RetailCall_080cce60(void *,u32,u8 *,u8 *);
asm(".global RetailCall_080c9078\n.thumb_set RetailCall_080c9078,0x080c9079\n.global RetailCall_080cce60\n.thumb_set RetailCall_080cce60,0x080cce61");

u32 UnitChoiceHasEnabledAbility(u8 choice)
{
    u8 bounds[2];
    u8 **root;
    int index;
    int last;
    u8 *flags;
    u8 *upper;
    void *query;
    if (choice==1)
        return 1;
    root=(u8 **)0x03002818;
    (*root)[0x1c1a]=choice;
    (*root)[0x1bec]=RetailCall_080c9078(*root+0x1be4);
    query=*root+0x1be4;
    upper=&bounds[1];
    RetailCall_080cce60(query,2,&bounds[0],upper);
    index=bounds[0];
    last=*upper;
    if (index<=last) {
        flags=*(u8 **)(*root+0x1d0c)+64;
        do {
            if (flags[index])
                return 1;
            index++;
        } while (index<=last);
    }
    return 0;
}
