typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *RosterDisplayRoot;
extern u8 RosterResourceScratch[];
extern u8 RosterPaletteSnapshot[];
extern u32 QuerySelectedRosterResource(void *);
extern void *CopySelectedRosterResource(void *,void *);
extern u32 QuerySelectedRosterVariant(void *,u32);
extern void PrepareRosterVariant(void *,u32);
extern void *GetSelectedRosterReference(void *);
extern void CopyRosterWords(const void *,void *,u32);
__asm__(".global RosterDisplayRoot\n.set RosterDisplayRoot,0x03002818\n"
        ".global RosterResourceScratch\n.set RosterResourceScratch,0x02003cb0\n"
        ".global RosterPaletteSnapshot\n.set RosterPaletteSnapshot,0x03003860\n"
        ".global QuerySelectedRosterResource\n.thumb_set QuerySelectedRosterResource,0x080cb809\n"
        ".global CopySelectedRosterResource\n.thumb_set CopySelectedRosterResource,0x080cb869\n"
        ".global QuerySelectedRosterVariant\n.thumb_set QuerySelectedRosterVariant,0x080cb7c1\n"
        ".global PrepareRosterVariant\n.thumb_set PrepareRosterVariant,0x080cb8d5\n"
        ".global GetSelectedRosterReference\n.thumb_set GetSelectedRosterReference,0x080cb929\n"
        ".global CopyRosterWords\n.thumb_set CopyRosterWords,0x0814186d");
void PrepareSelectedRosterResources(void) __asm__("CoreScene34_0007478C");
void PrepareSelectedRosterResources(void)
{
    register u8 *initial_scratch __asm__("r0") = RosterResourceScratch;
    register u8 *scratch __asm__("r8");
    register u8 **root_slot __asm__("r5");
    register u8 *initial_root __asm__("r0");
    register u32 selected_offset __asm__("r6");
    u32 raw;
    u8 *destination;
    u32 variant;
    void *reference;
    u8 *root;
    __asm__("" : "+r"(initial_scratch));
    scratch = initial_scratch;
    __asm__("" : "+r"(scratch));
    root_slot = &RosterDisplayRoot;
    __asm__("" : "+r"(root_slot));
    initial_root = *root_slot;
    __asm__("" : "+r"(initial_root));
    selected_offset = 0x1d0c;
    __asm__("" : "+r"(selected_offset));
    raw = QuerySelectedRosterResource(*(void **)(initial_root + selected_offset));
    CopySelectedRosterResource(scratch,*(void **)(*root_slot + selected_offset));
    CopyRosterWords(scratch,(void *)0x06014300,(raw << 10) >> 11);
    {
        register u8 *variant_root __asm__("r0") = *root_slot;
        register u32 destination_offset __asm__("r1");
        __asm__("" : "+r"(variant_root));
        destination_offset = 0x2e8;
        __asm__("" : "+r"(destination_offset));
        destination = variant_root + destination_offset;
        __asm__("" : "+r"(destination));
        variant = QuerySelectedRosterVariant(*(void **)(variant_root + selected_offset),1);
    }
    PrepareRosterVariant(destination,(u8)variant);
    reference = GetSelectedRosterReference(*(void **)(*root_slot + selected_offset));
    {
        register u8 *published_root __asm__("r1") = *root_slot;
        register u32 reference_offset __asm__("r3");
        register void **reference_destination __asm__("r2");
        __asm__("" : "+r"(published_root));
        reference_offset = 0x454;
        __asm__("" : "+r"(reference_offset));
        reference_destination = (void **)(published_root + reference_offset);
        __asm__("" : "+r"(reference_destination));
        *reference_destination = reference;
        published_root[0x452] = 1;
    }
    {
        register u8 *first_source __asm__("r0") = *root_slot + 40;
        register u8 *palette_cursor __asm__("r4");
        register u32 copy_control __asm__("r6");
        __asm__("" : "+r"(first_source));
        palette_cursor = RosterPaletteSnapshot;
        __asm__("" : "+r"(palette_cursor));
        copy_control = 0x04000080;
        __asm__("" : "+r"(copy_control));
        CopyRosterWords(first_source,palette_cursor,copy_control);
        {
            register u8 *second_source __asm__("r0") = *root_slot;
            register u32 second_source_offset __asm__("r1");
            register u32 snapshot_delta __asm__("r3");
            __asm__("" : "+r"(second_source));
            second_source_offset = 552;
            __asm__("" : "+r"(second_source_offset));
            second_source += second_source_offset;
            __asm__("" : "+r"(second_source));
            snapshot_delta = 512;
            __asm__("" : "+r"(snapshot_delta));
            palette_cursor += snapshot_delta;
            __asm__("" : "+r"(palette_cursor));
            CopyRosterWords(second_source,palette_cursor,copy_control);
        }
    }
}
