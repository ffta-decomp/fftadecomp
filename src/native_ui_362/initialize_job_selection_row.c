typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 * volatile JobMenuOwner asm("0x03002818");
extern void *JobMenuResources[] asm("0x03000e30");
extern u16 *ResolveJobMenuCell(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void PrepareJobMenuObject(void*,u32) asm("RetailCall_0804c7a0");
asm(".global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n.global RetailCall_0804c7a0\n.thumb_set RetailCall_0804c7a0,0x0804c7a1\n");
void InitializeJobSelectionRow(void) asm("CoreScene34_00080E00");
void InitializeJobSelectionRow(void)
{
    u16 *first = ResolveJobMenuCell(0,1,26,19);
    u16 zero = 0;
    int index;
    u16 *fourth;
    *first = zero;
    *ResolveJobMenuCell(0,1,27,19) = zero;
    *ResolveJobMenuCell(0,1,28,19) = zero;
    fourth = ResolveJobMenuCell(0,1,29,19);
    /* The actual fourth tile store consumes this initialized working zero.
     * Its lifetime is separate from the later signed ordinal initialization. */
    asm volatile("" : "+r"(zero));
    *fourth = zero;
    PrepareJobMenuObject(JobMenuResources[1],26);
    index = 0;
    while (index < *(u8 *)(JobMenuOwner+0x95c)) {
        *ResolveJobMenuCell(0,1,index+2,19) = 0;
        ++index;
    }
}
