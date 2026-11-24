/* Method-local interface declarations from the frozen build. */
typedef unsigned short u16;
extern unsigned int ReadSelectionIndex(void);
extern void *GetContentContext(void);
extern void ApplySelectionToContext(u16,void *);

asm(".global ReadSelectionIndex\n.thumb_set ReadSelectionIndex,0x800a019\n.global GetContentContext\n.thumb_set GetContentContext,0x8096d7d\n.global ApplySelectionToContext\n.thumb_set ApplySelectionToContext,0x8096e19");
unsigned int ApplyCurrentSelectionToSceneContext(void)
{
    u16 index = ReadSelectionIndex();
    ApplySelectionToContext(index,GetContentContext());
    return 272;
}
