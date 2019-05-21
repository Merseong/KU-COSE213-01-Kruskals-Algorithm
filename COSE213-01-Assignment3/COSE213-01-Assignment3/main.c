#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct _Graph {
	int verticeSize;
	int edgeSize;
	int** weight; // weighted graph == network
} Graph;

Graph* InitGraph();
void AddWeightedEdge(Graph* graph, int from, int to, int weight);
void PrintGraph(Graph* graph);

int main()
{
	Graph* currentGraph = InitGraph();

	return 0;
}

// create size*size matrix to show edge of matrix and its cost.
Graph* InitGraph()
{
	Graph* output = (Graph*)malloc(sizeof(Graph));;
	int size = 0;
	int** graph;
	output->weight = graph;
	output->edgeSize = 0;

	while (1)
	{
		printf("Enter size of vertices (maximum is %d): ", MAX_VERTICES);
		scanf("%d", &size);
		if (!(size > MAX_VERTICES) && !(size < 1)) break;
	}
	output->verticeSize = size;

	output->weight = graph = (int**)malloc(sizeof(int*) * size);
	if (graph != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			graph[i] = (int*)calloc(size, sizeof(int));
			if (graph[i] == NULL)
			{
				printf("[ERROR] Can't create graph cause malloc problem.");
				exit(1);
			}
		}
		return output;
	}
	else
	{
		printf("[ERROR] Can't create graph cause malloc problem.");
		exit(1);
	}
}