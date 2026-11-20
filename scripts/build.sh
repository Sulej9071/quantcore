
#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$PROJECT_ROOT"

echo "[1/4] Configuring QuantCore..."
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug

echo "[2/4] Compiling..."
cmake --build build --parallel

echo "[3/4] Running unit tests..."
ctest --test-dir build --output-on-failure

echo "[4/4] Running QuantCore..."
./build/quantcore_cli

echo "QuantCore build and tests completed successfully."
