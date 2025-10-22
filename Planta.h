#ifndef PLANTA_H
#define PLANTA_H

#include <string>

enum class Beleza {
    FEIA,
    NEUTRA,
    BONITA
};

class Planta {
protected:
    int aguaAcumulada;
    int nutrientesAcumulados;
    int idade;
    Beleza beleza;
    int linhaPos;
    int colunaPos;
    
    int totalNutrientesAbsorvidos;
    int totalAguaAbsorvida;

public:
    Planta(int agua, int nutrientes, Beleza bel);
    virtual ~Planta();
    
    // Métodos virtuais puros - devem ser implementados pelas subclasses
    virtual void simular(int& aguaSolo, int& nutrientesSolo) = 0;
    virtual bool deveMorrer() const = 0;
    virtual Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) = 0;
    virtual char getCaracter() const = 0;
    virtual std::string getTipo() const = 0;
    
    // Métodos auxiliares
    void incrementaIdade();
    void setPosicao(int linha, int coluna);
    
    // Getters
    int getAgua() const;
    int getNutrientes() const;
    int getIdade() const;
    Beleza getBeleza() const;
    int getLinha() const;
    int getColuna() const;
    int getTotalNutrientes() const;
    int getTotalAgua() const;
    
    // Setters
    void setAgua(int valor);
    void setNutrientes(int valor);
};

#endif