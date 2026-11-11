typedef unsigned char u8;
extern void ConfigureTransitionFlags(void *transition,u8 enabled,u8 secondary);
extern void QueueTransition(void *transition);
void ActivateMenuPaletteTransition(void *transition)
{
 ConfigureTransitionFlags(transition,1,0);
 ConfigureTransitionFlags(transition,1,1);
 QueueTransition(transition);
}
__asm__(".global Registered39_001369EC\n.thumb_set Registered39_001369EC,ActivateMenuPaletteTransition\n.global ConfigureTransitionFlags\n.thumb_set ConfigureTransitionFlags,0x081486c9\n.global QueueTransition\n.thumb_set QueueTransition,0x08148601\n");
