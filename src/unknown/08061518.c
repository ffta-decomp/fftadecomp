typedef unsigned char u8;
typedef unsigned int u32;
extern u8 gDialogOutput[];
extern u8 gDialogState[];
extern void SetWindowRectangle(u32,u32,u32,u32);
extern void InitializeDialogRecord(void *,u32,u32,void *,void *,u32,u32,u32,u32,u32);
void InitializeBank9MenuRecord(void *record,u32 ordinal)
{
 u8 record_ordinal=ordinal;
 SetWindowRectangle(0,0,0,0);
 InitializeDialogRecord(record,9,record_ordinal,gDialogOutput,gDialogState,2,1,24,16,448);
}
asm(".global gDialogOutput\n.set gDialogOutput,0x030008b0\n.global gDialogState\n.set gDialogState,0x03000990\n.global SetWindowRectangle\n.thumb_set SetWindowRectangle,0x0802a2c1\n.global InitializeDialogRecord\n.thumb_set InitializeDialogRecord,0x0801174d");
