typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSceneContext;
extern u32 gControlRoot[];
extern const u8 gMarkerResourceA[],gMarkerResourceB[];
extern void ConfigureMarker(u32,u32,u32,u32,u32,u32,u32,const void *,const void *,u32);
void PlaceSelectedMarker(void) {
 u8 *root=gSceneContext;
 u8 *view=*(u8 **)(root+4);
 u32 index=(u8)(view[26]-1);
 u8 *nodes=*(u8 **)(root+0x67c);
 u8 *node=(u8 *)(20*index+(u32)nodes);
 int x=node[0]*8;
 int draw_x=x+8;
 int draw_y=node[1]*8-*(u16 *)(view+12)+7;
 if(draw_x<=11) draw_x=12;
 else if(x+32>250) draw_x=226;
 if(draw_y<=9) draw_y=10;
 else if(draw_y>136) draw_y=136;
 ConfigureMarker(gControlRoot[1],3,0,(u8)draw_x,(u8)draw_y,0,1,gMarkerResourceA,gMarkerResourceB,294);
}
asm(".global gSceneContext\n.set gSceneContext,0x03002810\n.global gControlRoot\n.set gControlRoot,0x03000e30\n.global gMarkerResourceA\n.set gMarkerResourceA,0x08950d98\n.global gMarkerResourceB\n.set gMarkerResourceB,0x08951550\n.global ConfigureMarker\n.thumb_set ConfigureMarker,0x0804c4d5");
