// Write a program toImplement the ADT for singly linked list
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insert(){
    struct Node *newNode, *temp;
    int value;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter value: ");
    scanf("%d", &value);

    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else{
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
}

void deleteNode(){
    struct Node *temp, *prev;
    int value;

    printf("Enter value to delete: ");
    scanf("%d", &value);

    temp = head;
    prev = NULL;

    while (temp != NULL && temp->data != value){
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        printf("Value not found.\n");
    else{
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        free(temp);
        printf("Deleted successfully.\n");
    }
}

void search(){
    struct Node *temp = head;
    int value;

    printf("Enter value to search: ");
    scanf("%d", &value);

    while (temp != NULL){
        if (temp->data == value){
            printf("Value found.\n");
            return;
        }
        temp = temp->next;
    }

    printf("Value not found.\n");
}

void display(){
    struct Node *temp = head;

    if (head == NULL){
        printf("List is empty.\n");
        return;
    }

    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main(){
    int choice;

    while (1){
        printf("\nSingly Linked List ADT Operations:\n");
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice){
            case 1: insert(); break;
            case 2: deleteNode(); break;
            case 3: search(); break;
            case 4: display(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}