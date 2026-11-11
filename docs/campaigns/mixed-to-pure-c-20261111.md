# Pure-C representation refinement — 2026-11-12

Three already verified mixed implementations now use pure C. Complete original
ranges and native binary hashes are unchanged; the change adds no recovered
functions or original bytes.

| Entry | Function | Original B | Previous inline instruction B | Current inline B |
| --- | --- | ---: | ---: | ---: |
| `0x080E87C0` | `AdvanceAuthoredSpecialRecordTargetSequence` | 624 | 2 | 0 |
| `0x080EB740` | `AdvanceAuthoredCurvedOwnerFlagSequence` | 862 | 2 | 0 |
| `0x0810A134` | `RemainingBand43_0010A134` | 368 | 4 | 0 |
| **Total** | **3 representations** | **1,854** | **8** | **0** |

Each replacement passed pinned fixed-O2 complete native/ELF/retail/input checks
and independent mechanical verification. Final published preprocessing and link
inputs equal the captured compiler inputs. Empty truthful constraints and
non-emitting symbol/register declarations remain; no instruction-bearing inline
ASM remains in these three sources. Native module and function target hashes
are unchanged. See [source-bound verification](../../data/campaigns/mixed-to-pure-c-20261111-validation.json).

The preceding complete public build covered all 4,146 modules and produced the
retail-identical image. Its unchanged image was rehashed for this update, and
same-binary evidence was reused instead of recompiling historical trials or
building another ROM. The public source-hash CI independently builds the entire
current selection without a ROM.

The complete selection remains **4,146 modules / 624,304 original B**:
**4,054 pure-C modules / 576,440 B** and **92 mixed modules / 47,864 B**, with
**1,132 instruction-bearing inline ASM B**. Attributed upstream source remains
200,644 B, included once. The original 41-function / 49,506 B commitment remains
17 complete / 16,616 B; this refinement does not reduce its remaining scope.

Source organization by subsystem and the shared ABI-header migration are also
included in this publication; both preserve the verified native outputs.
