extern unsigned char *gSceneAssociationContext;
__asm__(".global gSceneAssociationContext\n.set gSceneAssociationContext,0x020159cc");
unsigned char *GetSceneIndexedAssociation(unsigned char index)
{
    unsigned char *base=gSceneAssociationContext;
    unsigned char *result;
    if (base)
        result=base+1240+((unsigned)index<<3);
    else
        result=0;
    return result;
}
