#include "interfaces.h"

void NormalizeBattleUnitCounters(void *unit)
{
    /* Each condition is re-evaluated in order after the preceding setter. */
    if (!(u8)ResolutionCheck_0C8280(unit)) ResolutionClear_0CE418(unit, 0);
    if (!(u8)ResolutionCheck_0CDA94(unit)) ResolutionClear_0CE420(unit, 0);
    if (!(u8)ResolutionCheck_0CDAAC(unit)) ResolutionClear_0CE428(unit, 0);
    if (!(u8)ResolutionCheck_0CDAC4(unit)) ResolutionClear_0CE430(unit, 0);
    if (!(u8)ResolutionCheck_0CDADC(unit)) ResolutionClear_0CE438(unit, 0);
    if (!(u8)ResolutionCheck_0CDAF4(unit)) ResolutionClear_0CE440(unit, 0);
    if (!(u8)ResolutionCheck_0CDB0C(unit)) ResolutionClear_0CE448(unit, 0);
    if (!(u8)ResolutionCheck_0CDB24(unit)) ResolutionClear_0CE450(unit, 0);
    if (!(u8)ResolutionCheck_0CDB3C(unit)) ResolutionClear_0CE458(unit, 0);
    if (!(u8)ResolutionCheck_0CDB54(unit)) ResolutionClear_0CE460(unit, 0);
    if (!(u8)ResolutionCheck_0CDB6C(unit)) ResolutionClear_0CE468(unit, 0);
    if (!(u8)ResolutionCheck_0CDB84(unit)) ResolutionClear_0CE470(unit, 0);
    if (!(u8)ResolutionCheck_0CDB9C(unit)) ResolutionClear_0CE478(unit, 0);
    if (!(u8)ResolutionCheck_0CDBB4(unit)) ResolutionClear_0CE480(unit, 0);
    if (!(u8)ResolutionCheck_0CDBCC(unit) && !(u8)ResolutionCheck_0CDA7C(unit) && !(u8)ResolutionCheck_0CDCA4(unit))
    ResolutionClear_0CE488(unit, 0);
}
