#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    long fileSize;

    printf("Enter the input file name: ");
    scanf("%s", inputFilename);
    printf("Enter the output file name: ");
    scanf("%s", outputFilename);

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Could not open input file %s.\n", inputFilename);
        return 1;
    }

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Could not open output file %s.\n", outputFilename);
        fclose(inputFile);
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    printf("Size of the file: %ld bytes\n", fileSize);

    // Reverse the contents
    for (long i = fileSize - 1; i >= 0; i--) {
        fseek(inputFile, i, SEEK_SET); // Move the file pointer
        char ch = fgetc(inputFile);   // Read the character
        fputc(ch, outputFile);        // Write it to the output file
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Reversed content has been written to %s.\n", outputFilename);

    return 0;
}