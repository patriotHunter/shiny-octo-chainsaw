#pragma once

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include "Struct.h"

using namespace std;

/*
*	Fun��o para fazer clear � consola.
*/
void clrConsole()
{
	system("cls");
}

/*
*	Fun��o que ir� converter, se poss�vel um char num inteiro.
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

		if (c == 10 || c == 0 || c == 32) // verifica��o se o char equivale a \n, \0 ou espa�o.
		{
			break;
		}
		else
		{
			if (c < 48 || c > 57 || i == 10) // verifica��o se o char � � um n�mero.
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
*	Coloca o menu principal no ecr� e devolve valores consoante a op��o escolhida pelo utilizador.
*/
int printMainMenu(bool logged)
{
	wstring resposta;
	int resposta_int;
	bool quit = false;

	clrConsole();

	while (!quit)
	{
		//	Imprime texto no ecr�.
		wcout << "\n\nBem vindo ao primeiro projecto de EDA." << endl;
		wcout << "\n\nEscolha a op��o pretendida.\n" << endl;
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
		wcout << "4. Pesquisa por n�mero mecanogr�fico." << endl;
		wcout << "5. Listar alunos por ordem alfab�tica." << endl;
		wcout << "6. Editar informa��o de aluno." << endl;
		wcout << "7. Remo��o de aluno." << endl;
		wcout << "8. Encomendar Refei��o." << endl;
		wcout << "9. Consumo de refei��o." << endl;
		wcout << "10. Carregar plafond." << endl;
		wcout << "11. Listar refei��es." << endl;
		wcout << "12. Listar refe��es por dia.\n\n" << endl;

		//	Obt�m resposta do utilizador.
		getline(wcin, resposta);

		resposta_int = convert_Str_2_INT(resposta);

		//	Verifica se a resposta do utilizado � v�lida.
		if (resposta_int == INT_MIN)
		{
			wcout << "O que foi inserido n�o � uma op��o v�lida." << endl;
		}
		else
		{
			quit = true;
		}
	}
	return resposta_int;
}

/*
*	Indica que o valor inserido n�o � v�lido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x)
{
	bool repeat = true;
	char answer;
	int num;
	wstring temp;

	while (repeat)
	{
		wcout << "O valor inserido n�o � v�lido, quer continuar a inser��o de aluno? (S/N)" << endl;
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

	wcout << endl << endl << "N�mero Mecanogr�fico: " << endl << endl;
	getline(wcin, temp);
	num = convert_Str_2_INT(temp);
	clrConsole();

	if (num == INT_MAX)
	{
		valorInvalido_inserirAluno(L"N�mero Mecanogr�fico: ");
	}

	wcout << endl << endl << "Data de nascimento" << endl << "Dia: " << endl << endl;
	cin >> dia;
	clrConsole();

	wcout << endl << "M�s(n�mero): " << endl << endl;
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
	wcout << endl << "N� da porta: ";
	wcin >> numPorta;
	wcout << endl << "C�digo Posal: ";
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

	wcout << "Confirma��o de Dados" << endl;
	wcout << "N�mero Mecanogr�fico: " << num << endl;
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