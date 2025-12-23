#ifndef TESOURA_H
#define TESOURA_H

#include "Ferramenta.h"

class Tesoura : public Ferramenta {
public:
    Tesoura();
    ~Tesoura() override;
    
    Ferramenta* clone() const override;
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
};

#endif