#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void insertionSort(int arr[]);

void selectionSort(int arr[]);

void printArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[SIZE];
    int arr2[SIZE];
    srand(time(NULL));
    // Fill array with random numbers
    for (int i = 0; i < SIZE; i++) {
        arr1[i] = rand() % 100; // Random numbers between 0 and 99
        arr2[i] = rand() % 100; // Random numbers between 0 and 99
    }

    //insertionSort(arr);

    selectionSort(arr1);

    printArray(arr1);

    

    return 0;
}

void insertionSort(int arr[]){

    for (size_t i = 1; i < SIZE; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; 
    }
}

void selectionSort(int arr[]){

    for (size_t i = 0; i < SIZE - 1; i++)
    {
        int maxindex = i;
        
        for (int j = i; j < SIZE; j++)
        {
            if (arr[j] < arr[maxindex])
            {
                maxindex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[maxindex];
        arr[maxindex] = temp;
    }
}