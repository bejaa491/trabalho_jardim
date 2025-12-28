#include "Erva.h"

Erva::Erva()
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             Beleza::FEIA),
      instantesDesdeUltimaMultiplicacao(0) {}

Erva::~Erva() {}

void Erva::simular(int& aguaSolo, int& nutrientesSolo) {
    int aguaAbsorvida = (aguaSolo >= Settings::ErvaDaninha::absorcao_agua)
                        ? Settings::ErvaDaninha::absorcao_agua : aguaSolo;
    int nutrientesAbsorvidos = (nutrientesSolo >= Settings::ErvaDaninha::absorcao_nutrientes)
                               ? Settings::ErvaDaninha::absorcao_nutrientes : nutrientesSolo;

    adicionarAgua(aguaAbsorvida);
    adicionarNutrientes(nutrientesAbsorvidos);
    aguaSolo -= aguaAbsorvida;
    nutrientesSolo -= nutrientesAbsorvidos;

    adicionarTotalAgua(aguaAbsorvida);
    adicionarTotalNutrientes(nutrientesAbsorvidos);

    instantesDesdeUltimaMultiplicacao++; 
}

bool Erva::deveMorrer() const {
    return getIdade() >= Settings::ErvaDaninha::morre_instantes;
}

Planta* Erva::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    if (getNutrientes() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        instantesDesdeUltimaMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes) {

        Erva* novaErva = new Erva();
        setNutrientes(Settings::ErvaDaninha::original_nutrientes);
        instantesDesdeUltimaMultiplicacao = 0;

        return novaErva;
        }
    return nullptr;
}

char Erva::getCaracter() const { return 'e'; }
std::string Erva::getTipo() const { return "Erva Daninha"; }

Planta* Erva::clone() const {
    Erva* e = new Erva();
    e->setAgua(getAgua());
    e->setNutrientes(getNutrientes());
    for (int k = 0; k < getIdade(); ++k) e->incrementaIdade();
    e->setTotalNutrientes(getTotalNutrientes());
    e->setTotalAgua(getTotalAgua());
    e->setPosicao(getLinha(), getColuna());
    return e;
} 