typedef unsigned char u8;
typedef unsigned int u32;
struct ResourceState { u8 state; };
u32 sub_08010FF0(const struct ResourceState *resource)
{
    if(resource->state == 2)return 1;
    return 0;
}
