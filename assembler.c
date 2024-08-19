#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "assembler.h"

size_t putBytes(unsigned short bytes, unsigned char **arr, size_t index, size_t size)
{
    int result = size;

    if (index + 2 > size)
    {
        unsigned char *temp = malloc(2*size);
        if (temp == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
        memcpy(temp, *arr, size);
        free(*arr);

        result = 2 * size;
    }

    (*arr)[index] = (bytes >> 8) & 0xff;
    (*arr)[index + 1] = bytes & 0xff;

    return result;
}

void shrink(unsigned char **arr, size_t newlen)
{
    unsigned char *temp = malloc(newlen);
    if (temp == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    memcpy(temp, *arr, newlen);
    free(*arr);
    *arr = temp;
}

void output(FILE *f, unsigned char *data, size_t datac)
{
    for (size_t i = 0; i < datac/2; i++)
    {
        unsigned short code = (data[2*i] << 8) + (data[2*i+1]);
        char temp[18];
        temp[16] = '\n';
        temp[17] = '\0';

        for (size_t j = 0; j < 16; j++)
        {
            temp[j] = (code >> 15-j) & 1 ? '1' : '0';
        }

        fprintf(f, "%s", temp);
    }
}

size_t assemble(FILE *f, unsigned char **out)
{
    char buff[256];
    int i = 0;
    int n = 0;
    int c;
    int firstPass = 1;  // for later

    // room for 32 instructions
    unsigned char *result = malloc(64);
    size_t r_size = 64;

    do {
        c = fgetc(f);

        if (c != '\n')
        {
            if (i >= 256)
            {
                fprintf(stderr, "Line %d too long (max 256), buffer overflow\n", n);
                exit(1);
            }

            buff[i] = c;
            i++; 
        }
        else 
        {
            buff[i] = '\0';
            i = 0;

            instruction *op = parseInstructions(buff);

            if (op != NULL)
            {
                unsigned short data;
                if (op->type == A)
                {
                    data = op->literal;
                    data = data & 0x7fff;
                }      
                else 
                {
                    data = (0x7 << 13) + (op->comp << 6) + (op->dest << 3) + op->jump;
                }

                r_size = putBytes(data, &result, n*2, r_size);
                free(op);

                n++;
            }
        }
        
    }
    while(c != EOF);

    shrink(&result, n*2);
    *out = result;

    return 2*n;
}