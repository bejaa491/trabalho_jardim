#include "Ferramenta.h"

int Ferramenta::contadorSerie = 1;

Ferramenta::Ferramenta() {
    numeroSerie = contadorSerie++;
}

Ferramenta::~Ferramenta() {}

int Ferramenta::getNumeroSerie() const {
    return numeroSerie;
}