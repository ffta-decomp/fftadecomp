typedef unsigned char u8;
struct MarkerNode { void *object; u8 active, column, row, cell; struct MarkerNode *next; };
struct MarkerList { struct MarkerNode *head; struct MarkerNode nodes[13]; unsigned int counter; };
extern u8 ReadMarkerMapCell_0801CC18(u8, u8);
void CoreClosure31_000BA818(struct MarkerList *state_argument, u8 column, u8 row)
{
    register struct MarkerList *incoming asm("r0") = state_argument;
    register struct MarkerList *state asm("r5");
    register struct MarkerNode *node asm("r4");
    /* Original 2-byte ADD captures the real state pointer after byte-argument
       normalization. The output is actually defined; cc is overwritten. */
    asm("add %0, %1, #0" : "=r" (state) : "r" (incoming) : "cc");
    {
        register int index asm("r2") = 0;
        register u8 *probe asm("r1");
        register unsigned int offset asm("r4");
        asm("" : : "r" (index));
        probe = (u8 *)state;
        asm("" : : "r" (probe));
        offset = 0;
        asm("" : : "r" (offset));
        do {
            register unsigned int snapshot asm("r3") = offset;
            asm("" : : "r" (snapshot));
            if (probe[8] == 0) {
                register unsigned int displacement asm("r0") = offset + 4;
                asm("" : "+r" (displacement));
                /* Original 2-byte ADD forms node = state + offset + 4. */
                asm("add %0, %1, %2" : "=r" (node)
                    : "r" (state), "r" (displacement) : "cc");
                goto found;
            }
            probe += 12;
            offset += 12;
            ++index;
        } while (index <= 12);
    }
    node = 0;
found:
    node->active = 1;
    node->column = column;
    node->row = row;
    node->cell = ReadMarkerMapCell_0801CC18(column, row);
    {
    register struct MarkerNode *head asm("r0") = state->head;
    asm("" : : "r" (head));
    if (head == 0) {
        state->head = node;
    } else {
        register struct MarkerNode *tail asm("r1") = head;
        asm("" : "+r" (tail));
        while (tail->next != 0)
            tail = tail->next;
        tail->next = node;
        node->next = 0;
    }
}

}

asm(".thumb_set ReadMarkerMapCell_0801CC18,0x0801cc19\n");
