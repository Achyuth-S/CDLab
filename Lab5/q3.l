%{
#include <stdio.h>

int positive_int_count = 0;
int negative_int_count = 0;
int positive_float_count = 0;
int negative_float_count = 0;
%}

%%

[1-9][0-9]*           { positive_int_count++; }  // Positive integers (e.g., 1, 10, 123)
-[1-9][0-9]*          { negative_int_count++; }   // Negative integers (e.g., -1, -10, -123)
[0-9]+\.[0-9]+        { positive_float_count++; }  // Positive floating point (e.g., 1.23, 10.0, 0.01)
-[0-9]+\.[0-9]+       { negative_float_count++; }  // Negative floating point (e.g., -1.23, -10.0, -0.01)

%%

int main(int argc, char **argv) {
    // Call yylex() to process the input
    yylex();  // Process the entire input (stdin)

    // Output the counts
    printf("Positive integers: %d\n", positive_int_count);
    printf("Negative integers: %d\n", negative_int_count);
    printf("Positive floating point numbers: %d\n", positive_float_count);
    printf("Negative floating point numbers: %d\n", negative_float_count);

    return 0;
}

