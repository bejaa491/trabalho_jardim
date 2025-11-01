#ifndef CANTORA_H
#define CANTORA_H

#include "Planta.h"
#include "Settings.h"

// Forward declaration
class Posicao;

class Cantora : public Planta {
private:
    int instantesAoLadoDeBonita;

public:
    Cantora();
    ~Cantora() override;
    
    void simular(int& aguaSolo, int& nutrientesSolo) override;
    bool deveMorrer() const override;
    Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) override;
    char getCaracter() const override;
    std::string getTipo() const override;
    
    // Método especial para regenerar plantas bonitas
    void cantar(Posicao** area, int linha, int coluna, int maxLinhas, int maxColunas);
    
    // Verifica se está ao lado de planta bonita (não const porque incrementa contador)
    bool temPlantaBonitaVizinha(Posicao** area, int linha, int coluna, int maxLinhas, int maxColunas);
    
    // Incrementa contador de instantes ao lado de bonita
    void incrementarContadorBonita();
};

#endif