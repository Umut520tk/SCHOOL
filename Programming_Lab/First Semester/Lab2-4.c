#include<stdio.h>
#include<math.h>
int main()
{
    int grades[5];
    int average = 0;
    float sum = 0;
    for (int i = 0; i < 5; i++)
    {
        printf("Please enter grades number %d: ",i + 1);
        scanf("%d",(grades + i));
        printf("\n");
        average += grades[i];
    }
    average = average / 5;
    for (int i = 0; i < 5; i++)
    {
        sum += pow((grades[i] - average),2);
    }
    printf("Your grades standart devision : %f",sqrt(sum/5.0f));

    return 0;
}