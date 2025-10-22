#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include "Ferramenta.h"

class Jardineiro {
private:
    int linha;
    int coluna;
    bool noJardim;
    
    std::vector<Ferramenta*> ferramentas;
    Ferramenta* ferramentaNaMao;
    
    // Contadores por turno
    int movimentosRestantes;
    int plantasColhidasNoTurno;
    int plantasPlantadasNoTurno;
    int entradasNoTurno;
    int saidasNoTurno;

public:
    Jardineiro();
    ~Jardineiro();
    
    // Movimento
    bool mover(int deltaLinha, int deltaColuna, int maxLinhas, int maxColunas);
    bool entrar(int l, int c, int maxLinhas, int maxColunas);
    bool sair();
    
    // Ferramentas
    void adicionarFerramenta(Ferramenta* f);
    bool pegarFerramenta(int numeroSerie);
    Ferramenta* largarFerramenta();
    void usarFerramentaNaMao(Posicao* pos);
    
    // Ações
    bool podeColher() const;
    bool podePlantar() const;
    bool podeMover() const;
    bool podeEntrar() const;
    bool podeSair() const;
    
    void registarColheita();
    void registarPlantacao();
    
    // Reset por turno
    void novoTurno();
    
    // Getters
    int getLinha() const;
    int getColuna() const;
    bool estaNoJardim() const;
    Ferramenta* getFerramentaNaMao() const;
    const std::vector<Ferramenta*>& getFerramentas() const;
    int getMovimentosRestantes() const;
};

#endif