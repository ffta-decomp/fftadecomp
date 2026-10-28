typedef unsigned int u32;
struct HandleWordView { u32 unaccessed[10]; u32 word_at40; };
u32 ExchangeHandleWord(struct HandleWordView *handle, u32 replacement)
{
    u32 previous = handle->word_at40;
    handle->word_at40 = replacement;
    return previous;
}
