
#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$PROJECT_ROOT"

echo "Configuring QuantCore..."
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug

echo "Compiling..."
cmake --build build --parallel

echo "Running QuantCore..."
./build/quantcore_cli
