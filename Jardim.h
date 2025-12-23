#ifndef JARDIM_H
#define JARDIM_H

#include "Posicao.h"
#include "Jardineiro.h"
#include <string>
#include <map>

class Jardim {
private:
    Posicao** area;
    int numLinhas;
    int numColunas;
    int instanteAtual;
    Jardineiro* jardineiro;
    
    std::map<std::string, Jardim*> copiasSalvas;

public:
    Jardim();
    ~Jardim();
    
    // Inicialização
    // Cria a grelha do jardim com as dimensões especificadas e inicializa o solo.
    // Retorna true se a criação for bem sucedida (invocar apenas uma vez por execução).
    bool criar(int linhas, int colunas);

    // Inicializa água e nutrientes do solo com valores pseudo-aleatórios no intervalo definido
    // em `Settings::Jardim`.
    void inicializarSolo();

    // Coloca algumas ferramentas iniciais em posições aleatórias do jardim.
    void colocarFerramentasIniciais();
    
    // Simulação
    void avancarTempo(int instantes = 1);
    void simularInstante();
    
    // Comandos de listagem
    void listarPlantas() const;
    void listarPlanta(int linha, int coluna) const;
    void listarArea() const;
    void listarSolo(int linha, int coluna, int raio = 0) const;
    void listarFerramentas() const;
    
    // Comandos de ação
    bool colherPlanta(int linha, int coluna);
    bool plantarPlanta(int linha, int coluna, char tipo);
    
    // Comandos do jardineiro
    bool moverJardineiro(char direcao);
    bool jardineirosEntra(int linha, int coluna);
    bool jardineirosai();
    bool jardineiroPega(int numeroSerie);
    bool jardineirolLarga();
    bool comprarFerramenta(char tipo);
    
    // Gestão de cópias
    bool gravarCopia(const std::string& nome);
    bool recuperarCopia(const std::string& nome);
    bool apagarCopia(const std::string& nome);
    
    // Visualização
    void imprimir() const;
    
    // Utilidades
    bool posicaoValida(int linha, int coluna) const;
    Posicao* getPosicao(int linha, int coluna);
    const Posicao* getPosicao(int linha, int coluna) const;
    void setPosicao(int linha, int coluna, const Posicao& p);
    bool foiCriado() const;
    
    // Para multiplicação de plantas
    bool existePlantaVizinha(int linha, int coluna) const;
    bool adicionarPlantaVizinha(int linhaOrigem, int colunaOrigem, Planta* novaPlanta);
    bool adicionarPlantaVizinhaMatando(int linhaOrigem, int colunaOrigem, Planta* novaPlanta);
    
private:
    void liberarMemoria();
    char letraParaIndice(char letra) const;
    char indiceParaLetra(int indice) const;
    void colocarFerramentaAleatoria();
    Ferramenta* criarFerramentaAleatoria();
};

#endif