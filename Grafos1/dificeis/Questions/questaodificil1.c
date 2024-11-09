#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maximalPathQuality(int* values, int valuesSize, int** edges, int edgesSize, int* edgesColSize, int maxTime) {
    int** adjList = (int**)malloc(valuesSize * sizeof(int*));
    int** adjWeights = (int**)malloc(valuesSize * sizeof(int*));
    int* adjListSize = (int*)calloc(valuesSize, sizeof(int));

    for (int i = 0; i < valuesSize; ++i) {
        adjList[i] = (int*)malloc(valuesSize * sizeof(int));
        adjWeights[i] = (int*)malloc(valuesSize * sizeof(int));
    }

        // Construindo o grafo
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        adjList[u][adjListSize[u]] = v;
        adjWeights[u][adjListSize[u]++] = w;
        adjList[v][adjListSize[v]] = u;
        adjWeights[v][adjListSize[v]++] = w;
    }

    //int maxPathQuality = INT_MIN;

    void dfs(int u, int timeLeft, int currentQuality, int* visited) {
        if (timeLeft < 0) return;

        
        if (visited[u] == 0) {
            currentQuality += values[u];
    }
}