/*
	Use this header for both Lab 1.2 and 1.3.
	You are not supposed to modify this file. (You can modify for debugging purposes
	but make sure to revert it back to its original form for the final submission.)
*/

//For Lab 1.2
typedef struct {
	int **data;
	int num_rows;
	int num_cols;
} matrix;

//Matrix operations
matrix *create_matrix(int num_rows, int num_cols);
void add_row(matrix *mat, int *row);
void add_col(matrix *mat, int *col);
void increment(matrix *mat, int num);
void scalar_multiply(matrix *mat, int num);
void scalar_divide(matrix *mat, int num);
void scalar_power(matrix *mat, int num);
void delete_matrix(matrix *mat);
void print_matrix(matrix *mat); // implemented for you

//Additional definitions for Lab1.3

typedef struct NODE {
	struct NODE *prev;
	struct NODE *next;
    matrix *mat;
} node;

typedef struct {
	node *head;
} chain;

// chain function prototypes
void insert_node_before(chain *chn, int index, matrix *mat);
void insert_node_after(chain *chn, int index, matrix *mat);
void delete_node(chain *chn, int index);
void delete_list(chain *chn);

