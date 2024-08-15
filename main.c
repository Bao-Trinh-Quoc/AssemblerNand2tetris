#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        // Handle I/O files
        FILE *input = fopen(argv[1], "r");

        if (input == NULL)
        {
            printf("Cannot open file %s\n", argv[1]);
            return 1;
        }

    }
    else
    {
        printf("Usage: %s [filename]\n", argv[0]);
    }
}