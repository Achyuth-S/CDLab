#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

int main() {
    FILE *file1, *file2, *resultFile;
    char file1Name[100], file2Name[100], resultFileName[100];
    char line[MAX_LINE_SIZE];
    int file1EOF = 0, file2EOF = 0;

    printf("Enter the first file name: ");
    scanf("%s", file1Name);
    printf("Enter the second file name: ");
    scanf("%s", file2Name);
    printf("Enter the resultant file name: ");
    scanf("%s", resultFileName);

    // Open the files
    file1 = fopen(file1Name, "r");
    if (file1 == NULL) {
        printf("Could not open file %s.\n", file1Name);
        return 1;
    }

    file2 = fopen(file2Name, "r");
    if (file2 == NULL) {
        printf("Could not open file %s.\n", file2Name);
        fclose(file1);
        return 1;
    }

    resultFile = fopen(resultFileName, "w");
    if (resultFile == NULL) {
        printf("Could not open file %s.\n", resultFileName);
        fclose(file1);
        fclose(file2);
        return 1;
    }

    // Read and write lines alternatively
    while (!file1EOF || !file2EOF) {
        if (!file1EOF && fgets(line, MAX_LINE_SIZE, file1) != NULL) {
            fputs(line, resultFile);
        } else {
            file1EOF = 1;
        }

        if (!file2EOF && fgets(line, MAX_LINE_SIZE, file2) != NULL) {
            fputs(line, resultFile);
        } else {
            file2EOF = 1;
        }
    }

    // Close the files
    fclose(file1);
    fclose(file2);
    fclose(resultFile);

    printf("Merged lines have been written to %s.\n", resultFileName);

    return 0;
}