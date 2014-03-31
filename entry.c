//entry.c 
//entry, entry_cons, and entry_queue functions

#include <assert.h> 
#include <stdlib.h> 
#include "entry.h"
#include <stdbool.h> 

//construct new entry
entry new_entry(float start, float service, float wait) { 
	entry result = (entry) malloc(sizeof(entry_store)); 
	assert(result != NULL); 
	result->start = start; 
	result->service = service; 
	result->wait = wait;
	return result; 
} 

//free entry - used to remove entries from queue
void free_entry(entry p) { 
	free((void *) p); 
} 

//linked list used to produce entry queue
entry_cons new_entry_cons(entry p, entry_cons next) 
{
	entry_cons result = (entry_cons) malloc(sizeof(struct entry_cons_store)); 
	assert(result != NULL); //because otherwise couldn't do result->contents
	result->contents = p; 
	result->next = next; 
	return result; 
} 


void free_entry_cons(entry_cons pc) { 
	free((void *) pc); 
} 

//creates a new entry queue with a null front and rear linked list
entry_queue new_entry_queue() { 
	entry_queue result = (entry_queue) malloc(sizeof(struct entry_queue_store)); 
	assert(result != NULL); 
	result->front = NULL; 
	result->rear = NULL; 
	return result; 
} 


//insert into entry_queue
void entry_queue_insert(entry_queue q, entry p) { 
	entry_cons new_cons = new_entry_cons(p,NULL); 
	if (q->front == NULL) { 
		q->front = new_cons; 
		q->rear = new_cons; 
	} 
	else { 
		q->rear->next = new_cons; 
		q->rear = new_cons; 
	} 
} 

//check if empty
bool entry_queue_isempty(entry_queue q) { 
	return q->front != NULL; 
} 

//pop front element out of queue
entry entry_queue_pop(entry_queue q) { 
	assert(q->front != NULL); 
	entry result = q->front->contents; //got the first element - now we can remove it... 
	entry_cons old_front = q->front; 
	q->front = q->front->next; 
	free_entry_cons(old_front); 
	return result; 
}

//get the first entry without popping it
entry front_entry (entry_queue q) { 
	assert(q->front != NULL); 
	entry result = q->front->contents; 
	return result; 
}

//returns total start+wait+service time (useful for figuring out when to pop an item)
float get_total_time(entry e)
{
	return (e->start) + (e->service) + (e-> wait);
}
