typedef unsigned int u32;
extern void ConfigureNameEditorBackground(u32,u32,u32,u32,u32,void *,void *) asm("RetailCall_0801e458");
asm(".global RetailCall_0801e458\n.thumb_set RetailCall_0801e458,0x0801e459\n");
void InitializeNameEditorBackgrounds(void) asm("CoreRegion_0012B340");
void InitializeNameEditorBackgrounds(void)
{
    ConfigureNameEditorBackground(2,1,0,208,0,(void *)0x06008000,(void *)0x0600e000);
    ConfigureNameEditorBackground(3,1,1,208,0,(void *)0x06008000,(void *)0x06005000);
}
