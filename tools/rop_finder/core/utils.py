from capstone import *

# Dictionaries for capstone constants
arch_map = {
    'EM_X86_64': CS_ARCH_X86, # includes x86 & x86 64
    'EM_ARM': CS_ARCH_ARM,
}

mode_map = {
    ('EM_X86_64', 64): CS_MODE_64,
    ('EM_X86_64', 32): CS_MODE_32,
    ('EM_ARM', 32): CS_MODE_ARM,
}