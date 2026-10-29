#!/usr/bin/env python3
"""Verify an existing output image without compiling or creating another ROM."""
import argparse
import hashlib
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]

def verify(path, expected_sha256, expected_size):
    digest = hashlib.sha256()
    size = 0
    with Path(path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(chunk)
            size += len(chunk)
    actual = digest.hexdigest()
    if size != expected_size or actual != expected_sha256:
        raise ValueError('Final on-disk ROM size/SHA-256 mismatch')
    return {'verified': True, 'bytes': size, 'sha256': actual}

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--rom', required=True, type=Path)
    a = p.parse_args()
    config = json.loads((ROOT/'config/completed-build.json').read_text())
    print(json.dumps(verify(a.rom, config['sha256'], config['size'])))
if __name__ == '__main__':
    main()
