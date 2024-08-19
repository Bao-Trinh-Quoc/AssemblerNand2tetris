#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

int main(int argc, char *argv[])
{
    // if (argc >= 2)
    // {
    //     // Handle I/O files
    //     FILE *input = fopen(argv[1], "r");

    //     if (input == NULL)
    //     {
    //         printf("Cannot open file %s\n", argv[1]);
    //         return 1;
    //     }



    // }
    // else
    // {
    //     printf("Usage: %s [filename]\n", argv[0]);
    // }


    // Write tests for parseCType
    // char line1[] = "D=M;JGT";
    // unsigned short comp;
    // unsigned char dest;
    // unsigned char jump;
    // parseCType(line1, &comp, &dest, &jump);

    // printf("Line: %s\n", line1);
    // printf("Comp: %d\n", comp);
    // printf("Dest: %d\n", dest);
    // printf("Jump: %d\n", jump);

    // Write tests for cleanLine
    // char line3[] = "D=M // This is a comment";
    // char *result3 = cleanLine(line3);
    // printf("Line: %s\n", result3);
    
    // Write tests for isValidInstruction
    // printf("isValidInstruction: %d\n", isValidInstruction("@2"));
    // printf("isValidInstruction: %d\n", isValidInstruction("D=M;JGT"));
    // printf("isValidInstruction: %d\n", isValidInstruction("D;JGT"));
    // printf("isValidInstruction: %d\n", isValidInstruction("       D;JGT  "));
    // printf("isValidInstruction: %d\n", isValidInstruction("=M;JGT"));
    // printf("isValidInstruction: %d\n", isValidInstruction("// This is a comment"));

    // Write tests for parseInstruction
    // Test empty line
    // instruction *instr = parseInstructions("");
    // if (instr == NULL) {
    //     printf("Test empty line passed.\n");
    // } else {
    //     printf("Test empty line failed.\n");
    // }

    // // Test comment line
    // instr = parseInstructions("// This is a comment");
    // if (instr == NULL) {
    //     printf("Test comment line passed.\n");
    // } else {
    //     printf("Test comment line failed.\n");
    // }

    // Test valid A-instruction
    instruction *instr = parseInstructions("@123");
    if (instr != NULL && instr->type == A && instr->literal == 123) {
        printf("Test valid A-instruction passed.\n");
    } else {
        printf("Test valid A-instruction failed.\n");
    }
    free(instr);

    // Test invalid A-instruction (out of bounds)
    // instr = parseInstructions("@32768");
    // if (instr == NULL) {
    //     printf("Test invalid A-instruction (out of bounds) passed.\n");
    // } else {
    //     printf("Test invalid A-instruction (out of bounds) failed.\n");
    // }
    // free(instr);

    // Test valid C-instruction
    // instr = parseInstructions("D=A");
    // DEBUG_PRINT("instr->type: %d\n", instr->type);
    // DEBUG_PRINT("instr->comp: %d\n", instr->comp);
    // DEBUG_PRINT("instr->dest: %d\n", instr->dest);
    // DEBUG_PRINT("instr->jump: %d\n", instr->jump);
    // free(instr);

    // Test invalid C-instruction
    instr = parseInstructions("D=Z");
    if (instr == NULL) {
        printf("Test invalid C-instruction passed.\n");
    } else {
        printf("Test invalid C-instruction failed.\n");
    }
    free(instr);

    return 0;
}