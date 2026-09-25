// Singly Linked List ADT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    void *data;
    char type;              
    struct Node *next;
};

struct Node *head = NULL;
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
    return head == NULL;
}

void insertBeginning() {
    struct Node *n;

    n = makeNode(readValue());

    if (n == NULL) {
        printf("List Overflow\n");
        return;
    }

    n->next = head;
    head = n;

    if (rear == NULL)
        rear = n;

    printf("Inserted at beginning successfully\n");
}

void insertEnd() {
    struct Node *n;

    n = makeNode(readValue());

    if (n == NULL) {
        printf("List Overflow\n");
        return;
    }

    if (head == NULL) {
        head = n;
        rear = n;
    }
    else {
        rear->next = n;
        rear = n;
    }

    printf("Inserted at end successfully\n");
}

void insertPosition() {
    struct Node *n;
    struct Node *t;
    int position;
    int i;

    printf("Enter position: ");
    scanf("%d", &position);

    if (position <= 0) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        insertBeginning();
        return;
    }

    n = makeNode(readValue());

    if (n == NULL) {
        printf("List Overflow\n");
        return;
    }

    t = head;

    for (i = 1; i < position - 1 && t != NULL; i++)
        t = t->next;

    if (t == NULL) {
        printf("Invalid position\n");

        free(n->data);
        free(n);

        return;
    }

    n->next = t->next;
    t->next = n;

    if (n->next == NULL)
        rear = n;

    printf("Inserted at position %d successfully\n", position);
}

void deleteBeginning() {
    struct Node *t;

    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    t = head;

    printf("Deleted: ");
    printData(t);
    printf("\n");

    head = head->next;

    if (head == NULL)
        rear = NULL;

    free(t->data);
    free(t);
}

void deleteEnd() {
    struct Node *t;
    struct Node *prev;

    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    t = head;
    prev = NULL;

    while (t->next != NULL) {
        prev = t;
        t = t->next;
    }

    printf("Deleted: ");
    printData(t);
    printf("\n");

    if (prev == NULL) {
        head = NULL;
        rear = NULL;
    }
    else {
        prev->next = NULL;
        rear = prev;
    }

    free(t->data);
    free(t);
}

void deletePosition() {
    struct Node *t;
    struct Node *prev;
    int position;
    int i;

    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    printf("Enter position: ");
    scanf("%d", &position);

    if (position <= 0) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        deleteBeginning();
        return;
    }

    t = head;
    prev = NULL;

    for (i = 1; i < position && t != NULL; i++) {
        prev = t;
        t = t->next;
    }

    if (t == NULL) {
        printf("Invalid position\n");
        return;
    }

    printf("Deleted: ");
    printData(t);
    printf("\n");

    prev->next = t->next;

    if (t == rear)
        rear = prev;

    free(t->data);
    free(t);
}

void search() {
    struct Node *t;
    struct Node *key;
    int found = 0;

    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    key = makeNode(readValue());

    if (key == NULL) {
        printf("Unable to create search value\n");
        return;
    }

    t = head;

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
                     strcmp((char *)t->data,
                            (char *)key->data) == 0) {
                found = 1;
            }
        }

        if (found) {
            printf("Element found\n");
            break;
        }

        t = t->next;
    }

    if (!found)
        printf("Element not found\n");

    free(key->data);
    free(key);
}

void display() {
    struct Node *t;

    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    t = head;

    printf("\nList: ");

    while (t != NULL) {
        printData(t);
        printf(" -> ");

        t = t->next;
    }

    printf("NULL\n");
}

void count() {
    struct Node *t;
    int count = 0;

    t = head;

    while (t != NULL) {
        count++;
        t = t->next;
    }

    printf("Number of elements: %d\n", count);
}

void destroyList() {
    struct Node *t;

    while (head != NULL) {
        t = head;

        head = head->next;

        free(t->data);
        free(t);
    }

    rear = NULL;
}

int main() {
    int ch;

    do {
        printf("\n\nSingly Linked List Operations:");

        printf("\n1. Insert at Beginning");
        printf("\n2. Insert at End");
        printf("\n3. Insert at Specific Position");

        printf("\n4. Delete from Beginning");
        printf("\n5. Delete from End");
        printf("\n6. Delete from Specific Position");

        printf("\n7. Search");
        printf("\n8. Display");
        printf("\n9. Count");
        printf("\n10. Exit");

        printf("\nEnter choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");

            while (getchar() != '\n');

            ch = 0;

            continue;
        }

        switch (ch) {

            case 1:
                insertBeginning();
                break;

            case 2:
                insertEnd();
                break;

            case 3:
                insertPosition();
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                deletePosition();
                break;

            case 7:
                search();
                break;

            case 8:
                display();
                break;

            case 9:
                count();
                break;

            case 10:
                destroyList();
                printf("List destroyed\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (ch != 10);

    return 0;
}