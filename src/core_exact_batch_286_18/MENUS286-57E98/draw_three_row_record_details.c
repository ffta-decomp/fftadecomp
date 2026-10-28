typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gRecordData[];
extern u32 ResolveMenuRow(void *,u32);
extern u32 GetRecordPalette(u32);
extern void ConfigureTileArea(void *,u32,u32,u32,u32,u32,u32);
extern void DrawTileCodes(void *,u32,u32,u32);
extern void DrawNumberTiles(void *,u32,u32);
static inline void *PanelTileAddress(u8 *panel,u32 offset)
{
 register u32 byte_offset asm("r1")=offset;
 asm("" : "+r" (byte_offset));
 return *(u8 **)(panel+12)+byte_offset;
}
void DrawThreeRowRecordDetails(u8 *panel,u32 ordinal,u32 identifier,u32 mode)
{
 u8 row=ordinal;
 u8 record_id=identifier;
 u8 detail_mode=mode;
 u8 resolved=ResolveMenuRow(panel,row);
 u8 stride=panel[21];
 u32 row_product;
 u32 tile_product;
 u16 row_base;
 u16 tile_base;
 register u8 *record_base asm("r1");
 register u8 *record_address asm("r0");
 u8 *record;
 u8 palette;
 u16 position;
 u16 tile;
 u16 column;
 u16 *map;
 row_product=5*row;
 asm("" : "+r" (row_product));
 row_base=row_product*stride;
 tile_product=5*(resolved&3);
 asm("" : "+r" (tile_product));
 tile_base=*(u16 *)(panel+28)+tile_product*stride;
 record_base=gRecordData;
 asm("" : "+r" (record_base));
 record_address=(u8 *)(264*record_id+(u32)record_base);
 asm("" : "+r" (record_address));
 record=record_address;
 palette=GetRecordPalette(record[135]);
 switch(detail_mode){
 case 0:
  position=row_base;
  ConfigureTileArea(panel,position,tile_base,panel[21],panel[21],panel[31],1);
  position+=2*panel[21];
  tile_base+=2*panel[21];
  ConfigureTileArea(panel,position,tile_base,panel[21],4,palette,detail_mode);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+2*panel[21])+8),147,14,6);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+3*panel[21])+8),153,14,6);
  DrawNumberTiles(PanelTileAddress(panel,2*(row_base+3*panel[21])+20),2,record[368]);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+3*panel[21])+24),143,14,4);
  position=row_base+4*panel[21];
  column=0;
  if(column<panel[21]){
   map=*(u16 **)(panel+12);
   do{
    map[position]=0;
    column++;
    position++;
   }while(column<panel[21]);
  }
  break;
 case 1:
  position=row_base;
  ConfigureTileArea(panel,position,tile_base,panel[21],panel[21],panel[31],detail_mode);
  position+=2*panel[21];
  tile_base+=2*panel[21];
  ConfigureTileArea(panel,position,tile_base,panel[21],4,palette,0);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+2*panel[21])+10),288,15,2);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+3*panel[21])+10),290,15,2);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+2*panel[21])+18),288,14,2);
  DrawTileCodes(PanelTileAddress(panel,2*(row_base+3*panel[21])+18),290,14,2);
  DrawNumberTiles(PanelTileAddress(panel,2*(row_base+3*panel[21])+14),1,record[387]);
  DrawNumberTiles(PanelTileAddress(panel,2*(row_base+3*panel[21])+22),1,record[386]);
  position=row_base+4*panel[21];
  column=0;
  if(column<panel[21]){
   map=*(u16 **)(panel+12);
   do{
    map[position]=0;
    column++;
    position++;
   }while(column<panel[21]);
  }
  break;
 }
}
asm(".global gRecordData\n.set gRecordData,0x02000000\n.global ResolveMenuRow\n.thumb_set ResolveMenuRow,0x0805871d\n.global GetRecordPalette\n.thumb_set GetRecordPalette,0x080cba15\n.global ConfigureTileArea\n.thumb_set ConfigureTileArea,0x0802ab65\n.global DrawTileCodes\n.thumb_set DrawTileCodes,0x0802aca1\n.global DrawNumberTiles\n.thumb_set DrawNumberTiles,0x08029731");
