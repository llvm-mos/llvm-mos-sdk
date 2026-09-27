#!/usr/bin/env python3
"""Run a C64 or C128 test program under VICE (x64sc/x128) and report its result.

Usage: vice-runner.py --vice <x128> --prg <test.prg> --map <test.map>
                      [--restore-range 0800-09ff] [--timeout 120]
                      [--expect-basic-prompt]

Result protocol: the same one the emutest runner uses (see test/README.md and
test-lib-emutest.c). The program exits with a status - returning it from main,
or calling exit() - and test-lib-emutest's _Exit stores the signature
"TestPass" (status 0) or "TestFail" in the RAM array test_result and then
spins. This script runs the program until the end of its exit handlers (the
.fini_rts section), steps the CPU on through _Exit, dumps test_result through
the VICE monitor, and decodes it.

On the c128, if the program links bank1.o (it has an .init.011 section), two
things the platform promises to restore are also checked, by reading them just
before the program changes them and again after the exit handlers: the
"Common-RAM code area" that c128_bank1_call borrows must hold identical bytes
(the area defaults to the platform default, $0800-$09FF; pass --restore-range
if the test moves it), and the RAM Configuration Register ($D506) must have
its original value.

--expect-basic-prompt is a different kind of test: the program is linked with
save-basic.o (not test-lib-emutest) and returns to BASIC. The runner stops at
_Exit, lets the machine run on, and passes if BASIC has printed a NEW READY.
prompt (one more READY. line than were on the screen at _Exit - autostart
leaves its own prompt behind, so the mere presence of one proves nothing) and
did not fall into the machine-language monitor (BREAK). That shows the return,
including the restore of BASIC's memory configuration, worked.

Exit status: 0 pass, 1 fail, 2 no result (crash, hang, timeout, or the
program never reached _Exit).
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

SIGNATURES = {b"TestPass": 0, b"TestFail": 1}

# Instructions to execute after the exit handlers so _Exit can store the
# signature (about a hundred are needed; the rest are the spin loop). The
# monitor's `z` command takes a hexadecimal count, so this is formatted as hex.
EXIT_STEPS = 3000

# Instructions to let BASIC run after the program returns to it, so that it
# prints its prompt (again a number for `z`, formatted as hex).
BASIC_STEPS = 0x20000


def parse_map(path):
    """Return (symbols, sections): name -> address, from an lld -Map file."""
    symbols, sections = {}, {}
    for line in open(path, errors="replace"):
        m = re.match(r"^\s+([0-9a-f]+)\s+[0-9a-f]+\s+[0-9a-f]+\s+\d+\s+(.*\S)\s*$", line)
        if not m:
            continue
        addr, rest = int(m.group(1), 16), m.group(2)
        sec = re.search(r"\((\.[^)\s]+)\)$", rest)
        if sec:
            sections.setdefault(sec.group(1), addr)
        elif re.fullmatch(r"[A-Za-z_][\w.]*", rest):
            symbols.setdefault(rest, addr)
    return symbols, sections


def strip_header(data):
    # The monitor's `save` writes a two-byte load address first.
    return data[2:]


def screen_text(data):
    """Decode 40 x 25 screen RAM (screen codes) to text lines."""
    def dec(b):
        b &= 0x7F
        return chr(64 + b) if 1 <= b <= 26 else chr(b) if 32 <= b <= 63 else "."
    return ["".join(dec(b) for b in data[r * 40:(r + 1) * 40]).rstrip() for r in range(25)]


def run_basic_prompt(args, symbols):
    if "_Exit" not in symbols:
        print("runner: _Exit not found in the map; is the program linked with "
              "save-basic.o?", file=sys.stderr)
        return 2
    with tempfile.TemporaryDirectory(prefix="vice-test-") as tmp:
        def p(name):
            return os.path.join(tmp, name).replace("\\", "/")

        # Stop when the program calls _Exit and look at the screen, then let
        # BASIC run and look again.
        mon = ["bank ram",
               f'save "{p("screen_before.bin")}" 0 0400 07e7',
               f"z {BASIC_STEPS:x}",
               f'save "{p("screen_after.bin")}" 0 0400 07e7',
               "quit"]
        with open(p("script.mon"), "w") as f:
            f.write("\n".join(mon) + "\n")
        cmd = [args.vice, "-default", "-initbreak", str(symbols["_Exit"]),
               "-moncommands", p("script.mon"), "-autostart", os.path.abspath(args.prg)]
        proc = subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        deadline = time.time() + args.timeout
        while proc.poll() is None and time.time() < deadline:
            time.sleep(0.25)
        timed_out = proc.poll() is None
        if timed_out:
            proc.kill()
        proc.wait()
        if not os.path.exists(p("screen_after.bin")):
            print("FAIL (no result): the program never reached _Exit"
                  + (" (timeout)" if timed_out else ""))
            return 2
        before = screen_text(strip_header(open(p("screen_before.bin"), "rb").read()))
        after = screen_text(strip_header(open(p("screen_after.bin"), "rb").read()))
        if any("BREAK" in line for line in after):
            print("FAIL: the return to BASIC ended in the machine-language monitor (BREAK)")
            return 1
        ready_before = sum("READY." in line for line in before)
        ready_after = sum("READY." in line for line in after)
        if ready_after <= ready_before:
            print(f"FAIL: BASIC printed no new READY. prompt after _Exit "
                  f"({ready_before} on screen before, {ready_after} after)")
            return 1
        print("PASS (returned to BASIC)")
        return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--vice", required=True, help="path to x128")
    ap.add_argument("--prg", required=True)
    ap.add_argument("--map", required=True)
    ap.add_argument("--restore-range", default="0800-09ff",
                    help="hex start-end of the Common-RAM code area to check")
    ap.add_argument("--timeout", type=float, default=120)
    ap.add_argument("--expect-basic-prompt", action="store_true",
                    help="pass if the program returns to BASIC's READY. prompt")
    args = ap.parse_args()

    symbols, sections = parse_map(args.map)
    if args.expect_basic_prompt:
        return run_basic_prompt(args, symbols)
    if "test_result" not in symbols or ".fini_rts" not in sections:
        print("runner: test_result/.fini_rts not found in the map; does the test "
              "link test-lib-emutest?", file=sys.stderr)
        return 2
    result_addr = symbols["test_result"]
    end_addr = sections[".fini_rts"]
    check_restore = ".init.011" in sections
    lo, hi = (int(x, 16) for x in args.restore_range.split("-"))

    with tempfile.TemporaryDirectory(prefix="vice-test-") as tmp:
        def p(name):
            return os.path.join(tmp, name).replace("\\", "/")

        # Read RAM, not the CPU's current view: after the exit handlers restore
        # BASIC's memory configuration, $4000-$BFFF shows BASIC ROM.
        mon = ["bank ram"]
        if check_restore:
            # First stop: just before .init.011 changes the RCR, and so before
            # .init.012 copies the common code over the area.
            mon += [f'save "{p("before.bin")}" 0 {lo:04x} {hi:04x}',
                    "bank io", f'save "{p("rcr_before.bin")}" 0 d506 d506', "bank ram",
                    f"break {end_addr:x}", "x",
                    f'save "{p("after.bin")}" 0 {lo:04x} {hi:04x}',
                    "bank io", f'save "{p("rcr_after.bin")}" 0 d506 d506', "bank ram"]
            first_stop = sections[".init.011"]
        else:
            first_stop = end_addr
        mon += [f"z {EXIT_STEPS:x}",
                f'save "{p("result.bin")}" 0 {result_addr:04x} {result_addr + 7:04x}']
        # Tests that use test-check.h say which check failed.
        fail_addr = symbols.get("test_fail_line")
        if fail_addr is not None:
            mon.append(f'save "{p("fail.bin")}" 0 {fail_addr:04x} {fail_addr + 1:04x}')
        mon.append("quit")
        with open(p("script.mon"), "w") as f:
            f.write("\n".join(mon) + "\n")

        # -initbreak takes a DECIMAL address.
        cmd = [args.vice, "-default", "-initbreak", str(first_stop),
               "-moncommands", p("script.mon"), "-autostart", os.path.abspath(args.prg)]
        proc = subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        deadline = time.time() + args.timeout
        while proc.poll() is None and time.time() < deadline:
            time.sleep(0.25)
        timed_out = proc.poll() is None
        if timed_out:
            proc.kill()
        proc.wait()

        if not os.path.exists(p("result.bin")):
            print("FAIL (no result): the program never reached the end of its exit "
                  "handlers" + (" (timeout)" if timed_out else ""))
            return 2
        sig = strip_header(open(p("result.bin"), "rb").read())[:8]
        status = SIGNATURES.get(sig)
        if status is None:
            print(f"FAIL (no result): test_result holds {sig!r}; the program never "
                  "reached _Exit (is test-lib-emutest linked?)")
            return 2
        if status != 0:
            where = ""
            if os.path.exists(p("fail.bin")):
                line = int.from_bytes(strip_header(open(p("fail.bin"), "rb").read())[:2], "little")
                if line:
                    where = f"; the failing check is at line {line}"
            print("FAIL: the program exited with a failure status (TestFail)" + where)
            return 1
        if check_restore:
            rcr_before = strip_header(open(p("rcr_before.bin"), "rb").read())
            rcr_after = strip_header(open(p("rcr_after.bin"), "rb").read())
            if rcr_before != rcr_after:
                print(f"FAIL: RCR ($D506) was ${rcr_before[0]:02X} at startup but "
                      f"${rcr_after[0]:02X} after exit")
                return 1
            before = strip_header(open(p("before.bin"), "rb").read())
            after = strip_header(open(p("after.bin"), "rb").read())
            if before != after:
                diff = [f"${lo + i:04X}" for i, (a, b) in enumerate(zip(before, after)) if a != b]
                print(f"FAIL: ${lo:04X}-${hi:04X} was not restored at exit; differs at "
                      + " ".join(diff[:16]))
                return 1
        print("PASS" + (f" (${lo:04X}-${hi:04X} and RCR restored)" if check_restore else ""))
        return 0


if __name__ == "__main__":
    sys.exit(main())
