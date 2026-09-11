// Write a program to solve tower of Hanoi problem.

#include <stdio.h>

// Recursive function to calculate C(n, k)
int combination(int n, int k){
    if (k == 0 || n == k)
        return 1;
    else
        return combination(n - 1, k) + combination(n - 1, k - 1);
}

int main(){
    int n, k, result;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k < 0 || k > n){
        printf("Invalid input! k must be between 0 and n.\n");
    }
    else{
        result = combination(n, k);
        printf("C(%d, %d) = %d\n", n, k, result);
    }

    return 0;
}