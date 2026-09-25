// Write a program toImplement the Doubly linked list write the functions to insert(front ,rear,middle), delete(front ,rear,middle), and display
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *prev, *next;
};

struct Node *head = NULL;

// Insert at front
void insertFront(){
    struct Node *newNode = malloc(sizeof(struct Node));

    printf("Enter value: ");
    scanf("%d", &newNode->data);

    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL)
        head->prev = newNode;

    head = newNode;
}

// Insert at rear
void insertRear(){
    struct Node *newNode = malloc(sizeof(struct Node));
    struct Node *temp = head;

    printf("Enter value: ");
    scanf("%d", &newNode->data);

    newNode->next = NULL;

    if (head == NULL){
        newNode->prev = NULL;
        head = newNode;
        return;
    }

    while (temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Insert in middle (after a given value)
void insertMiddle(){
    struct Node *temp = head;
    struct Node *newNode = malloc(sizeof(struct Node));
    int value;

    printf("Insert after which value: ");
    scanf("%d", &value);

    while (temp != NULL && temp->data != value){
        temp = temp->next;
    }

    if (temp == NULL){
        printf("Value not found.\n");
        free(newNode);
        return;
    }

    printf("Enter value: ");
    scanf("%d", &newNode->data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL){
        temp->next->prev = newNode;
    }

    temp->next = newNode;
}

// Delete front
void deleteFront(){
    struct Node *temp;

    if (head == NULL){
        printf("List is empty.\n");
        return;
    }

    temp = head;
    head = head->next;

    if (head != NULL){
        head->prev = NULL;
    }

    free(temp);
}

// Delete rear
void deleteRear(){
    struct Node *temp = head;

    if (head == NULL){
        printf("List is empty.\n");
        return;
    }

    while (temp->next != NULL){
        temp = temp->next;
    }

    if (temp->prev != NULL){
        temp->prev->next = NULL;
    }
    else{
        head = NULL;
    }

    free(temp);
}

// Delete middle (by value)
void deleteMiddle(){
    struct Node *temp = head;
    int value;

    printf("Enter value to delete: ");
    scanf("%d", &value);

    while (temp != NULL && temp->data != value){
        temp = temp->next;
    }

    if (temp == NULL){
        printf("Value not found.\n");
        return;
    }

    if (temp->prev != NULL){
        temp->prev->next = temp->next;
    }

    if (temp->next != NULL){
        temp->next->prev = temp->prev;
    }

    if (temp == head){
        head = temp->next;
    }

    free(temp);
}

// Display
void display(){
    struct Node *temp = head;

    if (head == NULL){
        printf("List is empty.\n");
        return;
    }

    while (temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main(){
    int choice;

    while (1){
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert Front\n");
        printf("2. Insert Rear\n");
        printf("3. Insert Middle\n");
        printf("4. Delete Front\n");
        printf("5. Delete Rear\n");
        printf("6. Delete Middle\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice){
            case 1: insertFront(); break;
            case 2: insertRear(); break;
            case 3: insertMiddle(); break;
            case 4: deleteFront(); break;
            case 5: deleteRear(); break;
            case 6: deleteMiddle(); break;
            case 7: display(); break;
            case 8: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}