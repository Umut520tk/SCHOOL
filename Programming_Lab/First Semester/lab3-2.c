#include<stdio.h>
int main(){
    int day;
    printf("( (1: Monday) (2: Tuesday) (3: Wednesday) (4: Thursday) (5: Friday) (6: Saturday) (7: Sunday))\n");
    printf("Please enter a number o find there is a C course today or not: ");
    scanf("%d",&day);
    switch(day){
        case 2:
            printf("\nThere is a C course today.");
            break;
        default:
            printf("\nThere is not a C course today.");
            break;
    }
}