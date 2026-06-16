Initial prototype developed in Python, later reimplemented in C to gain a deeper understanding of ELF internals and binary parsing.

Don't use a library like:

pyelftools

for the core parsing.

If the goal is learning and showcasing RE knowledge, parse the structures yourself.

Using:

struct.unpack()

is perfectly respectable.




ELF parser demonstrates:
- file format knowledge
- binary structures
- offsets
- headers
- sections
- segments
- ELF headers
- Sections
- Segments
- Entry points
- Offsets
- Symbols
- Relocations

## Elf parser (C or Python)
Output:
```
$ ./elf_parser test.bin

Architecture: x86_64
Entry point: 0x401080

Sections:
.text
.data
.bss

Segments:
LOAD
LOAD
DYNAMIC
```

Goal v1 (finishable in one day)

Don't build readelf.

Build:

$ python elf_parser.py /bin/ls

ELF Header
----------
Architecture : x86_64
Endianness   : Little Endian
Entry Point  : 0x61d0

Sections
--------
.text
.data
.bss
.rodata

Segments
--------
LOAD
LOAD
DYNAMIC
GNU_STACK

That's enough for a first version.

Roadmap
Step 1 — Parse ELF Header

Learn:

Elf64_Ehdr

Important fields:

e_ident
e_type
e_machine
e_entry
e_phoff
e_shoff
e_phnum
e_shnum

Output:

ELF64
Little Endian
x86_64
Entry: 0x401080
Step 2 — Parse Section Headers

Learn:

Elf64_Shdr

Output:

.text
.data
.bss
.rodata
.plt
.got
.symtab
.strtab

This is where you start understanding how ELF files are organized.

Step 3 — Parse Program Headers

Learn:

Elf64_Phdr

Output:

LOAD
LOAD
DYNAMIC
GNU_STACK
GNU_RELRO

This is important because loaders use segments, not sections.

A lot of beginners confuse the two.

Step 4 — Nice Features

Add:

--header
--sections
--segments

Example:

$ elf_parser.py test.bin --sections

Only display sections.

Step 5 — Bonus

Display section sizes:

.text      0x1234
.data      0x200
.bss       0x500

Very easy.

Looks professional.

Step 6 — Bonus++

Symbols

Parse:

main
printf
puts
exit

from:

.symtab
.dynsym

This is where it starts looking like a real analysis tool.

Project Structure

I'd build:

elf_parser/
├── README.md
├── elf_parser.py
├── core/
│   ├── elf_header.py
│   ├── section_parser.py
│   ├── segment_parser.py
│   └── constants.py
└── tests/
