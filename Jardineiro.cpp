#include "Jardineiro.h"
#include "Settings.h"
#include <iostream>

static const int JARDINEIRO_CAP_INICIAL = 4;

Jardineiro::Jardineiro()
    : linha(-1), coluna(-1), noJardim(false),
      ferramentas(nullptr), numFerramentas(0), capacidadeFerramentas(0),
      ferramentaNaMao(nullptr),
      movimentosRestantes(0), plantasColhidasNoTurno(0),
      plantasPlantadasNoTurno(0), entradasNoTurno(0), saidasNoTurno(0) {
    // Inicializa capacidade
    garantirCapacidade(JARDINEIRO_CAP_INICIAL);
}

Jardineiro::~Jardineiro() {
    // Libertar ferramentas guardadas no inventario
    if (ferramentas != nullptr) {
        for (int i = 0; i < numFerramentas; ++i) {
            delete ferramentas[i];
        }
        delete[] ferramentas;
        ferramentas = nullptr;
    }
    // Ferramenta na mão é propriedade do jardineiro -> libertar se existir
    delete ferramentaNaMao;
    ferramentaNaMao = nullptr;
}

// Garante capacidade do array; realoca e copia elementos existentes.
bool Jardineiro::garantirCapacidade(int novaCapacidade) {
    if (novaCapacidade <= capacidadeFerramentas) return true;

    if (novaCapacidade < 1) novaCapacidade = JARDINEIRO_CAP_INICIAL;
    Ferramenta** novo = new Ferramenta*[novaCapacidade];
    for (int i = 0; i < novaCapacidade; ++i) novo[i] = nullptr;

    // copiar existentes
    for (int i = 0; i < numFerramentas; ++i) {
        novo[i] = ferramentas[i];
    }

    delete[] ferramentas;
    ferramentas = novo;
    capacidadeFerramentas = novaCapacidade;
    return true;
}

// Movimento simples com limites.
bool Jardineiro::mover(int deltaLinha, int deltaColuna, int maxLinhas, int maxColunas) {
    if (!noJardim || !podeMover()) return false;

    int novaLinha = linha + deltaLinha;
    int novaColuna = coluna + deltaColuna;

    if (novaLinha < 0 || novaLinha >= maxLinhas ||
        novaColuna < 0 || novaColuna >= maxColunas) {
        return false;
    }

    linha = novaLinha;
    coluna = novaColuna;
    movimentosRestantes--;
    return true;
}

// Entra no jardim numa posição válida.
bool Jardineiro::entrar(int l, int c, int maxLinhas, int maxColunas) {
    if (noJardim || !podeEntrar()) return false;
    if (l < 0 || l >= maxLinhas || c < 0 || c >= maxColunas) return false;

    linha = l;
    coluna = c;
    noJardim = true;
    entradasNoTurno++;
    return true;
}

// Sai do jardim.
bool Jardineiro::sair() {
    if (!noJardim || !podeSair()) return false;

    noJardim = false;
    linha = -1;
    coluna = -1;
    saidasNoTurno++;
    return true;
}

// Adiciona ferramenta ao inventário; expande array se necessário.
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    if (numFerramentas + 1 > capacidadeFerramentas) {
        int novaCap = capacidadeFerramentas * 2;
        if (novaCap < 1) novaCap = JARDINEIRO_CAP_INICIAL;
        garantirCapacidade(novaCap);
    }
    ferramentas[numFerramentas++] = f;
}

// Pega ferramenta por número de série; faz shift left para manter array compacto.
bool Jardineiro::pegarFerramenta(int numeroSerie) {
    if (ferramentaNaMao != nullptr) return false;

    for (int i = 0; i < numFerramentas; ++i) {
        if (ferramentas[i] != nullptr && ferramentas[i]->getNumeroSerie() == numeroSerie) {
            ferramentaNaMao = ferramentas[i];
            // shift left
            for (int j = i; j < numFerramentas - 1; ++j) {
                ferramentas[j] = ferramentas[j + 1];
            }
            ferramentas[numFerramentas - 1] = nullptr;
            --numFerramentas;
            return true;
        }
    }
    return false;
}

// Larga ferramenta que está na mão (retorna ponteiro, jardineiro deixa de a possuir).
Ferramenta* Jardineiro::largarFerramenta() {
    Ferramenta* temp = ferramentaNaMao;
    ferramentaNaMao = nullptr;
    return temp;
}

// Verificações de limites por turno (usam Settings).
bool Jardineiro::podeColher() const {
    return plantasColhidasNoTurno < Settings::Jardineiro::max_colheitas;
}

bool Jardineiro::podePlantar() const {
    return plantasPlantadasNoTurno < Settings::Jardineiro::max_plantacoes;
}

bool Jardineiro::podeMover() const {
    return movimentosRestantes > 0;
}

bool Jardineiro::podeEntrar() const {
    return entradasNoTurno < Settings::Jardineiro::max_entradas_saidas;
}

bool Jardineiro::podeSair() const {
    return saidasNoTurno < Settings::Jardineiro::max_entradas_saidas;
}

// Registos de ações no turno corrente.
void Jardineiro::registarColheita() {
    plantasColhidasNoTurno++;
}

void Jardineiro::registarPlantacao() {
    plantasPlantadasNoTurno++;
}

// Reseta contadores e movimentos para novo turno.
void Jardineiro::novoTurno() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantasColhidasNoTurno = 0;
    plantasPlantadasNoTurno = 0;
    entradasNoTurno = 0;
    saidasNoTurno = 0;
}

// Getters simples.
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }
bool Jardineiro::estaNoJardim() const { return noJardim; }
Ferramenta* Jardineiro::getFerramentaNaMao() const { return ferramentaNaMao; }
Ferramenta** Jardineiro::getFerramentas() const { return ferramentas; }
int Jardineiro::getNumFerramentas() const { return numFerramentas; }
int Jardineiro::getMovimentosRestantes() const { return movimentosRestantes; }
