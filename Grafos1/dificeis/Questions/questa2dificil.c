#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int visited[MAX_N];


void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = graph[v];
    graph[v] = newNode;
}

double dfs(int current, int t, int target) {
    if (t == 0) {
        return current == target ? 1.0 : 0.0;
    }

    visited[current] = 1;

    int unvisitedCount = 0;
    Node* temp = graph[current];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            unvisitedCount++;
        }
        temp = temp->next;
    }

    if (unvisitedCount == 0) {
        return current == target ? 1.0 : 0.0;
    }

    double probability = 0.0;
    temp = graph[current];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            probability += (1.0 / unvisitedCount) * dfs(temp->vertex, t - 1, target);
        }
        temp = temp->next;
    }

    visited[current] = 0;
    return probability;
}

// Função principal para calcular a posição da rã
double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;
        visited[i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(u, v);
    }

    return dfs(1, t, target);
}