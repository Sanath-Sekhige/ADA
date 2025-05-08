#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 10
#define INF INT_MAX

int cost[MAX][MAX];

void dijkstra(int dist[], int start, int n) {
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++)
        dist[i] = (cost[start][i] >= 0) ? cost[start][i] : INF;

    visited[start] = 1;
    dist[start] = 0;

    for (int count = 1; count < n; count++) {
        int minDist = INF, u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] >= 0 && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }
}

int main() {
    int n, start, dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (0 for self, -1 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    clock_t begin = clock();
    dijkstra(dist, start, n);
    clock_t end = clock();

    printf("\nShortest distances from vertex %d:\n", start);
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        if (dist[i] == INF)
            printf("To %d: No path\n", i);
        else
            printf("To %d: %d\n", i, dist[i]);
    }

    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %.6f seconds\n", time);

    return 0;
}
