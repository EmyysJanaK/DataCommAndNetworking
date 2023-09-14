// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{
    node *temp;
    node *newNode = (node *)malloc(sizeof(node));
    newNode->word = (char *)malloc(strlen(word) + 1);
    strcpy(newNode->word, word);

    if (lst -> head != NULL){
        temp = lst ->head;
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
        lst -> head = newNode;
        newNode -> prev = newNode;
        newNode -> next = newNode;
    }
}

void insert_node_after(list *lst, int index, char *word)
{

    insert_node_before(lst, index+1, word);
}

char *list_to_sentence(list *lst)
{
    // TODO
    node *temp = lst -> head;
    if (lst -> head != NULL){
        do {
            printf("%s ", temp->word);
            temp = temp -> next;
        } while (temp != lst->head);

    }else{
        printf("List is empty");
    }
    printf("\n");

    return NULL; // Change this line accordingly
}

void delete_node(list *lst, int index) {
    node *temp = lst->head;
    int i = 0;

    // Traverse the list to find the node at the given index
    while (temp != NULL && i != index) {
        temp = temp->next;
        i++;
    }

    // Check if the node was found
    if (temp != NULL) {
        // Update the previous node's next pointer
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            // If the node being deleted is the head, update the head
            lst->head = temp->next;
        }

        // Update the next node's previous pointer
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }

        // Free the memory occupied by the node and its word
        free(temp->word);
        free(temp);
    }
}


void delete_list(list *lst)
{
    // TODO
    node *temp = lst -> head;
    int i=0;
    while(temp -> next != NULL){
        delete_node(lst, i);
        i++;
    }
    free(lst);
}
