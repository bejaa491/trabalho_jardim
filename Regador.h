#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"

class Regador : public Ferramenta {
private:
    int capacidadeAgua;

public:
    Regador();
    // Construtor para clonagem com estado
    Regador(int capacidade, int numeroSerie);
    ~Regador() override;
    
    Ferramenta* clone() const override;
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
    
    int getCapacidade() const;
};

#endif