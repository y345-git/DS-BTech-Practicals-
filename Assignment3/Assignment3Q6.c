// Write c program to convert decimal to binary using stack 
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
    int decimal, binary;

    printf("Enter decimal number: ");
    scanf("%d", &decimal);

    if (decimal == 0) {
        printf("Binary number: 0\n");
        return 0;
    }

    while (decimal > 0) {
        push(decimal % 2);
        decimal = decimal / 2;
    }

    printf("Binary number: ");

    while (top != -1) {
        binary = pop();
        printf("%d", binary);
    }

    printf("\n");

    return 0;
}