#include <stdio.h>
#include <stdlib.h>

struct MatrixChainContainer {

    int n_matrices;
    char *matrices;
    int *dimensions;
};

typedef struct MatrixChainContainer Container;

Container *new_container() {

    Container *container = (Container*)malloc(sizeof(Container));
    
    int i = 0;
    int n;
    char ch;

    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    container->n_matrices = n;
    container->matrices = (char*)malloc(sizeof(char) * n);
    container->dimensions = (int*)malloc(sizeof(int) * (n + 1));

    printf("Enter characters to signify matrices: ");

    while (i < n) {

        scanf("%c", &ch);

        if ((int)ch >= 65 && (int)ch <= 90) {
            *(container->matrices + i++) = ch;
        }
    } // end of while loop

    printf("Enter dimensions of matrices: ");
    
    for (i = 0; i <= n; i++) {
        scanf("%d", (container->dimensions + i));
    }

    return container;
} // end of new_container()

void display_container(Container *container) {

    int i = 0;
    printf("Matrices in container: ");

    for (; i < container->n_matrices; i++) {
        printf("%c(%d x %d) ", *(container->matrices + i),
                              *(container->dimensions + i),
                              *(container->dimensions + i + 1)
        );
    }

    printf("\n");
} // end of display_container(Container*)

int get_least_multiplications_recur(Container *container, int **m_matrix, int **s_matrix, int row, int column) {

    if (row == column) { return 0; }

    if (*(*(m_matrix + row) + column) != 0) { return *(*(m_matrix + row) + column); }

    int partition = row + 1;
    int i = 0;
    int min = get_least_multiplications_recur(container, m_matrix, s_matrix, row, partition);

    for (; partition < column; partition++) {

        get_least_multiplications_recur(container, m_matrix, s_matrix, row, partition);
        get_least_multiplications_recur(container, m_matrix, s_matrix, partition, column);
    }

} // end of get_least_multiplications_recur(Container*, int**, int**, int, int)

int get_least_multiplications(Container *container) {

    int **m = (int**)malloc(sizeof(int*) * container->n_matrices);
    int **s = (int**)malloc(sizeof(int*) * container->n_matrices);
    
    int i = 0;

    for (; i < container->n_matrices; i++) {

        *(m + i) = (int*)malloc(sizeof(int) * container->n_matrices);
        *(s + i) = (int*)malloc(sizeof(int) * container->n_matrices);
    }

    int pass;
    int row = 0, column = 1;
    int j, k;
    
    i = row;
    j = column;

    for (pass = container->n_matrices - 1; pass >= 0; pass--) {

        for (k = 0; k < pass; k++) {



            i++;
            j++;
        } // end of inner for loop

        i = ++row;
        j = ++ column;
    } // end of outer for loop
    
} // end of get_least_multiplications(Container*)


int main() {

    Container *container = new_container();

    display_container(container);

    return 0;
}