#!/usr/bin/env python3
"""Audit selected source paths and prepare content-preserving source promotion.

This tool never grants acceptance, changes production selection, compiles or pushes.
"""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import subprocess


TRANSIENT = re.compile(
    r"^(?:.*[-_])?(?:batch\d*|refill\d*|import\d*|upstream(?:[-_].*)?|campaign(?:[-_].*)?|"
    r"worker\d+|round\d+|cause\d+|candidate|trial|resume\d*)(?:[-_.].*)?$", re.I)
QUOTED_INCLUDE = re.compile(rb'^\s*#\s*include\s*"([^"\n]+)"', re.M)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def source_path_error(name):
    if not isinstance(name, str) or "\\" in name:
        return "source must be a repository-relative POSIX path"
    p = PurePosixPath(name)
    if p.is_absolute() or ".." in p.parts or any(x.startswith('.') for x in p.parts):
        return "source escapes the repository or uses a hidden directory"
    if len(p.parts) < 3 or p.parts[0] != "src" or p.suffix != ".c":
        return "use src/<subsystem>/<stable-name>.c; use unknown for unproved ownership"
    if any(TRANSIENT.fullmatch(x) for x in (*p.parts[1:-1], p.stem)):
        return "production paths must not encode batches, actors or experiments"
    return None


def within(root, name):
    p = PurePosixPath(name)
    if p.is_absolute() or ".." in p.parts or "\\" in name:
        raise ValueError("unsafe repository-relative path: " + name)
    result = (root / name).resolve()
    if not result.is_relative_to(root):
        raise ValueError("path resolves outside repository: " + name)
    return result


def production_file(root, name):
    result = within(root, name)
    current = root
    for part in PurePosixPath(name).parts:
        current = current / part
        if current.is_symlink():
            raise ValueError("production paths must not traverse symlinks")
    return result


def selected(config):
    return [m for m in config['modules']
            if m.get('enabled', True) and m.get('kind') in ('c', 'mixed')]


def audit(root, manifest, baseline_ref=None):
    raw = within(root, manifest).read_bytes()
    config = json.loads(raw)
    baseline = {}
    if baseline_ref:
        baseline_ref = subprocess.run(
            ['git', '-C', str(root), 'rev-parse', '--verify', '--end-of-options',
             baseline_ref + '^{commit}'], check=True,
            capture_output=True, text=True).stdout.strip()
        old = subprocess.run(['git', '-C', str(root), 'show',
                              baseline_ref + ':' + manifest], check=True,
                             capture_output=True).stdout
        baseline = {m['name']: m for m in selected(json.loads(old))}
    issues, legacy = [], []
    for module in selected(config):
        name = module.get('source', '')
        error = source_path_error(name)
        try:
            path = production_file(root, name)
            if not path.is_file():
                raise ValueError("selected source is missing")
        except (ValueError, OSError) as exc:
            issues.append({'module': module['name'], 'source': name, 'reason': str(exc)})
            continue
        if not error:
            continue
        old = baseline.get(module['name'])
        identity = ('name', 'kind', 'offset', 'size', 'source', 'functions')
        unchanged = old is not None and all(old.get(k) == module.get(k) for k in identity)
        if unchanged:
            blob = subprocess.run(['git', '-C', str(root), 'show',
                                   baseline_ref + ':' + name], capture_output=True)
            unchanged = blob.returncode == 0 and blob.stdout == path.read_bytes()
        row = {'module': module['name'], 'source': name, 'reason': error}
        (legacy if unchanged else issues).append(row)
    return {'schema': 'source-layout-audit-v1', 'manifest': manifest,
            'manifest_sha256': sha(raw), 'selected_modules': len(selected(config)),
            'baseline_ref': baseline_ref, 'issues': issues, 'legacy_unchanged': legacy,
            'ok': not issues, 'limits': 'Layout only; not ABI, byte-match or integration proof.'}


def prepare(root, manifest, module_name, destination):
    error = source_path_error(destination)
    if error:
        raise ValueError(error)
    raw = within(root, manifest).read_bytes()
    modules = selected(json.loads(raw))
    matches = [m for m in modules if m['name'] == module_name]
    if len(matches) != 1:
        raise ValueError("select one existing C/mixed module; no invented identity")
    module = matches[0]
    source = within(root, module['source'])
    target = production_file(root, destination)
    if source == target:
        raise ValueError("source already has the requested path")
    files, closure, visited = {}, [], set()

    def visit(path, output):
        if path in visited:
            return
        visited.add(path)
        data = path.read_bytes()
        if re.search(rb'\b__(?:FILE|BASE_FILE|INCLUDE_LEVEL)__\b|\.(?:incbin|include)\b', data):
            raise ValueError("path-sensitive source needs an explicit manual relocation proof")
        for directive in re.findall(rb'^\s*#\s*include\s+([^\n]+)', data, re.M):
            if not directive.lstrip().startswith((b'"', b'<')):
                raise ValueError("macro-selected includes need manual dependency qualification")
        closure.append({'path': path.relative_to(root).as_posix(), 'sha256': sha(data)})
        if output is not None:
            previous = files.get(output)
            if previous is not None and previous != data:
                raise ValueError("dependency destination collision")
            files[output] = data
        for inc in QUOTED_INCLUDE.findall(data):
            name = inc.decode('utf-8')
            rel = PurePosixPath(name)
            if rel.is_absolute() or '..' in rel.parts or '\\' in name:
                raise ValueError("relative-parent includes need manual relocation")
            local = (path.parent / name).resolve()
            shared = (root / 'include' / name).resolve()
            if local.is_file() and local.is_relative_to(source.parent):
                dest = target.parent / local.relative_to(source.parent)
                visit(local, dest)
            elif shared.is_file() and shared.is_relative_to(root / 'include'):
                # A same-named file next to the promoted source would shadow this include.
                if (target.parent / name).exists():
                    raise ValueError("destination would shadow a shared header")
                visit(shared, None)
            else:
                raise ValueError("unresolved quoted include: " + name)

    visit(source, target)
    for path, data in files.items():
        if not path.resolve().is_relative_to(root):
            raise ValueError("dependency destination escapes repository")
        if path.exists() and path.read_bytes() != data:
            raise ValueError("refusing to overwrite a different destination: " + str(path))
    created = []
    try:
        for path, data in files.items():
            if path.exists():
                continue
            path.parent.mkdir(parents=True, exist_ok=True)
            with path.open('xb') as handle:
                handle.write(data)
            created.append(path)
        if any(p.read_bytes() != data for p, data in files.items()):
            raise ValueError("promoted bytes changed during preparation")
    except Exception:
        for path in reversed(created):
            path.unlink()
        raise
    candidate = dict(module, source=destination)
    return {'schema': 'source-relocation-preparation-v1', 'module': module_name,
            'manifest': manifest, 'manifest_sha256': sha(raw),
            'original_source': module['source'], 'candidate_module': candidate,
            'copied_files': [{'path': p.relative_to(root).as_posix(), 'sha256': sha(data)}
                             for p, data in files.items()],
            'input_closure': closure, 'source_bytes_unchanged': True,
            'status': 'prepared_only', 'production_manifest_changed': False,
            'next': 'Validate final-path compilation/dependencies, rebind selection and proof/index '
                    'together, verify one coherent final image, then publish. Retain old evidence '
                    'until its consumer obligations finish. This is not new recovery credit.'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path.cwd())
    sub = parser.add_subparsers(dest='operation', required=True)
    for name in ('audit', 'prepare'):
        cmd = sub.add_parser(name)
        cmd.add_argument('--manifest', default='config/retail-us.json')
        cmd.add_argument('--report', type=Path)
        if name == 'audit':
            cmd.add_argument('--baseline-ref')
        else:
            cmd.add_argument('--module', required=True)
            cmd.add_argument('--destination', required=True)
    args = parser.parse_args()
    try:
        root = args.root.resolve(strict=True)
        if args.report and args.report.exists():
            raise ValueError('report already exists; do not replace frozen evidence')
        result = (audit(root, args.manifest, args.baseline_ref) if args.operation == 'audit'
                  else prepare(root, args.manifest, args.module, args.destination))
        if args.report:
            args.report.parent.mkdir(parents=True, exist_ok=True)
            with args.report.open('x') as handle:
                handle.write(json.dumps(result, indent=2) + '\n')
        if args.operation == 'audit':
            print(json.dumps({k: v for k, v in result.items()
                              if k not in ('issues', 'legacy_unchanged')}
                             | {'issues': len(result['issues']),
                                'legacy_unchanged': len(result['legacy_unchanged']),
                                'first_issues': result['issues'][:5]}, indent=2))
            return int(not result['ok'])
        print(json.dumps(result, indent=2))
        return 0
    except (ValueError, OSError, KeyError, subprocess.CalledProcessError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
