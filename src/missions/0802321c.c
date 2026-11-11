typedef unsigned char u8;typedef unsigned short u16;
typedef struct {u8 unknown0[148];u16 state_flags;} GameState;
extern GameState Game __asm__("0x0200f390");
void *CurrentContext(void) __asm__("RetailCall_08096d7c");
void AdvanceContext(void*) __asm__("RetailCall_0809a3f4");
u8 GetFlag(unsigned int) __asm__("RetailCall_080c9540");
void DispatchFlagged(u8,void*) __asm__("RetailCall_08070c94");
void DispatchOrdinary(u8,void*) __asm__("RetailCall_08070604");
/* Flag74 chooses the game-specific dispatcher. The context getter is
 * intentionally repeated after its nonnull test; callbacks may change it. */
void DispatchGameCommandByFlag74(u8 command,void *payload)
{
 if(!(Game.state_flags&2)&&CurrentContext())AdvanceContext(CurrentContext());
 if(GetFlag(74))DispatchFlagged(command,payload);
 else DispatchOrdinary(command,payload);
}
asm(".global RetailCall_08070604\n.thumb_set RetailCall_08070604,0x08070605\n.global RetailCall_08070c94\n.thumb_set RetailCall_08070c94,0x08070c95\n.global RetailCall_08096d7c\n.thumb_set RetailCall_08096d7c,0x08096d7d\n.global RetailCall_0809a3f4\n.thumb_set RetailCall_0809a3f4,0x0809a3f5\n.global RetailCall_080c9540\n.thumb_set RetailCall_080c9540,0x080c9541\n");
