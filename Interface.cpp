#include "Interface.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

Interface::Interface() : jardim(nullptr), executando(true) {
    jardim = new Jardim();
}

Interface::~Interface() {
    delete jardim;
}

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

std::vector<std::string> Interface::dividirComando(const std::string& linha) {
    std::vector<std::string> partes;
    std::istringstream iss(linha);
    std::string palavra;
    
    while (iss >> palavra) {
        // Converter para minúsculas
        std::transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
        partes.push_back(palavra);
    }
    
    return partes;
}

bool Interface::processarComando(const std::string& linha) {
    std::vector<std::string> partes = dividirComando(linha);
    
    if (partes.empty()) {
        return false;
    }
    
    std::string comando = partes[0];
    
    // Comandos que podem ser executados antes de criar o jardim
    if (comando == "jardim") {
        return comandoJardim(partes);
    }
    if (comando == "executa") {
        return comandoExecuta(partes);
    }
    if (comando == "fim") {
        return comandoFim(partes);
    }
    
    // Verificar se o jardim foi criado
    if (!jardim->foiCriado()) {
        mostrarErro("Jardim ainda nao foi criado. Use 'jardim <linhas> <colunas>'");
        return false;
    }
    
    // Processar outros comandos
    if (comando == "avanca") return comandoAvanca(partes);
    if (comando == "lplantas") return comandoLPlantas(partes);
    if (comando == "lplanta") return comandoLPlanta(partes);
    if (comando == "larea") return comandoLArea(partes);
    if (comando == "lsolo") return comandoLSolo(partes);
    if (comando == "lferr") return comandoLFerr(partes);
    if (comando == "colhe") return comandoColhe(partes);
    if (comando == "planta") return comandoPlanta(partes);
    if (comando == "larga") return comandoLarga(partes);
    if (comando == "pega") return comandoPega(partes);
    if (comando == "compra") return comandoCompra(partes);
    if (comando == "e" || comando == "d" || comando == "c" || comando == "b") {
        return comandoMovimento(partes);
    }
    if (comando == "entra") return comandoEntra(partes);
    if (comando == "sai") return comandoSai(partes);
    if (comando == "grava") return comandoGrava(partes);
    if (comando == "recupera") return comandoRecupera(partes);
    if (comando == "apaga") return comandoApaga(partes);
    
    mostrarErro("Comando desconhecido: " + comando);
    return false;
}

// ========== IMPLEMENTAÇÃO DOS COMANDOS ==========

bool Interface::comandoJardim(const std::vector<std::string>& partes) {
    if (partes.size() != 3) {
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

bool Interface::comandoAvanca(const std::vector<std::string>& partes) {
    int n = 1;
    
    if (partes.size() > 2) {
        mostrarErro("Sintaxe: avanca [n]");
        return false;
    }
    
    if (partes.size() == 2) {
        if (!eNumero(partes[1], n) || n < 1) {
            mostrarErro("Numero de instantes deve ser inteiro positivo");
            return false;
        }
    }
    
    jardim->avancarTempo(n);
    jardim->imprimir();
    return true;
}

bool Interface::comandoLPlantas(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
        mostrarErro("Sintaxe: lplantas (sem parametros)");
        return false;
    }
    
    jardim->listarPlantas();
    return true;
}

bool Interface::comandoLPlanta(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoLArea(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
        mostrarErro("Sintaxe: larea (sem parametros)");
        return false;
    }
    
    jardim->listarArea();
    return true;
}

bool Interface::comandoLSolo(const std::vector<std::string>& partes) {
    if (partes.size() < 2 || partes.size() > 3) {
        mostrarErro("Sintaxe: lsolo <posicao> [raio]");
        return false;
    }
    
    int linha, coluna, raio = 0;
    if (!converterPosicao(partes[1], linha, coluna)) {
        return false;
    }
    
    if (partes.size() == 3) {
        if (!eNumero(partes[2], raio) || raio < 0) {
            mostrarErro("Raio deve ser inteiro nao-negativo");
            return false;
        }
    }
    
    jardim->listarSolo(linha, coluna, raio);
    return true;
}

bool Interface::comandoLFerr(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
        mostrarErro("Sintaxe: lferr (sem parametros)");
        return false;
    }
    
    jardim->listarFerramentas();
    return true;
}

bool Interface::comandoColhe(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoPlanta(const std::vector<std::string>& partes) {
    if (partes.size() != 3) {
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

bool Interface::comandoLarga(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
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

bool Interface::comandoExecuta(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
        mostrarErro("Sintaxe: executa <nome-do-ficheiro>");
        return false;
    }
    if (partes[1].empty()) {
        mostrarErro("Nome do ficheiro vazio");
        return false;
    }
    executarFicheiro(partes[1]);
    return true;
}

bool Interface::comandoFim(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
        mostrarErro("Sintaxe: fim (sem parametros)");
        return false;
    }
    mostrarSucesso("Encerrando simulador...");
    executando = false;
    return true;
}

bool Interface::comandoPega(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoCompra(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoMovimento(const std::vector<std::string>& partes) {
    // comandos: e | d | c | b  [n]
    if (partes.size() > 2) {
        mostrarErro("Sintaxe: <e|d|c|b> [n]");
        return false;
    }
    std::string cmd = partes[0];
    if (cmd.size() != 1 || (cmd != "e" && cmd != "d" && cmd != "c" && cmd != "b")) {
        mostrarErro("Direcao invalida. Use e, d, c ou b");
        return false;
    }
    if (partes.size() == 2) {
        int passos;
        if (!eNumero(partes[1], passos) || passos < 1) {
            mostrarErro("Numero de passos deve ser inteiro positivo");
            return false;
        }
    }
    mostrarSucesso("Comando de movimento validado (stub)");
    return true;
}

bool Interface::comandoEntra(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoSai(const std::vector<std::string>& partes) {
    if (partes.size() != 1) {
        mostrarErro("Sintaxe: sai (sem parametros)");
        return false;
    }
    mostrarSucesso("Comando 'sai' validado (stub)");
    return true;
}

bool Interface::comandoGrava(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoRecupera(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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

bool Interface::comandoApaga(const std::vector<std::string>& partes) {
    if (partes.size() != 2) {
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
