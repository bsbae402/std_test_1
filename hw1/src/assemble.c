#include <stdio.h>

#include "debug.h"
#include "hw1.h"

// Do I want them to use any arrays?  Why or why not?
// I definitely want to avoid the use of malloc.
// I don't want them to use string library (strcmp, etc.)

#define LINE_LENGTH 64

//// storing std input (human readable instr)
char line[LINE_LENGTH+1];

static int readline()
{
    int c;
    char *lp = line;
    while((c = getchar()) != -1 && c != '\n') {
	   *lp++ = c;
    }
    *lp = '\0';
    if(c == -1 && lp == line)
	   return -1;
    else
	   return(lp - line);
}

static int strcmp(const char *s1, const char *s2) {
    while(*s1 == *s2) {
    	if(*s1 == '\0')
    	    return 1;
    	s1++; s2++;
    }
    return 0;
}

static int findSpecial(int opcode) {
    // TODO: get rid of constant here
    for(int i = 0; i < 64; i++) {
    	if(specialTable[i] == opcode)
    	    return i;
    }
    return -1;
}

static Opcode getOpcode(int opcode) {
    // TODO: get rid of constant here
    for(int i = 0; i < 64; i++) {
    	if(opcodeTable[i] == opcode)
    	    return i;
    }
    return ILLEGL;
}

static int setArg(int instr, const Instr_info *ip, int *args, int i) {
    switch(ip->srcs[i]) {
        case RS:
        	debug("instr=0x%08x, RS=%d", instr, args[i]);
        	return instr | ((args[i] & 0x1f) << 21);
        case RT:
        	debug("instr=0x%08x, RT=%d", instr, args[i]);
        	return instr | ((args[i] & 0x1f) << 16);
        case RD:
        	debug("instr=0x%08x, RD=%d", instr, args[i]);
        	return instr | ((args[i] & 0x1f) << 11);
        case EXTRA:
        	debug("instr=0x%08x, EXTRA=%d", instr, args[i]);
        	if(ip->opcode == OP_BREAK) {
        	    instr |= (args[i] & 0xfffff) << 6;
        	} else if(ip->type == JTYP) {
        	    instr |= (args[i] & 0xfffffff) >> 2;
        	} else if(ip->type == RTYP) {
        	    instr |= (args[i] & 0x1f) << 6;
        	} else if(ip->type == ITYP) {
        	    instr |= args[i] & 0xffff;
        	} else {
        	    // TODO: Should be an error
        	    //printf("unknown instruction format\n");
        	}
        	return instr;
        default:
        	return instr;  // not an error, no argument
    }
}

static Instr_info *findInstruction(int args[]) {
    // TODO: get rid of magic constant here
    for(int i = 0; i < 64; i++) {
    	Instr_info *ip = &instrTable[i];
    	int n;
    	if((n = sscanf(line, ip->format, &args[0], &args[1], &args[2])) > 0) {
    	    return ip;
    	} else if(n == 0) {
    	    // No-argument case -- scanf will return 0.
    	    // Check for exact match.
    	    if(strcmp(line, ip->format))
    		return ip;
    	}
    }
    return NULL;
}

/**
 * @brief Computes the binary code for a MIPS machine instruction.
 * @details This function takes a pointer to an Instruction structure
 * that contains information defining a MIPS machine instruction and
 * computes the binary code for that instruction.  The code is returne
 * in the "value" field of the Instruction structure.
 *
 * @param ip The Instruction structure containing information about the
 * instruction, except for the "value" field.
 * @param addr Address at which the instruction is to appear in memory.
 * The address is used to compute the PC-relative offsets used in branch
 * instructions.
 * @return 1 if the instruction was successfully encoded, 0 otherwise.
 * @modifies the "value" field of the Instruction structure to contain the
 * binary code for the instruction.
 */
int encode(Instruction *ip, unsigned int addr) {
    unsigned int value = 0;
    Opcode opcode = ip->info->opcode;
    int *args = ip->args;
    int op;
    int spc;
    if((spc = findSpecial(opcode)) >= 0) {
    	op = 0;
    	value |= spc;
    } else if(opcode == OP_BEQ || opcode == OP_BNE) {
    	// TODO: This doesn't read well.
    	op = getOpcode(opcode);
    	args[2] = (args[2] - (addr + 4)) >> 2;
    } else if(opcode == OP_BGEZ || opcode == OP_BGEZAL ||
	      opcode == OP_BGTZ || opcode == OP_BLEZ ||
	      opcode == OP_BLTZ || opcode == OP_BLTZAL) {
    	// TODO: Have to test these BCOND cases.
    	args[1] = args[1] - (addr + 4);
    	args[1] >>= 2;
    	// Strangely, the above is *not* equivalent to:
    	// args[1] = (args[1] - (addr + 4)) >> 2;
    	// I don't know the reason for this.
    	if(opcode == OP_BLTZ) {
    	    op = 1;
    	    value |= 0x0;
    	} else if(opcode == OP_BGEZ) {
    	    op = 1;
    	    value |= 0x10000;
    	} else if(opcode == OP_BLTZAL) {
    	    op = 1;
    	    value |= 0x100000;
    	} else if(opcode == OP_BGEZAL) {
    	    op = 1;
    	    value |= 0x110000;
    	} else {
    	    op = getOpcode(opcode);
    	}
    } else {
	   op = getOpcode(opcode);
    }
    value |= op << 26;
    for(int i = 0; i < 3; i++)
	   value = setArg(value, ip->info, args, i);

    ip->value = value;
    return 1;
}

static int oneLine(unsigned int addr)
{
    Instruction ins;
    ins.args[0] = ins.args[1] = ins.args[2] = 0;
    if(readline() == -1)
	   return -1;
    if((ins.info = findInstruction(ins.args)) == NULL) {
    	// TODO: Should be an error
    	//printf("%s --> NO MATCH\n", line);
    	return 1;
    }
/*
      printf("%s --> %s: %d, %d, %d\n",
	     line, ins.info->format, ins.args[0], ins.args[1], ins.args[2]);
*/
    // TODO: error check
    encode(&ins, addr);
    unsigned int value = ins.value;
    //printf("instruction: 0x%08x\n", value);

    // Output instruction in little-endian format:
    // TODO: handle endianness.
    putchar(value & 0xff);
    putchar((value & 0xff00) >> 8);
    putchar((value & 0xff0000) >> 16);
    putchar((value & 0xff000000) >> 24);

    return 0;
}

// TODO: deal with endianness.
int assemble(void)
{
    unsigned int addr = global_options & BASE_ADDR_MASK;
    while(oneLine(addr) >= 0)
	   addr += 4;
    // TODO: handle assembly errors.
    return 1;
}
