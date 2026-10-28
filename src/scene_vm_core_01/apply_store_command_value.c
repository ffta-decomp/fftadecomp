/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
extern void ApplySceneValue(int);
extern void SetIndexedValue(int,int);

asm(".global ApplySceneValue\n.thumb_set ApplySceneValue,0x80bd11d\n.global SetIndexedValue\n.thumb_set SetIndexedValue,0x80c95c1");
unsigned int ApplyAndStoreSceneCommandValue(void *unused,u8 *command)
{
    ApplySceneValue(command[1]);
    SetIndexedValue(53,command[1]);
    return 272;
}
