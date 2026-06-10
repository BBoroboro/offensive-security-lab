#!/usr/bin/env python3

import sys
from elf_loader import *
from disassembler import *
from gadget_scanner import *
import os
from binaryornot.check import is_binary

# Control if:
#     - has between 1 [bin] and 2 [depth] args
#     - depth is an int
#     - if no input[depth] attribute 2 as 

def input_control(args):
    if len(args) < 2 or len(args) > 3 :
        # control if file is elf x86 or x64
        sys.stderr.write("Usage: ./rop_finder.py binary depth(optional)\n")
        sys.exit(1)
    if (len(args) == 3):
        try:
            depth = int(args[2])
        except:
            sys.stderr.write("Input [depth] is not an integer\n")
            sys.exit(1)
    else:
        depth = 2
    return depth

# Control if:
#     - file exists
#     - file is binary

def file_control(file):
    if os.path.exists(file): 
        print("The file exists") # test
    else:
        sys.stderr.write("The file does not exists.\n")
        exit(1)
    if not (is_binary(file)):
        sys.stderr.write("The file is not a binary.\n")
        exit(1)


def main():
    depth = input_control(sys.argv)
    file_control(sys.argv[1])

    elf = process_elf(sys.argv[1])
    d = Disassembler(elf)
    instr_list = d.disas()
    g_scan = GadgetScanner(instr_list, depth)
    gadget_list = g_scan.scan()

    g_scan.print_gadgets(gadget_list)

if __name__ == '__main__':
    main()

# TO IMPROVE
# handle other binaries
# handle missing .text
# handle CLI, use argparse to add proper flags like --depth, --output json, --arch
# deduplicate gadgets (same instructions at different addresses)
# filter out low quality gadgets (e.g. only a ret with nothing useful before)
# search for specific patterns like pop rdi; ret specifically
# dump gadgets as JSON so the output can be piped into other tools — very CTF/professional
# gadget_db.py         # stockage structuré
# ASLR offset support
# pwntools-ready chain export
# add docstrings to your classes and methods
# a README.md explaining what it does, how to install, how to use it with examples