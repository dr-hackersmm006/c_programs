#include<stdio.h>
#include<math.h>

void main() {
    float a, b, c;
    printf("ax^2 + bx + c = 0\n");
    printf ("Now,\n a=");
    scanf("%f", &a);
    printf (" b=");
    scanf("%f", &b);
    printf (" c=");
    scanf("%f", &c);
    if (a == 0) {
        printf("This is not a quadratic equation.\n");
    } else {
        float D = b * b - 4 * a * c;
        if (D > 0) {
            float r1 = (-b + sqrt(D)) / (2 * a); 
            float r2 = (-b - sqrt(D)) / (2 * a);
            printf("Roots are real and different.\n");
            printf("Root 1 = %.2f\n", r1);
            printf("Root 2 = %.2f\n", r2);
        } else if (D == 0) {
            float r = -b / (2 * a);
            printf("Roots are real and the same.\n");
            printf("Root = %.2f\n", r);
        } else {
            printf("Roots are complex and different.\n");
            printf("Root 1 = %.2f + %.2fi\n", -b / (2 * a), sqrt(-D) / (2 * a));
            printf("Root 2 = %.2f - %.2fi\n", -b / (2 * a), sqrt(-D) / (2 * a));
        }
    }

}