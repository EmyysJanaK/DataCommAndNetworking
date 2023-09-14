// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>// stdlib includes malloc() and free()


//updating implementing functions
// user-defined header files

#include "chain.c"

#define ADD_ROW 2
#define ADD_COLUMN 3
#define INCREMENT 4
#define MULTIPLY 5
#define DIVIDE 6
#define POWER 7



// function prototypes
void print_chain(chain * chn);
void run(chain * chn);

int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
    run(chn);
    print_chain(chn);
    free(chn);
    return 0;
}

// parse the input
void run(chain *chn)
{
    //getting input
    // matrix *mat = (matrix *)malloc(sizeof(matrix));
    // mat -> data = (int **)malloc(sizeof(int*));
    int chn_size = -1;
    int init_row_num;
    scanf("%d", &init_row_num);
    getchar();
    int **data = (int **)malloc(init_row_num*sizeof(int*));
    int *row;
    int index;
    int temp_int = 0;
    int col_number = 0;
    for (int i = 0; i < init_row_num; i++){
        index = 0;
        char *token;
        char row_num[100];
        fgets(row_num, 100, stdin);
        char temp_row_num[100];
        strcpy(temp_row_num, row_num);

        if (temp_int == 0){
            char *temp_token = strtok(row_num, " ");
            while (temp_token != NULL) {
                col_number++;
                temp_token = strtok(NULL, " ");
            }
            temp_int++;
        }
        row = (int *)malloc(col_number * sizeof(int));
        token = strtok(temp_row_num, " ");
        while (token != NULL) {
            if (token[strlen(token)-1] == '\n'){
                token[strlen(token)-1] = '\0';
            }
            row[index] = atoi(token);
            index++;
            token = strtok(NULL, " ");
        }
        data[i] = row;
    }

    // mat ->num_rows = init_row_num;
    // mat ->num_cols = index;
    matrix* mat = create_matrix(init_row_num, col_number);
    mat ->data = data;
    insert_node_after(chn, chn_size, mat);
    chn_size++;



    //implementing function inputs'
    char * token;
    while (1){
        int i = 0, op=0, loc=0;
        char input_word[1000];
        fgets(input_word, 1000, stdin);
        token = strtok(input_word, " ");
        if (strcmp(token, "0\n") == 0){
            break;
        }



        matrix *newMatrix = create_matrix(mat->num_rows, mat->num_cols);
        int **newdata = (int**)malloc(mat->num_rows* sizeof(int *));
        for (int i=0; i < mat->num_rows; i++){
            int *row = (int *)malloc((mat->num_cols) * sizeof(int));
            for (int j=0; j < mat->num_cols; j++){
                row[j] = mat->data[i][j];
            }
            newdata[i] = row;
        }
        newMatrix -> data = newdata;

        while (token != NULL) {
            if (token[strlen(token)-1] == '\n'){
                token[strlen(token)-1] = '\0';
            }

            op = atoi(token);

            if (op == ADD_ROW || op== ADD_COLUMN){

                int *line;
                if (op ==  ADD_ROW){
                    line = (int *)malloc(mat->num_cols *sizeof(int));
                } else{
                    line = (int *)malloc(mat->num_rows*sizeof(int));
                }
                int j = 0;
                int ele;
                token = strtok(NULL, " ");
                while (token != NULL){
                    if (token[strlen(token)-1] == '\n'){
                        token[strlen(token)-1] = '\0';
                    }
                    ele = atoi(token);
                    line[j] = ele;
                    j++;
                    token = strtok(NULL, " ");
                }
                //lasst line amedne'
                if (op ==  ADD_ROW){
                    add_row(newMatrix, line);

                } else{
                    add_col(newMatrix, line);

                }


                insert_node_after(chn, chn_size, newMatrix);

                mat = newMatrix;
                chn_size++;
                break;

            }
            else if (op == INCREMENT || op == DIVIDE || op == MULTIPLY || op == POWER){
                token = strtok(NULL, " ");
                int num = atoi(token);
                if (op == INCREMENT){
                    increment(newMatrix, num);

                } else if (op == DIVIDE){
                    scalar_divide(newMatrix, num);

                } else if (op == MULTIPLY){
                    scalar_multiply(newMatrix, num);

                } else if (op == POWER){
                    scalar_power(newMatrix, num);

                }
                insert_node_after(chn, chn_size, newMatrix);
                chn_size++;
                mat = newMatrix;
                break;

            }


        }

    }

}
//Print the chain
void print_chain(chain * chn)
{
    node *temp = chn -> head;
    if (chn -> head != NULL){
        do {

            print_matrix(temp->mat);
            printf("\n");
            temp = temp -> next;
        } while (temp != chn->head);

    }else{
        printf("List is empty");
    }

}