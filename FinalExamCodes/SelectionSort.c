#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100000

void selectionSort(int arr[SIZE]) {
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void selectionSort_v2(int arr[SIZE]) {
    // This version sorts in descending order for demonstration
    for (int i = 0; i < SIZE - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
}

void printArray(int arr[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    srand(time(NULL));

    int arr1[SIZE];
    int arr2[SIZE];

    for (size_t i = 0; i < SIZE; i++)
    {
        arr1[i] = rand() % SIZE;
        arr2[i] = rand() % SIZE;
    }
    

    // Measure selectionSort (seconds)
    time_t t_start = time(NULL);
    clock_t c_start = clock();
    selectionSort(arr1);
    clock_t c_end = clock();
    time_t t_end = time(NULL);
    printf("selectionSort time: %ld seconds\n", t_end - t_start);
    printf("selectionSort CPU time: %.6f seconds\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    //printf("Sorted arr1: ");
    //printArray(arr1);

    // Measure selectionSort_v2 (seconds)
    t_start = time(NULL);
    c_start = clock();
    selectionSort_v2(arr2);
    c_end = clock();
    t_end = time(NULL);
    printf("selectionSort_v2 time: %ld seconds\n", t_end - t_start);
    printf("selectionSort_v2 CPU time: %.6f seconds\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
   // printf("Sorted arr2: ");
    //printArray(arr2);

    return 0;
}