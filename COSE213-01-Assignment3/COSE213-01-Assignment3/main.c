#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct _Edge {
	int u, v; // u < v
	int cost;
} Edge;

typedef struct _Graph {
	Edge** edges;
	int edgeCount; // number of edge
	int nodeCount; // number of node
} Graph;

void Kruskal(Graph* graph);
int Find(int spanning[], int node);
void Union(int spanning[], int c1, int c2, int count);
void PutIn(Graph* graph, int from, int to, int cost, int index);
void Sort(Edge** edges, int start, int end);
void Swap(Edge** edges, int l, int r);

int main()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));

	int temp;
	printf("Enter the size of vertices (maximum 100): ");
	while (1)             
	{
		scanf("%d", &temp);
		if (temp <= MAX_VERTICES && temp > 0) break;
	}
	graph->nodeCount = temp;

	int minEdge = temp - 1;
	int maxEdge = temp * (temp - 1) / 2;
	printf("Enter the size of edges (minimum %d, maximum %d): ", minEdge, maxEdge);
	while (1)
	{
		scanf("%d", &temp);
		if (temp <= maxEdge && temp >= minEdge) break;
	}
	graph->edgeCount = temp;
	graph->edges = (Edge**)malloc(sizeof(Edge*) * graph->edgeCount);

	printf("Enter the edges (from to cost)\n");
	for (int i = 0; i < graph->edgeCount; i++)
	{
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		if (from == to || from < 0 || to < 0)
		{
			printf("[ERROR] invalid input");
			i--;
			continue;
		}
		graph->edges[i] = (Edge*)malloc(sizeof(Edge));
		PutIn(graph, from, to, cost, i);
	}

	Sort(graph->edges, 0, graph->edgeCount - 1);

	//Kruskal(graph);
	//Print(graph);

	for (int i = 0; i < graph->edgeCount; i++) free(graph->edges[i]);
	free(graph->edges);
	free(graph);
	return 0;
}

void Kruskal(Graph* graph)
{

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

void PutIn(Graph* graph, int u, int v, int cost, int index)
{
	graph->edges[index]->u = u < v ? u : v;
	graph->edges[index]->v = u < v ? v : u;
	graph->edges[index]->cost = cost;
}

void Sort(Edge** edges, int start, int end)
{
	int mid = (start + end) / 2;
	int pivot = edges[mid]->cost;
	int L = start, R = end;

	while (L <= R)
	{
		while (edges[L]->cost < pivot) L++;
		while (edges[R]->cost > pivot) R--;

		if (L <= R)
		{
			if (L != R) Swap(edges, L, R);
			L++; R--;
		}
	}

	if (start < R)
		Sort(edges, start, R);
	if (L < end)
		Sort(edges, L, end);
}

void Swap(Edge** edges, int l, int r)
{
	Edge* temp = edges[l];
	edges[l] = edges[r];
	edges[r] = temp;
}