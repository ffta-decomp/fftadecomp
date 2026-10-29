typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Keys {u16 h0,h2;};
struct DmaChannel {volatile const void * volatile source;volatile void * volatile destination;volatile u32 control;};
extern void *scene_screen_token;
extern u8 scene_mode;
extern struct Keys scene_keys;
extern u16 display_control;
extern struct DmaChannel dma_channel3;
extern void PrepareSceneScreen(void);
extern void *CreateSceneScreen(void);
extern u32 PollSceneScreen(void *,u32,u32);
extern void FinalizeSceneScreen(void *);
void AdvancePairedSceneScreen(void *,u8 *) asm("Registered39_0014011C");
void AdvancePairedSceneScreen(void *unused,u8 *state)
{
    u16 zero;
    register u16 *zero_target asm("r1");
    switch (*state) {
    case 0:
        PrepareSceneScreen();
        scene_screen_token=CreateSceneScreen();
        *state=1;
        break;
    case 1:
        if (!(u8)PollSceneScreen(scene_screen_token,scene_keys.h2,scene_keys.h0))
            *state=2;
        break;
    case 2:
        FinalizeSceneScreen(scene_screen_token);
        scene_mode=255;
        *state=3;
        zero_target=&zero;
        /* Actual write target precedes zero; DMA source is separately formed. */
        asm("" : "+r"(zero_target));
        *zero_target=0;
        dma_channel3.source=&zero;
        dma_channel3.destination=(void *)0x06000000;
        dma_channel3.control=0x8100C000;
        (void)dma_channel3.control;
        display_control=64;
        break;
    }
}
asm(".global scene_screen_token\n.set scene_screen_token,0x0200f3c0\n.global scene_mode\n.set scene_mode,0x0200f390\n.global scene_keys\n.set scene_keys,0x03000000\n.global display_control\n.set display_control,0x03000940\n.global dma_channel3\n.set dma_channel3,0x040000d4\n.global PrepareSceneScreen\n.thumb_set PrepareSceneScreen,0x0813fd79\n.global CreateSceneScreen\n.thumb_set CreateSceneScreen,0x081413f9\n.global PollSceneScreen\n.thumb_set PollSceneScreen,0x0814143d\n.global FinalizeSceneScreen\n.thumb_set FinalizeSceneScreen,0x08141475\n");
