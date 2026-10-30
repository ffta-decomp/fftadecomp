#!/usr/bin/env python3
"""Combine frozen positional comparison and displacement-aware ASM diagnosis."""
import argparse
import json
from pathlib import Path
import asmdiff


def summarize(segment, alignment, output):
    return {
        'schema': 'module-build-diagnosis-v1',
        'module': segment['module'],
        'positional': {k: segment.get(k) for k in
                       ('matching_bytes', 'reference_size', 'generated_size', 'fits')},
        'diagnostic_line_counts': alignment['diagnostic_line_counts'],
        'difference_details': alignment.get('difference_details', {}),
        'shifted_run_count': len(alignment['shifted_runs']),
        'largest_shifted_runs': sorted(alignment['shifted_runs'],
                                      key=lambda r: -r['aligned_lines'])[:8],
        'possible_moved_sequence_count': len(alignment['possible_moved_sequences']),
        'report_sha256': alignment['report_sha256'],
        'alignment_json': str(Path(output).resolve() / 'alignment.json'),
        'alignment_text': str(Path(output).resolve() / 'alignment.txt'),
        'diagnostic_only': True,
        'limits': 'Aligned text is not matched bytes or semantic equivalence; '
                  'data/literal decoding and repeated blocks can be ambiguous. '
                  'Original report and exact acceptance are unchanged.'}


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--build-report', required=True, type=Path)
    p.add_argument('--output', required=True, type=Path)
    p.add_argument('--module')
    args = p.parse_args()
    try:
        alignment = asmdiff.run(args.build_report, args.output, args.module)
        # Read the same report again only if its authenticated identity is unchanged.
        if asmdiff.sha(args.build_report) != alignment['report_sha256']:
            raise ValueError('Report changed after alignment; no combined summary')
        _, segment, _, _ = asmdiff.load_segment(args.build_report, args.module)
        result = summarize(segment, alignment, args.output)
        with (args.output / 'diagnosis.json').open('x') as f:
            json.dump(result, f, indent=2)
            f.write('\n')
    except (ValueError, OSError) as e:
        p.exit(2, f'diagnose-module: {e}\n')
    pos = result['positional']
    print(f"{result['module']}: {pos['matching_bytes']}/{pos['reference_size']} positional bytes; "
          f"generated={pos['generated_size']} fits={pos['fits']}")
    print('Aligned diagnostic lines: ' + json.dumps(result['diagnostic_line_counts']))
    print(f"Shifted equal-text runs: {result['shifted_run_count']}; "
          f"possible moved windows: {result['possible_moved_sequence_count']}")
    for r in result['largest_shifted_runs']:
        print(f"  original 0x{r['reference_start']:X} -> generated 0x{r['current_start']:X}, "
              f"delta {r['address_delta']:+d}, {r['aligned_lines']} lines")
    detail = result['difference_details']
    print(f"Register-difference sites: {len(detail.get('register_difference_sites', []))}; call/setup differences: {len(detail.get('call_setup_differences', []))}")
    for site in detail.get('call_setup_differences', [])[:5]:
        a, b = site['reference_call'], site['current_call']
        print(f"  Call 0x{a['address']:X} -> 0x{b['address']:X}: {site['kind']}; same target={site['same_textual_target']}")
    print(result['limits'])
    print('Side-by-side: ' + result['alignment_text'])
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
