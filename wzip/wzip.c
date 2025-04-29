#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    char current_char;
    char next_char;
    unsigned int count = 1;

    // Open the first file for reading
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        return 1;
    }

    // Read the first character
    current_char = fgetc(file);

    for (int i = 1; i < argc; i++) {
        // Open the non first file for reading 
        if (i > 1) {
            file = fopen(argv[i], "r");
            if (!file) {
                return 1;
          }
        }

        // Read the next character of the file
        next_char = fgetc(file);

        while (next_char != EOF) {
            if (current_char == next_char) {
                count++;
            } else {
                // Write the count to stdout as binary format
                fwrite(&count, sizeof(count), 1, stdout);
                printf("%c", current_char);
                count = 1;
            }
            current_char = next_char;
            next_char = fgetc(file);
        }

        // Close the file
        fclose(file);
    }

    // Handle the last character
    if (current_char != EOF) {
        fwrite(&count, sizeof(count), 1, stdout);
        printf("%c", current_char);
    }

    return 0;
}
