// Write a program to convert infix expression into prefix expression.  

#include <stdio.h>

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
    char infix[MAX], prefix[MAX];
    int i, j = 0;
    char ch;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    for (i = 0; infix[i] != '\0'; i++) {
    }

    i--;

    while (i >= 0) {
        ch = infix[i];

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9')) {

            prefix[j++] = ch;
        }
        else if (ch == ')') {
            push(ch);
        }
        else if (ch == '(') {
            while (top != -1 && stack[top] != ')') {
                prefix[j++] = pop();
            }
            pop();
        }
        else {
            while (top != -1 && priority(stack[top]) > priority(ch)) {
                prefix[j++] = pop();
            }

            push(ch);
        }

        i--;
    }

    while (top != -1) {
        prefix[j++] = pop();
    }

    prefix[j] = '\0';

    for (i = 0, j = j - 1; i < j; i++, j--) {
        ch = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = ch;
    }

    printf("Prefix expression: %s\n", prefix);

    return 0;
}