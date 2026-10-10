#!/usr/bin/env python3
# Copyright 2026 LLVM-MOS Project
# Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
# See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
# information.
"""Create a Commodore 1581 (.d81) disk image. Pure stdlib.

Geometry: 80 tracks x 40 sectors x 256 bytes. Track 40 holds the header (40/0),
the BAM (40/1 tracks 1-40, 40/2 tracks 41-80) and the directory (40/3..40/39),
and is allocated whole at format time, leaving 3160 blocks free.

Follows Peter Schepers / VICE "D81 (Disk Image) Format"
"""

import argparse
import itertools
import os
import sys
from collections.abc import Iterator
from pathlib import Path

TRACKS = 80
SECTORS_PER_TRACK = 40
SECTOR_SIZE = 256
IMAGE_SIZE = TRACKS * SECTORS_PER_TRACK * SECTOR_SIZE

# Track 40 is the directory track: reserved whole, so it never holds data.
DIR_TRACK = 40
HEADER_SECTOR = 0
BAM_SECTOR_LO = 1
BAM_SECTOR_HI = 2
FIRST_DIR_SECTOR = 3
LAST_DIR_SECTOR = 39

# Two of every sector go to the next-block link, leaving 254 for data.
DATA_PER_SECTOR = 254
ENTRIES_PER_SECTOR = 8
ENTRY_SIZE = 32
DIR_ENTRIES = (LAST_DIR_SECTOR - FIRST_DIR_SECTOR + 1) * ENTRIES_PER_SECTOR
NAME_LEN = 16
DISK_ID_LEN = 2
PAD = 0xA0  # CBM pads names with $A0, not spaces

# One BAM entry per track: a free-block count, then a bitmap with one bit per
# sector. The entries start at BAM_ENTRIES and run to the end of the sector.
BAM_ENTRIES = 0x10
BAM_BITMAP_BYTES = (SECTORS_PER_TRACK + 7) // 8
BAM_ENTRY_SIZE = 1 + BAM_BITMAP_BYTES

FILE_TYPES = {"DEL": 0, "SEQ": 1, "PRG": 2, "USR": 3, "REL": 4}
EXT_TO_TYPE = {".prg": "PRG", ".seq": "SEQ", ".usr": "USR", ".del": "DEL"}


def _to_petscii(s: str) -> bytes:
    """ASCII to PETSCII for disk and file names.

    Both cases map to $41-$5A, which is what the KERNAL's directory match
    compares against. Deliberately not the reversible c1541 mapping, which
    sends 'A'-'Z' to $C1-$DA instead and so depends on the caller's case.
    """
    def one(c: int) -> int:
        if 0x61 <= c <= 0x7A:  # fold lower case up
            return c - 0x20
        return c if 0x20 <= c <= 0x5F else 0x3F  # '?'

    return bytes(one(ord(ch)) for ch in s)


def _petscii_field(s: str, length: int) -> bytes:
    """PETSCII, truncated to length and padded with $A0 as CBM expects."""
    return _to_petscii(s)[:length].ljust(length, bytes([PAD]))


class D81:
    def __init__(self, name: str = "EMPTY", disk_id: str = "00") -> None:
        self.data = bytearray(IMAGE_SIZE)
        self._format(name, disk_id)

    def _sector(self, track: int, sec: int) -> memoryview:
        """A writable view of one sector. Tracks count from 1, sectors from 0."""
        if not (1 <= track <= TRACKS) or not (0 <= sec < SECTORS_PER_TRACK):
            raise ValueError(f"bad t/s {track}/{sec}")
        off = ((track - 1) * SECTORS_PER_TRACK + sec) * SECTOR_SIZE
        return memoryview(self.data)[off : off + SECTOR_SIZE]

    @staticmethod
    def _bam_loc(track: int) -> tuple[int, int]:
        """BAM sector on track 40, and the offset of this track's 6-byte entry."""
        half = TRACKS // 2
        if 1 <= track <= half:
            return BAM_SECTOR_LO, BAM_ENTRIES + (track - 1) * BAM_ENTRY_SIZE
        if half < track <= TRACKS:
            return BAM_SECTOR_HI, BAM_ENTRIES + (track - half - 1) * BAM_ENTRY_SIZE
        raise ValueError(f"bad track {track}")

    def _is_free(self, track: int, sec: int) -> bool:
        """True if the BAM bit is set: in CBM BAMs a set bit means free."""
        bs, off = self._bam_loc(track)
        bam = self._sector(DIR_TRACK, bs)
        return bool(bam[off + 1 + (sec >> 3)] & (1 << (sec & 7)))

    def _allocate(self, track: int, sec: int) -> None:
        """Clear the sector's BAM bit and decrement its track free count."""
        bs, off = self._bam_loc(track)
        bam = self._sector(DIR_TRACK, bs)
        i, mask = off + 1 + (sec >> 3), 1 << (sec & 7)
        if not bam[i] & mask:
            raise RuntimeError(f"sector {track}/{sec} already allocated")
        bam[i] &= ~mask & 0xFF
        bam[off] -= 1

    def blocks_free(self) -> int:
        return sum(
            self._sector(DIR_TRACK, bs)[off]
            for bs, off in map(self._bam_loc, range(1, TRACKS + 1))
        )

    def _format(self, name: str, disk_id: str = "00") -> None:
        """Write the header, BAM and first directory sector.

        The whole directory track is marked allocated, so file data never
        lands on it. Relies on the buffer being zeroed, which is why this runs
        only from __init__: a file type of 0 is what marks a directory entry
        unused.
        """
        did = _petscii_field(disk_id, DISK_ID_LEN)

        h = self._sector(DIR_TRACK, HEADER_SECTOR)
        h[0x00], h[0x01] = DIR_TRACK, FIRST_DIR_SECTOR
        h[0x02] = 0x44  # 'D', disk format type
        h[0x03] = 0x00
        h[0x04:0x14] = _petscii_field(name, NAME_LEN)
        h[0x14:0x16] = bytes([PAD, PAD])
        h[0x16:0x18] = did
        h[0x18] = PAD
        h[0x19] = 0x33  # DOS version '3'
        h[0x1A] = 0x44  # disk version 'D'
        h[0x1B:0x1D] = bytes([PAD, PAD])

        lo = self._sector(DIR_TRACK, BAM_SECTOR_LO)
        lo[0x00], lo[0x01] = DIR_TRACK, BAM_SECTOR_HI
        hi = self._sector(DIR_TRACK, BAM_SECTOR_HI)
        hi[0x00], hi[0x01] = 0x00, 0xFF
        for b in (lo, hi):
            b[0x02] = 0x44  # version 'D'
            b[0x03] = 0xBB  # its one's complement
            b[0x04:0x06] = did
            b[0x06] = 0xC0  # I/O byte: verify on, check CRC
            b[0x07] = 0x00  # autoloader flag

        for t in range(1, TRACKS + 1):
            bs, off = self._bam_loc(t)
            b = self._sector(DIR_TRACK, bs)
            b[off] = SECTORS_PER_TRACK
            b[off + 1 : off + BAM_ENTRY_SIZE] = b"\xff" * BAM_BITMAP_BYTES

        bs, off = self._bam_loc(DIR_TRACK)  # track 40 is reserved whole
        b = self._sector(DIR_TRACK, bs)
        b[off] = 0
        b[off + 1 : off + BAM_ENTRY_SIZE] = b"\x00" * BAM_BITMAP_BYTES

        d = self._sector(DIR_TRACK, FIRST_DIR_SECTOR)
        d[0x00], d[0x01] = 0x00, 0xFF

    def _free_blocks(self) -> Iterator[tuple[int, int]]:
        """Every free block in track order, skipping the directory track."""
        return (
            (t, s)
            for t in range(1, TRACKS + 1)
            if t != DIR_TRACK
            for s in range(SECTORS_PER_TRACK)
            if self._is_free(t, s)
        )

    def _alloc_chain(self, count: int) -> list[tuple[int, int]]:
        """Reserve count blocks, first-fit, and return them in chain order."""
        # No interleave: an image file has no rotational latency to hide.
        blocks = list(itertools.islice(self._free_blocks(), count))
        if len(blocks) < count:
            raise RuntimeError(
                f"disk full: need {count} blocks, {self.blocks_free()} free"
            )
        for t, s in blocks:
            self._allocate(t, s)
        return blocks

    def _alloc_dir_entry(self) -> tuple[int, int]:
        """Directory sector number, and the offset of a free 32-byte entry."""
        cur = FIRST_DIR_SECTOR
        while True:
            d = self._sector(DIR_TRACK, cur)
            for i in range(ENTRIES_PER_SECTOR):
                off = i * ENTRY_SIZE
                if d[off + 2] == 0x00:  # unused file-type byte
                    return cur, off
            if d[0] == DIR_TRACK:  # a further sector already exists
                cur = d[1]
                continue
            nxt = cur + 1
            if nxt > LAST_DIR_SECTOR:
                raise RuntimeError(f"directory full ({DIR_ENTRIES} entries)")
            d[0], d[1] = DIR_TRACK, nxt
            nd = self._sector(DIR_TRACK, nxt)
            nd[0], nd[1] = 0x00, 0xFF
            cur = nxt

    def add_file(self, cbm_name: str, data: bytes, ftype: str = "PRG") -> int:
        """Write data as a linked sector chain and add its directory entry.

        Returns the block count. Each sector holds 254 bytes behind a 2-byte
        link to the next; in the last, that link is 0 and the byte offset of
        the final valid byte, not a length.
        """
        if not data:
            raise ValueError(f"{cbm_name}: refusing to write an empty file")
        code = FILE_TYPES[ftype.upper()]
        chunks = [
            bytes(data[i : i + DATA_PER_SECTOR])
            for i in range(0, len(data), DATA_PER_SECTOR)
        ]
        blocks = self._alloc_chain(len(chunks))

        for i, (t, s) in enumerate(blocks):
            sec = self._sector(t, s)
            if i + 1 < len(blocks):
                sec[0], sec[1] = blocks[i + 1]
            else:
                # End of chain: byte 1 is the offset of the last valid byte.
                sec[0], sec[1] = 0x00, len(chunks[i]) + 1
            sec[2 : 2 + len(chunks[i])] = chunks[i]

        ds, off = self._alloc_dir_entry()
        e = self._sector(DIR_TRACK, ds)
        e[off + 2] = 0x80 | code  # bit 7 = closed
        e[off + 3], e[off + 4] = blocks[0]
        e[off + 5 : off + 5 + NAME_LEN] = _petscii_field(cbm_name, NAME_LEN)
        e[off + 30] = len(blocks) & 0xFF
        e[off + 31] = (len(blocks) >> 8) & 0xFF
        return len(blocks)

    def save(self, path: str) -> None:
        """Write the image out."""
        Path(path).write_bytes(self.data)


def _parse_spec(spec: str) -> tuple[str, str, str]:
    """PATH, or PATH=CBMNAME, or PATH=CBMNAME,TYPE."""
    path, _, rest = spec.partition("=")
    name, _, ftype = rest.partition(",")
    if not name:
        name = os.path.splitext(os.path.basename(path))[0]
    if not ftype:
        ftype = EXT_TO_TYPE.get(os.path.splitext(path)[1].lower(), "PRG")
    return path, name, ftype.upper()


def _read_file(d: "D81", cbm_name: str) -> bytes:
    """Walk a file's sector chain back into bytes, for the self-test."""
    want = _petscii_field(cbm_name, NAME_LEN)
    cur = FIRST_DIR_SECTOR
    while True:
        sec = d._sector(DIR_TRACK, cur)
        for i in range(ENTRIES_PER_SECTOR):
            off = i * ENTRY_SIZE
            if sec[off + 2] and bytes(sec[off + 5 : off + 5 + NAME_LEN]) == want:
                t, s = sec[off + 3], sec[off + 4]
                out = bytearray()
                while t:
                    blk = d._sector(t, s)
                    t, s = blk[0], blk[1]
                    # In the last block the link is 0 and s is the offset of
                    # the final valid byte.
                    out += blk[2 : s + 1] if t == 0 else blk[2:]
                return bytes(out)
        if sec[0] != DIR_TRACK:
            raise KeyError(cbm_name)
        cur = sec[1]


def _selftest() -> None:
    """Check geometry, BAM accounting, name encoding and chain round-trip."""
    empty = (TRACKS - 1) * SECTORS_PER_TRACK

    d = D81("TESTDISK", "42")
    assert len(d.data) == IMAGE_SIZE
    assert d.blocks_free() == empty, d.blocks_free()
    # the directory track is reserved whole, so no file can land on it
    assert not any(d._is_free(DIR_TRACK, s) for s in range(SECTORS_PER_TRACK))
    assert all(d._is_free(1, s) for s in range(SECTORS_PER_TRACK))

    for bad in ((0, 0), (TRACKS + 1, 0), (1, SECTORS_PER_TRACK), (1, -1)):
        try:
            d._sector(*bad)
        except ValueError:
            pass
        else:
            raise AssertionError(f"sector{bad} should be rejected")

    d._allocate(1, 0)
    assert not d._is_free(1, 0)
    assert d.blocks_free() == empty - 1
    try:
        d._allocate(1, 0)
    except RuntimeError:
        pass
    else:
        raise AssertionError("double allocation should be rejected")

    # A payload that does not divide evenly, so the last block exercises the
    # byte-offset convention rather than a full sector.
    d = D81()
    payload = bytes(range(256)) * 3
    want_blocks = -(-len(payload) // DATA_PER_SECTOR)
    assert d.add_file("ROUNDTRIP", payload) == want_blocks
    assert d.blocks_free() == empty - want_blocks
    assert _read_file(d, "ROUNDTRIP") == payload

    # Exactly one full sector: the last block is full and must not be truncated.
    d = D81()
    exact = bytes(range(254))
    assert d.add_file("EXACT", exact) == 1
    assert _read_file(d, "EXACT") == exact

    try:
        d.add_file("EMPTY", b"")
    except ValueError:
        pass
    else:
        raise AssertionError("an empty file should be rejected")

    # Names are upper-cased and $A0-padded, and truncated to the field.
    assert _petscii_field("ab", 4) == b"AB\xa0\xa0"
    assert _petscii_field("x" * 20, NAME_LEN) == b"X" * NAME_LEN
    assert _to_petscii("Az9") == b"AZ9"
    assert _to_petscii("\u00e9") == b"?"

    assert _parse_spec("dir/f.prg") == ("dir/f.prg", "f", "PRG")
    assert _parse_spec("f.bin=NAME") == ("f.bin", "NAME", "PRG")
    assert _parse_spec("f.bin=NAME,SEQ") == ("f.bin", "NAME", "SEQ")
    assert _parse_spec("f.seq") == ("f.seq", "f", "SEQ")

    print("d81.py: self-test passed", file=sys.stderr)


def main(argv=None) -> None:
    ap = argparse.ArgumentParser(description="Create a .d81 disk image.")
    ap.add_argument("image", nargs="?")
    ap.add_argument(
        "files", nargs="*", help="PATH[=CBMNAME[,TYPE]] with TYPE in PRG SEQ USR DEL"
    )
    ap.add_argument("-n", "--name", default="EMPTY", help="disk name, 16 chars")
    ap.add_argument("-i", "--id", default="00", dest="disk_id", help="disk ID, 2 chars")
    ap.add_argument(
        "--selftest", action="store_true", help="check the format code and exit"
    )
    # Intermixed so options may follow the file list, which a caller building
    # the command line by appending naturally produces.
    a = ap.parse_intermixed_args(argv)

    if a.selftest:
        _selftest()
        return
    if a.image is None:
        ap.error("an image path is required")

    d = D81(a.name, a.disk_id)
    for spec in a.files:
        path, cbm, ftype = _parse_spec(spec)
        if ftype not in FILE_TYPES:
            ap.error(f"unknown file type {ftype!r}")
        with open(path, "rb") as f:
            blocks = d.add_file(cbm, f.read(), ftype)
        print(f"{cbm:<16} {ftype:<3} {blocks:4d} blocks", file=sys.stderr)
    d.save(a.image)
    print(f"{d.blocks_free()} blocks free", file=sys.stderr)


if __name__ == "__main__":
    main()
