/**
 * Abstração de ferramenta para o jardineiro.
 * Cada ferramenta tem número de série único e define comportamento via interface virtual.
 */
#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

class Posicao; // Forward declaration

class Ferramenta {
    friend class Regador;
    friend class Adubo;
    friend class Tesoura;
    friend class Pulverizador;

private:
    int numeroSerie;                    /**< ID único */
    static int contadorSerie;           /**< Contador para gerar IDs */

    /** Restaura número de série (usado por clone) */
    void setNumeroSerie(int n);
    
    /** Sincroniza contador com série observada (snapshots) */
    static void ajustarContadorSeNecessario(int n);

public:
    /** Cria ferramenta com número de série único */
    Ferramenta();
    virtual ~Ferramenta();

    /** Cria cópia profunda preservando estado e ID */
    virtual Ferramenta* clone() const = 0;

    /** Aplica ferramenta. Retorna true se deve ser destruída */
    virtual bool usar(Posicao* pos) = 0;
    
    /** Símbolo para mapa (g=Regador, a=Adubo, t=Tesoura, z=Pulverizador) */
    virtual char getCaracter() const = 0;
    
    /** Nome do tipo (Regador, Adubo, Tesoura, Pulverizador) */
    virtual std::string getTipo() const = 0;
    
    /** Descrição completa (tipo, série, estado) */
    virtual std::string getInfo() const = 0;

    /** Retorna ID único da ferramenta */
    int getNumeroSerie() const;
};

#endif