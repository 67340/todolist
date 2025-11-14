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


Task* load_tasks(size_t* out_count);
int save_tasks(const Task* tasks, size_t count);

// Operations
void list_tasks(const Task* tasks, size_t count);
void add_task(char* name,
              char* description,
              char* due_date,
              int estimated_minutes);

int mark_task_done(int id);
void list_overdue_tasks(const Task* tasks, size_t count);
void list_upcoming_tasks(const Task* tasks, size_t count);

#endif // TASK_H
