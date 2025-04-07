#include <stdio.h>
#include <ctype.h>

void identify_operator(char token) {
    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%') {
        printf("%c is an Arithmetic operator.\n", token);
    } else if (token == '>' || token == '<' || token == '=' || token == '!' || token == '>=') {
        printf("%c is a Relational operator.\n", token);
    } else if (token == '&' || token == '|' || token == '^' || token == '!' || token == '~') {
        printf("%c is a Logical operator.\n", token);
    } else {
        printf("%c is not an operator.\n", token);
    }
}

int main() {
    char token;

    printf("Enter a token: ");
    scanf(" %c", &token);

    identify_operator(token);

    return 0;
