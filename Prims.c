#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define SIZE 10

int findMinKey(int key[], bool visited[], int n) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void primMST(int graph[SIZE][SIZE], int n) {
    int key[n], parent[n];
    bool visited[n];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinKey(key, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
}

int main() {
    int n, graph[SIZE][SIZE];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, n);
    return 0;
}
