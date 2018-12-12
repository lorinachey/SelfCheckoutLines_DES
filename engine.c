/////////////////////////////////////////////////////////////////////////////////////////////
//
// This code represents the simulation engine. Some of this code is taken and/or adapated from
// a simulation written by Dr. Richard Fujimoto at the Georgia Institute of Technology.
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>    //standard library for input and output
#include <stdlib.h>   //standard library for utility functions
#include "engine.h"

// Data srtucture for an event; this is independent of the application domain
struct Event {
	double timestamp;		// event timestamp
	void *AppData;			// pointer to event parameters
	void (*callback)(void *);	// callback, parameter is event
	struct Event *Next;		// priority queue pointer
} ;

// Future Event List
// Use an event structure as the header for the future event list (priority queue)
struct Event FEL ={-1.0, NULL, NULL, NULL};

// Function to print timestamps of events in event list
void PrintList (struct Event *List);

// Function to remove smallest timestamped event
struct Event *Remove (void);

// Simulation clock variable
double Now = 0.0;

// Return current simulation time
double CurrentTime (void)
{
	return (Now);
}

// Schedule new event in FEL
// queue is implemented as a timestamp ordered linear list
void Schedule (double ts, void *data, void (*cb)(void *))
{
	struct Event *e, *p, *q;

	// create event data structure and fill it in
	if ((e = malloc (sizeof (struct Event))) == NULL) exit(1);
	e->timestamp = ts;
	e->AppData = data;
	e->callback = cb;

	// insert into priority queue
	// p is lead pointer, q is trailer
	for (q=&FEL, p=FEL.Next; p!=NULL; p=p->Next, q=q->Next) {
		if (p->timestamp >= e->timestamp) break;
		}
	// insert after q (before p)
	e->Next = q->Next;
	q->Next = e;
}

// Remove smallest timestamped event from FEL, return pointer to this event
// return NULL if FEL is empty
struct Event *Remove (void)
{
	struct Event *e;

	if (FEL.Next==NULL) return (NULL);
	e = FEL.Next;		// remove first event in list
	FEL.Next = e->Next;
	return (e);
}


void PrintList (struct Event *List)
{
	struct Event *p;

	printf ("Event List: ");
	for (p=List; p!=NULL; p=p->Next) {
		printf ("%f ", p->timestamp);
	}
	printf ("\n");
}


void RunSim (void) 
{
	struct Event *e;

	printf ("Initial event list:\n");
	PrintList (FEL.Next);

	// Main scheduler loop
	while ((e=Remove()) != NULL) {
		Now = e->timestamp;
		e->callback(e->AppData);
		free (e);	// it is up to the event handler to free memory for parameters
	}
}

