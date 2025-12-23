#include "Pulverizador.h"
#include "Posicao.h"
#include "Planta.h"
#include "Erva.h"

Pulverizador::Pulverizador() : eficacia(100) {}

Pulverizador::Pulverizador(int eficaciaInicial, int numeroSerie) : eficacia(eficaciaInicial) {
    setNumeroSerie(numeroSerie);
}

Pulverizador::~Pulverizador() {}

Ferramenta* Pulverizador::clone() const {
    Pulverizador* p = new Pulverizador(eficacia, numeroSerie);
    return p;
}

bool Pulverizador::usar(Posicao* pos) {
    // O uso real é feito pelo Jardim que tem acesso às posições vizinhas
    // Esta ferramenta precisa de acesso especial no Jardim::simularInstante()
    // ou através de um método especial em Jardineiro
    return estaGasto();
}

void Pulverizador::degradar() {
    eficacia -= 10;
    if (eficacia < 0) eficacia = 0;
}

bool Pulverizador::estaGasto() const {
    return eficacia <= 0;
}

char Pulverizador::getCaracter() const { 
    return 'z'; 
}

std::string Pulverizador::getTipo() const { 
    return "Pulverizador"; 
}

std::string Pulverizador::getInfo() const {
    return "Pulverizador #" + std::to_string(numeroSerie) + 
           " (eficacia: " + std::to_string(eficacia) + "%)";
}

int Pulverizador::getEficacia() const {
    return eficacia;
}