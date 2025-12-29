/**
 * ============================================================================
 *  CLASSE: Jardineiro
 *  DESCRIÇÃO: Representa o jardineiro que trabalha no jardim
 *  
 *  Responsabilidades:
 *    - Movimento dentro do jardim (4 direções)
 *    - Entrada e saída do jardim
 *    - Gestão de ferramentas (adicionar, pegar, largar, usar)
 *    - Limitações por turno (movimentos, plantações, colheitas)
 *    - Uso de ferramentas na mão durante simulação
 * ============================================================================
 */
#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include "Ferramenta.h"

class Jardineiro {
private:
    int linha;                          /**< Posição linha do jardineiro */
    int coluna;                         /**< Posição coluna do jardineiro */
    bool noJardim;                      /**< true se jardineiro está dentro do jardim */
    Ferramenta** ferramentas;           /**< Array dinâmico de ferramentas possuídas */
    int numFerramentas;                 /**< Número atual de ferramentas */
    int capacidadeFerramentas;          /**< Capacidade alocada do array */

    Ferramenta* ferramentaNaMao;        /**< Ferramenta que o jardineiro segura (nullptr se vazio) */
    
    // ========== LIMITAÇÕES POR TURNO ==========
    int movimentosRestantes;            /**< Movimentos ainda disponíveis este turno */
    int plantasColhidasNoTurno;         /**< Plantas colhidas neste turno */
    int plantasPlantadasNoTurno;        /**< Plantas plantadas neste turno */
    int entradasNoTurno;                /**< Entradas no jardim neste turno */
    int saidasNoTurno;                  /**< Saídas do jardim neste turno */

    /**
     * Garante espaço suficiente no array de ferramentas.
     * Realoca se necessário.
     * 
     * @param novaCapacidade Capacidade mínima necessária
     * @return true se sucesso
     */
    bool garantirCapacidade(int novaCapacidade);

public:
    Jardineiro();
    ~Jardineiro();
    
    // ========== MOVIMENTO ==========
    /**
     * Move o jardineiro dentro do jardim.
     * Gasta um movimento do turno.
     * 
     * @param deltaLinha Deslocamento em linha (-1, 0, 1)
     * @param deltaColuna Deslocamento em coluna (-1, 0, 1)
     * @param maxLinhas Número máximo de linhas do jardim
     * @param maxColunas Número máximo de colunas do jardim
     * @return true se movimento bem sucedido
     */
    bool mover(int deltaLinha, int deltaColuna, int maxLinhas, int maxColunas);
    
    /**
     * Jardineiro entra no jardim numa posição específica.
     * Gasta uma entrada do turno.
     * 
     * @param l Linha de entrada
     * @param c Coluna de entrada
     * @param maxLinhas Número máximo de linhas do jardim
     * @param maxColunas Número máximo de colunas do jardim
     * @return true se entrada bem sucedida
     */
    bool entrar(int l, int c, int maxLinhas, int maxColunas);
    
    /**
     * Jardineiro sai do jardim.
     * Gasta uma saída do turno.
     * 
     * @return true se saída bem sucedida
     */
    bool sair();
    
    // ========== GESTÃO DE FERRAMENTAS ==========
    /**
     * Adiciona uma ferramenta ao inventário.
     * O jardineiro assume propriedade do objeto.
     * 
     * @param f Ponteiro a ferramenta (não nullptr)
     */
    void adicionarFerramenta(Ferramenta* f);
    
    /**
     * Pega numa ferramenta pelo número de série e coloca na mão.
     * Solta a ferramenta anterior, se houver.
     * 
     * @param numeroSerie Identificador da ferramenta a pegar
     * @return true se sucesso
     */
    bool pegarFerramenta(int numeroSerie);
    
    /**
     * Larga a ferramenta que está na mão.
     * 
     * @return Ponteiro a ferramenta largada (caller assume propriedade)
     */
    Ferramenta* largarFerramenta();
    
    /**
     * Usa a ferramenta que está na mão numa posição.
     * 
     * @param pos Posição onde usar
     * @return true se ferramenta deve ser destruída
     */
    bool usarFerramentaNaMao(Posicao* pos);
    
    /**
     * Define a ferramenta que o jardineiro tem na mão.
     * Assume propriedade do objeto f (apaga anterior se existir).
     * Usado por Jardim::recuperarCopia para restaurar snapshots.
     * 
     * @param f Ponteiro a ferramenta (pode ser nullptr)
     */
    void setFerramentaNaMao(Ferramenta* f);

    /**
     * Obtém array de ferramentas do inventário.
     * 
     * @return Ponteiro a array interno (não fazer delete!)
     */
    Ferramenta** getFerramentas() const;
    
    /**
     * @return Número de ferramentas no inventário
     */
    int getNumFerramentas() const;

    // ========== VERIFICAÇÃO DE PERMISSÕES ==========
    /**
     * Verifica se jardineiro pode colher neste turno.
     * Limite: Settings::Jardineiro::max_colheitas
     * 
     * @return true se ainda há colheitas disponíveis
     */
    bool podeColher() const;
    
    /**
     * Verifica se jardineiro pode plantar neste turno.
     * Limite: Settings::Jardineiro::max_plantacoes
     * 
     * @return true se ainda há plantações disponíveis
     */
    bool podePlantar() const;
    
    /**
     * Verifica se jardineiro pode mover-se neste turno.
     * Limite: Settings::Jardineiro::max_movimentos
     * 
     * @return true se ainda há movimentos disponíveis
     */
    bool podeMover() const;
    
    /**
     * Verifica se jardineiro pode entrar neste turno.
     * Limite: Settings::Jardineiro::max_entradas_saidas
     * 
     * @return true se pode entrar
     */
    bool podeEntrar() const;
    
    /**
     * Verifica se jardineiro pode sair neste turno.
     * Limite: Settings::Jardineiro::max_entradas_saidas
     * 
     * @return true se pode sair
     */
    bool podeSair() const;
    
    /**
     * Registra uma colheita realizada.
     */
    void registarColheita();
    
    /**
     * Registra uma plantação realizada.
     */
    void registarPlantacao();
    
    /**
     * Reset das limitações por turno.
     * Chamado pelo Jardim::simularInstante() no início de cada ciclo.
     */
    void novoTurno();
    
    // ========== GETTERS ==========
    /**
     * @return Linha atual do jardineiro
     */
    int getLinha() const;
    
    /**
     * @return Coluna atual do jardineiro
     */
    int getColuna() const;
    
    /**
     * @return true se jardineiro está dentro do jardim
     */
    bool estaNoJardim() const;
    
    /**
     * @return Ferramenta na mão ou nullptr se vazio
     */
    Ferramenta* getFerramentaNaMao() const;
    
    /**
     * @return Movimentos ainda disponíveis neste turno
     */
    int getMovimentosRestantes() const;
};

#endif