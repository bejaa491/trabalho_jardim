#include "Jardineiro.h"
#include "Settings.h"

Jardineiro::Jardineiro()
    : linha(-1), coluna(-1), noJardim(false), ferramentaNaMao(nullptr),
      movimentosRestantes(0), plantasColhidasNoTurno(0),
      plantasPlantadasNoTurno(0), entradasNoTurno(0), saidasNoTurno(0) {}

Jardineiro::~Jardineiro() {
    for (auto* f : ferramentas) {
        delete f;
    }
    delete ferramentaNaMao;
}

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

bool Jardineiro::entrar(int l, int c, int maxLinhas, int maxColunas) {
    if (noJardim || !podeEntrar()) return false;
    if (l < 0 || l >= maxLinhas || c < 0 || c >= maxColunas) return false;

    linha = l;
    coluna = c;
    noJardim = true;
    entradasNoTurno++;
    return true;
}

bool Jardineiro::sair() {
    if (!noJardim || !podeSair()) return false;

    noJardim = false;
    linha = -1;
    coluna = -1;
    saidasNoTurno++;
    return true;
}

void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    ferramentas.push_back(f);
}

bool Jardineiro::pegarFerramenta(int numeroSerie) {
    if (ferramentaNaMao != nullptr) return false;

    for (size_t i = 0; i < ferramentas.size(); i++) {
        if (ferramentas[i]->getNumeroSerie() == numeroSerie) {
            ferramentaNaMao = ferramentas[i];
            ferramentas.erase(ferramentas.begin() + i);
            return true;
        }
    }
    return false;
}

Ferramenta* Jardineiro::largarFerramenta() {
    Ferramenta* temp = ferramentaNaMao;
    ferramentaNaMao = nullptr;
    return temp;
}

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

void Jardineiro::registarColheita() {
    plantasColhidasNoTurno++;
}

void Jardineiro::registarPlantacao() {
    plantasPlantadasNoTurno++;
}

void Jardineiro::novoTurno() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantasColhidasNoTurno = 0;
    plantasPlantadasNoTurno = 0;
    entradasNoTurno = 0;
    saidasNoTurno = 0;
}

int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }
bool Jardineiro::estaNoJardim() const { return noJardim; }
Ferramenta* Jardineiro::getFerramentaNaMao() const { return ferramentaNaMao; }
const std::vector<Ferramenta*>& Jardineiro::getFerramentas() const { return ferramentas; }
int Jardineiro::getMovimentosRestantes() const { return movimentosRestantes; }
