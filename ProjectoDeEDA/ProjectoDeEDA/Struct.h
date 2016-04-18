#pragma once

#include "Functions.h"

struct util
{
	int numero;
	string nome;
	dataNasc nasc;
	morada morada;
};

struct dataNasc
{
	int ano;
	int mes;
	int dia;
};

struct morada
{
	string rua;
	int numPorta;
	string codPost;
};
