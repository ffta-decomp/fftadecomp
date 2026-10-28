struct SequenceObject;
struct Actor {unsigned char unknown0[68];struct SequenceObject *sequence;};
void SetCursor(struct SequenceObject *, unsigned int) __asm__("ThumbCall_08021e28");
void sub_0809A530(struct Actor *actor, unsigned int index)
{
    SetCursor(actor->sequence,index);
}
asm(".global ThumbCall_08021e28\n.thumb_set ThumbCall_08021e28,0x08021e29\n");
