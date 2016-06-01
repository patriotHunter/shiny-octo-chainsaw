#pragma once

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <cstddef>

using namespace std;

/*
	Estrutura que define o que � uma data...
*/
struct dataNasc
{
	int ano;
	int mes;
	int dia;
};

/*
	Estrutura que define a composi��o de uma morada...
*/
struct morada
{
	wstring rua;
	wstring numPorta;
	wstring codPost;
};		

/*
	Estrutura que define qual a informa��o necess�ria para termos um utilizador
*/
struct utilizador
{
	int numero;
	wstring nome;
	int money;
	dataNasc nasc;
	morada morada;
	wstring curso;
	wstring pass;
};

/*
	Estrutura que define o que � uma refei��o
*/
struct refeicao
{
	int numero;
	bool jantar;
	dataNasc data;
};

/*
M�todo de pilhas como na ficha 8
*/

struct filaUtilizadores {
	struct Utilizador {
		utilizador util;
		Utilizador *proximo;
	};
	Utilizador *ultimoAluno;
};


bool vazio(filaUtilizadores& fila);
int insereAluno(filaUtilizadores& fila);
void mostrar(filaUtilizadores& fila);
void retira(filaUtilizadores& fila);

struct listasUtil *primeiro = NULL, *ultimo = NULL, *actual;


