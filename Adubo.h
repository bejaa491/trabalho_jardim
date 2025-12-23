#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta {
private:
    int quantidadeAdubo;

public:
    Adubo();
    // Construtor para clonagem
    Adubo(int quantidade, int numeroSerie);
    ~Adubo() override;
    
    Ferramenta* clone() const override;
    bool usar(Posicao* pos) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    std::string getInfo() const override;
    
    int getQuantidade() const;
};

#endif