typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
struct MenuEntry {u16 observed0;u16 availability;};
struct MenuEntryView {u8 observed_prefix[0x424];struct MenuEntry *entries[0];};
extern unsigned QueryMenuRow(void *,int);
extern void SetMenuRowMarker(void *,int,unsigned);
__asm__(".global QueryMenuRow\n.thumb_set QueryMenuRow,0x08017b69\n.global SetMenuRowMarker\n.thumb_set SetMenuRowMarker,0x08017af5");
void ApplyMenuRowMarker(u8 *context,u8 row) {
 if(context[8]==4) {
  unsigned index=(u16)QueryMenuRow(context+72,(s8)row);
  if((*(struct MenuEntryView **)context)->entries[index]->availability) return;
 }
 SetMenuRowMarker(context+72,(s8)row,255);
}
