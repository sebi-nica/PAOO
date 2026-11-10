#!/usr/bin/env bash
# Configureaza, compileaza si ruleaza aplicatia.
set -e
cd "$(dirname "$0")"
mkdir -p build
cd build
cmake ..
make
echo
./aplicatie/aplicatie "$@"
