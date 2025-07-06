#include<stdio.h>
#include<math.h>
int main()
{
    float x;
    printf("Enter a number to find e^x, |x|, 4th root of x: ");
    scanf("%f",&x);
    printf("\n e^x = %f",(float)exp(x));
    printf("\n |x| = %f",(float)abs(x));
    printf("\n 4th root of x = %f",(float)pow(x,1.0f/4.0f));
    return 0;
}