#include "../include/huffman.hpp"

/**
 * @brief
 * Construtor para árvore de huffman.
 * Inicializa todos os atributos com valores nulos equivalentes ao tipo.
 */
huffman::huffman() : indice(INDICE_NULO), frequencia(ZERO_FREQUENCIA), simbolo(STRING_VAZIA), esq(nullptr), dir(nullptr) {}

/**
 * @brief Construtor para árvore de huffman.
 * @param indice valor inicial de índice.
 * @param frequencia valor inicial de frequência.
 * @param esq valor inicial do nó esquerdo (nulo caso não tenha argumentos).
 * @param dir valor inicial do nó direito (nulo caso não tenha argumentos).
 */
huffman::huffman(int indice, int frequencia, const std::string& simbolo, huffman* esq=nullptr, huffman* dir=nullptr)
{
    this->indice = indice;
    this->frequencia = frequencia;
    this->simbolo = simbolo;
    this->esq = esq;
    this->dir = dir;
}

/**
 * @brief Construtor para árvore de huffman.
 * @param esq nó esquerdo da árvore.
 * @param dir nó direito da árvore.
 */
huffman::huffman(huffman* esq, huffman* dir)
{
    this->frequencia = esq->frequencia + dir->frequencia;
    this->indice = std::min(esq->indice, dir->indice);
    this->simbolo = STRING_VAZIA;
    this->esq = esq;
    this->dir = dir;
}

/**
 * @brief Função membro para verificar de um nó huffman é folha.
 * @return Retorna true se folha.
 */
bool huffman::eh_folha() const
{
    return (esq == nullptr && dir == nullptr);
}

/**
 * @brief Função membro para recuperar nó esquerdo.
 * @return Retorna o nó esquerdo.
 */
huffman* huffman::get_esq() const
{
    return esq;
}

/**
 * @brief Função membro para recuperar nó direito.
 * @return Retorna o nó direito.
 */
huffman* huffman::get_dir() const
{
    return dir;
}

/**
 * @brief Função membro para recuperar símbolo.
 * @return Retorna símbolo.
 */
std::string huffman::get_simbolo() const
{
    return simbolo;
}

/**
 * @brief Função membro para recuperar frequência.
 * @return Retorna frequência.
 */
int huffman::get_freq() const
{
    return frequencia;
}

/**
 * @brief Função membro para recuperar índice.
 * @return Retorna índice.
 */
int huffman::get_indice() const
{
    return indice;
}

