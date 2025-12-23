#include "Adubo.h"
#include "Posicao.h"
#include "Settings.h"
#include <string>

Adubo::Adubo() : quantidadeAdubo(Settings::Adubo::capacidade) {}

Adubo::Adubo(int quantidade, int numeroSerie) : quantidadeAdubo(quantidade) {
    setNumeroSerie(numeroSerie);
}

Adubo::~Adubo() {}

Ferramenta* Adubo::clone() const {
    Adubo* a = new Adubo(quantidadeAdubo, numeroSerie);
    return a;
}

bool Adubo::usar(Posicao* pos) {
    if (quantidadeAdubo >= Settings::Adubo::dose) {
        pos->adicionarNutrientes(Settings::Adubo::dose);
        quantidadeAdubo -= Settings::Adubo::dose;
        return false;
    }
    return true;
}

char Adubo::getCaracter() const { return 'a'; }
std::string Adubo::getTipo() const { return "Adubo"; }
std::string Adubo::getInfo() const { 
    return "Adubo #" + std::to_string(numeroSerie) + 
           " (" + std::to_string(quantidadeAdubo) + "/" + 
           std::to_string(Settings::Adubo::capacidade) + ")"; 
}

int Adubo::getQuantidade() const { 
    return quantidadeAdubo; 
}