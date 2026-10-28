typedef unsigned char u8;
typedef unsigned short u16;
struct PanelDescriptor {u8 a,b,c,capacity;u16 count,value6;u8 value8;u8 observed9[7];};
typedef void (*CopyFunction)(void *,const void *,unsigned);
extern CopyFunction gDescriptorCopy;
extern struct PanelDescriptor gPanelTemplates[];
extern u8 gPanelDimensions[];
extern u8 *gPanelRoot;
extern void InvokeDescriptorCopy(void *,const void *,unsigned,CopyFunction);
extern unsigned QueryPanelStorage(void *);
extern void *AllocatePanelStorage(unsigned);
extern void CreateDescriptorPanel(void *,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void PopulateDescriptorPanel(void *,void *,void *);
extern void SetDescriptorPanelMode(void *,unsigned);
extern unsigned RegisterDescriptorCallback(void (*)(void),void *);
extern void DescriptorPanelCallback(void);
__asm__(".global gDescriptorCopy\n.set gDescriptorCopy,0x0836d4bc\n.global gPanelTemplates\n.set gPanelTemplates,0x08393890\n.global gPanelDimensions\n.set gPanelDimensions,0x08393910\n.global gPanelRoot\n.set gPanelRoot,0x0200f44c\n.global InvokeDescriptorCopy\n.thumb_set InvokeDescriptorCopy,0x08142251\n.global QueryPanelStorage\n.thumb_set QueryPanelStorage,0x08013b51\n.global AllocatePanelStorage\n.thumb_set AllocatePanelStorage,0x08005b29\n.global CreateDescriptorPanel\n.thumb_set CreateDescriptorPanel,0x08017491\n.global PopulateDescriptorPanel\n.thumb_set PopulateDescriptorPanel,0x08013b7d\n.global SetDescriptorPanelMode\n.thumb_set SetDescriptorPanelMode,0x08016c91\n.global RegisterDescriptorCallback\n.thumb_set RegisterDescriptorCallback,0x080098f5\n.global DescriptorPanelCallback\n.thumb_set DescriptorPanelCallback,0x080603f5");
void InitializeMenuPanelDescriptor(u8 *context) {
 CopyFunction *copy_cell=&gDescriptorCopy;
 CopyFunction copy_function;
 const struct PanelDescriptor *template;
 register struct PanelDescriptor *copy_destination __asm__("r4");
 register struct PanelDescriptor *descriptor __asm__("r5");
 __asm__("" : "+r"(copy_cell));
 copy_destination=(struct PanelDescriptor *)(context+132);
 __asm__("" : "+r"(copy_destination));
 template=&gPanelTemplates[context[0]];
 copy_function=*copy_cell;
 __asm__("" : "+r"(copy_function) : "r"(template));
 InvokeDescriptorCopy(copy_destination,template,16,copy_function);
 descriptor=copy_destination;
 __asm__("" : "+r"(descriptor));
 switch(context[0]) {
 case 3:case 7: {
  unsigned count=gPanelRoot[27];
  unsigned capacity_count=count;
  __asm__("" : "+r"(capacity_count));
  descriptor->count=count;
  if(count<descriptor->capacity) descriptor->capacity=capacity_count;
  if(descriptor->count<=6) descriptor->b=gPanelDimensions[descriptor->count];
  break;
 }
 case 2: {
  unsigned count=gPanelRoot[27];
  unsigned capacity_count=count;
  __asm__("" : "+r"(capacity_count));
  descriptor->count=count;
  if(count<descriptor->capacity) descriptor->capacity=capacity_count;
  if(descriptor->count<=8) descriptor->b=gPanelDimensions[descriptor->count-1];
  break;
 }
 case 4: {
  unsigned count=gPanelRoot[27];
  unsigned capacity_count=count;
  __asm__("" : "+r"(capacity_count));
  descriptor->count=count;
  if(count<descriptor->capacity) descriptor->capacity=capacity_count;
  break;
 }
 case 6: {
  int count=gPanelRoot[27]-2;
  int capacity_count=count;
  __asm__("" : "+r"(capacity_count));
  descriptor->count=count;
  if((u16)count<descriptor->capacity) descriptor->capacity=capacity_count;
  if(descriptor->count<=6) descriptor->b=gPanelDimensions[descriptor->count+1]*2+4;
  break;
 }
 case 5:break;
 }
 *(void **)(context+148)=AllocatePanelStorage((u16)QueryPanelStorage(descriptor));
 CreateDescriptorPanel(context+16,descriptor->a,descriptor->b,descriptor->c,descriptor->capacity,descriptor->value6,5,1,12);
 PopulateDescriptorPanel(descriptor,context+16,gPanelRoot+984);
 SetDescriptorPanelMode(context+16,descriptor->value8);
 context[7]=RegisterDescriptorCallback(DescriptorPanelCallback,context);
}
