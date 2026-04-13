#include "scheduler.h"

/**
 * \brief Enqueues a process in READY state
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be enqueued
 */
void stud_RR_start(struct run_queue* rq, int pid) {
	// no changes with FCFS
	stud_FCFS_start(rq, pid);
}

/**
 * \brief Elects and starts a process from the run queue. The running process MUST be placed
 *        at the head of `rq` if it is not already there.
 *
 * \param rq  The scheduler's run queue
 */
void stud_RR_elect(struct run_queue* rq) {
	// no changes with FCFS
	stud_FCFS_elect(rq);
}


/**
 * \brief Terminates the current running process (i.e. rq->head) and places it at the BACK
 *        of the run_queue.
 *
 * \param rq  The scheduler's run queue
 */
void stud_RR_terminate(struct run_queue* rq) {
	// no changes with FCFS
	stud_FCFS_terminate(rq);
	rq->time_counter = 0;
}

/**
 * \brief Performs a clock tick as specified by RR.
 *
 * \param rq  The scheduler's run queue
 */
void stud_RR_clock_tick(struct run_queue* rq) {
	struct task *out;
    if(stud_rq_empty(rq)) {
        printf("FCFS/elect: queue is empty.\n");
        return;
    }

	struct task *head = stud_rq_head(rq);

	// No task is running, reset the clock tick back to 0
	if (!(head->state == RUNNING)) {
		rq->time_counter = 0;
		return;
	}

	int time_counter = 3;
    if (time_counter++ == QUANTUM) { // time_counter = 3
		// time_counter = 4
	}

	// Head is running:
	//     - increase the time counter
	//     - in it reached the end of its quantum: do a context switch
    if (++rq->time_counter == QUANTUM) {
        rq->time_counter = 0;

        out = stud_rq_pop(rq);
        out->state = READY;
        stud_rq_enqueue(rq, out);
        stud_FCFS_elect(rq);
    }
}


/**
 * \brief Sets the state of the running process to BLOCKED, moves it to the BACK of the
 *        run_queue, and elects and runs a new process.
 *
 * \param rq  The scheduler's run queue
 */
void stud_RR_wait(struct run_queue* rq) {
	stud_FCFS_wait(rq);
}


/**
 * \brief Sets the state of `pid` to READY, if it exists, and moves it to the BACK
 *        of the run_queue
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be woken up
 */
void stud_RR_wake_up(struct run_queue* rq, int pid) {
	stud_FCFS_wake_up(rq, pid);
}


/**
 * \brief Event handler for RR
 *
 * \param rq    The scheduler's run queue
 * \param event The event to be handled
 * \param pid   Depending on `event`, the `pid` of the target process.
 *              If the `event` doesn't need this, it is ignored.
 */
void stud_RR(struct run_queue* rq, enum events event, int pid) {
    switch(event) {
        case start: {
            stud_RR_start(rq, pid);
            break;
        }
        case terminate: {
            stud_RR_terminate(rq);
            break;
        }
        case clock_tick: {
            stud_RR_clock_tick(rq);
            break;
        }
        case wait: {
            stud_RR_wait(rq);
            break;
        }
        case wake_up: {
            stud_RR_wake_up(rq, pid);
            break;
        }
    }
}
