#ifndef ERVA_H
#define ERVA_H

#include "Planta.h"
#include "Settings.h"

class Erva : public Planta {
private:
    int instantesDesdeUltimaMultiplicacao;

public:
    Erva();
    ~Erva() override;
    
    void simular(int& aguaSolo, int& nutrientesSolo) override;
    bool deveMorrer() const override;
    Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) override;
    char getCaracter() const override;
    std::string getTipo() const override;

    Planta* clone() const override;
};

#endif