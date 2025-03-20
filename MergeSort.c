#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void merge(int a[], int b[], int low, int mid, int high) {
    int i = low, h = low, j = mid + 1;
    while (h <= mid && j <= high) b[i++] = (a[h] < a[j]) ? a[h++] : a[j++];
    while (h <= mid) b[i++] = a[h++];
    while (j <= high) b[i++] = a[j++];
    for (i = low; i <= high; i++) a[i] = b[i];
}

void merge_sort(int a[], int b[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(a, b, low, mid);
        merge_sort(a, b, mid + 1, high);
        merge(a, b, low, mid, high);
    }
}

double get_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + (t.tv_usec / 1000000.0);
}

void fill_array(int a[], int n, int mode) {
    for (int i = 0; i < n; i++)
        a[i] = (mode == 0) ? i : (mode == 1) ? rand() % 100000 : n - i;
}

int main() {
    int a[100000], b[100000];
    FILE *fp = fopen("Sorting.txt", "w");
    
    printf("\nItems\tBest Case\tAverage Case\tWorst Case\n");
    for (int n = 10000; n <= 80000; n *= 2) {
        double times[3];
        for (int i = 0; i < 3; i++) {
            fill_array(a, n, i);
            double start = get_time();
            merge_sort(a, b, 0, n - 1);
            times[i] = get_time() - start;
        }
        printf("%d\t%lf\t%lf\t%lf\n", n, times[0], times[1], times[2]);
        fprintf(fp, "%d\t%lf\t%lf\t%lf\n", n, times[0], times[1], times[2]);
    }
    fclose(fp);
    printf("\nData written to 'Sorting.txt'.\n");
    
    FILE *pipe = popen("gnuplot --persist", "w");
    fprintf(pipe, "set title 'Runtime Analysis of Merge Sort';\nset xlabel 'Items';\nset ylabel 'Time (seconds)';\n");
    fprintf(pipe, "plot 'Sorting.txt' using 1:2 with lines title 'Best', 'Sorting.txt' using 1:3 with lines title 'Avg', 'Sorting.txt' using 1:4 with lines title 'Worst'\n");
    fclose(pipe);
    return 0;
}
