#include <stdio.h>
#include <stdlib.h>

int main(){
    int index = 0;
    printf("Plese enter the index number : ");
    scanf("%d", &index);

    int* a = (int *) malloc(index * sizeof(int)); 
    int* b = (int *) malloc((index- 1) * sizeof(int)); 
    printf("\nPlease enter the elements of the array : ");

    for(int i = 0; i < index; i++){
        scanf("%d", a + i);
    }
    
    for(int i = 0; i < index - 1; i++){
        b[i] = a[i+1]- a[i];
    }

    printf("\n");

    for (size_t i = 0; i < index; i++)
    {
        printf("original array %i \n",a[i]);
    }
    printf("\n");
    
    for (size_t i = 0; i < index - 1; i++)
    {
        printf("Difference array %i\n",b[i]);
    }

    free(a);
    free(b);
}