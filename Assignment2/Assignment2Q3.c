// Write program to Reverse given linked list 
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

int main(){
    struct Node *head = NULL, *newNode, *temp;
    struct Node *prev = NULL, *next;
    int n, i, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++){
        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter value: ");
        scanf("%d", &value);

        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    printf("Original List: ");
    temp = head;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    temp = head;

    while (temp != NULL){
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }

    head = prev;

    printf("Reversed List: ");
    temp = head;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    return 0;
}