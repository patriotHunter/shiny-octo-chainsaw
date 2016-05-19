#pragma once

#include "Struct.h"
#include <ctime>

/*
ATENÇÂO:	Neste ficheiro encontram-se funções que não necessitem de variáveis globais!!!
*/

/*
Função para fazer clear à consola.
*/
void clrConsole();

/*
Função que irá converter, se possível um char num inteiro.
*/
int convert_Str_2_INT(wstring input);

/*
Indica que o valor inserido não é válido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x);

/*
Password input e confirmation!
*/
wstring PassPrompt();

/*
Função para obter uma string com a data atual no formato yyyy/mm/dd
*/
wstring currentDate();

/*
Verifica se a data é válida, ou seja, se esta é possível no calendário e se é após a data atual.
*/
bool dateValid(int ano, int mes, int dia);

/*
Verifica se a data é igual à introduzida
*/
bool dataVerifica(int ano, int mes, int dia);
