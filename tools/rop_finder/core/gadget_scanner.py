mnemonic_list = ['ret', 'bx lr', 'pop \{pc\}']

class   Gadget:
    def __init__(self, addr, instructions):
        self.addr = addr
        self.instructions = instructions

    def __str__(self):
        result = ""
        for instr in self.instructions:
            result += ("\n\t0x%x:\t%s\t%s" %(instr.address, instr.mnemonic, instr.op_str))
        return f'At address: {hex(self.addr)} gadget is:{result}'

    def to_dict(self):
        dic = {"address": self.addr, "instructions":[]}
        for instr in self.instructions:
            dic["instructions"].append({"address": instr.address, "mnemonic": instr.mnemonic, "op_str": instr.op_str})
        return dic

    def to_str(self):
        i_list = []
        for instr in self.instructions:
            string = instr.mnemonic + " " + instr.op_str
            i_list.append(string)
        res = "; ".join(i_list)
        return res

class   GadgetScanner:
    def __init__(self, instr_list, depth):
        self.instr_list = instr_list
        self.depth = depth

    def scan(self):
        gadget_list = []
        for idx, instr in enumerate(self.instr_list):
            if (len(instr.op_str) > 0): # in case of ARM
                ret_instruction = instr.mnemonic + " " + instr.op_str
            else:                       # in case of ASM
                ret_instruction = instr.mnemonic
            if (ret_instruction in mnemonic_list):
                depth = idx - self.depth
                if(depth < 0):
                    depth = idx
                gadget_list.append(Gadget(self.instr_list[depth].address , self.instr_list[depth:idx + 1]))
        return gadget_list


    def print_gadgets(self, gadget_list):
        for i in gadget_list:
            print(i)