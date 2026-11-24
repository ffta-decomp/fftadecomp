extern void ReleaseManagedTaskWorkBuffer(void *buffer);
__asm__(".global ReleaseManagedTaskWorkBuffer\n.thumb_set ReleaseManagedTaskWorkBuffer,0x0808f7cd");
void ReleaseNullableManagedWorkBuffer(void **buffer_cell) __asm__("CoreDependency29_000247FC");
void ReleaseNullableManagedWorkBuffer(void **buffer_cell)
{
    if (*buffer_cell != 0) {
        ReleaseManagedTaskWorkBuffer(*buffer_cell);
        *buffer_cell = 0;
    }
}
