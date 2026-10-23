> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# GBA ASM-to-C resource collection

The supplied collection contains **47 resource entries and 23 distinct GitHub repositories**. All 23 have local reference checkouts: 19 newly cloned, four preserved at their existing revisions. Duplicate links keep their original R01-R47 identities. Full revisions, notice-file locations and provenance are in the [docs/gba-asm-to-c-resources.json](gba-asm-to-c-resources.json).

The supplied P0/P1/P2 labels rank reference reading, **not** implementation task priority. Current AGENTS.md, the local assignment, fixed O2, autonomous claims and immediate per-function gates remain authoritative. This collection does not install tools, build reference games, change production dependencies or prove a speedup.

## Start from the question

| Need | Read first |
| --- | --- |
| Mode, PC, signedness, BIOS or instruction meaning | [ARMv4T/Thumb lookup](gba-asm-to-c-idioms.md), then R01-R07 |
| One complete method and its minimum context | [Adapted recovery workflow](gba-asm-to-c-workflow.md) |
| Source-family objects and callback/script state | [pokeemerald study](pokeemerald-reconstruction-reference.md) |
| First register/allocation/reload divergence | [EDS study](eds-matching-reference.md), existing RTL artifacts |
| Proven source-shape alternatives and counterexamples | [FFTA O2 lookup](o2-reconstruction-quick-reference.md), Klonoa learnings |
| An optional draft or a measured repeated tool cost | R26-R34; inspect capabilities before adoption |

Open one relevant reference and return to the current method. Do not make reading all 47 resources, installing Ghidra or rescanning the ROM a new gate.

## Indexed resources

### 01 ISA / hardware

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R01 | P0 | [ARM7TDMI Technical Reference Manual (ARM DDI 0210C)](https://documentation-service.arm.com/static/5f4786a179ff4c392c0ff819) | Official ARM7TDMI instruction, register, exception and timing reference. |
| R02 | P0 | [GBATEK (GBA only)](https://rust-console.github.io/gbatek-gbaonly/) | GBA memory, CPU, BIOS and device reference; filter out later-CPU features. |
| R03 | P0 | [Tonc: ARM Assembly](https://gbadev.net/tonc/asm.html) | ARM/Thumb assembly, calling patterns and compiler-output examples. |
| R04 | P0 | [Tonc: BIOS Calls](https://gbadev.net/tonc/swi.html) | GBA BIOS service numbers, arguments and ARM-versus-Thumb encoding. |
| R05 | P0 | [Tonc: GBA Hardware](https://gbadev.net/tonc/hardware.html) | Memory regions, bus widths and execution-location context. |
| R06 | P1 | [Tonc: Hardware Interrupts](https://gbadev.net/tonc/interrupts.html) | IRQ entry, IWRAM and BIOS interrupt conventions. |
| R07 | P1 | [GBA BIOS Reference (clean-room)](https://retrointernals.github.io/gba-bios-reference/) | Independent BIOS semantic research; cross-check specific service claims. |
| R08 | P1 | [GBAdev documentation library](https://gbadev.org/docs.php) | Community index of CPU manuals and historical development documents. |
| R09 | P1 | [GBA CPU documentation](https://github.com/gbadev-org/gbadoc/blob/main/content/cpu.md) | Community CPU and pipeline documentation; inspect the pinned source. |
| R10 | P1 | [GBAdev curated resources](https://gbadev.net/resources) | GBA developer resource directory for targeted discovery. |

### 02 C SDK / headers

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R11 | P0 | [devkitPro/libgba](https://github.com/devkitPro/libgba) | Hardware and BIOS header reference; not a replacement SDK for matching. |
| R12 | P0 | [devkitPro/libtonc](https://github.com/devkitPro/libtonc) | GBA types, memory map, BIOS and object-attribute reference headers. |
| R13 | P1 | [libtonc API topics](https://gbadev.net/libtonc/topics.htm) | libtonc API lookup for BIOS, fixed point, DMA and OAM. |
| R14 | P1 | [devkitPro/gba-examples](https://github.com/devkitPro/gba-examples) | Modern libgba examples; compare concepts, not historical code generation. |
| R15 | P1 | [agbabi](https://github.com/felixjones/agbabi) | Modern arithmetic/memory/ABI helper research; preserve the actual target ABI. |
| R16 | P1 | [gba-toolchain](https://github.com/felixjones/gba-toolchain) | Modern CMake GBA build reference; not our historical matching pipeline. |
| R17 | P2 | [Historical GBA SDK overview](https://www.retroreversing.com/game-boy-advance-sdk) | Historical SDK/compiler background only, without proprietary SDK copies. |
| R18 | P2 | [libgba include/gba.h](https://github.com/devkitPro/libgba/blob/master/include/gba.h) | libgba umbrella header and module navigation. |
| R19 | P1 | [libgba include/gba_base.h](https://github.com/devkitPro/libgba/blob/master/include/gba_base.h) | GBA memory-region and low-level interface macros. |

### 03 Compiler / matching

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R20 | P0 | [pret/agbcc](https://github.com/pret/agbcc) | Historical ARM/Thumb compiler source; retain the existing pinned normal build. |
| R21 | P0 | [pokeemerald Makefile](https://github.com/pret/pokeemerald/blob/master/Makefile) | Concrete external build context; do not import flags into FFTA. |
| R22 | P0 | [Klonoa compiler boundaries and learnings](https://github.com/Dream-Atelier/kl-eod-decomp) | Compiler-boundary and source-shape research with project-specific evidence. |
| R23 | P1 | [Yu-Gi-Oh! EDS full matching decomp](https://github.com/CosmicScribe64/eds-decomp) | Whole-match source, discrepancy catalog and allocation/reload tooling study. |
| R24 | P1 | [Tonc development environment](https://gbadev.net/tonc/setup.html) | C/assembly/object/linking development overview. |
| R25 | P1 | [agbcc installer](https://github.com/pret/agbcc/blob/master/install.sh) | Compiler installation and library-output layout reference; do not run setup here. |

### 04 Analysis tools

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R26 | P0 | [Ghidra ARM/Thumb](https://github.com/NationalSecurityAgency/ghidra) | ARM disassembly, cross-reference, type and decompiler source reference. |
| R27 | P0 | [GBA Ghidra Loader](https://github.com/pudii/gba-ghidra-loader) | GBA header, memory-map and entry configuration for Ghidra; optional analyzer. |
| R28 | P0 | [Luvdis](https://github.com/aarant/luvdis) | GBA disassembly/reassembly research; function boundaries still need evidence. |
| R29 | P0 | [m2c](https://github.com/matt-kempster/m2c) | Context-driven candidate C with GBA/APCS support; output is an unverified draft. |
| R30 | P0 | [asm-differ](https://github.com/simonlindholm/asm-differ) | Assembly difference display and local matching feedback. |
| R31 | P0 | [objdiff](https://github.com/encounter/objdiff) | Object/function/data comparison and matching-report reference. |
| R32 | P1 | [decomp-permuter-agbcc](https://github.com/WhenGryphonsFly/decomp-permuter-agbcc) | ARMv4T/agbcc source permutation research; no unbounded search authorization. |
| R33 | P1 | [decomp.me](https://www.decomp.me/faq) | Public scratch/compilation service reference; no private upload authorization. |
| R34 | P1 | [Mizuchi](https://github.com/macabeus/mizuchi) | Automated compiler/diff orchestration research; not a replacement task runtime. |
| R35 | P1 | [mGBA](https://mgba.io/) | Emulator execution/debugging reference; reuse the installed executor. |
| R36 | P1 | [mGBA command line debugger reference](https://github.com/mgba-emu/mgba/blob/master/doc/mgba.6) | Command-line debugger documentation within the preserved mGBA checkout. |
| R37 | P2 | [gvasm](https://github.com/velipso/gvasm) | GBA assembler reference; its disassembler is explicitly experimental. |
| R38 | P1 | [Decompedia GBA](https://decomp.wiki/platforms/game-boy-advance) | Community matching-decompilation navigation. |

### 05 Decomp projects / corpora

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R39 | P0 | [pret/pokeemerald](https://github.com/pret/pokeemerald) | Mature shared-source, object, callback and build-layout reference corpus. |
| R40 | P0 | [Klonoa: Empire of Dreams](https://github.com/Dream-Atelier/kl-eod-decomp) | Source-shape and compiler-specific learning corpus; distinguish facts from policy. |
| R41 | P0 | [Yu-Gi-Oh! The Eternal Duelist Soul](https://github.com/CosmicScribe64/eds-decomp) | Matching source/ASM corpus; upstream also permits documented FAKEMATCH forms. |
| R42 | P1 | [Decomp Academy](https://decomp-academy.dev/) | Interactive matching exercises for optional focused training. |
| R43 | P2 | [SLaDe-AGBCC](https://github.com/JRickey/SLaDe-AGBCC) | Neural matching-decompilation research; no model training or quality claim. |

### 06 FFTA-specific

| ID | Reading priority | Reference | Intended use |
| --- | --- | --- | --- |
| R44 | P0 | [FFTA Decode public research](https://github.com/kttalley/ffta-decode-public) | Behavioral FFTA research, explicitly not a byte-matching GBA rebuild. |
| R45 | P1 | [FFTA static recomp ecosystem](https://github.com/mstan/gbarecomp) | Host-native static recompilation research, not original-style GBA C recovery. |
| R46 | P1 | [FFTA project index (unbaked)](https://unbaked.games/games/final-fantasy-tactics-advance/) | FFTA project discovery index; check each project's actual target and evidence. |
| R47 | P1 | [GBA BIOS asset compression](https://gbadev.net/tonc/swi.html) | BIOS decompression reference for distinguishing assets from executable code. |

## Local GitHub corpus

Existing checkout revisions were observed and preserved; this table does not change the active toolchain. New checkouts use shallow history without recursively fetching submodules or Git LFS payloads. Ghidra uses a sparse ARM-processor/decompiler working tree; it is source reference, not an installed application. Reproduce that selection after submodule initialization if desired; no full source build is required.

| Repository | Local reference | Revision prefix | Collection action |
| --- | --- | --- | --- |
| [aarant/luvdis](https://github.com/aarant/luvdis) | [vendor/luvdis](https://github.com/aarant/luvdis/tree/ec3a4e3ee3afe3e9b4a9c7ae8fffc65e1ea2096c) | `ec3a4e3ee3af` | New shallow clone |
| [CosmicScribe64/eds-decomp](https://github.com/CosmicScribe64/eds-decomp) | [vendor/eds-decomp](https://github.com/CosmicScribe64/eds-decomp/tree/857002acd7a2e3ce98afb2992fe9761144308c9a) | `857002acd7a2` | Preserved |
| [devkitPro/gba-examples](https://github.com/devkitPro/gba-examples) | [vendor/gba-examples](https://github.com/devkitPro/gba-examples/tree/435346171d820c0a6eb021b90e58032d88d30244) | `435346171d82` | New shallow clone |
| [devkitPro/libgba](https://github.com/devkitPro/libgba) | [vendor/libgba](https://github.com/devkitPro/libgba/tree/f0e44ce9ed57e1d21f148443223408fddeacfb9d) | `f0e44ce9ed57` | New shallow clone |
| [devkitPro/libtonc](https://github.com/devkitPro/libtonc) | [vendor/libtonc](https://github.com/devkitPro/libtonc/tree/ccc03fa321e56f51aed5e2ee1d6e3df3d1cbc803) | `ccc03fa321e5` | New shallow clone |
| [Dream-Atelier/kl-eod-decomp](https://github.com/Dream-Atelier/kl-eod-decomp) | [vendor/kl-eod-decomp](https://github.com/Dream-Atelier/kl-eod-decomp/tree/45e66dd20f55b637656bc86129b9ba3bd49a01d6) | `45e66dd20f55` | New shallow clone |
| [encounter/objdiff](https://github.com/encounter/objdiff) | [vendor/objdiff](https://github.com/encounter/objdiff/tree/9aeec9cbab1a056ade7dc1f1625aacc41b0f8511) | `9aeec9cbab1a` | New shallow clone |
| [felixjones/agbabi](https://github.com/felixjones/agbabi) | [vendor/agbabi](https://github.com/felixjones/agbabi/tree/19d148710a85b9e87f961071fd2fc5ee2b5136a4) | `19d148710a85` | New shallow clone |
| [felixjones/gba-toolchain](https://github.com/felixjones/gba-toolchain) | [vendor/gba-toolchain](https://github.com/felixjones/gba-toolchain/tree/9d9269536425972ffc93456ab27d73cfba6774d3) | `9d9269536425` | New shallow clone |
| [gbadev-org/gbadoc](https://github.com/gbadev-org/gbadoc) | [vendor/gbadoc](https://github.com/gbadev-org/gbadoc/tree/35a281ae9b03af221e9309b1074658cf2158c196) | `35a281ae9b03` | New shallow clone |
| [JRickey/SLaDe-AGBCC](https://github.com/JRickey/SLaDe-AGBCC) | [vendor/SLaDe-AGBCC](https://github.com/JRickey/SLaDe-AGBCC/tree/af5aebdb03e72b446e1ead508db0bc63b12f46c8) | `af5aebdb03e7` | New shallow clone |
| [kttalley/ffta-decode-public](https://github.com/kttalley/ffta-decode-public) | [vendor/ffta-decode-public](https://github.com/kttalley/ffta-decode-public/tree/d8c2355d953c8844818f53f7e8a93208f4329bd2) | `d8c2355d953c` | New shallow clone |
| [macabeus/mizuchi](https://github.com/macabeus/mizuchi) | [vendor/mizuchi](https://github.com/macabeus/mizuchi/tree/25eaef4214574cc20f376878dbc1b8099e97164e) | `25eaef421457` | New shallow clone |
| [matt-kempster/m2c](https://github.com/matt-kempster/m2c) | [vendor/m2c](https://github.com/matt-kempster/m2c/tree/c632946b8cfbe8fce442b522dba92dfa72f1f317) | `c632946b8cfb` | New shallow clone |
| [mgba-emu/mgba](https://github.com/mgba-emu/mgba) | [vendor/mgba](https://github.com/mgba-emu/mgba/tree/33f18f60fcff5b4f9e8abcf8ac1925a714d5f64a) | `33f18f60fcff` | Preserved |
| [mstan/gbarecomp](https://github.com/mstan/gbarecomp) | [vendor/gbarecomp](https://github.com/mstan/gbarecomp/tree/9266573123fb950dfdee2d19040a2daf5e63e39d) | `9266573123fb` | New shallow clone |
| [NationalSecurityAgency/ghidra](https://github.com/NationalSecurityAgency/ghidra) | [vendor/ghidra](https://github.com/NationalSecurityAgency/ghidra/tree/164003036607e669226647bd0f7bedaf281e56a6) | `164003036607` | New shallow clone |
| [pret/agbcc](https://github.com/pret/agbcc) | [vendor/agbcc](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9) | `da598c1d9184` | Preserved |
| [pret/pokeemerald](https://github.com/pret/pokeemerald) | [vendor/pokeemerald](https://github.com/pret/pokeemerald/tree/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881) | `731ad5bfd6e6` | Preserved |
| [pudii/gba-ghidra-loader](https://github.com/pudii/gba-ghidra-loader) | [vendor/gba-ghidra-loader](https://github.com/pudii/gba-ghidra-loader/tree/9bfb2d1fe891aa78bab7093a328feb3a52318ab7) | `9bfb2d1fe891` | New shallow clone |
| [simonlindholm/asm-differ](https://github.com/simonlindholm/asm-differ) | [vendor/asm-differ](https://github.com/simonlindholm/asm-differ/tree/0dd09af8f8008f1f880327cf0aca3b26d2562ea2) | `0dd09af8f800` | New shallow clone |
| [velipso/gvasm](https://github.com/velipso/gvasm) | [vendor/gvasm](https://github.com/velipso/gvasm/tree/049e786d557b10b0c428121410eef60f1a5b5cfa) | `049e786d557b` | New shallow clone |
| [WhenGryphonsFly/decomp-permuter-agbcc](https://github.com/WhenGryphonsFly/decomp-permuter-agbcc) | [vendor/decomp-permuter-agbcc](https://github.com/WhenGryphonsFly/decomp-permuter-agbcc/tree/1f7ef872b12f54db7678ff00e0346abc015410ae) | `1f7ef872b12f` | New shallow clone |

## Interpretation and adoption limits

- Hardware documents establish platform semantics; names and modern SDK wrappers do not establish FFTA object ownership, original ABI or source form.
- Ghidra/m2c drafts, permuter scores and normalized similarity are hypotheses. Full native identity and the existing semantic/mechanical gates determine actual delivery.
- The collection's general compiler fingerprint matrix does not authorize O0/O1/O2 or compiler-binary searches during current fixed-O2 recovery. External library profiles remain external evidence.
- Documented fixed-register locals and instruction-free empty ASM constraints are allowed with correct readable logic and valid operands. Actual emitted instructions retain mixed accounting.
- Klonoa's two learning documents make conflicting universal claims about barriers being always removable versus never removable. Use the specific source/ASM experiment and our native result; neither absolute becomes FFTA policy.
- FFTA Decode states a functional reimplementation goal. GBARecomp targets host-native recompilation. Both are research references and do not contribute recovered GBA C merely by being cloned.
- Preserve each upstream checkout and its component notices. Some roots do not contain a blanket license; missing a root notice in the catalog is not a permission grant. No upstream implementation/assets are copied into our game sources or ROM.
- The original four supplied documents are preserved externally with their hashes; this English adaptation covers their resource index, idioms, workflow and structured metadata. External links and upstream completion claims are not all independently reproduced.
