%{
#include <stdio.h>

int vowel_count = 0;
int consonant_count = 0;
%}

%%

[aeiouAEIOU]    { vowel_count++; }  // Count vowels
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]  { consonant_count++; }  // Count consonants

.|\n   { } // Ignore other characters (e.g., punctuation, spaces, digits)

%%
int yywrap (){

    return 1;
}
int main(int argc, char **argv) {
    // Call yylex() to process the input
    yylex();  // Process the entire input (stdin)

    // Output the vowel and consonant counts
    printf("Vowels: %d\n", vowel_count);
    printf("Consonants: %d\n", consonant_count);

    return 0;
}

