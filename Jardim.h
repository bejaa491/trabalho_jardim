/**
 * ============================================================================
 *  CLASSE: Jardim
 *  DESCRIÇÃO: Gerencia a simulação completa do jardim
 *  
 *  Responsabilidades:
 *    - Criação e manutenção da grelha (área) do jardim
 *    - Simulação de ciclos de vida das plantas (água, nutrientes, morte)
 *    - Gestão do jardineiro e suas ações (movimento, colheita, plantação)
 *    - Processamento de ferramentas e seus efeitos no jardim
 *    - Persistência: salvar e carregar estado do jardim
 * ============================================================================
 */
#ifndef JARDIM_H
#define JARDIM_H

#include "Posicao.h"
#include "Jardineiro.h"
#include <string>
#include <map>

class Jardim {
private:
    Posicao** area;                           /**< Matriz 2D de posições do jardim */
    int numLinhas;                            /**< Número de linhas da grelha */
    int numColunas;                           /**< Número de colunas da grelha */
    int instanteAtual;                        /**< Ciclo de simulação atual */
    Jardineiro* jardineiro;                   /**< Instância do jardineiro ativo */
    std::map<std::string, Jardim*> copiasSalvas; /**< Snapshots do estado para persistência */

public:
    Jardim();
    ~Jardim();
    
    // ========== INICIALIZAÇÃO ==========
    /**
     * Cria a grelha do jardim com as dimensões especificadas.
     * Inicializa o solo com água e nutrientes aleatórios.
     * Coloca ferramentas iniciais em posições aleatórias.
     * 
     * @param linhas    Número de linhas (1-26)
     * @param colunas   Número de colunas (1-26)
     * @return true se criação bem sucedida; false se já existe jardim
     * 
     * @note Deve ser invocado apenas uma vez por execução
     */
    bool criar(int linhas, int colunas);

    /**
     * Inicializa água e nutrientes do solo com valores pseudo-aleatórios.
     * Intervalo definido em Settings::Jardim (agua_min/max, nutrientes_min/max)
     */
    void inicializarSolo();

    /**
     * Coloca 3 ferramentas iniciais (Regador, Adubo, Tesoura, Pulverizador)
     * em posições aleatórias que não contêm plantas.
     */
    void colocarFerramentasIniciais();
    
    // ========== SIMULAÇÃO ==========
    /**
     * Avança a simulação um número de instantes.
     * Cada instante executa simularInstante().
     * 
     * @param instantes Número de ciclos a simular (padrão: 1)
     */
    void avancarTempo(int instantes = 1);
    
    /**
     * Simula um ciclo completo:
     *   1. Ações do jardineiro (ferramentas em mão)
     *   2. Simulação de plantas (absorção, morte, multiplicação)
     *   3. Regeneração de Cantoras
     *   4. Coleta de ferramentas no chão
     */
    void simularInstante();
    
    // ========== LISTAGEM E CONSULTA ==========
    /**
     * Lista todas as plantas do jardim com detalhes.
     */
    void listarPlantas() const;
    
    /**
     * Mostra detalhes de uma planta em posição específica.
     * 
     * @param linha Índice de linha (0-based)
     * @param coluna Índice de coluna (0-based)
     */
    void listarPlanta(int linha, int coluna) const;
    
    /**
     * Lista todas as posições que contêm plantas ou ferramentas.
     */
    void listarArea() const;
    
    /**
     * Mostra informações de solo (água, nutrientes) numa posição e raio.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @param raio Raio de visualização em volta da posição (padrão: 0)
     */
    void listarSolo(int linha, int coluna, int raio = 0) const;
    
    /**
     * Lista todas as ferramentas que o jardineiro possui.
     */
    void listarFerramentas() const;
    
    // ========== AÇÕES NO JARDIM ==========
    /**
     * Colhe uma planta na posição especificada.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return true se colheita bem sucedida
     */
    bool colherPlanta(int linha, int coluna);
    
    /**
     * Planta uma nova planta do tipo especificado.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @param tipo Tipo: 'c'=Cacto, 'r'=Roseira, 'e'=Erva, 'x'=Cantora
     * @return true se plantação bem sucedida
     */
    bool plantarPlanta(int linha, int coluna, char tipo);
    
    // ========== AÇÕES DO JARDINEIRO ==========
    /**
     * Move o jardineiro uma posição.
     * 
     * @param direcao 'e'=esquerda, 'd'=direita, 'c'=cima, 'b'=baixo
     * @return true se movimento bem sucedido
     */
    bool moverJardineiro(char direcao);
    
    /**
     * O jardineiro entra no jardim numa posição específica.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return true se entrada bem sucedida
     */
    bool jardineirosEntra(int linha, int coluna);
    
    /**
     * O jardineiro sai do jardim.
     * 
     * @return true se saída bem sucedida
     */
    bool jardineirosai();
    
    /**
     * Jardineiro pega uma ferramenta pelo número de série.
     * 
     * @param numeroSerie Identificador único da ferramenta
     * @return true se ação bem sucedida
     */
    bool jardineiroPega(int numeroSerie);
    
    /**
     * Jardineiro larga a ferramenta que tem na mão.
     * 
     * @return true se ação bem sucedida
     */
    bool jardineirolLarga();
    
    /**
     * Compra uma nova ferramenta do tipo especificado.
     * 
     * @param tipo 'g'=Regador, 'a'=Adubo, 't'=Tesoura, 'z'=Pulverizador
     * @return true se compra bem sucedida
     */
    bool comprarFerramenta(char tipo);
    
    // ========== PERSISTÊNCIA ==========
    /**
     * Salva o estado atual do jardim numa cópia (snapshot).
     * 
     * @param nome Identificador único da cópia
     * @return true se grava bem sucedida
     */
    bool gravarCopia(const std::string& nome);
    
    /**
     * Carrega o estado de uma cópia previamente gravada.
     * 
     * @param nome Identificador da cópia
     * @return true se recuperação bem sucedida
     */
    bool recuperarCopia(const std::string& nome);
    
    /**
     * Remove uma cópia gravada.
     * 
     * @param nome Identificador da cópia
     * @return true se apagamento bem sucedido
     */
    bool apagarCopia(const std::string& nome);
    
    // ========== VISUALIZAÇÃO ==========
    /**
     * Imprime a representação visual do jardim no stdout.
     * Mostra plantas (*), ferramentas (caracteres específicos), e jardineiro (J).
     */
    void imprimir() const;
    
    // ========== UTILIDADES ==========
    /**
     * Verifica se uma posição está dentro dos limites do jardim.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return true se (0 <= linha < numLinhas) e (0 <= coluna < numColunas)
     */
    bool posicaoValida(int linha, int coluna) const;
    
    /**
     * Obtém referência mutável a uma posição.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return Ponteiro a Posicao ou nullptr se inválida
     */
    Posicao* getPosicao(int linha, int coluna);
    
    /**
     * Obtém referência imutável a uma posição.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return Ponteiro const a Posicao ou nullptr se inválida
     */
    const Posicao* getPosicao(int linha, int coluna) const;
    
    /**
     * Define o estado de uma posição.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @param p Posição com novo estado
     */
    void setPosicao(int linha, int coluna, const Posicao& p);
    
    /**
     * Verifica se o jardim foi criado.
     * 
     * @return true se criar() foi invocado com sucesso
     */
    bool foiCriado() const;
    
    /**
     * Verifica se existe uma planta vizinha a uma posição.
     * Procura nas 4 direções (cima, baixo, esquerda, direita).
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     * @return true se existe planta vizinha
     */
    bool existePlantaVizinha(int linha, int coluna) const;
    
    /**
     * Adiciona uma nova planta numa posição vizinha aleatória (sem matar existente).
     * 
     * @param linhaOrigem Índice de linha da planta original
     * @param colunaOrigem Índice de coluna da planta original
     * @param novaPlanta Ponteiro a planta a adicionar
     * @return true se adição bem sucedida
     */
    bool adicionarPlantaVizinha(int linhaOrigem, int colunaOrigem, Planta* novaPlanta);
    
    /**
     * Adiciona uma nova planta matando existente (para ervas daninhas).
     * 
     * @param linhaOrigem Índice de linha da planta original
     * @param colunaOrigem Índice de coluna da planta original
     * @param novaPlanta Ponteiro a planta a adicionar
     * @return true se adição bem sucedida
     */
    bool adicionarPlantaVizinhaMatando(int linhaOrigem, int colunaOrigem, Planta* novaPlanta);
    
private:
    void liberarMemoria();
    char letraParaIndice(char letra) const;
    char indiceParaLetra(int indice) const;
    void colocarFerramentaAleatoria();
    Ferramenta* criarFerramentaAleatoria();
};

#endif