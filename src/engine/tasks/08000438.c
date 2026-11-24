/* The task descriptor layout and exact role of each group remain unknown. */
extern void RunTaskGroup(void *group, unsigned int count);

void RunInitialTaskGroups(void)
{
    RunTaskGroup((void *)0x03000880, 4);
    RunTaskGroup((void *)0x030027e0, 1);
}
