#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta {
private:
    int quantidadeAdubo;

public:
    Adubo();
    ~Adubo() override;
    
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
    
    int getQuantidade() const;
};

#endif