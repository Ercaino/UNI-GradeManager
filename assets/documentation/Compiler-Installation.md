## 📦 Compiler installation GCC - Clang (MacOS)

To install GCC (GNU Compiler Collection) on a Linux machine, the process varies slightly depending on the distribution you are using.

### 1. <img src="https://skillicons.dev/icons?i=ubuntu" width="20" alt="Gallery" /> Ubuntu / Debian / Kali Linux

```bash
    sudo apt update
    sudo apt install build-essential
```

> ⚠️ Note: The build-essential package includes GCC, G++, make, and other tools needed to build software.

### 2. <img src="https://skillicons.dev/icons?i=linux" width="20" alt="Gallery" /> Fedora / CentOS Stream

```bash
    # or yum on older versions
    sudo dnf install gcc       # Install only GCC
```
```bash
    sudo dnf install gcc-c++       # Install cpp compiler
```

### 3. <img src="https://skillicons.dev/icons?i=arch" width="20" alt="Gallery" /> Arch Linux

```bash
    sudo pacman -S gcc       # Install only GCC
```
```bash
    sudo pacman -S gcc-libs       # Install cpp compiler
```

### Verify Linux System

```bash
    gcc --version
    g++ --version
```


### 4. <img src="https://skillicons.dev/icons?i=windows" width="20" alt="Gallery" /> Windows

#### - 📦 MinGW

1. Download MinGW
    - Go to the official website: https://sourceforge.net/projects/mingw/files/  
    - Download the installer `mingw-get-setup.exe`.

2. Install MinGW
    - Run the `.exe` file and follow the instructions.
    - Select packages:
    ```bash
        mingw32-base (obligatory) 
        mingw32-gcc-g++ (to compile C and C++)
    ```

3. Add GCC to PATH
    - Go to System Properties → Advanced system settings → Environment variables.
    - Find the Path environment variable (system or user) and add the path:
    ```bash
        C:\MinGW\bin
    ```

#### - 📦 MSYS2

MSYS2 is a more complete platform than MinGW, with a package manager `pacman` similar to Arch Linux.

1. Download MSYS2
    - Go to the official website: https://www.msys2.org/   
    - Download and install the program.

2. Update the system
    ```bash
        pacman -Syu
    ```
    Close and reopen MSYS2, then repeat:

3. Install GCC
    - To compile C code:
    ```bash
        pacman -S mingw-w64-x86_64-gcc
    ```
    - To compile C++ code:
    ```bash
        pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-libstdc++-jit
    ```

4. Add to PATH
    - You can add it to your PATH if you want to use it outside of MSYS2 as well.
    ```bash
        C:\msys64\mingw64\bin
    ```

#### - 📦 WSL (Windows Subsystem for Linux)
If you prefer to work in a real Linux environment, you can install WSL on Windows and then install GCC as you would on Ubuntu or Debian.

1. Install WSL
    ```bash
        wsl --install
    ```
    Restart your PC and set up Linux when prompted.

### Verify Windows System

Open Command Prompt `cmd` and type:
```bash
    gcc --version
    g++ --version
```


### 5. <img src="https://skillicons.dev/icons?i=apple" width="20" alt="Gallery" /> MacOS (clang)
    
```bash
    xcode-select --install
```

> ⚠️ Note: This will install Clang, LLVM, make, and other useful development tools.

### 5. <img src="https://skillicons.dev/icons?i=apple" width="20" alt="Gallery" /> MacOS (Homebrew)
```bash
    brew install gcc
    brew install openssl readline     # Additional libraries
```

### Verify MacOS System

```bash
    clang --version
```

