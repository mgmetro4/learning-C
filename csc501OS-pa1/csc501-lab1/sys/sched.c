#include <kernel.h>
#include <proc.h>
#include <q.h>
#include "sched.h"
#include "math.h"

scheduling_class = 0;	/* Initializing the scheduler type with 0 (DEFAULT XINU) */
int epoch;				/* sum of time quantum counters in a epoch */
int flag;				/* has the first epoch been created? */

/*******************************************************************
set the scheduler class to the value passed as parameter
********************************************************************/
void setschedclass(int sched_class){
	scheduling_class = sched_class;
	if (sched_class == 2) {
		flag = 0; // epoch has not been created
	}
}

/*******************************************************************
return the scheduling class
********************************************************************/
int getschedclass(){
	return(scheduling_class);
}

/*******************************************************************
return process for exponential distribution scheduler
********************************************************************/
int getExpProcess(int exp_prio){

	int head = q[rdyhead].qnext;
	// start at head, keep going until not a process 
	// or exponential priority < processs
	while((q[head].qkey < exp_prio) && (head < NPROC)) {
		head = q[head].qnext;
	}

	if(head >= NPROC){
		return NULLPROC;
	}
	else { 
		return head;
	}
}
	
/*******************************************************************
update priorities for Linux Scheduler when new epoch is started
(reflect system changes to pprio)
********************************************************************/
void updatePriorities() {
	int i;
	for (i=0; i < NPROC; i++) {
		proctab[i].new_pprio = proctab[i].pprio;
	}	
}

/*******************************************************************
update time quantum counter for Linux Scheduler
********************************************************************/
void updateQuantumCounter() {
	int i;
	int counter;

	for (i=0; i < NPROC; i++) {
		counter = proctab[i].counter;

		if (i == NULLPROC) {
			// null process counter does not increase if not used
			proctab[i].counter = proctab[i].new_pprio;
		}	
		else if (proctab[i].counter > 0 ) {
			// if not all of counter was used; increase counter to give more time next epoch
			proctab[i].counter = ((int) (counter / 2)) + proctab[i].new_pprio;
		}
		else {
			// process used their entire counter. New counter = their pprio
			proctab[i].counter = proctab[i].new_pprio;
		}
	}
}

/*******************************************************************
update goodness (dynamic priority level) for Linux Scheduler
********************************************************************/
void updateGoodness() {

	int counter;
	int new_pprio;
	int i;

	for (i=0; i < NPROC; i++) {

		new_pprio = proctab[i].new_pprio;
		counter = proctab[i].counter;

		if (i == NULLPROC) {
			// null process should always be 0 priority level - run last
			proctab[i].goodness = 0;
		}	
		else if (proctab[i].counter > 0 ) {
			// did not finish last time, so raise priority level
			proctab[i].goodness = counter + new_pprio;
		}
		else {
			// priority level stays the same
			proctab[i].goodness = new_pprio;
		}
	}
	// to order by goodness after changes, dequeue and re-insert every process in queue
	resetQueue();
}

/*******************************************************************
find maximum value for goodness within queue for Linux Scheduler
used to find a process to run next
********************************************************************/
int getMaxGoodness() {
	int tail = q[rdytail].qprev;
	int max_goodness = 0;
	int current_goodness;
	int current_counter;

	while (tail != rdyhead && tail < NPROC) {
		current_goodness = proctab[tail].goodness;
		current_counter = proctab[tail].counter;

		// don't count if counter is 0 because it can't run
		if ((current_goodness > max_goodness) && (current_counter > 0)) {
			max_goodness = current_goodness;
		}
	}
	return max_goodness;
}

/*******************************************************************
start a new epoch for Linux Scheduler
********************************************************************/
void resetEpochs() {
	updatePriorities();
	updateQuantumCounter();
	updateGoodness();

	// to order by goodness after changes, dequeue and re-insert every process in queue
	resetQueue();
	
	//re-calculate time quantum sum - epoch

	int i;
	epoch = 0;
	for(i=0; i < NPROC; i++) {
		epoch = epoch + proctab[i].counter;
	}

}

/*******************************************************************
Re-order queue by goodness level for Linux Scheduler
********************************************************************/
void resetQueue() {
	int process = q[rdyhead].qnext;

	for(process; process <= q[rdytail].qprev; process=q[process].qnext){
		if (process < NPROC) {
			if (process != NULLPROC) { 
				dequeue(process);
				insert(process,rdyhead,proctab[process].goodness);
			}
		}
	}


}
