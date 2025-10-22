#ifndef POSICAO_H
#define POSICAO_H
#include "Posicao.h"
#include "Planta.h"
#include "Ferramenta.h"
class Planta;
class Ferramenta;

class Posicao {
private:
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Posicao();
    Posicao(int aguaInicial, int nutrientesInicial);
    ~Posicao();

    // Getters
    int getAgua() const;
    int getNutrientes() const;
    Planta* getPlanta() const;
    Ferramenta* getFerramenta() const;
    bool estaVazia() const;
    bool temPlanta() const;
    bool temFerramenta() const;

    // Setters
    void setAgua(int valor);
    void setNutrientes(int valor);
    void adicionarAgua(int quantidade);
    void adicionarNutrientes(int quantidade);
    void removerAgua(int quantidade);
    void removerNutrientes(int quantidade);

    // Gestão de plantas e ferramentas
    bool adicionarPlanta(Planta* p);
    Planta* removerPlanta();
    bool adicionarFerramenta(Ferramenta* f);
    Ferramenta* removerFerramenta();


    // Visualização
    char getCaracterVisivel(bool jardineiroPresentte) const;



};

#endif