//queuetime.c
//main queuetime function

#include <stdio.h> 
#include <stdlib.h> 
#include <stddef.h> 
#include <string.h> 
#include <math.h> 
#include "entry.h" 
 
int main (int argv, char **argc) 
{ 
	FILE *fp = fopen(argc[1], "r"); //the file path should be given as the first argument 
	float start_time; 
	float service_time;	 
	entry_queue q = new_entry_queue(); 
	float max_time = 0.0; //maximum time in line 
	int max_in_line = 0; 
	int in_line = 0; 
 
	while (fscanf(fp, "%f %f", &start_time, &service_time) != EOF)  
	{ 
		float wait_time = 0; //default value for the time the newest item will have to wait 
 
		//only check for items to be popped when there are items in the queue 
		if (entry_queue_isempty(q)) 
		{ 
			//pop items that should be taken off the queue - 
			//when the total start + service + wait time of the front entry is less than the start time of the new entry 
			if (get_total_time(front_entry(q)) < start_time) 
			{ 
				entry_queue_pop(q); 
				in_line -= 1; 
			} 
 
		} 

		if (entry_queue_isempty(q)) //again, don't want to traverse queue if it is empty 
		{ 
		/* The temp entry_cons will be used to traverse the queue to find out how long the current item will wait in the queue. 
		The item will be in the queue for the total service time ahead, plus the difference between their arrival and the first person's arrival*/		 
			entry_cons temp = q->front; 
			wait_time = (temp->contents)->start + (temp->contents)->wait - start_time; //and we'll also add the service time in the loop below... 
			while (temp != NULL)	//if the end of the queue has not been reached	 
			{ 
				wait_time += (temp->contents)->service;  
				temp = temp->next; 
			} 
			if (wait_time > max_time) 
			{ 
				max_time = wait_time; 
			} 
		} 
		 
		//add the new entry 
		entry ent = new_entry(start_time,service_time,wait_time); 
		entry_queue_insert(q, ent); 
 
		in_line += 1; //now one more is in line... 
		 
		//possibly change maximum number in line 
		if (in_line > max_in_line) 
			max_in_line = in_line; 
	} 
 
	//print max_time and max_in_line to the text file supplied by the user as the second argument 
	FILE *fout; 
	fout = fopen(argc[2], "w+"); 
	fprintf (fout, "Maximum items in queue: %d\nMaximum wait in queue: %.2f\n", max_in_line, max_time); 
	fclose(fout);
 

} 


