#ifndef APLICACAO_ALGORITMO_HUFFMAN_H_INCLUDED
#define APLICACAO_ALGORITMO_HUFFMAN_H_INCLUDED

#include <clocale>
#include <chrono>
#include <stdexcept>
#include "huffman.hpp"

/**
 * @class aplicacao Classe para algoritmo da árvore de huffman.
 */
class aplicacao
{
private:
    huffman* raiz;
    std::map<std::string, int> frequencias;
    std::map<std::string, std::string> codigos;

    /**
     * @brief Função membro para construir árvore de huffman.
     * @param frequencias mapa de símbolo para frequência de caracteres ou palavras.
     * @return Retorna um ponteiro para raiz.
     */
    huffman* construir_arvore(const std::map<std::string, int>&);

    /**
     * @brief Função membro para preencher o mapa de bits com código binário de forma recursiva.
     * @param raiz raiz da árvore de huffman.
     * @param caminho atributo para caminho que dita um símbolo.
     * @param codigos mapa a ser preenchido.
     */
    void gerar_codigo(huffman*, std::string, std::map<std::string, std::string>&);

    /**
     * @brief Função membro para percorrer o texto e extrair tokens.
     * @param texto texto a ser percorrido.
     * @return retorna um vetor de tokens.
     */
    std::vector<std::string> extrair_tokens(const std::string&);

    /**
     * @brief Função membro para escrever o número de símbolos, para cada símbolo o tamanho, a string e a frequência.
     * @param saida arquivo de saída.
     * @param frequencias mapa de frequência dos símbolos.
     */
    void escrever_cabecalho(std::ofstream&, const std::map<std::string, int>&, uint64_t);

    /**
     * @brief Função membro para ler o cabeçalho com o número de símbolos, para cada símbolo o tamanho, a string e a frequência.
     * @param entrada arquivo de entrada.
     * @return Retorna o mapa de frequência dos símbolos.
     */
    std::map<std::string, int> ler_cabecalho(std::ifstream&, uint64_t&);

    /**
     * @brief Função membro para escrever os dados.
     * @param saida arquivo de saída.
     * @param texto
     * @param codigos código a ser escrito no arquivo.
     * @param modo_palavra caso caractere: percorre byte a byte e escreve os códigos, caso palavra: percorre os tokens e escreve os códigos.
     */
    void escrever_dados_compactados(std::ofstream&, const std::string&, const std::map<std::string, std::string>&, bool, uint64_t&);

    /**
     * @brief Função membro para percorrer a arvore e escrever a string original.
     * @param entrada arquivo de entrada.
     * @param raiz raiz da árvore de huffman.
     * @param total_bits total de bits contidos no arquivo.
     * @return Retorna a palavra original.
     */
    std::string ler_dados_descompactados(std::ifstream&, huffman*, uint64_t);

    /**
     * @struct comparadorNo Struct para comparar nós de árvore para fila de prioridade.
     */
    struct comparadorNo{
        bool operator()(const huffman* a, const huffman* b) const {
            if(a->get_freq() != b->get_freq()){
                return a->get_freq() > b->get_freq();
            }

            return a->get_indice() > b->get_indice();
        }
    };

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
     * @brief Função membro para compactar texto por caractere.
     * @param entrada nome do arquivo de entrada.
     * @param saida nome do arquivo de saída.
     */
    void compactar_caractere(const std::string&, const std::string&);

    /**
     * @brief Função membro para descompactar texto por caractere.
     * @param entrada nome do arquivo de entrada.
     * @param saida nome do arquivo de saída.
     */
    void descompactar_caractere(const std::string&, const std::string&);

    /**
     * @brief Função membro para compactar texto por palavra.
     * @param entrada nome do arquivo de entrada.
     * @param saida nome do arquivo de saída.
     */
    void compactar_palavra(const std::string&, const std::string&);

    /**
     * @brief Função membro para descompactar texto por palavra.
     * @param entrada nome do arquivo de entrada.
     * @param saida nome do arquivo de saída.
     */
    void descompactar_palavra(const std::string&, const std::string&);

    /**
     * @brief Função membro para realizar a leitura de arquivo texto.
     * @param nome_arquivo nome do arquivo alvo.
     * @return Retorna o texto extraído do arquivo lido.
     */
    std::string ler_arquivo(std::string);
};

#endif
