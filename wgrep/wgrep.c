#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print lines that match the search term
void print_match_searchterm_lines(const regex_t searchterm, FILE *stream) {
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    while ((nread = getline(&line, &size, stream)) != -1) {
        // Check if the line matches the search term
        if (regexec(&searchterm, line, 0, NULL, 0) == 0) {
            // Print the line to STDOUT
            fwrite(line, nread, 1, stdout);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    // Compile the regex from the search term
    regex_t regex;
    int reti = regcomp(&regex, argv[1], 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // If no files are provided, read from stdin
    if (argc == 2) {
        print_match_searchterm_lines(regex, stdin);
    }

    // Iterate over each file provided in the command line arguments
    for (int i = 2; i < argc; i++) {
        // Open the file for reading
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        print_match_searchterm_lines(regex, file);

        // Close the file
        fclose(file);
    }

    return 0;
}
