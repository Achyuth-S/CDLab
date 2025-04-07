#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    int currentChar;

    // Open the input file in read mode
    inputFile = fopen("input.c", "r");
    if (inputFile == NULL) {
        printf("Cannot open input file.\n");
        exit(1);
    }

    // Open the output file in write mode
    outputFile = fopen("output.c", "w");
    if (outputFile == NULL) {
        printf("Cannot open output file.\n");
        fclose(inputFile);
        exit(1);
    }

    // Read characters from the input file
    while ((currentChar = getc(inputFile)) != EOF) {
        // If the character is '#', discard the entire preprocessor directive line
        if (currentChar == '#') {
            // Skip the entire line
            while (currentChar != '\n' && currentChar != EOF) {
                currentChar = getc(inputFile);
            }
        } else {
            // Write non-preprocessor characters to the output file
            putc(currentChar, outputFile);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Preprocessor directives discarded. Check 'output.c' for the result.\n");
    return 0;
}