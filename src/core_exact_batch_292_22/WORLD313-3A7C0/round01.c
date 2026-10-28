typedef unsigned char u8;
typedef unsigned int u32;
/* Actual neighbor-category dependency: byte count wraps independently of the
 * signed scan ordinal. Nonpositive lengths leave the input untouched. */
u32 CoreRegion_0003A7C0(u8 category,const u8 *values,int length)
{
 u8 count=0;
 int i;
 for(i=0;i<length;++i) {
  if(category==values[i]) ++count;
 }
 return count;
}
