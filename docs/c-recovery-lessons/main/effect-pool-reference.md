> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Effect 91: keep scan and callback-visible unit effects separate

`EffectCallback_00133758`, entry `0x08133759`, has a 154-byte original envelope.
A fixed-O2 readable reconstruction fits 152 bytes and passes two frozen starter
cases plus eight newly authored source-derived cases. Whole-function matching
is still open. The new cases and their one instruction-literal mutant are
implementer evidence, pending independent peer acceptance.

## Observed contract

Context flags at byte38 reject bit0x10 before any helper. The low byte of the
unit eligibility query gates the rest. Reload context+4 after that query, then
clear bit0x40 in the unit halfword at byte40 before scanning. The runtime pool
contains 24 four-byte rows at RAM base+0x3c3c. Compare each row's logical low
nibble with the unit's full byte at260; a byte above15 does not match. The first
match clears exactly four bytes through the existing runtime function pointer.
Only then inspect the current unit byte259. If nonzero, read progression13;
low byte one skips decrement. Otherwise reload context+4 and the byte, then
perform the byte decrement. A helper may retarget the context or turn the byte
zero, producing a wrapped decrement to255. No rollback or invented guard is
permitted.

Packed-field extraction is appropriate here because the ASM explicitly shifts
out a logical nibble, rather than consuming a raw masked-bit predicate. The
ordinary u16 field RMW and real helper boundaries preserve observed unit reloads.
This does not establish a global rule to add bitfields or remove volatile.

## Matching diagnosis and retained failures

Moving the runtime definition after the unit RMW follows the original lifetime;
a signed loop ordinal reproduces the BLE bound. A modern offsetof builtin was
unsupported and repaired with the existing constant-address layout assertion;
the guard was retained. Raw byte-offset calculation before comparison and typed
row indexing emitted identical candidates. No execution was repeated for that
identity.

An unchanged-source dump shows `.loop` reducing destination giv insn117 into
incremented register103 while the scan cursor is a separate induction variable.
The emitted candidate thus maintains two pointers instead of retaining the
original scaled ordinal. Moving the matched continuation outside the lexical
scan changes the result but grows to160 bytes, exceeding154, and was rejected
before execution. It is a failed source-boundary hypothesis, not a proven fix.
Do not fabricate volatile reads, change flags, or keep equivalent permutations.

## Evidence and limits

Two original direct/root starter cases reuse frozen retail outputs and the
corrected SUPPORT14 ABI adapter. Eight additional cases compare whole context,
two units and all96 pool bytes, with independent expected helper order. They
cover first/last row, a high-nibble row, counter zero, low-byte flag semantics,
pre-gate rejection and post-helper retarget/wrap. The IWRAM clear target is
controlled in those cases; its destination and size are asserted, not its
implementation recovered again. A real candidate literal mutation from0xffbf
to0xffdf is rejected by the unit-memory oracle. This is not natural gameplay or
hardware coverage.

Best candidate SHA-256:
`33ac50ba906274fdd4a63c1b267a593e946128f6c0b377fe363f8145164b6be6`.
There is no new semantic, whole exact or integrated credit. Source/headers,
native reports, custom oracles and failure history remain frozen separately.
Next transfer to effect92 must first establish its own fields and scan boundary;
neighboring addresses do not establish identical contracts.
