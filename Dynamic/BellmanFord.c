#include <stdio.h>
#include <stdlib.h>

struct Edge {

    int src; // store source vertex
    int dst; // store destination vertex
};

typedef struct Edge Edge;

Edge* new_edge(int src, int dst) {

    Edge *edge = (Edge*)malloc(sizeof(Edge));

    edge->src = src;
    edge->dst = dst;

    return edge;
} // end of new_edge(int, int)

/* ****************************    Edge ends here    ************************** */


struct Node {

    Edge *edge;
    struct Node *next;
};

typedef struct Node Node;

Node* new_node() { 
    
    Node *node = (Node*)malloc(sizeof(Node));
    
    node->edge = NULL;
    node->next = NULL;

    return node;
} // end of new_node()

struct List {

    Node *head;
};

typedef struct List List;

List* new_list() {

    List *list = (List*)malloc(sizeof(List));

    list->head = NULL;

    return list;
} // end of new_list()

void append(List *list, Edge *edge) {

    Node *node = new_node();
    node->edge = edge;

    if (list->head == NULL) {

        list->head = node;
        return;
    }

    Node *ptr = list->head;

    for (; ptr->next != NULL; ptr = ptr->next);

    ptr->next = node;
} // end of append(List*, Edge*)

/* ****************************    List ends here    ************************** */


struct Graph {

    int V;  // number of vertices
    int *cost; // calculated cost of each vertex from source
    int **adj; // adjacency matrix
    List *edges; // list of edges
};

typedef struct Graph Graph;

Graph* new_graph() {

    Graph *graph = (Graph*)malloc(sizeof(Graph));

    graph->V = 0;
    graph->cost = NULL;
    graph->adj = NULL;
    graph->edges = new_list();

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

void display_edges(Graph *graph) {

    Node *node = (graph->edges)->head;
    Edge *edge;

    printf("Edges: ");

    for (; node != NULL; node = node->next) {

        edge = node->edge;
        printf("(%d, %d) ", edge->src, edge->dst);
    }

    printf("\n");
} // end of display_edges(Graph*)

void import_graph(Graph *graph) {

    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL) {

        printf("error: cannot access file\n");
        exit(1);
    }

    int V;
    fscanf(fp, "%d", &V);

    int *cost = (int*)malloc(sizeof(int) * V);
    int **adj = (int**)malloc(sizeof(int*) * V);

    int i = 0, j = 0;
    int val = 0;

    for (; i < V; i++) {
        *(cost + i) = 0;
    }
    
    for (i = 0; i < V; i++) { 
        
        *(adj + i) = (int*)malloc(sizeof(int*) * V);

        for (j = 0; j < V; j++) {

            fscanf(fp, "%d", &val);
            *(*(adj + i) + j) = val;

            if (val != 0) {
                append(graph->edges, new_edge(i, j));
            }
        } // end of inner for loop
    } // end of outer for loop

    fclose(fp);

    graph->V = V;
    graph->cost = cost;
    graph->adj = adj;

} // end of import_graph(Graph*)

/* ****************************    Graph ends here    ************************* */

int min_of(int x, int y) { return (x < y) ? x : y; }

int find_shortest_paths(Graph *graph) {

    int i = 0;
    Node *node = (graph->edges)->head;
    int **adj = graph->adj;
    int *cost = graph->cost;
    int src, dst;

    int source_vertex = (node->edge)->src;

    for (; i < graph->V - 1; i++) {

        for (; node != NULL; node = node->next) {

            src = (node->edge)->src;
            dst = (node->edge)->dst;

            if (dst == source_vertex) { continue; }

            if (adj[src][dst]) {

                if (!cost[dst]) {
                    
                    cost[dst] = (adj[src][dst] + cost[src]);
                }
                else {

                    if ((adj[src][dst] + cost[src]) < cost[dst]) {
                        
                        cost[dst] = (adj[src][dst] + cost[src]);
                    }
                }
            } // end of outer if block

        } // end of inner for loop
    } // end of outer for loop

    return source_vertex;
} // end of find_shortest_paths(Graph*)

void display_costs(Graph *graph) {

    int i = 0;
    for (; i < graph->V; i++) {
        printf("%d ", *(graph->cost + i));
    }
    printf("\n");
} // end of display_costs(Graph*)


int main() {

    Graph *graph = new_graph();
    import_graph(graph);

    if ((graph->edges)->head == NULL) {

        printf("Graph does not have any edges\n");
        exit(0);
    }

    display_edges(graph);

    int source_vertex = find_shortest_paths(graph);

    printf("\nMinimum costs of vertices from vertex %d: ", source_vertex);
    display_costs(graph);

    return 0;
} // end of main()