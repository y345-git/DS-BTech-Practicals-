// Write a program to convert infix expression into prefix expression
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return stack[top--];
}

int priority(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

int main() {
    char infix[MAX], prefix[MAX];
    int i, j = 0;
    char ch;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    int len = strlen(infix);
    for (i = len - 1; i >= 0; i--) {
        ch = infix[i];

        if (isalnum(ch)) {
            prefix[j++] = ch;
        } else if (ch == ')') {
            push(ch);
        } else if (ch == '(') {
            while (top != -1 && stack[top] != ')') {
                prefix[j++] = pop();
            }
            pop(); // discard ')'
        } else {
            while (top != -1 && priority(stack[top]) > priority(ch)) {
                prefix[j++] = pop();
            }
            push(ch);
        }
    }

    while (top != -1) {
        prefix[j++] = pop();
    }
    prefix[j] = '\0';

    // Reverse the prefix string to get the final answer
    for (i = 0, j--; i < j; i++, j--) {
        ch = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = ch;
    }

    printf("Prefix expression: %s\n", prefix);
    return 0;
}
