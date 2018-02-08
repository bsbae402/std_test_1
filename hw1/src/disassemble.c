#include <stdio.h>

#include "hw1.h"

static unsigned int branchTarget(unsigned int pc, int arg) {
    return pc + (arg << 2);
}

static unsigned int jumpTarget(unsigned int pc, int arg) {
    return (pc & 0xf0000000) + (arg << 2);
}

static int getOpnd(Instruction *ip, int i) {
    switch(ip->info->srcs[i]) {
        case RS:
    	   return ip->regs[0];
        case RT:
    	   return ip->regs[1];
        case RD:
    	   return ip->regs[2];
        case EXTRA:
    	   return ip->extra;
        default:
    	   return -1;  // TODO: should be an error
    }
}

static int read_int()
{
    int buf[4];
    for(int i = 0; i < 4; i++) {
    	int c = getchar();
    	if(c == -1)
    	    return -1;
    	buf[i] = c;
    }
    //printf("%02x %02x %02x %02x\n", buf[0], buf[1], buf[2], buf[3]);
    int r = 0;
    for(int i = 0; i < 4; i++)
	   r = (r << 8) | buf[3-i];
    return r;
}

int decode(Instruction *ip, unsigned int addr) {
    unsigned int value = ip->value;
    ip->regs[0] = (char) ((value >> 21) & 0x1f);
    ip->regs[1] = (char) ((value >> 16) & 0x1f);
    ip->regs[2] = (char) ((value >> 11) & 0x1f);

    int i = (value >> 26) & 0x3f;
    int opcode = opcodeTable[i];
    if (opcode == SPECIAL) {
    	opcode = specialTable[(int) value & 0x3f];
    } else if (opcode == BCOND) {
    	int i = value & 0x1f0000;
    	if (i == 0) {
    	    opcode = OP_BLTZ;
    	} else if (i == 0x10000) {
    	    opcode = OP_BGEZ;
    	} else if (i == 0x100000) {
    	    opcode = OP_BLTZAL;
    	} else if (i == 0x110000) {
    	    opcode = OP_BGEZAL;
    	} else {
    	    opcode = OP_UNIMP;
    	}
    }
    Instr_info *info = &instrTable[opcode];
    ip->info = info;
    opcode = info->opcode;
    char type = info->type;

    if(opcode == OP_BREAK)
	   ip->extra = (int) (value >> 6) & 0xfffff;
    else if (type == ITYP) {
    	ip->extra = value & 0xffff;
    	// Sign extension
    	if ((ip->extra & 0x8000) != 0) {
    	    ip->extra |= 0xffff0000;
    	}
    } else if (type == RTYP) {
	   ip->extra = (value >> 6) & 0x1f;
    } else {
	   ip->extra = value & 0x3ffffff;
    }

    // Set args in order that they occur in assembler listing.
    // Handle conversion of relative branch offsets to absolute addresses.
    int *args = ip->args;
    if(type == JTYP) {
    	// TODO: Try to test with values that overflow.
    	args[0] = jumpTarget(addr + 4, getOpnd(ip, 0));
    } else if(opcode == OP_BEQ || opcode == OP_BNE) {
    	args[0] = getOpnd(ip, 0);
    	args[1] = getOpnd(ip, 1);
    	args[2] = branchTarget(addr + 4, getOpnd(ip, 2));
    } else if(opcode == OP_BGEZ || opcode == OP_BGEZAL ||
	      opcode == OP_BGTZ || opcode == OP_BLEZ ||
	      opcode == OP_BLTZ || opcode == OP_BLTZAL) {
    	args[0] = getOpnd(ip, 0);
    	args[1] = branchTarget(addr + 4, getOpnd(ip, 1));
    } else if(opcode == OP_UNIMP) {
	   printf("Unrecognized instruction (0x%x)", ip->value);
    } else {
    	args[0] = getOpnd(ip, 0);
    	args[1] = getOpnd(ip, 1);
    	args[2] = getOpnd(ip, 2);
    }

    // TODO: Error return?
    return 1;
}

static int oneInstruction(unsigned int addr)
{
    Instruction ins;
    if((ins.value = read_int()) == -1)
	   return -1;
    decode(&ins, addr);  // TODO: Possibly error return here
    //printf("%08x %08x ", addr, value);
    printf(ins.info->format, ins.args[0], ins.args[1], ins.args[2]);
    putchar('\n');
    return 0;
}

/**
 * @brief Decodes the binary code for a MIPS machine instruction.
 * @details This function takes a pointer to an Instruction structure
 * whose "value" field has been initialized to the binary code for
 * MIPS machine instruction and it decodes the instruction to obtain
 * details about the type of instruction and its arguments.
 * The decoded information is returned by setting the other fields
 * of the Instruction structure.
 *
 * @param ip The Instruction structure containing the binary code for
 * a MIPS instruction in its "value" field.
 * @param addr Address at which the instruction appears in memory.
 * The address is used to compute absolute branch addresses from the
 * the PC-relative offsets that occur in the instruction.
 * @return 1 if the instruction was successfully decoded, 0 otherwise.
 * @modifies the fields other than the "value" field to contain the
 * decoded information about the instruction.
 */
// TODO: deal with endianness
int disassemble(void)
{
    unsigned int addr = global_options & BASE_ADDR_MASK;
    while(oneInstruction(addr) >= 0)
	   addr += 4;

    // TODO: error return.
    return 1;
}
