#include "todolist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(const char* prog) {
    printf("Usage:\n");
    printf("  %s list\n", prog);
    printf("  %s add \"name\" \"due_date\" estimated_minutes \"description\"\n", prog);
    printf("      due_date format: \"YYYY-MM-DD HH:MM\"\n");
    printf("  %s done <id>\n", prog);
    printf("  %s overdue\n", prog);
    printf("  %s upcoming\n", prog);
    printf("  %s help\n", prog);
}

/*
 * Simple CLI:
 *   todo list
 *   todo add "name" "2025-11-14 18:00" 60 "some description"
 *   todo done 3
 *   todo overdue
 *   todo upcoming
 */
int main(int argc, char** argv) {
    const char* prog = (argc > 0) ? argv[0] : "todo";

    if (argc < 2) {
        print_usage(prog);
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        print_usage(prog);
        return 0;
    }

    if (strcmp(argv[1], "list") == 0) {
        size_t count;
        Task* tasks = load_tasks(&count);
        list_tasks(tasks, count);
        free(tasks);
        return 0;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 6) {
            printf("Error: not enough arguments for 'add'.\n");
            print_usage(prog);
            return 1;
        }

        char* name = argv[2];
        char* due_date = argv[3];
        int estimated_minutes = atoi(argv[4]);
        char* description = argv[5];

        add_task(name, description, due_date, estimated_minutes);
        return 0;
    }

    if (strcmp(argv[1], "done") == 0) {
        if (argc < 3) {
            printf("Error: missing id for 'done'.\n");
            print_usage(prog);
            return 1;
        }

        int id = atoi(argv[2]);
        if (!mark_task_done(id)) {
            return 1; // already prints an error
        }
        return 0;
    }

    if (strcmp(argv[1], "overdue") == 0) {
        size_t count;
        Task* tasks = load_tasks(&count);
        list_overdue_tasks(tasks, count);
        free(tasks);
        return 0;
    }

    if (strcmp(argv[1], "upcoming") == 0) {
        size_t count;
        Task* tasks = load_tasks(&count);
        list_upcoming_tasks(tasks, count);
        free(tasks);
        return 0;
    }

    printf("Unknown command: %s\n\n", argv[1]);
    print_usage(prog);
    return 1;
}
