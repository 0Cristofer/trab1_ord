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

    writeLED(NO_LED);
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

/*Importa os dados do arquivo dados-inline.txt e cria um novo registro */
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

/* Procura por um registro. Se encontrado preenche a estrutura passada e coloca o ponteiro do arquivo no inicio do registro */
void busca(char* inscricao, registro_t* registro){
    short size;
    char* str_registro;
    char* pch;
    size_t resultado;

    fseek(reg_file, 4, SEEK_SET); //Pula a cabeça da LED

    do{
        resultado = fread(&size, sizeof(short), 1, reg_file); //Lê o tamanho do registro

        if(resultado > 0){ //Executa apenas se leu o dado
            str_registro = malloc(sizeof(char) * (size + 1));

            fgets(str_registro, size+1, reg_file); //Lê o registro (size+1 por causa do /0)

            if(str_registro[1] != '*'){ //Verifica se é vazio

                pch = strtok(str_registro,"|");

                if(strcmp(pch, inscricao) == 0){ //Verifica se encontrou o registro procurado

                    registro->tam = size - 4;

                    int field_size;

                    field_size = strlen(pch) + 1;
                    registro->inscricao = malloc(sizeof(char) * field_size);
                    strcpy(registro->inscricao, pch);

                    pch = strtok(NULL,"|");
                    field_size = strlen(pch) + 1;
                    registro->nome = malloc(sizeof(char) * field_size);
                    strcpy(registro->nome, pch);

                    pch = strtok(NULL,"|");
                    field_size = strlen(pch) + 1;
                    registro->curso = malloc(sizeof(char) * field_size);
                    strcpy(registro->curso, pch);

                    pch = strtok(NULL,"|");
                    field_size = strlen(pch) + 1;
                    registro->score = malloc(sizeof(char) * field_size);
                    strcpy(registro->score, pch);
                }
            }
            free(str_registro);
        }

    } while(registro->tam == 0 && (feof(reg_file) == 0));

    if(registro->tam != 0){
        fseek(reg_file, ((registro->tam + 6)*-1), SEEK_CUR); //Coloca o ponteiro do arquivo no inicio do registro
    }
}

int insere(registro_t* registro){
    int led = 0;
    int last_led = 0;
    short tam = 0;
    short new_tam = 0;
    int next_led = 0;

    registroToString(registro);
    registro->tam = registro->tam + 4; //4 pipes

    if(reg_file == NULL){
        criaRegistro();
    }

    led = getLED();
    if(led == -1){
        fseek(reg_file, 0, SEEK_END);
        escreveRegistro(registro);

    }
    else{
        fseek(reg_file, led, SEEK_SET);
        fread(&tam, sizeof(short), 1, reg_file);
        while(tam < (registro->tam + 4)){
            last_led = led;

            fseek(reg_file, led+2, SEEK_SET);
            fread(&led, sizeof(int), 1, reg_file);

            if(led == -1){
                break;
            }

            fseek(reg_file, led, SEEK_SET);
            fread(&tam, sizeof(short), 1, reg_file);
        }

        if(led == -1){
            fseek(reg_file, 0, SEEK_END);
            escreveRegistro(registro);
        }
        else{
            fseek(reg_file, led, SEEK_SET);

            new_tam = tam - (registro->tam + 4);
            if(new_tam > 7){
                new_tam = new_tam - 2;
                fwrite(&new_tam, sizeof(short), 1, reg_file);
                fseek(reg_file, new_tam, SEEK_CUR);
            }
            else{
                fseek(reg_file, led+4, SEEK_SET);
                fread(&next_led, sizeof(int), 1, reg_file);
                if(last_led == 0){
                    fseek(reg_file, last_led, SEEK_SET);
                }
                else{
                    fseek(reg_file, last_led+4, SEEK_SET);
                }
                fwrite(&next_led, sizeof(int), 1, reg_file);
                fseek(reg_file, led, SEEK_SET);
            }

            escreveRegistro(registro);
            if((new_tam > 0) && (new_tam < 8)){
                while(new_tam > 0){
                    fputc(NULL_CHAR, reg_file);
                    new_tam = new_tam - 1;
                }
            }
        }
    }

    registro->tam = registro->tam - 4; //Remove os pipes

    salvaRegistro(TRUE);

    return TRUE;
}

int removeRegistro(char* inscricao){
    return TRUE;
}

void escreveRegistro(registro_t* registro){
    fwrite(&(registro->tam), sizeof(short), 1, reg_file);
    fputs(PIPE_STR, reg_file);
    fputs(registro->inscricao, reg_file);
    fputs(PIPE_STR, reg_file);
    fputs(registro->nome, reg_file);
    fputs(PIPE_STR, reg_file);
    fputs(registro->curso, reg_file);
    fputs(PIPE_STR, reg_file);
    fputs(registro->score, reg_file);
}
