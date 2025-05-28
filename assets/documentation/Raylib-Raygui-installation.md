## 📦 Installation Dependencies

La versione GUI richiede raylib  e raygui . 
1. Scarica raylib: https://www.raylib.com/   
2. Scarica raygui: https://github.com/raysan5/raygui   

### 1. Installa da sorgente (globalmente)
- Clona Raylib e raygui nel tuo progetto

```bash
    mkdir external
    cd external
    git clone https://github.com/raysan5/raylib.git 
    cd raylib
    git submodule update --init --recursive

```

```bash
    cd ..
    git clone https://github.com/raysan5/raygui.git 
```


```bash
    # Crea la build
    mkdir build && cd build
    cmake .. -DPLATFORM=PLATFORM_DESKTOP -DBUILD_SHARED_LIBS=OFF
    cmake --build . --target install
```


```CMake
    cmake_minimum_required(VERSION 3.14)
    project(MioProgetto)

    set(CMAKE_CXX_STANDARD 17)

    # Trova Raylib
    find_package(raylib REQUIRED)

    # Definisci l'eseguibile
    add_executable(MioProgetto src/main.cpp)

    # Linka Raylib
    target_link_libraries(MioProgetto PRIVATE raylib::raylib-header-only)

    # Se usi raygui, devi includerlo manualmente
    include_directories(${PROJECT_SOURCE_DIR}/external/raygui/src)
```

