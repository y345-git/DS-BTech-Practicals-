// Queue ADT (Generic: supports int, float, char, and string)
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
    struct Node *n = malloc(sizeof(struct Node));
    if (!n) return NULL;
    n->next = NULL;

    int len = strlen(s), hasDot = 0, isNum = 1, i;

    if (len == 1 && isalpha((unsigned char)s[0])) {
        n->type = 'c';
        n->data = malloc(sizeof(char));
        *(char *)n->data = s[0];
        return n;
    }

    for (i = 0; i < len; i++) {
        if (s[i] == '.' && !hasDot)
            hasDot = 1;
        else if (s[i] == '-' && i == 0)
            ;
        else if (!isdigit((unsigned char)s[i])) {
            isNum = 0;
            break;
        }
    }

    if (isNum && hasDot) {
        n->type = 'f';
        n->data = malloc(sizeof(float));
        *(float *)n->data = (float)atof(s);
    } else if (isNum) {
        n->type = 'i';
        n->data = malloc(sizeof(int));
        *(int *)n->data = atoi(s);
    } else {
        n->type = 's';
        n->data = malloc(len + 1);
        strcpy((char *)n->data, s);
    }

    return n;
}

void freeNode(struct Node *n) {
    if (n) {
        free(n->data);
        free(n);
    }
}

void printData(struct Node *n) {
    if (n->type == 'i') printf("%d", *(int *)n->data);
    else if (n->type == 'f') printf("%.2f", *(float *)n->data);
    else if (n->type == 'c') printf("%c", *(char *)n->data);
    else if (n->type == 's') printf("%s", (char *)n->data);
}

int match(struct Node *a, struct Node *b) {
    if (a->type != b->type) return 0;
    if (a->type == 'i') return *(int *)a->data == *(int *)b->data;
    if (a->type == 'f') return *(float *)a->data == *(float *)b->data;
    if (a->type == 'c') return *(char *)a->data == *(char *)b->data;
    if (a->type == 's') return strcmp((char *)a->data, (char *)b->data) == 0;
    return 0;
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
    struct Node *n = makeNode(readValue());
    if (n == NULL) {
        printf("Queue Overflow\n");
        return;
    }

    if (rear == NULL) {
        front = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    printf("Enqueued successfully\n");
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }

    struct Node *t = front;
    printf("Dequeued: ");
    printData(t);
    printf("\n");

    front = front->next;
    if (front == NULL)
        rear = NULL;

    freeNode(t);
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
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    struct Node *t = front;
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
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    struct Node *key = makeNode(readValue());
    if (key == NULL) {
        printf("Unable to create search value\n");
        return;
    }

    struct Node *t = front;
    int pos = 1, found = 0;
    while (t != NULL) {
        if (match(t, key)) {
            printf("Value found at position %d\n", pos);
            found = 1;
            break;
        }
        t = t->next;
        pos++;
    }

    if (!found)
        printf("Value not found\n");

    freeNode(key);
}

void count() {
    int cnt = 0;
    struct Node *t = front;
    while (t != NULL) {
        cnt++;
        t = t->next;
    }
    printf("Number of elements: %d\n", cnt);
}

void destroyQueue() {
    while (front != NULL) {
        struct Node *t = front;
        front = front->next;
        freeNode(t);
    }
    rear = NULL;
}

int main() {
    int ch;
    do {
        printf("\nQueue Operations:");
        printf("\n1. Enqueue\n2. Dequeue\n3. Front\n4. Rear\n5. Display\n6. Search\n7. Count\n8. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            ch = 0;
            continue;
        }

        switch (ch) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: frontElement(); break;
            case 4: rearElement(); break;
            case 5: display(); break;
            case 6: search(); break;
            case 7: count(); break;
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
