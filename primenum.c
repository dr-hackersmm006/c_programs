#include<stdio.h>

void main() {
    int n, i;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    if (n < 0){
        printf("It is not a positive integer");
    }
    else if (n <= 1) {
        printf("%d is not a prime number.\n",n);
    } else {
        for (i = 2; i < n; i++) {
            if (n % i == 0) {
                printf("%d is not a prime number.\n", n);
                printf("%d is divisible by %d.\n", n, i);
                break;
            }
        }
        if (i == n) {
            printf("%d is a prime number.\n", n);
        }
    }
}