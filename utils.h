/* Arquivo header que contém definições de utils.c
   Data: 24/06/2017
   Autores: Bruno Cesar, Cristofer Oswald */

#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include "ord.h"

int trimString(char** string);
unsigned int iConfirmar();
void errorLauncher(int e);
void registroToString(registro_t* registro);


#endif /* UTILS_H */
