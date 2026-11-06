typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u8 gNativeMissionDefinitions[];
extern u8 gNativeEwram[];
extern u8 gNativePanelVram[];
extern u8 *gNativeDetailContext;
extern const u8 *gNativeCaptionResources[];
extern u32 NativeTextOrigin(u32,u32,u32,u32);
extern u32 WritePaddedHalfwordDecimalText(u8*,u16,u32);
extern u32 ProcessNativeEncodedText(void*,u32,const u8*,u32,u32);
extern void SetNativePanelStyle(u32,u32,u32,u32,u32,u32);
extern void DrawNativeLabeledRow(u32,u32,u32,u32,u32,const u8*);
__asm__(".global gNativeMissionDefinitions\n.set gNativeMissionDefinitions,0x0855ae4c\n"
        ".global gNativeEwram\n.set gNativeEwram,0x02000000\n"
        ".global gNativePanelVram\n.set gNativePanelVram,0x0600afe0\n"
        ".global gNativeDetailContext\n.set gNativeDetailContext,0x03002810\n"
        ".global gNativeCaptionResources\n.set gNativeCaptionResources,0x085668b0\n"
        ".global NativeTextOrigin\n.thumb_set NativeTextOrigin,0x0808b92d\n"
        ".global WritePaddedHalfwordDecimalText\n.thumb_set WritePaddedHalfwordDecimalText,0x080142dd\n"
        ".global ProcessNativeEncodedText\n.thumb_set ProcessNativeEncodedText,0x08015111\n"
        ".global SetNativePanelStyle\n.thumb_set SetNativePanelStyle,0x080379a9\n"
        ".global DrawNativeLabeledRow\n.thumb_set DrawNativeLabeledRow,0x080378c9");
void DrawNativeMissionRequirementPanel(const u8*,u16) __asm__("CoreRegion_000461D4");
void DrawNativeMissionRequirementPanel(const u8 *record,u16 input_style_mask)
{
    u8 number_text[32];
    u32 snapshot;
    u32 style_mask=input_style_mask;
    u32 low_id_byte=(u32)record[0];
    u32 high_id_byte=(u32)record[1];
    /* The native high-bit projection is the destructive OR accumulator;
     * the earlier low byte is a separate captured input. */
    u32 mission_id=((high_id_byte&3)<<8)|low_id_byte;
    const u8 *definition=gNativeMissionDefinitions+mission_id*70;
    u32 value;
    register u32 definition_value_snapshot asm("r9");
    register u32 origin asm("r1");
    u32 digits;
    u32 row_label;
    snapshot=gNativeEwram[0x21b4];
    value=definition[42];
    /* Native preserves this byte-valued full snapshot separately from the
     * range-comparison working value, for the actual three-digit branch. */
    definition_value_snapshot=value;
    asm("" : : "r"(definition_value_snapshot));
    {
        u32 prefix_mode;
        void *prefix_destination;
        register void *suffix_destination asm("r0");
        u8 *prefix_base;
        register u8 **prefix_context_slot asm("r6");
        register u32 prefix_offset asm("r8");
        const u8 *prefix_caption;
        origin=NativeTextOrigin(5,(u32)gNativePanelVram,0,0);
        /* Actual full-word result enters R1 before the fresh context setup. */
        asm("" : "+r"(origin));
        prefix_context_slot=&gNativeDetailContext;
        /* Native context-slot pointer is a distinct initialized R6 value;
         * preserve actual pointee reloads after every text/origin helper. */
        asm("" : "+r"(prefix_context_slot));
        prefix_base=*prefix_context_slot;
        prefix_offset=0xc4c;
        /* Original saves this initialized offset only across the initial
         * number/suffix phase. The loaded base precedes that definition. */
        asm("" : "+r"(prefix_offset) : "r"(prefix_base));
        prefix_destination=prefix_base+prefix_offset;
        prefix_caption=gNativeCaptionResources[12];
        prefix_mode=1;
        /* Real argument setup precedes the native short mode lifetime.
         * The mode crosses only the initial number/suffix drawing calls. */
        asm("" : "+r"(prefix_mode) : "r"(prefix_destination), "r"(prefix_caption));
        ProcessNativeEncodedText(prefix_destination,origin,prefix_caption,0,prefix_mode);
        if(value<=9) {
            {
                register u8 *number_out asm("r0")=number_text;
                /* Original SP8 buffer argument is ready before the
                 * independent saved-value copy into R1. */
                asm("" : : "r"(number_out));
                WritePaddedHalfwordDecimalText(number_out,value,1);
            }
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,10,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            {
                u8 *small_base=*prefix_context_slot;
                u32 small_offset=0xc4c;
                /* Native reloads this short literal for this address,
                 * rather than preserving it across the text processor. */
                asm("" : "+r"(small_offset) : "r"(small_base));
                ProcessNativeEncodedText(small_base+small_offset,origin,number_text,0,prefix_mode);
            }
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,12,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            {
                register u8 *small_base asm("r0")=*prefix_context_slot;
                register u32 small_offset asm("r3")=0xc4c;
                /* Separate original post-call fresh offset definition. */
                asm("" : "+r"(small_offset) : "r"(small_base));
                suffix_destination=small_base+small_offset;
            }
            /* Actual full-pointer argument already occupies R0 on this
             * incoming edge; it is consumed only by the shared suffix call. */
            asm("" : : "r"(suffix_destination));
            goto draw_short_suffix;
        }
        if(value<=99) {
            {
                register u8 *number_out asm("r0")=number_text;
                /* Original SP8 buffer argument is ready before the
                 * independent saved-value copy into R1. */
                asm("" : : "r"(number_out));
                WritePaddedHalfwordDecimalText(number_out,value,2);
            }
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,10,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            ProcessNativeEncodedText(*prefix_context_slot+prefix_offset,origin,number_text,0,prefix_mode);
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,12,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            suffix_destination=*prefix_context_slot+prefix_offset;
            /* Actual full-pointer argument already occupies R0 on this
             * incoming edge; it is consumed only by the shared suffix call. */
            asm("" : : "r"(suffix_destination));
    draw_short_suffix:
            {
                register const u8 **suffix_captions asm("r3")=gNativeCaptionResources;
                /* Actual ROM table address is ready in R3 before its
                 * entry13 load; R3 becomes the zero helper argument later. */
                asm("" : : "r"(suffix_captions));
                ProcessNativeEncodedText(suffix_destination,origin,suffix_captions[13],0,prefix_mode);
            }
        } else {
            {
                register u8 *number_out asm("r0")=number_text;
                /* Original SP8 buffer argument is ready before the
                 * independent saved-value copy into R1. */
                asm("" : : "r"(number_out));
                WritePaddedHalfwordDecimalText(number_out,definition_value_snapshot,3);
            }
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,9,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            ProcessNativeEncodedText(*prefix_context_slot+prefix_offset,origin,number_text,0,prefix_mode);
            origin=NativeTextOrigin(5,(u32)gNativePanelVram,12,0);
            /* Actual full-word result enters R1 before the fresh context setup. */
            asm("" : "+r"(origin));
            ProcessNativeEncodedText(*prefix_context_slot+prefix_offset,origin,gNativeCaptionResources[13],0,prefix_mode);
        }
    }
    origin=NativeTextOrigin(5,(u32)gNativePanelVram,20,0);
    /* Actual full-word result enters R1 before the fresh context setup. */
    asm("" : "+r"(origin));
    ProcessNativeEncodedText(gNativeDetailContext+0xc4c,origin,gNativeCaptionResources[40],0,1);
    digits=1;
    if(snapshot>9) digits=2;
    {
        register u8 *number_out asm("r0")=number_text;
        /* Original heading buffer argument precedes the independent
         * SP40 snapshot reload into the value argument. */
        asm("" : : "r"(number_out));
        WritePaddedHalfwordDecimalText(number_out,snapshot,digits);
    }
    SetNativePanelStyle(5,23,2,2,2,(style_mask&1)?11:12);
    origin=NativeTextOrigin(5,(u32)gNativePanelVram,22,0);
    /* Actual full-word result enters R1 before the fresh context setup. */
    asm("" : "+r"(origin));
    ProcessNativeEncodedText(gNativeDetailContext+0xc4c,origin,number_text,0,1);
    origin=NativeTextOrigin(5,(u32)gNativePanelVram,0,2);
    /* Actual full-word result enters R1 before the fresh context setup. */
    asm("" : "+r"(origin));
    ProcessNativeEncodedText(gNativeDetailContext+0xc4c,origin,gNativeCaptionResources[14],0,1);
    if(!(style_mask&0x8000)) {
        row_label=20;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21b6],2);
        SetNativePanelStyle(5,5,6,2,2,(style_mask&0x2)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,1,4,row_label,number_text);
        row_label=21;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21b8],2);
        SetNativePanelStyle(5,11,6,2,2,(style_mask&0x4)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,7,4,row_label,number_text);
        row_label=22;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21ba],2);
        SetNativePanelStyle(5,17,6,2,2,(style_mask&0x8)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,13,4,row_label,number_text);
        row_label=23;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21bc],2);
        SetNativePanelStyle(5,23,6,2,2,(style_mask&0x10)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,19,4,row_label,number_text);
        row_label=24;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21be],2);
        SetNativePanelStyle(5,5,8,2,2,(style_mask&0x20)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,1,6,row_label,number_text);
        row_label=25;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c0],2);
        SetNativePanelStyle(5,11,8,2,2,(style_mask&0x40)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,7,6,row_label,number_text);
        row_label=26;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c2],2);
        SetNativePanelStyle(5,17,8,2,2,(style_mask&0x80)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,13,6,row_label,number_text);
        row_label=27;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c4],2);
        SetNativePanelStyle(5,23,8,2,2,(style_mask&0x100)?11:12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,19,6,row_label,number_text);
    } else {
        row_label=20;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21b7],2);
        SetNativePanelStyle(5,5,6,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,1,4,row_label,number_text);
        row_label=21;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21b9],2);
        SetNativePanelStyle(5,11,6,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,7,4,row_label,number_text);
        row_label=22;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21bb],2);
        SetNativePanelStyle(5,17,6,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,13,4,row_label,number_text);
        row_label=23;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21bd],2);
        SetNativePanelStyle(5,23,6,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,19,4,row_label,number_text);
        row_label=24;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21bf],2);
        SetNativePanelStyle(5,5,8,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,1,6,row_label,number_text);
        row_label=25;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c1],2);
        SetNativePanelStyle(5,11,8,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,7,6,row_label,number_text);
        row_label=26;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c3],2);
        SetNativePanelStyle(5,17,8,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,13,6,row_label,number_text);
        row_label=27;
        /* Original label definition survives the formatter and style call. */
        asm("" : "+r"(row_label));
        WritePaddedHalfwordDecimalText(number_text,gNativeEwram[0x21c5],2);
        SetNativePanelStyle(5,23,8,2,2,12);
        DrawNativeLabeledRow(5,(u32)gNativePanelVram,19,6,row_label,number_text);
    }
}
