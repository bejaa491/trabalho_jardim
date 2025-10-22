#include "Posicao.h"
#include "Planta.h"
#include "Ferramenta.h"

Posicao::Posicao() : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {}

Posicao::Posicao(int aguaInicial, int nutrientesInicial) 
    : agua(aguaInicial), nutrientes(nutrientesInicial), planta(nullptr), ferramenta(nullptr) {}

Posicao::~Posicao() {
    delete planta;
    delete ferramenta;
}

int Posicao::getAgua() const { return agua; }
int Posicao::getNutrientes() const { return nutrientes; }
Planta* Posicao::getPlanta() const { return planta; }
Ferramenta* Posicao::getFerramenta() const { return ferramenta; }

bool Posicao::estaVazia() const {
    return planta == nullptr && ferramenta == nullptr;
}

bool Posicao::temPlanta() const { return planta != nullptr; }
bool Posicao::temFerramenta() const { return ferramenta != nullptr; }

void Posicao::setAgua(int valor) { agua = valor; }
void Posicao::setNutrientes(int valor) { nutrientes = valor; }

void Posicao::adicionarAgua(int quantidade) { agua += quantidade; }
void Posicao::adicionarNutrientes(int quantidade) { nutrientes += quantidade; }

void Posicao::removerAgua(int quantidade) { 
    agua -= quantidade; 
    if (agua < 0) agua = 0;
}

void Posicao::removerNutrientes(int quantidade) { 
    nutrientes -= quantidade; 
    if (nutrientes < 0) nutrientes = 0;
}

bool Posicao::adicionarPlanta(Planta* p) {
    if (planta != nullptr) return false;
    planta = p;
    return true;
}

Planta* Posicao::removerPlanta() {
    Planta* temp = planta;
    planta = nullptr;
    return temp;
}

bool Posicao::adicionarFerramenta(Ferramenta* f) {
    if (ferramenta != nullptr) return false;
    ferramenta = f;
    return true;
}

Ferramenta* Posicao::removerFerramenta() {
    Ferramenta* temp = ferramenta;
    ferramenta = nullptr;
    return temp;
}

char Posicao::getCaracterVisivel(bool jardineirosPresente) const {
    if (jardineirosPresente) return 'J';
    if (planta != nullptr) return planta->getCaracter();
    if (ferramenta != nullptr) return ferramenta->getCaracter();
    return '.';
}