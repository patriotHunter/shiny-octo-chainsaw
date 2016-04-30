#pragma once

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <cstddef>
using namespace std;

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

struct utilizador
{
	int numero;
	wstring nome;
	dataNasc nasc;
	morada morada;
	wstring curso;
	wstring pass;
};

struct refeicao
{
	int numero;
	bool jantar;
	dataNasc data;
};

struct plafond
{
	int numero;
	int money;
};


