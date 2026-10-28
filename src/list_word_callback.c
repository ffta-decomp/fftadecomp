typedef unsigned int u32;

struct ListOwner;
extern u32 GetListOwnerWord0(const struct ListOwner *owner);

typedef u32 (*WordCallback)(u32 word, void *argument);

struct ListWordCallbackContext {
    void *argument;
    WordCallback callback;
};

u32 VisitListOwnerWord(const struct ListOwner *owner,
                       const struct ListWordCallbackContext *context)
{
    u32 word = GetListOwnerWord0(owner);
    return context->callback(word, context->argument);
}
