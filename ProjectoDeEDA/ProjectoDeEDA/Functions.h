#pragma once

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include "Struct.h"

using namespace std;

/*
*	Função para fazer clear à consola.
*/
void clrConsole()
{
	system("cls");
}

/*
*	Função que irá converter, se possível um char num inteiro.
*/
int convert_Str_2_INT(wstring input)
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
		int j = pow(10, i - 1);
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

/*
*	Coloca o menu principal no ecrã e devolve valores consoante a opção escolhida pelo utilizador.
*/
int printMainMenu(bool logged)
{
	wstring resposta;
	int resposta_int;
	bool quit = false;

	clrConsole();

	while (!quit)
	{
		//	Imprime texto no ecrã.
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

		//	Obtém resposta do utilizador.
		getline(wcin, resposta);

		resposta_int = convert_Str_2_INT(resposta);

		//	Verifica se a resposta do utilizado é válida.
		if (resposta_int == INT_MIN)
		{
			wcout << "O que foi inserido não é uma opção válida." << endl;
		}
		else
		{
			quit = true;
		}
	}
	return resposta_int;
}

/*
*	Indica que o valor inserido não é válido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x)
{
	bool repeat = true;
	char answer;
	int num;
	wstring temp;

	while (repeat)
	{
		wcout << "O valor inserido não é válido, quer continuar a inserção de aluno? (S/N)" << endl;
		cin >> answer;

		if (answer == 'n' || answer == 'N')
		{
			return -1;
		}
		wcout << endl << x << endl << endl;
		getline(wcin, temp);
		num = convert_Str_2_INT(temp);

		if (num != INT_MAX)
		{
			repeat = false;
		}
		clrConsole();
	}
	return num;
}

/*
*	Cria um aluno e...
*/
int inserirAluno()
{
	wstring nome, temp;
	int num, dia, mes, ano;


	wcout << "Por favor insira os dados do aluno." << endl << endl << "Nome Completo: " << endl << endl;
	getline(wcin, nome);
	clrConsole();

	wcout << endl << endl << "Número Mecanográfico: " << endl << endl;
	getline(wcin, temp);
	num = convert_Str_2_INT(temp);
	clrConsole();

	if (num == INT_MAX)
	{
		valorInvalido_inserirAluno(L"Número Mecanográfico: ");
	}

	wcout << endl << endl << "Data de nascimento" << endl << "Dia: " << endl << endl;
	cin >> dia;
	clrConsole();

	wcout << endl << "Mês(número): " << endl << endl;
	cin >> mes;
	clrConsole();

	wcout << endl << "Ano: ";
	cin >> ano;

	dataNasc date;

	date.ano = ano;
	date.mes = mes;
	date.dia = dia;

	wcout << endl << endl << "Morada" << endl << "Rua: ";
	wstring rua, codPost, numPorta;
	wcin >> rua;
	wcout << endl << "Nº da porta: ";
	wcin >> numPorta;
	wcout << endl << "Código Posal: ";
	wcin >> codPost;

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	wstring Pass;

	//PUT PASSWORD PROMPT HERE!!!!!!

	util util;

	//PUT USER DATA CONFIRMATION FUNCTION HERE!!!!!!!!!!!

	util.morada = mora;
	util.nasc = date;
	util.nome = nome;
	util.numero = num;
	util.pass = Pass;

/*
	char conf;

	wcout << "Confirmação de Dados" << endl;
	wcout << "Número Mecanográfico: " << num << endl;
	wcout << "Nome Completo: " << (wstring)nome << endl;
	wcout << "Data de Nascimento: " << date << endl;
	wcout << "Morada: " << mora << endl;
	wcout << "Confirma estes dados?(S/N) ";
	cin >> conf;
	if (conf == 'Y' || conf == 'y')
	{
		return 0;
	}
	else
	{
		wcout << "Insira novamente os seus dados" << endl;
		inserirAluno();
	}*/
}