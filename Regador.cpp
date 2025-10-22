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

char Regador::getCaracter() const { return 'R'; }
std::string Regador::getTipo() const { return "Regador"; }
std::string Regador::getInfo() const { 
    return "Regador #" + std::to_string(numeroSerie) + 
           " (" + std::to_string(capacidadeAgua) + "/" + 
           std::to_string(Settings::Regador::capacidade) + ")";
}

int Regador::getCapacidade() const { return capacidadeAgua; }

// ========== Adubo.cpp ==========
#include "Adubo.h"
#include "Posicao.h"
#include "Settings.h"

Adubo::Adubo() : quantidadeAdubo(Settings::Adubo::capacidade) {}
Adubo::~Adubo() {}

bool Adubo::usar(Posicao* pos) {
    if (quantidadeAdubo >= Settings::Adubo::dose) {
        pos->adicionarNutrientes(Settings::Adubo::dose);
        quantidadeAdubo -= Settings::Adubo::dose;
        return false;
    }
    return true;
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