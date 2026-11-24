/* Contributed by gg; original source and attribution follow. */
/* Buffer55_0000DE64
   entry 0x0800DE64, 12 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned int u32;

extern void BiosCpuSet(const void *source, void *destination, u32 control);

void f_target(const void *source, void *destination)
{
    BiosCpuSet(source, destination, 160U);
}

asm(".global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n"
    ".global CopyDefinitionWindowScanlines\n"
    ".thumb_set CopyDefinitionWindowScanlines,f_target\n");
