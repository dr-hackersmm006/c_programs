#include<stdio.h>
#include<math.h>
 void main(){

     double m, p, a;
     int b, i;
     printf("Enter number in decimal:");
     scanf("%lf",&m);
     printf("Enter the Base:");
     scanf("%d",&b);
     
     if(m < 2){
         printf("Invalid base number");
     }
     else if(b < 10){
        int n = m;
        p = m-n;
        i = 0;
        a = 0;
     
        while(n != 0){
            int r = n % b;
            a = a + r * pow(10,i);
            n = n / b;
            i++;
        }
        for(i=1;i<=4;i++){
            p = p * b;
            int r = p;
            p = p - r;
            a = a + r * pow(10,-i);
        }

        printf("%.4lf",a);

    }

    else if (b == 16) {
    int n = m;
    p = m - n;

    char hex[16];
    int i = 0;

    while (n != 0) {
        int r = n % 16;

        if (r < 10)
            hex[i] = r + '0';
        else
            hex[i] = r - 10 + 'A';

        n = n / 16;
        i++;
    }

    for (i = i - 1; i >= 0; i--)
        printf("%c", hex[i]);

    printf(".");

    for (i = 0; i < 4; i++) {
        p = p * 16;
        int r = p;
        p = p - r;

        if (r < 10)
            printf("%c", r + '0');
        else
            printf("%c", r - 10 + 'A');
    }
}
}
