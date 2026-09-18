#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *dataPtr;
    int type;
    struct node *link;
} QUEUE_NODE;

typedef struct {
    int count;
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
} QUEUE;


/* Create Queue */

QUEUE *createQueue() {
    QUEUE *queue;

    queue = malloc(sizeof(QUEUE));

    if (queue == NULL)
        return NULL;

    queue->count = 0;
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}


/* Enqueue */

int enqueue(QUEUE *queue, void *data, int type) {
    QUEUE_NODE *newNode;

    newNode = malloc(sizeof(QUEUE_NODE));

    if (newNode == NULL)
        return 0;

    newNode->dataPtr = data;
    newNode->type = type;
    newNode->link = NULL;

    if (queue->count == 0) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->link = newNode;
        queue->rear = newNode;
    }

    queue->count++;

    return 1;
}


/* Dequeue */

void *dequeue(QUEUE *queue, int *type) {
    QUEUE_NODE *temp;
    void *data;

    if (queue->front == NULL)
        return NULL;

    temp = queue->front;

    data = temp->dataPtr;
    *type = temp->type;

    queue->front = temp->link;

    if (queue->front == NULL)
        queue->rear = NULL;

    queue->count--;

    free(temp);

    return data;
}


/* Queue Front */

void *queueFront(QUEUE *queue, int *type) {
    if (queue->front == NULL)
        return NULL;

    *type = queue->front->type;

    return queue->front->dataPtr;
}


/* Queue Rear */

void *queueRear(QUEUE *queue, int *type) {
    if (queue->rear == NULL)
        return NULL;

    *type = queue->rear->type;

    return queue->rear->dataPtr;
}


/* Empty */

int emptyQueue(QUEUE *queue) {
    if (queue->count == 0)
        return 1;

    return 0;
}


/* Full */

int fullQueue(QUEUE *queue) {
    QUEUE_NODE *temp;

    temp = malloc(sizeof(QUEUE_NODE));

    if (temp == NULL)
        return 1;

    free(temp);

    return 0;
}


/* Count */

int queueCount(QUEUE *queue) {
    return queue->count;
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


/* Display Queue */

void displayQueue(QUEUE *queue) {
    QUEUE_NODE *temp;

    if (emptyQueue(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    temp = queue->front;

    printf("Queue: ");

    while (temp != NULL) {
        displayData(temp->dataPtr, temp->type);
        printf(" ");

        temp = temp->link;
    }

    printf("\n");
}


/* Destroy Queue */

void destroyQueue(QUEUE *queue) {
    QUEUE_NODE *temp;

    while (queue->front != NULL) {
        temp = queue->front;

        queue->front = temp->link;

        free(temp->dataPtr);
        free(temp);
    }

    free(queue);
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
    QUEUE *queue;
    void *data;
    void *result;
    int type;
    int choice;

    queue = createQueue();

    if (queue == NULL) {
        printf("Unable to create queue.\n");
        return 0;
    }

    while (1) {
        printf("\nQueue Operations:");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Front");
        printf("\n4. Rear");
        printf("\n5. Display");
        printf("\n6. Count");
        printf("\n7. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            data = readData(&type);

            if (enqueue(queue, data, type))
                printf("Enqueued successfully.\n");
            else {
                printf("Queue overflow.\n");
                free(data);
            }
        }

        else if (choice == 2) {
            result = dequeue(queue, &type);

            if (result == NULL)
                printf("Queue is empty.\n");
            else {
                printf("Dequeued value: ");
                displayData(result, type);
                printf("\n");

                free(result);
            }
        }

        else if (choice == 3) {
            result = queueFront(queue, &type);

            if (result == NULL)
                printf("Queue is empty.\n");
            else {
                printf("Front value: ");
                displayData(result, type);
                printf("\n");
            }
        }

        else if (choice == 4) {
            result = queueRear(queue, &type);

            if (result == NULL)
                printf("Queue is empty.\n");
            else {
                printf("Rear value: ");
                displayData(result, type);
                printf("\n");
            }
        }

        else if (choice == 5) {
            displayQueue(queue);
        }

        else if (choice == 6) {
            printf("Number of elements: %d\n", queueCount(queue));
        }

        else if (choice == 7) {
            destroyQueue(queue);
            printf("Queue destroyed.\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}