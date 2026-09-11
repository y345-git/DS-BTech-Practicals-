// Write a program to evaluate postfix expression using stack 

#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    stack[++top] = value;
}

int pop() {
    return stack[top--];
}

int main() {
    char exp[MAX];
    int i, a, b, result;

    printf("Enter postfix expression: ");
    scanf("%s", exp);

    for (i = 0; exp[i] != '\0'; i++) {

        if (exp[i] >= '0' && exp[i] <= '9') {
            push(exp[i] - '0');
        }
        else {
            b = pop();
            a = pop();

            if (exp[i] == '+') {
                result = a + b;
            }
            else if (exp[i] == '-') {
                result = a - b;
            }
            else if (exp[i] == '*') {
                result = a * b;
            }
            else if (exp[i] == '/') {
                result = a / b;
            }

            push(result);
        }
    }

    printf("Result = %d\n", pop());

    return 0;
}