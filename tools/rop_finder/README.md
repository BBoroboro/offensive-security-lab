# ROP Gadget Finder

This ROP Gadget Finder is aiming at facilitating binaries analysis. Running it on your binary will help you develop ROP chains exploits. For now it supports x86, x64 and ARM, until further updates!

# Installations

To run this program you'll first need to install the following frameworks:
```txt
    pip install binaryornot
    pip3 install pyelftools
    pip install capstone
```

# Usage

This program can be launch running the following command:
```txt
    ./rop_finder.py your-binary
```
It also support some flags to help you improve your analysis:
```txt
    usage: rop_finder.py [-h] [-d] [-o] [-f] binary

    ROP finder.

    positional arguments:
    binary          The elf binary to read

    options:
    -h, --help      show this help message and exit
    -d , --depth    Choose depth for the gadgets lists
    -o , --output   Create an output.json
    -f , --filter   Choose a gadget pattern
```

## Examples

The following commands show you a few exemples on how you could run this program with flags:
```txt
    ./rop_finder.py --help
    ./rop_finder.py [BINARY] --depth 3
    ./rop_finder.py [BINARY] --output output_file
    ./rop_finder.py [BINARY] --output output_file --depth 3
    ./rop_finder.py [BINARY] --filter "pop {r4, r5, r6}"
    ./rop_finder.py [BINARY] --output output_file --depth 8 --filter "pop {r4, r5, r6}"
```

# Further improvment to come
- Handle more binaries
- Handle more flags to narrow down axploitation or filter out low quality gadgets
- Handle deduplicate gadgets
- gadget_db.py
- ASLR offset support
- Pwntools-ready chain export
- Add docstrings to classes and methods
