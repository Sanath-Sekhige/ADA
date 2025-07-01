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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

void generateArray(int arr[], int n, int type) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
    if (type) quickSort(arr, 0, n - 1);
    if (type == 2) for (int i = 0; i < n / 2; i++) swap(&arr[i], &arr[n - i - 1]);
}

double measureTime(int arr[], int n) {
    double start = clock();
    quickSort(arr, 0, n - 1);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    FILE *fp = fopen("Sorting.txt", "w");
    fprintf(fp, "Size\tBest\tAvg\tWorst\n");

    for (int n = 100; n <= 5000; n += 100) {
        int arr[n];
        generateArray(arr, n, 1); double best = measureTime(arr, n);
        generateArray(arr, n, 0); double avg = measureTime(arr, n);
        generateArray(arr, n, 2); double worst = measureTime(arr, n);
        fprintf(fp, "%d\t%.6lf\t%.6lf\t%.6lf\n", n, best, avg, worst);
    }
    fclose(fp);

    FILE* gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title 'Quick Sort Runtime'; \
                set ylabel 'Time(s)'; \
                set xlabel 'Input Size'; \
                plot for [i=2:4] 'Sorting.txt' using 1:i title columnheader(i) with lines\n");
    fclose(gp);
    return 0;
}