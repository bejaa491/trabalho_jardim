#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"
#include "Settings.h"

class Roseira : public Planta {
public:
    Roseira();
    ~Roseira() override;
    
    void simular(int& aguaSolo, int& nutrientesSolo) override;
    bool deveMorrer() const override;
    Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    
    void deixarRecursosNoSolo(int& aguaSolo, int& nutrientesSolo);
    bool todasVizinhasOcupadas() const;
    void setJardimPtr(void* jardim);
    
private:
    void* jardimPtr; // Ponteiro para verificar vizinhos
};

#endif