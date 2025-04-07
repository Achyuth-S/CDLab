#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32

// List of C keywords
const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static", 
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", 
    "while", "for", "if", "else", "goto", "enum", "float", "double", "extern"
};

// Function to check if a word is a C keyword
int is_keyword(const char *word) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // The word is a keyword
        }
    }
    return 0; // The word is not a keyword
}

// Function to convert a string to uppercase
void to_uppercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = toupper(word[i]);
    }
}

int main() {
    FILE *inputFile;
    char word[100];
    int currentChar, i = 0;

    // Open the input C file in read mode
    inputFile = fopen("input.c", "r");
    if (inputFile == NULL) {
        printf("Cannot open input file.\n");
        exit(1);
    }

    // Read characters from the input file
    while ((currentChar = getc(inputFile)) != EOF) {
        // If the current character is a letter or underscore, it might be a keyword
        if (isalnum(currentChar) || currentChar == '_') {
            word[i++] = currentChar;
        } else {
            // End of a word, process it
            if (i > 0) {
                word[i] = '\0'; // Null-terminate the word
                if (is_keyword(word)) {
                    to_uppercase(word); // Convert keyword to uppercase
                    printf("%s ", word);
                } else {
                    printf("%s ", word); // Print the non-keyword word as it is
                }
                i = 0; // Reset word index
            }
            // Print the current non-alphanumeric character (e.g., spaces, operators)
            if (!isalnum(currentChar) && currentChar != '_') {
                putchar(currentChar);
            }
        }
    }

    // Close the input file
    fclose(inputFile);
    return 0;
}