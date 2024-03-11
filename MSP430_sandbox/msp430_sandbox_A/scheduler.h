#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

// Maximum number of tasks
#define MAX_TASKS 8

// Task structure
typedef struct {
    void (  *taskFunction)(void); // Function pointer
    uint32_t timeSlot;      // Interval in milliseconds
    uint32_t period;        // Last execution time
    uint8_t  inQueue;        // Flag or count for execution
} Task;

// Initialize the scheduler
void scheduler_init(void);

// Add a task to the scheduler
uint8_t scheduler_add_task(void (*function)(void), uint32_t timeSlot, uint32_t period);

// Delete task
void scheduler_delete_task(const uint8_t task_index);

// Execute task if there's one marked in queue
void scheduler_execute_tasks(void);

// Update tasks delays and queue up if ready to execute
void scheduler_update(void);

// Wrap up the necessary scheduler functions
void scheduler_run(void);

#endif /* SCHEDULER_H_ */
