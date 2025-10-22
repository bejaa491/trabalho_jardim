#include "Tesoura.h"
#include "Posicao.h"
#include "Planta.h"

Tesoura::Tesoura() {}
Tesoura::~Tesoura() {}

bool Tesoura::usar(Posicao* pos) {
    Planta* p = pos->getPlanta();
    if (p != nullptr) {
        delete p;
        pos->removerPlanta();
    }
    return false;
}

char Tesoura::getCaracter() const { return 'T'; }
std::string Tesoura::getTipo() const { return "Tesoura"; }
std::string Tesoura::getInfo() const { 
    return "Tesoura #" + std::to_string(numeroSerie);
}