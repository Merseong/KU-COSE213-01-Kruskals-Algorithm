#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Weighted graph.
typedef struct _Graph {
	int verticeSize;
	int edgeSize;
	int* edgeStart;
	int** edges;
	int** weight;
} Graph;

// Basic Graph Functions
Graph* InitGraph();
int AddWeightedEdge(Graph* graph, int from, int to, int weight);
void PrintGraph(Graph* graph);

// To Extend Boolean Array
void SetValue(Graph* graph, int x, int y);

void TPrintGraph(Graph* graph);

int main()
{
	Graph* currentGraph = InitGraph();

	// Get size of edges
	while (1) 
	{
		printf("Enter size of edges (maximum is %d): ", currentGraph->verticeSize * (currentGraph->verticeSize - 1) / 2);
		scanf("%d", &(currentGraph->edgeSize));
		if (currentGraph->edgeSize > currentGraph->verticeSize * (currentGraph->verticeSize - 1) / 2 || currentGraph->edgeSize < 0) continue;
		else break;
	}

	// Get weighted edges
	printf("Type weighted edge,\nschema: (int from) (int to) (int weight)\n");
	for (int i = 0; i < currentGraph->edgeSize; i++)
	{
		int from, to, weight;
		scanf("%d %d %d", &from, &to, &weight);
		if (AddWeightedEdge(currentGraph, from, to, weight)) i--;
	}

	// Print currntGraph
	PrintGraph(currentGraph);

	return 0;
}

void TPrintGraph(Graph* graph)
{
	//for (int i = 0; i < graph->verticeSize; i++)
	//{
	//	if (graph->edgeStart[i] >= 0)
	//	{
	//		int next = graph->edgeStart[i];

	//		while (next >= 0)
	//		{
	//			printf("%d %d %d\n", i, next, graph->edges[i][next]);
	//		}
	//	}
	//}
	//printf("\n\n\n");
	for (int i = 0; i < graph->verticeSize; i++)
	{
		for (int j = 0; j < graph->verticeSize; j++)
		{
			printf(" %d ", graph->edges[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < graph->verticeSize; i++)
	{
		printf(" %d ", graph->edgeStart[i]);
	}
}

// Create size*size matrix to show edge of matrix and its cost.
Graph* InitGraph()
{
	Graph* output = (Graph*)malloc(sizeof(Graph));;
	int size = 0;
	output->edgeSize = 0;

	// Get size of vertices
	while (1) 
	{
		printf("Enter size of vertices (maximum is %d): ", MAX_VERTICES);
		scanf("%d", &size);
		if (!(size > MAX_VERTICES) && !(size < 1)) break;
	}
	output->verticeSize = size;
	output->edgeStart = (int*)calloc(size, sizeof(int));
	for (int i = 0; i < size; i++) output->edgeStart[i] = -1;

	// Make adjacency matrix
	output->edges = (int**)malloc(sizeof(int*) * size);
	output->weight = (int**)malloc(sizeof(int*) * size);
	if (output->edges && output->weight)
	{
		for (int i = 0; i < size; i++)
		{
			output->weight[i] = (int*)calloc(size, sizeof(int));
			output->edges[i] = (int*)calloc(size, sizeof(int));
			if (output->weight[i] == NULL || output->edges[i] == NULL)
			{
				fprintf(stderr, "[ERROR] Can't create graph cause malloc problem.\n");
				exit(1);
			}
		}
		return output;
	}
	else
	{
		fprintf(stderr, "[ERROR] Can't create graph cause malloc problem.\n");
		exit(1);
	}
}

// Add one weighted edge to graph.
int AddWeightedEdge(Graph* graph, int from, int to, int weight)
{
	// Error handling
	if (from > graph->verticeSize || from < 0 || to > graph->verticeSize || to < 0)
	{
		printf("[CAUTION] Wrong node number.\n");
		return 1;
	}
	else if (graph->edges[from][to] || graph->edges[to][from])
	{
		printf("[CAUTION] Already have another edge between node %d and %d\n", from, to);
		return 1;
	}
	else if (from == to)
	{
		printf("[CAUTION] Node number can not be same.\n");
		return 1;
	}
	
	SetValue(graph, from, to);
	graph->weight[from][to] = weight;
	SetValue(graph, to, from);
	graph->weight[to][from] = weight;
	return 0;
}

// Prints graph.
void PrintGraph(Graph* graph)
{
	printf("\n 旨  vertexSize: %d, (node 0 to node %d)\n", graph->verticeSize, graph->verticeSize - 1);
	printf(" 朵  edgeSize: %d\n 朵  list of edges with weight\n", graph->edgeSize);
	printf(" 朵式式  | from |  to  |weight|\n");

	for (int i = 0; i < graph->verticeSize; i++)
	{
		int next = graph->edgeStart[i];
		while (next >= 0 && next < i) next = graph->edges[i][next];

		while (graph->edgeStart[i] >= 0)
		{
			if (next < 0) break;
			printf(" 朵式式  |%6d|%6d|%6d|\n", i, next, graph->weight[i][next]);
			next = graph->edges[i][next];
		}
	}
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收");
}

void SetValue(Graph* graph, int x, int y)
{
	if (graph->edges[x][y])
	{
		printf("[CAUTION] Already true.\n");
		return;
	}

	if (graph->edgeStart[x] < 0) // when first value in row
	{
		graph->edgeStart[x] = y;
		graph->edges[x][y] = -1;
	}
	else if (graph->edgeStart[x] > y) // when have smallest col
	{
		graph->edges[x][y] = graph->edgeStart[x];
		graph->edgeStart[x] = y;
	}
	else // when have middle or biggest col
	{
		int next = graph->edgeStart[x];
		int prevCol = -1;
		while (next > 0)
		{
			if (next > y)
			{
				break;
			}
			else
			{
				prevCol = next;
				next = graph->edges[x][next];
			}
		}
		graph->edges[x][prevCol] = y;
		graph->edges[x][y] = next;
	}
	return;
}