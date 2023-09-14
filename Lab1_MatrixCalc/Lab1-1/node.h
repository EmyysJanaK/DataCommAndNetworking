/*
	You can modify this file for your testing purpose 
	but note that we will use our own copies of this file for testing during grading 
	so changes in this file will be overwritten
*/

#define MAX_WORD_LENGTH 20

typedef struct NODE {
	struct NODE *prev;
	struct NODE *next;
    char *word;
} node;

typedef struct {
	node *head;
} list;

// function prototypes
void insert_node_before(list *lst, int index, char *word);
void insert_node_after(list *lst, int index, char *word);
void delete_node(list *lst, int index);
void delete_list(list *lst);
char *list_to_sentence(list *lst);
