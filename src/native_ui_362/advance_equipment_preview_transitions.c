typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *volatile gEquipmentMenuOwner;
__asm__(".global gEquipmentMenuOwner\n.set gEquipmentMenuOwner,0x03002818");
void AdvanceEquipmentPreviewTransitions(void) __asm__("CoreScene34_00073254");
void AdvanceEquipmentPreviewTransitions(void)
{
 register u8 *context __asm__("r3");
 register u8 *initial_context __asm__("r0");
 register u8 *final_context __asm__("r2");
 register u8 *first_counter __asm__("r3");
 register u8 *later_counter __asm__("r1");
 register u32 initial_offset __asm__("r2");
 register u32 later_offset __asm__("r3");
 u32 remaining;
 register u8 *volatile *first_slot __asm__("r1")=&gEquipmentMenuOwner;
 register u8 *volatile *owner_slot __asm__("r2");
 __asm__("" : "+r"(first_slot));
 initial_context=*first_slot;
 __asm__("" : "+r"(initial_context));
 initial_offset=0x984;
 __asm__("" : "+r"(initial_offset));
 first_counter=initial_context+initial_offset;
 __asm__("" : "+r"(first_counter));
 remaining=*first_counter;
 owner_slot=first_slot;
 __asm__("" : "+r"(owner_slot));
 if(remaining!=0) {
  *first_counter=remaining-1;
  context=*owner_slot;
  __asm__("" : "+r"(context));
  {
   register u32 field_offset __asm__("r4")=0x984;
   register u32 fresh_counter __asm__("r0");
   __asm__("" : "+r"(field_offset));
   fresh_counter=*(u8*)(context+field_offset);
   __asm__("" : "+r"(fresh_counter));
   if(fresh_counter!=0) {
    register u32 destination_offset __asm__("r0")=0x978;
    register u16 *destination __asm__("r1");
    register u32 delta_address __asm__("r0");
    register u32 delta_value __asm__("r0");
    register u32 current_value __asm__("r3");
    __asm__("" : "+r"(destination_offset));
    destination=(u16*)(context+destination_offset);
    __asm__("" : "+r"(destination));
    field_offset-=8;
    __asm__("" : "+r"(field_offset));
    delta_address=(u32)context+field_offset;
    __asm__("" : "+r"(delta_address));
    delta_value=*(u16*)delta_address;
    __asm__("" : "+r"(delta_value));
    /* The root's last address consumer precedes this destructive H read. */
    current_value=*destination;
    __asm__("" : "+r"(current_value));
    delta_value+=current_value;
    __asm__("" : "+r"(delta_value));
    *destination=delta_value;
   } else {
    register u32 source_address __asm__("r0");
    register u32 snapshot_value __asm__("r1");
    register u32 destination_address __asm__("r0");
    field_offset=0x980;
    __asm__("" : "+r"(field_offset));
    source_address=(u32)context+field_offset;
    __asm__("" : "+r"(source_address));
    snapshot_value=*(u16*)source_address;
    __asm__("" : "+r"(snapshot_value));
    field_offset-=8;
    __asm__("" : "+r"(field_offset));
    destination_address=(u32)context+field_offset;
    __asm__("" : "+r"(destination_address));
    *(u16*)destination_address=snapshot_value;
   }
  }
 }
 initial_context=*owner_slot;
 __asm__("" : "+r"(initial_context));
 later_offset=0x985;
 __asm__("" : "+r"(later_offset));
 later_counter=initial_context+later_offset;
 __asm__("" : "+r"(later_counter));
 remaining=*later_counter;
 if(remaining!=0) {
  *later_counter=remaining-1;
  context=*owner_slot;
  __asm__("" : "+r"(context));
  {
   register u32 field_offset __asm__("r4")=0x985;
   register u32 fresh_counter __asm__("r0");
   __asm__("" : "+r"(field_offset));
   fresh_counter=*(u8*)(context+field_offset);
   __asm__("" : "+r"(fresh_counter));
   if(fresh_counter!=0) {
    register u32 destination_offset __asm__("r0")=0x97a;
    register u16 *destination __asm__("r1");
    register u32 delta_address __asm__("r0");
    register u32 delta_value __asm__("r0");
    register u32 current_value __asm__("r3");
    __asm__("" : "+r"(destination_offset));
    destination=(u16*)(context+destination_offset);
    __asm__("" : "+r"(destination));
    field_offset-=7;
    __asm__("" : "+r"(field_offset));
    delta_address=(u32)context+field_offset;
    __asm__("" : "+r"(delta_address));
    delta_value=*(u16*)delta_address;
    __asm__("" : "+r"(delta_value));
    /* The root's last address consumer precedes this destructive H read. */
    current_value=*destination;
    __asm__("" : "+r"(current_value));
    delta_value+=current_value;
    __asm__("" : "+r"(delta_value));
    *destination=delta_value;
   } else {
    register u32 source_address __asm__("r0");
    register u32 snapshot_value __asm__("r1");
    register u32 destination_address __asm__("r0");
    field_offset=0x982;
    __asm__("" : "+r"(field_offset));
    source_address=(u32)context+field_offset;
    __asm__("" : "+r"(source_address));
    snapshot_value=*(u16*)source_address;
    __asm__("" : "+r"(snapshot_value));
    field_offset-=8;
    __asm__("" : "+r"(field_offset));
    destination_address=(u32)context+field_offset;
    __asm__("" : "+r"(destination_address));
    *(u16*)destination_address=snapshot_value;
   }
  }
 }
 initial_context=*owner_slot;
 __asm__("" : "+r"(initial_context));
 later_offset=0x98c;
 __asm__("" : "+r"(later_offset));
 later_counter=initial_context+later_offset;
 __asm__("" : "+r"(later_counter));
 remaining=*later_counter;
 if(remaining!=0) {
  *later_counter=remaining-1;
  context=*owner_slot;
  __asm__("" : "+r"(context));
  {
   register u32 field_offset __asm__("r4")=0x98c;
   register u32 fresh_counter __asm__("r0");
   __asm__("" : "+r"(field_offset));
   fresh_counter=*(u8*)(context+field_offset);
   __asm__("" : "+r"(fresh_counter));
   if(fresh_counter!=0) {
    register u32 destination_offset __asm__("r0")=0x994;
    register u16 *destination __asm__("r1");
    register u32 delta_address __asm__("r0");
    register u32 delta_value __asm__("r0");
    register u32 current_value __asm__("r3");
    __asm__("" : "+r"(destination_offset));
    destination=(u16*)(context+destination_offset);
    __asm__("" : "+r"(destination));
    field_offset+=6;
    __asm__("" : "+r"(field_offset));
    delta_address=(u32)context+field_offset;
    __asm__("" : "+r"(delta_address));
    delta_value=*(u16*)delta_address;
    __asm__("" : "+r"(delta_value));
    /* The root's last address consumer precedes this destructive H read. */
    current_value=*destination;
    __asm__("" : "+r"(current_value));
    delta_value+=current_value;
    __asm__("" : "+r"(delta_value));
    *destination=delta_value;
   } else {
    register u32 source_address __asm__("r0");
    register u32 snapshot_value __asm__("r1");
    register u32 destination_address __asm__("r0");
    field_offset=0x990;
    __asm__("" : "+r"(field_offset));
    source_address=(u32)context+field_offset;
    __asm__("" : "+r"(source_address));
    snapshot_value=*(u16*)source_address;
    __asm__("" : "+r"(snapshot_value));
    field_offset+=4;
    __asm__("" : "+r"(field_offset));
    destination_address=(u32)context+field_offset;
    __asm__("" : "+r"(destination_address));
    *(u16*)destination_address=snapshot_value;
   }
  }
 }
 final_context=*owner_slot;
 __asm__("" : "+r"(final_context));
 {
  register u32 source_offset __asm__("r1")=0x994;
  register u32 source_address __asm__("r0");
  register u32 copied_value __asm__("r1");
  register u32 destination_offset __asm__("r3");
  register u32 destination_address __asm__("r0");
  register u32 third_counter_offset __asm__("r4");
  register u32 second_counter_offset __asm__("r1");
  register u32 counter_address __asm__("r0");
  /* Guard scalar is a distinct C value from its short address working. */
  u32 counter_value;
  __asm__("" : "+r"(source_offset));
  source_address=(u32)final_context+source_offset;
  __asm__("" : "+r"(source_address));
  copied_value=*(u16*)source_address;
  __asm__("" : "+r"(copied_value));
  destination_offset=0x998;
  __asm__("" : "+r"(destination_offset));
  destination_address=(u32)final_context+destination_offset;
  __asm__("" : "+r"(destination_address));
  *(u16*)destination_address=copied_value;
  third_counter_offset=0x98c;
  __asm__("" : "+r"(third_counter_offset));
  counter_address=(u32)final_context+third_counter_offset;
  __asm__("" : "+r"(counter_address));
  counter_value=*(u8*)counter_address;
  __asm__("" : "+r"(counter_value));
  if(counter_value==0) {
   second_counter_offset=0x985;
   __asm__("" : "+r"(second_counter_offset));
   counter_address=(u32)final_context+second_counter_offset;
   __asm__("" : "+r"(counter_address));
   counter_value=*(u8*)counter_address;
   __asm__("" : "+r"(counter_value));
   if(counter_value==0) {
    destination_offset-=20;
    __asm__("" : "+r"(destination_offset));
    counter_address=(u32)final_context+destination_offset;
    __asm__("" : "+r"(counter_address));
    counter_value=*(u8*)counter_address;
    __asm__("" : "+r"(counter_value));
    if(counter_value==0) {
     third_counter_offset-=28;
     __asm__("" : "+r"(third_counter_offset));
     final_context+=third_counter_offset;
     __asm__("" : "+r"(final_context));
     {
      register u32 old_flags __asm__("r1")=*final_context;
      register int negative_mask __asm__("r0");
      __asm__("" : "+r"(old_flags));
      negative_mask=-3;
      /* Actual full signed word is consumed before LOW8 store. */
      __asm__("" : "+r"(negative_mask));
      negative_mask&=old_flags;
      __asm__("" : "+r"(negative_mask));
      *final_context=(u8)negative_mask;
     }
    }
   }
  }
 }
}
