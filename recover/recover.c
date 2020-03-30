#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // symbolize buffer's datatype
    typedef uint8_t byte;

    // ensure proper usage
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover forensicImage\n");
        return 1;
    }

    // open the forensic image
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }


    byte buffer[512];
    int isOpened = 0;     //no jpeg file is opened initially

    // set up for output files
    int filenumber = 0;
    char *filename = malloc(sizeof(char) * 8);
    FILE *outfile;

    while (fread(buffer, 1, 512, infile) == 512)
    {
        // flag the beginning of a JPEG file
        int startJPEG = (buffer[0] == 0xff &&
                         buffer[1] == 0xd8 &&
                         buffer[2] == 0xff &&
                         (buffer[3] & 0xf0) == 0xe0);

        if (startJPEG == 1)
        {
            if (isOpened == 0) {
                // create a new JPEG
                sprintf(filename, "%03i.jpg", filenumber);
                outfile = fopen(filename, "w");

                // write to the new file
                fwrite(buffer, 512, 1, outfile);

                // update open status
                isOpened = 1;
            }
            else {
                // close the current file
                fclose(outfile);
                filenumber++;

                // open a new JPEG
                sprintf(filename, "%03i.jpg", filenumber);
                outfile = fopen(filename, "w");

                // write to the new file
                fwrite(buffer, 512, 1, outfile);
            }
        }
        else{
            if (isOpened == 1) {
                fwrite(buffer, 512, 1, outfile);
            }
        }
    }

    if (isOpened == 1) {
        fclose(outfile);
    }


    free(filename);

    return 0;
}
