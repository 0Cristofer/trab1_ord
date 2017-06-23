/* Arquivo principal da aplicação, organiza a interface e executa as funções
   requisitadas
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ord.h"

void menuPrincipal(){
    system("clear");
    printf(HEADER);
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
    printf(HEADER);
    printf("\n----------- Ajuda -----------\n");

    printf("\n 1 - Importar de <ENTRADA> :\n  Importa os dados da entrada e substitui o arquivo de dados. Reseta o sistema.\n");

    printf("\n 2 - Buscar registros:\n  Inicia a interface de busca de registros pela inscrição, exibe o registro completo.\n");

    printf("\n 3 - Inserir registros:\n  Inicia a interface de cadastro e salva os registros criados no arquivo de dados.\n");

    printf("\n 4 - Remover registros:\n  Inicia a interface de remoção de registros. Altera permanentemente o arquivo de dados!\n");

    printf("\n 5 - Ajuda luciano: Exibe esta tela.\n");

    printf("\nPressione ENTER para voltar ao Menu Principal\n");

    getchar();
    char aux[10];
    fgets(aux, 100, stdin);
}

int iImportar(){
    system("clear");
    printf(HEADER);
    printf("\n----------- Importar -----------\n");

    printf(" Esta operação irá resetar o arquivo de dados!\n Você tem certeza? (0/1) ");

    unsigned int opt = 0;
    do{
        scanf("%d",&opt);

        if(opt > 1){
            printf("Erro, digite apenas 0 ou 1\n");
        }
    } while(opt > 1);

    return opt;
}

int iBuscar(){
    system("clear");
    printf(HEADER);
    printf("\n----------- Buscar registro -----------\n");

    unsigned int inscricao;

    printf(" Insira o número de inscrição para busca: ");
    scanf("%d", &inscricao);
    return inscricao;
}

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

void iCadastrar(registro_t* registro){
    system("clear");
    printf(HEADER);
    printf("\n----------- Cadastrar novo registro -----------\n");

    int tam = 0;
    char* inscricao;
    char* score;
    char* nome;
    char* curso;

    inscricao = malloc(sizeof(char) * 100);
    nome = malloc(sizeof(char) * 100);
    curso = malloc(sizeof(char) * 100);
    score = malloc(sizeof(char) * 100);

    printf("Número de inscrição: ");
    scanf("  %[^\n]",inscricao);
    tam += trimString(&inscricao);

    printf("Nome: ");
    scanf(" %[^\n]", nome);
    tam += trimString(&nome);

    printf("Curso: ");
    scanf(" %[^\n]", curso);
    tam += trimString(&curso);

    printf("Score: ");
    scanf("  %[^\n]", score);
    tam += trimString(&score);

    registro->tam = tam;
    registro->inscricao = inscricao;
    registro->nome = nome;
    registro->curso = curso;
    registro->score = score;
}

int main(){
    int opt;
    int opt2;
    unsigned int inscricao;

    registro_t* registro;

    do {
        menuPrincipal();
        scanf("%d", &opt);

        switch(opt){
            case 1:
                opt2 = iImportar();
                if(opt2){
                    importar();
                }
                break;

            case 2:
                inscricao = iBuscar();
                busca(inscricao, registro);
                break;

            case 3:
                registro = malloc(sizeof(registro_t));
                iCadastrar(registro);
                insere(registro);
                break;

            case 4:
                break;

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
