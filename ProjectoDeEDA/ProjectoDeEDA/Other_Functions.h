#pragma once

#include "Struct.h"
#include <ctime>

/*
ATEN��O:	Neste ficheiro encontram-se fun��es que n�o necessitem de vari�veis globais!!!
*/

/*
Fun��o para fazer clear � consola.
*/
void clrConsole();

/*
Fun��o que ir� converter, se poss�vel um char num inteiro.
*/
int convert_Str_2_INT(wstring input);

/*
Indica que o valor inserido n�o � v�lido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x);

/*
Password input e confirmation!
*/
wstring PassPrompt();

/*
Fun��o para obter uma string com a data atual no formato yyyy/mm/dd
*/
wstring currentDate();

/*
Verifica se a data � v�lida, ou seja, se esta � poss�vel no calend�rio e se � ap�s a data atual.
*/
bool dateValid(int ano, int mes, int dia);

/*
Verifica se a data � igual � introduzida
*/
bool dataVerifica(int ano, int mes, int dia);
