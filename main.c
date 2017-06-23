/* Arquivo principal da aplicação, organiza a interface e executa as funções
   requisitadas
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include <stdio.h>

#include "ord.h"

void menuPrincipal(){
    system("clear");
    printf("=== SOORD - Sistema Operacional de Organização e Recuperação de Dados ===\n");
    printf("\n----------- Menu princpal -----------\n");

    printf("  1 - Importar de %s\n", DATA_FILE);
    printf("  2 - Buscar registros\n");
    printf("  3 - Inserir registros\n");
    printf("  4 - Remover registros\n");
    printf("  5 - Ajuda luciano\n");
    printf("  0 - Sair\n");
    printf("-------------------------------------\n");

    printf("Selecione: ");
}

void ajuda(){
    system("clear");
    printf("=== SOORD - Sistema Operacional de Organização e Recuperação de Dados ===\n");
    printf("\n----------- Ajuda -----------\n");

    printf("\n 1 - Importar de <ENTRADA> :\n  Importa os dados da entrada e substitui o arquivo de dados. Reseta o sistema.\n");

    printf("\n 2 - Buscar registros:\n  Inicia a interface de busca de registros pela inscrição, exibe o registro completo.\n");

    printf("\n 3 - Inserir registros:\n  Inicia a interface de cadastro e salva os registros criados no arquivo de dados.\n");

    printf("\n 4 - Remover registros:\n  Inicia a interface de remoção de registros. Altera permanentemente o arquivo de dados!\n");

    printf("\n 5 - Ajuda luciano: Exibe esta tela.\n");

    printf("\nPressione ENTER para voltar ao Menu Principal\n");

    getchar();
    char aux[10];
    fflush(stdin);
    fflush(stdout);
    fgets(aux, 100, stdin);
}

int main(){
    int opt;
    do {
        menuPrincipal();
        scanf("%d", &opt);

        switch(opt){
            case 5:
                ajuda();
                break;

            default:
                break;
        }
    } while (opt > 0 );
    printf("Saindo...\n");

    return 0;

}
