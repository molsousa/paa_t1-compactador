#ifndef ALGORITMO_HUFFMAN_H_INCLUDED
#define ALGORITMO_HUFFMAN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>

#include <bitset>
#include <cstdint>
#include <cctype>
#include <cstring>
#include <algorithm>

/// Definição de constante para frequência zero.
const int ZERO_FREQUENCIA {0};
/// Definição de constante para índice nulo.
const int INDICE_NULO {-1};
/// Definição de constante para string vazia.
const std::string STRING_VAZIA {""};

/**
 * @class huffman Classe para criação de árvore de huffman.
 */
class huffman
{
private:
    int indice;
    int frequencia;
    std::string simbolo;
    huffman* esq;
    huffman* dir;

public:
    /**
     * @brief
     * Construtor para árvore de huffman.
     * Inicializa todos os atributos com valores nulos equivalentes ao tipo.
     */
    huffman();

    /**
     * @brief Construtor para árvore de huffman.
     * @param indice valor inicial de índice.
     * @param frequencia valor inicial de frequência.
     * @param esq valor inicial do nó esquerdo (nulo caso não tenha argumentos).
     * @param dir valor inicial do nó direito (nulo caso não tenha argumentos).
     */
    huffman(int, int, const std::string&, huffman*, huffman*);

    /**
     * @brief Construtor para árvore de huffman.
     * @param esq nó esquerdo da árvore.
     * @param dir nó direito da árvore.
     */
    huffman(huffman*, huffman*);

    /**
     * @brief Função membro para verificar de um nó huffman é folha.
     * @return Retorna true se folha.
     */
    bool eh_folha() const;

    /**
     * @brief Função membro para recuperar nó esquerdo.
     * @return Retorna o nó esquerdo.
     */
    huffman* get_esq() const;

    /**
     * @brief Função membro para recuperar nó direito.
     * @return Retorna o nó direito.
     */
    huffman* get_dir() const;

    /**
     * @brief Função membro para recuperar símbolo.
     * @return Retorna símbolo.
     */
    std::string get_simbolo() const;

    /**
     * @brief Função membro para recuperar frequência.
     * @return Retorna frequência.
     */
    int get_freq() const;

    /**
     * @brief Função membro para recuperar índice.
     * @return Retorna índice.
     */
    int get_indice() const;
};

#endif
