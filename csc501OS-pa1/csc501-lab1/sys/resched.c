#include <conf.h>
#include <kernel.h>
#include <q.h>
#include <stdio.h>
#include <proc.h>
#include "math.h"
#include "sched.h"
 
unsigned long currSP;	/* REAL sp of current process */
extern int ctxsw(int, int, int, int);

/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */

int epoch;
int flag;


int resched() 
{
	register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */
	int exp_prio;				/* random value for exponential scheduler */
	int process;				/* pid of next running of process */

	/* no switch needed if current process priority higher than next*/
	/* next process chosen based on scheduler policy		*/

	optr = &proctab[currpid]; //pointer to currently running process

	if (scheduling_class == LINUXSCHED) {
		//Linux Scheduler

		int max_goodness;

		// has the first epoch been created?
		if (flag == 0) {
			resetEpochs();
			flag = 1;
		}

		if (preempt == 0) {
			// check for nullproc - is epoch over?
			if ((currpid == NULLPROC) && (q[rdyhead].qnext < NPROC)) {
				// queue is empty
				resetEpochs();
				return OK;
			}

			//context switch!
			optr->counter = (optr->counter) - QUANTUM;		// update process time quantim (counter)
			epoch = epoch - QUANTUM;						// lower total epoch time left


			// if process's counter = 0; it can no longer run. Change goodness so it won't be chosen
			if (optr -> counter <= 0 ) {
				optr -> goodness = 0;
			}

			// place running process back on queue
			if (optr->pstate == PRCURR) {
					optr->pstate = PRREADY;
					insert(currpid,rdyhead,optr->goodness);
			}

			// next process to run - queue is in order
			currpid = getlast(rdytail);
		}
		else {
			// timer interupt is not over - stopped early

			// check if epoch time has run out
			if(epoch <= 0){
				resetEpochs();
				return OK;

			}
			else{
				/* force context switch */
				// place running process back on queue
				if (optr->pstate == PRCURR) {
					optr->pstate = PRREADY;
					insert(currpid,rdyhead,optr->goodness);
				}

				// next process to run - queue is in order
				currpid = getlast(rdytail);
			}
		}
	}
	else if (scheduling_class == EXPDISTSCHED) {
        //Exponential Distribution Scheduler

		//check for Round Robin - are there multiples of the process? Same priorities
		if (optr->pprio == q[q[currpid].qnext].qkey) {
			process = q[currpid].qnext;						//next process in queue
		}
		else if (optr->pprio == q[q[currpid].qprev].qkey) {
			process = q[q[currpid].qprev].qkey;				//previous process in queue
			while (q[process].qkey == q[q[process].qprev].qkey) {
				process = q[q[process].qprev].qkey;
			}
		}

		else {
			// no multiples, get a new process
			exp_prio = (int) expdev(LAMBDA);		// random exponental priority value
        	process = getExpProcess(exp_prio);		// process chosen to run by random priority value

        	// reset timer and do not switch if:
            // process is currently running,
            // the currently running process pprio < chosen process pprio
            // AND currently running process pprio > random exponential priority (it was not in the queue to return earlier)

            if( (optr->pstate == PRCURR) && ( (optr->pprio < q[process].qkey) && (optr->pprio > exp_prio) ) ) {

                    #ifdef  RTCLOCK
                            preempt = QUANTUM;              /* reset preemption counter     */
                    #endif
                    return OK;

            }
        }

        /* force context switch */

        // put currently running process back on queue
        if (optr->pstate == PRCURR) {
                optr->pstate = PRREADY;
                insert(currpid,rdyhead,optr->pprio);
        }

        // get currpid for context switch
        currpid = dequeue(process);

    }		
	else {
		//DEFAULT XINU

		/* no switch needed if current process priority higher than next*/
		if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
			(lastkey(rdytail) < optr->pprio)) {
			return(OK);
		}			
		/* force context switch */

		// put running process back on queue for context switch
		if (optr->pstate == PRCURR) {
			optr->pstate = PRREADY;
			insert(currpid,rdyhead,optr->pprio);
		}

		// get currpid for context switch
		currpid = getlast(rdytail);
	}


	/* force context switch for all schedulers */
	

	/* remove process about to be run from ready list */

    nptr = &proctab[currpid];
    nptr->pstate = PRCURR;       	    /* mark it currently running    */
	#ifdef  RTCLOCK
		preempt = QUANTUM;              /* reset preemption counter     */
	#endif

    ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);

    /* The OLD process returns here when resumed. */
    return OK;

}