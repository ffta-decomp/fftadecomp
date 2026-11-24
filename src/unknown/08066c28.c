typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
struct EntryView {u8 observed_prefix[0x424];void *entries[0];};
struct MenuMessage {u16 code;u8 uninitialized_payload[26];};
extern u8 *GetPanelData(void *);
extern unsigned QueryMenuRow(void *,int);
extern void UpdateModeFourChild(void *);
extern void SendMenuMessage(void *,struct MenuMessage *);
__asm__(".global GetPanelData\n.thumb_set GetPanelData,0x08005bfd\n.global QueryMenuRow\n.thumb_set QueryMenuRow,0x08017b69\n.global UpdateModeFourChild\n.thumb_set UpdateModeFourChild,0x080670b5\n.global SendMenuMessage\n.thumb_set SendMenuMessage,0x08005c05");
void UpdateMenuChildSelection(u8 *context) {
 struct MenuMessage message;
 if(context[8]==4) {
  u8 *child=GetPanelData(*(void **)(context+16));
  if(child[9]&1) UpdateModeFourChild(child);
 } else {
  struct EntryView *owner=*(struct EntryView **)context;
  unsigned index=(u16)QueryMenuRow(context+80,(s8)context[129]);
  void *entry=owner->entries[index];
  u8 *child=GetPanelData(*(void **)(context+16));
  *(void **)(child+0x108c)=entry;
  message.code=258;
  SendMenuMessage(*(void **)(context+16),&message);
 }
}
