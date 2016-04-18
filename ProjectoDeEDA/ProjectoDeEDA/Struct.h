#pragma once

#include "Functions.h"

struct util
{
	int numero;
	string nome;
	dataNasc nasc;
	morada morada;
	string pass;
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
	string numPorta;
	string codPost;
};
