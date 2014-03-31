// entry.h 
//entry interface file
//functions described in entry.c
#include <stdbool.h>

//entry datatype - includes start, service, and wait components
typedef struct entry_store { 
	float start; 
	float service;
	float wait;
} entry_store, *entry; 


entry new_entry(float start, float service, float wait); 


void free_entry(entry p); 

//linked list used to construct entry queue
typedef struct entry_cons_store { 
	entry contents; struct entry_cons_store *next; 
} *entry_cons; 

entry_cons new_entry_cons(entry p, entry_cons next); 

void free_entry_cons(entry_cons pc); 

//entry queue
typedef struct entry_queue_store { 
	entry_cons front; entry_cons rear; 
} *entry_queue; 

entry_queue new_entry_queue(); 

void free_entry_queue(entry_queue q); 

void entry_queue_insert(entry_queue q, entry p); 

bool entry_queue_isempty(entry_queue q); 

entry entry_queue_pop(entry_queue q);

entry front_entry(entry_queue q);

float get_total_time(entry e);
