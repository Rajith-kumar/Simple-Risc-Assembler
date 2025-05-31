#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_OPCODES 25  // Reduced to match SimpleRISC ISA
#define MAX_LINE 100

typedef struct {
    char mnemonic1[6];
   
    char binary[6];
} OpcodeTable1;
typedef struct {
   
    char mnemonic2[6];
    char binary[6];
} OpcodeTable2;
typedef struct {
   
    char mnemonic3[6];
    char binary[6];
} OpcodeTable3;
typedef struct {
    
    char mnemonic4[6];
    char binary[6];
} OpcodeTable4;
typedef struct {
    
    char mnemonic5[6];
    char binary[6];
} OpcodeTable5;
typedef struct {
    
    char mnemonic6[6];
    char binary[6];
} OpcodeTable6;

OpcodeTable1 opcodes1[NUM_OPCODES] = {
    {"add", "00000"}, {"sub", "00001"}, {"mul", "00010"}, {"div", "00011"},
    {"mod", "00100"}, {"and", "00110"}, {"or", "00111"}, {"lsl", "01010"},
    {"lsr", "01011"}, {"asr", "01100"}
};
OpcodeTable2 opcodes2[NUM_OPCODES] = {
    {"ld","01110"},{"st","01111"}
};
OpcodeTable3 opcodes3[NUM_OPCODES] = {
    {"not","01000"},{"mov","01001"}
};
OpcodeTable4 opcodes4[NUM_OPCODES] = {
    {"cmp","00101"}
};
OpcodeTable5 opcodes5[NUM_OPCODES] = {
    {"nop","01101"},{"ret","10100"}
};
OpcodeTable6 opcodes6[NUM_OPCODES] = {
    {"beq","10000"},{"bgt","10001"},{"b","10010"},{"call","10011"}
};
// Get opcode binary
const char* getOpcodeBinary1(char *mnemonic1) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes1[i].mnemonic1, mnemonic1) == 0) {
            return opcodes1[i].binary;
        }
    }
    return NULL;
}
const char* getOpcodeBinary2(char *mnemonic2) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes2[i].mnemonic2, mnemonic2) == 0) {
            return opcodes2[i].binary;
        }
    }
    return NULL;
}
const char* getOpcodeBinary3(char *mnemonic3) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes3[i].mnemonic3, mnemonic3) == 0) {
            return opcodes3[i].binary;
        }
    }
    return NULL;
}
const char* getOpcodeBinary4(char *mnemonic4) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes4[i].mnemonic4, mnemonic4) == 0) {
            return opcodes4[i].binary;
        }
    }
    return NULL;
}
const char* getOpcodeBinary5(char *mnemonic5) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes5[i].mnemonic5, mnemonic5) == 0) {
            return opcodes5[i].binary;
        }
    }
    return NULL;
}
const char* getOpcodeBinary6(char *mnemonic6) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes6[i].mnemonic6, mnemonic6) == 0) {
            return opcodes6[i].binary;
        }
    }
    return NULL;
}
// Convert register to 4-bit binary
const char* getRegisterBinary(char *reg) {
    if (strcmp(reg, "R0") == 0||strcmp(reg, "r0") == 0) return "0000";
    if (strcmp(reg, "R1") == 0||strcmp(reg, "r1") == 0) return "0001";
    if (strcmp(reg, "R2") == 0||strcmp(reg, "r2") == 0) return "0010";
    if (strcmp(reg, "R3") == 0||strcmp(reg, "r3") == 0) return "0011";
    if (strcmp(reg, "R4") == 0||strcmp(reg, "r4") == 0) return "0100";
    if (strcmp(reg, "R5") == 0||strcmp(reg, "r5") == 0) return "0101";
    if (strcmp(reg, "R6") == 0||strcmp(reg, "r6") == 0) return "0110";
    if (strcmp(reg, "R7") == 0||strcmp(reg, "r7") == 0) return "0111";
    if (strcmp(reg, "R8") == 0||strcmp(reg, "r8") == 0) return "1000";
    if (strcmp(reg, "R9") == 0||strcmp(reg, "r9") == 0) return "1001";
    if (strcmp(reg, "R10") == 0||strcmp(reg, "r10") == 0) return "1010";
    if (strcmp(reg, "R11") == 0||strcmp(reg, "r11") == 0) return "1011";
    if (strcmp(reg, "R12") == 0||strcmp(reg, "r12") == 0) return "1100";
    if (strcmp(reg, "R13") == 0||strcmp(reg, "r13") == 0) return "1101";
    if (strcmp(reg, "R14") == 0||strcmp(reg, "r14") == 0) return "1110";
    if (strcmp(reg, "R15") == 0||strcmp(reg, "r15") == 0) return "1111";
    return NULL;
}

// Convert an integer to an 18-bit binary string
void intToBinary(int num, int bits, char *output) {
    for (int i = bits - 1; i >= 0; i--) {
        output[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
    output[bits] = '\0';
}

// Check if a string is an integer (for immediate values)
int isNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-') {
            return 0;
        }
    }
    return 1;
}

// Assemble a single instruction
void assembleInstruction(char *instruction, FILE *outfile) {
    char mnemonic[10], rd[5], rs1[5], rs2imm[10];
    char offset[6];
    char binaryInstruction[33] = {0};
    // Read input with commas
    int numOperands = sscanf(instruction, "%s %[^,],%[^,],%s", mnemonic, rd, rs1, rs2imm);

    // if (numOperands < 3) {
    //     fprintf(outfile, "Error: Invalid instruction format: %s\n", instruction);
    //     return;
    // }

    const char *opcodeBin1 = getOpcodeBinary1(mnemonic);
    const char *opcodeBin2 = getOpcodeBinary2(mnemonic);
    const char *opcodeBin3 = getOpcodeBinary3(mnemonic);
    const char *opcodeBin4 = getOpcodeBinary4(mnemonic);
    const char *opcodeBin5 = getOpcodeBinary5(mnemonic);
    const char *opcodeBin6 = getOpcodeBinary6(mnemonic);
   
    // if (!opcodeBin1) {
    //     fprintf(outfile, "Error: Invalid opcode '%s' in instruction: %s\n", mnemonic1, instruction);
    //     return;
    // }

    const char *rdBin = getRegisterBinary(rd);
    const char *rs1Bin = getRegisterBinary(rs1);
    // char binaryInstruction[33] = {0};
    if(opcodeBin1){

    if (numOperands!=4){
        fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
        return;
    }
    // if (!rdBin || !rs1Bin) {
    //     fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
    //     return;
    // }
    // const char *rs3Bin = getRegisterBinary(rschk);
    // if (rs3Bin) {
    //     fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
    //     return;
    // }
    //LIMITATION
    // const char *rs2Bin = getRegisterBinary(rs2imm);
    // if (!rs2Bin) {
    //         fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
    //         return;
    //     }
    if (!rdBin || !rs1Bin) {
        fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
        return;
    }

    

    if (isNumber(rs2imm)) { // I-Type Instruction
        int immValue = atoi(rs2imm);
        char immBin[17];
        intToBinary(immValue, 16, immBin);
        sprintf(binaryInstruction, "%s1%s%s01%s", opcodeBin1, rdBin, rs1Bin, immBin);
    } else { // R-Type Instruction
        const char *rs2Bin = getRegisterBinary(rs2imm);
        if (!rs2Bin) {
            fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
            return;
        }
        sprintf(binaryInstruction, "%s0%s%s%s00000000000000", opcodeBin1, rdBin, rs1Bin, rs2Bin);
    }
    }
    else if(opcodeBin2){
        // if (numOperands!=4){
        //     fprintf(outfile,"Error: Invalid Instruction\n");
        //     return;
        // }
        sscanf(instruction, "%s %[^,],%[^[][%[^]]]", mnemonic, rd, rs2imm, rs1);
        // if (!rdBin || !rs1Bin) {
        //     fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
        //     return;
        // }
    
        
        const char *rdBin = getRegisterBinary(rd);
        const char *rs1Bin = getRegisterBinary(rs1);
        if (isNumber(rs2imm)) { // I-Type Instruction
            int immValue = atoi(rs2imm);
            char immBin[17];
            intToBinary(immValue, 16, immBin);
            sprintf(binaryInstruction, "%s1%s%s01%s", opcodeBin2, rdBin, rs1Bin, immBin);
        } else { // R-Type Instruction
            const char *rs2Bin = getRegisterBinary(rs2imm);
            if (!rs2Bin) {
                fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
                return;
            }
            sprintf(binaryInstruction, "%s0%s%s%s00000000000000", opcodeBin2, rdBin, rs1Bin, rs2Bin);
        }
    }
    else if(opcodeBin3){
        if (!rdBin) {
            fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
            return;
        }
        if (numOperands!=3){
            fprintf(outfile,"Error: Invalid Instruction\n");
            return;
        }
        const char *rs1Bin = getRegisterBinary(rs2imm);
            if(rs1Bin){
                fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
                return;
            }
    
        if (isNumber(rs1)) { // I-Type Instruction
            int immValue = atoi(rs1);
            char immBin[17];
            
            intToBinary(immValue, 16, immBin);
            sprintf(binaryInstruction, "%s1%s000001%s", opcodeBin3, rdBin,immBin);
        } else { // R-Type Instruction
            const char *rs2Bin = getRegisterBinary(rs1);
            if (!rs2Bin) {
                fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
                return;
            }
            
            sprintf(binaryInstruction, "%s0%s0000%s00000000000000", opcodeBin3, rdBin,rs2Bin);
        }
    }
    else if(opcodeBin4){
        if (!rdBin) {
            fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
            return;
        }
        if (numOperands!=3){
            fprintf(outfile,"Error: Invalid Instruction\n");
            return;
        }
        const char *rs1Bin = getRegisterBinary(rs2imm);
            if(rs1Bin){
                fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
                return;
            }
    
        if (isNumber(rs1)) { // I-Type Instruction
            int immValue = atoi(rs1);
            char immBin[17];
            
            intToBinary(immValue, 16, immBin);
            sprintf(binaryInstruction, "%s10000%s01%s", opcodeBin4, rdBin,immBin);
        } else { // R-Type Instruction
            const char *rs2Bin = getRegisterBinary(rs1);
            if (!rs2Bin) {
                fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
                return;
            }
            
            sprintf(binaryInstruction, "%s00000%s%s00000000000000", opcodeBin4, rdBin,rs2Bin);
        }
    }
    else if(opcodeBin5){
        if (numOperands!=1){
            fprintf(outfile,"Error: Invalid Instruction\n");
            return;
        }
        if (rdBin) {
            fprintf(outfile, "Error: Invalid register in instruction: %s\n", instruction);
            return;
        }
        int immValue = 0;
            char immBin[28];
            
            intToBinary(immValue, 27, immBin);
            sprintf(binaryInstruction, "%s%s", opcodeBin5,immBin);
    }
    else if(opcodeBin6){
        sscanf(instruction, "%s %s", mnemonic,offset);
        int immValue = atoi(offset);
        if(immValue>0){
            // int immValue = atoi(offset);
            char immBin[28];
            intToBinary(immValue, 27, immBin);
            sprintf(binaryInstruction, "%s%s", opcodeBin6,immBin);

        }
        if(immValue<0){
            char immBin[28];
            int twoscomp = (1 << 27) + immValue;
            intToBinary(immValue,27,immBin);
            sprintf(binaryInstruction, "%s%s", opcodeBin6,immBin);
        }

    }
//    elseif(numOperands==3){

//    }

    fprintf(outfile, "%s\n", binaryInstruction);
    // printf("%s 1 \n", binaryInstruction);
}


int main() {
    char instruction[30];
    FILE *inputFile = fopen("output.asm", "r");
    FILE *outputFile = fopen("output.bin", "w");

    if (!inputFile) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }
    if (!outputFile) {
        printf("Error: Unable to create output file.\n");
        fclose(inputFile);
        return 1;
    }

    printf("Assembling...\n");

    while (fgets(instruction, sizeof(instruction), inputFile)) {
        instruction[strcspn(instruction, "\n")] = 0;  // Remove newline character
        assembleInstruction(instruction,outputFile);
    }

    printf("Assembly complete. Output written to output.bin\n");
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
