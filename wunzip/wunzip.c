#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    char current_char;
    unsigned int count;

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            return 1;
        }

        // Read the first pair of count and character
        if (fread(&count, sizeof(count), 1, file) == 1) {
            current_char = fgetc(file);
            if (current_char == EOF) {
                fclose(file);
            }
        } else {
            fclose(file);
        }

        while (current_char != EOF) {
            // Print the character 'count' times
            for (unsigned int j = 0; j < count; j++) {
                printf("%c", current_char);
            }

            // Read the next pair of count and character
            if (fread(&count, sizeof(count), 1, file) == 1) {
                current_char = fgetc(file);
                if (current_char == EOF) {
                    fclose(file);
                    break;
                }
            } else {
                fclose(file);
                break;
            }
        }
        
        // Close the file
        fclose(file);
    }


    return 0;
}
