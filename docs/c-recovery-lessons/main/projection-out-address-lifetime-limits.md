# Projection OUT addresses: keep layout and lifetime as separate hypotheses

- Native `DC014` has three halfword OUT subranges at SP8/10/12. The Y and depth addresses are defined before signed coordinate loads, and the Y pointer alone remains live across projection.
- Passing three scalars directly as call arguments kept the native slots but defined the pointers late, reducing the saved-register frame. It fit68 bytes with43 same-offset bytes.
- Early initialized pointer locals restored the native32-byte frame but changed standalone scalar placement to Y/depth/X. A three-halfword scratch struct restored relative offsets0/2/4 but retained its base and another register, producing72 bytes instead of68.
- Thus adjacent OUT fields neither prove an original C aggregate nor make scalar declaration permutations useful. The Klonoa stack-layout reference and the project's independent-OUT successes identify questions, not a universal matching recipe. Preserve failed transfers as well as successes.
- The actual signed input fields and signed16 subtraction after unsigned output loads were unchanged. No helper, volatile, padding member, instruction island or compiler option was altered.
- Three causes consumed4.330331s in local comparisons and466.954392s from qualification to freeze. The best43/68 result stayed below70%; the entire exact ASM remains selected, with zero new C or runtime credit. Do not reopen the terminal budget from this note.
- Frozen terminal decision SHA-256:`9dcc4b874bae9fe13ab89e7b986e64bb8339e1ad90c999846842dc3370738cea`.
