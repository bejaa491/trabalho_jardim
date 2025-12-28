#include "Cato.h"

Cato::Cato()
    : Planta(0, 0, Beleza::NEUTRA),
      instantesAguaAlta(0),
      instantesNutrientesZero(0) {
}

Cato::~Cato() {
}

void Cato::simular(int& aguaSolo, int& nutrientesSolo) {
    // Absorve 25% da água do solo
    int aguaAbsorvida = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) / 100;
    adicionarAgua(aguaAbsorvida);
    aguaSolo -= aguaAbsorvida;
    adicionarTotalAgua(aguaAbsorvida);

    // Absorve até 5 unidades de nutrientes
    int nutrientesAbsorvidos = (nutrientesSolo >= Settings::Cacto::absorcao_nutrientes)
                                ? Settings::Cacto::absorcao_nutrientes
                                : nutrientesSolo;
    adicionarNutrientes(nutrientesAbsorvidos);
    nutrientesSolo -= nutrientesAbsorvidos;
    adicionarTotalNutrientes(nutrientesAbsorvidos);

    // Verificar condições de morte
    if (aguaSolo > Settings::Cacto::morre_agua_solo_maior) {
        instantesAguaAlta++;
    } else {
        instantesAguaAlta = 0;
    }

    if (nutrientesSolo < Settings::Cacto::morre_nutrientes_solo_menor) {
        instantesNutrientesZero++;
    } else {
        instantesNutrientesZero = 0;
    }
}

bool Cato::deveMorrer() const {
    // Morre se água alta por 3 instantes seguidos
    if (instantesAguaAlta > Settings::Cacto::morre_agua_solo_instantes) {
        return true;
    }

    // Morre se nutrientes baixos por mais de 3 instantes
    if (instantesNutrientesZero > Settings::Cacto::morre_nutrientes_solo_instantes) {
        return true;
    }

    return false;
}

Planta* Cato::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    // Multiplica se nutrientes > 100 e água > 50
    if (getNutrientes() > Settings::Cacto::multiplica_nutrientes_maior &&
        getAgua() > Settings::Cacto::multiplica_agua_maior) {

        // Criar novo cacto
        Cato* novoCacto = new Cato();

        // Dividir recursos em partes iguais
        novoCacto->setAgua(getAgua() / 2);
        novoCacto->setNutrientes(getNutrientes() / 2);

        setAgua(getAgua() / 2);
        setNutrientes(getNutrientes() / 2);

        return novoCacto;
    }

    return nullptr;
} 

char Cato::getCaracter() const {
    return 'c';
}

std::string Cato::getTipo() const {
    return "Cacto";
}

Planta* Cato::clone() const {
    Cato* c = new Cato();
    c->setAgua(getAgua());
    c->setNutrientes(getNutrientes());
    for (int k = 0; k < getIdade(); ++k) c->incrementaIdade();
    c->setTotalNutrientes(getTotalNutrientes());
    c->setTotalAgua(getTotalAgua());
    c->setPosicao(getLinha(), getColuna());
    return c;
} 

void Cato::deixarNutrientesNoSolo(int& nutrientesSolo) {
    // Ao morrer, deixa todos os nutrientes absorvidos
    nutrientesSolo += getTotalNutrientes();
} 