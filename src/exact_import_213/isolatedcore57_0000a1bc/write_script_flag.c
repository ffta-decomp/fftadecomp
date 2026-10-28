typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void SetGameFlag(u16, u16) __asm__("0x080c9574");
void WriteNestedScriptFlag(void *, const u8 *) __asm__("IsolatedCore57_0000A1BC");
void WriteNestedScriptFlag(void *context, const u8 *command)
{
    u32 flag = command[1] | (command[2] << 8);
    SetGameFlag(flag, command[3]);
}
