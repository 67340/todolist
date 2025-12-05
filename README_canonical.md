# TodoList CLI — C Project with CMake, Testing, Logging & Automation

This project is a command-line **task management tool** written in C.  
It demonstrates modern software engineering practices:

  Build automation (CMake)  
  Static code analysis  
  Pre-commit hook integration  
  Logging infrastructure  
  Unit testing  
  Debugging tooling  
  Project documentation & release management  

It was created as part of coursework requirements.

---

## Features

  Add tasks with deadlines  
  List existing tasks  
  Mark tasks as completed  
  Persistent storage using JSON  
  Logging with multiple severity levels  
  Unit test support  
  Static analysis configuration  

---

## Project Structure

```
/src
    main.c
    todolist.c
    todolist.h
    log.c
    log.h

/tests
    test_add_task.c
    test_done_function.c

/docs
    doxygen/          (generated documentation)
    tutorials/tutorial.md

/tools
    pre-commit-static-analysis.sh  (hook script)
```

---

## Build Instructions

### 1) Configure build

```bash
mkdir build
cd build
cmake ..
```

### 2) Build executable

```bash
cmake --build .
```

Executable output:

```
./todo
```

---

## Usage

### Add a task

```bash
./todo add "Fix bug" "2025-01-01 10:00" 30 "Bug description"
```

### List tasks

```bash
./todo list
```

### Mark a task done

```bash
./todo done 1
```

---

## Unit Tests

This project uses CTest.

To run tests:

```bash
cd build
ctest
```

---

## Static Analysis

Static analysis is performed using **cppcheck** and executed via CMake target:

```bash
cmake --build . --target static-analysis
```

Logs are printed in the build output.

---

## Pre-Commit Hook Automation

A pre-commit hook runs static analysis automatically before every commit.

### Install locally

```bash
cp tools/pre-commit-static-analysis.sh .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

---

## Logging System

The project includes a custom logging module with multiple levels: DEBUG, INFO, WARN, ERROR.

Example:

```c
log_info("Loaded %zu tasks", count);
```

---

## Debugging Support

Debug build enabled with:

```cmake
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
```

---

## Documentation

Doxygen API docs generated in:

```
docs/doxygen/html/index.html
```

---

## Tutorial

User guide located at:

```
docs/tutorials/tutorial.md
```

---

## Releases

Versioned releases are available on GitHub.

---

## License

Licensed under the MIT License.
