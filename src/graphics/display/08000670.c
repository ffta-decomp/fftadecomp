struct DisplayDefaults {
    unsigned char reserved[7];
    unsigned char field_07 : 8;
    unsigned short field_08 : 16;
    unsigned char field_0a : 8;
    unsigned char field_0b : 8;
};
extern volatile struct DisplayDefaults gDisplayDefaults;

/* Field meanings remain unknown; retain the observed full-width bitfields. */
void InitDisplayDefaults(void)
{
    gDisplayDefaults.field_07 = 2;
    gDisplayDefaults.field_08 = 240;
    gDisplayDefaults.field_0a = 15;
    gDisplayDefaults.field_0b = 4;
}
