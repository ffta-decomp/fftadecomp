extern unsigned char *payload(void*);extern void update(void*);
void RemainingCore48_00068820(unsigned char *panel){if(panel[8]==4){if(payload(*(void **)(panel+16))[9]&1)return;}update(panel+132);}
__asm__(".thumb_set payload,0x08005bfd\n.thumb_set update,0x08017e29");
