typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
extern u8 *Scene __asm__("0x03002818");extern u8 MessageState[] __asm__("0x020020d0");extern u8 Next __asm__("0x0200f28e"),TaskIndex __asm__("0x0200f28f");extern u8 TaskRecords[] __asm__("0x030009e0");extern volatile u16 Display[] __asm__("0x03000940");extern volatile u16 DisplayAux __asm__("0x030027f0");extern u8 DisplayState __asm__("0x030027a4");extern u16 Input[] __asm__("0x03000000");extern u8 Graphics[] __asm__("0x03000990"),Render[] __asm__("0x030008b0"),PromptGraphics[] __asm__("0x03000e80");
void Sound(u32) __asm__("RetailCall_08141540");void SoundStop(u32) __asm__("RetailCall_08141520");u16 DialogTick(void) __asm__("RetailCall_08011860");void DialogClose(void) __asm__("RetailCall_08013364");s8 Confirmation(void) __asm__("RetailCall_08013380");void DialogInit(void*,u8,u16,void*,void*,u32,u16,u8,u8,u16) __asm__("RetailCall_0801174c");void DialogText(void*,u8,u32) __asm__("RetailCall_08013210");u8 UnitPredicate(void*,u32) __asm__("RetailCall_080c8194");s16 Random(void) __asm__("RetailCall_08002804");int SignedModulo(int,int) __asm__("RetailCall_08142950");void SetFlag(u32,u32) __asm__("RetailCall_080c9574");void SetUnitClass(void*,u8) __asm__("RetailCall_080c8c24");void CpuSet(const void*,void*,u32) __asm__("RetailCall_0814186c");void UpdateRoster(u8,void*) __asm__("RetailCall_08072130");void Cleanup(u8) __asm__("RetailCall_08087b30");void RestoreMenu(u8) __asm__("RetailCall_08076420");void UpdateDialog(void) __asm__("RetailCall_08011c60");
/* One real inlined definition preserves the argument preparation boundary
 * while allowing the equivalent message tails to share their typed call. */
static __inline__ void SubmitUnitDialogRecord(void *record)
{
 register void *record_arg __asm__("r0")=record;
 register u32 side_zero __asm__("r1")=0;
 __asm__("" : "+r"(record_arg) : "r"(side_zero));
 DialogText(record_arg,0,17152);
}
#define BYTE(o) (Scene[o])
#define HALF(o) (*(u16*)(Scene+(o)))
#define SIGNED(o) (*(s16*)(Scene+(o)))
#define UNIT (*(u8**)(Scene+0x1d0c))
#define DIALOG (Scene+0x1d10)
/* The native final pointer reuses the indexed stride after the biased owner join. */
#define UNIT_RECORD(i) ({ \
 u32 record_stride=(u32)(i)*264; \
 u32 record_bias=(u32)-8272; \
 __asm__("" : "+r"(record_bias) : "r"(record_stride), "r"(parameters)); \
 record_stride+=record_bias+(u32)parameters; \
 (u8*)record_stride; \
})
#define UNIT_MESSAGE(id,zero) {u8 *record=UNIT_RECORD(BYTE(0x987));DialogInit(DIALOG,15,id,Graphics,Render,-1,zero,22,6,343);SubmitUnitDialogRecord(record);}
/* Physical parameter words: opaque first word, selected-unit pointer at byte4. */
struct UnitMessageParameters {u32 context;u8 *unit;};
/* Remove the selected unit only after the ordered confirmation dialogue.
 * Dialogue state fields retain neutral physical names where their roles are uncertain. */
void CoreScene34_000868D4(u32 unused,u8 *state)
{
 register u32 terminal_resume_value __asm__("r0");
 register u32 unit_resume_value __asm__("r0");
 register u32 task_resume_value __asm__("r0");
 switch(*state){
 case 0:
  Sound(101);BYTE(0xbf5)=5;BYTE(0x1d04)=0;*(s8 *)(Scene+0x95e)&=~1;Next=3;terminal_resume_value=12;goto publish_terminal_state;
 case 12:{
  register void *dialog_buffer __asm__("r0")=(void*)0x02003cb0;
  /* Retail defines this real first argument before the context publications. */
  __asm__("" : "+r"(dialog_buffer));
  {u8 previous_overlay=BYTE(0x43a);BYTE(0x43b)=previous_overlay;}
  BYTE(0x43a)=3;DialogInit(dialog_buffer,1,19,Graphics,PromptGraphics,2,7,24,4,928);task_resume_value=13;goto publish_task_resume;
 }
 case 13:
  if(DialogTick()){
   if(!Confirmation()){DialogClose();
    {register u8 *next_address __asm__("r0")=&Next;
     __asm__("" : "+r"(next_address));
     *next_address=16;
    }
    {register u32 accepted_wait_value __asm__("r0")=19;
     register u8 *accepted_wait_target __asm__("r2")=state;
     __asm__("" : "+r"(accepted_wait_target) : "r"(accepted_wait_value));
     *accepted_wait_target=accepted_wait_value;
    }
   }
   else{DialogClose();
    {u8 *cancel_owner=Scene;
     register u32 saved_overlay_offset __asm__("r3")=0x43b;
     register u32 active_overlay_offset __asm__("r4");
     u8 saved_overlay;
     register u8 *saved_overlay_address __asm__("r1");
     __asm__("" : "+r"(saved_overlay_offset) : "r"(cancel_owner));
     saved_overlay_address=cancel_owner+saved_overlay_offset;
     __asm__("" : "+r"(saved_overlay_address));
     saved_overlay=*saved_overlay_address;
     active_overlay_offset=0x43a;
     __asm__("" : "+r"(active_overlay_offset) : "r"(cancel_owner), "r"(saved_overlay));
     cancel_owner[active_overlay_offset]=saved_overlay;
    }
    Next=253;terminal_resume_value=19;goto publish_terminal_state;
   }
  }break;
 case 16:{
  u8 first,second;
  register u8 *parameter_input __asm__("r0")=MessageState;
  __asm__("" : "+r"(parameter_input));
  {
  register u8 *parameters __asm__("r8")=parameter_input;
  __asm__("" : "+r"(parameters));
  {
  register u8 *initial_scene __asm__("r1")=Scene;
  register u8 *selected_unit __asm__("r0");
  __asm__("" : "+r"(initial_scene));
  selected_unit=*(u8**)(initial_scene+0x1d0c);
  /* The native unit load consumes R0 before the saved owner is used to publish it. */
  __asm__("" : "+r"(selected_unit) : "r"(parameters));
  ((struct UnitMessageParameters*)parameters)->unit=selected_unit;
  /* This same native owner becomes the pause-byte address before zero is defined. */
  initial_scene+=37;
  __asm__("" : "+r"(initial_scene));
  {
  /* This real initialized zero feeds the timer and the first dialogue y. */
  register u32 initial_zero=0;
  *initial_scene=initial_zero;
  {register u8 *flag_owner __asm__("r1")=Scene;
   register u32 flag_offset __asm__("r3")=0x95e;
   __asm__("" : "+r"(flag_offset) : "r"(flag_owner));
   flag_owner+=flag_offset;
   __asm__("" : "+r"(flag_owner));
   *flag_owner|=1;
  }
  first=UnitPredicate(UNIT,94);
  if(first){
   __asm__("" : : "r"(initial_zero));
   {u8 *message_owner=Scene;
    register u32 index_offset __asm__("r4")=0x987;
    register u32 dialog_offset __asm__("r5");
    u8 *record;
    register u8 *message_index_address __asm__("r1");
    __asm__("" : "+r"(index_offset) : "r"(message_owner));
    message_index_address=message_owner+index_offset;
    __asm__("" : "+r"(message_index_address));
    record=UNIT_RECORD(*message_index_address);
    dialog_offset=0x1d10;
    __asm__("" : "+r"(dialog_offset) : "r"(message_owner), "r"(record));
    DialogInit(message_owner+dialog_offset,15,27,Graphics,Render,-1,initial_zero,22,6,343);
    SubmitUnitDialogRecord(record);
   }
  }
  else{
   second=UnitPredicate(UNIT,10);
   if(second){UNIT_MESSAGE(15,first);}
   else{
    first=UnitPredicate(UNIT,9);
    if(first){UNIT_MESSAGE(18,second);}
    else{
     second=UnitPredicate(UNIT,4);
     if(second){UNIT_MESSAGE(21,first);}
     else{
      first=UnitPredicate(UNIT,12);
      if(first){UNIT_MESSAGE(24,second);}
      else if(UNIT[4]==2){u8 message=(u8)SignedModulo(Random(),3);UNIT_MESSAGE(message,first);}
      else{
       s16 random=Random();u8 *owner=Scene;u8 *unit=*(u8**)(owner+0x1d0c);int offset=(unit[6]-1)*3;u8 message=(u8)(SignedModulo(random,3)+offset);u8 *record=UNIT_RECORD(owner[0x987]);
       DialogInit(owner+0x1d10,15,message,Graphics,Render,-1,first,22,6,343);SubmitUnitDialogRecord(record);
      }
     }
    }
   }
  }
  }
  }
  }
  unit_resume_value=17;goto publish_unit_resume;
 }
 case 17:
  if(BYTE(37)==5){Display[3]=0x2b09;DisplayAux=0;DisplayState=253;}
  if(BYTE(37)<=49){
   register u32 scroll_offset __asm__("r5")=0x458;
   register u16 *scroll_position __asm__("r2");
   register int signed_scroll __asm__("r1");
   register u32 signed_read_scratch __asm__("r0");
   u16 before_scroll;
   __asm__("" : "+r"(scroll_offset) : "r"(Scene));
   scroll_position=(u16*)(Scene+scroll_offset);
   __asm__("" : "+r"(scroll_position));
   before_scroll=*scroll_position;
   /* The pinned Thumb backend otherwise chooses R4 for this implicit scratch.
    * This 4-byte island reads the actual signed halfword through R2; R0 is
    * genuinely written before the load, and MOV changes condition codes. */
   __asm__("mov %0, #0\n\tldrsh %1, [%2, %0]"
           : "=&l"(signed_read_scratch), "=l"(signed_scroll)
           : "l"(scroll_position), "m"(*(s16*)scroll_position)
           : "cc");
   if(signed_scroll>-64)*scroll_position=before_scroll-4;
  }
  else{BYTE(37)=0;
   {register u32 scroll_resume_value __asm__("r0")=18;
    register u8 *scroll_resume_target __asm__("r1")=state;
    __asm__("" : "+r"(scroll_resume_target) : "r"(scroll_resume_value));
    *scroll_resume_target=scroll_resume_value;
   }
  }
  BYTE(37)++;DialogTick();break;
 case 18:
  if((Input[1]&1)||BYTE(37)>70){
   SoundStop(113);DialogClose();
   {u8 *overlay_owner=Scene;u8 saved_overlay=overlay_owner[0x43b];
    u8 *overlay_destination=overlay_owner+0x43a;
    __asm__("" : : "r"(overlay_destination));
    {register u32 timer_zero __asm__("r3")=0;
     /* The native zero survives the first byte publication until the halfword clear. */
     __asm__("" : "+r"(timer_zero));
     *overlay_destination=saved_overlay;
     {u8 *timer_owner=Scene;
      *(u16*)(timer_owner+0x126c)=timer_zero;
      saved_overlay=timer_owner[0x43b];timer_owner[0x43a]=saved_overlay;
     }
    }
   }
   *state=6;
  }
  DialogTick();BYTE(37)++;break;
 case 6:
  if(HALF(0x126c)<=29){if(SIGNED(0x458)>-64)HALF(0x458)-=4;}
  else if(HALF(0x126c)>30)*state=5;
  HALF(0x126c)++;break;
 case 5:{
  u8 previousClass=UNIT[7];u16 zero;
  switch(UNIT[4]){
   case 10:SetFlag(600,0);break;case 9:SetFlag(601,0);break;case 4:SetFlag(602,0);break;case 12:SetFlag(603,0);break;case 94:SetFlag(604,0);break;
  }
  SetUnitClass(UNIT,previousClass);
  {register u16 *fill_source_address __asm__("r1")=&zero;
   __asm__("" : : "r"(fill_source_address));
   *fill_source_address=0;
  }
  CpuSet(&zero,UNIT,0x01000084);UpdateRoster(MessageState[20],Scene+0x9ba);HALF(0x438)=200;unit_resume_value=254;
publish_unit_resume:
  {register u8 *unit_resume_target __asm__("r4")=state;
   __asm__("" : "+r"(unit_resume_target) : "r"(unit_resume_value));
   *unit_resume_target=unit_resume_value;
  }
  break;
 }
 case 19:if(DialogTick()){terminal_resume_value=Next;goto publish_terminal_state;}break;
 case 11:
  if(!TaskRecords[TaskIndex*76]){
   task_resume_value=Next;
publish_task_resume:
   {register u8 *task_resume_target __asm__("r1")=state;
    __asm__("" : "+r"(task_resume_target) : "r"(task_resume_value));
    *task_resume_target=task_resume_value;
   }
  }break;
 case 253:
  Cleanup(255);
  {u8 *cleanup_owner=Scene;
   register u32 cleanup_offset __asm__("r3")=0x1d04;
   __asm__("" : "+r"(cleanup_offset) : "r"(cleanup_owner));
   cleanup_owner[cleanup_offset]=0;
  }
  {u8 *menu_owner=Scene;
   register u32 menu_offset __asm__("r4")=0x986;
   __asm__("" : "+r"(menu_offset) : "r"(menu_owner));
   RestoreMenu(menu_owner[menu_offset]);
  }
  terminal_resume_value=255;goto publish_terminal_state;
 /* Both actual terminal outcomes retain only the common tail below. */
 case 254:case 255:break;
 }
 goto update_dialog;
publish_terminal_state:
 {register u8 *terminal_resume_target __asm__("r5")=state;
  __asm__("" : "+r"(terminal_resume_target) : "r"(terminal_resume_value));
  *terminal_resume_target=terminal_resume_value;
 }
update_dialog:
 {u8 *flag_owner=Scene;
  register u32 flag_offset __asm__("r1")=0x95e;
  __asm__("" : "+r"(flag_offset) : "r"(flag_owner));
  if(flag_owner[flag_offset]&1)UpdateDialog();
 }
}

__asm__(".global RetailCall_08002804\n.thumb_set RetailCall_08002804, 0x08002805\n.global RetailCall_0801174c\n.thumb_set RetailCall_0801174c, 0x0801174d\n.global RetailCall_08011860\n.thumb_set RetailCall_08011860, 0x08011861\n.global RetailCall_08011c60\n.thumb_set RetailCall_08011c60, 0x08011c61\n.global RetailCall_08013210\n.thumb_set RetailCall_08013210, 0x08013211\n.global RetailCall_08013364\n.thumb_set RetailCall_08013364, 0x08013365\n.global RetailCall_08013380\n.thumb_set RetailCall_08013380, 0x08013381\n.global RetailCall_08072130\n.thumb_set RetailCall_08072130, 0x08072131\n.global RetailCall_08076420\n.thumb_set RetailCall_08076420, 0x08076421\n.global RetailCall_08087b30\n.thumb_set RetailCall_08087b30, 0x08087b31\n.global RetailCall_080c8194\n.thumb_set RetailCall_080c8194, 0x080c8195\n.global RetailCall_080c8c24\n.thumb_set RetailCall_080c8c24, 0x080c8c25\n.global RetailCall_080c9574\n.thumb_set RetailCall_080c9574, 0x080c9575\n.global RetailCall_08141520\n.thumb_set RetailCall_08141520, 0x08141521\n.global RetailCall_08141540\n.thumb_set RetailCall_08141540, 0x08141541\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c, 0x0814186d\n.global RetailCall_08142950\n.thumb_set RetailCall_08142950, 0x08142951\n");
