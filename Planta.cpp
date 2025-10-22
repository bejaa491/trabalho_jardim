#include "Planta.h"

Planta::Planta(int agua, int nutrientes, Beleza bel)
    : aguaAcumulada(agua), nutrientesAcumulados(nutrientes), 
      beleza(bel), idade(0), linhaPos(-1), colunaPos(-1),
      totalNutrientesAbsorvidos(0), totalAguaAbsorvida(0) {
}

Planta::~Planta() {
}

void Planta::incrementaIdade() {
    idade++;
}

void Planta::setPosicao(int linha, int coluna) {
    linhaPos = linha;
    colunaPos = coluna;
}

int Planta::getAgua() const {
    return aguaAcumulada;
}

int Planta::getNutrientes() const {
    return nutrientesAcumulados;
}

int Planta::getIdade() const {
    return idade;
}

Beleza Planta::getBeleza() const {
    return beleza;
}

int Planta::getLinha() const {
    return linhaPos;
}

int Planta::getColuna() const {
    return colunaPos;
}

int Planta::getTotalNutrientes() const {
    return totalNutrientesAbsorvidos;
}

int Planta::getTotalAgua() const {
    return totalAguaAbsorvida;
}

void Planta::setAgua(int valor) {
    aguaAcumulada = valor;
}

void Planta::setNutrientes(int valor) {
    nutrientesAcumulados = valor;
}