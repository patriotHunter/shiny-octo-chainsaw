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

/*
*	Coloca o menu principal no ecr� e devolve valores consoante a op��o escolhida pelo utilizador. 
*/
int printMainMenu(bool logged)
{
	string resposta;
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
		getline(cin, resposta);

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
*	Cria um aluno e...
*/
void inserirAluno()
{
	wcout << "Por favor insira os dados do aluno." << endl << endl << "Nome Completo: ";
	string nome;
	cin >> nome;

	wcout << endl << endl << "N�mero Mecaogr�fico: ";
	int num;
	cin >> num;

	wcout << endl << endl << "Data de nascimento" << endl << "Dia: ";
	int dia, mes, ano;
	cin >> dia;
	wcout << endl << "M�s(n�mero): ";
	cin >> mes;
	wcout << endl << "Ano: ";
	cin >> ano;

	dataNasc date;

	date.ano = ano;
	date.mes = mes;
	date.dia = dia;

	wcout << endl << endl << "Morada" << endl << "Rua: ";
	string rua, codPost, numPorta;
	cin >> rua;
	wcout << endl << "N� da porta: ";
	cin >> numPorta;
	wcout << endl << "C�digo Posal: ";
	cin >> codPost;

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	string Pass;

	//PUT PASSWORD PROMPT HERE!!!!!!

	util util;

	//PUT USER DATA CONFIRMATION FUNCTION HERE!!!!!!!!!!!

	util.morada = mora;
	util.nasc = date;
	util.nome = nome;
	util.numero = num;
	util.pass = Pass;
}