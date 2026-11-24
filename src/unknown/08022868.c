/* Actual shared pool cell consumed by the candidate-container allocator. */
void *GetSharedAllocationPool(void)
{
    return *(void * const *)0x0200f434;
}
