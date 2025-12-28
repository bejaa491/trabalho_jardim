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

void Planta::setTotalNutrientes(int v) {
    totalNutrientesAbsorvidos = v;
}

void Planta::setTotalAgua(int v) {
    totalAguaAbsorvida = v;
}

// Adiciona/Remove recursos de forma segura
void Planta::adicionarAgua(int quantidade) {
    aguaAcumulada += quantidade;
    if (aguaAcumulada < 0) aguaAcumulada = 0;
}

void Planta::removerAgua(int quantidade) {
    adicionarAgua(-quantidade);
}

void Planta::adicionarNutrientes(int quantidade) {
    nutrientesAcumulados += quantidade;
    if (nutrientesAcumulados < 0) nutrientesAcumulados = 0;
}

void Planta::removerNutrientes(int quantidade) {
    adicionarNutrientes(-quantidade);
}

void Planta::adicionarTotalAgua(int quantidade) {
    totalAguaAbsorvida += quantidade;
    if (totalAguaAbsorvida < 0) totalAguaAbsorvida = 0;
}

void Planta::adicionarTotalNutrientes(int quantidade) {
    totalNutrientesAbsorvidos += quantidade;
    if (totalNutrientesAbsorvidos < 0) totalNutrientesAbsorvidos = 0;
} 