#include "Interface.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

// Construtor / destrutor simples.
Interface::Interface() : jardim(nullptr), executando(true) {
    jardim = new Jardim();
}

Interface::~Interface() {
    delete jardim;
}

// Loop principal: lê do stdin e processa linhas.
void Interface::executar() {
    std::string linha;
    std::cout << "=== Simulador de Jardim - POO 2025/2026 ===\n";
    std::cout << "Digite 'jardim <linhas> <colunas>' para comecar\n";
    std::cout << "Digite 'fim' para sair\n\n";
    
    while (executando) {
        std::cout << "> ";
        std::getline(std::cin, linha);
        
        if (!linha.empty()) {
            processarComando(linha);
        }
    }
}

// Executa ficheiro de comandos (linha-a-linha). Ignora comentários '#'.

void Interface::executarFicheiro(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro);
    
    if (!ficheiro.is_open()) {
        mostrarErro("Nao foi possivel abrir o ficheiro: " + nomeFicheiro);
        return;
    }
    
    std::string linha;
    int numLinha = 0;
    
    while (std::getline(ficheiro, linha)) {
        numLinha++;
        if (!linha.empty() && linha[0] != '#') { // Ignorar linhas vazias e comentários
            std::cout << "[Ficheiro linha " << numLinha << "] " << linha << "\n";
            processarComando(linha);
        }
    }
    
    ficheiro.close();
    mostrarSucesso("Ficheiro executado com sucesso");
}

// Tokeniza linha em std::string[] (alocado com new[]). outCount recebe numero de tokens.

std::string* Interface::dividirComando(const std::string& linha, int& outCount) {
    outCount = 0;
    std::istringstream issCount(linha);
    std::string palavra;
    while (issCount >> palavra) outCount++;
    if (outCount == 0) return nullptr;

    std::string* partes = new std::string[outCount];
    std::istringstream issFill(linha);
    int idx = 0;
    while (issFill >> palavra) {
        std::transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
        partes[idx++] = palavra;
    }
    return partes;
}

// Dispatcher de comandos; garante delete[] do array de tokens.

bool Interface::processarComando(const std::string& linha) {
    int n = 0;
    std::string* partes = dividirComando(linha, n);
    if (n == 0 || partes == nullptr) {
        delete[] partes;
        return false;
    }

    std::string comando = partes[0];
    bool res = false;

    // Comandos permitidos antes de criar jardim
    if (comando == "jardim") { res = comandoJardim(partes, n); delete[] partes; return res; }
    if (comando == "executa") { res = comandoExecuta(partes, n); delete[] partes; return res; }
    if (comando == "fim") { res = comandoFim(partes, n); delete[] partes; return res; }

    // Verifica jardim criado
    if (!jardim->foiCriado()) {
        mostrarErro("Jardim ainda nao foi criado. Use 'jardim <linhas> <colunas>'");
        delete[] partes;
        return false;
    }

    // Outros comandos
    if (comando == "avanca") res = comandoAvanca(partes, n);
    else if (comando == "lplantas") res = comandoLPlantas(partes, n);
    else if (comando == "lplanta") res = comandoLPlanta(partes, n);
    else if (comando == "larea") res = comandoLArea(partes, n);
    else if (comando == "lsolo") res = comandoLSolo(partes, n);
    else if (comando == "lferr") res = comandoLFerr(partes, n);
    else if (comando == "colhe") res = comandoColhe(partes, n);
    else if (comando == "planta") res = comandoPlanta(partes, n);
    else if (comando == "larga") res = comandoLarga(partes, n);
    else if (comando == "pega") res = comandoPega(partes, n);
    else if (comando == "compra") res = comandoCompra(partes, n);
    else if (comando == "e" || comando == "d" || comando == "c" || comando == "b") res = comandoMovimento(partes, n);
    else if (comando == "entra") res = comandoEntra(partes, n);
    else if (comando == "sai") res = comandoSai(partes, n);
    else if (comando == "grava") res = comandoGrava(partes, n);
    else if (comando == "recupera") res = comandoRecupera(partes, n);
    else if (comando == "apaga") res = comandoApaga(partes, n);
    else {
        mostrarErro("Comando desconhecido: " + comando);
        res = false;
    }

    delete[] partes;
    return res;
}

// ========== IMPLEMENTAÇÃO DOS COMANDOS (comentários curtos) ==========

// jardim: cria grelha
bool Interface::comandoJardim(const std::string* partes, int n) {
    if (n != 3) {
        mostrarErro("Sintaxe: jardim <linhas> <colunas>");
        return false;
    }
    
    int linhas, colunas;
    if (!eNumero(partes[1], linhas) || !eNumero(partes[2], colunas)) {
        mostrarErro("Linhas e colunas devem ser numeros inteiros");
        return false;
    }
    
    if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
        mostrarErro("Dimensoes devem estar entre 1 e 26");
        return false;
    }
    
    if (jardim->foiCriado()) {
        mostrarErro("Jardim ja foi criado");
        return false;
    }
    
    if (jardim->criar(linhas, colunas)) {
        mostrarSucesso("Jardim criado com " + std::to_string(linhas) + "x" + std::to_string(colunas));
        jardim->imprimir();
        return true;
    }
    
    return false;
}

// avanca: avança instantes
bool Interface::comandoAvanca(const std::string* partes, int n) {
    int iter = 1;

    if (n > 2) {
        mostrarErro("Sintaxe: avanca [n]");
        return false;
    }

    if (n == 2) {
        if (!eNumero(partes[1], iter) || iter < 1) {
            mostrarErro("Numero de instantes deve ser inteiro positivo");
            return false;
        }
    }

    jardim->avancarTempo(iter);
    jardim->imprimir();
    return true;
}

// lplantas: lista plantas
bool Interface::comandoLPlantas(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: lplantas (sem parametros)");
        return false;
    }
    jardim->listarPlantas();
    return true;
}

// lplanta: detalhes de uma planta
bool Interface::comandoLPlanta(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: lplanta <posicao>");
        return false;
    }
    int linha, coluna;
    if (!converterPosicao(partes[1], linha, coluna)) {
        return false;
    }
    jardim->listarPlanta(linha, coluna);
    return true;
}

// larea: imprime area
bool Interface::comandoLArea(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: larea (sem parametros)");
        return false;
    }
    jardim->listarArea();
    return true;
}

// lsolo: informa solo posicao/raio
bool Interface::comandoLSolo(const std::string* partes, int n) {
    if (n < 2 || n > 3) {
        mostrarErro("Sintaxe: lsolo <posicao> [raio]");
        return false;
    }
    int linha, coluna, raio = 0;
    if (!converterPosicao(partes[1], linha, coluna)) {
        return false;
    }
    if (n == 3) {
        if (!eNumero(partes[2], raio) || raio < 0) {
            mostrarErro("Raio deve ser inteiro nao-negativo");
            return false;
        }
    }
    jardim->listarSolo(linha, coluna, raio);
    return true;
}

// lferr: lista ferramentas
bool Interface::comandoLFerr(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: lferr (sem parametros)");
        return false;
    }
    jardim->listarFerramentas();
    return true;
}

// colhe: colher planta
bool Interface::comandoColhe(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: colhe <posicao>");
        return false;
    }
    int linha, coluna;
    if (!converterPosicao(partes[1], linha, coluna)) {
        return false;
    }
    if (jardim->colherPlanta(linha, coluna)) {
        jardim->imprimir();
        return true;
    }
    return false;
}

// planta: plantar tipo na posicao
bool Interface::comandoPlanta(const std::string* partes, int n) {
    if (n != 3) {
        mostrarErro("Sintaxe: planta <posicao> <tipo>");
        return false;
    }
    int linha, coluna;
    if (!converterPosicao(partes[1], linha, coluna)) {
        return false;
    }
    if (partes[2].length() != 1) {
        mostrarErro("Tipo deve ser um caracter: c, r, e, ou x");
        return false;
    }
    char tipo = partes[2][0];
    if (tipo != 'c' && tipo != 'r' && tipo != 'e' && tipo != 'x') {
        mostrarErro("Tipo invalido. Use: c (cacto), r (roseira), e (erva), x (exotica)");
        return false;
    }
    if (jardim->plantarPlanta(linha, coluna, tipo)) {
        jardim->imprimir();
        return true;
    }
    return false;
}

// larga: larga ferramenta
bool Interface::comandoLarga(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: larga (sem parametros)");
        return false;
    }
    if (jardim->jardineirolLarga()) {
        mostrarSucesso("Ferramenta largada com sucesso");
        jardim->imprimir();
        return true;
    }
    mostrarErro("Nao ha ferramenta para largar");
    return false;
}

// Utilitários: mensagens e conversões curtas.
void Interface::mostrarErro(const std::string& mensagem) {
    std::cout << "[ERRO] " << mensagem << std::endl;
}

void Interface::mostrarSucesso(const std::string& mensagem) {
    std::cout << "[OK] " << mensagem << std::endl;
}

bool Interface::eNumero(const std::string& str, int& numero) {
    try {
        numero = std::stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool Interface::converterPosicao(const std::string& pos, int& linha, int& coluna) {
    if (pos.size() != 2)
        return false;
    linha = pos[0] - 'a';
    coluna = pos[1] - 'a';
    return linha >= 0 && linha < 26 && coluna >= 0 && coluna < 26;
}

// executa: executa ficheiro
bool Interface::comandoExecuta(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: executa <nome-do-ficheiro>");
        return false;
    }
    executarFicheiro(partes[1]);
    return true;
}

// fim: encerra simulador
bool Interface::comandoFim(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: fim (sem parametros)");
        return false;
    }
    mostrarSucesso("Encerrando simulador...");
    executando = false;
    return true;
}

// pega: validar posicao para pegar
bool Interface::comandoPega(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: pega <posicao>");
        return false;
    }
    int linha, coluna;
    if (!converterPosicao(partes[1], linha, coluna)) {
        mostrarErro("Posicao invalida. Use formato: <letra><letra> (a..z)(a..z)");
        return false;
    }
    mostrarSucesso("Comando 'pega' validado (stub)");
    return true;
}

// compra: validar tipo
bool Interface::comandoCompra(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: compra <tipo>");
        return false;
    }
    if (partes[1].empty()) {
        mostrarErro("Tipo invalido");
        return false;
    }
    mostrarSucesso("Comando 'compra' validado (stub)");
    return true;
}

// movimento: valida direcao e passos
bool Interface::comandoMovimento(const std::string* partes, int n) {
    // comandos: e | d | c | b  [n]
    if (n > 2) {
        mostrarErro("Sintaxe: <e|d|c|b> [n]");
        return false;
    }
    std::string cmd = partes[0];
    if (cmd.size() != 1 || (cmd != "e" && cmd != "d" && cmd != "c" && cmd != "b")) {
        mostrarErro("Direcao invalida. Use e, d, c ou b");
        return false;
    }
    if (n == 2) {
        int passos;
        if (!eNumero(partes[1], passos) || passos < 1) {
            mostrarErro("Numero de passos deve ser inteiro positivo");
            return false;
        }
    }
    mostrarSucesso("Comando de movimento validado (stub)");
    return true;
}

// entra: valida posicao e regista entrada
bool Interface::comandoEntra(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: entra <posicao>");
        return false;
    }
    int linha, coluna;
    if (!converterPosicao(partes[1], linha, coluna)) {
        mostrarErro("Posicao invalida. Use formato: <letra><letra> (a..z)(a..z)");
        return false;
    }
    mostrarSucesso("Comando 'entra' validado (stub)");
    return true;
}

// sai: valida saída
bool Interface::comandoSai(const std::string* partes, int n) {
    if (n != 1) {
        mostrarErro("Sintaxe: sai (sem parametros)");
        return false;
    }
    mostrarSucesso("Comando 'sai' validado (stub)");
    return true;
}

// grava/recupera/apaga: valida nomes de ficheiro
bool Interface::comandoGrava(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: grava <nome-do-ficheiro>");
        return false;
    }
    if (partes[1].empty()) {
        mostrarErro("Nome de ficheiro invalido");
        return false;
    }
    mostrarSucesso("Comando 'grava' validado (stub)");
    return true;
}

bool Interface::comandoRecupera(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: recupera <nome-do-ficheiro>");
        return false;
    }
    if (partes[1].empty()) {
        mostrarErro("Nome de ficheiro invalido");
        return false;
    }
    mostrarSucesso("Comando 'recupera' validado (stub)");
    return true;
}

bool Interface::comandoApaga(const std::string* partes, int n) {
    if (n != 2) {
        mostrarErro("Sintaxe: apaga <nome-do-ficheiro>");
        return false;
    }
    if (partes[1].empty()) {
        mostrarErro("Nome de ficheiro invalido");
        return false;
    }
    mostrarSucesso("Comando 'apaga' validado (stub)");
    return true;
}
