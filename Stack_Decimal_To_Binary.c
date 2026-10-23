// Write a C program to convert decimal to binary using stack
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
    int decimal;

    printf("Enter decimal number: ");
    scanf("%d", &decimal);

    // Using do-while naturally handles 0 as well as positive numbers
    do {
        push(decimal % 2);
        decimal /= 2;
    } while (decimal > 0);

    printf("Binary number: ");
    while (top != -1) {
        printf("%d", pop());
    }
    printf("\n");

    return 0;
}
