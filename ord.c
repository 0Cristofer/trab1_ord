/* Contém as funções usadas pelo arquivo main.c, as quais executam as
   funcionalidades do programa
   requisitadas
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#include "ord.h"
#include "utils.h"

int importar(){
    FILE* data_file;

    if((data_file = fopen(DATA_FILE, "rb")) != NULL){
        registro_t* registro;
        int led = -1;
        int field_count = 0;
        int field_size = 0;
        int reg_size = 0;
        int i;
        char reg[50];
        char* reg_s;
        char c;

        if((reg_file = fopen(REG_FILE, "wb")) == NULL){
            errorLauncher(1);
        }

        fwrite(&led, sizeof(int), 1, reg_file);

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
                    (*registro).inscricao = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 1:
                    (*registro).nome = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 2:
                    (*registro).curso = reg_s;
                    reg_size = reg_size + field_size;
                    break;

                case 3:
                    (*registro).score = reg_s;
                    reg_size = reg_size + field_size;
                    (*registro).tam = reg_size;

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

void busca(char* inscricao, registro_t** registro, FILE** ponteiro_reg_file){

    if((*ponteiro_reg_file = fopen(REG_FILE, "rb")) == NULL){
        errorLauncher(1);
    }

    //TODO Percorrer o arquivo testando as inscrições até achar o registro:
    *registro = malloc(sizeof(registro_t)); //TODO Acontece apenas se achou.

    printf("%s", inscricao);
}

int insere(registro_t* registro){
    registroToString(registro);
    return TRUE;
}

int removeRegistro(char* inscricao){
    return TRUE;
}
