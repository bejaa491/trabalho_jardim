/**
 * ============================================================================
 *  CLASSE: Interface
 *  DESCRIÇÃO: Interface com utilizador - parsing e execução de comandos
 *  
 *  Responsabilidades:
 *    - Ler comandos do utilizador (stdin ou ficheiro)
 *    - Fazer parse de comandos com argumentos
 *    - Executar comandos e atualizar o Jardim
 *    - Fornecer feedback visual ao utilizador
 * ============================================================================
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "Jardim.h"
#include <string>

class Interface {
private:
    Jardim* jardim;                     /**< Instância do jardim a controlar */
    bool executando;                    /**< Flag para controlar loop principal */

public:
    Interface();
    ~Interface();
    
    // ========== ENTRADA PRINCIPAL ==========
    /**
     * Loop principal interativo.
     * Lê comandos do stdin e processa até comando "fim".
     * Mostra prompt ">" para cada entrada.
     */
    void executar();

    /**
     * Lê e executa comandos de um ficheiro de texto.
     * Ignora linhas vazias e comentários (começam com '#').
     * Exibe cada linha processada.
     * 
     * @param nomeFicheiro Caminho do ficheiro a executar
     */
    void executarFicheiro(const std::string& nomeFicheiro);
    
private:
    // ========== PARSING ==========
    /**
     * Processa uma linha de comando: faz parse, valida e executa.
     * 
     * @param linha String com comando e argumentos
     * @return true se processamento bem sucedido
     */
    bool processarComando(const std::string& linha);
    
    /**
     * Divide uma linha em tokens (palavras separadas por espaço).
     * Converte para minúsculas.
     * 
     * @param linha String a dividir
     * @param outCount [out] Número de tokens
     * @return Array de strings (caller liberta com delete[])
     */
    std::string* dividirComando(const std::string& linha, int& outCount); 
    
    /**
     * Valida se o comando é conhecido.
     * 
     * @param partes Array de tokens
     * @param n Número de tokens
     * @return true se comando válido
     */
    bool validarComando(const std::string* partes, int n);
    
    // ========== HANDLERS DE COMANDO ==========
    /**
     * Comando: jardim <linhas> <colunas>
     * Cria o jardim com dimensões especificadas.
     */
    bool comandoJardim(const std::string* partes, int n);
    
    /**
     * Comando: avanca [n]
     * Avança n instantes de simulação (padrão: 1).
     */
    bool comandoAvanca(const std::string* partes, int n);
    
    /**
     * Comando: lplantas
     * Lista todas as plantas do jardim.
     */
    bool comandoLPlantas(const std::string* partes, int n);
    
    /**
     * Comando: lplanta <posicao>
     * Mostra detalhes de uma planta em posição (ex: "bd").
     */
    bool comandoLPlanta(const std::string* partes, int n);
    
    /**
     * Comando: larea
     * Lista posições com plantas ou ferramentas.
     */
    bool comandoLArea(const std::string* partes, int n);
    
    /**
     * Comando: lsolo <posicao> [raio]
     * Mostra informações de solo com raio opcional.
     */
    bool comandoLSolo(const std::string* partes, int n);
    
    /**
     * Comando: lferr
     * Lista ferramentas do jardineiro.
     */
    bool comandoLFerr(const std::string* partes, int n);
    
    /**
     * Comando: colhe <posicao>
     * Colhe planta em posição especificada.
     */
    bool comandoColhe(const std::string* partes, int n);
    
    /**
     * Comando: planta <posicao> <tipo>
     * Planta novo tipo em posição (c/r/e/x).
     */
    bool comandoPlanta(const std::string* partes, int n);
    
    /**
     * Comando: larga
     * Jardineiro larga ferramenta.
     */
    bool comandoLarga(const std::string* partes, int n);
    
    /**
     * Comando: pega <numero_serie>
     * Jardineiro pega ferramenta por número de série.
     */
    bool comandoPega(const std::string* partes, int n);
    
    /**
     * Comando: compra <tipo>
     * Compra ferramenta (g/a/t/z).
     */
    bool comandoCompra(const std::string* partes, int n);
    
    /**
     * Comando: e, d, c, b
     * Move jardineiro em direção (esquerda, direita, cima, baixo).
     */
    bool comandoMovimento(const std::string* partes, int n);
    
    /**
     * Comando: entra <posicao>
     * Jardineiro entra no jardim em posição.
     */
    bool comandoEntra(const std::string* partes, int n);
    
    /**
     * Comando: sai
     * Jardineiro sai do jardim.
     */
    bool comandoSai(const std::string* partes, int n);
    
    /**
     * Comando: grava <nome>
     * Salva snapshot do estado com nome.
     */
    bool comandoGrava(const std::string* partes, int n);
    
    /**
     * Comando: recupera <nome>
     * Carrega snapshot previamente gravado.
     */
    bool comandoRecupera(const std::string* partes, int n);
    
    /**
     * Comando: apaga <nome>
     * Remove snapshot.
     */
    bool comandoApaga(const std::string* partes, int n);
    
    /**
     * Comando: executa <ficheiro>
     * Executa comandos de ficheiro de texto.
     */
    bool comandoExecuta(const std::string* partes, int n);
    
    /**
     * Comando: fim
     * Encerra o simulador de forma limpa.
     */
    bool comandoFim(const std::string* partes, int n);
    
    // ========== UTILITÁRIOS ==========
    /**
     * Converte posição em formato letra-letra (ex: "bd") para índices.
     * 
     * @param pos String de posição (ex: "bd")
     * @param linha [out] Índice de linha
     * @param coluna [out] Índice de coluna
     * @return true se conversão bem sucedida
     */
    bool converterPosicao(const std::string& pos, int& linha, int& coluna);
    
    /**
     * Tenta converter string para número inteiro.
     * 
     * @param str String a converter
     * @param numero [out] Número convertido
     * @return true se conversão bem sucedida
     */
    bool eNumero(const std::string& str, int& numero);
    
    /**
     * Exibe mensagem de erro em vermelho (se suportado).
     * 
     * @param mensagem Texto a exibir
     */
    void mostrarErro(const std::string& mensagem);
    
    /**
     * Exibe mensagem de sucesso em verde (se suportado).
     * 
     * @param mensagem Texto a exibir
     */
    void mostrarSucesso(const std::string& mensagem);
};

#endif