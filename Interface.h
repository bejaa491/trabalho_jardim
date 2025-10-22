#ifndef INTERFACE_H
#define INTERFACE_H

#include "Jardim.h"
#include <string>
#include <vector>

class Interface {
private:
    Jardim* jardim;
    bool executando;

public:
    Interface();
    ~Interface();
    
    void executar();
    void executarFicheiro(const std::string& nomeFicheiro);
    
private:
    bool processarComando(const std::string& linha);
    std::vector<std::string> dividirComando(const std::string& linha);
    bool validarComando(const std::vector<std::string>& partes);
    
    // Comandos específicos
    bool comandoJardim(const std::vector<std::string>& partes);
    bool comandoAvanca(const std::vector<std::string>& partes);
    bool comandoLPlantas(const std::vector<std::string>& partes);
    bool comandoLPlanta(const std::vector<std::string>& partes);
    bool comandoLArea(const std::vector<std::string>& partes);
    bool comandoLSolo(const std::vector<std::string>& partes);
    bool comandoLFerr(const std::vector<std::string>& partes);
    bool comandoColhe(const std::vector<std::string>& partes);
    bool comandoPlanta(const std::vector<std::string>& partes);
    bool comandoLarga(const std::vector<std::string>& partes);
    bool comandoPega(const std::vector<std::string>& partes);
    bool comandoCompra(const std::vector<std::string>& partes);
    bool comandoMovimento(const std::vector<std::string>& partes);
    bool comandoEntra(const std::vector<std::string>& partes);
    bool comandoSai(const std::vector<std::string>& partes);
    bool comandoGrava(const std::vector<std::string>& partes);
    bool comandoRecupera(const std::vector<std::string>& partes);
    bool comandoApaga(const std::vector<std::string>& partes);
    bool comandoExecuta(const std::vector<std::string>& partes);
    bool comandoFim(const std::vector<std::string>& partes);
    
    // Utilidades
    bool converterPosicao(const std::string& pos, int& linha, int& coluna);
    bool eNumero(const std::string& str, int& numero);
    void mostrarErro(const std::string& mensagem);
    void mostrarSucesso(const std::string& mensagem);
};

#endif