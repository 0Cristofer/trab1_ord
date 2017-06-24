/* Contém as funções usadas pelo arquivo main.c, as quais executam as
   funcionalidades do programa
   requisitadas
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include "ord.h"
#include "utils.h"

FILE* reg_file = NULL;
FILE* led_file = NULL;

/* Abre o arquivo de registros para leitura */
void abreRegistro(){
    reg_file = fopen(REG_FILE, "r+b");
}

/* Cria um novo arquivo de registro inicializando a LED */
void criaRegistro(){
    reg_file = fopen(REG_FILE, "w+b");

    if(reg_file == NULL){
        errorLauncher(1);
    }

    writeLED(-1);
}

/* Efetivamente salva os dados no registro fechado os arquivos */
void salvaRegistro(int reopen){
    if(reg_file != NULL){
        fclose(reg_file);
    }

    if(reopen){
        reg_file = fopen(REG_FILE, "r+b");
    }
}

/* Lê a cabeça da LED */
int getLED(){
    int led = 0;
    long int p_pos;

    p_pos = ftell(reg_file);

    fseek(reg_file, 0, SEEK_SET);
    fread(&led, sizeof(int), 1, reg_file);

    fseek(reg_file, p_pos, SEEK_SET);
    return led;
}

/* Escreve na cabeça da LED */
void writeLED(int led){
    long int p_pos;

    p_pos = ftell(reg_file);

    fseek(reg_file, 0, SEEK_SET);
    fwrite(&led, sizeof(int), 1, reg_file);

    salvaRegistro(TRUE);
    fseek(reg_file, p_pos, SEEK_SET);
}

/*Importa os dados do arquivo dados-inline.txt e cria um novo registro_t */
int importar(){
    FILE* data_file;

    if((data_file = fopen(DATA_FILE, "rb")) != NULL){
        registro_t* registro;
        int field_count = 0;
        int field_size = 0;
        int reg_size = 0;
        int i;
        char reg[50];
        char* reg_s;
        char c;

        criaRegistro();

        registro = malloc(sizeof(registro_t));
        c = fgetc(data_file);
        while(c != EOF){
            i = 0;
            while((c != PIPE) && (c != EOF)){
                if(c == ','){
                    c = '.';
                }
                reg[i] = c;

                c = fgetc(data_file);
                i = i + 1;
                field_size = field_size + 1;
            }

            reg_s = malloc((field_size + 1) * sizeof(char));
            for(i = 0; i < field_size; i++){
                reg_s[i] = reg[i];
            }
            reg_s[field_size] = '\0';

            switch (field_count % 4) {
                case 0:
                    registro->inscricao = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 1:
                    registro->nome = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 2:
                    registro->curso = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 3:
                    registro->score = reg_s;
                    reg_size = reg_size + field_size;
                    registro->tam = reg_size;

                    insere(registro);
                    free(registro);
                    registro = malloc(sizeof(registro_t));
                    reg_size = 0;
                    break;
            }

            field_size = 0;
            field_count = field_count + 1;
            c = fgetc(data_file);
        }

        return TRUE;
    }

    return FALSE;
}

void busca(char* inscricao, registro_t** registro){

    //TODO Percorrer o arquivo testando as inscrições até achar o registro:
    *registro = malloc(sizeof(registro_t)); //TODO Acontece apenas se achou.

    printf("%s", inscricao);
}

int insere(registro_t* registro){
    registroToString(registro);
    registro->tam = registro->tam + 4; //4 pipes

    if(reg_file == NULL){
        criaRegistro();
    }

    if(getLED() == -1){
        fseek(reg_file, 0, SEEK_END);
        fwrite(&(registro->tam), sizeof(short), 1, reg_file);
        fputs(registro->inscricao, reg_file);
        fputs(PIPE_STR, reg_file);
        fputs(registro->nome, reg_file);
        fputs(PIPE_STR, reg_file);
        fputs(registro->curso, reg_file);
        fputs(PIPE_STR, reg_file);
        fputs(registro->score, reg_file);
        fputs(PIPE_STR, reg_file);
    }else{
        //Procurar espaço na LED
    }

    registro->tam = registro->tam - 4; //Remove os pipes

    return TRUE;
}

int removeRegistro(char* inscricao){
    return TRUE;
}
