#pragma once

#include "Struct.h"
#include <ctime>

/*
	ATENÇÂO:	Neste ficheiro encontram-se funções que não necessitem de variáveis globais!!!
*/

/*
	Função para fazer clear à consola.
*/
void clrConsole()
{
	system("cls");
}

/*
	Função que irá converter, se possível um char num inteiro.
*/
int convert_Str_2_INT(wstring input)
{
	if (input.compare(L"") == 0)
	{
		return INT_MIN;
	}
	bool possible = true;
	int value, i;
	int arr[10];

	value = 0;
	i = 0;

	while (i < sizeof(input))
	{
		wchar_t c = input[i];

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

	if (possible)												//Se a string passada é um número...
	{
		double j = pow(10, i - 1);								//j = 10^(i-1)
		int x = 0;
		int aux;

		for (x; x < i; x++)
		{
			aux = arr[x] * (int)j;
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
	Indica que o valor inserido não é válido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x)
{
	bool repeat = true;
	wchar_t answer;
	int num;
	wstring temp;

	while (repeat)
	{
		wcout << "O valor inserido não é válido, quer continuar a inserção de aluno? (S/N)" << endl;
		wcin >> answer;
		cin.sync();
		cin.get();										//Retira um ghost "ENTER"
		if (answer == L'n' || answer == L'N')
		{
			return -1;
		}
		wcout << endl << x << endl << endl;
		getline(wcin, temp);
		num = convert_Str_2_INT(temp);

		if (num != INT_MIN)
		{
			repeat = false;
		}
		clrConsole();
	}
	return num;
}

/*
	Password input e confirmation!
*/
wstring PassPrompt()
{
	wstring Pass, tempPass;
	bool repeat = true;
	clrConsole();

	while (repeat)	// Enquanto o utilizador não inserir duas vezes a mesma pass 
	{
		wcout << "Insira a sua password: " << endl << endl;
		getline(wcin, tempPass);
		clrConsole();

		wcout << "Insira novamente a sua password: " << endl << endl;
		getline(wcin, Pass);
		clrConsole();

		if (Pass.compare(tempPass) == 0)				// Compara para ver se o que foi inserido coincide
		{
			repeat = false;
		}
		else
		{
			wcout << "As passwords não coincidem!" << endl << endl;
		}
	}
	clrConsole();

	return Pass;
}

/*
	Função para obter uma string com a data atual no formato yyyy/mm/dd
*/
wstring currentDate()
{
	time_t t = time(0);   // Obtém o tempo atual
	struct tm now;
	localtime_s(&now, &t);	// atribui à struct tm o tempo atual

	int dia, mes, ano;

	//Vai buscar à struct tm os valores que nos interessam
	ano = now.tm_year + 1900;		//O ano 2016 devolve 116
	mes = now.tm_mon + 1;			//Os meses começam em 0 até 11
	dia = now.tm_mday;

	//Para ficar algo do género yyyy/04/dd em vez de yyyy/4/dd....
	if (mes < 10)
	{
		return to_wstring(ano) + L"/0" + to_wstring(mes) + L"/" + to_wstring(dia);
	}
	else
	{
		return to_wstring(ano) + L"/" + to_wstring(mes) + L"/" + to_wstring(dia);
	}
	
}

/*
	Verifica se a data é válida, ou seja, se esta é possível no calendário e se é após a data atual.
*/
bool dateValid(int ano, int mes, int dia)
{
	//Verificação se a data é possível no calendário...
	if (ano >= 2016)
	{
		if (mes > 0 || mes <= 12)
		{
			switch (mes)
			{
			case 1:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 2:
				if (dia < 1 || dia > 29)
				{
					return false;
				}
				else if ((ano % 4) != 0 && dia == 29)
				{
					return false;
				}
			case 3:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 4:
				if (dia < 1 || dia > 30)
				{
					return false;
				}
				break;
			case 5:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 6:
				if (dia < 1 || dia > 30)
				{
					return false;
				}
				break;
			case 7:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 8:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 9:
				if (dia < 1 || dia > 30)
				{
					return false;
				}
				break;
			case 10:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			case 11:
				if (dia < 1 || dia > 30)
				{
					return false;
				}
				break;
			case 12:
				if (dia < 1 || dia > 31)
				{
					return false;
				}
				break;
			default:
				return false;
				break;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	wstring data;

	//Para ficar algo do género yyyy/04/dd em vez de yyyy/4/dd....
	if (mes < 10)
	{
		data = to_wstring(ano) + L"/0" + to_wstring(mes) + L"/" + to_wstring(dia);
	}
	else
	{
		data = to_wstring(ano) + L"/" + to_wstring(mes) + L"/" + to_wstring(dia);
	}

	//Compara ambas as strings e desta forma consegue verificar se a data é antes, durante ou depois de hoje.
	if (data.compare(currentDate()) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}