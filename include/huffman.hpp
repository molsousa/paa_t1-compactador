#ifndef ALGORITMO_HUFFMAN_H_INCLUDED
#define ALGORITMO_HUFFMAN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

const int ZERO_FREQUENCIA {0};
const int INDICE_NULO {-1};

class huffman
{
private:
    int indice;
    int frequencia;
    huffman* esq;
    huffman* dir;

public:
    huffman();

    huffman(int, int, huffman*, huffman*);
};

class aplicacao
{
private:

public:
    void menu();

    std::string ler_arquivo(std::string);

    void escrever_arquivo(std::string&);
};

#endif
