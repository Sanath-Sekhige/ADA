#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int a[], int b[], int low, int mid, int high) {
    int i = low, h = low, j = mid + 1;
    while (h <= mid && j <= high) b[i++] = (a[h] < a[j]) ? a[h++] : a[j++];
    while (h <= mid) b[i++] = a[h++];
    while (j <= high) b[i++] = a[j++];
    for (i = low; i <= high; i++) a[i] = b[i];
}

void mergeSort(int a[], int b[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(a, b, low, mid);
        mergeSort(a, b, mid + 1, high);
        merge(a, b, low, mid, high);
    }
}

double measureTime(int a[], int b[], int n) {
    clock_t start = clock();
    mergeSort(a, b, 0, n - 1);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

void generateArray(int a[], int n, int type) {
    for (int i = 0; i < n; i++)
        a[i] = (type == 1) ? i : (type == 0) ? rand() % 100000 : n - i;
}

int main() {
    srand(time(NULL));
    FILE *fp = fopen("merge_sort_data.txt", "w");
    fprintf(fp, "Size\tBest\tAvg\tWorst\n");

    int a[100000], b[100000];
    for (int n = 10000; n <= 100000; n += 10000) {
        generateArray(a, n, 1); double best = measureTime(a, b, n);
        generateArray(a, n, 0); double avg = measureTime(a, b, n);
        generateArray(a, n, 2); double worst = measureTime(a, b, n);
        fprintf(fp, "%d\t%.6lf\t%.6lf\t%.6lf\n", n, best, avg, worst);
    }
    fclose(fp);

    FILE *gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title 'Merge Sort Runtime'; \
                set ylabel 'Time(s)'; \
                set xlabel 'Input Size'; \
                plot for [i=2:4] 'merge_sort_data.txt' using 1:i title columnheader(i) with lines\n");
    fclose(gp);

    return 0;
}
