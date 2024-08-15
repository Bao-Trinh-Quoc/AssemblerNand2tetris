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

    // Test the trim function
    char *line = "    Hello, World!    ";
    printf("Before: %s\n", line);
    printf("After: %s\n", trim(line));
}