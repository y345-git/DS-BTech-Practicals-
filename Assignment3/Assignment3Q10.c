// Queue ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    void *data;
    char type;             
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

struct Node *makeNode(char *s) {
    struct Node *n;
    int i;
    int isNumber = 1;
    int hasDot = 0;
    int len;

    n = malloc(sizeof(struct Node));

    if (n == NULL)
        return NULL;

    len = strlen(s);

    if (len == 1 && isalpha((unsigned char)s[0])) {
        n->type = 'c';

        n->data = malloc(sizeof(char));

        *(char *)n->data = s[0];
    }

    else {
        for (i = 0; i < len; i++) {

            if (s[i] == '.' && !hasDot)
                hasDot = 1;

            else if (s[i] == '-' && i == 0)
                ;

            else if (!isdigit((unsigned char)s[i])) {
                isNumber = 0;
                break;
            }
        }

        if (isNumber && hasDot) {
            n->type = 'f';

            n->data = malloc(sizeof(float));

            *(float *)n->data = atof(s);
        }

        else if (isNumber) {
            n->type = 'i';

            n->data = malloc(sizeof(int));

            *(int *)n->data = atoi(s);
        }

        else {
            n->type = 's';

            n->data = malloc((len + 1) * sizeof(char));

            strcpy((char *)n->data, s);
        }
    }

    n->next = NULL;

    return n;
}

void printData(struct Node *n) {
    switch (n->type) {

        case 'i':
            printf("%d", *(int *)n->data);
            break;

        case 'f':
            printf("%.2f", *(float *)n->data);
            break;

        case 'c':
            printf("%c", *(char *)n->data);
            break;

        case 's':
            printf("%s", (char *)n->data);
            break;
    }
}

char *readValue() {
    static char s[100];

    printf("Enter value: ");
    scanf("%99s", s);

    return s;
}

int isEmpty() {
    return front == NULL;
}

void enqueue() {
    struct Node *n;

    n = makeNode(readValue());

    if (n == NULL) {
        printf("Queue Overflow\n");
        return;
    }

    if (rear == NULL) {
        front = n;
        rear = n;
    }
    else {
        rear->next = n;
        rear = n;
    }

    printf("Enqueued successfully\n");
}

void dequeue() {
    struct Node *t;

    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }

    t = front;

    printf("Dequeued: ");
    printData(t);
    printf("\n");

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(t->data);
    free(t);
}

void frontElement() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    printf("Front element: ");
    printData(front);
    printf("\n");
}

void rearElement() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    printf("Rear element: ");
    printData(rear);
    printf("\n");
}

void display() {
    struct Node *t;

    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    t = front;

    printf("Queue (front to rear):\n");

    while (t != NULL) {
        printData(t);

        if (t == front)
            printf("  <-- front");

        if (t == rear)
            printf("  <-- rear");

        printf("\n");

        t = t->next;
    }
}

void search() {
    struct Node *t;
    struct Node *key;
    int position = 1;
    int found = 0;

    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    key = makeNode(readValue());

    if (key == NULL) {
        printf("Unable to create search value\n");
        return;
    }

    t = front;

    while (t != NULL) {

        if (t->type == key->type) {

            if (t->type == 'i' &&
                *(int *)t->data == *(int *)key->data) {
                found = 1;
            }

            else if (t->type == 'f' &&
                     *(float *)t->data == *(float *)key->data) {
                found = 1;
            }

            else if (t->type == 'c' &&
                     *(char *)t->data == *(char *)key->data) {
                found = 1;
            }

            else if (t->type == 's' &&
                     strcmp((char *)t->data, (char *)key->data) == 0) {
                found = 1;
            }
        }

        if (found) {
            printf("Value found at position %d\n", position);
            break;
        }

        t = t->next;
        position++;
    }

    if (!found)
        printf("Value not found\n");

    free(key->data);
    free(key);
}

void count() {
    struct Node *t;
    int count = 0;

    t = front;

    while (t != NULL) {
        count++;
        t = t->next;
    }

    printf("Number of elements: %d\n", count);
}

void destroyQueue() {
    struct Node *t;

    while (front != NULL) {
        t = front;

        front = front->next;

        free(t->data);
        free(t);
    }

    rear = NULL;
}

int main() {
    int ch;

    do {
        printf("\nQueue Operations:");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Front");
        printf("\n4. Rear");
        printf("\n5. Display");
        printf("\n6. Search");
        printf("\n7. Count");
        printf("\n8. Exit");

        printf("\nEnter choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");

            while (getchar() != '\n');

            ch = 0;

            continue;
        }

        switch (ch) {

            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                frontElement();
                break;

            case 4:
                rearElement();
                break;

            case 5:
                display();
                break;

            case 6:
                search();
                break;

            case 7:
                count();
                break;

            case 8:
                destroyQueue();
                printf("Queue destroyed\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (ch != 8);

    return 0;
}