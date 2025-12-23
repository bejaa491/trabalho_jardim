#include "Tesoura.h"
#include "Posicao.h"
#include "Planta.h"

Tesoura::Tesoura() {}
Tesoura::~Tesoura() {}

Ferramenta* Tesoura::clone() const {
    Tesoura* t = new Tesoura();
    t->setNumeroSerie(numeroSerie);
    return t;
}

bool Tesoura::usar(Posicao* pos) {
    Planta* p = pos->getPlanta();
    if (p != nullptr && p->getBeleza() == Beleza::FEIA) {
        delete p;
        pos->removerPlanta();
    }
    return false;
}

char Tesoura::getCaracter() const { return 't'; }
std::string Tesoura::getTipo() const { return "Tesoura"; }
std::string Tesoura::getInfo() const { 
    return "Tesoura #" + std::to_string(numeroSerie);
}