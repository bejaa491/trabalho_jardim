#include "Roseira.h"

Roseira::Roseira() 
    : Planta(Settings::Roseira::inicial_agua, 
             Settings::Roseira::inicial_nutrientes, 
             Beleza::BONITA),
      jardimPtr(nullptr) {}

Roseira::~Roseira() {}

void Roseira::simular(int& aguaSolo, int& nutrientesSolo) {
    aguaAcumulada -= Settings::Roseira::perda_agua;
    nutrientesAcumulados -= Settings::Roseira::perda_nutrientes;
    
    int aguaAbsorvida = (aguaSolo >= Settings::Roseira::absorcao_agua) 
                        ? Settings::Roseira::absorcao_agua : aguaSolo;
    int nutrientesAbsorvidos = (nutrientesSolo >= Settings::Roseira::absorcao_nutrientes)
                               ? Settings::Roseira::absorcao_nutrientes : nutrientesSolo;
    
    aguaAcumulada += aguaAbsorvida;
    nutrientesAcumulados += nutrientesAbsorvidos;
    aguaSolo -= aguaAbsorvida;
    nutrientesSolo -= nutrientesAbsorvidos;
    
    totalAguaAbsorvida += aguaAbsorvida;
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;
}

bool Roseira::deveMorrer() const {
    return aguaAcumulada < Settings::Roseira::morre_agua_menor ||
           nutrientesAcumulados < Settings::Roseira::morre_nutrientes_menor ||
           nutrientesAcumulados > Settings::Roseira::morre_nutrientes_maior;
}

Planta* Roseira::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    if (nutrientesAcumulados > Settings::Roseira::multiplica_nutrientes_maior) {
        Roseira* novaRoseira = new Roseira();
        
        novaRoseira->setNutrientes(Settings::Roseira::nova_nutrientes);
        novaRoseira->setAgua(aguaAcumulada * Settings::Roseira::nova_agua_percentagem / 100);
        
        nutrientesAcumulados = Settings::Roseira::original_nutrientes;
        aguaAcumulada = aguaAcumulada * Settings::Roseira::original_agua_percentagem / 100;
        
        return novaRoseira;
    }
    return nullptr;
}

char Roseira::getCaracter() const { return 'r'; }
std::string Roseira::getTipo() const { return "Roseira"; }