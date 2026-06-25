#include <iostream>
#include <stdlib.h>
#include "include/aplicacao.hpp"

int main()
{
    int opcao;

    do{
        std::cout << "============================\n";
        std::cout << "|| 1 - Utilizar algoritmo ||\n";
        std::cout << "|| 0 - Sair               ||\n";
        std::cout << "============================\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        #ifdef _WIN32
            system("cls");
        #elif __linux__
            system("clear");
        #endif

        if(opcao != 0){
            aplicacao app;
            app.menu();
        }

    }while(opcao != 0);

    return 0;
}
