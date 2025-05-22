#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int profits[], int weights[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;
    int profits[100], weights[100];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter capacity of knapsack: ");
    scanf("%d", &capacity);

    printf("Enter profit and weight for each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d - Profit and Weight: ", i + 1);
        scanf("%d %d", &profits[i], &weights[i]);
    }

    int result = knapsack(profits, weights, n, capacity);
    printf("Maximum Profit: %d\n", result);

    return 0;
}
