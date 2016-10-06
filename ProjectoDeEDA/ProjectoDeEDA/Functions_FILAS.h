#pragma once

#include "Struct.h"

//Protótipo de funções

void novo(filaUtilizadores& fila);

void novo(filaRefeicao& fila);

void insereNaFila(filaUtilizadores& fila, utilizador util);

void insereNaFila(filaRefeicao& fila, refeicao ref);

bool vazio(filaUtilizadores& fila);

bool vazio(filaRefeicao& fila);

void retiraDaFila(filaUtilizadores& fila, int numero);

void retiraDaFila(filaRefeicao& fila, refeicao ref);

filaUtilizadores ordenaPorNome(filaUtilizadores& fila);
