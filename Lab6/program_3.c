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
void A();
void B();

void S() {
    if (str[curr] == 'a') {
        curr++;
        A();
        if (str[curr] == 'c') {
            curr++;
            B();
            if (str[curr] == 'e') {
                curr++;
                return;
            } else {
                invalid();
            }
        } else {
            invalid();
        }
    } else {
        invalid();
    }
}

void A() {
    if (str[curr] == 'b') {
        curr++;  // Consume 'b'
        while (str[curr] == 'b') { // Multiple b's
            curr++;  // Consume 'b'
        }
    } else {
        invalid();  // If not 'b', it's invalid
    }
}

void B() {
    if (str[curr] == 'd') {
        curr++;
        return;
    } else {
        invalid();
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
