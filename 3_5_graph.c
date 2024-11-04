#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Graph {
  int vertices;
  int adjacencyMatrix[MAX][MAX];
  struct Node *adjacencyList[MAX];
} Graph;

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

// Function prototypes
Graph *createGraph(int vertices);
void addEdge(Graph *graph, int src, int dest);
void printAdjacencyMatrix(Graph *graph);
void printAdjacencyList(Graph *graph);
void dfs(Graph *graph, int vertex, bool visited[]);
void bfs(Graph *graph, int startVertex);
Node *createNode(int vertex);
void freeGraph(Graph *graph);

int main() {
  int vertices, edges, src, dest;

  printf("Enter the number of vertices: ");
  scanf("%d", &vertices);

  Graph *graph = createGraph(vertices);

  printf("Enter the number of edges: ");
  scanf("%d", &edges);

  for (int i = 0; i < edges; i++) {
    printf("Enter edge %d (src dest): ", i + 1);
    scanf("%d %d", &src, &dest);
    addEdge(graph, src, dest);
  }

  printf("\nAdjacency Matrix:\n");
  printAdjacencyMatrix(graph);

  printf("\nAdjacency List:\n");
  printAdjacencyList(graph);

  printf("\nDepth First Search (DFS):\n");
  bool visited[MAX] = {false};
  dfs(graph, 0, visited); // Starting from vertex 0
  printf("\n");

  printf("\nBreadth First Search (BFS):\n");
  bfs(graph, 0); // Starting from vertex 0
  printf("\n");

  freeGraph(graph);
  return 0;
}

// Create a graph with the specified number of vertices
Graph *createGraph(int vertices) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->vertices = vertices;

  for (int i = 0; i < vertices; i++) {
    graph->adjacencyList[i] = NULL;
    for (int j = 0; j < vertices; j++) {
      graph->adjacencyMatrix[i][j] = 0; // Initialize the adjacency matrix
    }
  }
  return graph;
}

// Create a new node for the adjacency list
Node *createNode(int vertex) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
}

// Add an edge to the graph (undirected)
void addEdge(Graph *graph, int src, int dest) {
  // Update the adjacency matrix
  graph->adjacencyMatrix[src][dest] = 1;
  graph->adjacencyMatrix[dest][src] = 1; // Undirected graph

  // Update the adjacency list
  Node *newNode = createNode(dest);
  newNode->next = graph->adjacencyList[src];
  graph->adjacencyList[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjacencyList[dest];
  graph->adjacencyList[dest] = newNode;
}

// Print the adjacency matrix
void printAdjacencyMatrix(Graph *graph) {
  for (int i = 0; i < graph->vertices; i++) {
    for (int j = 0; j < graph->vertices; j++) {
      printf("%d ", graph->adjacencyMatrix[i][j]);
    }
    printf("\n");
  }
}

// Print the adjacency list
void printAdjacencyList(Graph *graph) {
  for (int i = 0; i < graph->vertices; i++) {
    printf("%d: ", i);
    Node *temp = graph->adjacencyList[i];
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("NULL\n");
  }
}

// Depth First Search (DFS) algorithm
void dfs(Graph *graph, int vertex, bool visited[]) {
  visited[vertex] = true;
  printf("%d ", vertex);

  Node *temp = graph->adjacencyList[vertex];
  while (temp) {
    if (!visited[temp->vertex]) {
      dfs(graph, temp->vertex, visited);
    }
    temp = temp->next;
  }
}

// Breadth First Search (BFS) algorithm
void bfs(Graph *graph, int startVertex) {
  bool visited[MAX] = {false};
  int queue[MAX], front = 0, rear = 0;

  visited[startVertex] = true;
  queue[rear++] = startVertex;

  while (front < rear) {
    int currentVertex = queue[front++]; // Dequeue
    printf("%d ", currentVertex);

    Node *temp = graph->adjacencyList[currentVertex];
    while (temp) {
      if (!visited[temp->vertex]) {
        visited[temp->vertex] = true;
        queue[rear++] = temp->vertex; // Enqueue
      }
      temp = temp->next;
    }
  }
}

// Free the graph memory
void freeGraph(Graph *graph) {
  for (int i = 0; i < graph->vertices; i++) {
    Node *temp = graph->adjacencyList[i];
    while (temp) {
      Node *toFree = temp;
      temp = temp->next;
      free(toFree);
    }
  }
  free(graph);
}
