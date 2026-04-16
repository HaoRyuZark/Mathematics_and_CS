#include "scheduler.h"

/**
 * \brief Enqueues a process in READY state
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be enqueued
 */
void stud_FCFS_start(struct run_queue* rq, int pid) {
    struct task* new_task = stud_task_create(pid, READY);
	if (new_task == NULL)
		return;
    stud_rq_enqueue(rq, new_task);
}

/**
 * \brief Elects and starts a process from the run queue. The running process MUST be placed
 *        at the head of `rq` if it is not already there.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_elect(struct run_queue* rq) {
    if(stud_rq_empty(rq)) {
        printf("FCFS/elect: queue is empty.\n");
        return;
    }

	struct task *it = stud_rq_head(rq);

	if (it->state == RUNNING) {
		return;
	}

    // Iterate through the run queue
    while(it != NULL) {
		// the first ready task is elected because
		// First Come First Served
        if(it->state == READY) {
            // Update state
            it->state = RUNNING;

			if (it == stud_rq_head(rq)) {
				// If it's the head, perfect, we have nothing more to do
				return;
			}

			// Otherwise, remove it from the queue
			remove_task_from_runqueue(it);
            // And put it at the top
            stud_rq_prepend(rq, it);

            rq->n_tasks--;
            return;
        }
        it = it->next;
    }

}

/**
 * \brief Terminates the current running process (i.e. rq->head) and places it at the BACK
 *        of the run_queue.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_terminate(struct run_queue* rq) {
    if(stud_rq_empty(rq)) {
        return;
    }

    stud_rq_head(rq)->state = TERMINATED;

    // Put the terminated task at the back of the list
    stud_rq_enqueue(rq, stud_rq_pop(rq));

    // Elect new task
    stud_FCFS_elect(rq);

}

/**
 * \brief Performs a clock tick as specified by FCFS.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_clock_tick(struct run_queue* rq) {
    return;
}

/**
 * \brief Sets the state of the running process to BLOCKED, moves it to the BACK of the
 *        run_queue, and elects and runs a new process.
 *
 * \param rq  The scheduler's run queue
 */
void stud_FCFS_wait(struct run_queue* rq) {
    if(stud_rq_empty(rq)) {
        return;
    }

    // Set state to blocked
    stud_rq_head(rq)->state = BLOCKED;

    // Move to back of list
    stud_rq_enqueue(rq, stud_rq_pop(rq));

    // Elect new task
    stud_FCFS_elect(rq);
}

/**
 * \brief Sets the state of `pid` to READY, if it exists, and moves it to the BACK
 *        of the run_queue
 *
 * \param rq  The scheduler's run queue
 * \param pid The process to be woken up
 */
void stud_FCFS_wake_up(struct run_queue* rq, int pid) {
    struct task* task = stud_rq_find(rq, pid);
    if(task == NULL) {
        return;
    }

    // Update state
    task->state = READY;

    if(task == stud_rq_head(rq)) {
		// Don't call remove_task_from_runqueue on the head
		stud_rq_pop(rq);
    } else {
        // Move to end as if task were a newly created task
        remove_task_from_runqueue(task);
        rq->n_tasks--;
    }

	stud_rq_enqueue(rq, task);
    stud_FCFS_elect(rq);
}

/**
 * \brief Event handler for FCFS
 *
 * \param rq    The scheduler's run queue
 * \param event The event to be handled
 * \param pid   Depending on `event`, the `pid` of the target process.
 *              If the `event` doesn't need this, it is ignored.
 */
void stud_FCFS(struct run_queue* rq, enum events event, int pid) {
    switch(event) {
        case start: {
            stud_FCFS_start(rq, pid);
            break;
        }
        case terminate: {
            stud_FCFS_terminate(rq);
            break;
        }
        case clock_tick: {
            stud_FCFS_clock_tick(rq);
            break;
        }
        case wait: {
            stud_FCFS_wait(rq);
            break;
        }
        case wake_up: {
            stud_FCFS_wake_up(rq, pid);
            break;
        }
    }
}
