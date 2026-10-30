#!/usr/bin/env python3
"""Retrieve one maintained reconstruction topic by symptom; never compiles code."""
import argparse
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
REFERENCES = ROOT / ".agents/skills/ffta-decomp/references"


def rules():
    return json.loads((REFERENCES / "rules.json").read_text())["rules"]


def select(query, rows, limit=2):
    words = query.casefold().split()
    scored = []
    for row in rows:
        keys = [str(key).casefold() for key in (row["id"], *row["keywords"])]
        score = sum(3 if word in keys else int(any(word in key for key in keys)) for word in words)
        if score:
            scored.append((score, row))
    return [row for _, row in sorted(scored, key=lambda pair: (-pair[0], pair[1]["id"]))[:limit]]


def section(row):
    path = (REFERENCES / row["document"]).resolve()
    if not path.is_relative_to(REFERENCES.resolve()):
        raise ValueError("rule document escapes the skill references")
    lines = path.read_text().splitlines()
    for i, line in enumerate(lines):
        match = re.match(r"^(#{1,6}) (.+)$", line)
        if match and match[2] == row["heading"]:
            level, end = len(match[1]), i + 1
            while end < len(lines):
                next_heading = re.match(r"^(#{1,6}) ", lines[end])
                if next_heading and len(next_heading[1]) <= level:
                    break
                end += 1
            return path, i + 1, lines[i:end]
    raise ValueError("index heading missing: " + row["heading"])


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("query", nargs="*")
    p.add_argument("--list", action="store_true")
    p.add_argument("--limit", type=int, choices=(1, 2, 3), default=2)
    p.add_argument("--max-lines", type=int, default=35)
    args = p.parse_args(argv)
    if not 1 <= args.max_lines <= 100:
        p.error("--max-lines must be 1..100")
    rows = rules()
    if args.list:
        for row in rows:
            print(row["id"] + ": " + row["heading"])
        return 0
    if not args.query:
        p.error("provide a symptom or use --list")
    found = select(" ".join(args.query), rows, args.limit)
    if not found:
        print("No indexed symptom matched. Use --list, then inspect the original operation.")
        return 0
    for row in found:
        path, line, text = section(row)
        location = path.relative_to(ROOT).as_posix()
        print(f'\n[{row["id"]}] {location}:{line}')
        print("\n".join(text[:args.max_lines]))
        if len(text) > args.max_lines:
            print(f"... section continues at {location}:{line + args.max_lines}")
    print("\nDiagnostic guidance only: verify the original ABI and complete native output.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
