typedef unsigned char u8;
typedef unsigned int u32;
/* Only observed object prefix fields are named; no allocation-size claim. */
typedef struct { u32 field_00; void *record_pool; } NativeRecordControlPrefix;
extern u8 *gNativePanelState;
extern NativeRecordControlPrefix gNativeRecordControl;
extern void SetNativeRecordBytePair(void *,u8,u8,u8);
__asm__(".global gNativePanelState\n.set gNativePanelState,0x03002818\n"
        ".global gNativeRecordControl\n.set gNativeRecordControl,0x03000e30\n"
        ".global SetNativeRecordBytePair\n.thumb_set SetNativeRecordBytePair,0x0804c789");
void HideNativePanelOptionalWidgets(u8 *pane) __asm__("CoreGlobal36_00088F5C");
void HideNativePanelOptionalWidgets(u8 *pane)
{
    u32 flags = pane[0];
    u32 clear_mask = ~1u;
    /* Original full-word -2 mask and byte input meet before the byte store.
       Both operands are initialized; no fixed register, clobber or instruction. */
    asm("" : "+r"(clear_mask) : "r"(flags));
    pane[0] = (u8)(clear_mask & flags);
    if (gNativePanelState[0x569] != 0) {
        void *pool = gNativeRecordControl.record_pool;
        u8 slot = pane[0x10d];
        SetNativeRecordBytePair(pool,slot,240,240);
    }
    if (gNativePanelState[0x56a] != 0) {
        void *pool = gNativeRecordControl.record_pool;
        u8 slot = pane[0x10e];
        SetNativeRecordBytePair(pool,slot,240,240);
    }
    if (gNativePanelState[0x56b] != 0) {
        void *pool = gNativeRecordControl.record_pool;
        u8 slot = pane[0x10f];
        SetNativeRecordBytePair(pool,slot,240,240);
    }
}
