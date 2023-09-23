// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l) {
	// printf("Hello world");
  node_t * head = l->head;
  node_t *nextnode;
	// node_t *temp = NULL;		
	
	while(head != NULL){
		nextnode = head->next;
		free(head);
		head = nextnode;
	}
	l->head = NULL;
  
		}
  

  // free(head);


void list_print(list_t *l) {
  node_t *head = l->head;
  while (head != NULL) {
    printf("%d, ", head->value);
    head = head->next;
  }
}

// char * listToString(list_t *l) {
//   char* buf = (char *) malloc(sizeof(char) * 1024);
//   char tbuf[20];
// 	node_t* curr = l->head;
//   while (curr != NULL) {
//     sprintf(tbuf, "%d->", curr->value);
//     curr = curr->next;
//     strcat(buf, tbuf);
//   }
//   strcat(buf, "NULL");
//   // return buf;
	
// }

int list_length(list_t *l) { 
  int count = 0;
  node_t *head = l->head;
  while(head != NULL) {
    count += 1;
    head = head -> next;
  }
	return count;
  // printf("%d", count);
 }

void list_add_to_back(list_t *l, elem value) {
  node_t * cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node->value = value;
  node_t *head = l->head;
	if (head == NULL) {
		head = cur_node;
	} 
	else{
		while(head->next != NULL){
    head = head->next;
    }
    head->next = cur_node;  
    cur_node->next = NULL;
		}
}

void list_add_to_front(list_t *l, elem value) {
	node_t* cur_node = (node_t *) malloc(sizeof(node_t));
	cur_node->value = value;
	cur_node->next = l->head;
	l->head = cur_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
	node_t* cur_node = (node_t *) malloc(sizeof(node_t));
	cur_node->value = value;
  node_t *head = l->head, *temp1;
	node_t *temp = NULL;
  int count = 2;
	if (index == 1) {
		cur_node->next = l->head;
		l->head = cur_node;
	}
	else{
		while (count != (index ) ) {
    head = head->next;
    count += 1;
  }
	cur_node->next = head->next;
	head->next = cur_node;
	}
}

elem list_remove_from_back(list_t *l) { 
	node_t *curr = l->head;
	node_t *prev;
	while(curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	
	free(curr);
	curr = prev;
	curr->next = NULL;

}


elem list_remove_from_front(list_t *l) { 
	node_t *curr = l->head;
	node_t *temp = curr->next;
	if(curr);
		l->head = curr->next;
		free(curr);
		// curr = temp;
 }

elem list_remove_at_index(list_t *l, int index) { 
  node_t *head = l->head, *prev;
	node_t *temp = head->next;
  int count = 1;
  while (head != NULL && count != index ) {
		prev = head;
    head = head->next;
    count += 1;
  }
	prev->next = head->next;
	free(head);
	}

bool list_is_in(list_t *l, elem value) { 
	node_t *curr = l->head;
	while (curr != NULL) {
		if (curr->value == value) {
			return true;
		}
		else{
			curr = curr->next;
		}
	}
	return false; 
	}

elem list_get_elem_at(list_t *l, int index) {
	node_t *temp;
	node_t *head = l->head;
	int count = 1;
	while(count != (index)){
		head = head->next;
		count += 1;
	}
	return head->value;
}

int list_get_index_of(list_t *l, elem value) { 
	node_t *head = l->head;
	int count = 1;
	while(head->value != value) {
		head = head->next;
		count += 1;
	}
	return (count);
}

