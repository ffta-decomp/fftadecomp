typedef unsigned int u32;
extern void *AllocatePoolBytes(void *pool, u32 byte_count);
void *AllocateGlobalPoolBytes(u32 byte_count)
{
    return AllocatePoolBytes(*(void **)0x0200f434, byte_count);
}
asm(".global AllocatePoolBytes\n.thumb_set AllocatePoolBytes,0x08007139\n");
