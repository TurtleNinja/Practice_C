#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int value;
    struct node *next;
} node;

// GLOBAL VARIABLE
//node *head;

//FUNCTION PROTOTYPE
node* init(void);
void add(node* list, int val);
void print_list(node* l);
void sort(node* list);
int size(node *list);
void merge_sort(node* list, node* low, node* high);

//MAIN
int main(void)
{
    node* list = init();
    add(list, 14);
    add(list, 6);
    add(list, 3);
    add(list, 9);
    //print_list(list);
    sort(list);
}

void add(node *list, int val)
{
    //point to head
    node *iterator = list;

    //iterate through the list
    while(iterator->next != NULL)
        iterator = iterator->next;

    iterator->value = val;
    iterator->next = malloc(sizeof(node));
    (iterator->next)->next = NULL;
}

//initialize a list
node* init(void)
{
    node *head = malloc(sizeof(node));
    head->next = NULL;

    return head;
}

void print_list(node* l)
{
    node *iterator = l;
    while (iterator->next != NULL)
    {
        printf("%d\n", iterator->value);
        iterator = iterator->next;
    }
    printf("%d\n", size(l));
}

int size(node *list)
{
    int count = 0;
    node *iterator = list;
    while (iterator->next != NULL)
    {
        count++;
        iterator = iterator->next;
    }
    return count;
}

// merge sort the list
void sort(node* list)
{
    //copy list to an auxiliary list
    node *aux_list = init();
    node *iterator = list;
    while (iterator->next != NULL)
    {
        add(aux_list, iterator->value);
        iterator = iterator->next;
    }

    //trace the last node in aux_list
    iterator = aux_list;
    while (iterator->next != NULL)
        iterator = iterator->next;

    merge_sort(aux_list, aux_list, iterator);

    print_list(aux_list);
}

void merge_sort(node* list, node* low, node* high)
{
    node *i = low, *j = high;
}