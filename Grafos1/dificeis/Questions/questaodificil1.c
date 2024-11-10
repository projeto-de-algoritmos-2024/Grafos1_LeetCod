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

    int maxPathQuality = INT_MIN;

    // Função DFS para explorar o grafo
    void dfs(int u, int timeLeft, int currentQuality, int* visited) {
        if (timeLeft < 0) return;

        // Se é a primeira visita ao nó, soma o valor ao caminho
        if (visited[u] == 0) {
            currentQuality += values[u];
        }
        
        visited[u]++;
        
        // Verifica se chegamos de volta ao nó 0 com tempo restante
        if (u == 0) {
            if (currentQuality > maxPathQuality) {
                maxPathQuality = currentQuality;
            }
        }

        // Explora vizinhos
        for (int i = 0; i < adjListSize[u]; ++i) {
            int v = adjList[u][i];
            int w = adjWeights[u][i];
            dfs(v, timeLeft - w, currentQuality, visited);
        }

        // Volta para o estado anterior para exploração de novos caminhos
        visited[u]--;
    }

    // Array para monitorar as visitas a cada nó
    int* visited = (int*)calloc(valuesSize, sizeof(int));

    // Inicia a DFS a partir do nó 0 com o tempo máximo
    dfs(0, maxTime, 0, visited);

    for (int i = 0; i < valuesSize; ++i) {
        free(adjList[i]);
        free(adjWeights[i]);
    }
    free(adjList);
    free(adjWeights);
    free(adjListSize);
    free(visited);

    return maxPathQuality;
}
