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
#define HEADER "=== SOORD - Sistema Operacional de Organização e Recuperação de Dados ===\n"

FILE* ponteiro_reg_file;
FILE* reg_file;


typedef struct{
  int tam;
  char* inscricao;
  char* nome;
  char* curso;
  char* score;
}registro_t;


int importar();
void busca(char* inscricao, registro_t** registro, FILE** ponteiro_reg_file);
int insere(registro_t* registro);
int removeRegistro(char* inscricao);

#endif /* ORD_H */
