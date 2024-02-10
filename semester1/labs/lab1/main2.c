#include<stdio.h>

int main(int argc, char* argv[]) {
    float x, y;
    
    printf("Enter value for x: ");
    scanf("%f", &x);

    if (x > -15 && x <= 3) {
        y = 4 * x*x + 2;
        printf("f(%.2f) = %.2f\n", x, y);
    }
    else {
        if (x <= -30 || x > 20) {
            y = (3 * x*x*x) / 4 - 5;
            printf("f(%.2f) = %.2f\n", x, y);
        }
        else {
            printf("no value\n");
        }
    }

    return 0;
}