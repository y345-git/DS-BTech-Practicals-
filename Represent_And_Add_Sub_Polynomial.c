// Write a program to represent polynomials as linked lists and add/subtract two polynomials
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff, power;
    struct Node *next;
};

struct Node *p1 = NULL, *p2 = NULL;

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

void display(struct Node *p) {
    while (p != NULL) {
        printf("%dx^%d", p->coeff, p->power);
        if (p->next != NULL) {
            printf(" + ");
        }
        p = p->next;
    }
    printf("\n");
}

void add() {
    struct Node *a = p1, *b = p2;
    printf("Addition: ");

    while (a != NULL && b != NULL) {
        if (a->power == b->power) {
            printf("%dx^%d + ", a->coeff + b->coeff, a->power);
            a = a->next;
            b = b->next;
        } else if (a->power > b->power) {
            printf("%dx^%d + ", a->coeff, a->power);
            a = a->next;
        } else {
            printf("%dx^%d + ", b->coeff, b->power);
            b = b->next;
        }
    }

    while (a != NULL) {
        printf("%dx^%d + ", a->coeff, a->power);
        a = a->next;
    }

    while (b != NULL) {
        printf("%dx^%d + ", b->coeff, b->power);
        b = b->next;
    }

    printf("\n");
}

void subtract() {
    struct Node *a = p1, *b = p2;
    printf("Subtraction: ");

    while (a != NULL && b != NULL) {
        if (a->power == b->power) {
            printf("%dx^%d + ", a->coeff - b->coeff, a->power);
            a = a->next;
            b = b->next;
        } else if (a->power > b->power) {
            printf("%dx^%d + ", a->coeff, a->power);
            a = a->next;
        } else {
            printf("%dx^%d + ", -b->coeff, b->power);
            b = b->next;
        }
    }

    while (a != NULL) {
        printf("%dx^%d + ", a->coeff, a->power);
        a = a->next;
    }

    while (b != NULL) {
        printf("%dx^%d + ", -b->coeff, b->power);
        b = b->next;
    }

    printf("\n");
}

int main() {
    printf("Enter First Polynomial:\n");
    p1 = create();

    printf("\nEnter Second Polynomial:\n");
    p2 = create();

    printf("\nFirst Polynomial: ");
    display(p1);

    printf("Second Polynomial: ");
    display(p2);

    add();
    subtract();

    return 0;
}
