#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define RUNS 10000


void datagen(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

int comp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int binary_search(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    srand(100);
    int *arr = malloc(SIZE * sizeof(int));
    int target = -1; 

  // UNOPTIMIZED ALGORITHM : LINEAR SEARCH

    clock_t start_total_unopt = clock();
    
    datagen(arr, SIZE);
    qsort(arr, SIZE, sizeof(int), comp); 
    
    clock_t start_proc_unopt = clock();
    for (int i = 0; i < RUNS; i++) {
        linear_search(arr, SIZE, target);
    }
    clock_t end_proc_unopt = clock();
    
    clock_t end_total_unopt = clock();

    // OPTIMIZED ALGORITHM: BINARY SEARCH
    clock_t start_total_opt = clock();
    
    datagen(arr, SIZE);
    qsort(arr, SIZE, sizeof(int), comp);
    
    clock_t start_proc_opt = clock();
    for (int i = 0; i < RUNS; i++) {
        binary_search(arr, SIZE, target);
    }
    clock_t end_proc_opt = clock();
    
    clock_t end_total_opt = clock();

    double T_unoptimized = (double)(end_total_unopt - start_total_unopt) / CLOCKS_PER_SEC;
    double T_processing_unopt= (double)(end_proc_unopt - start_proc_unopt) / CLOCKS_PER_SEC;
    
    double T_optimized = (double)(end_total_opt - start_total_opt) / CLOCKS_PER_SEC;
    double T_processing_opt = (double)(end_proc_opt - start_proc_opt) / CLOCKS_PER_SEC;

    double measured_speedup = T_unoptimized / T_optimized;
    double P = T_processing_unopt / T_unoptimized;
    double S = T_processing_unopt / T_processing_opt;
    double theoretical_speedup = 1.0 / ((1.0 - P) + (P / S));

    printf("Searching Algorithm Execution Times (seconds)\n");
    printf("T_unoptimized: (LINEAR SEARCH) %.6f\n", T_unoptimized);
    printf("T_processing_unoptimized: %.6f\n", T_processing_unopt);
    printf("T_optimized:(BINARY SEARCH) %.6f\n", T_optimized);
    printf("T_processing_optimized: %.6f\n\n", T_processing_opt);

    printf("Results\n");
    printf("P (Proportion): %.6f\n", P);
    printf("S (Speedup): %.6f\n", S);
    printf("Measured Overall Speedup: %.6f\n", measured_speedup);
    printf("Theoretical Speedup: %.6f\n", theoretical_speedup);

    free(arr);
    return 0;
}