#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[], int low, int high) {
    int i = low, j = high, p = a[low];
    while (i < j) {
        while (i < high && a[++i] < p);
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
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;

    if (type == 1) {
        quickSort(arr, 0, n - 1);
    } else if (type == 2) {
        quickSort(arr, 0, n - 1);
        for (int i = 0; i < n / 2; i++)
            swap(&arr[i], &arr[n - i - 1]);
    }
}

double measureTime(int arr[], int n) {
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    FILE *fp = fopen("Sorting.txt", "w");

    fprintf(fp, "Size\tBest(Random)\tAvg(Reverse)\tWorst(Sorted)\n");

    for (int n = 10000; n <= 100000; n += 10000) {
        int *arr = malloc(n * sizeof(int));

        generateArray(arr, n, 0); double best = measureTime(arr, n);     // Random → Best
        generateArray(arr, n, 2); double avg = measureTime(arr, n);      // Reversed → Avg (worse than random)
        generateArray(arr, n, 1); double worst = measureTime(arr, n);    // Sorted → Worst for pivot=first

        fprintf(fp, "%d\t%.6lf\t%.6lf\t%.6lf\n", n, best, avg, worst);
        free(arr);
    }

    fclose(fp);

    // Plot using gnuplot
    FILE *gp = popen("gnuplot -persist", "w");
    if (gp) {
        fprintf(gp,
            "set title 'Quick Sort Runtime (Pivot = First Element)'\n"
            "set xlabel 'Input Size'\n"
            "set ylabel 'Time (seconds)'\n"
            "plot 'Sorting.txt' using 1:2 title 'Best (Random)' with lines, "
                 "'Sorting.txt' using 1:3 title 'Avg (Reversed)' with lines, "
                 "'Sorting.txt' using 1:4 title 'Worst (Sorted)' with lines\n");
        fclose(gp);
    } else {
        printf("Gnuplot not available.\n");
    }

    return 0;
}
