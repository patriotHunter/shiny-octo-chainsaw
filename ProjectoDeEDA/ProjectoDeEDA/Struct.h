#pragma once

#include "Functions.h"

struct util
{
	int numero;
	wstring nome;
	dataNasc nasc;
	morada morada;
	wstring pass;
};

struct dataNasc
{
	int ano;
	int mes;
	int dia;
};

struct morada
{
	wstring rua;
	wstring numPorta;
	wstring codPost;
};
