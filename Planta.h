#ifndef PLANTA_H
#define PLANTA_H

#include <string>

enum class Beleza {
    FEIA,
    NEUTRA,
    BONITA
};

class Planta {
private:
    int aguaAcumulada;
    int nutrientesAcumulados;
    int idade;
    Beleza beleza;
    int linhaPos;
    int colunaPos;
    
    int totalNutrientesAbsorvidos;
    int totalAguaAbsorvida;

public:
    // Operações seguras para alterar estado (substituem acesso direto aos campos)
    void adicionarAgua(int quantidade);
    void removerAgua(int quantidade);
    void adicionarNutrientes(int quantidade);
    void removerNutrientes(int quantidade);
    void adicionarTotalAgua(int quantidade);
    void adicionarTotalNutrientes(int quantidade);
    Planta(int agua, int nutrientes, Beleza bel);
    virtual ~Planta();
    
    // Métodos virtuais puros - devem ser implementados pelas subclasses
    virtual void simular(int& aguaSolo, int& nutrientesSolo) = 0;
    virtual bool deveMorrer() const = 0;
    virtual Planta* tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) = 0;
    virtual char getCaracter() const = 0;
    virtual std::string getTipo() const = 0;

    // Clonagem
    // clone() cria uma cópia profunda da planta (água, nutrientes, idade, totais)
    // e devolve um novo objeto alocado com `new`. O chamador passa a ser responsável
    // por libertar o objeto.
    virtual Planta* clone() const = 0;
    
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

    // Permitir clonar estado interno
    void setTotalNutrientes(int v);
    void setTotalAgua(int v);
};

#endif