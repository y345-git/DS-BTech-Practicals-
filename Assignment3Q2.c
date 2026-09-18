#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *dataPtr;
    int type;
    struct node *link;
} STACK_NODE;

typedef struct {
    int count;
    STACK_NODE *top;
} STACK;


/* Create Stack */

STACK *createStack() {
    STACK *stack;

    stack = malloc(sizeof(STACK));

    if (stack == NULL)
        return NULL;

    stack->count = 0;
    stack->top = NULL;

    return stack;
}


/* Push */

int pushStack(STACK *stack, void *data, int type) {
    STACK_NODE *newNode;

    newNode = malloc(sizeof(STACK_NODE));

    if (newNode == NULL)
        return 0;

    newNode->dataPtr = data;
    newNode->type = type;
    newNode->link = stack->top;

    stack->top = newNode;
    stack->count++;

    return 1;
}


/* Pop */

void *popStack(STACK *stack, int *type) {
    STACK_NODE *temp;
    void *data;

    if (stack->top == NULL)
        return NULL;

    temp = stack->top;

    data = temp->dataPtr;
    *type = temp->type;

    stack->top = temp->link;
    stack->count--;

    free(temp);

    return data;
}


/* Stack Top */

void *stackTop(STACK *stack, int *type) {
    if (stack->top == NULL)
        return NULL;

    *type = stack->top->type;

    return stack->top->dataPtr;
}


/* Empty */

int emptyStack(STACK *stack) {
    if (stack->count == 0)
        return 1;

    return 0;
}


/* Full */

int fullStack(STACK *stack) {
    STACK_NODE *temp;

    temp = malloc(sizeof(STACK_NODE));

    if (temp == NULL)
        return 1;

    free(temp);

    return 0;
}


/* Count */

int stackCount(STACK *stack) {
    return stack->count;
}


/* Display Data */

void displayData(void *data, int type) {
    if (type == 1)
        printf("%d", *(int *)data);

    else if (type == 2)
        printf("%f", *(float *)data);

    else if (type == 3)
        printf("%c", *(char *)data);

    else
        printf("%s", (char *)data);
}


/* Display Stack */

void displayStack(STACK *stack) {
    STACK_NODE *temp;

    if (emptyStack(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    temp = stack->top;

    printf("Stack: ");

    while (temp != NULL) {
        displayData(temp->dataPtr, temp->type);
        printf(" ");

        temp = temp->link;
    }

    printf("\n");
}


/* Destroy Stack */

void destroyStack(STACK *stack) {
    STACK_NODE *temp;

    while (stack->top != NULL) {
        temp = stack->top;

        stack->top = temp->link;

        free(temp->dataPtr);
        free(temp);
    }

    free(stack);
}


/* Read Data Automatically */

void *readData(int *type) {
    char input[100];
    char *end;
    long intValue;
    float floatValue;
    int i;

    printf("Enter value: ");
    scanf("%99s", input);

    /* Single character */

    if (strlen(input) == 1 &&
        !((input[0] >= '0' && input[0] <= '9'))) {

        char *value;

        value = malloc(sizeof(char));
        *value = input[0];

        *type = 3;

        return value;
    }


    /* Integer */

    intValue = strtol(input, &end, 10);

    if (*end == '\0') {
        int *value;

        value = malloc(sizeof(int));
        *value = intValue;

        *type = 1;

        return value;
    }


    /* Float */

    floatValue = strtof(input, &end);

    if (*end == '\0') {
        float *value;

        value = malloc(sizeof(float));
        *value = floatValue;

        *type = 2;

        return value;
    }


    /* String */

    {
        char *value;

        value = malloc(strlen(input) + 1);
        strcpy(value, input);

        *type = 4;

        return value;
    }
}


/* Main */

int main() {
    STACK *stack;
    void *data;
    void *result;
    int type;
    int choice;

    stack = createStack();

    if (stack == NULL) {
        printf("Unable to create stack.\n");
        return 0;
    }

    while (1) {
        printf("\nStack Operations:");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Top");
        printf("\n4. Display");
        printf("\n5. Count");
        printf("\n6. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            data = readData(&type);

            if (pushStack(stack, data, type))
                printf("Pushed successfully.\n");
            else {
                printf("Stack overflow.\n");
                free(data);
            }
        }

        else if (choice == 2) {
            result = popStack(stack, &type);

            if (result == NULL)
                printf("Stack is empty.\n");
            else {
                printf("Popped value: ");
                displayData(result, type);
                printf("\n");

                free(result);
            }
        }

        else if (choice == 3) {
            result = stackTop(stack, &type);

            if (result == NULL)
                printf("Stack is empty.\n");
            else {
                printf("Top value: ");
                displayData(result, type);
                printf("\n");
            }
        }

        else if (choice == 4) {
            displayStack(stack);
        }

        else if (choice == 5) {
            printf("Number of elements: %d\n", stackCount(stack));
        }

        else if (choice == 6) {
            destroyStack(stack);
            printf("Stack destroyed.\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}