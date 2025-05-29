#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a[30], count = 0;

int place(int pos) {
    for (int i = 1; i < pos; i++) {
        if (a[i] == a[pos] || abs(a[i] - a[pos]) == abs(i - pos))
            return 0;
    }
    return 1;
}

void print_sol(int n) {
    count++;
    printf("\nSolution #%d:\n", count);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%s\t", (a[i] == j) ? "Q" : "*");
        printf("\n");
    }
}

void queen(int n) {
    int k = 1;
    a[k] = 0;

    while (k != 0) {
        do {
            a[k]++;
        } while (a[k] <= n && !place(k));

        if (a[k] <= n) {
            if (k == n)
                print_sol(n);
            else {
                k++;
                a[k] = 0;
            }
        } else {
            k--;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of Queens: ");
    scanf("%d", &n);
    queen(n);
    printf("\nTotal solutions = %d\n", count);
    return 0;
}
