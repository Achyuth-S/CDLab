#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100], ch;
    int lines = 0, characters = 0;


    printf("Enter the file name: ");
    scanf("%s", filename);


    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s.\n", filename);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        characters++; 
        if (ch == '\n') {
            lines++; 
        }
    }


    if (characters > 0 && ch != '\n') {
        lines++;
    }


    fclose(file);

    printf("Total number of lines: %d\n", lines);
    printf("Total number of characters: %d\n", characters);

    return 0;
}