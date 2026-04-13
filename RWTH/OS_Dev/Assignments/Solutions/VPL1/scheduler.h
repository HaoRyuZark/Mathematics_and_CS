#ifndef SCHEDULER_H__
#define SCHEDULER_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUANTUM 10

enum states {
    BLOCKED = 0,
    RUNNING,
    READY,
    TERMINATED,
};

enum events {
    start = 0,
    wait,
    wake_up,
    terminate,
    clock_tick,
};

struct task {
    int pid;
    enum states state;
    struct task* prev;
    struct task* next;
};

struct run_queue {
    struct task* head;
    size_t n_tasks;
    int time_counter;
};



/**
 * \brief Checks whether a run_queue is empty
 *
 * \param rq Pointer to the run_queue
 *
 * \returns `true` iff the run_queue is empty
 */
bool stud_rq_empty(struct run_queue const *rq);
struct task *stud_task_create(int pid, enum states state);
void stud_task_free(struct task *task);
void stud_rq_destroy(struct run_queue *rq);
struct task *stud_rq_find(struct run_queue *rq, int pid);
struct task *stud_rq_tail(struct run_queue *rq);
bool stud_rq_enqueue(struct run_queue *rq, struct task *task);
bool stud_rq_prepend(struct run_queue *rq, struct task *task);
size_t stud_rq_length(struct run_queue *rq);
struct task* stud_rq_pop(struct run_queue* rq);
struct task *stud_rq_head(struct run_queue *rq);

void stud_FCFS_start(struct run_queue* rq, int pid);
void stud_FCFS_elect(struct run_queue* rq);
void stud_FCFS_terminate(struct run_queue* rq);
void stud_FCFS_clock_tick(struct run_queue* rq);
void stud_FCFS_wait(struct run_queue* rq);
void stud_FCFS_wake_up(struct run_queue* rq, int pid);

void remove_task_from_runqueue(struct task* task);
struct task* stud_rq_pop(struct run_queue* rq);


#endif // SCHEDULER_H__
