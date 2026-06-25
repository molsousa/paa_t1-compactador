#include "../include/huffman.hpp"

huffman::huffman() : indice(INDICE_NULO), frequencia(ZERO_FREQUENCIA), simbolo(STRING_VAZIA), esq(nullptr), dir(nullptr) {}

huffman::huffman(int indice, int frequencia, const std::string& simbolo, huffman* esq=nullptr, huffman* dir=nullptr)
{
    this->indice = indice;
    this->frequencia = frequencia;
    this->simbolo = simbolo;
    this->esq = esq;
    this->dir = dir;
}

huffman::huffman(huffman* esq, huffman* dir)
{
    this->frequencia = esq->frequencia + dir->frequencia;
    this->indice = std::min(esq->indice, dir->indice);
    this->simbolo = STRING_VAZIA;
    this->esq = esq;
    this->dir = dir;
}

bool huffman::eh_folha() const
{
    return (esq == nullptr && dir == nullptr);
}

huffman* huffman::get_esq() const
{
    return esq;
}

huffman* huffman::get_dir() const
{
    return dir;
}

std::string huffman::get_simbolo() const
{
    return simbolo;
}

int huffman::get_freq() const
{
    return frequencia;
}

int huffman::get_indice() const
{
    return indice;
}

