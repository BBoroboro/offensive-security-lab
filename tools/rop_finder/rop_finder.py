#!/usr/bin/env python3

import sys
import os
import argparse
from core.elf_loader import *
from core.disassembler import *
from core.gadget_scanner import *
from binaryornot.check import is_binary
from core.display_res import display_output

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
    parser.add_argument('-f', '--filter', type=str, metavar='', action='store', help='Choose a gadget pattern') # change name?
    args = parser.parse_args()

    file_control(args.binary)
    elf = process_elf(args.binary)
    d = Disassembler(elf)
    instr_list = d.disas()

    g_scan = GadgetScanner(instr_list, args.depth)
    gadget_list = g_scan.scan()

    if (args.filter):
        filtered_list = []
        for gadget in gadget_list:
            if (args.filter in gadget.to_str()):
                filtered_list.append(gadget)
        display_output(args.output, filtered_list, g_scan)
    else:
        display_output(args.output, gadget_list, g_scan)

if __name__ == '__main__':
    main()
