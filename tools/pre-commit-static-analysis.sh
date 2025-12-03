#!/bin/sh
# Git pre-commit hook: run CMake static-analysis target (cppcheck)

echo "Running static analysis (cppcheck) before commit..."

# Ensure we are at the repo root (where CMakeLists.txt is)
REPO_ROOT="$(git rev-parse --show-toplevel)"
cd "$REPO_ROOT" || exit 1

# Ensure build directory + CMake configuration exist
if [ ! -d "build" ]; then
  echo "No build directory found. Creating one and running CMake..."
  mkdir -p build || exit 1
  cd build || exit 1
  cmake .. || exit 1
  cd ..
fi

# Run static-analysis target
cd build || exit 1
cmake --build . --target static-analysis
STATUS=$?
cd ..

if [ $STATUS -ne 0 ]; then
  echo "Static analysis FAILED. Commit aborted."
  exit 1
fi

echo "Static analysis OK. Proceeding with commit."
exit 0
