#ifndef ALGORITMO_HUFFMAN_H_INCLUDED
#define ALGORITMO_HUFFMAN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <clocale>

/// Definição de constante para frequência zero.
const int ZERO_FREQUENCIA {0};
/// Definição de constante para índice nulo.
const int INDICE_NULO {-1};

/**
 * @class huffman Classe para criação de árvore de huffman.
 */
class huffman
{
private:
    int indice;
    int frequencia;
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
     * @param esq valor inicial do nó esquerdo (nulo caso não tenha argumentos)
     * @param dir valor inicial do nó direito (nulo caso não tenha argumentos)
     */
    huffman(int, int, huffman*, huffman*);
};

/**
 * @class aplicacao Classe para algoritmo da árvore de huffman.
 */
class aplicacao
{
private:
    // std::unordered_set<std::string, int> frequencia_caracteres;

public:
    /**
     * @brief Contrutor para algoritmo de huffman.
     * Inicializa o locale para leitura de caracteres unicode.
     */
    aplicacao();

    /**
     * @brief Função membro para acessar menu de opções.
     */
    void menu();

    /**
     * @brief Função membro para realizar a leitura de arquivo texto.
     * @param nome_arquivo nome do arquivo alvo.
     * @return Retorna o texto extraído do arquivo lido.
     */
    std::string ler_arquivo(std::string);

    /**
     * @brief Função membro para contar caracteres em arquivo de texto.
     * @param texto texto extraído do arquivo de texto lido.
     * @return Retorna uma coleção com os caracteres dentro do arquivo.
     */
    std::unordered_map<int, int> contar_caracteres(std::string);

    void escrever_arquivo(std::string&);
};

#endif
