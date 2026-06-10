from capstone import *
from utils import *

# class for disassembler to use capstone
class   Disassembler:
    def __init__(self, loader):
        self.md = Cs(loader.arch, loader.bitness)
        self.code = loader.bytes
        self.addr = loader.base_addr
    
    def disas(self):
        instr_list = []
        for i in self.md.disasm(self.code, self.addr):
            instr_list.append(i)
            # print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
        return instr_list
#  You can enable more detail with self.md.detail = True after creating the Cs instance. Not strictly necessary now, but useful later for the gadget scanner.
