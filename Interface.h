#ifndef INTERFACE_H
#define INTERFACE_H

#include "Jardim.h"
#include <string>


class Interface {
private:
    Jardim* jardim;
    bool executando;

public:
    Interface();
    ~Interface();
    
    // Loop principal de leitura de comandos do utilizador (stdin).
    void executar();

    // Executa comandos lidos de um ficheiro texto (linha por linha).
    void executarFicheiro(const std::string& nomeFicheiro);
    
private:
    bool processarComando(const std::string& linha);
    std::string* dividirComando(const std::string& linha, int& outCount); 
    bool validarComando(const std::string* partes, int n);
    
    // Comandos específicos (recebem array de tokens + numero de tokens)
    bool comandoJardim(const std::string* partes, int n);
    bool comandoAvanca(const std::string* partes, int n);
    bool comandoLPlantas(const std::string* partes, int n);
    bool comandoLPlanta(const std::string* partes, int n);
    bool comandoLArea(const std::string* partes, int n);
    bool comandoLSolo(const std::string* partes, int n);
    bool comandoLFerr(const std::string* partes, int n);
    bool comandoColhe(const std::string* partes, int n);
    bool comandoPlanta(const std::string* partes, int n);
    bool comandoLarga(const std::string* partes, int n);
    bool comandoPega(const std::string* partes, int n);
    bool comandoCompra(const std::string* partes, int n);
    bool comandoMovimento(const std::string* partes, int n);
    bool comandoEntra(const std::string* partes, int n);
    bool comandoSai(const std::string* partes, int n);
    bool comandoGrava(const std::string* partes, int n);
    bool comandoRecupera(const std::string* partes, int n);
    bool comandoApaga(const std::string* partes, int n);
    bool comandoExecuta(const std::string* partes, int n);
    bool comandoFim(const std::string* partes, int n);
    
    // Utilidades
    bool converterPosicao(const std::string& pos, int& linha, int& coluna);
    bool eNumero(const std::string& str, int& numero);
    void mostrarErro(const std::string& mensagem);
    void mostrarSucesso(const std::string& mensagem);
};

#endif