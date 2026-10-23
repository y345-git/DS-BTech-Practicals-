// Write a program to represent a given polynomial as a linked list and evaluate it
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int coeff, power;
    struct Node *next;
};

struct Node *create() {
    struct Node *head = NULL, *temp = NULL, *newNode;
    int n, i;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));
        printf("Enter coefficient and power: ");
        scanf("%d %d", &newNode->coeff, &newNode->power);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;
    }
    return head;
}

void display(struct Node *head) {
    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->power);
        if (head->next != NULL) {
            printf(" + ");
        }
        head = head->next;
    }
    printf("\n");
}

int evaluate(struct Node *head, int x) {
    int result = 0;
    while (head != NULL) {
        result += head->coeff * (int)pow(x, head->power);
        head = head->next;
    }
    return result;
}

int main() {
    struct Node *poly;
    int x;

    poly = create();

    printf("\nPolynomial: ");
    display(poly);

    printf("Enter value of x: ");
    scanf("%d", &x);

    printf("Value of polynomial = %d\n", evaluate(poly, x));

    return 0;
}
