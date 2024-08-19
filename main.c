#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "assembler.h"

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

        size_t outlen;
        unsigned char *out;
        outlen = assemble(input, &out);
        fclose(input);

        FILE *outfile;
        char outfilename[64];
        char ext[8];
        sscanf(argv[1], "%[^.].%s", outfilename, ext);
        strcpy(ext, "hack");

        sprintf(outfilename, "%s.%s", outfilename, ext);
        outfile = fopen(outfilename, "w");

        output(outfile, out, outlen);
        fclose(outfile);
        free(out);
    }
    else
    {
        printf("Usage: %s [filename]\n", argv[0]);
    }

    return 0;

}