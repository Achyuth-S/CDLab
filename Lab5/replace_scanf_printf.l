%{
#include <stdio.h>

int scanf_count = 0;
int printf_count = 0;
%}

%%

"scanf"    { 
                printf_count++; 
                printf("READ");  // Replace scanf with READ
            }

"printf"   { 
                scanf_count++; 
                printf("WRITE");  // Replace printf with WRITE
            }

.|\n       { printf("%c", yytext[0]); }  // Copy all other characters as is

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    // Set the input file for lex to process
    yyin = input_file;

    // Process the file with yylex
    yylex();

    // Output the counts
    printf("\nNumber of 'scanf' replaced: %d\n", scanf_count);
    printf("Number of 'printf' replaced: %d\n", printf_count);

    fclose(input_file);

    return 0;
}

