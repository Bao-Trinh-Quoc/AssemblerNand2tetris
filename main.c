#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "assembler.h"

int main(int argc, char *argv[])
{
    if(argc >= 2) {
        FILE *infile;
        infile = fopen(argv[1], "r");
        size_t outlen;
        unsigned char *out;
        outlen = assemble(infile, &out);
        fclose(infile);

        // FILE *outfile;
        // char outfilename[64];
        // char ext[8];
        // sscanf(argv[1], "%[^.].%s", outfilename, ext);
        // strcpy(ext, "hack");

        // sprintf(outfilename, "%s.%s", outfilename, ext);
        // outfile = fopen(outfilename, "w");

        char outfilename[64];
        char ext[8];
        char temp[64];  // Temporary buffer

        sscanf(argv[1], "%[^.].%s", outfilename, ext);
        strcpy(ext, "hack");

        sprintf(temp, "%s.%s", outfilename, ext);  // Use temporary buffer
        strcpy(outfilename, temp);  // Copy back to outfilename

        FILE *outfile = fopen(outfilename, "w");

        output(outfile, out, outlen);
        fclose(outfile);
        free(out);
    }else{
        printf("Usage: %s [filename]\n", argv[0]);
    }

    return 0;

}