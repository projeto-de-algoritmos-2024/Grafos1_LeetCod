#include <limits.h>

#define INF 10000000

int findTheCity(int n, int** edges, int edgesSize, int* edgesColSize, int distanceThreshold) {
    int d[n][n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        d[u][v] = w;
        d[v][u] = w;
    }

    //Floyd-Warshall 
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (d[i][k] < INF) {
                for (int j = 0; j < n; j++) {
                    if (d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }
    }

    int z = n - 1, o = n;
    for (int i = n - 1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (d[i][j] <= distanceThreshold) count++;
        }
        if (count < o) {
            z = i;
            o = count;
        }
    }

    return z;
    
}
