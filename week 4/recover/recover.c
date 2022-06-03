#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Struct size of 512 bytes
typedef uint8_t BYTE;

// Size of each BLOCK in bytes
#define BLOCK 512

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open memory file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Store 512 bytes block
    BYTE buffer[BLOCK];

    bool jpeg_found = false;
    char file_name[8];
    FILE *img;

    // Initialize img file count to 0
    int img_count = 0;

    // Iterate until EOF
    while (fread(buffer, 512, 1, file))
    {
        // Check for file header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the file if already found
            if (jpeg_found)
            {
                fclose(img);
            }

            // Create a new file name
            sprintf(file_name, "%03i.jpg", img_count);

            // Open a new file with that file name
            img = fopen(file_name, "w");

            jpeg_found = true;
            img_count++;
        }

        // Write data to the file
        fwrite(buffer, 512, 1, img);
    }

    // Close the last file
    fclose(img);

    // Close infile
    fclose(file);

    // Success
    return 0;
}
