/* Arquivo header que contém definições para o programa
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#ifndef ORD_H
#define ORD_H

#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define DATA_FILE "dados-inline.txt"
#define REG_FILE "registros.dat"
#define PIPE '|'
#define NULL_CHAR '#'
#define PIPE_STR "|"
#define NULL_REG "*|"
#define NO_LED -1
#define HEADER "=== SOORD - Sistema Operacional de Organização e Recuperação de Dados ===\n"

//Variável global
extern FILE* reg_file;

typedef struct{
    short tam;
    char* inscricao;
    char* nome;
    char* curso;
    char* score;
}registro_t;

int importar();
void abreRegistro();
void salvaRegistro(int REOPEN);
void writeLED(int led);
void busca(char* inscricao, registro_t* registro);
void insere(registro_t* registro);
void removeRegistro(char* inscricao, registro_t* registro);
void escreveRegistro(registro_t* registro);

#endif /* ORD_H */
