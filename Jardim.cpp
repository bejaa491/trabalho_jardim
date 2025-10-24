#include "Jardim.h"
#include "Cato.h"
#include "Roseira.h"
#include "Erva.h"
#include "Regador.h"
#include "Adubo.h"
#include "Tesoura.h"
#include "Settings.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Jardim::Jardim() : area(nullptr), numLinhas(0), numColunas(0), 
                   instanteAtual(0), jardineiro(nullptr) {
    std::srand(std::time(nullptr));
}

Jardim::~Jardim() {
    liberarMemoria();
    delete jardineiro;
    
    for (auto& par : copiasSalvas) {
        delete par.second;
    }
}

bool Jardim::criar(int linhas, int colunas) {
    if (area != nullptr) {
        return false;
    }
    
    numLinhas = linhas;
    numColunas = colunas;
    instanteAtual = 0;
    
    area = new Posicao*[numLinhas];
    for (int i = 0; i < numLinhas; i++) {
        area[i] = new Posicao[numColunas];
    }
    
    inicializarSolo();
    colocarFerramentasIniciais();
    
    jardineiro = new Jardineiro();
    
    return true;
}

void Jardim::inicializarSolo() {
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            int agua = Settings::Jardim::agua_min + 
                       (std::rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1));
            int nutrientes = Settings::Jardim::nutrientes_min + 
                            (std::rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1));
            
            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);
        }
    }
}

void Jardim::colocarFerramentasIniciais() {
    int numFerramentas = (numLinhas * numColunas) / 10;
    if (numFerramentas < 1) numFerramentas = 1;
    
    for (int i = 0; i < numFerramentas; i++) {
        colocarFerramentaAleatoria();
    }
}

void Jardim::colocarFerramentaAleatoria() {
    int tentativas = 0;
    while (tentativas < 100) {
        int linha = std::rand() % numLinhas;
        int coluna = std::rand() % numColunas;
        
        if (area[linha][coluna].estaVazia()) {
            Ferramenta* f = criarFerramentaAleatoria();
            area[linha][coluna].adicionarFerramenta(f);
            return;
        }
        tentativas++;
    }
}

Ferramenta* Jardim::criarFerramentaAleatoria() {
    int tipo = std::rand() % 3;
    switch (tipo) {
        case 0: return new Regador();
        case 1: return new Adubo();
        case 2: return new Tesoura();
        default: return new Regador();
    }
}

void Jardim::avancarTempo(int instantes) {
    for (int i = 0; i < instantes; i++) {
        simularInstante();
        instanteAtual++;
    }
}

void Jardim::simularInstante() {
    jardineiro->novoTurno();
    
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            Planta* p = area[i][j].getPlanta();
            if (p != nullptr) {
                int agua = area[i][j].getAgua();
                int nutrientes = area[i][j].getNutrientes();
                
                p->simular(agua, nutrientes);
                p->incrementaIdade();
                
                area[i][j].setAgua(agua);
                area[i][j].setNutrientes(nutrientes);
                
                if (p->deveMorrer()) {
                    delete p;
                    area[i][j].removerPlanta();
                } else {
                    Planta* nova = p->tentatMultiplicar(agua, nutrientes);
                    if (nova != nullptr) {
                        adicionarPlantaVizinha(i, j, nova);
                    }
                }
            }
        }
    }
}

bool Jardim::adicionarPlantaVizinha(int linhaOrigem, int colunaOrigem, Planta* novaPlanta) {
    int direcoes[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for (int i = 0; i < 4; i++) {
        int novaLinha = linhaOrigem + direcoes[i][0];
        int novaColuna = colunaOrigem + direcoes[i][1];
        
        if (posicaoValida(novaLinha, novaColuna) && area[novaLinha][novaColuna].estaVazia()) {
            area[novaLinha][novaColuna].adicionarPlanta(novaPlanta);
            novaPlanta->setPosicao(novaLinha, novaColuna);
            return true;
        }
    }
    
    delete novaPlanta;
    return false;
}

void Jardim::imprimir() const {
    std::cout << "\n=== Jardim (Instante: " << instanteAtual << ") ===\n";
    std::cout << "  ";
    for (int j = 0; j < numColunas; j++) {
        std::cout << indiceParaLetra(j);
    }
    std::cout << "\n";
    
    for (int i = 0; i < numLinhas; i++) {
        std::cout << indiceParaLetra(i) << " ";
        for (int j = 0; j < numColunas; j++) {
            bool jardineiro_aqui = jardineiro->estaNoJardim() && 
                                   jardineiro->getLinha() == i && 
                                   jardineiro->getColuna() == j;
            std::cout << area[i][j].getCaracterVisivel(jardineiro_aqui);
        }
        std::cout << "\n";
    }
}

void Jardim::listarPlantas() const {
    std::cout << "\n=== Plantas no Jardim ===\n";
    int total = 0;
    
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            Planta* p = area[i][j].getPlanta();
            if (p != nullptr) {
                total++;
                std::cout << indiceParaLetra(i) << indiceParaLetra(j) 
                          << " - " << p->getTipo() 
                          << " (idade: " << p->getIdade() << ")\n";
            }
        }
    }
    
    std::cout << "Total: " << total << " plantas\n";
}

void Jardim::listarPlanta(int linha, int coluna) const {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return;
    }
    
    Planta* p = area[linha][coluna].getPlanta();
    if (p == nullptr) {
        std::cout << "Nao ha planta nesta posicao\n";
        return;
    }
    
    std::cout << "\n=== Informacoes da Planta ===\n";
    std::cout << "Tipo: " << p->getTipo() << "\n";
    std::cout << "Idade: " << p->getIdade() << " instantes\n";
    std::cout << "Agua acumulada: " << p->getAgua() << "\n";
    std::cout << "Nutrientes acumulados: " << p->getNutrientes() << "\n";
}

void Jardim::listarArea() const {
    imprimir();
}

void Jardim::listarSolo(int linha, int coluna, int raio) const {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return;
    }
    
    std::cout << "\n=== Informacoes do Solo ===\n";
    
    if (raio == 0) {
        std::cout << "Posicao " << indiceParaLetra(linha) << indiceParaLetra(coluna) << ":\n";
        std::cout << "  Agua: " << area[linha][coluna].getAgua() << "\n";
        std::cout << "  Nutrientes: " << area[linha][coluna].getNutrientes() << "\n";
    } else {
        for (int i = linha - raio; i <= linha + raio; i++) {
            for (int j = coluna - raio; j <= coluna + raio; j++) {
                if (posicaoValida(i, j)) {
                    std::cout << "Posicao " << indiceParaLetra(i) << indiceParaLetra(j) << ":\n";
                    std::cout << "  Agua: " << area[i][j].getAgua() << "\n";
                    std::cout << "  Nutrientes: " << area[i][j].getNutrientes() << "\n";
                }
            }
        }
    }
}

void Jardim::listarFerramentas() const {
    std::cout << "\n=== Ferramentas ===\n";
    std::cout << "Ferramentas do jardineiro:\n";
    
    Ferramenta** ferrs = jardineiro->getFerramentas();
    int numF = jardineiro->getNumFerramentas();
    for (int i = 0; i < numF; ++i) {
        const Ferramenta* f = ferrs[i];
        std::cout << "  " << f->getInfo() << "\n";
    }
    
    if (jardineiro->getFerramentaNaMao() != nullptr) {
        std::cout << "Na mao: " << jardineiro->getFerramentaNaMao()->getInfo() << "\n";
    }
}

bool Jardim::colherPlanta(int linha, int coluna) {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return false;
    }
    
    if (!jardineiro->estaNoJardim() || 
        jardineiro->getLinha() != linha || 
        jardineiro->getColuna() != coluna) {
        std::cout << "Jardineiro nao esta nesta posicao\n";
        return false;
    }
    
    if (!jardineiro->podeColher()) {
        std::cout << "Limite de colheitas atingido\n";
        return false;
    }
    
    Planta* p = area[linha][coluna].removerPlanta();
    if (p == nullptr) {
        std::cout << "Nao ha planta para colher\n";
        return false;
    }
    
    delete p;
    jardineiro->registarColheita();
    std::cout << "Planta colhida com sucesso\n";
    return true;
}

bool Jardim::plantarPlanta(int linha, int coluna, char tipo) {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return false;
    }
    
    if (!jardineiro->estaNoJardim() || 
        jardineiro->getLinha() != linha || 
        jardineiro->getColuna() != coluna) {
        std::cout << "Jardineiro nao esta nesta posicao\n";
        return false;
    }
    
    if (!jardineiro->podePlantar()) {
        std::cout << "Limite de plantacoes atingido\n";
        return false;
    }
    
    if (area[linha][coluna].temPlanta()) {
        std::cout << "Ja existe uma planta nesta posicao\n";
        return false;
    }
    
    Planta* nova = nullptr;
    switch (tipo) {
        case 'c': nova = new Cato(); break;
        case 'r': nova = new Roseira(); break;
        case 'e': nova = new Erva(); break;
        default:
            std::cout << "Tipo de planta invalido\n";
            return false;
    }
    
    area[linha][coluna].adicionarPlanta(nova);
    nova->setPosicao(linha, coluna);
    jardineiro->registarPlantacao();
    std::cout << "Planta plantada com sucesso\n";
    return true;
}

bool Jardim::jardineirolLarga() {
    if (!jardineiro->estaNoJardim()) {
        return false;
    }
    
    Ferramenta* f = jardineiro->largarFerramenta();
    if (f == nullptr) {
        return false;
    }
    
    int linha = jardineiro->getLinha();
    int coluna = jardineiro->getColuna();
    
    if (!area[linha][coluna].temFerramenta()) {
        area[linha][coluna].adicionarFerramenta(f);
        return true;
    }
    
    jardineiro->adicionarFerramenta(f);
    return false;
}

bool Jardim::posicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas;
}

bool Jardim::foiCriado() const {
    return area != nullptr;
}

void Jardim::liberarMemoria() {
    if (area != nullptr) {
        for (int i = 0; i < numLinhas; i++) {
            delete[] area[i];
        }
        delete[] area;
        area = nullptr;
    }
}

char Jardim::indiceParaLetra(int indice) const {
    return 'a' + indice;
}

char Jardim::letraParaIndice(char letra) const {
    return letra - 'a';
}