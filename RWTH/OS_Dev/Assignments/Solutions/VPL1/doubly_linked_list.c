#include <stdbool.h>
#include "scheduler.h"


/**
 * \brief Creates a task
 *
 * \param pid   The pid of the new task
 * \param state Default state of the task
 *
 * \return A pointer to the new task, `NULL` if failed
 */

struct task *stud_task_create(int pid, enum states state) {
    struct task* task = malloc(sizeof(struct task));
    if(task == NULL) return NULL;

    *task = (struct task){
        .pid   = pid,
        .state = state,
        .prev  = NULL,
        .next  = NULL,
    };
    return task;
}

/**
 * \brief Frees/destroys a task
 *
 * \param task Pointer to the task to-be-destroyed
 */
void stud_task_free(struct task *task) {
    if(task == NULL) return;

    free(task);
}

/**
 * \brief Checks whether a run_queue is empty
 *
 * \param rq Pointer to the run_queue
 *
 * \returns `true` iff the run_queue is empty
 */
bool stud_rq_empty(struct run_queue const *rq) {
    return rq == NULL || rq->head == NULL;
}

/**
 * \brief Returns the head of the `run_queue`.
 *
 * \param rq An element of the list
 */
struct task *stud_rq_head(struct run_queue *rq) {
    if(stud_rq_empty(rq)) return NULL;

    return rq->head;
}

/**
 * \brief Computes the length of a `run_queue`
 *
 * \param rq The run_queue
 *
 * \return The length of `rq`
 */
size_t stud_rq_length(struct run_queue *rq) {
	return rq->n_tasks;
}


/**
 * \brief Enqueues a task on the given run_queue. The head stays where it is
 *        and the new task is put at the END of the list.
 *
 * \param rq   Pointer to the run_queue
 * \param task The task to-be-enqueued
 *
 * \returns `true` iff successful
 */
bool stud_rq_enqueue(struct run_queue *rq, struct task *task) {
    if(rq == NULL || task == NULL) {
        printf("err: enqueue got a NULL ptr\n");
        return false;
    }

    if(stud_rq_empty(rq)) {
        rq->head = task;
        rq->n_tasks = 1;
		// make sure that the pointers are empty
		task->next = task->prev = NULL;
        return true;
    } else if(stud_rq_find(rq, task->pid) != NULL) {
		// do not add duplicate pids
        return false;
    }


    struct task *old_tail = stud_rq_tail(rq);

	// start to insert the task at the end of the queue
    task->next = NULL;
    task->prev = old_tail;
	old_tail->next = task;

	// increase the number of tasks
    rq->n_tasks++;

    return true;
}

/**
 * \brief Prepends a task on the given run_queue. The head of the list MUST be
 *        moved to the new task!
 *
 * \param rq   Pointer the run_queue
 * \param task The task to-be-prepended
 *
 * \returns `true` iff successful
 */
bool stud_rq_prepend(struct run_queue *rq, struct task *task) {
    if(rq == NULL || task == NULL) {
        printf("err: prepend got a NULL ptr\n");
        return false;
    }

    if(stud_rq_empty(rq)) {
        rq->head = task;
		task->prev = task->next = NULL;
        rq->n_tasks = 1;
        return true;
    } else if(stud_rq_find(rq, task->pid) != NULL) {
        printf("err: a task with pid %d already exists in the runqueue\n", task->pid);
        return false;
    }


    struct task* old_head = stud_rq_head(rq);
    task->next = old_head;
    task->prev = NULL;
    old_head->prev = task;

    // update list head
    rq->head = task;
    rq->n_tasks++;

    return true;
}

/**
 * \brief Returns the tail of the `run_queue`.
 *
 * \param rq An element of the list
 */
struct task *stud_rq_tail(struct run_queue *rq) {
    if(stud_rq_empty(rq)) return NULL;

    struct task* tsk = rq->head;
	// Notice here that we don't check tsk == NULL but tsk->next
    while(tsk->next != NULL) {
        tsk = tsk->next;
    }

    return tsk;
}

/**
 * \brief Tries to find a task in a run_queue by its PID
 *
 * \param rq  Pointer to the run_queue
 * \param pid PID of the wanted task
 *
 * \returns Pointer to the task, `NULL` if failed
 */
struct task *stud_rq_find(struct run_queue *rq, int pid) {
    if(stud_rq_empty(rq)) return NULL;

    struct task* tsk = rq->head;

    while(tsk != NULL) {
        if(tsk->pid == pid) {
			// we found it !
            return tsk;
        }
        tsk = tsk->next;
    }

    return NULL;
}

// additional function
// make sure this is not the head of the queue
void remove_task_from_runqueue(struct task* task) {
    if(task == NULL) return;

    if(task->next != NULL) {
        task->next->prev = task->prev;
    }

    if(task->prev != NULL) {
        task->prev->next = task->next;
    }

    task->prev = task->next = NULL;
}

// additional function that can be very useful
// very important not to call the remove function because we need to
// update the head
//
// removes the head of the queue and update the run queue's head
struct task* stud_rq_pop(struct run_queue* rq) {
    if(stud_rq_empty(rq)) {
        // Nothing to pop
        return NULL;
    }

    struct task *old_head = stud_rq_head(rq);

    // if there is a next element, update it and shift the list there
    if(old_head->next != NULL) {
		// head->prev should be NULL
        old_head->next->prev = NULL;
    }

    rq->head = old_head->next;
    old_head->next = old_head->prev = NULL;
    rq->n_tasks--;

    return old_head;
}


/**
 * \brief Frees/destroys **the whole** run_queue
 *
 * \param rq Pointer to the run_queue to-be-destroyed
 */
void stud_rq_destroy(struct run_queue *rq) {
    if(stud_rq_empty(rq)) return;

    struct task* head = rq->head;
	struct task* del;

    while(head != NULL) {
		// make sure to use a temporary head pointer to be able
		// to continue the iteration after deletion
		del = head;
        head = head->next;
        stud_task_free(del);
    }

    rq->head = NULL;
    rq->n_tasks = 0;
}
