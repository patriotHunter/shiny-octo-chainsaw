#pragma once

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
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

//struct refeicao
//{
//	dataNasc data;
//	bool entrada;
//	bool carne;
//	bool peixe;
//	bool vegie;
//};

struct plafond
{
	int numero;
	int money;
};


