# Tutorial — Using the TodoList CLI Application

This guide explains how to build, run and use the TodoList command-line application.

---

## 1. Prerequisites

Make sure you have these installed:

- `gcc`
- `cmake`
- `make`
- `git`

---

## 2. Build the Project

From project root:

```bash
mkdir build
cd build
cmake ..
cmake --build .
A program called todo will be generated.

3. Basic Usage
The program lets you manage simple tasks stored in JSON.

Add a task :
./todo add "Fix Bug" "2025-01-01 10:00" 30 "Detailed description"

List tasks :
./todo list

Mark the task number n as done :
./todo done n

4. Running Unit Tests
Tests are executed with ctest:

cd build
ctest

5. Logging & Errors
The program logs useful information (INFO, WARN, ERROR) during execution.
Logs appear directly on the terminal.

6. Static Analysis
A dedicated target checks for bugs using cppcheck:

cmake --build . --target static-analysis

7. Debugging Support
You can run the program under GDB:

gdb ./todo
(gdb) break mark_task_done
(gdb) run done 1
This makes debugging easy for development and assignments.

8. Where are tasks stored?
Tasks are saved in tasks.json so they persist between runs.

9. Extending the Source Code
Developers can:

Add new commands

Improve scheduling

Modify task properties

Implement sorting / filtering

Changes are done mainly in:
src/todolist.c
src/todolist.h

10. About This Project
This software was built for a programming course and demonstrates:

C programming

CMake build automation

Unit testing

Debugging

Documentation with Doxygen

Automated analysis and hooks