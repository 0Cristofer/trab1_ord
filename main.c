/* Arquivo principal da aplicação, organiza a interface e executa as funções
   requisitadas
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include "ord.h"
#include "utils.h"

void menuPrincipal(){
    system("clear");
    printf(HEADER);

    if(reg_file != NULL){
        printf("\n\t\t   Arquivo de registros existente!\n");
    }
    else{
        printf("\n\t\t   Arquivo de registros inexistente!\n");
    }

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

    pause();
}


int iImportar(){
    system("clear");
    printf(HEADER);
    printf("\n----------- Importar -----------\n");

    printf(" Esta operação irá resetar o arquivo de dados!\n Você tem certeza? (0/1) ");

    unsigned int opt = iConfirmar();

    return opt;
}

void iBuscar(char** inscricao){
    system("clear");
    printf(HEADER);
    printf("\n----------- Buscar registro -----------\n");

    printf(" Insira o número da inscrição para busca: ");
    *inscricao = malloc(sizeof(char) * 100);

    scanf(" %[^\n]", *inscricao);
    trimString(inscricao);
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

    printf("Número da inscrição: ");
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

void iRemover1(char** inscricao){
    system("clear");
    printf(HEADER);
    printf("\n-------------- Remoção de registros --------------\n");

    printf("Para remover um registro, primeiro insira seu número de inscrição.\n ATENÇÃO: Esta ação é permanente.\n");

    printf("\nNúmero da inscrição: ");
    scanf(" %[^\n]", *inscricao);
    trimString(inscricao);
}

unsigned int iRemover2(registro_t* registro){
    system("clear");
    printf(HEADER);
    printf("\n-------------- Remoção de registros --------------\n");

    printf("\nRegistro encontrado!\n\n");

    registroToString(registro);

    printf("\nVocê tem certeza que deseja remover este registro? (0/1)\n ATENÇÃO: Esta ação é permanente.\n");

    unsigned int opt = iConfirmar();

}

int main(){
    unsigned int opt, opt2;

    registro_t registro;
    char* inscricao;

    abreRegistro();

    do {
        registro.tam = 0;
        inscricao = malloc(sizeof(char) * 10);

        menuPrincipal();
        scanf("%d", &opt);

        switch(opt){
            case 1:
                if(iImportar()){
                    importar();
                }
                break;

            case 2:
                iBuscar(&inscricao);
                busca(inscricao, &registro);
                if(registro.tam != 0){
                    printf("\nRegistro encontrado!\n");
                    registroToString(&registro);
                    //TODO free nos ponteiros do registro
                } else {
                    printf("\nRegistro não encontrado :(\n");
                }
                pause();
                break;

            case 3:
                iCadastrar(&registro);
                insere(&registro);
                break;

            case 4:
                opt2 = 0;
                do{
                    iRemover1(&inscricao);
                    printf("insc: %s\n", inscricao);
                    busca(inscricao, &registro);

                    if(registro.tam == 0){
                        printf("Registro %s não encontrado!\nDeseja procurar novamente? (0/1)", inscricao);
                        opt2 = iConfirmar();

                    }
                } while((registro.tam == 0) || (opt2 == 1));

                if(registro.tam != 0){
                    if(iRemover2(&registro)){
                        removeRegistro(inscricao, &registro);
                    }
                }

                break;

            case 5:
                ajuda();
                break;

            default:
                break;
        }

        free(inscricao);

    } while (opt > 0 );

    printf("Saindo...\n");
    salvaRegistro(FALSE);

    return 0;

}
