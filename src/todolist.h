#ifndef TASK_H
#define TASK_H

#include <stddef.h>

typedef struct {
    int id;
    char name[128];
    char description[256];
    char due_date[20];      // "YYYY-MM-DD HH:MM"
    int estimated_minutes;
    int done;
} Task;

/**
 * @brief Load tasks from the JSON storage file.
 *
 * If the file does not exist or cannot be parsed, @p out_count is set to 0
 * and the function returns NULL.
 *
 * @param[out] out_count Will receive the number of tasks loaded.
 * @return Dynamically allocated array of Task, or NULL on error.
 *         Caller is responsible for calling free() on the returned pointer.
 */
Task* load_tasks(size_t* out_count);

/**
 * @brief Save an array of tasks to the JSON storage file.
 *
 * @param tasks Pointer to the first element of the tasks array.
 * @param count Number of tasks to write.
 * @return 1 on success, 0 on failure.
 */
int save_tasks(const Task* tasks, size_t count);

/**
 * @brief Print all tasks to stdout in a human-readable form.
 *
 * @param tasks Pointer to the tasks array.
 * @param count Number of tasks in the array.
 */
void list_tasks(const Task* tasks, size_t count);

/**
 * @brief Add a new task and append it to the JSON storage.
 *
 * A new unique id is automatically assigned.
 *
 * @param name Title of the task.
 * @param description Optional description.
 * @param due_date Due date as string "YYYY-MM-DD HH:MM".
 * @param estimated_minutes Estimated duration in minutes.
 */
void add_task(char* name,
              char* description,
              char* due_date,
              int estimated_minutes);

/**
 * @brief Mark a task as completed.
 *
 * @param id Identifier of the task to mark as DONE.
 * @return 1 if the task was found and updated, 0 otherwise.
 */
int mark_task_done(int id);

/**
 * @brief List only overdue tasks (due date in the past).
 *
 * @param tasks Pointer to the tasks array.
 * @param count Number of tasks.
 */
void list_overdue_tasks(const Task* tasks, size_t count);

/**
 * @brief List tasks that are due in the future.
 *
 * @param tasks Pointer to the tasks array.
 * @param count Number of tasks.
 */
void list_upcoming_tasks(const Task* tasks, size_t count);


#endif // TASK_H
