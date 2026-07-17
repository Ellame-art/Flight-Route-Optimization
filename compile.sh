#!/bin/bash

echo "Compiling Airport Management System..."

g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o AirportSystem

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Compilation successful!"
    echo "Executable created: ./AirportSystem"
    echo ""
    echo "Run using:"
    echo "./AirportSystem"
else
    echo ""
    echo "❌ Compilation failed."
    echo "Please fix the compilation errors and try again."
fi