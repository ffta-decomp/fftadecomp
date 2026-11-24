typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u32 NativeMapBufferWorkspace[];
extern u8 *NativeMapBufferRoot;
extern u8 NativeMapBufferResource[];
void InitializeNativeMapBuffers(void) asm("CoreRegion_000318E8");
void InitializeNativeMapBuffers(void)
{
    register u32 *workspace asm("r4");
    register u8 **root_cell asm("r0");
    register u32 resource_address asm("r5");
    register u32 zero asm("r2");
    register u32 *cursor asm("r3");
    register s32 remaining asm("r1");
    register u32 first_map asm("r1");
    register u32 second_map asm("r2");
    register u8 *root asm("r3");
    register u8 *root_field asm("r1");
    register u8 *third_map_field asm("r0");
    workspace=NativeMapBufferWorkspace;
    asm("" : "+r"(workspace));
    root_cell=&NativeMapBufferRoot;
    asm("" : "+r"(root_cell));
    resource_address=(u32)NativeMapBufferResource;
    asm("" : "+r"(resource_address));
    zero=0;
    asm("" : "+r"(zero));
    cursor=workspace+2;
    asm("" : "+r"(cursor));
    remaining=11;
    asm("" : "+r"(remaining));
    do {
        *cursor++=zero;
        remaining--;
    } while (remaining>=0);
    first_map=0x06005000;
    asm("" : "+r"(first_map));
    workspace[0]=first_map;
    second_map=0x06007000;
    asm("" : "+r"(second_map));
    workspace[1]=second_map;
    root=*root_cell;
    asm("" : "+r"(root));
    *(u32 *)(root+140)=first_map;
    root_field=root+136;
    asm("" : "+r"(root_field));
    *(u32 *)root_field=0x06006000;
    third_map_field=root+148;
    asm("" : "+r"(third_map_field));
    *(u32 *)third_map_field=second_map;
    root_field+=8;
    *(u32 *)root_field=0x06007800;
    root_field+=8;
    workspace[2]=*(u32 *)root_field;
    workspace[3]=*(u32 *)root_field+120;
    workspace[4]=*(u32 *)root_field+208;
    workspace[5]=*(u32 *)root_field+2080;
    workspace[6]=*(u32 *)root_field+3312;
    workspace[7]=*(u32 *)root_field+4768;
    workspace[12]=resource_address;
}
__asm__(".global NativeMapBufferWorkspace\n.set NativeMapBufferWorkspace,0x03002740\n"
        ".global NativeMapBufferRoot\n.set NativeMapBufferRoot,0x03002810\n"
        ".global NativeMapBufferResource\n.set NativeMapBufferResource,0x02003cb0\n");
