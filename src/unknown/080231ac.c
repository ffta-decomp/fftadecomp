/* C09 selector80 delegates the three observed setup steps in order. */
extern void RestoreDisplayLayerState(void);
extern void ConfigureDisplayLayerBindings(void);
extern void RefreshDisplayRegisterShadow(void);
__asm__(".global RestoreDisplayLayerState\n.thumb_set RestoreDisplayLayerState,0x0801d495");
__asm__(".global ConfigureDisplayLayerBindings\n.thumb_set ConfigureDisplayLayerBindings,0x08022875");
__asm__(".global RefreshDisplayRegisterShadow\n.thumb_set RefreshDisplayRegisterShadow,0x08022b25");
void RunBattleDisplaySetupSequence(void)
{
    RestoreDisplayLayerState();
    ConfigureDisplayLayerBindings();
    RefreshDisplayRegisterShadow();
}
