#include <stdio.h>

int sumUpTo(int num);

int main() {
    int num;
    printf("Enter a number n: ");
    scanf("%d", &num);

    printf("The sum of the numbers from 1 to %d is %d\n", num, sumUpTo(num));

    return 0;
}

int sumUpTo(int num){

    if (num == 0 || num == 1){
        return num;
    } 

    return num + sumUpTo(num - 1);
}