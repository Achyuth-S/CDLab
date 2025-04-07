#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ID_LEN 50
#define TABLE_SIZE 100

// Token types
typedef enum { KEYWORD, IDENTIFIER, NUMBER, SYMBOL, END } TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_ID_LEN];
} Token;

// Symbol Table Entry
typedef struct Symbol {
    char name[MAX_ID_LEN];
    struct Symbol* next;
} Symbol;

// Symbol Tables
Symbol* globalSymbolTable[TABLE_SIZE] = {NULL};
Symbol* localSymbolTable[TABLE_SIZE] = {NULL};

// Keywords
const char* keywords[] = {"int", "float", "if", "else", "return", "void", "main"};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Hash Function
unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str)
        hash = (hash * 31) + *str++;
    return hash % TABLE_SIZE;
}

// Insert into Symbol Table
void insertSymbol(Symbol* table[], const char* name) {
    unsigned int index = hash(name);
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->next = table[index];
    table[index] = newSymbol;
}

// Check if Symbol Exists
int lookupSymbol(Symbol* table[], const char* name) {
    unsigned int index = hash(name);
    Symbol* entry = table[index];
    while (entry) {
        if (strcmp(entry->name, name) == 0)
            return 1; // Found
        entry = entry->next;
    }
    return 0; // Not found
}

// Check if a string is a keyword
int isKeyword(const char* str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Lexical Analyzer - getNextToken()
Token getNextToken(FILE* fp) {
    Token token;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        // Skip whitespace
        if (isspace(ch)) continue;

        // Identifiers and Keywords
        if (isalpha(ch)) {
            char buffer[MAX_ID_LEN] = {ch};
            int i = 1;
            while (isalnum(ch = fgetc(fp)) && i < MAX_ID_LEN - 1)
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);

            strcpy(token.value, buffer);
            token.type = isKeyword(buffer) ? KEYWORD : IDENTIFIER;
            return token;
        }

        // Numbers
        if (isdigit(ch)) {
            char buffer[MAX_ID_LEN] = {ch};
            int i = 1;
            while (isdigit(ch = fgetc(fp)) && i < MAX_ID_LEN - 1)
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);

            strcpy(token.value, buffer);
            token.type = NUMBER;
            return token;
        }

        // Symbols
        token.value[0] = ch;
        token.value[1] = '\0';
        token.type = SYMBOL;
        return token;
    }

    // End of file
    token.type = END;
    return token;
}

// Process tokens and manage symbol tables
void processTokens(FILE* fp) {
    Token token;
    int inFunction = 0; // Track local/global scope

    while ((token = getNextToken(fp)).type != END) {
        if (token.type == IDENTIFIER) {
            if (inFunction) {
                if (!lookupSymbol(localSymbolTable, token.value))
                    insertSymbol(localSymbolTable, token.value);
            } else {
                if (!lookupSymbol(globalSymbolTable, token.value))
                    insertSymbol(globalSymbolTable, token.value);
            }
        } else if (token.type == KEYWORD) {
            if (strcmp(token.value, "void") == 0 || strcmp(token.value, "int") == 0) {
                inFunction = 1; // Entering function scope
            } else if (strcmp(token.value, "return") == 0) {
                inFunction = 0; // Exiting function scope
            }
        }
    }
}

// Print Symbol Table
void printSymbolTable(Symbol* table[], const char* name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* entry = table[i];
        while (entry) {
            printf("%s\n", entry->name);
            entry = entry->next;
        }
    }
}

// Main function
int main() {
    FILE* fp = fopen("test.c", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    processTokens(fp);
    fclose(fp);

    printSymbolTable(globalSymbolTable, "Global Symbol Table");
    printSymbolTable(localSymbolTable, "Local Symbol Table");

    return 0;
}