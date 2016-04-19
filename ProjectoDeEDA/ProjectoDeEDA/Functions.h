#pragma once

#include "Struct.h"

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
*	Password input e confirmation!
*/
wstring PassPrompt()
{
	wstring Pass, tempPass;
	bool repeat = true;
	clrConsole();

	while (repeat)
	{
		wcout << "Insira a sua password: " << endl << endl;
		getline(wcin, tempPass);
		clrConsole();

		wcout << "Insira novamente a sua password: " << endl << endl;
		getline(wcin, Pass);
		clrConsole();

		if (Pass.compare(tempPass) == 0)
		{
			repeat = false;
		}
		else
		{
			wcout << "As passwords n�o coincidem!" << endl << endl;
		}
	}
	clrConsole();

	return Pass;
}

/*
*	Cria um aluno e...
*/
int inserirAluno(/*utilizador array_util[], int tamanho*/)
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

	wcout << endl << endl << "Data de nascimento" << endl << "Dia: ";
	getline(wcin, temp);
	dia = convert_Str_2_INT(temp);
	clrConsole();

	if (dia == INT_MAX)
	{
		valorInvalido_inserirAluno(L"Dia: ");
	}

	wcout << endl << "M�s(n�mero): ";
	getline(wcin, temp);
	mes = convert_Str_2_INT(temp);
	clrConsole();

	if (mes == INT_MAX)
	{
		valorInvalido_inserirAluno(L"M�s(n�mero): ");
	}

	wcout << endl << "Ano: ";
	getline(wcin, temp);
	ano = convert_Str_2_INT(temp);
	clrConsole();

	if (ano == INT_MAX)
	{
		valorInvalido_inserirAluno(L"Ano: ");
	}

	dataNasc date;

	date.ano = ano;
	date.mes = mes;
	date.dia = dia;

	wcout << endl << endl << "Morada" << endl << "Rua: " << endl << endl;
	wstring rua, codPost, numPorta;
	getline(wcin, rua);
	clrConsole();

	wcout << endl << "N� da porta: " << endl << endl;
	getline(wcin, numPorta);
	clrConsole();

	wcout << endl << "C�digo Postal: " << endl << endl;
	getline(wcin, codPost);
	clrConsole();

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	wstring Pass = PassPrompt();

	utilizador aluno;

	//PUT USER DATA CONFIRMATION FUNCTION HERE!!!!!!!!!!!

	aluno.morada = mora;
	aluno.nasc = date;
	aluno.nome = nome;
	aluno.numero = num;
	aluno.pass = Pass;

	char conf;

	wcout << "Confirma��o de Dados" << endl;
	wcout << "N�mero Mecanogr�fico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", C�digo postal: " << mora.codPost << endl << endl;
	wcout << "Os dados est�o correctos?(S/N) ";
	cin >> conf;
	if (conf == 'S' || conf == 's')
	{
		wcout << "YAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return 0;
	}
	else
	{
		//alterar dados function...
	}

	return 0;
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
