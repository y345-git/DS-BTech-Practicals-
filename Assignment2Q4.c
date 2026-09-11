// Write program to create ordered linked list
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

int main(){
    struct Node *head = NULL, *newNode, *temp, *prev;
    int n, value, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++){
        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter value: ");
        scanf("%d", &value);

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL || value < head->data){
            newNode->next = head;
            head = newNode;
        }
        else{
            temp = head;

            while (temp->next != NULL && temp->next->data < value)
                temp = temp->next;

            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    printf("\nOrdered Linked List: ");

    temp = head;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");

    return 0;
}