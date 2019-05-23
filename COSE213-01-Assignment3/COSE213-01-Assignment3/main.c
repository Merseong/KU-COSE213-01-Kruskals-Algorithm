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

// Used functions
int* Kruskal(Graph* graph);
int Find(int spanning[], int node);
void Union(int spanning[], int c1, int c2, int count);
void PutIn(Graph* graph, int from, int to, int cost, int index);
void Sort(Edge** edges, int start, int end);
void Swap(Edge** edges, int l, int r);
void Print(Graph* graph, int* spanning);

int main()
{
	printf("\nKU Data Structure (2019-1) - Assignment #3, Kruskal's Algorithm\n");
	printf("2018320205 �Ŵ뼺\n\n");

	Graph* graph = (Graph*)malloc(sizeof(Graph));

	// Get size of nodes
	int temp;
	printf("Enter the size of vertices (maximum %d): ", MAX_VERTICES);
	while (1)             
	{
		scanf("%d", &temp);
		if (temp <= MAX_VERTICES && temp > 0) break;
	}
	graph->nodeCount = temp;

	// Get size of edges
	int maxEdge = temp * (temp - 1) / 2;
	printf("Enter the size of edges (maximum %d): ", maxEdge);
	while (1)
	{
		scanf("%d", &temp);
		if (temp <= maxEdge) break;
	}
	graph->edgeCount = temp;
	graph->edges = (Edge**)malloc(sizeof(Edge*) * graph->edgeCount);

	// Get edges
	printf("Enter the edges (from to cost)\n");
	for (int i = 0; i < graph->edgeCount; i++)
	{
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		if (from == to || from < 0 || to < 0 || from >= graph->nodeCount || to >= graph->nodeCount)
		{
			printf("[ERROR] invalid input\n");
			i--;
			continue;
		}
		int sameCheck = 0;
		for (int j = 0; j < i; j++)
		{
			if ((graph->edges[j]->u == (from < to ? from : to)) && (graph->edges[j]->v == (from < to ? to : from)))
			{
				printf("[ERROR] invalid input\n");
				i--;
				sameCheck = 1;
				break;
			}
		}
		if (sameCheck) continue;
		graph->edges[i] = (Edge*)malloc(sizeof(Edge));
		PutIn(graph, from, to, cost, i);
	}

	int* spanning = Kruskal(graph);
	Print(graph, spanning);

	for (int i = 0; i < graph->edgeCount; i++) free(graph->edges[i]);
	free(graph->edges);
	free(graph);
	free(spanning);
	return 0;
}

// Prints spanning graph
void Print(Graph* graph, int* spanning)
{
	if (spanning != NULL)
	{
		int costSum = 0;

		printf("\nUsed Edge in Kruskal Spanning Graph: \n");
		for (int i = 0; i < graph->nodeCount - 1; i++)
		{
			printf("%d %d %d\n", graph->edges[spanning[i]]->u, graph->edges[spanning[i]]->v, graph->edges[spanning[i]]->cost);
			costSum += graph->edges[spanning[i]]->cost;
		}
		printf("\nTotal Cost Sum: %d\n", costSum);
	}
	else
	{
		printf("\nThis Graph do not have Spanning Graph with Kruskal's Algorithm.");
	}
}

// Perform Kruskal's Algorithm, and check validity of spanning graph.
int* Kruskal(Graph* graph)
{
	int spanSize = graph->nodeCount - 1;
	int* output = (int*)malloc(sizeof(int) * spanSize);
	for (int i = 0; i < spanSize; i++) output[i] = -1;
	int* parentCheck = (int*)malloc(sizeof(int) * spanSize);
	for (int i = 0; i < spanSize; i++) parentCheck[i] = i;
	int* validCheck = (int*)calloc(graph->nodeCount, sizeof(int));

	Sort(graph->edges, 0, graph->edgeCount - 1);

	// Check is there will make loop
	int index = 0;
	for (int i = 0; i < graph->edgeCount; i++)
	{
		int parent1 = Find(parentCheck, graph->edges[i]->u);
		int parent2 = Find(parentCheck, graph->edges[i]->v);

		if (parent1 != parent2)
		{
			output[index++] = i;
			Union(parentCheck, parent1, parent2, graph->nodeCount);
			validCheck[graph->edges[i]->u] = 1;
			validCheck[graph->edges[i]->v] = 1;
		}
	}
	// check validity
	int valid = 1;
	for (int i = 0; i < graph->nodeCount; i++)
	{
		if (!validCheck[i])
		{
			valid = 0;
			break;
		}
	}

	if (valid) return output;
	else return NULL;
}

// Find its parent.
int Find(int spanning[], int node)
{
	return (spanning[node]);
}

// Change top parent.
void Union(int spanning[], int c1, int c2, int count)
{
	for (int i = 0; i < count; i++)
		if (spanning[i] == c2) spanning[i] = c1;
}

// Put input edge to graph.
void PutIn(Graph* graph, int u, int v, int cost, int index)
{
	graph->edges[index]->u = u < v ? u : v;
	graph->edges[index]->v = u < v ? v : u;
	graph->edges[index]->cost = cost;
}

// Use quick sort.
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

// Swap index of edges[l] and edges[r].
void Swap(Edge** edges, int l, int r)
{
	Edge* temp = edges[l];
	edges[l] = edges[r];
	edges[r] = temp;
}
