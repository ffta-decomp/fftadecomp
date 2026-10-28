typedef unsigned short u16;

extern void Routine_08001194(void);
extern void Routine_08001244(void);
extern void RunTaskGroup(void *group, unsigned int count);
extern void Routine_08002804(void);
extern void Routine_08001cd0(void);
extern void Routine_08001ce0(void);
extern void Routine_0800221c(void *state, u16 buttons);
extern unsigned char gDisplayDefaults;

/* The roles of the called subsystems remain under investigation. */
void InitializeRuntimeState(void)
{
    Routine_08001194();
    Routine_08001244();
    RunTaskGroup((void *)0x03000e10, 3);
    Routine_08002804();
    Routine_08001cd0();
    Routine_08001ce0();
    Routine_0800221c(&gDisplayDefaults,
                     (*(volatile u16 *)0x04000130 ^ 0x03ff) & 0xffff);
}
