#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"


/*
    Needed to implement these using Hash tables for speed --- maybe in the future
*/

/* 
    All the possible operations in C-instructions
*/
static const map ops = {
    37, {
    {"0",   42},
    {"1",   63},
    {"-1",  58},
    {"D",   12},
    {"A",   48}, {"M",   112},
    {"!D",  13},
    {"!A",  49}, {"!M",  113},
    {"-D",  15},
    {"-A",  51}, {"-M",  115},
    {"D+1", 31},
    {"1+D", 31},
    {"A+1", 55}, {"M+1", 119},
    {"1+A", 55}, {"1+M", 119},
    {"D-1", 14},
    {"A-1", 50}, {"M-1", 114},
    {"D+A",  2}, {"D+M",  66},
    {"A+D",  2}, {"M+D",  66},
    {"D-A", 19}, {"D-M",  83},
    {"A-D",  7}, {"M-D",  71},
    {"D&A",  0}, {"D&M",  64},
    {"A&D",  0}, {"M&D",  64},
    {"D|A", 21}, {"D|M",  85},
    {"A|D", 21}, {"M|D",  85}
    }
};

static const map jumps = {
    7, {
    {"JGT", 1}, {"JEQ", 2}, {"JGE", 3}, {"JLT", 4},
    {"JNE", 5}, {"JLE", 6}, {"JMP", 7}
    }
};

static const map dests = {
    14, {
    {"M",   1}, {"D",   2}, {"MD",  3}, {"DM",  3}, {"A",   4},
    {"AM",  5}, {"MA",  5}, {"AD",  6}, {"DA",  6}, {"AMD", 7},
    {"ADM", 7}, {"DAM", 7}, {"DMA", 7}, {"MAD", 7}, {"MDA", 7}
    }
};

instruction *parseIntructions(char *line) 
{
    // First, we clean all the whitespaces, comments and empty lines
    return NULL;
}


char *cleanLine(char * line) 
{
    line = trim(line);
    char *comment = strstr(line, "//");
    if (comment != NULL)
    {
        *comment = '\0';
        line = trim(line);
    }

    return line;
}

char *trim(char *line)
{
    while (*line == ' ' || *line == '\t')
    {
        line++;
    }
    return line;
}

int isValidInstruction(char *line)
{
    line = cleanLine(line);
    if (line == NULL || *line == '\0')
    {
        return 0;
    }
    // Handle A-instructions
    if (*line == '@')
    {
        return 1;
    }

    // Handle C-instructions
    return 0;
}

// C-instruction format: dest=comp;jump
void parseCType(char *line, unsigned short *comp, unsigned char *dest, unsigned char *jump) 
{
    *dest = 0;
    *jump = 0;

    char *dpos = strchr(line, '=');
    char *jpos = strchr(line, ';');

    if(jpos != NULL) 
    {
        jpos[0] = '\0';
        jpos++;

        jpos = trim(jpos);

        *jump = getVal(jpos, &jumps);
    }
    else
    {
        *jump = KNF;
    }

    if(dpos != NULL) 
    {
        dpos[0] = '\0';
        dpos++;

        dpos = trim(dpos);
        line = trim(line);

        *dest = getVal(line, &dests);
        *comp = getVal(dpos, &ops);
    }
    else
    {
        *dest = KNF;
        line = trim(line);
        *comp = getVal(line, &ops);
    }    
}

unsigned short getVal(const char *key, const map *list)
{
    for (size_t i = 0; i < list->len; i++)
    {
        if (strcmp(key, list->list[i].name) == 0)
        {
            return list->list[i].data;
        }
    }

    return KERR;
}