#ifndef HW_H
#define HW_H

#include "const.h"
#include "instruction.h"

#define HELP_MODE 0x1
#define DISASSEMBLE_MODE 0x2
#define BIG_ENDIAN_MODE 0x4
#define BASE_ADDR_MASK 0xfffff000

int assemble(void);
int disassemble(void);

#endif
