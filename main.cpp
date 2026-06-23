#include <iostream>
#include "include/huffman.hpp"

int main()
{
    // debug

    aplicacao app;

    std::unordered_map<int, int> frequencia;
    std::string texto;

    texto = app.ler_arquivo("arq_teste.txt");

    frequencia = app.contar_caracteres(texto);

    for(auto& par : frequencia){
        std::wcout << (char) par.first << ":" << par.second << "\n";
    }

    return 0;
}
