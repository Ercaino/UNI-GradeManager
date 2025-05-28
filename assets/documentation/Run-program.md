## Run with CMake

1. Make sure g++ and cmake are installed

    ```bash
        sudo apt update
        sudo apt install build-essential cmake
    ```
    On Windows: Use `MSYS2` or `MinGW` or use `WSL`

2. Create a build folder and configure the project

    ```bash
        mkdir build
        cd build
        cmake ..
    ```

3. Fill out the project

    ```bash
        cmake --build .
    ```

2. Run the program

    ```bash
        ./programma     # Linux
    ```
    ```bash
        programma.exe       # Windows
    ```


## Run with G++ one file

1. Compile the `.cpp` file

    ```bash
        g++ main.cpp -o programma
    ```

2. Run the program

    ```bash
        ./programma     # Linux
    ```
    ```bash
        programma.exe       # Windows
    ```

## Run with G++ across multiple files

1. Compile the `.cpp` file

    ```bash
        g++ main.cpp funzioni.cpp -o programma
    ```

2. Run the program

    ```bash
        ./programma     # Linux
    ```
    ```bash
        programma.exe       # Windows
    ```

### Separate compilation (advanced mode)

1. Compile each `.cpp` file into a `.o` object

    ```bash
        g++ -c main.cpp -o main.o
        g++ -c funzioni.cpp -o funzioni.o
    ```

2. Link objects into a single executable

    ```bash
        g++ main.o funzioni.o -o programma
    ```

### 🧱 Makefile

```bash
programma: main.o funzioni.o
    g++ main.o funzioni.o -o programma

main.o: main.cpp funzioni.h
    g++ -c main.cpp

funzioni.o: funzioni.cpp funzioni.h
    g++ -c funzioni.cpp

clean:
    rm -f *.o programma
```

Use the make command to compile:
```bash
    make
    ./programma
```
