typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyBytesFn)(u8 *, const u8 *, u32);
extern CopyBytesFn const gNativeTextCopy;
extern const u8 gReplacementText[];
extern u8 IsTextReplacement(u32) asm("RetailCall_08013BEC");
extern u32 PrepareTextReplacement(u32) asm("RetailCall_08013C20");
u16 CopyNativeTextTokens(u8 *, const u8 *) asm("Remaining38_0001407C");
u16 CopyNativeTextTokens(u8 *destination, const u8 *source)
{
    u16 written = 0;
    u32 byte;
    while ((byte = *source) != 0) {
        if (byte == 64) {
            *destination = (u8)byte;
            source++;
            destination++;
            switch (*source) {
            case 37:
                if (IsTextReplacement(source[1])) {
                    u16 length = (u16)PrepareTextReplacement(source[1]);
                    destination--;
                    if (length) {
                        CopyBytesFn const *copy_slot = &gNativeTextCopy;
                        const u8 *replacement = gReplacementText;
                        (*copy_slot)(destination, replacement, length);
                    }
                    destination += length;
                    source += 2;
                    written = (u16)(written + length);
                    break;
                }
                /* A false predicate shares the original two-byte command. */
            case 33: case 60: case 62: case 103:
            case 108: case 114: case 116:
                *destination = *source;
                source++;
                destination++;
                *destination = *source;
                source++;
                destination++;
                written = (u16)(written + 3);
                break;
            case 102:
                *destination = *source;
                source++;
                destination++;
                *destination = *source;
                source++;
                destination++;
                *destination = *source;
                source++;
                destination++;
                written = (u16)(written + 4);
                break;
            case 83: {
                int piece = 0;
copy_next_segment:
                    byte = *source;
                    piece++;
                    while (byte != 0) {
                        *destination = (u8)byte;
                        source++;
                        destination++;
                        written = (u16)(written + 1);
                        byte = *source;
                    }
                    *destination = *source;
                    source++;
                    destination++;
                    written = (u16)(written + 1);
                if (piece <= 1)
                    goto copy_next_segment;
                break;
            }
            case 97: case 98: case 99: case 107: case 110:
            case 112: case 115: case 117: case 119: case 120: case 121:
                goto copy_one_byte;
            default:
                /* The prefix and source advance already occurred. */
                break;
            }
        } else {
            *destination = (u8)byte;
            source++;
            destination++;
copy_one_byte:
            *destination = *source;
            source++;
            destination++;
            written = (u16)(written + 2);
        }
    }
    *destination = 0;
    written = (u16)(written + 1);
    return written;
}
__asm__(".global gNativeTextCopy\n.set gNativeTextCopy,0x0836D4BC");
__asm__(".global gReplacementText\n.set gReplacementText,0x020078B0");
__asm__(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
__asm__(".global RetailCall_08013BEC\n.thumb_set RetailCall_08013BEC,0x08013BED");
__asm__(".global RetailCall_08013C20\n.thumb_set RetailCall_08013C20,0x08013C21");
