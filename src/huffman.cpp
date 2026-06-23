#include "../include/huffman.hpp"

/*
 * em qualquer uma das op¸c˜oes deve ser permitido o usu´ario informar o arquivo que deseja compactar ou descompactar, sendo gerado outro arquivo.
 *
 * considerar que todos os arquivos a serem compactados s˜ao do tipo texto na l´ıngua portuguesa, podendo
 t er caracteres acentuados (˜a, ˜o, ˆo, ¸c, ´a, `a, ...), de tamanho da ordem de megabytes.*
 *
 * na codifica¸c˜ao por caracter: criar uma codifica¸c˜ao de tamanho vari´avel usando o algoritmo de Huffman
 cl´assico.
 *
 * na codifica¸c˜ao por palavras: considerar cada palavra diferente do texto como um s´ımbolo, contar suas
 frequˆencias e gerar uma codifica¸c˜ao de Huffman para as palavras.
 *
 * criar estruturas de dados adequadas para representa¸c˜ao e armazenamento da codifica¸c˜ao no pr´oprio
 arquivo compactado tal que permita a opera¸c˜ao de descompress˜ao.
 *
 */

huffman::huffman()
{
    indice = INDICE_NULO;
    frequencia = ZERO_FREQUENCIA;
    esq = dir = nullptr;
}

huffman::huffman(int indice, int frequencia, huffman* esq=nullptr, huffman* dir=nullptr)
{
    this->indice = indice;
    this->frequencia = frequencia;
    this->esq = esq;
    this->dir = dir;
}

aplicacao::aplicacao()
{
    setlocale(LC_ALL, "");
}

void aplicacao::menu()
{
    std::cout << "|| ===== Algoritmo árvore huffman ====== ||\n";
    std::cout << "|| 1 - Compactar arquivo (caractere)     ||\n";
    std::cout << "|| 2 - Descompactar arquivo (caractere)  ||\n";
    std::cout << "|| 3 - Compactar arquivo (palavra)       ||\n";
    std::cout << "|| 4 - Descompactar arquivo (palavra)    ||\n";
    std::cout << "|| ===================================== ||\n";
    std::cout << "Insira uma opção: ";
}

std::string aplicacao::ler_arquivo(std::string nome_arquivo)
{
    std::string buffer;
    std::string texto;
    std::ifstream ifile(nome_arquivo);

    if(ifile.is_open()){
        while(std::getline(ifile, buffer)){
            texto.append(buffer);
        }

        ifile.close();
    }
    else{
        std::cerr << "Erro ao abrir arquivo\n";
    }

    return texto;
}

std::unordered_map<int, int> aplicacao::contar_caracteres(std::string texto)
{
    std::unordered_map<int, int> frequencia_caracteres;

    for(int c : texto){
        frequencia_caracteres[c]++;
    }

    return frequencia_caracteres;
}


