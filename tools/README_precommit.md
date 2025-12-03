# Pre-commit Hook: Automatic Static Code Analysis

This project includes a **Git pre-commit hook** that automatically runs\
**cppcheck static analysis** before any commit.

## Purpose

The goal is to ensure that every commit satisfies the project's static
analysis rules (Step 1 of the assignment).\
If cppcheck reports errors, the commit is **blocked** until the issues
are fixed.

This improves code quality and prevents faulty commits from entering the
repository.

------------------------------------------------------------------------

## Hook Script (copy included for evaluation)

Git hooks are stored in `.git/hooks/`, which is **not tracked** by Git
and\
cannot be pushed to GitHub.

To allow evaluation of the hook configuration, the script is duplicated
in:

    tools/pre-commit-static-analysis.sh

This file contains the exact same code used by the real hook.

------------------------------------------------------------------------

## Installing the Hook Locally

To activate the hook on any clone of this repository, run:

``` bash
cp tools/pre-commit-static-analysis.sh .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

After installation, every `git commit` will:

1.  Run CMake (if needed)
2.  Run the `static-analysis` target configured with cppcheck
3.  Abort the commit if analysis fails

Example output:

    Running static analysis (cppcheck) before commit...
    [100%] Running cppcheck static analysis
    Static analysis OK. Proceeding with commit.

If cppcheck reports errors, the commit stops:

    Static analysis FAILED. Commit aborted.

------------------------------------------------------------------------

## Technical Details

The hook uses the custom CMake target:

``` cmake
add_custom_target(static-analysis
    COMMAND ${CPPCHECK_EXECUTABLE}
        --enable=all
        --inconclusive
        --std=c11
        --language=c
        --quiet
        ${CMAKE_SOURCE_DIR}/src
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck static analysis"
)
```

It is executed from the script located at:

    tools/pre-commit-static-analysis.sh

The script automatically:

-   Ensures a `build/` directory exists\
-   Runs `cmake ..` if needed\
-   Runs `cmake --build . --target static-analysis`\
-   Blocks commits if analysis fails

------------------------------------------------------------------------

This completes **Step 2: Automate static analysis with a pre-commit
hook** for the assignment.
