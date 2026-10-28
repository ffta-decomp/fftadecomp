typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DisplayStateNode {
    struct DisplayStateNode *next;
    u16 state;
    u16 unused;
} DisplayStateNode;

extern void CallR2Trampoline(void *destination, u32 length, u32 target);

/* Clear both list nodes, then activate the first node in state 11. */
void ResetDisplayStateList(void)
{
    register const u32 *clear_routine __asm__("r6") = (const u32 *)0x0836d4b8;
    register DisplayStateNode *nodes __asm__("r4") = (DisplayStateNode *)0x030034c0;
    u32 clear_target = *clear_routine;

    CallR2Trampoline(nodes, 16, clear_target);
    {
        register volatile u8 *flag __asm__("r1") = (volatile u8 *)0x030034d0;
        register DisplayStateNode *volatile *head __asm__("r5");
        /* Keep the flag address load before the head address load. */
        __asm__ volatile("" : "+r"(flag));
        head = (DisplayStateNode *volatile *)0x030034b8;
        *flag = 1;
        *head = nodes;
        clear_target = *clear_routine;
        CallR2Trampoline(nodes, 8, clear_target);
        (*head)->state = 11;
    }
}
