typedef signed short s16;
typedef unsigned int u32;
struct Step {s16 fields[12];};
u32 sub_08007894(const struct Step *state)
{
 u32 result=0;
 if(state->fields[10] <= 0) result=1;
 return result;
}
