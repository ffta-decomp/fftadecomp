typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *volatile gAbilityMenuOwner;
extern u8 gAbilityMenuBufferRoot[];
extern u8 gAbilityMenuDisplay[];
extern u8 gAbilityMenuTitleWork[];
extern u16 *ResolveAbilityMenuTilemap(u32,u32,u32,u32);
extern void FillAbilityMenuRow(u32,u16*,u32,u32);
extern void ConfigureAbilityMenuGroup(u32,u32,u32,u32,void*,void*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void CpuSetAbilityMenu(const void*,void*,u32);
extern void BuildAbilityMenuContents(u32,void*,u32,u32,u32,u32);
extern void ConfigureAbilityMenuSurface(void*,u32,u32,u32,u32,u32,u32);
extern void ConfigureAbilityMenuFrame(void*,u32,u32,u32,u32,u32,u32);
extern u32 ReadAbilityMenuTitle(void*,u32,u32);
extern void DrawAbilityMenuTitle(u32,u16*,u32,u32);
__asm__(".global gAbilityMenuOwner\n.set gAbilityMenuOwner,0x03002818\n"
".global gAbilityMenuBufferRoot\n.set gAbilityMenuBufferRoot,0x03002740\n"
".global gAbilityMenuDisplay\n.set gAbilityMenuDisplay,0x030009e0\n"
".global gAbilityMenuTitleWork\n.set gAbilityMenuTitleWork,0x02003cb0\n"
".global ResolveAbilityMenuTilemap\n.thumb_set ResolveAbilityMenuTilemap,0x0808b8e5\n"
".global FillAbilityMenuRow\n.thumb_set FillAbilityMenuRow,0x0808b859\n"
".global ConfigureAbilityMenuGroup\n.thumb_set ConfigureAbilityMenuGroup,0x0808a269\n"
".global CpuSetAbilityMenu\n.thumb_set CpuSetAbilityMenu,0x0814186d\n"
".global BuildAbilityMenuContents\n.thumb_set BuildAbilityMenuContents,0x0808136d\n"
".global ConfigureAbilityMenuSurface\n.thumb_set ConfigureAbilityMenuSurface,0x08016345\n"
".global ConfigureAbilityMenuFrame\n.thumb_set ConfigureAbilityMenuFrame,0x08016561\n"
".global ReadAbilityMenuTitle\n.thumb_set ReadAbilityMenuTitle,0x08018525\n"
".global DrawAbilityMenuTitle\n.thumb_set DrawAbilityMenuTitle,0x08035679");
void InitializeAbilityAssignmentList(u32 mode) __asm__("CoreScene34_0007DC24");
void InitializeAbilityAssignmentList(u32 mode)
{
 register u8 *title_work __asm__("r10")=gAbilityMenuTitleWork;
 __asm__("" : "+r"(title_work));
 if(mode==2){
  s32 row=2;
  s32 remaining=4;
  do{
   register u16 *destination __asm__("r1")=ResolveAbilityMenuTilemap(5,1,0,row);
   __asm__("" : "+r"(destination));
   FillAbilityMenuRow(5,destination,0,14);
   row+=2;
   --remaining;
  }while(remaining>=0);
 }else{
  register u8 *volatile *owner_working __asm__("r1")=&gAbilityMenuOwner;
  register u8 *volatile *owner_cell __asm__("r9");
  u8 *owner;
  register u32 resource_a __asm__("r2");
  register u32 resource_b __asm__("r3");
  u32 two,six,width;
  register u8 *display __asm__("r6");
  u32 one,twelve;
  register u32 clear_offset __asm__("r2");
  register u32 field_offset __asm__("r3");
  u16 zero_half;
  owner_cell=owner_working;
  __asm__("" : "+r"(owner_working), "+r"(owner_cell));
  owner=*owner_working;
  resource_a=*(u32*)(owner+24);
  resource_b=*(u32*)(owner+20);
  __asm__("" : "+r"(resource_a), "+r"(resource_b));
  {
   register const u8 *buffer_root __asm__("r0")=gAbilityMenuBufferRoot;
   register u8 *buffer __asm__("r0");
   __asm__("" : "+r"(buffer_root));
   buffer=*(u8**)(buffer_root+20);
   __asm__("" : "+r"(buffer));
   ConfigureAbilityMenuGroup(5,12,resource_a,resource_b,buffer,buffer+364,
       0,0,(two=2),(six=6),(width=14),13,2,6,14,13,14,13);
  }
  display=gAbilityMenuDisplay;
  __asm__("" : "+r"(display));
  {
   register u32 two_offset __asm__("r2")=0x1b0;
   register u8 *two_destination __asm__("r0");
   __asm__("" : "+r"(two_offset));
   two_destination=display+two_offset;
   __asm__("" : "+r"(two_destination));
   *two_destination=two;
  }
  {
   register u32 six_offset __asm__("r3")=0x1b1;
   register u8 *six_destination __asm__("r0");
   __asm__("" : "+r"(six_offset));
   six_destination=display+six_offset;
   __asm__("" : "+r"(six_destination));
   *six_destination=six;
  }
  if(mode==0){
   zero_half=mode;
   CpuSetAbilityMenu(&zero_half,(void*)0x0600c520,0x01000900);
  }
  {
   register u16 *tag_destination __asm__("r2")=(u16*)(display+0x18a);
   register u32 zero __asm__("r0");
   register u32 tag __asm__("r1");
   __asm__("" : "+r"(tag_destination));
   zero=0;
   __asm__("" : "+r"(zero));
   tag=0x229;
   __asm__("" : "+r"(tag));
   *tag_destination=tag;
   clear_offset=0x17d;
   __asm__("" : "+r"(clear_offset));
   display[clear_offset]=zero;
  }
  field_offset=0x1c4;
  __asm__("" : "+r"(field_offset));
  {
   register u8 *one_destination __asm__("r0")=display+field_offset;
   __asm__("" : "+r"(one_destination));
   one=1;
   *one_destination=one;
  }
  display[0x1c5]=one;
  clear_offset+=73;
  __asm__("" : "+r"(clear_offset));
  {
   register u8 *twelve_destination __asm__("r0")=display+clear_offset;
   __asm__("" : "+r"(twelve_destination));
   twelve=12;
   *twelve_destination=twelve;
  }
  field_offset+=3;
  __asm__("" : "+r"(field_offset));
  {
   register u8 *last_twelve_destination __asm__("r0")=display+field_offset;
   __asm__("" : "+r"(last_twelve_destination));
   *last_twelve_destination=twelve;
  }
  if(mode==0){
   register u8 *volatile *content_cell __asm__("r1")=owner_cell;
   register u8 *content_owner __asm__("r0");
   register u32 content_offset __asm__("r2");
   __asm__("" : "+r"(content_cell));
   content_owner=*content_cell;
   content_offset=0x2d50;
   __asm__("" : "+r"(content_owner), "+r"(content_offset));
   BuildAbilityMenuContents(0,*(void**)(content_owner+content_offset),5,0,mode,mode);
  }
  {
   register u32 surface_offset __asm__("r3")=0x198;
   register u32 x_offset __asm__("r2");
   register void *surface __asm__("r0");
   u32 x,y;
   __asm__("" : "+r"(surface_offset));
   surface=*(void**)(display+surface_offset);
   __asm__("" : "+r"(surface));
   x_offset=0x1a4;
   __asm__("" : "+r"(x_offset));
   {
    register const u8 *x_address __asm__("r1")=display+x_offset;
    __asm__("" : "+r"(x_address));
    x=*x_address;
   }
   surface_offset+=13;
   __asm__("" : "+r"(surface_offset));
   {
    register const u8 *y_address __asm__("r2")=display+surface_offset;
    __asm__("" : "+r"(y_address));
    y=*y_address;
   }
   ConfigureAbilityMenuSurface(surface,x,y,192,x,5,twelve);
  }
  {
   register u32 frame_offset __asm__("r1")=0x194;
   register void **frame_address __asm__("r0");
   register void *frame __asm__("r0");
   register u32 width_argument __asm__("r2");
   __asm__("" : "+r"(frame_offset));
   frame_address=(void**)(display+frame_offset);
   __asm__("" : "+r"(frame_address));
   frame=*frame_address;
   __asm__("" : "+r"(frame), "+r"(width));
   width_argument=width;
   __asm__("" : : "r"(width_argument));
   ConfigureAbilityMenuFrame(frame,14,13,192,width_argument,one,twelve);
  }
  {
   u32 title_style=0xc044;
   u16 *title_destination=ResolveAbilityMenuTilemap(5,1,1,1);
   u32 title=ReadAbilityMenuTitle(title_work,68,4);
   DrawAbilityMenuTitle(title_style,title_destination,title,1);
  }
 }
}
