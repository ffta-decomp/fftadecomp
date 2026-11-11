typedef unsigned char u8;
typedef unsigned int u32;
struct ManagedTransitionRequest { u8 unknown_00[3]; u8 value; };
extern struct ManagedTransitionRequest gManagedTransitionRequest;
void WriteManagedTransitionRequestByte(u32 value)
{
    gManagedTransitionRequest.value = value;
}
asm(".global gManagedTransitionRequest\n.set gManagedTransitionRequest, 0x0200ffc8\n");
