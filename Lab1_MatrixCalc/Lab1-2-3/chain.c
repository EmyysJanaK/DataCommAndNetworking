#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:




// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *newmat = (matrix *)malloc(sizeof(matrix));
    int  **data;
    newmat ->num_rows = num_rows;
    newmat -> num_cols = num_cols;
    data = (int**)malloc(num_rows* sizeof(int *));
    for (int i=0; i < num_rows; i++){
        int *row = (int *)malloc((num_cols) * sizeof(int));
        for (int j=0; j < num_cols; j++){
            row[j] = 0;
        }
        data[i] = row;
    }
    newmat -> data = data;
    return newmat;
}

int power(int base, int exp){
    int result=1;
    for (int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

void add_row(matrix *mat, int *row)
{
    // TODO
    mat -> num_rows = (mat->num_rows)+1;
    mat->data = (int**)realloc(mat->data, mat->num_rows*sizeof(int *));
    mat->data[mat->num_rows-1] = row;


}



void add_col(matrix *mat, int *col)
{
    int rows = mat->num_rows;
    int cols = mat->num_cols;

    for(int j=0; j < rows; j++){
        mat->data[j] = (int*)realloc(mat->data[j], (cols+1)*sizeof(int));
        mat->data[j][cols] = col[j];
    }
    mat->num_cols = mat->num_cols +1;

}

void increment(matrix *mat, int num)
{

    for (int i=0; i < mat->num_rows; i++){
        for (int j=0; j < mat->num_cols ;j++){
            mat ->data[i][j] = mat ->data[i][j] + num;
        }
    }


}

void scalar_multiply(matrix *mat, int num)
{
    // TODO
    for (int i=0; i < mat->num_rows; i++){
        for (int j=0; j < mat->num_cols ;j++){
            mat ->data[i][j] = mat ->data[i][j] *num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    // TODO
    for (int i=0; i < mat->num_rows; i++){
        for (int j=0; j < mat->num_cols ;j++){
            mat ->data[i][j] = mat ->data[i][j] /num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    // TODO
    for (int i=0; i < mat->num_rows; i++){
        for (int j=0; j < mat->num_cols ;j++){
            mat ->data[i][j] = power(mat ->data[i][j], num);
        }
    }


}

void delete_matrix(matrix *mat)
{
    // TODO
    for (int i=0; i < mat->num_rows; i++){
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below
//add row_ele must be modified
int* add_line(matrix *mat,  char *token){
    int *temp = (int *)malloc(sizeof(int));
    int j =0;
    int ele;
    token = strtok(NULL, " ");
    while (token != NULL){
        if (token[strlen(token)-1] == '\n'){
            token[strlen(token)-1] = '\0';
        }
        ele = atoi(token);
        temp[j] = ele;
        j++;
    }
    int *line = (int*)malloc(j*sizeof(int));
    for (int i=0; i<j+1; j++){
        line[i] = temp[i];
    }
    free(temp);
    return line;
}


void insert_node_before(chain *chn, int index, matrix *mat)
{
    node *temp;
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mat = (matrix *)malloc(sizeof(matrix));
    newNode->mat->data = (int **)malloc(mat->num_rows*sizeof(int *));
    newNode->mat->num_rows = mat->num_rows;
    newNode -> mat -> num_cols = mat->num_cols;
    for (int i=0; i< mat->num_rows; i++){
        newNode->mat->data[i] = mat->data[i];
    }

    if (chn -> head != NULL){
        temp = chn ->head;
        int i=0;
        while (i != index-1){
            temp = temp ->next;
            i++;
        }

        newNode -> next =  temp-> next;
        newNode -> prev = temp;
        temp ->next = newNode;
        newNode -> next ->prev = newNode;

    } else{
        chn -> head = newNode;
        newNode -> prev = newNode;
        newNode -> next = newNode;
    }





}

void insert_node_after(chain *chn, int index, matrix* mat)
{

    insert_node_before(chn, index+1, mat);
}



void delete_node(chain *chn, int index)
{
    // TODO
    node *temp = chn -> head;
    int i=0;
    while (i != index){
        temp = temp -> next;
        i++;
    }
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    free(temp);

}

void delete_list(chain *chn)
{
    // TODO
    node *temp = chn -> head;
    int i=0;
    while(temp -> next != NULL){
        delete_node(chn, i);
        i++;
    }
    free(chn);
}