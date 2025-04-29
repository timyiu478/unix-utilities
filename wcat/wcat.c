#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_file(const char *filename) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 1;
    }

    // Read and print the file line by line to STDOUT
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
        // Ensure the buffer is cleared for the next line
        memset(buffer, 0, sizeof(buffer));
    }

    // Close the file
    fclose(file);

    return 0;
}

int main(int argc, char *argv[]) {
    // Iterate over each file provided in the command line arguments
    for (int i = 1; i < argc; i++) {
        if (print_file(argv[i]) != 0) {
            printf("wcat: cannot open file\n");
            return 1;
        }
    }

    return 0;
}
