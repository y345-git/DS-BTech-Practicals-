// Write a program to convert  infix expression into postfix expression.  
#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    top++;
    stack[top] = ch;
}

char pop() {
    return stack[top--];
}

int priority(char ch) {
    if (ch == '^') {
        return 3;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '+' || ch == '-') {
        return 1;
    }

    return 0;
}

int main() {
    char infix[MAX], postfix[MAX];
    int i, j = 0;
    char ch;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    for (i = 0; i < strlen(infix); i++) {
        ch = infix[i];

        // Check for operand
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9')) {

            postfix[j] = ch;
            j++;
        }

        else if (ch == '(') {
            push(ch);
        }

        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j] = pop();
                j++;
            }

            pop();
        }

        else {
            while (top != -1 && priority(stack[top]) >= priority(ch)) {
                postfix[j] = pop();
                j++;
            }

            push(ch);
        }
    }

    while (top != -1) {
        postfix[j] = pop();
        j++;
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);

    return 0;
}