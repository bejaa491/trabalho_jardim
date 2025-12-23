#include "Ferramenta.h"
#include <algorithm>

int Ferramenta::contadorSerie = 1;

Ferramenta::Ferramenta() {
    numeroSerie = contadorSerie++;
}

Ferramenta::~Ferramenta() {}

int Ferramenta::getNumeroSerie() const {
    return numeroSerie;
}

void Ferramenta::setNumeroSerie(int n) {
    numeroSerie = n;
    ajustarContadorSeNecessario(n);
}

void Ferramenta::ajustarContadorSeNecessario(int n) {
    if (contadorSerie <= n) contadorSerie = n + 1;
}