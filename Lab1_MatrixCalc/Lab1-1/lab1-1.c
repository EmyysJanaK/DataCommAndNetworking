#include <stdio.h>
#include <stdlib.h>
#include <string.h> //stdlib includes malloc() and free()

// user-defined header files
#include "node.c"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst);
void run(list * lst);

void operation(list* lst,int index, int op, char* word){
    if (op == INSERT_BEFORE){
        insert_node_before(lst, index, word);
    } else if (op == INSERT_AFTER){
        insert_node_after(lst, index, word);
    }
}

int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
    run(lst);
    print_list(lst);
    free(lst);
    return 0;
}


// parse the input
void run(list *lst)
{
    char line[1000];

    //getting the intial values of the linked list, comma seperated strings
    fgets(line, 1000, stdin);
    char*token;
    token = strtok(line, ",");

    int index = -1;  // Start index at 0
    while (token != NULL) {
        if (token[strlen(token)-1] == '\n'){
            token[strlen(token)-1] = '\0';
        }
        //printf("%s", token);
        insert_node_after(lst, index, token);
        token = strtok(NULL, ",");
        index++;
    }


    int i, op, loc;


    //
    while (1){
        i = 0, op=0, loc=0;
        char input_word[1000];
        fgets(input_word, 1000, stdin);
        token = strtok(input_word, " ");
        if (strcmp(token, "0\n") == 0){
            break;
        }
        while (token != NULL) {
            if (token[strlen(token)-1] == '\n'){
                token[strlen(token)-1] = '\0';
            }
            if (i==0){
                op = atoi(token);
                if (op == DELETE_LIST){
                    delete_list(lst);
                    index = -1;
                    break;
                }
                i++;
            } else if (i==1){
                loc = atoi(token);
                if (loc < 0){
                    loc = index+1+loc;
                }
                if (op == DELETE_NODE){
                    delete_node(lst, loc);
                    index--;
                    break;
                }
                i++;
            } else if(i==2){
                strcpy(input_word, token);
                operation(lst, loc, op, input_word);
                index++;
                break;
            }
            //printf("%s", token);
            token = strtok(NULL, " ");
        }


    }


}



//Print the list contents
void print_list(list * lst)
{
    node *temp = lst -> head;
    if (lst -> head != NULL){
        do {
            printf("%s ", temp->word);
            temp = temp -> next;
        } while (temp != lst->head);

    }else{
        printf("List is empty");
    }
}