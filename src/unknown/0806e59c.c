typedef unsigned char u8;
typedef signed char s8;
struct MarkerPanel {u8 observed0[21];u8 height;u8 observed22[10];};
struct MarkerCursor {u8 observed0[17];s8 selected;};
struct MarkerContext {u8 observed_prefix[0x14c0];struct MarkerPanel panel;struct MarkerCursor cursor;};
extern struct MarkerContext *gMarkerContext;
extern void DrawMenuRowMarker(void *,int,unsigned,unsigned,unsigned);
extern unsigned QueryMenuRowCount(void *);
__asm__(".global gMarkerContext\n.set gMarkerContext,0x0200f428\n.global DrawMenuRowMarker\n.thumb_set DrawMenuRowMarker,0x0802acd5\n.global QueryMenuRowCount\n.thumb_set QueryMenuRowCount,0x08017b51");
void RefreshVariableMenuRowMarkers(void) {
 register struct MarkerPanel *panel __asm__("r4")=&gMarkerContext->panel;
 struct MarkerCursor *cursor=&gMarkerContext->cursor;
 int selected;
 u8 i=0;
 unsigned count;
 __asm__("" : "+r"(cursor), "+r"(i), "+r"(panel));
 selected=cursor->selected;
 for(;;) {
  count=(unsigned short)QueryMenuRowCount(panel);
  __asm__("" : "+r"(count));
  if(i>=count) break;
  if(i==selected) DrawMenuRowMarker(panel,i,11,2,(u8)(panel->height-2));
  else DrawMenuRowMarker(panel,(s8)i,255,2,(u8)(panel->height-2));
  ++i;
 }
}
