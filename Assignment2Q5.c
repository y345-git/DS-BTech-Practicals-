#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *dataPtr;
    int type;
    struct node *link;
} LIST_NODE;

typedef struct {
    int count;
    LIST_NODE *head;
    LIST_NODE *rear;
} LIST;


/* Create List */

LIST *createList() {
    LIST *list;

    list = malloc(sizeof(LIST));

    if (list == NULL)
        return NULL;

    list->count = 0;
    list->head = NULL;
    list->rear = NULL;

    return list;
}


/* Insert at End */

int addNode(LIST *list, void *data, int type) {
    LIST_NODE *newNode;

    newNode = malloc(sizeof(LIST_NODE));

    if (newNode == NULL)
        return 0;

    newNode->dataPtr = data;
    newNode->type = type;
    newNode->link = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->rear = newNode;
    }
    else {
        list->rear->link = newNode;
        list->rear = newNode;
    }

    list->count++;

    return 1;
}


/* Compare Data */

int compareData(void *data1, int type1, void *data2, int type2) {
    if (type1 != type2)
        return 0;

    if (type1 == 1) {
        if (*(int *)data1 == *(int *)data2)
            return 1;
    }

    else if (type1 == 2) {
        if (*(float *)data1 == *(float *)data2)
            return 1;
    }

    else if (type1 == 3) {
        if (*(char *)data1 == *(char *)data2)
            return 1;
    }

    else {
        if (strcmp((char *)data1, (char *)data2) == 0)
            return 1;
    }

    return 0;
}


/* Delete */

void *removeNode(LIST *list, void *key, int keyType, int *type) {
    LIST_NODE *temp;
    LIST_NODE *previous;
    void *data;

    temp = list->head;
    previous = NULL;

    while (temp != NULL) {
        if (compareData(temp->dataPtr, temp->type, key, keyType)) {

            data = temp->dataPtr;
            *type = temp->type;

            if (previous == NULL)
                list->head = temp->link;
            else
                previous->link = temp->link;

            if (temp == list->rear)
                list->rear = previous;

            list->count--;

            free(temp);

            return data;
        }

        previous = temp;
        temp = temp->link;
    }

    return NULL;
}


/* Search */

void *searchList(LIST *list, void *key, int keyType, int *type) {
    LIST_NODE *temp;

    temp = list->head;

    while (temp != NULL) {
        if (compareData(temp->dataPtr, temp->type, key, keyType)) {
            *type = temp->type;
            return temp->dataPtr;
        }

        temp = temp->link;
    }

    return NULL;
}


/* Empty */

int emptyList(LIST *list) {
    if (list->count == 0)
        return 1;

    return 0;
}


/* Full */

int fullList(LIST *list) {
    LIST_NODE *temp;

    temp = malloc(sizeof(LIST_NODE));

    if (temp == NULL)
        return 1;

    free(temp);

    return 0;
}


/* Count */

int listCount(LIST *list) {
    return list->count;
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


/* Display List */

void displayList(LIST *list) {
    LIST_NODE *temp;

    if (emptyList(list)) {
        printf("List is empty.\n");
        return;
    }

    temp = list->head;

    printf("List: ");

    while (temp != NULL) {
        displayData(temp->dataPtr, temp->type);
        printf(" -> ");

        temp = temp->link;
    }

    printf("NULL\n");
}


/* Destroy List */

void destroyList(LIST *list) {
    LIST_NODE *temp;

    while (list->head != NULL) {
        temp = list->head;

        list->head = temp->link;

        free(temp->dataPtr);
        free(temp);
    }

    free(list);
}


/* Read Data */

void *readData(int *type) {
    char input[100];
    char *end;
    long intValue;
    float floatValue;

    printf("Enter value: ");
    scanf("%99s", input);


    /* Character */

    if (strlen(input) == 1 &&
        !(input[0] >= '0' && input[0] <= '9')) {

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
    LIST *list;
    void *data;
    void *result;
    void *key;
    int type;
    int keyType;
    int choice;

    list = createList();

    if (list == NULL) {
        printf("Unable to create list.\n");
        return 0;
    }

    while (1) {
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. Display");
        printf("\n5. Count");
        printf("\n6. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            data = readData(&type);

            if (addNode(list, data, type))
                printf("Inserted successfully.\n");
            else {
                printf("List overflow.\n");
                free(data);
            }
        }

        else if (choice == 2) {
            printf("Enter value to delete:\n");

            key = readData(&keyType);

            result = removeNode(list, key, keyType, &type);

            if (result == NULL)
                printf("Value not found.\n");
            else {
                printf("Deleted value: ");
                displayData(result, type);
                printf("\n");

                free(result);
            }

            free(key);
        }

        else if (choice == 3) {
            printf("Enter value to search:\n");

            key = readData(&keyType);

            result = searchList(list, key, keyType, &type);

            if (result == NULL)
                printf("Value not found.\n");
            else {
                printf("Value found: ");
                displayData(result, type);
                printf("\n");
            }

            free(key);
        }

        else if (choice == 4) {
            displayList(list);
        }

        else if (choice == 5) {
            printf("Number of elements: %d\n", listCount(list));
        }

        else if (choice == 6) {
            destroyList(list);
            printf("List destroyed.\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}