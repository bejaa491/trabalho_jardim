#include "Regador.h"
#include "Posicao.h"
#include "Settings.h"

Regador::Regador() : capacidadeAgua(Settings::Regador::capacidade) {}
Regador::~Regador() {}

bool Regador::usar(Posicao* pos) {
    if (capacidadeAgua >= Settings::Regador::dose) {
        pos->adicionarAgua(Settings::Regador::dose);
        capacidadeAgua -= Settings::Regador::dose;
        return false;
    }
    return true;
}

char Regador::getCaracter() const { return 'g'; }
std::string Regador::getTipo() const { return "Regador"; }
std::string Regador::getInfo() const { 
    return "Regador #" + std::to_string(numeroSerie) + 
           " (" + std::to_string(capacidadeAgua) + "/" + 
           std::to_string(Settings::Regador::capacidade) + ")";
}

int Regador::getCapacidade() const { return capacidadeAgua; }