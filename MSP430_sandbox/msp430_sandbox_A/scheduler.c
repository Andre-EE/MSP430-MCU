#include "scheduler.h"

// Array to hold tasks
static Task task_list[MAX_TASKS];
static uint8_t numTasks = 0;
static uint8_t task_index = 0;

void scheduler_init(void)
{
    // Initialize any necessary scheduler data structures or variables
    numTasks = 0;
}

uint8_t scheduler_add_task(void (*function)(void), uint32_t timeSlot, uint32_t period)
{
    task_index = 0;

    // Find a gap in the array
    while ((task_list[task_index].taskFunction != 0) && (task_index < MAX_TASKS))
    {
        task_index++;
    }

    // Error out if no gap in array
    if (task_index == MAX_TASKS)
    {
        // Handle task list error - work to go
        return MAX_TASKS;
    }

    // Initialize the new task
    Task new_task;

    new_task.taskFunction  = function;
    new_task.timeSlot      = timeSlot;
    new_task.period        = period;
    new_task.inQueue       = 0;

    // Copy the new task to the task_list array
    task_list[task_index] = new_task;

    // Increment the number of tasks
    numTasks++;

    return task_index;
}

void scheduler_delete_task(const uint8_t task_index)
{
    if (task_list[task_index].taskFunction != 0)
    {
        task_list[task_index].taskFunction  = 0x0000;
        task_list[task_index].period        = 0;
        task_list[task_index].timeSlot      = 0;
        task_list[task_index].inQueue       = 0;
    }
    // Decrement the number of tasks
    numTasks--;
}

void scheduler_update(void)
{
    for (task_index = 0; task_index < MAX_TASKS; task_index++)
    {
        if (task_list[task_index].taskFunction)
        {
            // Task time slot has not arrived
            if (task_list[task_index].timeSlot > 0)
                task_list[task_index].timeSlot -= 1;
            // Task is ready to be executed
            else
            {
                // Mark for execution
                task_list[task_index].inQueue += 1;
                // If repeating task, add back to queue with time slot defined by period
                if (task_list[task_index].period)
                    task_list[task_index].timeSlot = task_list[task_index].period - 1;
            }
        }
    }
}

void scheduler_execute_tasks(void)
{
    for (task_index = 0; task_index < MAX_TASKS; task_index++)
    {
        if (task_list[task_index].inQueue > 0)
        {
            task_list[task_index].taskFunction();
            task_list[task_index].inQueue -= 1;

            // Delete 'execute once' task
            if (task_list[task_index].period == 0)
                scheduler_delete_task(task_index);
        }
    }
}

void scheduler_run(void)
{
    scheduler_update();
    scheduler_execute_tasks();
}

