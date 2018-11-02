/* sched.h */

#ifndef _SCHED_H_
#define _SCHED_H_

#define EXPDISTSCHED 1
#define LINUXSCHED 2
#define LAMBDA 0.1

extern int scheduling_class;	
extern int epoch; 				 // sum of time quantim
extern int flag;  				//is first time creating an epoch?


void setschedclass(int sched_class);
int getschedclass();

//Exponential Functions
int getExpProcess();				// find a process for exponential scheduler

// Linux Like Functions
int getMaxGoodness();
void updateQuantumCounter();		//time quantum counter 
void updatePriorities();			// let priorities reflect system changes
void updateGoodness();				// update goodness for every process in NPROC
void resetQueue();					// dequeue and insert every process in the queue to reflect new goodness
void resetEpochs();					// start a new epoch

#endif
