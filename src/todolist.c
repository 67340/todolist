#include "todolist.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cjson/cJSON.h>

#define TASKS_FILE "tasks.json"

/* ============================================================
   Helper: read entire file into a buffer
   ============================================================ */
static char* read_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

/* ============================================================
   Load tasks from JSON
   ============================================================ */
Task* load_tasks(size_t* out_count) {
    LOG_DEBUG("Loading tasks from file: %s", TASKS_FILE);

    *out_count = 0;

    char* json_text = read_file(TASKS_FILE);
    if (!json_text) {
        LOG_INFO("Task file '%s' not found. Starting with an empty list.", TASKS_FILE);
        return NULL;    // no file yet, no tasks
    }

    LOG_DEBUG("File '%s' read successfully, parsing JSON...", TASKS_FILE);

    cJSON* root = cJSON_Parse(json_text);
    free(json_text);

    if (!root) {
        LOG_ERROR("Failed to parse JSON from '%s'. File content is invalid.", TASKS_FILE);
        return NULL;
    }

    if (!cJSON_IsArray(root)) {
        LOG_ERROR("Expected root JSON array, but file '%s' is malformed.", TASKS_FILE);
        cJSON_Delete(root);
        return NULL;
    }

    size_t count = cJSON_GetArraySize(root);
    LOG_INFO("Loaded %zu task(s) from file.", count);

    Task* tasks = malloc(sizeof(Task) * count);
    if (!tasks) {
        LOG_ERROR("Memory allocation failed while loading %zu tasks.", count);
        cJSON_Delete(root);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);

        /* Optional debug of each ID loaded */
        LOG_DEBUG("Parsing task index %zu", i);

        tasks[i].id = cJSON_GetObjectItem(item, "id")->valueint;

        strcpy(tasks[i].name,
            cJSON_GetObjectItem(item, "name")->valuestring);

        strcpy(tasks[i].description,
            cJSON_GetObjectItem(item, "description")->valuestring);

        strcpy(tasks[i].due_date,
            cJSON_GetObjectItem(item, "due_date")->valuestring);

        tasks[i].estimated_minutes =
            cJSON_GetObjectItem(item, "estimated_minutes")->valueint;

        tasks[i].done = cJSON_GetObjectItem(item, "done")->valueint;
    }

    cJSON_Delete(root);

    LOG_INFO("Successfully built in-memory task list.");
    *out_count = count;
    return tasks;
}


/* ============================================================
   Save tasks to JSON
   ============================================================ */
int save_tasks(const Task* tasks, size_t count) {
    cJSON* root = cJSON_CreateArray();

    for (size_t i = 0; i < count; i++) {
        cJSON* obj = cJSON_CreateObject();

        cJSON_AddNumberToObject(obj, "id", tasks[i].id);
        cJSON_AddStringToObject(obj, "name", tasks[i].name);
        cJSON_AddStringToObject(obj, "description", tasks[i].description);
        cJSON_AddStringToObject(obj, "due_date", tasks[i].due_date);
        cJSON_AddNumberToObject(obj, "estimated_minutes",
                                tasks[i].estimated_minutes);
        cJSON_AddNumberToObject(obj, "done", tasks[i].done);

        cJSON_AddItemToArray(root, obj);
    }

    char* json_str = cJSON_Print(root);
    FILE* f = fopen(TASKS_FILE, "w");
    if (!f) {
        free(json_str);
        cJSON_Delete(root);
        return 0;
    }

    fwrite(json_str, 1, strlen(json_str), f);
    fclose(f);

    free(json_str);
    cJSON_Delete(root);
    return 1;
}

/* ============================================================
   List all tasks
   ============================================================ */
void list_tasks(const Task* tasks, size_t count) {
    if (!tasks || count == 0) {
        printf("No tasks found.\n");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        printf("[%d] %s\n", tasks[i].id, tasks[i].name);
        printf("    Desc: %s\n", tasks[i].description);
        printf("    Due:  %s\n", tasks[i].due_date);
        printf("    Est:  %d min\n", tasks[i].estimated_minutes);
        printf("    %s\n\n", tasks[i].done ? "DONE" : "TODO");
    }
}

/* ============================================================
   Add a task
   ============================================================ */
void add_task(char* name,
              char* description,
              char* due_date,
              int estimated_minutes)
{
    size_t count;
    Task* tasks = load_tasks(&count);

    // allocate new space
    Task* new_list = realloc(tasks, sizeof(Task) * (count + 1));

    if (!new_list) {
        printf("Memory error.\n");
        free(tasks);
        return;
    }

    tasks = new_list;

    // create new task
    Task t;
    t.id = (count == 0) ? 1 : tasks[count - 1].id + 1;

    strncpy(t.name, name, sizeof(t.name) - 1);
    t.name[sizeof(t.name) - 1] = '\0';

    strncpy(t.description, description,
            sizeof(t.description) - 1);
    t.description[sizeof(t.description) - 1] = '\0';

    strncpy(t.due_date, due_date,
            sizeof(t.due_date) - 1);
    t.due_date[sizeof(t.due_date) - 1] = '\0';

    t.estimated_minutes = estimated_minutes;
    t.done = 0;

    // append to array
    tasks[count] = t;

    // write back
    save_tasks(tasks, count + 1);
    free(tasks);

    printf("Task added.\n");
}

/* ============================================================
   Mark task as done
   ============================================================ */
int mark_task_done(int id) {
    size_t count;
    Task* tasks = load_tasks(&count);
    if (!tasks) return 0;

    int found = 0;

    for (size_t i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            tasks[i].done = 1;
            found = 1;
            break;
        }
    }

    if (found) {
        save_tasks(tasks, count);
        printf("Task %d marked as DONE.\n", id);
    } else {
        printf("Task %d not found.\n", id);
    }

    free(tasks);
    return found;
}

/* ============================================================
   Optional: list overdue tasks
   ============================================================ */
void list_overdue_tasks(const Task* tasks, size_t count) {
    (void)tasks; // remove this once implemented
    (void)count;

    // TODO: parse due_date ("YYYY-MM-DD HH:MM")
    // TODO: compare with current time
    // TODO: list only overdue tasks

    printf("(overdue feature not implemented yet)\n");
}

/* ============================================================
   Optional: list tasks due in the future
   ============================================================ */
void list_upcoming_tasks(const Task* tasks, size_t count) {
    (void)tasks;
    (void)count;

    // TODO: same logic as overdue but reversed

    printf("(upcoming feature not implemented yet)\n");
}
