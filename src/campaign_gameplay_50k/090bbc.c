typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u32 word;u16 offset,kind;u32 unknown8;} Definition;
typedef struct {u32 word,unknown4;u16 offset;u8 unknown10,kind;u32 unknown12;} SceneRecord;
typedef struct {void *first,*second;const Definition *definitions;SceneRecord records[11];u8 unknown188[956];} Scene;
typedef void (*CopyRoutine)(void*,const void*,u32);
extern u8 SceneRecordCount asm("0x0200f49c"),SceneFirstMode asm("0x0200f498"),SceneSecondMode asm("0x0200f4a0"),SceneThirdMode asm("0x0200f4a4");
extern const Definition SceneDefinitions[11] asm("0x08394288");
extern CopyRoutine const CurrentCopyRoutine asm("0x0836d4bc");
extern u16 DisplayControl asm("0x03000940");
extern void *Allocate(u32) asm("0x08022841");
extern void LoadAsset(const void*,void*,u32,u32) asm("0x08005319");
extern void InitializeTransfer(void*,void*,void*,u32) asm("0x08000a99");
extern void InitializePaletteJob(void*,const void*,void*,u32,u32,u32,u32) asm("0x08000bad");
extern const void *GetPalette(u32) asm("0x080cbabd");
extern void CallCopy(void*,const void*,u32,CopyRoutine) asm("0x08142251");
void CoreFrontier_00090BBC(Scene *scene)
{
 u32 i;
 const Definition *definitions,*definition;
 SceneRecord *record;
 CopyRoutine const *copy_cell;
 u8 *palette_destination;
 scene->first=Allocate(6144);
 scene->second=Allocate(3840);
 {
 register u8 *count_address asm("r1")=&SceneRecordCount;
 asm("" : "+r"(count_address));
 {
 register u32 initial_zero asm("r2")=0;
 asm("" : "+r"(initial_zero));
 *count_address=11;
 SceneFirstMode=6;
 SceneSecondMode=initial_zero;
 SceneThirdMode=8;
 }
 }
 i=0;
 definitions=SceneDefinitions;
 definition=definitions;
 record=scene->records;
 do {
  record->word=definition->word;
  record->offset=definition->offset+480;
  record->kind=definition->kind;
  definition++;
  record++;
  i++;
 }while(i<=10);
 scene->definitions=definitions;
 LoadAsset((void*)0x083bf308,scene->first,3,1);
 LoadAsset((void*)0x083c05e8,scene->second,3,1);
 InitializeTransfer((u8*)scene+592,scene->first,(void*)0x06013c00,3072);
 {
  register void *transfer asm("r0");
  asm volatile("movs r3, #155\n\tlsl r3, r3, #2\n\tadd %0, %1, r3"
               : "=l"(transfer) : "l"(scene) : "r3", "cc");
  {
   register void *source asm("r1")=scene->second;
   register void *destination asm("r2")=(void*)0x06009c00;
   asm("" : "+r"(source), "+r"(destination));
   InitializeTransfer(transfer,source,destination,1920);
  }
 }
 InitializePaletteJob((u8*)scene+648,(void*)0x083c3864,
  ({ register u8 **palette_root asm("r2")=(u8**)0x030008b0;
     register u32 palette_offset asm("r3");
     register u8 *palette_source asm("r2");
     asm("" : "+r"(palette_root));
     palette_source=palette_root[5];
     asm("" : "+r"(palette_source));
     palette_offset=512;
     asm("" : "+r"(palette_offset));
     palette_source+palette_offset; }),30,4,60,64);
 copy_cell=&CurrentCopyRoutine;
 palette_destination=(u8*)0x03003b20;
 CallCopy(palette_destination,GetPalette(17),32,*copy_cell);
 {
  register u32 actual_destination asm("r4")=(u32)palette_destination;
  register u32 negative_offset asm("r7")=0xfffffe00U;
  asm("" : "+r"(negative_offset));
  asm volatile("add %0, %0, %1" : "+l"(actual_destination) : "l"(negative_offset) : "cc");
  palette_destination=(u8*)actual_destination;
 }
 CallCopy(palette_destination,GetPalette(16),32,*copy_cell);
 DisplayControl&=0xfbff;
}
