#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

class Posicao; // Forward declaration

class Ferramenta {
protected:
    int numeroSerie;
    static int contadorSerie;

    // Permite forçar número de série em clones
    void setNumeroSerie(int n);
    static void ajustarContadorSeNecessario(int n);

public:
    Ferramenta();
    virtual ~Ferramenta();

    // Método de clonagem (preserva estado interno).
    // clone() deve retornar um novo objeto alocado com `new` que é propriedade do
    // chamador; o número de série e o estado interno (capacidade/eficácia/quantidade)
    // devem ser preservados na cópia.
    virtual Ferramenta* clone() const = 0;

    // Métodos virtuais 
    virtual bool usar(Posicao* pos) = 0;  // Retorna true se a ferramenta deve ser destruída
    virtual char getCaracter() const = 0;
    virtual std::string getTipo() const = 0;
    virtual std::string getInfo() const = 0;

    // Getters
    int getNumeroSerie() const;
};

#endif