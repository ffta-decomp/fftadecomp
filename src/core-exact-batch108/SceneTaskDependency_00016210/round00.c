typedef unsigned char u8;
typedef unsigned short u16;
struct ManagedControllerExtent { u8 unknown_00[18]; u8 extent_x, extent_y; };
extern void SetManagedControllerDataExtent(struct ManagedControllerExtent *, void *,
                                         unsigned int, unsigned int, unsigned int, unsigned int);
void SetManagedControllerData(struct ManagedControllerExtent *controller, void *buffer,
                              u16 first_value, u16 second_value)
{
    SetManagedControllerDataExtent(controller, buffer, controller->extent_x,
                                   controller->extent_y, first_value, second_value);
}
asm(".thumb_set SetManagedControllerDataExtent, 0x08015c91\n");
