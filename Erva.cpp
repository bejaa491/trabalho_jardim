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

    aguaAcumulada += aguaAbsorvida;
    nutrientesAcumulados += nutrientesAbsorvidos;
    aguaSolo -= aguaAbsorvida;
    nutrientesSolo -= nutrientesAbsorvidos;

    totalAguaAbsorvida += aguaAbsorvida;
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;

    instantesDesdeUltimaMultiplicacao++;
}

bool Erva::deveMorrer() const {
    return idade >= Settings::ErvaDaninha::morre_instantes;
}

Planta* Erva::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    if (nutrientesAcumulados > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        instantesDesdeUltimaMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes) {

        Erva* novaErva = new Erva();
        nutrientesAcumulados = Settings::ErvaDaninha::original_nutrientes;
        instantesDesdeUltimaMultiplicacao = 0;

        return novaErva;
        }
    return nullptr;
}

char Erva::getCaracter() const { return 'e'; }
std::string Erva::getTipo() const { return "Erva Daninha"; }