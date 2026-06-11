#!/usr/bin/env python3

import sys
import os
import argparse
from core.elf_loader import *
from core.disassembler import *
from core.gadget_scanner import *
from binaryornot.check import is_binary
from core.display_res import display_output

# Controls if:
#     - file exists
#     - file is binary
def file_control(file):
    if not os.path.exists(file): 
        sys.stderr.write("The file does not exists.\n")
        exit(1)
    if not (is_binary(file)):
        sys.stderr.write("The file is not a binary.\n")
        exit(1)


def main():
    parser = argparse.ArgumentParser(description='ROP finder.')
    parser.add_argument('binary', type=str, help='The elf binary to read')
    parser.add_argument('-d', '--depth', type=int, default=3, metavar='', action='store', help='Choose depth for the gadgets lists')
    parser.add_argument('-o', '--output', type=str, metavar='', action='store', help='Create an output.json')
    args = parser.parse_args()

    file_control(args.binary)
    elf = process_elf(args.binary)
    d = Disassembler(elf)
    instr_list = d.disas()

    g_scan = GadgetScanner(instr_list, args.depth)
    gadget_list = g_scan.scan()

    display_output(args.output, gadget_list, g_scan)

if __name__ == '__main__':
    main()




# TO IMPROVE
# handle other binaries: already ARM, x86(64, 32)
# handle CLI, add other flags ?

# deduplicate gadgets (same instructions at different addresses)
# filter out low quality gadgets (e.g. only a ret with nothing useful before)
# search for specific patterns like pop rdi; ret specifically
# dump gadgets as JSON so the output can be piped into other tools — very CTF/professional
# gadget_db.py         # stockage structuré
# ASLR offset support
# pwntools-ready chain export
# add docstrings to your classes and methods
# a README.md explaining what it does, how to install, how to use it with examples