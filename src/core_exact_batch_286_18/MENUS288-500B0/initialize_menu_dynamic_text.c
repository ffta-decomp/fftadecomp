typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
struct TextPanel {u8 observed0[8];void *transfer;u16 *buffer;u8 observed16[5];u8 width;u8 observed22[6];u16 tile;u8 observed30[2];};
struct TextRoot {u8 observed[20];};
struct TextContext {struct TextRoot *root;u8 observed4[68];struct TextPanel panel;u8 observed104[40];s8 *choices;};
struct TextState {unsigned word0;u8 observed4[8];u16 id;u16 selection;};
struct TextChannel {u8 observed0[16];u8 *buffer;};
struct TextDefaults {u8 observed0[152];void *name;};
extern struct TextState gTextState;
extern struct TextChannel gTextChannel;
extern const u16 TextIds[];
extern const struct TextDefaults TextDefaults;
extern unsigned QueryTextSelection(void *);
extern void ClearTextDestination(void *,unsigned);
extern void *AllocateText(unsigned);
extern void ComposeFixedText(void *,void *,void *,unsigned,unsigned,unsigned);
extern void CopyTextName(void *,void *);
extern void RenderText(void *,void *,void *,unsigned,unsigned);
extern void ReleaseText(void *);
extern void DrawTextNumber(void *,unsigned,unsigned,unsigned);
extern void DrawPanelNumber(void *,unsigned,unsigned,unsigned,unsigned);
extern void *QueryTextTransfer(void);
extern void ScheduleTextTransfer(void *,void *,void *,unsigned,unsigned,unsigned,unsigned);
__asm__(".global gTextState\n.set gTextState,0x20020d0\n.global gTextChannel\n.set gTextChannel,0x30008b0\n.global TextIds\n.set TextIds,0x8529ee4\n.global TextDefaults\n.set TextDefaults,0x85567f0\n.global QueryTextSelection\n.thumb_set QueryTextSelection,0x80502ed\n.global ClearTextDestination\n.thumb_set ClearTextDestination,0x8013a89\n.global AllocateText\n.thumb_set AllocateText,0x8005b29\n.global ComposeFixedText\n.thumb_set ComposeFixedText,0x8013e9d\n.global CopyTextName\n.thumb_set CopyTextName,0x8018c25\n.global RenderText\n.thumb_set RenderText,0x8015111\n.global ReleaseText\n.thumb_set ReleaseText,0x8005b41\n.global DrawTextNumber\n.thumb_set DrawTextNumber,0x804fdf5\n.global DrawPanelNumber\n.thumb_set DrawPanelNumber,0x804ffb9\n.global QueryTextTransfer\n.thumb_set QueryTextTransfer,0x804ca8d\n.global ScheduleTextTransfer\n.thumb_set ScheduleTextTransfer,0x8000bad");
void InitializeMenuDynamicText(struct TextContext *ctx) {
 struct TextPanel *panel=&ctx->panel;
 u16 selected=(u16)QueryTextSelection(ctx);
 u8 *destination;
 u8 *buffer;
 u16 *first;
 void *second;
 void *transfer;
 register unsigned tail_offset __asm__("r1");
 u8 *tail;
 gTextState.selection=selected;
 gTextState.word0=0;
 gTextState.id=TextIds[selected-1];
 destination=gTextChannel.buffer+32*panel->tile;
 ClearTextDestination(destination,28);
 buffer=AllocateText(512);
 if(ctx->choices[selected-1]) {
  tail_offset=256;
  __asm__("" : "+r"(tail_offset));
  tail=buffer+tail_offset;
  __asm__("" : "+r"(tail));
  ComposeFixedText(buffer,(void *)0x084c3798,tail,9,0,0);
 }
 else {
  buffer[0]=64;buffer[1]=103;buffer[2]=0;
  CopyTextName(buffer+3,TextDefaults.name);
 }
 RenderText(ctx->root+1,destination,buffer,0,1);
 ReleaseText(buffer);
 DrawTextNumber(ctx,6,0,selected);
 DrawPanelNumber(panel,2,1,selected,0);
 first=panel->buffer;
 first[1]=0xd0f8;
 first[2]=0xd0f9;
 second=panel->transfer;
 transfer=QueryTextTransfer();
 ScheduleTextTransfer(transfer,first,second,(u16)(panel->width-6),2,2*panel->width,64);
}
