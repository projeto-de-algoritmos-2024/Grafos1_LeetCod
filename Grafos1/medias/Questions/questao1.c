#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Função principal para calcular a qualidade máxima do caminho com tempo limitado
int maximalPathQuality(int* values, int valuesSize, int** edges, int edgesSize, int* edgesColSize, int maxTime) {
    
    // Aloca memória para as listas de adjacência e pesos dos nós
    int** adjList = (int**)malloc(valuesSize * sizeof(int*)); // Lista de adjacências
    int** adjWeights = (int**)malloc(valuesSize * sizeof(int*)); // Pesos das arestas
    int* adjListSize = (int*)calloc(valuesSize, sizeof(int)); // Tamanho da lista de adjacências para cada nó

    // Inicializa as listas de adjacência e pesos
    for (int i = 0; i < valuesSize; ++i) {
        adjList[i] = (int*)malloc(valuesSize * sizeof(int)); // Aloca espaço para os vizinhos do nó
        adjWeights[i] = (int*)malloc(valuesSize * sizeof(int)); // Aloca espaço para os pesos das arestas
    }

    // Constrói o grafo a partir das arestas fornecidas
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0]; // Nó de origem
        int v = edges[i][1]; // Nó de destino
        int w = edges[i][2]; // Peso da aresta

        // Adiciona o vizinho v a u e o peso w
        adjList[u][adjListSize[u]] = v;
        adjWeights[u][adjListSize[u]++] = w;

        // Adiciona o vizinho u a v e o peso w (grafo não direcionado)
        adjList[v][adjListSize[v]] = u;
        adjWeights[v][adjListSize[v]++] = w;
    }

    // Inicializa a variável para armazenar a qualidade máxima do caminho
    int maxPathQuality = INT_MIN;

    // Função de busca em profundidade (DFS) para explorar o grafo
    void dfs(int u, int timeLeft, int currentQuality, int* visited) {
        // Caso base: se o tempo restante for menor que 0, retorna
        if (timeLeft < 0) return;

        // Se o nó u ainda não foi visitado, soma sua qualidade ao caminho
        if (visited[u] == 0) {
            currentQuality += values[u]; // Adiciona a qualidade do nó u
        }
        
        // Marca o nó como visitado
        visited[u]++;
        
        // Se o nó 0 for alcançado e há tempo restante, compara a qualidade do caminho
        if (u == 0) {
            if (currentQuality > maxPathQuality) {
                maxPathQuality = currentQuality; // Atualiza a qualidade máxima do caminho
            }
        }

        // Explora os vizinhos do nó u
        for (int i = 0; i < adjListSize[u]; ++i) {
            int v = adjList[u][i]; // Vizinho v de u
            int w = adjWeights[u][i]; // Peso da aresta entre u e v
            // Chama recursivamente DFS para o vizinho v com o tempo restante reduzido pelo peso
            dfs(v, timeLeft - w, currentQuality, visited);
        }

        // Desmarca o nó u para que novos caminhos possam ser explorados
        visited[u]--;
    }

    // Array para controlar as visitas a cada nó
    int* visited = (int*)calloc(valuesSize, sizeof(int));

    // Inicia a DFS a partir do nó 0 com o tempo máximo disponível
    dfs(0, maxTime, 0, visited);

    // Libera a memória alocada
    for (int i = 0; i < valuesSize; ++i) {
        free(adjList[i]); // Libera a memória da lista de adjacência de cada nó
        free(adjWeights[i]); // Libera a memória dos pesos de cada nó
    }
    free(adjList); // Libera a memória da lista de adjacência
    free(adjWeights); // Libera a memória dos pesos
    free(adjListSize); // Libera a memória para o tamanho da lista de adjacência
    free(visited); // Libera a memória para o controle de visitas

    // Retorna a qualidade máxima do caminho encontrado
    return maxPathQuality;
}
