typedef unsigned int u32;

extern void BiosCpuSet(const void *source, void *destination, u32 control);

void RemainingBand43_000DAE70(const void *source, void *destination)
{
    BiosCpuSet(source, destination, 160U);
}

asm(".global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n"
    ".global CopyDefinitionWindowScanlines\n"
    ".thumb_set CopyDefinitionWindowScanlines,RemainingBand43_000DAE70\n");
