/**
 * ============================================================================
 *  CLASSE: Posicao
 *  DESCRIÇÃO: Representa uma célula do jardim com solo, planta e ferramenta
 *  
 *  Responsabilidades:
 *    - Armazenar recursos do solo (água, nutrientes)
 *    - Armazenar planta (se houver) nesta célula
 *    - Armazenar ferramenta (se houver) nesta célula
 *    - Facilitar consultas e modificações de estado
 * ============================================================================
 */
#ifndef POSICAO_H
#define POSICAO_H

#include "Planta.h"
#include "Ferramenta.h"

class Planta;
class Ferramenta;

class Posicao {
private:
    int agua;                           /**< Água disponível no solo */
    int nutrientes;                     /**< Nutrientes disponíveis no solo */
    Planta* planta;                     /**< Planta nesta posição (nullptr se vazio) */
    Ferramenta* ferramenta;             /**< Ferramenta nesta posição (nullptr se vazio) */

public:
    // ========== CONSTRUTORES ==========
    /**
     * Construtor padrão. Inicializa solo vazio (0 água, 0 nutrientes).
     */
    Posicao();
    
    /**
     * Construtor com valores iniciais de solo.
     * 
     * @param aguaInicial Água inicial do solo
     * @param nutrientesInicial Nutrientes iniciais do solo
     */
    Posicao(int aguaInicial, int nutrientesInicial);
    ~Posicao();

    // ========== GETTERS SOLO ==========
    /**
     * @return Água disponível no solo desta posição
     */
    int getAgua() const;
    
    /**
     * @return Nutrientes disponíveis no solo desta posição
     */
    int getNutrientes() const;
    
    /**
     * @return Planta nesta posição ou nullptr
     */
    Planta* getPlanta() const;
    
    /**
     * @return Ferramenta nesta posição ou nullptr
     */
    Ferramenta* getFerramenta() const;
    
    /**
     * @return true se posição não contém planta nem ferramenta
     */
    bool estaVazia() const;
    
    /**
     * @return true se posição contém planta
     */
    bool temPlanta() const;
    
    /**
     * @return true se posição contém ferramenta
     */
    bool temFerramenta() const;

    // ========== SETTERS SOLO ==========
    /**
     * Define a quantidade de água no solo.
     * 
     * @param valor Nova quantidade de água
     */
    void setAgua(int valor);
    
    /**
     * Define a quantidade de nutrientes no solo.
     * 
     * @param valor Nova quantidade de nutrientes
     */
    void setNutrientes(int valor);
    
    /**
     * Aumenta água no solo.
     * 
     * @param quantidade Água a adicionar
     */
    void adicionarAgua(int quantidade);
    
    /**
     * Aumenta nutrientes no solo.
     * 
     * @param quantidade Nutrientes a adicionar
     */
    void adicionarNutrientes(int quantidade);
    
    /**
     * Diminui água no solo (não fica negativa).
     * 
     * @param quantidade Água a remover
     */
    void removerAgua(int quantidade);
    
    /**
     * Diminui nutrientes no solo (não fica negativa).
     * 
     * @param quantidade Nutrientes a remover
     */
    void removerNutrientes(int quantidade);

    // ========== GESTÃO DE PLANTA ==========
    /**
     * Adiciona uma planta nesta posição.
     * A posição assume propriedade do objeto.
     * 
     * @param p Ponteiro a planta
     * @return true se sucesso; false se já existe planta
     */
    bool adicionarPlanta(Planta* p);
    
    /**
     * Remove a planta desta posição.
     * O caller assume propriedade do objeto retornado.
     * 
     * @return Planta removida ou nullptr
     */
    Planta* removerPlanta();
    
    // ========== GESTÃO DE FERRAMENTA ==========
    /**
     * Adiciona uma ferramenta nesta posição.
     * A posição assume propriedade do objeto.
     * 
     * @param f Ponteiro a ferramenta
     * @return true se sucesso; false se já existe ferramenta
     */
    bool adicionarFerramenta(Ferramenta* f);
    
    /**
     * Remove a ferramenta desta posição.
     * O caller assume propriedade do objeto retornado.
     * 
     * @return Ferramenta removida ou nullptr
     */
    Ferramenta* removerFerramenta();

    // ========== VISUALIZAÇÃO ==========
    /**
     * Obtém o caractere visual para esta posição.
     * 
     * @param jardineirosPresente true se jardineiro está aqui
     * @return '*' se jardineiro aqui; caractere de planta; caractere de ferramenta; ' ' se vazio
     */
    char getCaracterVisivel(bool jardineirosPresente) const;
};

#endif