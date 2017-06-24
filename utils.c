/* Arquivo de funcionalidades auxiliares para o funcionamento do programa
   Data: 24/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include "utils.h"

/**
* Trimma a string para o tamanho minimo.
**/
int trimString(char** string){
    int size;
    char *aux;

    size = strlen(*string);
    aux = malloc(size);
    aux = strndup(*string, size);

    free(*string);
    *string = malloc(size);
    *string = strdup(aux);

    return size;
}

/**
* Garante que a entrada do usuário é apenas 0 ou 1
**/
unsigned int iConfirmar(){
    unsigned int opt = 0;

    do{
        scanf("%d",&opt);

        if(opt > 1){
            printf("Erro, digite apenas 0 ou 1\n");
        }
    } while(opt > 1);

    return opt;
}

/**
* Exibe mensagens de erro e mata a aplicação!
**/
void errorLauncher(int e){
    printf("\nERRO!\n");
    switch (e) {
        case 1:
            printf("Erro na abertura do arquivo!\nAbortando...");
            break;

        default:
            printf("Erro desconhecido.\nAbortando...");
            break;
    }

    exit(1);
}

/**
* Printa um registro
*/
void registroToString(registro_t* registro){
    printf("-------------- Registro ----------------\n");
    printf("Tamanho: %d \n",  registro->tam);
    printf("Inscrição: %s\n", registro->inscricao);
    printf("Nome: %s\n",      registro->nome);
    printf("Curso: %s\n",     registro->curso);
    printf("Score: %s\n",     registro->score);
}
