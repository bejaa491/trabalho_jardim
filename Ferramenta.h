/**
 * ============================================================================
 *  CLASSE: Ferramenta (Classe Base Abstrata)
 *  DESCRIÇÃO: Abstração de uma ferramenta que o jardineiro usa
 *  
 *  Responsabilidades:
 *    - Armazenar identificação única (número de série)
 *    - Definir interface virtual para uso no jardim
 *    - Suportar clonagem para salvar/restaurar estado
 * 
 *  Subclasses Concretas:
 *    - Regador: adiciona água às plantas
 *    - Adubo: adiciona nutrientes às plantas
 *    - Tesoura: corta ervas daninhas
 *    - Pulverizador: mata ervas num raio (ferramenta especial)
 * ============================================================================
 */
#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

class Posicao; // Forward declaration

class Ferramenta {
protected:
    int numeroSerie;                    /**< Identificador único da ferramenta */
    static int contadorSerie;           /**< Gerador de números de série únicos */

    /**
     * Define o número de série de uma ferramenta.
     * Usado internamente por clone() para preservar ID.
     * 
     * @param n Novo número de série
     */
    void setNumeroSerie(int n);
    
    /**
     * Ajusta o contador global se necessário (para restaurar snapshots).
     * 
     * @param n Número de série observado
     */
    static void ajustarContadorSeNecessario(int n);

public:
    /**
     * Construtor padrão. Atribui número de série único automático.
     */
    Ferramenta();
    virtual ~Ferramenta();

    // ========== INTERFACE VIRTUAL (implementada por subclasses) ==========
    /**
     * Clona esta ferramenta criando cópia profunda.
     * Preserva número de série e estado interno (capacidade, eficácia, quantidade).
     * O chamador assume propriedade do novo objeto.
     * 
     * @return Novo objeto Ferramenta* alocado com 'new'
     */
    virtual Ferramenta* clone() const = 0;

    /**
     * Usa a ferramenta numa posição do jardim.
     * Efeito específico varia por tipo:
     *   - Regador: hidrata planta
     *   - Adubo: fertiliza planta
     *   - Tesoura: corta ervas
     *   - Pulverizador: elimina ervas numa área
     * 
     * @param pos Posição onde usar a ferramenta
     * @return true se a ferramenta deve ser destruída após uso; false caso continue útil
     */
    virtual bool usar(Posicao* pos) = 0;
    
    /**
     * Retorna o caractere que representa esta ferramenta no mapa visual.
     * Exemplos: 'g' Regador, 'a' Adubo, 't' Tesoura, 'z' Pulverizador
     * 
     * @return Caractere ASCII
     */
    virtual char getCaracter() const = 0;
    
    /**
     * Retorna o nome do tipo de ferramenta.
     * 
     * @return String descritiva (ex: "Regador", "Adubo", "Tesoura", "Pulverizador")
     */
    virtual std::string getTipo() const = 0;
    
    /**
     * Retorna informações detalhadas da ferramenta (tipo, série, estado).
     * 
     * @return String com descrição completa
     */
    virtual std::string getInfo() const = 0;

    // ========== GETTERS ==========
    /**
     * Obtém o número de série único desta ferramenta.
     * 
     * @return Identificador inteiro positivo
     */
    int getNumeroSerie() const;
};

#endif