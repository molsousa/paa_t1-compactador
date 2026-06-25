#include "../include/aplicacao.hpp"
#include "../include/bits.hpp"

/**
 * @brief Contrutor para algoritmo de huffman.
 * Inicializa o locale para leitura de caracteres unicode.
 */
aplicacao::aplicacao() : raiz(nullptr)
{
    setlocale(LC_ALL, "");
    frequencias.clear();
    codigos.clear();
}

/**
 * @brief Função membro para realizar a leitura de arquivo texto.
 * @param nome_arquivo nome do arquivo alvo.
 * @return Retorna o texto extraído do arquivo lido.
 */
std::string aplicacao::ler_arquivo(std::string nome_arquivo)
{
    std::ifstream arquivo(nome_arquivo, std::ios::binary);
    std::streamsize tamanho;

    if(!arquivo.is_open()){
        throw std::runtime_error("Não foi possível abrir o arquivo "+ nome_arquivo);
    }
    else{
        arquivo.seekg(0, std::ios::end);
        tamanho = arquivo.tellg();
        arquivo.seekg(0, std::ios::beg);

        std::string texto(tamanho, '\0');
        arquivo.read(&texto[0], tamanho);

        if(arquivo.gcount() != tamanho){
            throw std::runtime_error("Erro na leiturado arquivo");
        }

        arquivo.close();

        return texto;
    }
}

/**
 * @brief Função membro para acessar menu de opções.
 */
void aplicacao::menu()
{
    int opcao;
    std::string entrada, saida;

    std::cout << "|| ===== Algoritmo árvore huffman ====== ||\n";
    std::cout << "|| 1 - Compactar arquivo (caractere)     ||\n";
    std::cout << "|| 2 - Descompactar arquivo (caractere)  ||\n";
    std::cout << "|| 3 - Compactar arquivo (palavra)       ||\n";
    std::cout << "|| 4 - Descompactar arquivo (palavra)    ||\n";
    std::cout << "|| ===================================== ||\n";
    std::cout << "Insira uma opção: ";

    std::cin >> opcao;

    std::cout << "Arquivo de entrada: ";
    std::cin >> entrada;

    std::cout << "Arquivo de saída: ";
    std::cin >> saida;

    auto inicio {std::chrono::high_resolution_clock::now()};

    try{
        switch(opcao){
            case 1:
                compactar_caractere(entrada, saida);
                break;
            case 2:
                descompactar_caractere(entrada, saida);
                break;
            case 3:
                compactar_palavra(entrada, saida);
                break;
            case 4:
                descompactar_caractere(entrada, saida);
                break;
            default:
                std::cout << "Opção inválida\n";
                return;
        }
    } catch(const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return;
    }
    auto fim {std::chrono::high_resolution_clock::now()};
    auto duracao {std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio)};

    std::cout << "Tempo de execução: " << duracao.count() << " ms\n";
}

/**
 * @brief Função membro para construir árvore de huffman.
 * @param frequencias mapa de símbolo para frequência de caracteres ou palavras.
 * @return Retorna um ponteiro para raiz.
 */
huffman* aplicacao::construir_arvore(const std::map<std::string, int>& frequencias)
{
    std::priority_queue<huffman*, std::vector<huffman*>, comparadorNo> fila;

    int proximo_indice = 0;

    for(const auto& par : frequencias){
        huffman* no = new huffman(proximo_indice++, par.second, par.first, nullptr, nullptr);
        fila.push(no);
    }

    while(fila.size() > 1){
        huffman* x {fila.top()};
        fila.pop();

        huffman* y {fila.top()};
        fila.pop();

        huffman* z = new huffman(x, y);
        fila.push(z);
    }

    huffman* raiz = fila.top();
    fila.pop();

    return raiz;
}

/**
 * @brief Função membro para preencher o mapa de bits com código binário de forma recursiva.
 * @param raiz raiz da árvore de huffman.
 * @param caminho atributo para caminho que dita um símbolo.
 * @param codigos mapa a ser preenchido.
 */
void aplicacao::gerar_codigo(huffman* no, std::string caminho, std::map<std::string, std::string>& codigos)
{
    if(no == nullptr){
        return;
    }
    if(no->eh_folha()){
        codigos[no->get_simbolo()] = caminho;
        return;
    }
    gerar_codigo(no->get_esq(), caminho+"0", codigos);
    gerar_codigo(no->get_dir(), caminho+"1", codigos);
}

/**
 * @brief Função membro para percorrer o texto e extrair tokens.
 * @param texto texto a ser percorrido.
 * @return retorna um vetor de tokens.
 */
std::vector<std::string> aplicacao::extrair_tokens(const std::string& texto)
{
    std::vector<std::string> tokens;
    size_t i {0};

    while(i < texto.size()){
        unsigned char c = static_cast<unsigned char>(texto[i]);

        if(std::isalpha(c)){
            std::string palavra;

            while(i < texto.size() && std::isalpha(static_cast<unsigned char>(texto[i]))){
                palavra += texto[i];
                i++;
            }
            tokens.push_back(palavra);
        }
        else{
            tokens.push_back(std::string(1, texto[i]));
            i++;
        }
    }

    return tokens;
}

/**
 * @brief Função membro para escrever o número de símbolos, para cada símbolo o tamanho, a string e a frequência.
 * @param saida arquivo de saída.
 * @param frequencias mapa de frequência dos símbolos.
 */
void aplicacao::escrever_cabecalho(std::ofstream& saida, const std::map<std::string, int>& frequencias, uint64_t total_bits)
{
    uint32_t num_simbolos = static_cast<uint32_t>(frequencias.size());
    saida.write(reinterpret_cast<const char*>(&total_bits), sizeof(total_bits));
    saida.write(reinterpret_cast<const char*>(&num_simbolos), sizeof(num_simbolos));

    for(const auto& par : frequencias){
        uint16_t tam = static_cast<uint16_t>(par.first.size());
        saida.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        saida.write(par.first.c_str(), tam);

        uint32_t freq = static_cast<uint32_t>(par.second);
        saida.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }
}

/**
 * @brief Função membro para ler o cabeçalho com o número de símbolos, para cada símbolo o tamanho, a string e a frequência.
 * @param entrada arquivo de entrada.
 * @return Retorna o mapa de frequência dos símbolos.
 */
std::map<std::string, int> aplicacao::ler_cabecalho(std::ifstream& entrada, uint64_t& total_bits)
{
    entrada.read(reinterpret_cast<char*>(&total_bits), sizeof(total_bits));
    uint32_t num_simbolos;
    entrada.read(reinterpret_cast<char*>(&num_simbolos), sizeof(num_simbolos));

    std::map<std::string, int> frequencias;
    for(uint32_t i {0}; i < num_simbolos; i++){
        uint16_t tam;
        entrada.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        std::string simbolo(tam, '\0');
        entrada.read(&simbolo[0], tam);
        uint32_t freq;
        entrada.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        frequencias[simbolo] = static_cast<int>(freq);
    }

    return frequencias;
}

/**
 * @brief Função membro para escrever os dados.
 * @param saida arquivo de saída.
 * @param texto
 * @param codigos código a ser escrito no arquivo.
 * @param modo_palavra caso caractere: percorre byte a byte e escreve os códigos, caso palavra: percorre os tokens e escreve os códigos.
 */
void aplicacao::escrever_dados_compactados(std::ofstream& saida,
                                           const std::string& texto,
                                           const std::map<std::string, std::string>& codigos,
                                           bool modo_palavra,
                                           uint64_t& total_bits)
{
    escrita_bit escritor(saida);
    total_bits = 0;

    if(!modo_palavra){
        for(unsigned char b : texto){
            std::string chave(1, static_cast<char>(b));
            auto it {codigos.find(chave)};

            if(it == codigos.end()){
                throw std::runtime_error("Código não encontrado para o caractere");
            }

            const std::string& cod = it->second;
            escritor.escrever_bits(cod);
            total_bits += cod.size();
        }
    }
    else{
        std::vector<std::string> tokens = extrair_tokens(texto);
        for(const std::string& token : tokens){
            auto it {codigos.find(token)};
            if(it == codigos.end()){
                throw std::runtime_error("Código não encontrado para o token: "+token);
            }
            const std::string& cod = it->second;
            escritor.escrever_bits(cod);
            total_bits += cod.size();
        }
    }

    escritor.flush();
}

/**
 * @brief Função membro para percorrer a arvore e escrever a string original.
 * @param entrada arquivo de entrada.
 * @param raiz raiz da árvore de huffman.
 * @param total_bits total de bits contidos no arquivo.
 * @return Retorna a palavra original.
 */
std::string aplicacao::ler_dados_descompactados(std::ifstream& entrada, huffman* raiz, uint64_t total_bits)
{
    leitura_bit leitor(entrada);
    std::string resultado;
    huffman* atual {raiz};
    uint64_t bits_lidos {0};

    while(bits_lidos < total_bits){
        int bit{leitor.ler_bit()};

        if(bit == -1){
            throw std::runtime_error("Fim inesperado do arquivo durante descompactação");
        }

        ++bits_lidos;

        if(bit == 0){
            atual = atual->get_esq();
        }
        else{
            atual = atual->get_dir();
        }

        if(atual->eh_folha()){
            resultado += atual->get_simbolo();
            atual = raiz;
        }
    }

    return resultado;
}

/**
 * @brief Função membro para compactar texto por caractere.
 * @param entrada nome do arquivo de entrada.
 * @param saida nome do arquivo de saída.
 */
void aplicacao::compactar_caractere(const std::string& entrada, const std::string& saida)
{
    std::string texto {ler_arquivo(entrada)};
    std::map<std::string, int> freq;

    for(unsigned char b : texto){
        freq[std::string(1, static_cast<char>(b))]++;
    }

    raiz = construir_arvore(freq);
    codigos.clear();
    gerar_codigo(raiz, STRING_VAZIA, codigos);

    std::ofstream ofile(saida, std::ios::binary);

    if(!ofile){
        throw std::runtime_error("Não foi possível criar arquivo de saída");
    }

    uint64_t total_bits {0};
    escrever_cabecalho(ofile, freq, total_bits);
    escrever_dados_compactados(ofile, texto, codigos, false, total_bits);

    ofile.seekp(0);
    escrever_cabecalho(ofile, freq, total_bits);
    ofile.close();
}

/**
 * @brief Função membro para descompactar texto por caractere.
 * @param entrada nome do arquivo de entrada.
 * @param saida nome do arquivo de saída.
 */
void aplicacao::descompactar_caractere(const std::string& entrada, const std::string& saida)
{
    std::ifstream ifile(entrada, std::ios::binary);

    if(!ifile){
        throw std::runtime_error("Não foi possível abrir o arquivo compactado");
    }

    uint64_t total_bits {0};
    std::map<std::string, int> freq {ler_cabecalho(ifile, total_bits)};

    raiz = construir_arvore(freq);

    std::string original {ler_dados_descompactados(ifile, raiz, total_bits)};
    ifile.close();

    std::ofstream ofile(saida);

    if(!ofile){
        throw std::runtime_error("Não foi possível criar o arquivo de saída");
    }

    ofile << original;
    ofile.close();
}

/**
 * @brief Função membro para compactar texto por palavra.
 * @param entrada nome do arquivo de entrada.
 * @param saida nome do arquivo de saída.
 */
void aplicacao::compactar_palavra(const std::string& entrada, const std::string& saida)
{
    std::string texto {ler_arquivo(entrada)};
    std::vector<std::string> tokens = extrair_tokens(texto);

    std::map<std::string, int> freq;

    for(const std::string& token : tokens){
        freq[token]++;
    }

    raiz = construir_arvore(freq);
    codigos.clear();
    gerar_codigo(raiz, STRING_VAZIA, codigos);

    std::ofstream ofile(saida, std::ios::binary);
    if(!ofile){
        throw std::runtime_error("Não foi possível criar o arquivo de saída");
    }

    uint64_t total_bits {0};
    escrever_cabecalho(ofile, freq, total_bits);
    escrever_dados_compactados(ofile, texto, codigos, true, total_bits);

    ofile.seekp(0);
    escrever_cabecalho(ofile, freq, total_bits);
    ofile.close();
}

/**
 * @brief Função membro para descompactar texto por palavra.
 * @param entrada nome do arquivo de entrada.
 * @param saida nome do arquivo de saída.
 */
void aplicacao::descompactar_palavra(const std::string& entrada, const std::string& saida)
{
    std::ifstream ifile(entrada, std::ios::binary);

    if(!ifile){
        throw std::runtime_error("Não foi possivel abrir o arquivo");
    }

    uint64_t total_bits {0};
    std::map<std::string, int> freq {ler_cabecalho(ifile, total_bits)};

    raiz = construir_arvore(freq);

    std::string original {ler_dados_descompactados(ifile, raiz, total_bits)};
    ifile.close();

    std::ofstream ofile(saida);

    if(!ofile){
        throw std::runtime_error("Não foi possível criar arquivo de saída");
    }

    ofile << original;
    ofile.close();
}
