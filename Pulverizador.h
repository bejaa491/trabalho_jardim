#ifndef PULVERIZADOR_H
#define PULVERIZADOR_H

#include "Ferramenta.h"

class Pulverizador : public Ferramenta {
private:
    int eficacia; // 0-100

public:
    Pulverizador();
    ~Pulverizador() override;
    
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
    
    void degradar(); // Chamado pelo jardineiro a cada instante
    int getEficacia() const;
    bool estaGasto() const;
};

#endif