#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*  your list function definitions */

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void printdelist(struct node *list) {
	printf("Printing list vvv\n");
	while (list != NULL) {
		printf("%d\n", list->val);
		list = list -> next;
	}
	printf("------------\n");
}

void insert_sort(const int add_val, struct node **head) {

	struct node* leader = *head;
	struct node* follower = *head;
	struct node* add_node = malloc(sizeof(struct node));
	add_node -> val = add_val;
	add_node -> next = NULL;
	
	if (leader == NULL) {
		add_node -> next = *head;
		*head = add_node;
	}
	
	else {
		if (leader->next == NULL) {
			if (add_val <= (leader -> val)) {
				add_node -> next = *head;
				*head = add_node;
			}
			else {
				leader -> next = add_node;
			}
		}
		else {
			if (add_val < (leader -> val)) {
				add_node -> next = *head;
				*head = add_node;
			}
			
			else {
				leader = leader -> next;
				while (leader != NULL) {
					if (add_val <= (leader -> val)) {
						follower -> next = add_node;
						add_node -> next = leader;
						break;
					}
					follower = follower -> next;
					leader = leader -> next;
				}
				if (leader == NULL) {
				follower -> next = add_node;
				}
			}
		}
	}
}


