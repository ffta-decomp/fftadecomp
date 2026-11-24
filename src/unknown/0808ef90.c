/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808EF90.c
 * Original SHA-256: 25e8a71013100492dc042234495760f721ec911138f9c81911e4408833f8f743
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct State {
    u8 unknown_00[0x2D50];
    void *context;
};

extern struct State *data_03002818;
extern int func_0808CBDC(u16 index, void *context);

int func_0808EF90(int count)
{
    int index;

    for (index = 0; index < count; index++) {
        if (func_0808CBDC(index, data_03002818->context))
            return 1;
    }

    return 0;
}
