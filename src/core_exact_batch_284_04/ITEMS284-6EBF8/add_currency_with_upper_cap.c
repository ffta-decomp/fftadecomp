typedef unsigned char u8;
typedef unsigned int u32;
struct CurrencyRam { u8 unknown00[0x1f64]; u32 currency; };
extern struct CurrencyRam gCurrencyRam;
asm(".global gCurrencyRam\n.set gCurrencyRam,0x02000000\n");
void AddCurrencyWithUpperCap(u32 amount) __asm__("SceneTaskDependency_0006EBF8");
/* The u32 sum wraps before the unsigned upper comparison. Do not reinterpret
 * a high-bit amount as signed or replace it with a wider saturating add. */
void AddCurrencyWithUpperCap(u32 amount)
{
    gCurrencyRam.currency += amount;
    if (gCurrencyRam.currency > 99999999U)
        gCurrencyRam.currency = 99999999U;
}
