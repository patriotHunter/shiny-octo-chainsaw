#pragma once

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>

using namespace std;

/*
*	Função que irá converter, se possível um char num inteiro.
*/
int convert_Str_2_INT(string input)
{
	bool possible = true;
	int value, i;
	int arr[10];
	
	value = 0;
	i = 0;

	while (i < sizeof(input))
	{
		char c = input[i];

		if (c == 10 || c == 0 || c == 32) // verificação se o char equivale a \n, \0 ou espaço.
		{
			break;
		}
		else
		{
			if (c < 48 || c > 57 || i == 10) // verificação se o char ñ é um número.
			{
				possible = false;
				break;
			}
			else
			{
				arr[i] = c - 48;
			}
		}

		i++;
	}

	if (possible)
	{

		int j = pow(10,i-1);
		int x = 0;
		int aux;

		for (x; x < i; x++)
		{
			aux = arr[x] * j;
			value += aux;
			j /= 10;
		}

		return value;
	}
	else
	{
		return INT_MIN;
	}
}

int printMainMenu(bool logged)
{
	string resposta;

	wcout << "\n\nBem vindo ao primeiro projecto de EDA." << endl;
	wcout << "\n\nEscolha a opção pretendida.\n" << endl;
	if (logged)
	{
		wcout << "1. Logout." << endl;
	}
	else
	{
		wcout << "1. Login." << endl;
	}

	wcout << "2. Inserir novo aluno." << endl;

	wcout << "3. Pesquisa de aluno pelo primeiro nome." << endl;

	wcout << "4. Pesquisa por número mecanográfico." << endl;

	wcout << "5. Listar alunos por ordem alfabética." << endl;

	wcout << "6. Editar informação de aluno." << endl;

	wcout << "7. Remoção de aluno." << endl;

	wcout << "8. Encomendar Refeição." << endl;

	wcout << "9. Consumo de refeição." << endl;

	wcout << "10. Carregar plafond." << endl;

	wcout << "11. Listar refeições." << endl;

	wcout << "12. Listar refeções por dia.\n\n" << endl;

	getline(cin, resposta);

	int resposta_int = convert_Str_2_INT(resposta);

	if (resposta_int == INT_MIN)
	{
		wcout << "O que foi inserido não é uma opção válida." << endl;
	}
	else
	{
		wcout << "ECHO: " << resposta_int << endl;
	}

	return 0;
}