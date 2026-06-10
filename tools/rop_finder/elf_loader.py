from elftools.elf.elffile import ELFFile 
from elftools.elf.segments import Segment
from utils import *
from capstone import *
import sys

authorized_elf = ['EM_X86_64', 'EM_ARM']

# class for elf loader
class   ELFLoader:
    def __init__(self, txt_addr, txt_bytes, architecture, bitness):
        self.base_addr = txt_addr
        self.bytes = txt_bytes
        self.arch = arch_map[architecture]
        self.bitness = mode_map[architecture, bitness]

def elf_control(file):
    for elfs in authorized_elf:
        if (elfs == file):
            print("this elf is supported!") # test
            return
    print(f"This program does not support {file} yet") # change it to error ? Maybe no
    exit(1) # is it really an error?

def process_elf(filename):
    with open(filename, 'rb') as f:
        elffile = ELFFile(f)
        # dataSec = elffile.get_section_by_name(b'.data')
        textSec = elffile.get_section_by_name('.text')
        if (textSec == None):
                sys.stderr.write("The binary is missing the .text section")
                exit(1)
        # print(textSec.data()) # raw baytes of .text

        print(hex(textSec.header.sh_addr)) # base address of .text

        elf_control(elffile.header.e_machine)
        # print(elffile.header.e_machine)
        # print(elffile.elfclass)

        rop = ELFLoader(textSec.header.sh_addr, textSec.data(), elffile.header.e_machine, elffile.elfclass)
    return rop

