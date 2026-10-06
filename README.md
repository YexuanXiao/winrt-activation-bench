How to build and run:

1. Open Visual Studio Command Prompt
2. Clone the repo
3. cd into the repo
4. git clone https://github.com/google/benchmark.git --depth=1
5. cmake -G "Visual Studio 18 2026" -A x64 -S . -B build
6. cmake --build build --config Release
7. .\\build\\Release\\bench32.exe
8. .\\build\\Release\\bench64.exe
9. .\\build\\Release\\bench219.exe