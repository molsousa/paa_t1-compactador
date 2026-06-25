#include "../include/bits.hpp"

/**
 * @brief Construtor para classe escrita_bit.
 * @param saida arquivo de saída.
 */
escrita_bit::escrita_bit(std::ofstream& saida) : saida(saida), buffer(0), contador(0) {}

/**
 * @brief Função membro para escrever um bit.
 * @param bit inteiro contendo um unico bit.
 */
void escrita_bit::escrever_bit(int bit)
{
    if(bit != 0 && bit != 1){
        throw std::invalid_argument("Bit inválido");
    }

    buffer = (buffer << 1) | (bit & 1);
    contador++;

    if(contador == 8){
        saida.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
        contador = 0;
        buffer = 0;
    }
}

/**
 * @brief Função membro para escrever a sequência de bits.
 * @param codigo string contendo a sequência de bits
 */
void escrita_bit::escrever_bits(const std::string& codigo)
{
    for(char c : codigo){
        if(c == '0'){
            escrever_bit(0);
        }
        else if(c == '1'){
            escrever_bit(1);
        }
        else{
            throw std::invalid_argument("código contém caractere inválido");
        }
    }
}

/**
 * @brief Função membro para escrever o último byte, preenchendo com zeros.
 */
void escrita_bit::flush()
{
    if(contador > 0){
        buffer = buffer << (8 - contador);
        saida.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
        contador = 0;
        buffer = 0;
    }
}

/**
 * @brief Construtor para classe leitura_bit.
 * @param entrada arquivo de entrada.
 */
leitura_bit::leitura_bit(std::ifstream& entrada) : entrada(entrada), buffer(0), contador(0) {}

/**
 * @brief Função membro para leitura de bits.
 * @return Retorna 0, 1 ou -1 (caso esteja no final do arquivo).
 */
int leitura_bit::ler_bit()
{
    if(contador == 0){
        entrada.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        if(entrada.gcount() == 0){
            return -1;
        }
        contador = 8;
    }

    contador--;
    int bit = (buffer >> contador) & 1;

    return bit;
}

/**
 * @brief Função membro para indicar se está no final de um arquivo.
 * @return Retorna true caso esteja ao final do arquivo.
 */
bool leitura_bit::fim()
{
    return (entrada.eof() && contador == 0);
}
