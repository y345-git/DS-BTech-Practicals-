// Write a program to implement  priorityQueue  Ascending adn descending Priority 
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX];
int n = 0;

void insert() {
    int value;

    if (n == MAX) {
        printf("Queue is full.\n");
    }
    else {
        printf("Enter value: ");
        scanf("%d", &value);

        queue[n] = value;
        n++;
    }
}

void ascending() {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (queue[i] > queue[j]) {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    printf("Ascending Priority: ");

    for (i = 0; i < n; i++) {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

void descending() {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (queue[i] < queue[j]) {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    printf("Descending Priority: ");

    for (i = 0; i < n; i++) {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert\n");
        printf("2. Ascending Priority\n");
        printf("3. Descending Priority\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
                break;

            case 2:
                ascending();
                break;

            case 3:
                descending();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}