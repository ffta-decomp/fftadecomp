> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# ARMv4T / Thumb-1 recovery lookup

Adapted from the user-supplied GBA ASM-to-C resource pack. These are candidate
interpretations, not reversible one-to-one translations. Pair them with the
[fixed-O2 source lookup](o2-reconstruction-quick-reference.md), original callers,
object ownership and the actual generated span.

## Decode the target before choosing C

- Identify ARM versus Thumb at every entry and indirect transfer. ARM7TDMI uses
  ARMv4T; later instructions such as `CBZ`, `CBNZ` or `BLX` are not valid evidence
  for its instruction stream. Recheck mode, data boundaries and decoder settings.
- ARM instructions occupy four bytes. Thumb-1 instructions normally occupy two;
  a Thumb `BL` occupies two halfwords. Do not split that call when defining spans.
- Normal cartridge addresses start at `0x08000000`; convert mirrors through the
  actual cartridge mapping rather than blindly subtracting that base everywhere.
- A callable address can encode Thumb state in bit zero. Keep the mode separately
  from the aligned instruction address; do not clear arbitrary data bits.
- ARM PC-relative calculations normally observe instruction address plus eight;
  Thumb calculations observe plus four, with alignment for literal loads.
  Literal pools and jump tables are data, not extra executable instructions.

See [Tonc assembly](https://gbadev.net/tonc/asm.html) and the
[GBATEK CPU reference](https://rust-console.github.io/gbatek-gbaonly/).
The latter also contains later-CPU material; select the ARM7TDMI/ARMv4T rules.

## Operation to source questions

| Observed operation | Candidate meaning | Check before selecting a source form |
| --- | --- | --- |
| Byte or halfword load, signed or unsigned | Physical field/array read | Storage width differs from arithmetic working type and call-boundary type; identify extensions and actual consumers |
| Byte/halfword/word store | Truncating write or object assignment | Preserve physical write width, order and ownership; ordinary RAM, callback-visible RAM and MMIO have different contracts |
| `ADD` / `SUB` | Arithmetic, pointer advance, record addressing | Recover element stride, wraparound and separate base/offset lifetimes |
| `LSL`, `LSR`, `ASR` | Scaling, extraction, packing or signed arithmetic | Recover the operand type and intermediate truncation; signed division by a power of two can require bias rather than a bare arithmetic shift |
| ARM shifted-register operand | Combined arithmetic or address calculation | This is not a Thumb-1 three-operand shifted form; retain original mode |
| `NEG` or ARM reverse subtract from zero | Negation | Track width and flags; do not infer a unique signed C expression |
| `AND`, `ORR`, `EOR`, `BIC` | Raw mask, logical field or packed update | A masked byte and a normalized bitfield are different values; check preserved bits and physical access |
| `TST` or AND followed by zero comparison | Bit predicate | Distinguish branch-only consumption from a materialized numeric result |
| `CMP` with `GT/LE/GE/LT` | Signed relational branch | Recover both promoted operands; a sign branch does not establish the storage type by itself |
| `CMP` with `HI/LS/HS/LO` (`CS/CC` aliases) | Unsigned relational branch | Recover selector width, wraparound and actual target/fallthrough edges |
| Multiply / multiply-accumulate | Product or product plus accumulator | Check whether the instruction exists in the current mode, operand roles and overflow width |
| ARM `UMULL` / `SMULL` | Wide unsigned/signed product | Preserve both halves and signedness; Thumb can instead call a helper |
| PC-relative literal load | Constant, linked object, callable or table base | Resolve relocation/identity and distinguish symbol references from integer-address constants |
| `LDM` / `STM` | Block copy, aggregate or explicit source assembly | Establish complete accesses and ABI; this is not automatically a C struct copy |
| Register save/restore and stack adjustment | Frame, preserved values and stack arguments | Frame size alone does not reveal local count; shared tails and internal entries can share a frame |
| Direct `BL` | Ordinary call, ABI helper or internal convention | Check callers, stack arguments, return width, side effects and callee-preserved state |
| `BX` through LR or another register | Return, indirect call/branch or mode change | Follow the target and bit zero; an indirect branch is not automatically a standard function call |
| `POP {pc}` | Possible return in the current mode | On ARMv4T it is not a replacement for interworking through `BX`; preserve the observed return sequence |
| `SWI` | BIOS request | The GBA BIOS convention uses the service number directly in Thumb, shifted by sixteen in ARM; recover service-specific arguments/results and clobbers |
| Division/remainder helper call | Signed/unsigned quotient or remainder | Identify the helper and result registers; `/` versus `%` is not determined from a helper name alone |
| Access in the IO address range | Hardware register operation | Resolve width and effects using hardware documentation; a modern SDK wrapper is not evidence of the original access sequence |

The BIOS calling convention is described in
[Tonc BIOS calls](https://gbadev.net/tonc/swi.html). These are platform semantics,
not authorization to replace our existing ABI bindings or pinned build flags.

## Minimal recovery context

Reuse the existing method record: revision/hash; complete native range/mode;
original ASM; caller and helper contracts; field offsets/stride; literal and
jump-table ranges; CFG/shared returns; call-visible captures/reloads; fixed
compiler context; previous failed causes and last native diff. Keep uncertain
meaning explicit. Do not create a second inventory or require a full-ROM scan.

Empty ASM constraints and fixed-register locals may document a concrete matching
requirement under current AGENTS.md. Preserve defined operands and readable
logic; actual emitted inline instructions retain mixed accounting. Byte identity
does not establish the original author's exact source text.
