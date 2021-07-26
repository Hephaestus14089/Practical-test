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

/* ****************************    Graph ends here    ************************* */

int min_of(int x, int y) { return (x < y) ? x : y; }

void display_square_matrix(int **matrix, int n) {

    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
} // end of display_square_matrix(int**, int)

void compute_shortest_paths(Graph *graph) {

    int V = graph->V;
    int **matrix = graph->adj;
    
    int **new_matrix;

    int k, i, j;

    for (k = 0; k < V; k++) {

        printf("\n");
        display_square_matrix(matrix, V);
        printf("\n");
        
        new_matrix = (int**)malloc(sizeof(int*) * V);

        for (i = 0; i < V; i++) { // initialising new_matrix

            *(new_matrix + i) = (int*)malloc(sizeof(int) * V);

            for (j = 0; j < V; j++) {
                new_matrix[i][j] = 0;
                // *(*(new_matrix + i) + j) = 0;
            }
        }


        for (i = 0; i < V; i++) {

            for (j = 0; j < V; j++) {

                if (i == j) { continue; }

                if (matrix[i][k] && matrix[k][j]) {

                    if (matrix[i][j]) {
                        new_matrix[i][j] = min_of(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                    else {
                        new_matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
                else {
                    new_matrix[i][j] = matrix[i][j];
                }
            } // end of for loop with j
        } // end of for loop with i

        free(matrix);
        matrix = new_matrix;

    } // end of for loop with k

    display_square_matrix(matrix, V);
    graph->adj = matrix;

} // end of compute_shortest_paths(Graph*)


int main() {

    Graph *graph = new_graph();

    import_graph(graph);

    printf("\nGraph :-\n");
    display_graph(graph);

    compute_shortest_paths(graph);

    return 0;
} // end of main()