#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *next;
};
typedef struct node Node;

struct mylist                    //structure for a list
{
    Node *head;
    Node *tail;
};
typedef struct mylist Tlist;     //the new data type called Tlist

Tlist L;

void insertToHead(int x, Tlist *l);
void insertToTail(int x, Tlist *l);
void insertAfter(Node *n, int x);
void iterate(Tlist l);
void add(int x, Tlist *l);
Node *FindInfo(int info, Tlist L);
int isEmpty(Tlist L);
void deleteNextNode(Node *r);

int main()
{
    int a[] = {4, 2, 7, 10, 1};
    insertToHead(a[0],&L);
    printf("Head: %d\n", L.head->info);
    L.tail = L.head;
    for(int i=1;i<5;i++)
    {
        add(a[i],&L);
    }
    iterate(L);

    Node *n1;
    n1 = FindInfo(4,L);
    printf("\n%d %p\n",n1->info, n1->next);
    deleteNextNode(n1);
    iterate(L);
    return 0;
}

/*We use the function below when we want to insert a new int value at the head of the list.
  This function takes as arguments the integer value and the pointer to your list. */
void insertToHead(int x, Tlist *l)
{
	/*1. Create a new node */
    Node *tmp;
	/*2. Allocate memory for the new node  -  steps 1 and 2 can be done in one single step */
    tmp = (Node*) malloc(sizeof(Node));
	/*3. Set the info field from the new node with the integer value given as parameter */
    tmp->info = x;
	/*4. Set the pointer to the next node as head */
    tmp->next = l->head;
	/*5. Move the head of the list to point to the new added node */
    l->head = tmp;
}

/*We use the function below when we want to insert a new int value at the end of the list.
  This function takes as arguments the integer value and the pointer to your list. */
void insertToTail(int x, Tlist *l)
{
    /*1. Create and allocate memory of the new node */
    Node *tmp;
    tmp = (Node*) malloc(sizeof(Node));
	/*2. Set the info field from the new node with the integer value given as parameter */
	tmp->info = x;
	/*3. This new node is going to be the last node, so set the next of it as NULL */
	tmp->next = NULL;
	/*4. If the tail is not empty, set the next of the current tail as the new added note and then make the tail to point to the new added node */
    if(l->tail)
    {
        l->tail->next = tmp;
        l->tail = tmp;
    }

	/*5. Else directly make the tail to point to the new added node and also the head to point to the new added node */
	else
        l->tail = tmp;
}

/*We use the function below when we want to insert a new int value after a node.
  This function takes as arguments the integer value and the pointer after you want to insert the value. */
void insertAfter(Node *n, int x)
{
	/*1. Check if the given prev_node "n" is NULL */
	if(n == NULL)
        printf("Empty node");
	/*2. Create and allocate memory of the new node */
	Node *tmp = (Node*) malloc(sizeof(Node));
        /*3. Set the info field from the new node with the integer value given as parameter */
        tmp->info = x;
        /*4. Set the pointer to the next node as next of previous node "n" */
        tmp->next = n->next;
        /*5. Move the next of the previous node "n" to point to the new added node */
        n->next = tmp;
}

/*We use the function below when we want to iterate trough the list.
  This function takes as argument a list (pay attention that the list is contains a pointer to the head and a pointer to the tail - see the mylist structure). */
void iterate(Tlist l)
{
	/*1. Initialize a node pointer (usually it is called "it" from iterator) to the head of the list - you will start iterating from the head of the list */
	Node *it = l.head;
    printf("Iteration");
	/*2. Check if "it" is NULL - then the list is empty */
	if(it==NULL)
        printf("The list is empty!");
	/*3. Else, using a for loop until it is NULL, go "from next to next" and print the info field */
	else
    {
        for(; it!=NULL; it=it->next)
            printf("\n%d",it->info);
    }
}

/*We use the function below when we want to add a new int value in the list and maintain a ascending order of the integer values inside the nodes.
  This function takes as arguments the integer value and the pointer to your list. */
void add(int x, Tlist *l)
{
	/*1. Check if the integer value given as parameter is less than the integer value from the head of the list or if the list is empty. Is so, call the function insertToHead() */
	if(x < l->head->info || l->head==NULL)
        insertToHead(x,l);
    /*2. Check if the integer value given as parameter is greater than the integer value from the tail of the list. Is so, call the function insertToTail() */
    if(x > l->tail->info)
        insertToTail(x,l);
    /*3. Create an iterator, iterate through the list and if the integer value given as parameter is greater than the info field of one node "n" and
         less than the info field of the next of that node "n", call the function insertAfter(it,n) */
    Node *it = l->head;
    for(; it!=NULL; it=it->next)
        if(x > it->info && x < it->next->info)
            insertAfter(it,x);
}

/*We use the function below when we want to find a specific integer value in the list.
  This function takes as arguments the integer value and your list. */
Node *FindInfo(int info, Tlist l)
{
	/*1. Initialize a pointer to the head of the list - you will start searching from the head of the list */
	Node *search = l.head;
	/*2. If the new node is empty, it means the list is empty, so you can print a message */
	if(search == NULL)
        printf("List is empty");
	/*3. Else, while the new tmp node is not NULL (you have not reached the end of the list), check if the info
         field of the new node is equal to the integer value given as parameter and if it is, then return the value.
         If not, go to the next node */
    else
    {
        for(; search != NULL; search = search->next)
            if(search->info == info)
                return search;
        return NULL;
    }
	/*4. Return NULL in case you have not found the information */
}

int isEmpty(Tlist l)
{
	/*Return true if the head of the list is NULL and false otherwise*/
	return l.head == NULL;
}

/*We use the function below when we want to delete the successor of a node in the list.
  This function takes as argument the node. */
void deleteNextNode(Node *r)
{
	/*1. Check if the given node is NULL and print an error message */
	if(r == NULL)
        printf("Node is NULL");
    /*2. Check if the next of the given node exists and print an error message */
    if(r->next == NULL)
        printf("Next node is NULL");
    /*3. Initialize a pointer to the next of the given node "r" (this pointer will point to the memory area we want di deallocate) */
    Node *del = r->next;
    /*4. Set the next of the "r" node as the next of tmp(which is the next of "r") */
    r->next = del->next;
    /*5. Free the allocated memory. */
    free(del);
}
