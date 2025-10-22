#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

class Posicao; // Forward declaration

class Ferramenta {
protected:
    int numeroSerie;
    static int contadorSerie;

public:
    Ferramenta();
    virtual ~Ferramenta();

    // Métodos virtuais puros
    virtual bool usar(Posicao* pos) = 0;  // Retorna true se a ferramenta deve ser destruída
    virtual char getCaracter() const = 0;
    virtual std::string getTipo() const = 0;
    virtual std::string getInfo() const = 0;

    // Getters
    int getNumeroSerie() const;
};

#endif