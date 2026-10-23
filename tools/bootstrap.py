#!/usr/bin/env python3
"""Build only the pinned Thumb C compiler, with a bounded, owned work tree."""
import argparse
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PIN = "da598c1d918402c42c0c0d7128ba14567f3175e9"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cc", default="clang")
    args = parser.parse_args()
    source = ROOT / "vendor/agbcc"
    revision = subprocess.check_output(["git", "-C", str(source), "rev-parse", "HEAD"], text=True).strip()
    if revision != PIN:
        raise SystemExit("agbcc submodule does not match the compiler pin")
    if subprocess.check_output(["git", "-C", str(source), "status", "--porcelain"]):
        raise SystemExit("agbcc submodule has local changes")
    for tool in [args.cc, "make", "arm-none-eabi-as", "arm-none-eabi-ld", "arm-none-eabi-objcopy"]:
        if not shutil.which(tool):
            raise SystemExit("Missing prerequisite: " + tool)
    dest = ROOT / "build/toolchain"
    dest.mkdir(parents=True, exist_ok=True)
    binary = dest / "agbcc"
    if binary.exists():
        print("Using existing compiler; remove build/toolchain/agbcc to rebuild")
        return
    work = dest / "bootstrap-work"
    if work.exists():
        raise SystemExit("Existing bootstrap-work retained; inspect before removing it")
    shutil.copytree(source / "gcc", work)
    with (dest / "bootstrap.log").open("w") as log:
        # Upstream generated-header dependencies require a serial build.
        subprocess.run(["make", "-C", str(work), "-j1", "CC=" + args.cc], stdout=log, stderr=subprocess.STDOUT, check=True)
    shutil.copy2(work / "agbcc", binary)
    shutil.rmtree(work)
    print("Built " + str(binary))


if __name__ == "__main__":
    main()
