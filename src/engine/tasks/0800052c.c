/* The task descriptor layout and callback roles remain unknown. */
extern void ConfigureTaskGroup(void *group, void *storage, void *state, unsigned int count);
extern void AttachTaskCallback(void *group, unsigned int index, void *callback);

void InitializeTaskDescriptors(void)
{
    ConfigureTaskGroup((void *)0x03000880, (void *)0x03002860, (void *)0x03000eb8, 4);
    ConfigureTaskGroup((void *)0x030027e0, (void *)0x03000e4c, (void *)0x030009a8, 1);
    ConfigureTaskGroup((void *)0x03000e10, (void *)0x03002800, (void *)0x030027d0, 3);
    AttachTaskCallback((void *)0x03000e10, 0, (void *)0x08003661);
}
