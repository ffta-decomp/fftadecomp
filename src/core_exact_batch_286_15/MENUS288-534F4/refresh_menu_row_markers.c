typedef unsigned char u8;
typedef signed char s8;
struct MarkerPanel {u8 observed0[21];u8 height;u8 observed22[10];};
struct MarkerCursor {u8 observed0[17];s8 selected;};
struct MarkerContext {u8 observed_prefix[0xd1c];struct MarkerPanel panel;struct MarkerCursor cursor;};
extern struct MarkerContext *gMarkerContext;
extern void DrawMenuRowMarker(void *,int,unsigned,unsigned,unsigned);
extern void RefreshMarkerPanel(void *);
__asm__(".global gMarkerContext\n.set gMarkerContext,0x0200f428\n.global DrawMenuRowMarker\n.thumb_set DrawMenuRowMarker,0x08054205\n.global RefreshMarkerPanel\n.thumb_set RefreshMarkerPanel,0x0802b109");
void RefreshMenuRowMarkers(void) {
 struct MarkerPanel *panel=&gMarkerContext->panel;
 struct MarkerCursor *cursor=&gMarkerContext->cursor;
 int selected;
 u8 i=0;
 __asm__("" : "+r"(cursor), "+r"(i));
 selected=cursor->selected;
 do {
  if(i==selected) DrawMenuRowMarker(panel,(s8)(i*3),11,2,(u8)(panel->height-2));
  else DrawMenuRowMarker(panel,(s8)(i*3),255,2,(u8)(panel->height-2));
  ++i;
 } while(i<=3);
 RefreshMarkerPanel(panel);
}
