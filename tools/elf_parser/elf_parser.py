#!/usr/bin/env python3

import sys
import os
import struct
from dataclasses import dataclass

ELF64_FMT = "<HHLQQQLHHHHHH"
ELF32_FMT = "<HHIIIIIHHHHHH"

ELF64_FMT_BE = ">HHLQQQLHHHHHH"
ELF32_FMT_BE = ">HHIIIIIHHHHHH"

@dataclass
class Elfheader:
    e_type: int
    e_machine: int
    e_version: int
    e_entry: int
    e_phoff: int
    e_shoff: int
    e_flags: int
    e_ehsize: int
    e_phentsize: int
    e_phnum: int
    e_shentsize: int
    e_shnum: int
    e_shstrndx: int

def display_header(header, arch, endianness):
    print("ELF Header\n-------------")
    if arch == 2:
        print("Architecture\t: x86_64")
    else:
        print("Architecture\t: x86")
    print("Endianness\t:", "Little Endian" if endianness == 1 else "Big Endian")
    print("Entry point\t:", hex(header.e_entry))

def parse(data, arch, endianness):

    if (arch == 2): # ELF64
        fmt = ELF64_FMT if endianness == 1 else ELF64_FMT_BE
        e_header = struct.unpack(fmt, data[16:64])
    else: # ELF32
        fmt = ELF32_FMT if endianness == 1 else ELF32_FMT_BE
        e_header = struct.unpack(fmt, data[16:64])
    header = Elfheader(*e_header)
    if (endianness == 1):
        e_header = struct.unpack("<HHLQQQLHHHHHH", data[16:64])
    else:
        e_header = struct.unpack(">HHLQQQLHHHHHH", data[16:64])
    header = Elfheader(*e_header)
    display_header(header, arch, endianness)

def main():
    with open(sys.argv[1], 'rb') as f:
        data = f.read()
        if ((data[:4]) != b'\x7fELF'):
            print("File is not an elf")

        e_ident = struct.unpack('16B', data[:16])

        arch = e_ident[4]
        endianness = e_ident[5]

        parse(data, arch, endianness)


if __name__ == '__main__':
    main()