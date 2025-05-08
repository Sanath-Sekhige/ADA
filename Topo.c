#include <stdio.h>
#define MAX 10

int vis[MAX], stack[MAX], top = -1, adj[MAX][MAX];

void dfs(int node, int n) {
    vis[node] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[node][i] && !vis[i]) {
            dfs(i, n);
        }
    }
    stack[++top] = node;
}

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i])
            dfs(i, n);
    }

    printf("Topological Sort:\n");
    while (top != -1) {
        printf("%d ", stack[top--] + 1);
    }
    printf("\n");

    return 0;
}
