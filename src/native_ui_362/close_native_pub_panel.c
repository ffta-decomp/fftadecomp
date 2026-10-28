struct PubPanelPrefix {void *group;void *allocation;};
extern struct PubPanelPrefix *gPubPanel;
extern void PanelGroupOperation05A24(void*) asm("RetailCall_08005A24");
extern void PanelGroupOperation05B18(void*) asm("RetailCall_08005B18");
extern void PanelGroupOperation05C34(void*) asm("RetailCall_08005C34");
extern void ReleasePanelAllocation(void*) asm("RetailCall_08022854");
void ClosePubPanelStorage(void) asm("SceneRegisteredRoot_0005F414");
void ClosePubPanelStorage(void)
{
    struct PubPanelPrefix *initial=gPubPanel;
    if(initial) {
        void *allocation=initial->allocation;
        PanelGroupOperation05A24(initial->group);
        PanelGroupOperation05B18(gPubPanel->group);
        PanelGroupOperation05C34(gPubPanel->group);
        ReleasePanelAllocation(allocation);
        gPubPanel=0;
    }
}
__asm__(".global gPubPanel\n.set gPubPanel,0x0200F44C");
__asm__(".global RetailCall_08005A24\n.thumb_set RetailCall_08005A24,0x08005A25");
__asm__(".global RetailCall_08005B18\n.thumb_set RetailCall_08005B18,0x08005B19");
__asm__(".global RetailCall_08005C34\n.thumb_set RetailCall_08005C34,0x08005C35");
__asm__(".global RetailCall_08022854\n.thumb_set RetailCall_08022854,0x08022855");
