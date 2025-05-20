#include <iostream>
#include "CMakeConfig.h"

int main(){
    std::cout<<"hello Word"<<std::endl;
    std::cout << "Versione del progetto: " << PROJECT_VERSION << std::endl;
    std::cout << "Versione del progetto M e m: " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << std::endl;

    return 0;
}