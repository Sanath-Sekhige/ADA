#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int partition(int a[], int low, int high) {
    int i = low, j = high, p = a[low];
    while (i < j) {
        while (a[++i] < p && i < high);
        while (a[--j] > p);
        if (i < j) swap(&a[i], &a[j]);
    }
    swap(&a[low], &a[j]);
    return j;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void generateArray(int arr[], int n, int type) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
    if (type) quickSort(arr, 0, n - 1);
    if (type == 2) for (int i = 0; i < n / 2; i++) swap(&arr[i], &arr[n - i - 1]);
}

double measureTime(int arr[], int n) {
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    FILE *fp = fopen("quick_sort_data.txt", "w");
    fprintf(fp, "Size BestCase AvgCase WorstCase\n");

    for (int n = 100; n <= 5000; n += 100) {
        int arr[n];
        generateArray(arr, n, 1); double best = measureTime(arr, n);
        generateArray(arr, n, 0); double avg = measureTime(arr, n);
        generateArray(arr, n, 2); double worst = measureTime(arr, n);
        fprintf(fp, "%d %.6f %.6f %.6f\n", n, best, avg, worst);
    }
    fclose(fp);

    FILE *gp = popen("gnuplot -persistent", "w");
    fprintf(gp, "set title 'Quick Sort Performance'\nset xlabel 'Size'\nset ylabel 'Time (s)'\n");
    fprintf(gp, "plot for [i=2:4] 'quick_sort_data.txt' using 1:i title columnheader(i) with lines\n");

    return 0;
}
