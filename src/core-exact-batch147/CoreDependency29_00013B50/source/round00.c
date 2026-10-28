typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RequestBytePair { u8 unaccessed_00[2]; u8 first; u8 second; u16 unaccessed_04; u16 selector; };
typedef char SelectorOffset[(u32)&(((struct RequestBytePair *)0)->selector)==6?1:-1];
/* Caller-provided values and consumed results; callee internals remain opaque. */
extern u32 RequestHelper_08013AAC(u32,u32);
extern u32 RequestHelper_08013ACC(u32,u32);
extern u32 RequestHelper_08013B08(u32,u32,u32);
u16 UpdateRequestBytePairAndReadResult(struct RequestBytePair *request)
{
    request->first=RequestHelper_08013AAC(request->first,request->selector);
    request->second=RequestHelper_08013ACC(request->second,request->selector);
    return RequestHelper_08013B08(request->first,request->second,request->selector);
}
asm(".global RequestHelper_08013AAC\n.thumb_set RequestHelper_08013AAC,0x08013aad\n"
    ".global RequestHelper_08013ACC\n.thumb_set RequestHelper_08013ACC,0x08013acd\n"
    ".global RequestHelper_08013B08\n.thumb_set RequestHelper_08013B08,0x08013b09\n");
