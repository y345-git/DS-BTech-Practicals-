// Write a algorithm and program to represent given polynomial as linked list and write function to add/substract two polynomial
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff, power;
    struct Node *next;
};

struct Node *p1 = NULL, *p2 = NULL;

void create1() {
    struct Node *newNode, *temp;
    int n, i;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));

        printf("Enter coefficient and power: ");
        scanf("%d %d", &newNode->coeff, &newNode->power);

        newNode->next = NULL;

        if (p1 == NULL) {
            p1 = newNode;
        }
        else {
            temp = p1;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }
}

void create2() {
    struct Node *newNode, *temp;
    int n, i;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));

        printf("Enter coefficient and power: ");
        scanf("%d %d", &newNode->coeff, &newNode->power);

        newNode->next = NULL;

        if (p2 == NULL) {
            p2 = newNode;
        }
        else {
            temp = p2;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }
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
        }
        else if (a->power > b->power) {
            printf("%dx^%d + ", a->coeff, a->power);
            a = a->next;
        }
        else {
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
        }
        else if (a->power > b->power) {
            printf("%dx^%d + ", a->coeff, a->power);
            a = a->next;
        }
        else {
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
    create1();

    printf("\nEnter Second Polynomial:\n");
    create2();

    printf("\nFirst Polynomial: ");
    display(p1);

    printf("Second Polynomial: ");
    display(p2);

    add();
    subtract();

    return 0;
}