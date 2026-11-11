typedef unsigned char u8;typedef signed char s8;typedef signed short s16;typedef unsigned short u16;typedef unsigned int u32;
extern u8 **Context __asm__("0x03002810");extern u8 Task[] __asm__("0x03002720"),TaskGraphics[] __asm__("0x030009b0"),TaskData[] __asm__("0x03000ec8"),Callbacks[] __asm__("0x03000880");extern u8 *Preview[] __asm__("0x03000e30");extern u8 MissionDefinitions[] __asm__("0x0855ae4c"),MessageState[] __asm__("0x020020d0");extern u8 PoolStorage[] __asm__("0x0200f390");extern void *Pool __asm__("0x0200f38c"),*StateBuffer __asm__("0x03002778"),*Offered __asm__("0x030027f4");extern u32 StateSize __asm__("0x03000e54");extern u8 Next __asm__("0x0200f388"),Following __asm__("0x0200f389");
void Reset(void) __asm__("RetailCall_08031060");void Initialize(void) __asm__("RetailCall_08030e50");void Setup(void) __asm__("RetailCall_08031348");void SetupMode(u32) __asm__("RetailCall_08030088");void CreateTask(void*,void*,void*,u32) __asm__("RetailCall_08006a7c");void FinishSetup(void) __asm__("RetailCall_08031698");void Restore(void) __asm__("RetailCall_08031714");void SetupMission(void) __asm__("RetailCall_080312a8");void SetupAlternate(void) __asm__("RetailCall_080312cc");void Register(void*,u32,void(*)(u32,u8*)) __asm__("RetailCall_08006adc");void CallbackA(u32,u8*) __asm__("Callback_0803155c"),CallbackB(u32,u8*) __asm__("Callback_0808b288"),CallbackC(u32,u8*) __asm__("Callback_0803197c");void InitMission(void) __asm__("RetailCall_08034e34");void *FindMission(u16) __asm__("RetailCall_080d2de0");void CommitMission(void*,u16) __asm__("RetailCall_080d1e70");u32 Flag(u32) __asm__("RetailCall_080c95a8");u32 SelectContinuation(u32,u32) __asm__("RetailCall_08036034");void ModeReset(void) __asm__("RetailCall_08141708");void ContinueMission(void) __asm__("RetailCall_08030168");void SetScene(u32) __asm__("RetailCall_08009afc");void SetTransition(u32) __asm__("RetailCall_080038e8");void SetFlag(u32,u32) __asm__("RetailCall_080c9574");void PreviewStop(void*,u32) __asm__("RetailCall_0804c834");void SetMode(u32) __asm__("RetailCall_08141748");void Cleanup(void) __asm__("RetailCall_080316d0");void Destroy(void*) __asm__("RetailCall_08006b5c");void Release(void) __asm__("RetailCall_08031264");void *PoolInit(void*,u32) __asm__("RetailCall_080070c8");void *Allocate(void*,u32) __asm__("RetailCall_08007138");void SetTransitionPair(u32,u32) __asm__("RetailCall_08003900");void ConfigureBuffer(void*,u32) __asm__("RetailCall_08137b20");void SelectScene(u32) __asm__("RetailCall_080038c8");void DestroyChild(void*,u32) __asm__("RetailCall_080069f4");void Animate(u32,u8) __asm__("RetailCall_0804bddc");void PoolFree(void*) __asm__("RetailCall_0800718c");
#define DATA Context[1]
#define BYTE(o) DATA[o]
#define HALF(o) (*(u16*)(DATA+(o)))
#define OWNER(o) (((u8*)Context)[o])
#define CLEAR_PREVIEW() PreviewStop(Preview[1],64);Cleanup();Destroy(Task);Release()
#define POOL_SETUP(copy,alloc) Pool=PoolInit(PoolStorage,copy);StateBuffer=Allocate(Pool,alloc);StateSize=alloc
#define TRANSITION2() {register u32 transition __asm__("r0")=2;__asm__("" : "+r"(transition));SetTransition(transition);}
#define SCENE_EXIT(id) SetFlag(69,0);PreviewStop(Preview[1],64);SetMode(3);Cleanup();Destroy(Task);Release();SetScene(id);TRANSITION2();goto exit_scene
#define MAIN_SETUP() Reset();Initialize();Setup();SetupMode(1);FinishSetup();CreateTask(Task,TaskGraphics,TaskData,5);Register(Callbacks,0,CallbackA);Register(Callbacks,1,CallbackB)
/* Mission mode names remain tentative; physical widths and the ordered
 * commit/continuation decisions are taken directly from the original. */
void CoreGlobal36_00030200(u32 unused,u8 *incoming_state)
{
 register u8 *state __asm__("r6")=incoming_state;
 u32 scene_selector;u8 *exit_owner;u32 exit_value;
 __asm__("" : "+r"(state));
 switch(*state){
 case 1:
  Reset();Initialize();Setup();SetupMode(1);CreateTask(Task,TaskGraphics,TaskData,5);FinishSetup();OWNER(132)=0;(*(s8*)(DATA+142))&=~32;BYTE(140)=0;goto register_initial_callbacks;
 case 0:
  Reset();Initialize();Setup();SetupMode(0);CreateTask(Task,TaskGraphics,TaskData,5);FinishSetup();
  {
   u8 *parent_flag=(u8*)Context+132;
   register u32 half_zero __asm__("r2");
   register u32 byte_zero __asm__("r4");
   u8 *volatile *owner;
   u16 *half_out;
   /* Native forms the first real target before defining this zero. */
   __asm__("" : "+r"(parent_flag));
   half_zero=0;
   __asm__("" : "+r"(half_zero));
   *parent_flag=half_zero;
   owner=Context;
   half_out=(u16*)(owner[1]+164);
   __asm__("" : "+r"(half_out));
   byte_zero=0;
   __asm__("" : "+r"(byte_zero));
   *half_out=half_zero;
   owner[1][169]=byte_zero;
   owner=Context;
   /* The original halfword-zero stream remains live to this third store. */
   *(u16*)(owner[1]+32)=half_zero;
   owner[1][100]=byte_zero;
   BYTE(101)=byte_zero;
   BYTE(142)|=32;
   BYTE(140)=3;
   MessageState[20]=128;
   MessageState[21]=byte_zero;
  }
  goto register_initial_callbacks;
 case 2:Restore();BYTE(141)=0;(*(s8*)DATA)&=~1;OWNER(128)=0;OWNER(132)=0;*state=15;break;
 case 12:Restore();(*(s8*)DATA)&=~1;OWNER(128)=0;OWNER(132)=56;*state=15;break;
 case 3:{
  u8 mode;
  Reset();SetupMission();Initialize();Setup();SetupMode(1);FinishSetup();CreateTask(Task,TaskGraphics,TaskData,5);Register(Callbacks,0,CallbackA);Register(Callbacks,1,CallbackB);
  {u8 *volatile *owner=Context;(*(s16*)owner[1])&=~384;(*(s8*)(owner[1]+142))&=~32;}(*(s8*)DATA)&=~2;{u8 *entry_data=DATA;mode=entry_data[169];
  if(!mode){InitMission();*state=2;break;}
  if(mode==1){
   u8 *definition;u8 *committed_data;CommitMission(FindMission(*(u16*)(entry_data+32)),1);committed_data=DATA;definition=MissionDefinitions+*(u16*)(committed_data+32)*70;
   {register u32 low __asm__("r1")=definition[18];register u32 high __asm__("r0")=definition[19];__asm__("" : "+r"(low),"+r"(high));high<<=8;high|=low;__asm__("" : "+r"(high));if(high==1664){committed_data[142]|=32;BYTE(140)=Flag(128);}}
   {u32 continuation=SelectContinuation(0,1);u8 *continuation_out=DATA+172;__asm__("" : "+r"(continuation_out));{register u32 half_zero __asm__("r3")=0;__asm__("" : "+r"(half_zero));*continuation_out=continuation;{u8 *volatile *owner=Context;u16 *half_out=(u16*)(owner[1]+164);__asm__("" : "+r"(half_out));{register u32 byte_zero __asm__("r2")=0;__asm__("" : "+r"(byte_zero));*half_out=half_zero;owner[1][169]=byte_zero;}}}}*state=2;break;
  }
  }
  ModeReset();
  {u8 *selected_data=DATA;
  if(selected_data[169]!=3&&*(u16*)(selected_data+30)){
   u8 *selected=({ u32 index_offset=(u32)*(u16*)(selected_data+30)*4; __asm__("" : "+r"(index_offset)); ({ u8 *slot_base=selected_data+36; __asm__("" : "+r"(slot_base)); *(u8**)(slot_base+index_offset); }); });register u32 low __asm__("r2")=selected[0];register u32 high __asm__("r0")=selected[1];u8 *definition;register u32 definition_flags __asm__("r0");__asm__("" : "+r"(low),"+r"(high));{register u32 mask __asm__("r1")=3;__asm__("" : "+r"(high),"+r"(mask));high&=mask;__asm__("" : "+r"(high));}high<<=8;__asm__("" : "+r"(high));high|=low;__asm__("" : "+r"(high));definition=MissionDefinitions+high*70;
   {
     register u32 flags_low __asm__("r1")=definition[65];
     register u32 flags_high __asm__("r0")=definition[66];
     /* The actual high byte owns the destructive shift and OR. */
     __asm__("" : "+r"(flags_low),"+r"(flags_high));
     flags_high<<=8;
     flags_high|=flags_low;
     definition_flags=flags_high;
    }
   __asm__("" : "+r"(definition_flags));
   {register u32 mask_source __asm__("r2")=2048;register u32 mask_operand __asm__("r1");
    __asm__("" : "+r"(mask_source));mask_operand=mask_source;__asm__("" : "+r"(mask_operand));
    if(definition_flags&mask_operand){*state=2;break;}}
  }
  }
  {u8 *volatile *owner=Context;register u8 *mode_data __asm__("r4");register u8 *mode_address __asm__("r0");register u32 mode_value __asm__("r2");register u32 mode_local __asm__("r1");
  mode_data=owner[1];__asm__("" : "+r"(mode_data));mode_address=mode_data+169;__asm__("" : "+r"(mode_address));mode_value=*mode_address;__asm__("" : "+r"(mode_value));mode_local=mode_value;__asm__("" : "+r"(mode_local));
  if(mode_local==2){mode_address+=4;__asm__("" : "+r"(mode_address));*mode_address=mode_value;__asm__("" : "+r"(mode_local));*state=mode_local;}
  else if(mode_local==4){u8 *record_root=owner[0];u8 *record;__asm__("" : "+r"(record_root));record=record_root+mode_data[170]*6+0x21e;{register u32 low __asm__("r2")=record[4];register u32 high __asm__("r0")=record[5];__asm__("" : "+r"(low),"+r"(high));{register u32 bitmask __asm__("r1")=1;__asm__("" : "+r"(high),"+r"(bitmask));high&=bitmask;__asm__("" : "+r"(high));}high<<=8;__asm__("" : "+r"(high));high|=low;__asm__("" : "+r"(high));*(u16*)(mode_data+32)=high;}{register u8 *target __asm__("r1")=owner[1];register u32 invalid __asm__("r0");__asm__("" : "+r"(target));invalid=65535;__asm__("" : "+r"(invalid));*(u16*)(target+34)=invalid;}{register u8 *selected_pair __asm__("r0")=owner[1];register u32 snapshot __asm__("r1");__asm__("" : "+r"(selected_pair));snapshot=selected_pair[169];__asm__("" : "+r"(snapshot));selected_pair[173]=snapshot;}*state=2;}
  else if(mode_local==5){u8 *record_root=owner[0];u8 *record;u8 *record_prefix;
   register u32 field_bias __asm__("r2");
   __asm__("" : "+r"(record_root));
   record_prefix=record_root+mode_data[170]*6;
   /* This actual prefix is formed before the mode-5 field-bias definition. */
   __asm__("" : "+r"(record_prefix));
   field_bias=0x21e;
   __asm__("" : "+r"(field_bias));
   record=record_prefix+field_bias;{register u32 low __asm__("r2")=record[4];register u32 high __asm__("r0")=record[5];__asm__("" : "+r"(low),"+r"(high));{register u32 bitmask __asm__("r1")=1;__asm__("" : "+r"(high),"+r"(bitmask));high&=bitmask;__asm__("" : "+r"(high));}high<<=8;__asm__("" : "+r"(high));high|=low;__asm__("" : "+r"(high));*(u16*)(mode_data+32)=high;}{register u8 *target __asm__("r1")=owner[1];register u32 invalid __asm__("r0");__asm__("" : "+r"(target));invalid=65535;__asm__("" : "+r"(invalid));*(u16*)(target+34)=invalid;}{register u8 *selected_pair __asm__("r0")=owner[1];register u32 snapshot __asm__("r1");__asm__("" : "+r"(selected_pair));snapshot=selected_pair[169];__asm__("" : "+r"(snapshot));selected_pair[173]=snapshot;}*state=2;}
  else if(mode_local==3){BYTE(172)=SelectContinuation(1,3);{register u8 *pair __asm__("r0")=DATA;register u32 mode_snapshot __asm__("r1");__asm__("" : "+r"(pair));mode_snapshot=pair[169];__asm__("" : "+r"(mode_snapshot));pair[173]=mode_snapshot;}ContinueMission();*state=2;}
  }
  break;
 }
 case 6:Reset();SetupAlternate();Initialize();Setup();SetupMode(1);FinishSetup();CreateTask(Task,TaskGraphics,TaskData,5);Register(Callbacks,0,CallbackA);Register(Callbacks,1,CallbackB);*state=12;break;
 case 5:case 8:case 9:Reset();SetupAlternate();Initialize();Setup();SetupMode(1);FinishSetup();CreateTask(Task,TaskGraphics,TaskData,5);register_initial_callbacks:Register(Callbacks,0,CallbackA);Register(Callbacks,1,CallbackB);*state=2;break;
 case 10:SetScene(172);TRANSITION2();goto exit_scene;
 case 15:Register(Task,0,CallbackC);exit_owner=(u8*)Context+129;exit_value=11;goto write_exit;
 case 16:SCENE_EXIT(164);
 case 17:SCENE_EXIT(166);
 case 18:SCENE_EXIT(163);
 case 19:SCENE_EXIT(165);
 case 20:SCENE_EXIT(162);
 case 21:SetFlag(69,0);CLEAR_PREVIEW();SetTransition(8);goto exit_scene;
 case 23:
  CLEAR_PREVIEW();Reset();Release();Reset();Release();Pool=PoolInit(PoolStorage,50752);{register void **output __asm__("r5")=&StateBuffer;__asm__("" : "+r"(output));*output=Allocate(Pool,50688);}StateSize=50688;Offered=(void*)0x02002fc4;SetTransitionPair(10,1);goto exit_scene;
 case 22:
  SetMode(3);CLEAR_PREVIEW();Pool=PoolInit(PoolStorage,50752);{register void **output __asm__("r5")=&StateBuffer;__asm__("" : "+r"(output));*output=Allocate(Pool,50688);}StateSize=50688;SetTransition(3);goto exit_scene;
 case 24:
  SetFlag(69,0);PreviewStop(Preview[1],64);SetMode(3);Cleanup();Destroy(Task);Release();SetTransition(2);goto exit_scene;
 case 25:
  CLEAR_PREVIEW();Pool=PoolInit(PoolStorage,8992);{register void **output __asm__("r4")=&StateBuffer;register u32 size __asm__("r5")=8928;__asm__("" : "+r"(output),"+r"(size));*output=Allocate(Pool,size);ConfigureBuffer(*output,1);StateSize=size;}scene_selector=6;goto select_scene;
 case 26:
  CLEAR_PREVIEW();Pool=PoolInit(PoolStorage,8992);{register void **output __asm__("r4")=&StateBuffer;register u32 size __asm__("r5")=8928;__asm__("" : "+r"(output),"+r"(size));*output=Allocate(Pool,size);ConfigureBuffer(*output,1);StateSize=size;}scene_selector=7;
  select_scene:SelectScene(scene_selector);
  exit_scene:exit_owner=(u8*)Context+129;exit_value=253;write_exit:*exit_owner=exit_value;*state=exit_value;break;
 case 11:DestroyChild(Task,5);*state=OWNER(129);break;
 case 13:{
  u16 *timer=(u16*)((u8*)Context+158);
  u32 working=(u32)*timer-1;
  register u32 observed __asm__("r2")=working;
  /* Original preserves the full result before STRH. Comparison narrows its
   * own value; the actual callback consumes LOW8 of this surviving copy. */
  __asm__("" : "+r"(observed) : "r"(working));
  *timer=working;
  if(!(u16)working)goto timer_done;
  Animate(8,observed);break;
 }
 case 14:{
  u16 *timer=(u16*)((u8*)Context+158);
  u32 working=(u32)*timer+1;
  register u32 observed __asm__("r2")=working;
  __asm__("" : "+r"(observed) : "r"(working));
  *timer=working;
  if((u16)working==8){timer_done:*state=Next;Next=Following;}
  else Animate(8,observed);break;
 }
 case 254:Cleanup();Destroy(Task);Release();PoolFree(Pool);break;
case 4: case 7: case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: case 60: case 61: case 62: case 63: case 64: case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84: case 85: case 86: case 87: case 88: case 89: case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118: case 119: case 120: case 121: case 122: case 123: case 124: case 125: case 126: case 127: case 128: case 129: case 130: case 131: case 132: case 133: case 134: case 135: case 136: case 137: case 138: case 139: case 140: case 141: case 142: case 143: case 144: case 145: case 146: case 147: case 148: case 149: case 150: case 151: case 152: case 153: case 154: case 155: case 156: case 157: case 158: case 159: case 160: case 161: case 162: case 163: case 164: case 165: case 166: case 167: case 168: case 169: case 170: case 171: case 172: case 173: case 174: case 175: case 176: case 177: case 178: case 179: case 180: case 181: case 182: case 183: case 184: case 185: case 186: case 187: case 188: case 189: case 190: case 191: case 192: case 193: case 194: case 195: case 196: case 197: case 198: case 199: case 200: case 201: case 202: case 203: case 204: case 205: case 206: case 207: case 208: case 209: case 210: case 211: case 212: case 213: case 214: case 215: case 216: case 217: case 218: case 219: case 220: case 221: case 222: case 223: case 224: case 225: case 226: case 227: case 228: case 229: case 230: case 231: case 232: case 233: case 234: case 235: case 236: case 237: case 238: case 239: case 240: case 241: case 242: case 243: case 244: case 245: case 246: case 247: case 248: case 249: case 250: case 251: case 252: case 253:break;
 }
}

__asm__(".global RetailCall_080038c8\n.thumb_set RetailCall_080038c8, 0x080038c9\n.global RetailCall_080038e8\n.thumb_set RetailCall_080038e8, 0x080038e9\n.global RetailCall_08003900\n.thumb_set RetailCall_08003900, 0x08003901\n.global RetailCall_080069f4\n.thumb_set RetailCall_080069f4, 0x080069f5\n.global RetailCall_08006a7c\n.thumb_set RetailCall_08006a7c, 0x08006a7d\n.global RetailCall_08006adc\n.thumb_set RetailCall_08006adc, 0x08006add\n.global RetailCall_08006b5c\n.thumb_set RetailCall_08006b5c, 0x08006b5d\n.global RetailCall_080070c8\n.thumb_set RetailCall_080070c8, 0x080070c9\n.global RetailCall_08007138\n.thumb_set RetailCall_08007138, 0x08007139\n.global RetailCall_0800718c\n.thumb_set RetailCall_0800718c, 0x0800718d\n.global RetailCall_08009afc\n.thumb_set RetailCall_08009afc, 0x08009afd\n.global RetailCall_08030088\n.thumb_set RetailCall_08030088, 0x08030089\n.global RetailCall_08030168\n.thumb_set RetailCall_08030168, 0x08030169\n.global RetailCall_08030e50\n.thumb_set RetailCall_08030e50, 0x08030e51\n.global RetailCall_08031060\n.thumb_set RetailCall_08031060, 0x08031061\n.global RetailCall_08031264\n.thumb_set RetailCall_08031264, 0x08031265\n.global RetailCall_080312a8\n.thumb_set RetailCall_080312a8, 0x080312a9\n.global RetailCall_080312cc\n.thumb_set RetailCall_080312cc, 0x080312cd\n.global RetailCall_08031348\n.thumb_set RetailCall_08031348, 0x08031349\n.global RetailCall_08031698\n.thumb_set RetailCall_08031698, 0x08031699\n.global RetailCall_080316d0\n.thumb_set RetailCall_080316d0, 0x080316d1\n.global RetailCall_08031714\n.thumb_set RetailCall_08031714, 0x08031715\n.global RetailCall_08034e34\n.thumb_set RetailCall_08034e34, 0x08034e35\n.global RetailCall_08036034\n.thumb_set RetailCall_08036034, 0x08036035\n.global RetailCall_0804bddc\n.thumb_set RetailCall_0804bddc, 0x0804bddd\n.global RetailCall_0804c834\n.thumb_set RetailCall_0804c834, 0x0804c835\n.global RetailCall_080c9574\n.thumb_set RetailCall_080c9574, 0x080c9575\n.global RetailCall_080c95a8\n.thumb_set RetailCall_080c95a8, 0x080c95a9\n.global RetailCall_080d1e70\n.thumb_set RetailCall_080d1e70, 0x080d1e71\n.global RetailCall_080d2de0\n.thumb_set RetailCall_080d2de0, 0x080d2de1\n.global RetailCall_08137b20\n.thumb_set RetailCall_08137b20, 0x08137b21\n.global RetailCall_08141708\n.thumb_set RetailCall_08141708, 0x08141709\n.global RetailCall_08141748\n.thumb_set RetailCall_08141748, 0x08141749\n.global Callback_0803155c\n.thumb_set Callback_0803155c,0x0803155d\n.global Callback_0808b288\n.thumb_set Callback_0808b288,0x0808b289\n.global Callback_0803197c\n.thumb_set Callback_0803197c,0x0803197d\n");
