#ifndef MANIPULACAO_BITS_H_INCLUDED
#define MANIPULACAO_BITS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdint>

/**
 * @class escrita_bit Classe para encapsular a escrita de bits em arquivo binário.
 */
class escrita_bit
{
private:
    std::ofstream& saida;
    uint8_t buffer;
    int contador;

public:
    /**
     * @brief Construtor para classe escrita_bit.
     * @param saida arquivo de saída.
     */
    escrita_bit(std::ofstream&);

    /**
     * @brief Função membro para escrever um bit.
     * @param bit inteiro contendo um unico bit.
     */
    void escrever_bit(int);

    /**
     * @brief Função membro para escrever a sequência de bits.
     * @param codigo string contendo a sequência de bits
     */
    void escrever_bits(const std::string&);

    /**
     * @brief Função membro para escrever o último byte, preenchendo com zeros.
     */
    void flush();
};

/**
 * @class leitura_bit Classe para encapsular a leitura de bits em arquivo binário.
 */
class leitura_bit
{
    std::ifstream& entrada;
    uint8_t buffer;
    int contador;

public:
    /**
     * @brief Construtor para classe leitura_bit.
     * @param entrada arquivo de entrada.
     */
    leitura_bit(std::ifstream&);

    /**
     * @brief Função membro para leitura de bits.
     * @return Retorna 0, 1 ou -1 (caso esteja no final do arquivo).
     */
    int ler_bit();

    /**
     * @brief Função membro para indicar se está no final de um arquivo.
     * @return Retorna true caso esteja ao final do arquivo.
     */
    bool fim();
};

#endif
