## 📦 CMake installation 

### 1. <img src="https://skillicons.dev/icons?i=ubuntu" width="20" alt="Gallery" /> Ubuntu / Debian / Kali Linux

```bash
    sudo apt update
    sudo apt install cmake
```

> ⚠️ Note: This version may not be the latest available.


### 2. <img src="https://skillicons.dev/icons?i=linux" width="20" alt="Gallery" /> Fedora / CentOS Stream

```bash
    # or yum on older versions
    sudo dnf install cmake       
```

> ⚠️ Note: This will install the stable release available in the Fedora repositories (often updated).

### 3. <img src="https://skillicons.dev/icons?i=arch" width="20" alt="Gallery" /> Arch Linux

```bash
    sudo pacman -S cmake       
```

### Verify Linux System

```bash
    cmake --version
```

### 4. <img src="https://skillicons.dev/icons?i=windows" width="20" alt="Gallery" /> Windows

1. Download CMake
    - Go to the official website: https://cmake.org/download/ 
    - Find `cmake-x.y.z-win64-x64.msi` (for 64-bit systems)

2. Run installer
    - This allows you to use cmake directly from the command prompt.
    
    > ✅ Add CMake to the system PATH for all users

3. Add GCC to PATH
    - Go to System Properties → Advanced system settings → Environment variables.
    - Find the Path environment variable (system or user) and add the path:
    ```bash
        C:\MinGW\bin
    ```

### Verify Windows System

```bash
    cmake --version
```

### Quick test with a CMake project

CMake file:
```CMake
    cmake_minimum_required(VERSION 3.10)
    project(TestCMake)

    add_executable(hello main.cpp)
```
Code cpp:
```Cpp
    #include <iostream>
    int main() {
        std::cout << "Hello from CMake!\n";
        return 0;
    }
```
Build project and execute:
```bash
    mkdir build     # 1. Create a build directory
    cd build
    cmake ..        # 2. Configure the project
    cmake --build .     # 3. Build the project
    ./hello
```
On Windows:
```bash
    cmake --build .
    .\hello.exe
```


### Basic program

```cpp
#include <iostream>
#include "CMakeConfig.h"

int main(){
    std::cout<<"hello Word"<<std::endl;
    std::cout << "Versione del progetto: " << PROJECT_VERSION << std::endl;
    std::cout << "Versione del progetto M e m: " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << std::endl;

    return 0;
}
```