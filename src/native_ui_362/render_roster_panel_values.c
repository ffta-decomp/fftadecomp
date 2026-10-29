typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *volatile gRosterPanelOwner;
extern u8 gRosterPanelMode[];
extern u8 gRosterPhysicalRecordPool[];
extern u16 *ResolveRosterTilemap(u32,u32,u32,u32);
extern void DrawRosterTileRun(u32,u16*,u32,u32);
extern void DrawRosterDecimal(u16*,u32,u32,u32);
__asm__(".global gRosterPanelOwner\n.set gRosterPanelOwner,0x03002818\n"
".global gRosterPanelMode\n.set gRosterPanelMode,0x020020d0\n"
".global gRosterPhysicalRecordPool\n.set gRosterPhysicalRecordPool,0x02000000\n"
".global ResolveRosterTilemap\n.thumb_set ResolveRosterTilemap,0x0808b8e5\n"
".global DrawRosterTileRun\n.thumb_set DrawRosterTileRun,0x08035679\n"
".global DrawRosterDecimal\n.thumb_set DrawRosterDecimal,0x08035a69");
#define HALF_AT(p,o) (*(u16*)((u8*)(p)+(o)))
void RenderRosterPanelValues(u32 clear_only) __asm__("CoreScene34_000725B8");
void RenderRosterPanelValues(u32 clear_only)
{
 if(clear_only==1){
  s32 index=0;
  if(index<gRosterPanelOwner[0x95c]){
   u8 *volatile *owner_cell=&gRosterPanelOwner;
   s32 offset=0;
   do{
    u8 *row=*owner_cell+offset;
    u32 x=(u16)((s16)HALF_AT(row,0x9f6)>>3);
    u32 y=(u16)(((s16)HALF_AT(row,0x9f8)>>3)+5);
    u16 *destination=ResolveRosterTilemap(0,1,x,y);
    DrawRosterTileRun(0,destination,6,0);
    offset+=20;
    ++index;
   }while(index<(*owner_cell)[0x95c]);
  }
  return;
 }
 {
  register u32 palette __asm__("r9")=15;
  __asm__("" : "+r"(palette));
  switch(gRosterPanelMode[21]){
  case 0:{
   register u32 header_working __asm__("r4")=0xd0bf;
   register u32 header __asm__("r8")=header_working;
   s32 header_index;
   __asm__("" : "+r"(header_working), "+r"(header));
   header_index=0;
   if(header_index<gRosterPanelOwner[0x95c]){
    u8 *volatile *owner_cell=&gRosterPanelOwner;
    s32 header_offset=0;
    do{
     u8 *row=*owner_cell+header_offset;
     u32 x=({
      register u32 x_offset __asm__("r4")=0x9f6;
      register const u16 *x_address __asm__("r0");
      __asm__("" : "+r"(x_offset));
      x_address=(const u16*)(row+x_offset);
      __asm__("" : "+r"(x_address));
      (u16)((s16)*x_address>>3);
     });
     u32 y=(u16)(((s16)HALF_AT(row,0x9f8)>>3)+5);
     u16 *destination=ResolveRosterTilemap(0,1,x,y);
     DrawRosterTileRun(0,destination,6,0);
     DrawRosterTileRun(header,destination,2,1);
     header_offset+=20;
     ++header_index;
    }while(header_index<(*owner_cell)[0x95c]);
   }
   {
    s32 value_index=0;
    if(value_index<gRosterPanelOwner[0x95c]){
     u8 *volatile *owner_cell=&gRosterPanelOwner;
     s32 value_offset=0;
     register u32 palette_working __asm__("r4")=palette;
     register u32 packed_palette __asm__("r8");
     __asm__("" : "+r"(palette_working));
     palette_working<<=28;
     __asm__("" : "+r"(palette_working));
     packed_palette=palette_working;
     __asm__("" : "+r"(packed_palette));
     do{
      u8 *owner=*owner_cell;
      u32 mapped_row=({
       register const u8 *mapping __asm__("r0")=owner+0x9ba;
       __asm__("" : "+r"(mapping));
       mapping[value_index];
      });
      u8 *row=owner+value_offset;
      s32 x=({ register s32 x_working __asm__("r0")=(s16)HALF_AT(row,0x9f6)>>3; __asm__("" : "+r"(x_working)); x_working+2; });
      s32 y=({ register s32 y_working __asm__("r0")=(s16)HALF_AT(row,0x9f8)>>3; __asm__("" : "+r"(y_working)); y_working+5; });
      u16 *destination=ResolveRosterTilemap(0,1,x,y);
      u32 value=({
       register const u8 *value_record __asm__("r2")=*owner_cell;
       __asm__("" : "+r"(value_record));
       value_record+=mapped_row*20;
       __asm__("" : "+r"(value_record));
       value_record+=0x9ef;
       __asm__("" : "+r"(value_record));
       ({
        register u32 loaded_value __asm__("r2")=*value_record;
        __asm__("" : "+r"(loaded_value));
        loaded_value;
       });
      });
      {
       register u32 digits_argument __asm__("r1")=2;
       register u32 value_argument __asm__("r2")=value;
       __asm__("" : "+r"(digits_argument), "+r"(value_argument));
       {
        register u32 attribute_working __asm__("r4")=packed_palette;
        __asm__("" : "+r"(attribute_working));
        DrawRosterDecimal(destination,digits_argument,value_argument,attribute_working>>16);
       }
      }
      value_offset+=20;
      ++value_index;
     }while(value_index<({
      register u8 *count_root __asm__("r0")=*owner_cell;
      register u32 count_offset __asm__("r1");
      __asm__("" : "+r"(count_root));
      count_offset=0x95c;
      __asm__("" : "+r"(count_offset));
      count_root+=count_offset;
      __asm__("" : "+r"(count_root));
      *count_root;
     }));
    }
   }
   break;
  }
  case 1:{
   register u32 header_working __asm__("r2")=0xf05e;
   register u32 header __asm__("r8")=header_working;
   s32 header_index;
   __asm__("" : "+r"(header_working), "+r"(header));
   header_index=0;
   if(header_index<({
    register u8 *count_root __asm__("r0")=gRosterPanelOwner;
    register u32 count_offset __asm__("r4");
    __asm__("" : "+r"(count_root));
    count_offset=0x95c;
    __asm__("" : "+r"(count_offset));
    count_root+=count_offset;
    __asm__("" : "+r"(count_root));
    *count_root;
   })){
    u8 *volatile *owner_cell=&gRosterPanelOwner;
    s32 header_offset=0;
    do{
     u8 *row=*owner_cell+header_offset;
     u32 x=(u16)((s16)HALF_AT(row,0x9f6)>>3);
     u32 y=({
      register u32 y_offset __asm__("r4")=0x9f8;
      register const u16 *y_address __asm__("r1");
      __asm__("" : "+r"(y_offset));
      y_address=(const u16*)(row+y_offset);
      __asm__("" : "+r"(y_address));
      (u16)(((s16)*y_address>>3)+5);
     });
     u16 *destination=ResolveRosterTilemap(0,1,x,y);
     DrawRosterTileRun(0,destination,6,0);
     DrawRosterTileRun(header,destination,2,1);
     header_offset+=20;
     ++header_index;
    }while(header_index<(*owner_cell)[0x95c]);
   }
   {
    s32 value_index=0;
    if(value_index<gRosterPanelOwner[0x95c]){
     u8 *volatile *owner_cell=&gRosterPanelOwner;
     register u8 *pool_working __asm__("r4")=gRosterPhysicalRecordPool;
     register u8 *record_pool __asm__("r8")=pool_working;
     s32 value_offset;
     __asm__("" : "+r"(pool_working), "+r"(record_pool));
     value_offset=0;
     do{
      u8 *row=*owner_cell+value_offset;
      s32 x=({ register s32 x_working __asm__("r0")=(s16)HALF_AT(row,0x9f6)>>3; __asm__("" : "+r"(x_working)); x_working+2; });
      s32 y=({ register s32 y_working __asm__("r0")=(s16)HALF_AT(row,0x9f8)>>3; __asm__("" : "+r"(y_working)); y_working+5; });
      u16 *destination=ResolveRosterTilemap(0,1,x,y);
      u8 *current_row=*owner_cell+value_offset;
      u32 record_id=HALF_AT(current_row,0x9f0);
      u32 value=*(u8*)(record_pool+record_id*264+137);
      DrawRosterDecimal(destination,2,value,(u16)(palette<<12));
      value_offset+=20;
      ++value_index;
     }while(value_index<(*owner_cell)[0x95c]);
    }
   }
   break;
  }
  case 2:{
   register u32 header_working __asm__("r2")=0xd052;
   register u32 header __asm__("r8")=header_working;
   s32 header_index;
   __asm__("" : "+r"(header_working), "+r"(header));
   header_index=0;
   if(header_index<({
    register u8 *count_root __asm__("r0")=gRosterPanelOwner;
    register u32 count_offset __asm__("r4");
    __asm__("" : "+r"(count_root));
    count_offset=0x95c;
    __asm__("" : "+r"(count_offset));
    count_root+=count_offset;
    __asm__("" : "+r"(count_root));
    *count_root;
   })){
    u8 *volatile *owner_cell=&gRosterPanelOwner;
    s32 header_offset=0;
    do{
     u8 *row=*owner_cell+header_offset;
     u32 x=(u16)((s16)HALF_AT(row,0x9f6)>>3);
     u32 y=({
      register u32 y_offset __asm__("r4")=0x9f8;
      register const u16 *y_address __asm__("r1");
      __asm__("" : "+r"(y_offset));
      y_address=(const u16*)(row+y_offset);
      __asm__("" : "+r"(y_address));
      (u16)(((s16)*y_address>>3)+5);
     });
     u16 *destination=ResolveRosterTilemap(0,1,x,y);
     DrawRosterTileRun(0,destination,6,0);
     DrawRosterTileRun(header,destination,2,1);
     header_offset+=20;
     ++header_index;
    }while(header_index<(*owner_cell)[0x95c]);
   }
   {
    header_index=0;
    if(header_index<gRosterPanelOwner[0x95c]){
     register u8 *volatile *owner_cell __asm__("r8");
     register u8 *pool_working __asm__("r4")=gRosterPhysicalRecordPool;
     register u8 *record_pool __asm__("r10")=pool_working;
     s32 value_offset;
     __asm__("" : "+r"(pool_working), "+r"(record_pool));
     owner_cell=&gRosterPanelOwner;
     __asm__("" : "+r"(owner_cell));
     value_offset=0;
     {
      register u32 palette_working __asm__("r0")=palette;
      __asm__("" : "+r"(palette_working));
      palette_working<<=28;
      __asm__("" : "+r"(palette_working));
      palette=palette_working;
      __asm__("" : "+r"(palette));
     }
     do{
      u8 *row=({
       register u8 *volatile *cell_working __asm__("r1")=owner_cell;
       register u8 *root_working __asm__("r0");
       __asm__("" : "+r"(cell_working));
       root_working=*cell_working;
       __asm__("" : "+r"(root_working));
       ({
        register u8 *row_working __asm__("r3")=root_working+value_offset;
        __asm__("" : "+r"(row_working));
        row_working;
       });
      });
      u32 record_id=({
       register u32 record_offset __asm__("r2")=0x9f0;
       register const u16 *id_address __asm__("r0");
       __asm__("" : "+r"(record_offset));
       id_address=(const u16*)(row+record_offset);
       __asm__("" : "+r"(id_address));
       *id_address;
      });
      s32 value=HALF_AT(record_pool,record_id*264+154);
      s32 digits=3;
      s32 x,y;
      u16 *destination;
      if(value<=99)digits=2;
      x=({ register s32 x_working __asm__("r0")=(s16)HALF_AT(row,0x9f6)>>3; __asm__("" : "+r"(x_working)); x_working+2; });
      y=({ register s32 y_working __asm__("r0")=(s16)HALF_AT(row,0x9f8)>>3; __asm__("" : "+r"(y_working)); y_working+5; });
      destination=ResolveRosterTilemap(0,1,x,y);
      {
       register u32 digits_argument __asm__("r1")=digits;
       register u32 value_argument __asm__("r2")=value;
       __asm__("" : "+r"(digits_argument), "+r"(value_argument));
       {
        register u32 attribute_working __asm__("r4")=palette;
        __asm__("" : "+r"(attribute_working));
        DrawRosterDecimal(destination,digits_argument,value_argument,attribute_working>>16);
       }
      }
      value_offset+=20;
      ++header_index;
     }while(header_index<({
      register u8 *volatile *cell_working __asm__("r1")=owner_cell;
      register u8 *root_working __asm__("r0");
      __asm__("" : "+r"(cell_working));
      root_working=*cell_working;
      __asm__("" : "+r"(root_working));
      root_working[0x95c];
     }));
    }
   }
   break;
  }
  case 3:{
   register u32 header_working __asm__("r4")=0xe054;
   register u32 header __asm__("r8")=header_working;
   s32 header_index;
   __asm__("" : "+r"(header_working), "+r"(header));
   header_index=0;
   if(header_index<gRosterPanelOwner[0x95c]){
    u8 *volatile *owner_cell=&gRosterPanelOwner;
    s32 header_offset=0;
    do{
     u8 *row=*owner_cell+header_offset;
     u32 x=({
      register u32 x_offset __asm__("r4")=0x9f6;
      register const u16 *x_address __asm__("r0");
      __asm__("" : "+r"(x_offset));
      x_address=(const u16*)(row+x_offset);
      __asm__("" : "+r"(x_address));
      (u16)((s16)*x_address>>3);
     });
     u32 y=(u16)(((s16)HALF_AT(row,0x9f8)>>3)+5);
     u16 *destination=ResolveRosterTilemap(0,1,x,y);
     DrawRosterTileRun(0,destination,6,0);
     DrawRosterTileRun(header,destination,2,1);
     header_offset+=20;
     ++header_index;
    }while(header_index<(*owner_cell)[0x95c]);
   }
   {
    header_index=0;
    if(header_index<gRosterPanelOwner[0x95c]){
     register u8 *volatile *owner_cell __asm__("r8");
     register u8 *pool_working __asm__("r4")=gRosterPhysicalRecordPool;
     register u8 *record_pool __asm__("r10")=pool_working;
     s32 value_offset;
     __asm__("" : "+r"(pool_working), "+r"(record_pool));
     owner_cell=&gRosterPanelOwner;
     __asm__("" : "+r"(owner_cell));
     value_offset=0;
     {
      register u32 palette_working __asm__("r0")=palette;
      __asm__("" : "+r"(palette_working));
      palette_working<<=28;
      __asm__("" : "+r"(palette_working));
      palette=palette_working;
      __asm__("" : "+r"(palette));
     }
     do{
      u8 *row=({
       register u8 *volatile *cell_working __asm__("r1")=owner_cell;
       register u8 *root_working __asm__("r0");
       __asm__("" : "+r"(cell_working));
       root_working=*cell_working;
       __asm__("" : "+r"(root_working));
       ({
        register u8 *row_working __asm__("r3")=root_working+value_offset;
        __asm__("" : "+r"(row_working));
        row_working;
       });
      });
      u32 record_id=({
       register u32 record_offset __asm__("r2")=0x9f0;
       register const u16 *id_address __asm__("r0");
       __asm__("" : "+r"(record_offset));
       id_address=(const u16*)(row+record_offset);
       __asm__("" : "+r"(id_address));
       *id_address;
      });
      s32 value=HALF_AT(record_pool,record_id*264+158);
      s32 digits=3;
      s32 x,y;
      u16 *destination;
      if(value<=99)digits=2;
      x=({ register s32 x_working __asm__("r0")=(s16)HALF_AT(row,0x9f6)>>3; __asm__("" : "+r"(x_working)); x_working+2; });
      y=({ register s32 y_working __asm__("r0")=(s16)HALF_AT(row,0x9f8)>>3; __asm__("" : "+r"(y_working)); y_working+5; });
      destination=ResolveRosterTilemap(0,1,x,y);
      {
       register u32 digits_argument __asm__("r1")=digits;
       register u32 value_argument __asm__("r2")=value;
       __asm__("" : "+r"(digits_argument), "+r"(value_argument));
       {
        register u32 attribute_working __asm__("r4")=palette;
        __asm__("" : "+r"(attribute_working));
        DrawRosterDecimal(destination,digits_argument,value_argument,attribute_working>>16);
       }
      }
      value_offset+=20;
      ++header_index;
     }while(header_index<({
      register u8 *volatile *cell_working __asm__("r1")=owner_cell;
      register u8 *root_working __asm__("r0");
      __asm__("" : "+r"(cell_working));
      root_working=*cell_working;
      __asm__("" : "+r"(root_working));
      root_working[0x95c];
     }));
    }
   }
   break;
  }
  case 4:{
   register u32 header_working __asm__("r4")=0xd056;
   register u32 header __asm__("r8")=header_working;
   s32 header_index;
   __asm__("" : "+r"(header_working), "+r"(header));
   header_index=0;
   if(header_index<gRosterPanelOwner[0x95c]){
    u8 *volatile *owner_cell=&gRosterPanelOwner;
    s32 header_offset=0;
    do{
     u8 *row=*owner_cell+header_offset;
     u32 x=({
      register u32 x_offset __asm__("r4")=0x9f6;
      register const u16 *x_address __asm__("r0");
      __asm__("" : "+r"(x_offset));
      x_address=(const u16*)(row+x_offset);
      __asm__("" : "+r"(x_address));
      (u16)((s16)*x_address>>3);
     });
     u32 y=(u16)(((s16)HALF_AT(row,0x9f8)>>3)+5);
     u16 *destination=ResolveRosterTilemap(0,1,x,y);
     DrawRosterTileRun(0,destination,6,0);
     DrawRosterTileRun(header,destination,2,1);
     header_offset+=20;
     ++header_index;
    }while(header_index<(*owner_cell)[0x95c]);
   }
   {
    s32 value_index=0;
    if(value_index<gRosterPanelOwner[0x95c]){
     u8 *volatile *owner_cell=&gRosterPanelOwner;
     register u8 *pool_working __asm__("r4")=gRosterPhysicalRecordPool;
     register u8 *record_pool __asm__("r8")=pool_working;
     s32 value_offset;
     __asm__("" : "+r"(pool_working), "+r"(record_pool));
     value_offset=0;
     do{
      u8 *row=*owner_cell+value_offset;
      s32 x=({ register s32 x_working __asm__("r0")=(s16)HALF_AT(row,0x9f6)>>3; __asm__("" : "+r"(x_working)); x_working+2; });
      s32 y=({ register s32 y_working __asm__("r0")=(s16)HALF_AT(row,0x9f8)>>3; __asm__("" : "+r"(y_working)); y_working+5; });
      u16 *destination=ResolveRosterTilemap(0,1,x,y);
      u8 *current_row=*owner_cell+value_offset;
      u32 record_id=HALF_AT(current_row,0x9f0);
      u32 value=*(u16*)(record_pool+record_id*264+342);
      DrawRosterDecimal(destination,2,value,(u16)(palette<<12));
      value_offset+=20;
      ++value_index;
     }while(value_index<(*owner_cell)[0x95c]);
    }
   }
   break;
  }
  }
 }
}
