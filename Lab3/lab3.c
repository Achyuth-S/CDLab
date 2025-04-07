#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "for", "while",
    "do", "switch", "case", "break", "continue", "return", "void",
    "static", "struct", "union", "typedef", "enum", "const", "sizeof",
    "default", "goto", "unsigned", "signed", "short", "long", "extern",
    "volatile", "register", "inline"
};
const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(const char *word) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isSpecialSymbol(char ch) {
    char specialSymbols[] = ";,(){}[]";
    for (int i = 0; i < strlen(specialSymbols); i++) {
        if (ch == specialSymbols[i]) {
            return 1;
        }
    }
    return 0;
}

int isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return 0;
        }
    }
    return 1;
}

void getNextToken(FILE *file) {
    char ch;
    char buffer[100];
    int bufferIndex = 0;
    int row = 1, col = 1;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            row++;
            col = 1;
            continue;
        }

        if (isspace(ch)) {
            col++;
            continue;
        }

        if (ch == '/' && (ch = fgetc(file)) == '/') {
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            row++;
            col = 1;
            continue;
        }

        if (ch == '/' && (ch = fgetc(file)) == '*') {
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '*' && (ch = fgetc(file)) == '/') {
                    break;
                }
            }
            continue;
        }

        if (ch == '#') {
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            row++;
            col = 1;
            continue;
        }

        if (ch == '"') {
            bufferIndex = 0;
            buffer[bufferIndex++] = ch;
            while ((ch = fgetc(file)) != '"' && ch != EOF) {
                buffer[bufferIndex++] = ch;
            }
            buffer[bufferIndex++] = '"';
            buffer[bufferIndex] = '\0';
            printf("<%s, STRING_LITERAL, row: %d, col: %d>\n", buffer, row, col);
            col += bufferIndex;
            continue;
        }

        if (strchr("+-*/%", ch)) {
            printf("<%c, ARITHMETIC_OPERATOR, row: %d, col: %d>\n", ch, row, col);
            col++;
            continue;
        }

        if (strchr("<>=!", ch)) {
            char nextCh = fgetc(file);
            if (nextCh == '=') {
                printf("<%c%c, RELATIONAL_OPERATOR, row: %d, col: %d>\n", ch, nextCh, row, col);
                col += 2;
            } else {
                printf("<%c, RELATIONAL_OPERATOR, row: %d, col: %d>\n", ch, row, col);
                ungetc(nextCh, file);
                col++;
            }
            continue;
        }

        if (ch == '&' || ch == '|') {
            char nextCh = fgetc(file);
            if (ch == nextCh) {
                printf("<%c%c, LOGICAL_OPERATOR, row: %d, col: %d>\n", ch, nextCh, row, col);
                col += 2;
            } else {
                ungetc(nextCh, file);
                printf("<%c, INVALID_TOKEN, row: %d, col: %d>\n", ch, row, col);
                col++;
            }
            continue;
        }

        if (isSpecialSymbol(ch)) {
            printf("<%c, SPECIAL_SYMBOL, row: %d, col: %d>\n", ch, row, col);
            col++;
            continue;
        }

        if (isalnum(ch) || ch == '_') {
            bufferIndex = 0;
            while (isalnum(ch) || ch == '_') {
                buffer[bufferIndex++] = ch;
                ch = fgetc(file);
            }
            buffer[bufferIndex] = '\0';
            ungetc(ch, file);

            if (isKeyword(buffer)) {
                printf("<%s, KEYWORD, row: %d, col: %d>\n", buffer, row, col);
            } else if (isNumeric(buffer)) {
                printf("<%s, NUMERIC_CONSTANT, row: %d, col: %d>\n", buffer, row, col);
            } else {
                printf("<%s, IDENTIFIER, row: %d, col: %d>\n", buffer, row, col);
            }
            col += bufferIndex;
            continue;
        }

        printf("<%c, INVALID_TOKEN, row: %d, col: %d>\n", ch, row, col);
        col++;
    }
}

int main() {
    FILE *file = fopen("test.c", "r");
    if (!file) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    getNextToken(file);

    fclose(file);
    return 0;
}