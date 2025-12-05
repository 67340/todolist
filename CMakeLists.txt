
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(todo_deadlines
    VERSION 0.1.0
    LANGUAGES C
)

enable_testing()

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================================
# Dependencies: cJSON via FetchContent
# ============================================================
include(FetchContent)

FetchContent_Declare(
    cjson
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG master    # you can replace by a specific tag for reproducibility
)

FetchContent_MakeAvailable(cjson)

# ============================================================
# Executable
# ============================================================
add_executable(todo
    src/main.c
    src/todolist.c
    src/log.c
)

# Link with cJSON
target_link_libraries(todo PRIVATE cjson)

# Optionally, you can add extra include dirs if needed:
# target_include_directories(todo PRIVATE ${cjson_SOURCE_DIR})

# ============================================================
# Install & packaging (for assignment "packaging" part)
# ============================================================
install(TARGETS todo
    RUNTIME DESTINATION bin
)

include(CPack)

# ==========================
# Static analysis: cppcheck
# ==========================
find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)

if(CPPCHECK_EXECUTABLE)
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
endif()

