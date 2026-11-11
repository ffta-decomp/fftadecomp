/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
struct Unit {u8 data[264];};
struct Reference {unsigned int unknown;struct Unit *unit;};
struct View {u8 gap[168];u8 selection[3];};
extern struct View gView;
extern struct Unit gSecondary[];
extern struct Reference *GetSceneReference(u8);

asm(".global gView\n.set gView,0x020020d0\n.global gSecondary\n.set gSecondary,0x02002fc4\n.global GetSceneReference\n.thumb_set GetSceneReference,0x8121c71");
unsigned int SetSceneReferenceFromSavedSelection(void *unused,u8 *command)
{
    u8 index = 0;
    struct Reference *reference;
    switch (command[1]) {
    case 0: index = gView.selection[0]-1; break;
    case 1: index = gView.selection[1]-1; break;
    case 2: index = gView.selection[2]-1; break;
    }
    reference = GetSceneReference(command[2]);
    reference->unit = &gSecondary[index];
    return 272;
}
