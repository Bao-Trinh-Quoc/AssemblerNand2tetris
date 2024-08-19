#ifndef PARSER_H
#define PARSER_H

#define KNF 0xff    // Key not found
#define KERR 0xeff  // Key errror

#if DEBUG == 1
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...) // No-op
#endif

// There are two types of instructions: A and C
typedef enum {A, C} optype;

typedef struct 
{
    optype type;                    // Type of instruction
    // The literal field is used exactly 15 bits of unsigned short
    unsigned short literal:15;      // If A-instruction, it's the literal value #literal
    unsigned short comp:7;          // The 7 bits comp field if C type
    unsigned char dest:3;           // The 3 bits dest field if C type
    unsigned char jump:3;           // The 3 bits jump field if C type
} instruction;


// Symbol table
typedef struct 
{
    char *name;
    unsigned short data;
} kvp; // key-value pair

typedef struct
{
    size_t len;
    kvp list[];
} map; 


/**
    * Parses an instruction from a given line of code.
    * Returns NULL for a blank line or a comment.
    * Otherwise, returns a dynamically allocated instruction struct with the parsed values.
    *
    * If an invalid command is parsed, an error message is printed and the program terminates.
 */
instruction *parseInstructions(char *line);




/** 
    * Remove comments and trims the line.
*/
char *cleanLine(char *line);

/**
    * Remove trailing whitespaces 
    * Return a pointer to the first non-whitespace character
 */
char *trim(char *line);

/**
 * return whether the line is a valid instruction or not
 */
int isValidInstruction(char *line);

/**
 * Parses a c-type instruction (dest=comp;jump) where the fields can be filled
 * only by elements of the respective maps and both dest and comp can be ommited
 * 
 * Assumes the string is a C-type instruction with no whitespace or comments
 * surrounding it (things like dest = comp;\tjump are allowed but not
 * dest=comp;jump\t)
 *
 * Sets comp, dest, and jump to their codes or KNF if that field was not present
 * and KERR if invalid
 */
void parseCType(char *line, unsigned short *comp, unsigned char *dest, unsigned char *jump);

/**
 * returns the value associated with the key in the map 
 * returns KNF if the key is not found
 */
unsigned short getVal(const char *key, const map *list);

#endif // PARSER_H