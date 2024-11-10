#include <stdio.h>   // Biblioteca padrão para entrada e saída
#include <stdlib.h>  // Biblioteca padrão para alocação de memória

#define MAX_N 100005  // Define o número máximo de vértices na árvore

// Estrutura de um nó para a lista de adjacência
typedef struct Node {
    int vertex;          // Vértice adjacente
    struct Node* next;   // Ponteiro para o próximo nó na lista
} Node;

Node* graph[MAX_N];   // Array de ponteiros para representar o grafo como lista de adjacência
int visited[MAX_N];   // Array para marcar os vértices visitados

// Função para adicionar uma aresta ao grafo
void addEdge(int u, int v) {
    // Adiciona 'v' na lista de adjacência de 'u'
    Node* newNode = (Node*)malloc(sizeof(Node));  // Aloca memória para o novo nó
    newNode->vertex = v;                          // Define o vértice adjacente
    newNode->next = graph[u];                     // Aponta para o próximo nó atual de 'u'
    graph[u] = newNode;                           // Atualiza o início da lista de 'u'

    // Adiciona 'u' na lista de adjacência de 'v'
    newNode = (Node*)malloc(sizeof(Node));        // Aloca memória para o novo nó
    newNode->vertex = u;                          // Define o vértice adjacente
    newNode->next = graph[v];                     // Aponta para o próximo nó atual de 'v'
    graph[v] = newNode;                           // Atualiza o início da lista de 'v'
}

// Função DFS para calcular a probabilidade de estar no vértice 'target' após 't' segundos
double dfs(int current, int t, int target) {
    // Caso base: se o tempo acabou
    if (t == 0) {
        return current == target ? 1.0 : 0.0;   // Retorna 1.0 se estiver no 'target', senão retorna 0.0
    }

    visited[current] = 1;  // Marca o vértice atual como visitado

    int unvisitedCount = 0;       // Conta o número de vizinhos não visitados
    Node* temp = graph[current];  // Ponteiro temporário para percorrer a lista de adjacência

    // Conta os vizinhos não visitados
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            unvisitedCount++;     // Incrementa se o vizinho não foi visitado
        }
        temp = temp->next;        // Move para o próximo nó na lista
    }

    // Se não há vizinhos não visitados, a rã fica parada
    if (unvisitedCount == 0) {
        return current == target ? 1.0 : 0.0;   // Retorna 1.0 se estiver no 'target', senão 0.0
    }

    double probability = 0.0;     // Inicializa a probabilidade acumulada
    temp = graph[current];        // Reinicia o ponteiro para o início da lista

    // Percorre os vizinhos não visitados
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            // Calcula a probabilidade recursivamente
            probability += (1.0 / unvisitedCount) * dfs(temp->vertex, t - 1, target);
        }
        temp = temp->next;  // Move para o próximo nó na lista
    }

    visited[current] = 0;   // Desmarca o vértice atual (backtracking)
    return probability;     // Retorna a probabilidade acumulada
}

// Função principal para calcular a posição da rã após 't' segundos
double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    // Inicializa o grafo e o vetor de visitados
    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;    // Inicializa a lista de adjacência como vazia
        visited[i] = 0;     // Marca todos os vértices como não visitados
    }

    // Constrói o grafo adicionando as arestas
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];   // Pega o vértice 'u' da aresta
        int v = edges[i][1];   // Pega o vértice 'v' da aresta
        addEdge(u, v);         // Adiciona a aresta entre 'u' e 'v'
    }

    // Inicia a DFS a partir do vértice 1
    return dfs(1, t, target);
}
