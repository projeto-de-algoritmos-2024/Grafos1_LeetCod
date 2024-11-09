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

}