#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"

class Regador : public Ferramenta {
private:
    int capacidadeAgua;

public:
    Regador();
    ~Regador() override;
    
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
    
    int getCapacidade() const;
};

#endif