typedef unsigned char u8;
typedef signed short s16;
struct NativeWindowExtent {
    u8 unknown00[32];
    s16 width,height,target_width,target_height,width_step,height_step;
};
void AdvanceNativeWindowExtents(struct NativeWindowExtent*) asm("Remaining38_00016B50");
void AdvanceNativeWindowExtents(struct NativeWindowExtent *window)
{
    /* Preserve the native height-before-width updates and wrapped halfword
     * intermediate stores, including the equality arm's subtract/clamp. */
    if(window->height < window->target_height) {
        window->height += window->height_step;
        if(window->height > window->target_height)
            window->height=window->target_height;
    } else {
        window->height -= window->height_step;
        if(window->height < window->target_height)
            window->height=window->target_height;
    }
    if(window->width < window->target_width) {
        window->width += window->width_step;
        if(window->width > window->target_width)
            window->width=window->target_width;
    } else {
        window->width -= window->width_step;
        if(window->width < window->target_width)
            window->width=window->target_width;
    }
}
