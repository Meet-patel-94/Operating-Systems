#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"

/** @file pri_queue.c */

static Node_ptr_t head = NULL;

/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Meet Patel 500509440
 */

void PQ_insert(int priority, char * data) {
 //FIX THIS
Node_ptr_t node1 = (struct node1 *)malloc(sizeof(struct node));
 node1->priority = priority;
 node1->data = data;
  int n=1;
 if (head == NULL){
     head = node1;
     head->next = NULL;
}

else if (node1->priority >= head->priority){
    Node_ptr_t  node = head;
    head = node1;
    head->next = node;
}

while (!(head == NULL) && !(node1->priority >= head->priority) && (n==1)) {
      Node_ptr_t nods;
      for(nods = head; nods != NULL; nods = nods->next){
	if(node1->priority < nods->priority && (node1->priority > nods->next->priority || nods->next ==NULL)){
             node1->next = nods->next;
             nods->next = node1;
             n=2;

         }
     }
 }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */

Node_ptr_t PQ_delete() {
  //FIX THIS
    Node_ptr_t  nods = head->next;
    head = nods;
    return head;   
    return NULL;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */

Node_ptr_t PQ_get_head() {
    return head;
}
/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t nods;
    for(nods = head; nods != NULL; nods = nods-> next, size++);
    return size;
}


