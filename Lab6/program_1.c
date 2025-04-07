#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void invalid() {
    printf("ERROR\n");
    exit(0);
}

void valid() {
    printf("Valid string\n");
    exit(0);
}

void S();
void T();

void S() {
    if (str[curr] == 'a') {
        curr++;
        return;
    } else if (str[curr] == '>') {
        curr++;
        return;
    } else if (str[curr] == '(') {
        curr++;
        T();
        if (str[curr] == ')') {
            curr++;
            return;
        } else {
            invalid();
        }
    } else {
        invalid();
    }
}

void T() {
    S();
    while (str[curr] == ',') {
        curr++;
        S();
    }
}

int main() {
    printf("Enter a string with $ end character:\n");
    scanf("%s", str);

    S();
    if (str[curr] == '$')
        valid();
    else
        invalid();
    return 0;
}
