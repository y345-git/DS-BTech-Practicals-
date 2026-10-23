// Singly Linked List ADT (Generic: supports int, float, char, and string)
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
    return head == NULL;
}

void insertBeginning() {
    struct Node *n = makeNode(readValue());
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
    struct Node *n = makeNode(readValue());
    if (n == NULL) {
        printf("List Overflow\n");
        return;
    }
    if (head == NULL) {
        head = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    printf("Inserted at end successfully\n");
}

void insertPosition() {
    int position, i;
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

    struct Node *n = makeNode(readValue());
    if (n == NULL) {
        printf("List Overflow\n");
        return;
    }

    struct Node *t = head;
    for (i = 1; i < position - 1 && t != NULL; i++)
        t = t->next;

    if (t == NULL) {
        printf("Invalid position\n");
        freeNode(n);
        return;
    }

    n->next = t->next;
    t->next = n;
    if (n->next == NULL)
        rear = n;

    printf("Inserted at position %d successfully\n", position);
}

void deleteBeginning() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    struct Node *t = head;
    printf("Deleted: ");
    printData(t);
    printf("\n");

    head = head->next;
    if (head == NULL)
        rear = NULL;

    freeNode(t);
}

void deleteEnd() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    struct Node *t = head, *prev = NULL;
    while (t->next != NULL) {
        prev = t;
        t = t->next;
    }

    printf("Deleted: ");
    printData(t);
    printf("\n");

    if (prev == NULL) {
        head = rear = NULL;
    } else {
        prev->next = NULL;
        rear = prev;
    }
    freeNode(t);
}

void deletePosition() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    int position, i;
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

    struct Node *t = head, *prev = NULL;
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

    freeNode(t);
}

void search() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }

    struct Node *key = makeNode(readValue());
    if (key == NULL) {
        printf("Unable to create search value\n");
        return;
    }

    struct Node *t = head;
    int found = 0;
    while (t != NULL) {
        if (match(t, key)) {
            printf("Element found\n");
            found = 1;
            break;
        }
        t = t->next;
    }

    if (!found)
        printf("Element not found\n");

    freeNode(key);
}

void display() {
    if (isEmpty()) {
        printf("List is empty\n");
        return;
    }
    struct Node *t = head;
    printf("\nList: ");
    while (t != NULL) {
        printData(t);
        printf(" -> ");
        t = t->next;
    }
    printf("NULL\n");
}

void count() {
    int cnt = 0;
    struct Node *t = head;
    while (t != NULL) {
        cnt++;
        t = t->next;
    }
    printf("Number of elements: %d\n", cnt);
}

void destroyList() {
    while (head != NULL) {
        struct Node *t = head;
        head = head->next;
        freeNode(t);
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
            case 1: insertBeginning(); break;
            case 2: insertEnd(); break;
            case 3: insertPosition(); break;
            case 4: deleteBeginning(); break;
            case 5: deleteEnd(); break;
            case 6: deletePosition(); break;
            case 7: search(); break;
            case 8: display(); break;
            case 9: count(); break;
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
