typedef unsigned char u8;
typedef unsigned int u32;
struct ResourceOption { u8 unknown0[42]; u8 option; };
void CoreDependency29_00011138(struct ResourceOption *resource,u32 option)
{
    resource->option=option;
}
