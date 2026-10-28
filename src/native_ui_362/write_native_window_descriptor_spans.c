typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct NativeWindowTileContext {
    u16 *primary,*secondary;
    u8 unknown08[12];
    u16 style;
    u8 stride,palette,unknown18[5],first_descriptor,second_descriptor;
};
extern u32 ReadWindowDescriptorSpan(u8) asm("RetailCall_080185B8");
void WriteNativeWindowDescriptorSpans(struct NativeWindowTileContext*,u16,u8) asm("Remaining38_00016E88");
void WriteNativeWindowDescriptorSpans(struct NativeWindowTileContext *window,u16 row,u8 width)
{
    u32 used=0;
    if(window->style&0x1420) return;
    if(window->first_descriptor) {
        s32 start,end;
        register s32 position asm("r3");
        used=ReadWindowDescriptorSpan(window->first_descriptor&127);
        if(window->first_descriptor&128) {
            u8 extra=ReadWindowDescriptorSpan(window->second_descriptor&127);
            s32 available=width-extra;
            start=(u8)(available-used-2);
            end=(u8)(available-2);
            used+=extra;
        } else {
            start=1;
            end=(u8)(used+1);
        }
        /* Preserve the ordinary projection before its actual count carrier. */
        position=start;
        asm("" : "+r"(position));
        if((s32)width>(s32)(used+1)) {
            u16 *base;
            u32 tile_work;
            u16 tile;
            if(window->style&0x800) {
                base=window->secondary+row;
                tile_work=(window->palette<<12)+74;
            } else {
                u32 row_bytes=(u32)row*2;
                u32 address=(u32)window->primary;
                address+=row_bytes;
                address+=(u32)window->stride*2;
                base=(u16*)address;
                tile_work=(window->palette<<12)+62;
            }
            tile=tile_work;
            if(position<end) {
                u32 destination_address=(u32)position*2;
                u16 *destination;
                destination_address+=(u32)base;
                destination=(u16*)destination_address;
                position=end-position;
                do {
                    u16 old_tile=tile;
                    tile=old_tile+1;
                    *destination=old_tile;
                    destination++;
                    position--;
                } while(position);
            }
        }
    }
    if(window->second_descriptor) {
        u32 span=ReadWindowDescriptorSpan(window->second_descriptor&127);
        s32 start,end;
        register s32 position asm("r3");
        if(window->second_descriptor&128) {
            used=0;
            start=1;
            end=(u8)(span+1);
        } else {
            start=(u8)(width-span-1);
            end=(u8)(width-1);
        }
        /* Preserve the ordinary projection before its actual count carrier. */
        position=start;
        asm("" : "+r"(position));
        if((s32)width>(s32)(used+span+1)) {
            u16 *base;
            u32 tile_work;
            u16 tile;
            if(window->style&0x800) {
                base=window->secondary+row;
                tile_work=(window->palette<<12)+74;
            } else {
                u32 row_bytes=(u32)row*2;
                u32 address=(u32)window->primary;
                address+=row_bytes;
                address+=(u32)window->stride*2;
                base=(u16*)address;
                tile_work=(window->palette<<12)+68;
            }
            tile=tile_work;
            if(position<end) {
                u32 destination_address=(u32)position*2;
                u16 *destination;
                destination_address+=(u32)base;
                destination=(u16*)destination_address;
                position=end-position;
                do {
                    u16 old_tile=tile;
                    tile=old_tile+1;
                    *destination=old_tile;
                    destination++;
                    position--;
                } while(position);
            }
        }
    }
}
__asm__(".global RetailCall_080185B8\n.thumb_set RetailCall_080185B8,0x080185b9");
