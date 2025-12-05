#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todolist.h"

/* Start from a clean tasks.json */
static void reset_tasks_file(void) {
    /* ignore error if file doesn't exist */
    remove("tasks.json");
}

int main(void) {
    size_t count;
    Task* tasks = NULL;

    /* -------- Test 1: add_task + load_tasks round-trip -------- */
    reset_tasks_file();

    add_task("Test1", "Desc1", "2025-01-01 10:00", 30);
    add_task("Test2", "Desc2", "2025-01-02 11:30", 45);

    tasks = load_tasks(&count);
    assert(tasks != NULL);
    assert(count == 2);

    /* Check first task fields */
    assert(strcmp(tasks[0].name, "Test1") == 0);
    assert(strcmp(tasks[0].description, "Desc1") == 0);
    assert(strcmp(tasks[0].due_date, "2025-01-01 10:00") == 0);
    assert(tasks[0].estimated_minutes == 30);
    assert(tasks[0].done == 0);

    /* Check second task fields */
    assert(strcmp(tasks[1].name, "Test2") == 0);
    assert(strcmp(tasks[1].description, "Desc2") == 0);
    assert(strcmp(tasks[1].due_date, "2025-01-02 11:30") == 0);
    assert(tasks[1].estimated_minutes == 45);
    assert(tasks[1].done == 0);

    free(tasks);

    /* -------- Test 2: mark_task_done changes state -------- */
    /* Task IDs start at 1 in our implementation */
    int result = mark_task_done(1);
    assert(result == 1);  /* should succeed */

    tasks = load_tasks(&count);
    assert(tasks != NULL);
    assert(count == 2);
    assert(tasks[0].done == 1);  /* first task marked done */
    assert(tasks[1].done == 0);  /* second still todo */

    free(tasks);

    /* -------- Test 3: mark_task_done on unknown id -------- */
    result = mark_task_done(9999);
    assert(result == 0);  /* should fail gracefully */

    printf("All todolist unit tests passed.\n");
    return 0;
}
