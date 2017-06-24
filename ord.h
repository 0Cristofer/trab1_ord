/* Arquivo header que contém definições para o programa
   Data: 23/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#ifndef ORD_H
#define ORD_H

#define FALSE 0
#define TRUE 1

#define DATA_FILE "dados-inline.txt"
#define REG_FILE "registros.dat"
#define PIPE '|'
#define HEADER "=== SOORD - Sistema Operacional de Organização e Recuperação de Dados ===\n"

typedef struct{
  int tam;
  char* inscricao;
  char* nome;
  char* curso;
  char* score;
}registro_t;

int importar();
void busca(int inscricao, registro_t* registro);
int insere(registro_t* registro);
int removeRegistro(int inscricao);

#endif /* ORD_H */
