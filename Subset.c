#include <stdio.h>

void printSubset(int *subset, int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) printf("%d ", subset[i]);
    printf("}\n");
}

void findSubsets(int *set, int n, int target) {
    int subset[n], total = 1 << n;
    for (int i = 0; i < total; i++) {
        int sum = 0, k = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset[k++] = set[j];
                sum += set[j];
            }
        }
        if (sum == target) printSubset(subset, k);
    }
}

int main() {
    int set[10], n, target;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &set[i]);
    printf("Enter target sum: ");
    scanf("%d", &target);
    findSubsets(set, n, target);
    return 0;
}
