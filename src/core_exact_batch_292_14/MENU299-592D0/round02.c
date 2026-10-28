typedef unsigned char u8;
struct Payload {u8 *target;unsigned value;unsigned state;};
extern u8 *context;
extern void Service(unsigned);
asm(".global context\n.set context,0x0200f428\n.global Service\n.thumb_set Service,0x08141541");
void CoreClosure31_000592D0(struct Payload *payload){*payload->target=payload->value;{u8 *root=context;unsigned next_state=payload->state;root[0x2ca0]=next_state;}Service(105);}
