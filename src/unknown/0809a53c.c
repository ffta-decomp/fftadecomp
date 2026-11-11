struct SequenceObject;
struct Actor {unsigned char unknown0[68];struct SequenceObject *sequence;};
int QueryIndex(struct SequenceObject *) __asm__("ThumbCall_08021e3c");
int sub_0809A53C(struct Actor *actor)
{
    return QueryIndex(actor->sequence);
}
asm(".global ThumbCall_08021e3c\n.thumb_set ThumbCall_08021e3c,0x08021e3d\n");
