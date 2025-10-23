#include "Adubo.h"

int quantidadeAdubo; // 100 inicialmente
bool usar(Posicao* pos) {
    if (quantidadeAdubo >= 10) {
        pos->adicionarNutrientes(10);
        quantidadeAdubo -= 10;
        return false;
    }
    return true; // Destruir quando vazio
}