// write program to concatenate the two linked list 
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create() {
    struct Node *head = NULL, *newNode, *temp;
    int n, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));

        printf("Enter value: ");
        scanf("%d", &newNode->data);

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        }
        else {
            temp->next = newNode;
        }

        temp = newNode;
    }

    return head;
}

void display(struct Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

struct Node* concatenate(struct Node *head1, struct Node *head2) {
    struct Node *temp;

    if (head1 == NULL) {
        return head2;
    }

    temp = head1;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = head2;

    return head1;
}

int main() {
    struct Node *head1, *head2;

    printf("First Linked List\n");
    head1 = create();

    printf("\nSecond Linked List\n");
    head2 = create();

    printf("\nFirst List: ");
    display(head1);

    printf("Second List: ");
    display(head2);

    head1 = concatenate(head1, head2);

    printf("Concatenated List: ");
    display(head1);

    return 0;
}