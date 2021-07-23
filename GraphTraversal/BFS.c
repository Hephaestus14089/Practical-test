#include <stdio.h>
#include <stdlib.h>

struct Graph {

    int V;  // number of vertices
    int **adj; // adjacency matrix
};

typedef struct Graph Graph;

Graph* new_graph() {

    Graph *graph = (Graph*)malloc(sizeof(Graph));

    graph->V = 0;
    graph->adj = NULL;

    return graph;
} // end of new_graph()

void display_graph(Graph *graph) {

    int **adj = graph->adj;
    int i, j;

    for (i = 0; i < graph->V; i++) {
        
        printf("vertex %d: ", i);

        for (j = 0; j < graph->V; j++) {
        
            if (*(*(adj + i) + j)) {
                printf("%d ", j);
            }
        } // end of inner for loop

        printf("\n");
    } // end of outer loop

} // end of display_graph(Graph*)


// **************  Queue starts  **************

struct Node {

	int data;
	struct Node* next;
};

typedef struct Node Node;

Node* new_node() {

    Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = 0;
    newNode->next = NULL;
        
    return newNode;
} // end of constructor for struct Node


struct Queue {
	
	struct Node* head;
	struct Node* tail;
};

typedef struct Queue Queue;

Queue* new_queue() {
	
	Queue* newQueue = (Queue*)malloc(sizeof(Queue));

	newQueue->head = NULL;
	newQueue->tail = NULL;

	return newQueue;
} // end of constructor for struct Queue

int is_queue_empty(Queue *queue) { return (queue->head == NULL); }

void enqueue(Queue* queue, int value) {

	Node *node = new_node();
	node->data = value;

	if (is_queue_empty(queue)) { queue->head = node; }
	else { (queue->tail)->next = node; }

	queue->tail = node;
} // end of enqueue(Queue*, int)

int dequeue(Queue* queue) {

	if (is_queue_empty(queue)) { return 0; }

	int value = (queue->head)->data;

	Node *node = queue->head;
	queue->head = (queue->head)->next;

	if (queue->head == NULL) { queue->tail = NULL; } // resolving dangling pointer

	free(node);

	return value;
} // end of dequeue(Queue*)

// ***************  Queue ends  ****************

void bfs_traversal(Graph *graph, int starting_vertex) {

    int **adj = graph->adj;

    Queue *queue = new_queue();
    int is_visited[graph->V];
    int i, j;
    int vertex;

    // initialising the is_visited array
    for (i = 0; i <= graph->V; i++) { *(is_visited + i) = 0; }

    enqueue(queue, starting_vertex);
    is_visited[starting_vertex] = 1;

    while (!is_queue_empty(queue)) {

        vertex = dequeue(queue);
        printf("%d ", vertex);

        for (j = 0; j < graph->V; j++) {

            if (*(*(adj + vertex) + j) && !is_visited[j]) {
                
                enqueue(queue, j);
                is_visited[j] = 1;
            }
        } // end of for loop

    } // end of outer while loop

} // end of bfs_traversal(Graph*)

void import_graph(Graph *graph) {

    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL) {

        printf("error: cannot access file\n");
        exit(1);
    }

    int V;
    fscanf(fp, "%d", &V);

    int **adj = (int**)malloc(sizeof(int*) * V);

    int i = 0, j = 0;
    int val = 0;
    
    for (; i < V; i++) { 
        
        *(adj + i) = (int*)malloc(sizeof(int*) * V);

        for (j = 0; j < V; j++) {

            fscanf(fp, "%d", &val);
            *(*(adj + i) + j) = val;
        }
    } // end of outer for loop

    fclose(fp);

    graph->V = V;
    graph->adj = adj;

} // end of import_graph(Graph*)


int main() {

    Graph *graph = new_graph();

    import_graph(graph);

    printf("\nGraph :-\n");
    display_graph(graph);

    int starting_vertex;
    printf("\nEnter starting vertex for bfs traversal: ");
    scanf("%d", &starting_vertex);

    printf("\nBFS traversal: ");
    bfs_traversal(graph, starting_vertex);
    printf("\n");

    return 0;
} // end of main()