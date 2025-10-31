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
#include <cstring>

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
    int numFerramentas = 3; // Como especificado no enunciado
    
    for (int i = 0; i < numFerramentas; i++) {
        colocarFerramentaAleatoria();
    }
}

void Jardim::colocarFerramentaAleatoria() {
    int tentativas = 0;
    while (tentativas < 100) {
        int linha = std::rand() % numLinhas;
        int coluna = std::rand() % numColunas;
        
        if (!area[linha][coluna].temFerramenta()) {
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
    
    // Usar ferramenta na mão se jardineiro estiver no jardim
    if (jardineiro->estaNoJardim() && jardineiro->getFerramentaNaMao() != nullptr) {
        int linha = jardineiro->getLinha();
        int coluna = jardineiro->getColuna();
        jardineiro->usarFerramentaNaMao(&area[linha][coluna]);
    }
    
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
                    // Cacto deixa nutrientes ao morrer
                    Cato* cato = dynamic_cast<Cato*>(p);
                    if (cato != nullptr) {
                        int nutSolo = area[i][j].getNutrientes();
                        cato->deixarNutrientesNoSolo(nutSolo);
                        area[i][j].setNutrientes(nutSolo);
                    }
                    
                    delete p;
                    area[i][j].removerPlanta();
                } else {
                    Planta* nova = p->tentatMultiplicar(agua, nutrientes);
                    if (nova != nullptr) {
                        // Erva mata planta vizinha
                        Erva* erva = dynamic_cast<Erva*>(p);
                        if (erva != nullptr) {
                            adicionarPlantaVizinhaMatando(i, j, nova);
                        } else {
                            adicionarPlantaVizinha(i, j, nova);
                        }
                    }
                }
            }
            
            // Apanhar ferramenta se jardineiro estiver na posição
            if (jardineiro->estaNoJardim() && 
                jardineiro->getLinha() == i && 
                jardineiro->getColuna() == j &&
                area[i][j].temFerramenta()) {
                
                Ferramenta* f = area[i][j].removerFerramenta();
                jardineiro->adicionarFerramenta(f);
                
                // Aparecer nova ferramenta aleatória
                colocarFerramentaAleatoria();
            }
        }
    }
}

bool Jardim::adicionarPlantaVizinha(int linhaOrigem, int colunaOrigem, Planta* novaPlanta) {
    int direcoes[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for (int i = 0; i < 4; i++) {
        int novaLinha = linhaOrigem + direcoes[i][0];
        int novaColuna = colunaOrigem + direcoes[i][1];
        
        if (posicaoValida(novaLinha, novaColuna) && !area[novaLinha][novaColuna].temPlanta()) {
            area[novaLinha][novaColuna].adicionarPlanta(novaPlanta);
            novaPlanta->setPosicao(novaLinha, novaColuna);
            return true;
        }
    }
    
    delete novaPlanta;
    return false;
}

bool Jardim::adicionarPlantaVizinhaMatando(int linhaOrigem, int colunaOrigem, Planta* novaPlanta) {
    int direcoes[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for (int i = 0; i < 4; i++) {
        int novaLinha = linhaOrigem + direcoes[i][0];
        int novaColuna = colunaOrigem + direcoes[i][1];
        
        if (posicaoValida(novaLinha, novaColuna)) {
            // Matar planta existente se houver
            Planta* antiga = area[novaLinha][novaColuna].removerPlanta();
            delete antiga;
            
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
        std::cout << (char)('A' + j);
    }
    std::cout << "\n";
    
    for (int i = 0; i < numLinhas; i++) {
        std::cout << (char)('A' + i) << " ";
        for (int j = 0; j < numColunas; j++) {
            bool jardineiro_aqui = jardineiro->estaNoJardim() && 
                                   jardineiro->getLinha() == i && 
                                   jardineiro->getColuna() == j;
            std::cout << area[i][j].getCaracterVisivel(jardineiro_aqui);
        }
        std::cout << " " << (char)('A' + i) << "\n";
    }
    
    std::cout << "  ";
    for (int j = 0; j < numColunas; j++) {
        std::cout << (char)('A' + j);
    }
    std::cout << "\n";
}

void Jardim::listarPlantas() const {
    std::cout << "\n=== Plantas no Jardim ===\n";
    int total = 0;
    
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            Planta* p = area[i][j].getPlanta();
            if (p != nullptr) {
                total++;
                std::cout << (char)('a' + i) << (char)('a' + j)
                          << " - " << p->getTipo() 
                          << " (idade: " << p->getIdade() 
                          << ", agua: " << p->getAgua()
                          << ", nutrientes: " << p->getNutrientes() << ")\n";
                std::cout << "     Solo: agua=" << area[i][j].getAgua() 
                          << ", nutrientes=" << area[i][j].getNutrientes() << "\n";
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
    std::cout << "Posicao: " << (char)('a' + linha) << (char)('a' + coluna) << "\n";
    std::cout << "Tipo: " << p->getTipo() << "\n";
    std::cout << "Idade: " << p->getIdade() << " instantes\n";
    std::cout << "Agua acumulada: " << p->getAgua() << "\n";
    std::cout << "Nutrientes acumulados: " << p->getNutrientes() << "\n";
}

void Jardim::listarArea() const {
    std::cout << "\n=== Area do Jardim ===\n";
    
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            if (!area[i][j].estaVazia() || area[i][j].getAgua() > 0 || area[i][j].getNutrientes() > 0) {
                std::cout << "Posicao " << (char)('a' + i) << (char)('a' + j) << ":\n";
                std::cout << "  Agua: " << area[i][j].getAgua() 
                          << ", Nutrientes: " << area[i][j].getNutrientes() << "\n";
                
                if (area[i][j].getPlanta() != nullptr) {
                    std::cout << "  Planta: " << area[i][j].getPlanta()->getTipo() << "\n";
                }
                if (area[i][j].getFerramenta() != nullptr) {
                    std::cout << "  Ferramenta: " << area[i][j].getFerramenta()->getInfo() << "\n";
                }
            }
        }
    }
}

void Jardim::listarSolo(int linha, int coluna, int raio) const {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return;
    }
    
    std::cout << "\n=== Informacoes do Solo ===\n";
    
    if (raio == 0) {
        std::cout << "Posicao " << (char)('a' + linha) << (char)('a' + coluna) << ":\n";
        std::cout << "  Agua: " << area[linha][coluna].getAgua() << "\n";
        std::cout << "  Nutrientes: " << area[linha][coluna].getNutrientes() << "\n";
        
        if (area[linha][coluna].getPlanta() != nullptr) {
            std::cout << "  Planta: " << area[linha][coluna].getPlanta()->getTipo() << "\n";
        }
        if (area[linha][coluna].getFerramenta() != nullptr) {
            std::cout << "  Ferramenta: " << area[linha][coluna].getFerramenta()->getInfo() << "\n";
        }
    } else {
        for (int i = linha - raio; i <= linha + raio; i++) {
            for (int j = coluna - raio; j <= coluna + raio; j++) {
                if (posicaoValida(i, j)) {
                    std::cout << "Posicao " << (char)('a' + i) << (char)('a' + j) << ":\n";
                    std::cout << "  Agua: " << area[i][j].getAgua() << "\n";
                    std::cout << "  Nutrientes: " << area[i][j].getNutrientes() << "\n";
                    
                    if (area[i][j].getPlanta() != nullptr) {
                        std::cout << "  Planta: " << area[i][j].getPlanta()->getTipo() << "\n";
                    }
                    if (area[i][j].getFerramenta() != nullptr) {
                        std::cout << "  Ferramenta: " << area[i][j].getFerramenta()->getInfo() << "\n";
                    }
                }
            }
        }
    }
}

void Jardim::listarFerramentas() const {
    std::cout << "\n=== Ferramentas ===\n";
    
    Ferramenta** ferrs = jardineiro->getFerramentas();
    int numF = jardineiro->getNumFerramentas();
    
    if (numF == 0 && jardineiro->getFerramentaNaMao() == nullptr) {
        std::cout << "O jardineiro nao tem ferramentas\n";
        return;
    }
    
    std::cout << "Ferramentas no inventario:\n";
    for (int i = 0; i < numF; ++i) {
        const Ferramenta* f = ferrs[i];
        std::cout << "  " << f->getInfo() << "\n";
    }
    
    if (jardineiro->getFerramentaNaMao() != nullptr) {
        std::cout << "Na mao: " << jardineiro->getFerramentaNaMao()->getInfo() << "\n";
    } else {
        std::cout << "Nada na mao\n";
    }
}

bool Jardim::colherPlanta(int linha, int coluna) {
    if (!posicaoValida(linha, coluna)) {
        std::cout << "Posicao invalida\n";
        return false;
    }
    
    if (!jardineiro->podeColher()) {
        std::cout << "Limite de colheitas atingido neste turno\n";
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
    
    if (!jardineiro->podePlantar()) {
        std::cout << "Limite de plantacoes atingido neste turno\n";
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

bool Jardim::moverJardineiro(char direcao) {
    if (!jardineiro->estaNoJardim()) {
        std::cout << "Jardineiro nao esta no jardim\n";
        return false;
    }
    
    int deltaLinha = 0, deltaColuna = 0;
    
    switch (direcao) {
        case 'c': deltaLinha = -1; break; // cima
        case 'b': deltaLinha = 1; break;  // baixo
        case 'e': deltaColuna = -1; break; // esquerda
        case 'd': deltaColuna = 1; break;  // direita
        default: return false;
    }
    
    return jardineiro->mover(deltaLinha, deltaColuna, numLinhas, numColunas);
}

bool Jardim::jardineirosEntra(int linha, int coluna) {
    // Validações
    if (!foiCriado()) {
        return false;
    }

    // Verifica se já existe jardineiro
    if (jardineiro->estaNoJardim()) {
        return false;
    }

    // Verifica limites do jardim
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        return false;
    }

    // Tenta fazer o jardineiro entrar
    if (jardineiro->entrar(linha, coluna, numLinhas, numColunas)) {
        imprimir();
        return true;
    }

    return false;
}

bool Jardim::jardineirosai() {
    return jardineiro->sair();
}

bool Jardim::jardineiroPega(int numeroSerie) {
    return jardineiro->pegarFerramenta(numeroSerie);
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
    
    // Se já existe ferramenta, devolve ao jardineiro
    jardineiro->adicionarFerramenta(f);
    return false;
}

bool Jardim::comprarFerramenta(char tipo) {
    Ferramenta* nova = nullptr;
    
    switch (tipo) {
        case 'g': nova = new Regador(); break;
        case 'a': nova = new Adubo(); break;
        case 't': nova = new Tesoura(); break;
        case 'z': 
            std::cout << "FerramentaZ ainda nao implementada\n";
            return false;
        default: return false;
    }
    
    jardineiro->adicionarFerramenta(nova);
    return true;
}

bool Jardim::gravarCopia(const std::string& nome) {
    // Se já existe, apagar primeiro
    auto it = copiasSalvas.find(nome);
    if (it != copiasSalvas.end()) {
        delete it->second;
        copiasSalvas.erase(it);
    }
    
    // Criar cópia (implementação simplificada - copia estado atual)
    Jardim* copia = new Jardim();
    copia->numLinhas = numLinhas;
    copia->numColunas = numColunas;
    copia->instanteAtual = instanteAtual;
    
    // Copiar área
    copia->area = new Posicao*[numLinhas];
    for (int i = 0; i < numLinhas; i++) {
        copia->area[i] = new Posicao[numColunas];
        for (int j = 0; j < numColunas; j++) {
            copia->area[i][j].setAgua(area[i][j].getAgua());
            copia->area[i][j].setNutrientes(area[i][j].getNutrientes());
            // TODO: Copiar plantas e ferramentas (deep copy)
        }
    }
    
    copiasSalvas[nome] = copia;
    return true;
}

bool Jardim::recuperarCopia(const std::string& nome) {
    auto it = copiasSalvas.find(nome);
    if (it == copiasSalvas.end()) {
        std::cout << "Copia nao encontrada: " << nome << "\n";
        return false;
    }
    
    // Libertar estado atual
    liberarMemoria();
    
    // Copiar da cópia salva
    Jardim* copia = it->second;
    numLinhas = copia->numLinhas;
    numColunas = copia->numColunas;
    instanteAtual = copia->instanteAtual;
    
    area = new Posicao*[numLinhas];
    for (int i = 0; i < numLinhas; i++) {
        area[i] = new Posicao[numColunas];
        for (int j = 0; j < numColunas; j++) {
            area[i][j].setAgua(copia->area[i][j].getAgua());
            area[i][j].setNutrientes(copia->area[i][j].getNutrientes());
            // TODO: Copiar plantas e ferramentas
        }
    }
    
    // Apagar cópia
    delete copia;
    copiasSalvas.erase(it);
    
    return true;
}

bool Jardim::apagarCopia(const std::string& nome) {
    auto it = copiasSalvas.find(nome);
    if (it == copiasSalvas.end()) {
        std::cout << "Copia nao encontrada: " << nome << "\n";
        return false;
    }
    
    delete it->second;
    copiasSalvas.erase(it);
    return true;
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
