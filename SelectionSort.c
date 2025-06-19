#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void generate_random(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) 
          if (arr[j] < arr[min_idx]) min_idx = j;
        int temp = arr[i]; 
        arr[i] = arr[min_idx]; 
        arr[min_idx] = temp;
    }
}

int main() {
    int arr[100000];
    struct timeval t;
    FILE *fp = fopen("Sorting.txt", "w"), *pipe;

    for (int i = 10000; i <= 80000; i *= 2) {
        generate_random(arr, i);
        gettimeofday(&t, NULL);
        double start = t.tv_sec + (t.tv_usec / 1e6);
        selection_sort(arr, i);
        gettimeofday(&t, NULL);
        double end = t.tv_sec + (t.tv_usec / 1e6);
        printf("%d\t%lf\n", i, end - start);
        fprintf(fp, "%d\t%lf\n", i, end - start);
    }
    
    fclose(fp);
    pipe = popen("gnuplot --persist", "w");
    fprintf(pipe, "set title 'Selection Sort Runtime'; \
               set ylabel 'Time (s)'; \
               set xlabel 'Input Size'; \
               plot 'Sorting.txt' using 1:2 title 'Selection Sort' with linespoints\n");

    fclose(pipe);
    return 0;
}
