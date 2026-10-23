// Write a program to create an ordered linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node *head = NULL, *newNode, *temp;
    int n, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));
        printf("Enter value: ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if (head == NULL || newNode->data < head->data) {
            newNode->next = head;
            head = newNode;
        } else {
            temp = head;
            while (temp->next != NULL && temp->next->data < newNode->data) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    printf("\nOrdered Linked List: ");
    for (temp = head; temp != NULL; temp = temp->next) {
        printf("%d -> ", temp->data);
    }
    printf("NULL\n");

    return 0;
}
