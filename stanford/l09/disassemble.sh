#!/bin/bash
# disassemble.sh
# dekoduje binarni program na asm instrukce

# dekodovani do GNU assembleru
objdump -S -d simple


# dekodovani do intel assembleru
#objdump -S -d -Mintel simple
