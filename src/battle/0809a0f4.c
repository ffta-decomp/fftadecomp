/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct Unit;
struct Parent { u8 prefix[8]; void *allocation_context; };
struct Owner {
    struct Unit *unit;
    u8 bytes04[60];
    void *context;
    u8 bytes44[16];
    void *first_buffer;
    void *second_buffer;
    u8 bytes5c[36];
    struct Parent *parent;
};
typedef char ContextOffset[(u32)&((struct Owner*)0)->context==64?1:-1];
typedef char BufferOffset[(u32)&((struct Owner*)0)->first_buffer==84?1:-1];
typedef char SecondBufferOffset[(u32)&((struct Owner*)0)->second_buffer==88?1:-1];
typedef char ParentOffset[(u32)&((struct Owner*)0)->parent==128?1:-1];
extern void *CreateBufferContext(void *allocation_context);
extern void *AllocatePolicyBuffer(void);
extern u32 GetUnitProperty(const struct Unit *unit, u8 selector);
extern u32 ReadUnitField(const struct Unit *unit, u8 selector);
extern void (*InitializePolicyBuffer)(void *buffer, void *context);
extern void (*LoadPolicyData)(void *buffer, const void *data);
extern const u8 gSelectedPolicy[];
extern const u8 gDefaultPolicy[];
__asm__(".global CreateBufferContext\n.thumb_set CreateBufferContext, 0x8021b1d");
__asm__(".global AllocatePolicyBuffer\n.thumb_set AllocatePolicyBuffer, 0x808f79d");
__asm__(".global GetUnitProperty\n.thumb_set GetUnitProperty, 0x80c92f1");
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x80c7ea5");
__asm__(".global InitializePolicyBuffer\n.set InitializePolicyBuffer, 0x8394030");
__asm__(".global LoadPolicyData\n.set LoadPolicyData, 0x8394038");
__asm__(".global gSelectedPolicy\n.set gSelectedPolicy, 0x8391576");
__asm__(".global gDefaultPolicy\n.set gDefaultPolicy, 0x8391584");


/* Preserve repeated live unit queries and the original double first-buffer initialization. */
void InitializeUnitPolicyBuffers(struct Owner *owner)
{
    owner->context = CreateBufferContext(owner->parent->allocation_context);
    owner->first_buffer = AllocatePolicyBuffer();
    owner->second_buffer = AllocatePolicyBuffer();
    InitializePolicyBuffer(owner->first_buffer, owner->context);
    InitializePolicyBuffer(owner->first_buffer, owner->context);
    if (GetUnitProperty(owner->unit, 3) == 1
        || ReadUnitField(owner->unit, 1) == 6
        || ReadUnitField(owner->unit, 1) == 18
        || ReadUnitField(owner->unit, 1) == 30
        || ReadUnitField(owner->unit, 1) == 57
        || ReadUnitField(owner->unit, 1) == 58
        || ReadUnitField(owner->unit, 1) == 59
        || ReadUnitField(owner->unit, 1) == 60
        || ReadUnitField(owner->unit, 1) == 61
        || ReadUnitField(owner->unit, 1) == 62
        || ReadUnitField(owner->unit, 1) == 63
        || ReadUnitField(owner->unit, 1) == 23
        || ReadUnitField(owner->unit, 1) == 14
        || ReadUnitField(owner->unit, 1) == 75
    ) {
        LoadPolicyData(owner->second_buffer, gSelectedPolicy);
    } else {
        LoadPolicyData(owner->second_buffer, gDefaultPolicy);
    }
}
