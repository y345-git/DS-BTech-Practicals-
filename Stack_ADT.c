// Stack ADT (Generic: supports int, float, char, and string)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    void *data;
    char type;
    struct Node *next;
};

struct Node *top = NULL;

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
    return top == NULL;
}

void push() {
    struct Node *n = makeNode(readValue());
    if (n == NULL) {
        printf("Stack Overflow\n");
        return;
    }
    n->next = top;
    top = n;
    printf("Pushed successfully\n");
}

void pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    struct Node *t = top;
    printf("Popped: ");
    printData(t);
    printf("\n");

    top = top->next;
    freeNode(t);
}

void peek() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element: ");
    printData(top);
    printf("\n");
}

void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    struct Node *t = top;
    printf("Stack (top to bottom):\n");
    while (t != NULL) {
        printData(t);
        if (t == top)
            printf("  <-- top");
        printf("\n");
        t = t->next;
    }
}

void search() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }

    struct Node *key = makeNode(readValue());
    if (key == NULL) {
        printf("Unable to create search value\n");
        return;
    }

    struct Node *t = top;
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
    struct Node *t = top;
    while (t != NULL) {
        cnt++;
        t = t->next;
    }
    printf("Number of elements: %d\n", cnt);
}

void destroyStack() {
    while (top != NULL) {
        struct Node *t = top;
        top = top->next;
        freeNode(t);
    }
}

int main() {
    int ch;
    do {
        printf("\nStack Operations:");
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Search\n6. Count\n7. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            ch = 0;
            continue;
        }

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: display(); break;
            case 5: search(); break;
            case 6: count(); break;
            case 7:
                destroyStack();
                printf("Stack destroyed\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (ch != 7);

    return 0;
}
