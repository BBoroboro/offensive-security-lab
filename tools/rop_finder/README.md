


Input: ELF x67 / ELF x64

Output: Useful ROP gadgets used

## Architecture

rop_finder/
│
├── rop_finder.py        # CLI entrypoint
├── elf_loader.py        # charge ELF + sections
├── disassembler.py      # capstone wrapper
├── gadget_scanner.py    # find patterns
├── gadget_db.py         # stockage structuré
└── utils.py

## 1. ELF loader

Responsible for:
- read ELF
- get .text
- get base addresses

Lib:
- pyelftools

## 2. Disassembly Engine

Lib:
- capstone

Ex:
```
for insn in md.disasm(code, base):
    print(insn.address, insn.mnemonic, insn.op_str)
```

## 3. Gadget scanner (important part)

Simple patterns:
ret
pop rdi; ret
pop rsi ; pop r15 ; ret
syscall

## 4. Gadget representation

```
class Gadget:
    def __init__(self, addr, instructions):
        self.addr = addr
        self.instructions = instructions
```

## 5. CLI

Ex:
```
python rop_finder.py ./binary
```

Ouput:
tri par type
export JSON optionnel


## BONUS (to level up)
filtre gadgets utiles only (skip junk)
support ASLR offsets
export pwntools-ready chain



## requirements

pip install binaryornot

pip3 install pyelftools

also capstone
 capstone is a programmatically disassembler, md is a CsInsn object — specifically, md is a Capstone disassembler instance that you create before disassembling and it needs
 the architecture (x86, ARM, MIPS...)
 the mode (32-bit or 64-bit)
