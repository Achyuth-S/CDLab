#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    int currentChar, prevChar = 0; 

    inputFile = fopen("input", "r");
    if (inputFile == NULL) {
        printf("Cannot open input file.\n");
        exit(1);
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Cannot open output file.\n");
        fclose(inputFile);
        exit(1);
    }

    while ((currentChar = getc(inputFile)) != EOF) {

        if (currentChar == ' ' || currentChar == '\t') {
            if (prevChar != ' ') {
                putc(' ', outputFile); // Write a single space to output
            }
        } else {
            putc(currentChar, outputFile); 
        }
        prevChar = currentChar; 
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Spaces and tabs replaced. Check 'output.txt' for the result.\n");
    return 0;
}