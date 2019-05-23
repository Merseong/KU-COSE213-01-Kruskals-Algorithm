#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct _Edge {
	int u, v;
	int cost;
} Edge;

typedef struct _Graph {
	Edge* edges;
	int edgeCount; // number of edge
	int nodeCount; // number of node
} Graph;

void kruskal(Graph* graph);
int Find(int spanning[], int node);
void Union(int spanning[], int c1, int c2, int count);
int PutIn(Graph* graph, int from, int to, int cost);

int main()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));

	int temp;
	printf("Enter the size of vertices (maximum 100): ");
	while (1)             
	{
		scanf("%d", &temp);
		if (temp <= MAX_VERTICES) break;
	}
	graph->nodeCount = temp;

	int maxEdge = temp * (temp - 1) / 2;
	printf("Enter the size of edges (maximum %d): ", maxEdge);
	while (1)
	{
		scanf("%d", &temp);
		if (temp <= maxEdge) break;
	}
	graph->edgeCount = temp;
	graph->edges = (Edge*)malloc(sizeof(Edge) * graph->edgeCount);

	printf("Enter the edges (from to cost)\n");
	for (int i = 0; i < graph->edgeCount; i++)
	{
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		PutIn(graph, from, to, cost);
	}

	kruskal(graph);
	Print(graph);

	free(graph->edges);
	free(graph);
	return 0;
}

int Find(int spanning[], int node)
{
	return(spanning[node]);
}

void Union(int spanning[], int c1, int c2, int count)
{
	for (int i = 0; i < count; i++)
		if (spanning[i] == c2) spanning[i] = c1;
}