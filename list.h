#ifndef __LIST_H__
#define __LIST_H__
#include <stdio.h>
#include <stdlib.h>

/* your list data structure declarations */
struct node {
	int val;
	struct node *next;
};

/* your function declarations associated with the list */
void list_clear(struct node *list);
void printdelist(struct node *list);
void insert_sort(const int add_val, struct node **list);
void inserttolist(const int add_val, struct node **head);

#endif // __LIST_H__
