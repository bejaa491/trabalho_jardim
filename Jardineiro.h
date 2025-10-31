#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include "Ferramenta.h"

class Jardineiro {
private:
    int linha;
    int coluna;
    bool noJardim;
    Ferramenta** ferramentas;    // array de ponteiros para ferramentas
    int numFerramentas;          // numero actual de ferramentas
    int capacidadeFerramentas;   // capacidade alocada

    Ferramenta* ferramentaNaMao;
    
    // Contadores por turno
    int movimentosRestantes;
    int plantasColhidasNoTurno;
    int plantasPlantadasNoTurno;
    int entradasNoTurno;
    int saidasNoTurno;

    // Helpers internos para gerir array dinamico
    bool garantirCapacidade(int novaCapacidade);

public:
    Jardineiro();
    ~Jardineiro();
    
    // Movimento
    bool mover(int deltaLinha, int deltaColuna, int maxLinhas, int maxColunas);
    bool entrar(int l, int c, int maxLinhas, int maxColunas);
    bool sair();
    
    // Ferramentas
    void adicionarFerramenta(Ferramenta* f); // adiciona (passa a propriedade)
    bool pegarFerramenta(int numeroSerie);
    Ferramenta* largarFerramenta();
    bool usarFerramentaNaMao(Posicao* pos);
    
    // Acesso às ferramentas (sem std::vector): devolve apontador para array interno
    // e numero via getNumFerramentas()
    Ferramenta** getFerramentas() const;
    int getNumFerramentas() const;

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
    int getMovimentosRestantes() const;
};

#endif