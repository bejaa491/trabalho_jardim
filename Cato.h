#ifndef CATO_H
#define CATO_H

#include "Planta.h"
#include "Settings.h"

class Cato : public Planta {
private:
    int instantesAguaAlta;
    int instantesNutrientesZero;

public:
    Cato();
    ~Cato() override;
    
    void simular(int& aguaSolo, int& nutrientesSolo) override;
    bool deveMorrer() const override;
    Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    
    void deixarNutrientesNoSolo(int& nutrientesSolo);
};

#endif