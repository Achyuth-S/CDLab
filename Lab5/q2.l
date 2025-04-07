%{
#include <stdio.h>

int word_count = 0;
int char_count = 0;
int blank_count = 0;
int line_count = 0;
%}

%%

\n              { line_count++; }    // Count lines (new line)
[ \t]           { blank_count++; }   // Count blanks (spaces and tabs)
[a-zA-Z0-9]+    { word_count++; char_count += yyleng; }  // Count words (alphanumeric) and characters
.               { char_count++; }    // Count any other character

%%

int main(int argc, char **argv) {
    // Call yylex() to process the input
    yylex();  // Process the entire input (stdin)

    // Output the counts
    printf("Words: %d\n", word_count);
    printf("Characters: %d\n", char_count);
    printf("Blanks: %d\n", blank_count);
    printf("Lines: %d\n", line_count);

    return 0;
}

