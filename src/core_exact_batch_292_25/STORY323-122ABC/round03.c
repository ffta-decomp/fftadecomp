typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SceneCommandContext {
 s16 offset;
 u8 unknown02[10];
 const u8 *base;
};
typedef u32 (*SceneCommandHandler)(struct SceneCommandContext *,const u8 *);
struct SceneCommandDescriptor {
 u16 length;
 SceneCommandHandler handler;
} __attribute__((packed));
typedef char DescriptorStride[(sizeof(struct SceneCommandDescriptor)==6)?1:-1];
extern const struct SceneCommandDescriptor gSceneCommandDescriptors[];
u32 RunSceneCommandLoop_08122ABC(struct SceneCommandContext *context)
{
 const struct SceneCommandDescriptor *descriptor;
 const struct SceneCommandDescriptor *bank;
 const u8 *command;
 u32 status;
 u32 descriptor_offset;
 bank=gSceneCommandDescriptors;
 /* The original initializes this real bank once, retained across every handler. */
 asm("" : "+r"(bank));
 do {
  command=context->base+context->offset;
  descriptor_offset=6U*command[0];
  descriptor=(const struct SceneCommandDescriptor *)(descriptor_offset+(u32)bank);
  status=descriptor->handler(context,command);
  context->offset=(u16)context->offset+descriptor->length;
 } while(status==0x110);
 return status;
}
asm(".global gSceneCommandDescriptors\n.set gSceneCommandDescriptors,0x083A7EE4\n.global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
