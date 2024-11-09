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