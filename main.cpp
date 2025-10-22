#include "Interface.h"
#include <iostream>

int main() {
    try {
        Interface interface;
        interface.executar();
    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}