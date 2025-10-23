#include "Adubo.h"
#include "Posicao.h"
#include "Settings.h"
#include <string>

Adubo::Adubo() : quantidadeAdubo(Settings::Adubo::capacidade) {}
Adubo::~Adubo() {}

bool Adubo::usar(Posicao* pos) {
    if (quantidadeAdubo >= Settings::Adubo::dose) {
        pos->adicionarNutrientes(Settings::Adubo::dose);
        quantidadeAdubo -= Settings::Adubo::dose;
        return false; // ainda existe adubo
    }
    return true; // deve ser destruída quando vazio
}

char Adubo::getCaracter() const { return 'A'; }
std::string Adubo::getTipo() const { return "Adubo"; }
std::string Adubo::getInfo() const { 
    return "Adubo #" + std::to_string(numeroSerie) + 
           " (" + std::to_string(quantidadeAdubo) + "/" + 
           std::to_string(Settings::Adubo::capacidade) + ")"; 
}

int Adubo::getQuantidade() const { 
    return quantidadeAdubo; 
}