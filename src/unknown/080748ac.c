extern void ConfigureUnitPanel(void *,unsigned,unsigned);
asm(".global ConfigureUnitPanel\n.thumb_set ConfigureUnitPanel,0x080717cd");
void CoreScene34_000748AC(void *unit){ConfigureUnitPanel(unit,0,3);}
