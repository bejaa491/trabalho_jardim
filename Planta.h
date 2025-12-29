/**
 * ============================================================================
 *  CLASSE: Planta (Classe Base Abstrata)
 *  DESCRIÇÃO: Abstração de uma planta no jardim
 *  
 *  Responsabilidades:
 *    - Armazenar estado (água, nutrientes, idade, beleza, posição)
 *    - Definir interface virtual para simulação de ciclo de vida
 *    - Permitir clonagem para multiplicação
 * 
 *  Subclasses Concretas:
 *    - Roseira: planta bonita, depende de água e nutrientes
 *    - Cacto: planta resiliente, absorve muita água
 *    - Erva: planta selvagem, mata vizinhas e multiplica-se rapidamente
 *    - Cantora: planta especial, regenera plantas bonitas e canta
 * ============================================================================
 */
#ifndef PLANTA_H
#define PLANTA_H

#include <string>

/**
 * @enum Beleza
 * @brief Atributo visual e funcional de uma planta
 */
enum class Beleza {
    FEIA,     /**< Planta feia (ex: Erva) */
    NEUTRA,   /**< Planta neutra visualmente (ex: Cacto) */
    BONITA    /**< Planta bonita (ex: Roseira, Cantora) */
};

class Planta {
private:
    int aguaAcumulada;                /**< Quantidade de água que a planta contém */
    int nutrientesAcumulados;         /**< Quantidade de nutrientes que a planta contém */
    int idade;                        /**< Número de ciclos desde criação */
    Beleza beleza;                    /**< Classificação visual da planta */
    int linhaPos;                     /**< Linha atual no jardim */
    int colunaPos;                    /**< Coluna atual no jardim */
    int totalNutrientesAbsorvidos;    /**< Estatística: total absorvido até agora */
    int totalAguaAbsorvida;           /**< Estatística: total de água absorvida */

public:
    // ========== CONSTRUTORES ==========
    /**
     * Construtor protegido (chamado por subclasses).
     * 
     * @param agua Água inicial da planta
     * @param nutrientes Nutrientes iniciais da planta
     * @param bel Nível de beleza
     */
    Planta(int agua, int nutrientes, Beleza bel);
    virtual ~Planta();
    
    // ========== INTERFACE VIRTUAL (implementada por subclasses) ==========
    /**
     * Simula um ciclo de vida: absorve recursos, perde água/nutrientes.
     * Modifica aguaSolo e nutrientesSolo por referência.
     * 
     * @param aguaSolo [in/out] Água disponível no solo
     * @param nutrientesSolo [in/out] Nutrientes disponíveis no solo
     */
    virtual void simular(int& aguaSolo, int& nutrientesSolo) = 0;
    
    /**
     * Determina se a planta deve morrer neste ciclo.
     * Critérios variam por tipo (água/nutrientes insuficientes, idade, etc).
     * 
     * @return true se deve ser removida do jardim
     */
    virtual bool deveMorrer() const = 0;
    
    /**
     * Tenta multiplicar-se se condições são favoráveis.
     * Consome recursos do solo se bem sucedido.
     * 
     * @param aguaSolo [in/out] Água disponível no solo
     * @param nutrientesSolo [in/out] Nutrientes disponíveis no solo
     * @return Ponteiro a nova planta se sucesso; nullptr caso contrário
     */
    virtual Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) = 0;
    
    /**
     * Retorna o caractere que representa esta planta no mapa visual.
     * Exemplos: '*' genérica, 'r' Roseira, 'c' Cacto, 'e' Erva, 'x' Cantora
     * 
     * @return Caractere ASCII
     */
    virtual char getCaracter() const = 0;
    
    /**
     * Retorna o nome do tipo de planta.
     * 
     * @return String descritiva (ex: "Roseira", "Cacto", "Erva", "Cantora")
     */
    virtual std::string getTipo() const = 0;

    /**
     * Clona esta planta criando uma cópia profunda.
     * Copia água, nutrientes, idade, posição e estatísticas.
     * O chamador assume propriedade do novo objeto.
     * 
     * @return Novo objeto Planta* alocado com 'new'
     */
    virtual Planta* clone() const = 0;
    
    // ========== MUTADORES DE RECURSOS ==========
    /**
     * Aumenta água da planta.
     * 
     * @param quantidade Água a adicionar
     */
    void adicionarAgua(int quantidade);
    
    /**
     * Diminui água da planta (não fica negativa).
     * 
     * @param quantidade Água a remover
     */
    void removerAgua(int quantidade);
    
    /**
     * Aumenta nutrientes da planta.
     * 
     * @param quantidade Nutrientes a adicionar
     */
    void adicionarNutrientes(int quantidade);
    
    /**
     * Diminui nutrientes da planta (não fica negativa).
     * 
     * @param quantidade Nutrientes a remover
     */
    void removerNutrientes(int quantidade);
    
    /**
     * Atualiza estatística de total de água absorvida.
     * 
     * @param quantidade Água absorvida neste ciclo
     */
    void adicionarTotalAgua(int quantidade);
    
    /**
     * Atualiza estatística de total de nutrientes absorvidos.
     * 
     * @param quantidade Nutrientes absorvidos neste ciclo
     */
    void adicionarTotalNutrientes(int quantidade);
    
    // ========== UTILITÁRIOS ==========
    /**
     * Incrementa a idade da planta em 1 ciclo.
     */
    void incrementaIdade();
    
    /**
     * Define a posição desta planta no jardim.
     * 
     * @param linha Índice de linha
     * @param coluna Índice de coluna
     */
    void setPosicao(int linha, int coluna);
    
    // ========== GETTERS ==========
    /**
     * @return Quantidade de água acumulada na planta
     */
    int getAgua() const;
    
    /**
     * @return Quantidade de nutrientes acumulados na planta
     */
    int getNutrientes() const;
    
    /**
     * @return Idade da planta em ciclos
     */
    int getIdade() const;
    
    /**
     * @return Nível de beleza (FEIA, NEUTRA, BONITA)
     */
    Beleza getBeleza() const;
    
    /**
     * @return Linha atual no jardim
     */
    int getLinha() const;
    
    /**
     * @return Coluna atual no jardim
     */
    int getColuna() const;
    
    /**
     * @return Total de nutrientes absorvidos na vida da planta
     */
    int getTotalNutrientes() const;
    
    /**
     * @return Total de água absorvida na vida da planta
     */
    int getTotalAgua() const;
    
    // ========== SETTERS ==========
    /**
     * Define a quantidade de água da planta.
     * 
     * @param valor Novo valor de água
     */
    void setAgua(int valor);
    
    /**
     * Define a quantidade de nutrientes da planta.
     * 
     * @param valor Novo valor de nutrientes
     */
    void setNutrientes(int valor);
    
    /**
     * Define o total de nutrientes absorvidos (para restaurar snapshots).
     * 
     * @param v Novo valor de total
     */
    void setTotalNutrientes(int v);
    
    /**
     * Define o total de água absorvida (para restaurar snapshots).
     * 
     * @param v Novo valor de total
     */
    void setTotalAgua(int v);
};

#endif