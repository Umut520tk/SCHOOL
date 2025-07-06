#include<stdio.h>
int main()
{
    float labGrade,midterm1,midterm2,FinalGrade;
    printf("Please enter your grades to find your passed or failed :\n");
    printf("(Lab Grade ): ");
    scanf("%f",&labGrade);
    printf("\n");
    printf("(Mid Term 1 ): ");
    scanf("%f",&midterm1);
    printf("\n");
    printf("(Mid Term 2 ): ");
    scanf("%f",&midterm2);
    printf("\n");
    printf("(Final Grade ): ");
    scanf("%f",&FinalGrade);
    printf("\n The result is: %d (1 means you passed, 0 means you failed)",(labGrade * 0.2 + midterm1 * 0.2 + midterm2 * 0.2 + FinalGrade * 0.4)>=70 ? 1:0);
    return 0;
}