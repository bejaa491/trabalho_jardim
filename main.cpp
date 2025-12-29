/**
 * ============================================================================
 *  SIMULADOR DE JARDIM - POO 2025/2026
 *  Programação Orientada a Objetos - Trabalho Prático
 *  
 *  Simulador completo de um jardim com plantas, ferramentas e jardineiro.
 *  
 *  Características:
 *    - 5 tipos de plantas (Roseira, Cacto, Erva, Cantora, Exótica)
 *    - 4 tipos de ferramentas (Regador, Adubo, Tesoura, Pulverizador)
 *    - Simulação realista com ciclos de vida
 *    - Persistência de estado (salvar/restaurar snapshots)
 *    - Interface textual interativa
 *  
 *  Uso:
 *    ./trabalho_jardim.exe
 *    Digite 'jardim <linhas> <colunas>' para iniciar
 *    Digite 'fim' para terminar
 * ============================================================================
 */
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