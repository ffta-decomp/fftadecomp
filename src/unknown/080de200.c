typedef signed char s8;
extern void SetActorDirectionSequence(void *, int);
asm(".global SetActorDirectionSequence\n.thumb_set SetActorDirectionSequence, 0x080de211");
void RemainingBand43_000DE200(void *actor) { SetActorDirectionSequence(actor, *(s8 *)((char *)actor + 31)); }
