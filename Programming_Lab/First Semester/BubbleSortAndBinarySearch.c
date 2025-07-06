#include <stdio.h>

void DefineArray(int array[]);
int BinarySearch(int [], size_t, int);
void BubbleSort(int [],size_t);

int SIZE;

int main() {

    while(1){
        printf("\n\nWhich size do you prefer for your array (Enter -1 to Exit) ? ");
        scanf("%d",&SIZE);

        if (SIZE == -1) break;

        int Array[SIZE];
        int value;

        DefineArray(Array);

        BubbleSort(Array,SIZE);

        puts("My sorted array: ");
        for (size_t i = 0; i < SIZE; i++) printf("%d ",Array[i]);

        printf("\nWhich integers do you want to find ? ");
        scanf("%d",&value);

        puts("");
        value = BinarySearch(Array,SIZE,value);
        if (value != -1)    printf("Your integer at index : %d",value);
        else printf("Your value is not in the array.");

    }
    return 0;
}

void DefineArray(int array[])
{
    printf("Enter you array elements: \n");
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("Array[%d] = ",i);
        scanf("%d",array + i);
    }
}
int BinarySearch(int array[], size_t size, int value)
{
    int high = size - 1;
    int low = 0;

    while (low <= high)
    {    
        int middle = (high + low) / 2;
        if (value == array[middle]) return middle;
        else if (value < array[middle]) high = middle - 1;
        else low = middle + 1;
    }
    return -1;
}
void BubbleSort(int array[],size_t size){
    
    for (size_t i = 0; i < SIZE; i++)
    {    
        for (size_t i = 1; i < size; i++)
        {
            if (array[i - 1] > array[i])
            {
                int hold = array[i];
                array[i] = array[i-1];
                array[i-1]=hold;
            }
        }
    }

}

















