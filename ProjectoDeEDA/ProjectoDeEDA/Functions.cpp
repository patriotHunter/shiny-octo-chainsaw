#pragma once

#include "Struct.h"
#include "Other_Functions.h"
#include "Functions.h"

/*
ATEN��O:	Neste ficheiro encontram-se todas as fun��es que necessitem de vari�veis globais!!!
*/

bool logged = false;							// O utilizador esta logged in ou n�o
bool admin = false;								// O utilizador � funcion�rio ou n�o
int const TAMANHO = 500;						// Tamanho dos arrays
int Util_logged;								// Numero mecanografico do ultimo/atual utilizador logged in
utilizador array_util[TAMANHO];					// Array de utilizadores
plafond array_plafond[TAMANHO];					// Array de plafonds
refeicao array_refeicao[TAMANHO * 10];			// Array de refeicoes
wchar_t dadU[50] = L"BaseDados.txt";			// Nome do ficheiro contendo a informa��o dos utilizadores 
wchar_t dadP[50] = L"Plafond.txt";				// Nome do ficheiro contendo a informa��o dos plafonds
wchar_t dadR[50] = L"Refeicoes.txt";			// Nome do ficheiro contendo a informa��o dos plafonds
int numUtils = 0;								// Numero total de utilizadores
int numPlafonds = 0;							// Numero total de utilizadores com plafond
int numRefeicoes = 0;							// Numero total de refeicoes

												/*
												Preenche o resto dos utilizadores com informa��o que seja f�cil para n�s descartarmos esse utilizador como inv�lido
												*/
void fillArrayBlankUtil(int i)
{
	while (i < TAMANHO)
	{
		array_util[i].numero = INT_MIN;
		i++;
	}
}

/*
Preenche o resto dos utilizadores com informa��o que seja f�cil para n�s descartarmos esse utilizador como inv�lido
*/
void fillArrayBlankPlafond(int i)
{
	while (i < TAMANHO)
	{
		array_plafond[i].numero = INT_MIN;
		i++;
	}
}

/*
Preenche o resto dos utilizadores com informa��o que seja f�cil para n�s descartarmos esse utilizador como inv�lido
*/
void fillArrayBlankRefeicoes(int i)
{
	while (i < (TAMANHO * 10))
	{
		array_refeicao[i].numero = INT_MIN;
		i++;
	}
}

/*
Le dados do ficheiro contendo os plafonds
*/
void leDadosPlafonds()
{
	wstring temp;

	int aux;

	wfstream file;

	file.open(dadP, ios::in);
	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nPressione Enter para terminar o programa.\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekg(ios::beg);

	int i = 0;

	while (i < TAMANHO)
	{
		getline(file, temp);

		aux = convert_Str_2_INT(temp);									// Guarda o valor numerico da string temp em aux

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que n�o h� utilizadores por criar pois o que foi lido j� n�o � um valor v�lido
		{
			array_plafond[i].numero = aux;

			getline(file, temp);
			array_plafond[i].money = convert_Str_2_INT(temp);

			getline(file, temp);

			numPlafonds++;
			i++;
		}
		else
		{
			fillArrayBlankPlafond(i);
			i = TAMANHO;
		}
	}
	file.close();
}

/*
Escreve os dados de plafonds nos ficheiros
*/
void escreveDadosPlafonds()
{
	wfstream file;

	file.open(dadP, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que � para come�ar o ficheiro como se fosse um novo ficheiro, apagando o conte�do presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nN�o � poss�vel guardar dados!!!\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekp(ios::beg);

	int i = 0;

	int plafonds_guardados = 0;

	while (i < TAMANHO && plafonds_guardados != numPlafonds)
	{
		if (array_plafond[i].numero != INT_MIN && plafonds_guardados < numPlafonds)			// Se for um plafond v�lido guarda caso contr�rio passa ao pr�ximo plafond
		{
			file << array_plafond[i].numero << endl;
			file << array_plafond[i].money << endl;
			file << "-" << endl;

			plafonds_guardados++;
		}
		else if (array_plafond[i].numero != INT_MIN && plafonds_guardados == numPlafonds)		// Se for o �ltimo plafond v�lido guarda sem colocar uma linha em branco no fim do ficheiro
		{
			file << array_plafond[i].numero << endl;
			file << array_plafond[i].money << endl;
			file << "-";
		}
		i++;
	}
	file.close();
}

/*
Le a informa��o relativa �s refei��es e coloca-a no array respectivo
*/
void leDadosRefeicoes()
{
	wfstream file;
	file.open(dadR, ios::in);

	wstring temp;
	int aux;

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nPressione Enter para terminar o programa.\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekg(ios::beg);


	int i = 0;
	while (i < TAMANHO)
	{
		getline(file, temp);

		aux = convert_Str_2_INT(temp);

		if (aux != INT_MIN && aux != 0)
		{
			array_refeicao[i].numero = aux;

			getline(file, temp);

			if (convert_Str_2_INT(temp) == 1)
			{
				array_refeicao[i].jantar = true;
			}
			else
			{
				array_refeicao[i].jantar = false;
			}

			getline(file, temp);
			array_refeicao[i].data.ano = convert_Str_2_INT(temp);

			getline(file, temp);
			array_refeicao[i].data.mes = convert_Str_2_INT(temp);

			getline(file, temp);
			array_refeicao[i].data.dia = convert_Str_2_INT(temp);

			getline(file, temp);

			//Se for uma data anterior � atual descarta-a 
			if (dateValid(array_refeicao[i].data.ano, array_refeicao[i].data.mes, array_refeicao[i].data.dia))
			{
				numRefeicoes++;
				i++;
			}
			else
			{
				refeicao ref;
				ref.numero = INT_MIN;
				array_refeicao[i] = ref;	//Substitui por refei��o inv�lida e ir� fazer overwrite desta informa��o se ainda faltar refei��es por meter no array
			}
		}
		else
		{
			fillArrayBlankRefeicoes(i);
			i = TAMANHO * 10;
		}
	}
	file.close();
}

/*
Escreve os dados de refeicoes nos ficheiros
*/
void escreveDadosRefeicoes()
{
	wfstream file;

	file.open(dadR, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que � para come�ar o ficheiro como se fosse um novo ficheiro, apagando o conte�do presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nN�o � poss�vel guardar dados!!!\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekp(ios::beg);

	int i = 0;

	int refeicoes_guardadas = 0;

	while (i < TAMANHO && refeicoes_guardadas != numRefeicoes)
	{
		if (array_refeicao[i].numero != INT_MIN && refeicoes_guardadas < numRefeicoes)			// Se for uma refeicao v�lida guarda caso contr�rio passa � pr�xima refeicao
		{
			file << array_refeicao[i].numero << endl;
			if (array_refeicao[i].jantar)
			{
				file << 1 << endl;
			}
			else
			{
				file << 0 << endl;
			}
			file << array_refeicao[i].data.ano << endl;
			file << array_refeicao[i].data.mes << endl;
			file << array_refeicao[i].data.dia << endl;
			file << "-" << endl;

			refeicoes_guardadas++;
		}
		else if (array_refeicao[i].numero != INT_MIN && refeicoes_guardadas == numRefeicoes)		// Se for a �ltima refeicao v�lida guarda sem colocar uma linha em branco no fim do ficheiro
		{
			file << array_refeicao[i].numero << endl;
			if (array_refeicao[i].jantar)
			{
				file << 1 << endl;
			}
			else
			{
				file << 0 << endl;
			}
			file << array_refeicao[i].data.ano << endl;
			file << array_refeicao[i].data.mes << endl;
			file << array_refeicao[i].data.dia << endl;
			file << "-";
		}
		i++;
	}
	file.close();
}

/*
L� ficheiro de dados de utilizador e carrega os dados num array
*/
void leDadosUtilizadores()
{
	wstring temp;

	int aux;

	wfstream file;

	file.open(dadU, ios::in);
	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nPressione Enter para terminar o programa.\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekg(ios::beg);

	int i = 0;

	while (i < TAMANHO)
	{
		getline(file, temp);

		aux = convert_Str_2_INT(temp);									// Guarda o valor numerico da string temp em aux

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que n�o h� utilizadores por criar pois o que foi lido j� n�o � um valor v�lido
		{
			array_util[i].numero = aux;

			getline(file, temp);
			array_util[i].nome = temp;

			getline(file, temp);
			array_util[i].nasc.dia = convert_Str_2_INT(temp);

			getline(file, temp);
			array_util[i].nasc.mes = convert_Str_2_INT(temp);

			getline(file, temp);
			array_util[i].nasc.ano = convert_Str_2_INT(temp);

			getline(file, temp);
			array_util[i].morada.rua = temp;

			getline(file, temp);
			array_util[i].morada.numPorta = temp;

			getline(file, temp);
			array_util[i].morada.codPost = temp;

			getline(file, temp);
			array_util[i].curso = temp;

			getline(file, temp);
			array_util[i].pass = temp;

			numUtils++;
			i++;
		}
		else
		{
			fillArrayBlankUtil(i);
			i = TAMANHO;
		}
	}
	file.close();
}

/*
Escreve os dados de utilizadores nos ficheiros
*/
void escreveDadosUtilizadores()
{
	wfstream file;

	file.open(dadU, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que � para come�ar o ficheiro como se fosse um novo ficheiro, apagando o conte�do presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nN�o � poss�vel guardar dados!!!\n";
		cin.sync();
		cin.get();
		exit(1);
	}
	file.clear();
	file.seekp(ios::beg);

	int i = 0;
	int utilizadores_guardados = 0;

	while (i < TAMANHO && utilizadores_guardados != numUtils)
	{
		if (array_util[i].numero != INT_MIN && utilizadores_guardados < numUtils)			// Se for um utilizador v�lido guarda caso contr�rio passa ao pr�ximo utilizador
		{
			file << array_util[i].numero << endl;
			file << array_util[i].nome << endl;
			file << array_util[i].nasc.dia << endl;
			file << array_util[i].nasc.mes << endl;
			file << array_util[i].nasc.ano << endl;
			file << array_util[i].morada.rua << endl;
			file << array_util[i].morada.numPorta << endl;
			file << array_util[i].morada.codPost << endl;
			file << array_util[i].curso << endl;
			file << array_util[i].pass << endl;

			utilizadores_guardados++;
		}
		else if (array_util[i].numero != INT_MIN && utilizadores_guardados == numUtils)		// Se for o �ltimo utilizador a guardar, guarda informa��o no ficheiro sem colocar uma linha em branco no fim
		{
			file << array_util[i].numero << endl;
			file << array_util[i].nome << endl;
			file << array_util[i].nasc.dia << endl;
			file << array_util[i].nasc.mes << endl;
			file << array_util[i].nasc.ano << endl;
			file << array_util[i].morada.rua << endl;
			file << array_util[i].morada.numPorta << endl;
			file << array_util[i].morada.codPost << endl;
			file << array_util[i].curso << endl;
			file << array_util[i].pass;
		}
		i++;
	}
	file.close();
}

/*
Cria um aluno e insere-o na lista de alunos, n�o � feito a confirma��o de alguns dados visto esta opera��o s� poder ser realizada por funcion�rios
*/
int inserirAluno()
{
	wstring nome, temp, rua, codPost, numPorta;
	int num, dia, mes, ano;

	//Pede o Nome
	wcout << "Por favor insira os dados do aluno." << endl << endl << "Nome Completo (Sem colocar acentos ou cedilhas): ";
	getline(wcin, nome);
	clrConsole();

	//Pede o Numero
	wcout << "N�mero Mecanogr�fico: ";
	getline(wcin, temp);
	num = convert_Str_2_INT(temp);
	clrConsole();

	if (num == INT_MIN)
	{
		num = valorInvalido_inserirAluno(L"N�mero Mecanogr�fico: ");
		if (num == -1)
		{
			return -1;
		}
	}

	//Pede a data de nascimento come�ando pelo ano
	wcout << "Data de nascimento" << endl << "Ano: ";
	getline(wcin, temp);
	ano = convert_Str_2_INT(temp);
	clrConsole();

	if (ano == INT_MIN)
	{
		ano = valorInvalido_inserirAluno(L"Ano: ");
		if (ano == -1)
		{
			return -1;
		}
	}

	//Pede o mes de nascimento
	wcout << "M�s(n�mero): ";
	getline(wcin, temp);
	mes = convert_Str_2_INT(temp);
	clrConsole();

	if (mes == INT_MIN)
	{
		mes = valorInvalido_inserirAluno(L"M�s(n�mero): ");
		if (mes == -1)
		{
			return -1;
		}
	}

	//Pede o dia do nascimento
	wcout << "Dia: ";
	getline(wcin, temp);
	dia = convert_Str_2_INT(temp);
	clrConsole();

	if (dia == INT_MIN)
	{
		dia = valorInvalido_inserirAluno(L"Dia: ");
		if (dia == -1)
		{
			return -1;
		}
	}

	dataNasc date;

	date.ano = ano;
	date.mes = mes;
	date.dia = dia;

	//Pede a rua da morada
	wcout << "Morada" << endl << "Rua: ";
	getline(wcin, rua);
	clrConsole();

	//Pede a porta da morada
	wcout << "N� da porta: ";
	getline(wcin, numPorta);
	clrConsole();

	//Pede o codigo postal da morada
	wcout << "C�digo Postal: ";
	getline(wcin, codPost);
	clrConsole();

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	wstring curso;

	//Pede o Curso
	wcout << "Curso: ";
	getline(wcin, curso);
	clrConsole();

	wstring Pass = PassPrompt();

	utilizador aluno;

	wchar_t conf;

	//insere os dados no ecr� excepto a password para confirma��o
	wcout << "Confirma��o de Dados" << endl;
	wcout << "N�mero Mecanogr�fico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", C�digo postal: " << mora.codPost << endl;
	wcout << "Curso: " << curso << endl << endl;
	wcout << "Os dados est�o correctos?(S/N) ";
	wcin >> conf;
	cin.sync();
	cin.get();										//Retira um ghost "ENTER"
													//Se o utilizador quiser editar os seus dados
	if (conf == L'N' || conf == L'n')
	{
		bool repeat = true;
		int answer;
		while (repeat)
		{
			clrConsole();
			wcout << "O que deseja alterar?" << endl;
			wcout << "1) N�mero Mecanogr�fico" << endl;
			wcout << "2) Nome Completo" << endl;
			wcout << "3) Data de Nascimento" << endl;
			wcout << "4) Morada" << endl;
			wcout << "5) Curso" << endl;
			wcout << "0) Terminar edi��o" << endl;
			wcout << endl << "Insira o valor da op��o pretendida: ";
			getline(wcin, temp);

			answer = convert_Str_2_INT(temp);

			if (answer < 0 || answer > 4)
			{
				wcout << endl << endl << "O valor inserido n�o � v�lido!";
				Sleep(1000);
			}
			else
			{
				clrConsole();
				switch (answer)
				{
					//Sair da edi��o
				case 0:
					wcout << endl << "Deseja mesmo sair da edi��o de aluno? (S/N) ";
					char answer;
					cin >> answer;
					if (answer == 'n' || answer == 'N')
					{
						repeat = false;
					}
					break;
					//Alterar n� mecanografico
				case 1:
					wcout << endl << "Reinsira o n�mero mecanogr�fico: ";
					getline(wcin, temp);
					num = convert_Str_2_INT(temp);

					if (num == INT_MIN)
					{
						num = valorInvalido_inserirAluno(L"N�mero Mecanogr�fico: ");
					}
					break;
					//alterar o nome
				case 2:
					wcout << endl << "Reinsira o nome: ";
					getline(wcin, nome);
					break;
					//alterar a data de nascimento
				case 3:
					wcout << endl << endl << "Data de nascimento" << endl << "Dia: ";
					getline(wcin, temp);
					dia = convert_Str_2_INT(temp);
					clrConsole();

					if (dia == INT_MIN)
					{
						dia = valorInvalido_inserirAluno(L"Dia: ");
					}

					wcout << endl << "M�s(n�mero): ";
					getline(wcin, temp);
					mes = convert_Str_2_INT(temp);
					clrConsole();

					if (mes == INT_MIN)
					{
						mes = valorInvalido_inserirAluno(L"M�s(n�mero): ");
					}

					wcout << endl << "Ano: ";
					getline(wcin, temp);
					ano = convert_Str_2_INT(temp);
					clrConsole();

					if (ano == INT_MIN)
					{
						ano = valorInvalido_inserirAluno(L"Ano: ");
					}
					date.ano = ano;
					date.mes = mes;
					date.dia = dia;
					break;
					//alterar a morada
				case 4:
					wcout << endl << endl << "Morada" << endl << "Rua: " << endl << endl;
					getline(wcin, rua);
					clrConsole();

					wcout << endl << "N� da porta: " << endl << endl;
					getline(wcin, numPorta);
					clrConsole();

					wcout << endl << "C�digo Postal: " << endl << endl;
					getline(wcin, codPost);
					clrConsole();
					break;
					//alterar o curso
				case 5:
					wcout << endl << "Reinsira o curso: ";
					getline(wcin, curso);
					break;
					//default: corre quando n�o for um valor esperado
				default:
					wcout << "Valor inv�lido!!!!";
					Sleep(500);
					break;
				}
			}
		}
	}

	aluno.morada = mora;
	aluno.nasc = date;
	aluno.nome = nome;
	aluno.numero = num;
	aluno.curso = curso;
	aluno.pass = Pass;

	int i = 0;

	//procura um espa�o vazio no array para colocar este utilizador
	while (i < TAMANHO)
	{
		if (array_util[i].numero == INT_MIN)
		{
			array_util[i] = aluno;
			numUtils++;
			break;
		}
		i++;
	}

	if (i < TAMANHO)
	{
		escreveDadosUtilizadores();		//Atualiza a informa��o da base de dados para conter este novo aluno
	}
	else
	{
		clrConsole();
		wcout << "ERRO!!!\n\nA base de dados encontra-se cheia!!!\n\nPresione a tecla Enter para prosseguir...";
		cin.sync();
		cin.get();
	}


	return 0;
}

/*
Coloca os utilizadores no array por ordem alfab�tica para facilitar a coloca��o dos utilizadores no ecr� por ordem alfab�tica
*/
void organizearray_bynames()
{
	int i = 0;
	int j;
	wstring aux_str, aux_string;
	while (i < TAMANHO)
	{
		if (array_util[i].numero != INT_MIN)
		{
			aux_str = array_util[i].nome;
			j = i + 1;
			while (j < TAMANHO)
			{
				if (array_util[j].numero != INT_MIN)
				{
					aux_string = array_util[j].nome;
					if (aux_string.compare(aux_str) > 0)
					{
						swap(array_util[j], array_util[i]);
						j = TAMANHO;
					}
				}
				j++;
			}
		}
		i++;
	}
}

/*
Realiza o login se a informa��o do utilizador constar na base de dados e o n�mero e a pass estiverem correctos
*/
bool login_logout()
{
	clrConsole();
	if (logged)
	{
		wcout << "Logout realizado com sucesso!" << endl;
		Sleep(3000);
		Util_logged = 0;
		admin = false;										//Faz logout do admin
		return false;										//Realiza um logout
	}

	int i, num;
	wstring pass;
	bool repeat = true;
	bool notAdmin = false;
	wchar_t answer;

	while (repeat)
	{
		notAdmin = false;									//Reinicia a vari�vel
		wstring temp;
		wcout << "Insira o seu n�mero mecanogr�fico: ";
		getline(wcin, temp);

		if (temp.compare(L"admin") == 0)
		{
			wcout << "Insira a password de admin: ";
			getline(wcin, pass);
			if (pass.compare(L"aminhapass") == 0)
			{
				clrConsole();
				wcout << "Bem vindo administrador!" << endl;
				admin = true;
				Util_logged = INT_MIN;
				return true;
			}
			notAdmin = true;
		}

		num = convert_Str_2_INT(temp);
		if (num == INT_MIN || notAdmin)						//notAdmin significa que alguem tentou entrar como admin mas n�o meteu a pass correcta, logo n�o faz sentido pedir novamente a pass
		{
			wcout << "N�o � um valor v�lido!!!" << endl;
			Sleep(1000);
		}
		else
		{
			wcout << "Insira a sua password: ";
			getline(wcin, pass);
			i = 0;
			while (i < TAMANHO)								//Procura, no array, por um utilizador com a informa��o que foi passada pelo utilizador do programa
			{
				if (num == array_util[i].numero && array_util[i].pass.compare(pass) == 0)
				{
					clrConsole();
					wcout << "Bem vindo " << array_util[i].nome << "!" << endl;
					Sleep(3000);
					Util_logged = num;
					return true;							//Indica que ocorreu login
				}
				i++;
			}
		}
		if (repeat)
		{
			clrConsole();
			wcout << "N�o foi poss�vel encontrar um utilizador com a informa��o que disponibilizou!!\n\nPretende tentar novamente? (S/N): ";
			wcin >> answer;
			if (answer == 'n' || answer == 'N')
			{
				return false;								//Indica que n�o ocorreu um login correcto
			}
			cin.sync();
			cin.get();										//Retira um ghost "ENTER"
			clrConsole();
		}
	}
	return false;											//Indica que n�o ocorreu um login correcto
}

/*
Imprime users por ordem alfab�tica
*/
void printUsers()
{
	organizearray_bynames();
	//organizearray_bynames();			//por alguma raz�o �s vezes n�o ordena corretamente � primeira NON ISSUE
	int i = TAMANHO - 1;
	while (i >= 0)
	{
		if (array_util[i].numero != INT_MIN)
		{
			wcout << "Nome: " << array_util[i].nome << " NUM: " << array_util[i].numero << endl;
		}
		i--;
	}

	wcout << "\n\nPrima a tecla Enter para prosseguir...";

	cin.sync();
	cin.get();
}

/*
Permite carregar plafond se nao houver informa�ao cria um novo plafond na lista
*/
int carregarPlafond()
{
	clrConsole();
	int i = 0;
	int aux;
	bool repeat = true;
	wstring temp;
	while (i < TAMANHO && repeat)
	{
		if (array_plafond[i].numero == Util_logged)
		{
			repeat = false;
		}
		else
		{
			i++;
		}
	}

	if (i < 500)
	{
		wcout << "Neste momento vo�� possui " << array_plafond[i].money << "�." << endl;
	}

	repeat = true;
	while (repeat)
	{
		wcout << "Quanto deseja carregar?? (Insira \"0\" para cancelar)\n\nValor: ";
		getline(wcin, temp);
		wcout << endl;
		aux = convert_Str_2_INT(temp);
		if (aux != INT_MIN)
		{
			if (aux == 0)				//Utilizador escolheu terminar
			{
				return 0;
			}
			wcout << "Tem a certeza que quer carregar " << aux << "�?(S/N)" << endl;
			wchar_t c;
			wcin >> c;
			cin.sync();
			cin.get();
			if (c == L's' || c == L'S')
			{
				repeat = false;
			}
		}
		else
		{
			wcout << "Valor inv�lido!!!!";
			Sleep(500);
		}
		clrConsole();
	}

	if (i == 500)				//N�o conseguiu encontrar
	{
		i = 0;
		while (i < TAMANHO)
		{
			if (array_plafond[i].numero == INT_MIN)
			{
				array_plafond[i].numero = Util_logged;
				array_plafond[i].money = aux;
				escreveDadosPlafonds();
				return 0;
			}
			i++;
		}
	}
	else
	{
		array_plafond[i].money += aux;
		escreveDadosPlafonds();
		wcout << "Ap�s o caregamento ficou com: " << array_plafond[i].money << "�." << endl;
		Sleep(500);
	}
	return 0;
}

/*
Remover alunos
*/
void removerAluno()
{
	int numAluno;
	wstring aux;
	wchar_t val;
	bool verd = true;

	while (verd)
	{
		wcout << "Qual o n�mero do aluno que pretende eliminar: ";
		getline(wcin, aux);
		numAluno = convert_Str_2_INT(aux);
		if (numAluno != INT_MIN)
		{
			verd = false;
		}
		else
		{
			wcout << "O n�mero introduzido n�o � v�lido." << endl;
			wcout << "Deseja tentar novamente?(S/N)";
			wcin >> val;
			cin.sync();
			cin.get();
			if (val != L's' || val != L'S')
			{
				return;
			}
		}
	}
	int i = 0;
	while (i < TAMANHO)
	{
		if (numAluno == array_util[i].numero)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	if (i < TAMANHO)						// Se encontrar um aluno com este numero...
	{
		wcout << "N�mero: " << array_util[i].numero << endl << "Nome: " << array_util[i].nome << endl << "Data de Nascimento: " <<
			array_util[i].nasc.ano << "-" << array_util[i].nasc.mes << "-" << array_util[i].nasc.dia << endl << "Morada: " <<
			array_util[i].morada.rua << ", n� " << array_util[i].morada.numPorta << endl << "C�digo Postal: " << array_util[i].morada.codPost <<
			endl << "Curso: " << array_util[i].curso << endl << endl;
		wcout << "Tem a certeza que quer eliminar o aluno n� " << numAluno << "?(S/N)";
		wcin >> val;
		cin.sync();
		cin.get();
		if (val == L's' || val == L'S')
		{
			utilizador utilizador_remove;
			utilizador_remove.numero = INT_MIN;
			array_util[i] = utilizador_remove;
			numUtils--;
			escreveDadosUtilizadores();
			i = 0;
			while (i < TAMANHO)
			{
				if (numAluno == array_plafond[i].numero)
				{
					break;
				}
				else
				{
					i++;
				}
			}
			if (i < TAMANHO)
			{
				plafond plafond_remove;
				plafond_remove.numero = INT_MIN;
				array_plafond[i] = plafond_remove;
				numPlafonds--;
				escreveDadosPlafonds();
			}
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		wcout << "O utilizador com o n� " << numAluno << " n�o foi encontrado" << endl;
		Sleep(500);
		return;
	}
}

/*
Pesquisar pelo primeiro nome
*/
void primNome()
{
	wstring temp, aux, nomeP;
	int i = 0;														// Inicializa i a zero
	int r = 0;														// Inicializa r a zero
	wcout << "Qual � o nome que quer procurar (primeiro nome)? ";	// Pede ao utilizador o nome que pretende procurar
	getline(wcin, nomeP);											// Guarda em momeP o nome inserido pelo utilizador
	while (i < TAMANHO)												// Enquanto o tamanho do array for menor...
	{
		if (array_util[i].numero != INT_MIN)						// Verifica se o n�mero � v�lido
		{
			aux = array_util[i].nome;								// Coloca em aux o nome do utilizador
			wstring::size_type pos = aux.find(' ');					// Guarda em pos a posi��o do primeiro ' '(espa�o)
			if (pos != string::npos)								// Se a posi��o do espa�o for diferente da �ltima posi��o da string...
			{
				temp = aux.substr(0, pos);							// Guarda em temp o primeiro nome do aluno, que vai da posi��o 0 at� � posi��o do espa�o, guardado em pos
				if (temp.compare(nomeP) == 0)						// Se o nome guardado em temp for igual ao nome inserido...
				{
					wcout << endl << "N�mero: " << array_util[i].numero << "  Nome: " << array_util[i].nome << endl << endl;
					r++;											// Incrementa a var�avel que d� a quantidade de registos encontrados
				}
			}
		}
		i++;														// Passa para o aluno seguinte
	}
	wcout << "N�mero de resultados encontrados: " << r << endl << endl;
	wcout << "Para prosseguir pressione Enter. ";
	cin.sync();														// Sincroniza o teclado
	cin.get();														// Detecta o utilizador a pressionar a tecla Enter
}

/*
Listar Refei��es
*/
void listarRefeicao()
{
	wstring aux;
	int num, i;
	int r = 0;														// Inicializa i a zero
	wcout << "Deseja listar as refei��es de que aluno? (N�mero Mecanogr�fico ou 0 para todos os alunos) ";
	getline(wcin, aux);												// Guarda em aux o valor inserido
	num = convert_Str_2_INT(aux);									// Converte a string em int

	if (num != INT_MIN)												// Se a int inserida for v�lida, isto �, se for realmente um valor n�m�rico...
	{
		if (num == 0)												// Se o valor for zero...
		{
			i = 0;													// Inicializa i a zero
			while (i < TAMANHO)										// Enquanto i for menor que o tamanho do array...
			{
				if (array_refeicao[i].numero != INT_MIN)			// Se existe uma refei��o v�lida para aquele aluno...
				{
					if (array_refeicao[i].jantar)					// Se a refei��o � jantar...
					{
						wcout << endl << "N�mero: " << array_refeicao[i].numero << "  Refei��o: Jantar  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					else
					{
						wcout << endl << "N�mero: " << array_refeicao[i].numero << "  Refei��o: Almo�o  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					r++;											// Incrementa o n�mero de refei��es encontradas
				}
				i++;												// Incrementa a posi��o do array
			}
		}
		else														// Se foi inserido um n�mero mecanogr�fico...
		{
			i = 0;													// Inicializa i a zero
			while (i < TAMANHO)										// Enquanto i for menor que o tamanho do array...
			{
				if (num == array_refeicao[i].numero)				// Se existe uma refei��o encomendada pelo aluno cujo n�mero foi inserido...
				{
					if (array_refeicao[i].jantar)					// Se for jantar...
					{
						wcout << endl << "N�mero: " << array_refeicao[i].numero << "  Refei��o: Jantar  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					else
					{
						wcout << endl << "N�mero: " << array_refeicao[i].numero << "  Refei��o: Almo�o  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					r++;											// Incrementa a quantidade de refei��es encontradas para o aluno
				}
				i++;												// Incrementa a posi��o do array
			}
		}
		wcout << "\nN�mero total de refei��es encontradas: " << r << endl << endl;
		wcout << "Pressione a tecla Enter para prosseguir...";
		cin.sync();													// Sincroniza o teclado
		cin.get();													// Detecta o utilizador a pressionar a tecla Enter
	}
}

/*
Encomendar Refei��es
*/
void encomendarRefeicao()
{
	wstring aux;
	int num;
	int i = 0;
	while (i < TAMANHO)
	{
		if (array_plafond[i].numero == Util_logged)
		{
			if (array_plafond[i].money < 3)
			{
				wcout << "N�o tem saldo suficiente para encomendar refei��es." << endl << endl;
				wcout << "Pressione a tecla Enter para prosseguir...";
				cin.sync();
				cin.get();
				return;
			}
			else
			{
				break;
			}
		}
		else
		{
			i++;
		}
	}
	if (i == TAMANHO)
	{
		wcout << "N�o tem saldo suficiente para encomendar refei��es." << endl << endl;
		wcout << "Pressione a tecla Enter para prosseguir...";
		cin.sync();
		cin.get();
		return;
	}
	else
	{
		bool repeat = true;
		while (repeat)
		{
			wcout << "Qual a quantidade de refei��es que quer encomendar? (Insira 0 para sair) ";
			getline(wcin, aux);
			num = convert_Str_2_INT(aux);
			if (num < 0)
			{
				wcout << "o valor incerido � inv�lido.";
				Sleep(500);
				clrConsole();
			}
			else if (num == 0)
			{
				return;
			}
			else
			{
				if (array_plafond[i].money < (num * 3))
				{
					wcout << "O seu plafond n�o premite encomendar " << num << " refei��es." << endl;
					Sleep(500);
					clrConsole();
				}
				else
				{
					break;
				}
			}
		}
		int j = 0;
		wstring temp;
		int ano, mes, dia;
		while (j < num)
		{
			//Pede a data de nascimento come�ando pelo ano
			wcout << "Data da refei��o n� " << j + 1 << endl << "Ano: ";
			getline(wcin, temp);
			ano = convert_Str_2_INT(temp);
			clrConsole();

			if (ano == INT_MIN)
			{
				ano = valorInvalido_inserirAluno(L"Ano: ");
				if (ano == -1)
				{
					return;
				}
			}

			//Pede o mes de nascimento
			wcout << "M�s(n�mero): ";
			getline(wcin, temp);
			mes = convert_Str_2_INT(temp);
			clrConsole();

			if (mes == INT_MIN)
			{
				mes = valorInvalido_inserirAluno(L"M�s(n�mero): ");
				if (mes == -1)
				{
					return;
				}
			}

			//Pede o dia do nascimento
			wcout << "Dia: ";
			getline(wcin, temp);
			dia = convert_Str_2_INT(temp);
			clrConsole();

			if (dia == INT_MIN)
			{
				dia = valorInvalido_inserirAluno(L"Dia: ");
				if (dia == -1)
				{
					return;
				}
			}

			if (dateValid(ano, mes, dia))
			{
				bool jantar;
				repeat = true;

				clrConsole();

				while (repeat)
				{
					wcout << "1 - Almo�o" << endl;
					wcout << "2 - Jantar" << endl;
					wcout << "Op��o: ";
					getline(wcin, aux);
					if (convert_Str_2_INT(aux) == 1)
					{
						jantar = false;
						repeat = false;
					}
					else if (convert_Str_2_INT(aux) == 2)
					{
						jantar = true;
						repeat = false;
					}
					else
					{
						wcout << "Op��o Inv�lida" << endl;
						Sleep(500);
						clrConsole();
					}
				}

				refeicao food;
				food.data.ano = ano;
				food.data.mes = mes;
				food.data.dia = dia;
				food.numero = Util_logged;
				food.jantar = jantar;

				j = 0;

				while (j < (TAMANHO * 10))
				{
					if (array_refeicao[j].numero == INT_MIN)
					{
						array_refeicao[j] = food;
						numRefeicoes++;
						array_plafond[i].money -= 3;
						escreveDadosPlafonds();
						escreveDadosRefeicoes();
						break;
					}
					j++;
				}
				if (j == (TAMANHO * 10))
				{
					wcout << "N�o � poss�vel encomendar mais refei��es." << endl;
					Sleep(500);
					clrConsole();
					return;
				}
			}
		}
	}
}

/*
Consumir Refei��o
*/
void consumirRefei��o()
{
	int i = 0;
	int num, op;
	wstring aux, temp;
	wcout << "N� do aluno: ";
	getline(wcin, aux);
	num = convert_Str_2_INT(aux);
	if (num != INT_MIN)
	{
		wcout << "1 - Almo�o" << endl << "2 - Jantar" << endl << "Op��o: ";
		getline(wcin, aux);
		op = convert_Str_2_INT(aux);
		if (op == 1)
		{
			while (i < (TAMANHO * 10))
			{
				if (array_refeicao[i].numero == num && array_refeicao[i].jantar == false)
				{
					if (dataVerifica(array_refeicao[i].data.ano, array_refeicao[i].data.mes, array_refeicao[i].data.dia))
					{
						refeicao ref;
						ref.numero = INT_MIN;
						array_refeicao[i] = ref;
						wcout << "A refei��o foi removida com sucesso." << endl;
						Sleep(500);
						escreveDadosRefeicoes();
					}
					else
					{
						wcout << "A data dessa refei��o n�o corresponde � do dia de hoje." << endl;
						Sleep(500);
					}
				}
				i++;
			}
		}
		else if (op == 2)
		{
			while (i < (TAMANHO * 10))
			{
				if (array_refeicao[i].numero == num && array_refeicao[i].jantar == true)
				{
					if (dataVerifica(array_refeicao[i].data.ano, array_refeicao[i].data.mes, array_refeicao[i].data.dia))
					{
						refeicao ref;
						ref.numero = INT_MIN;
						array_refeicao[i] = ref;
						wcout << "A refei��o foi removida com sucesso." << endl;
						Sleep(500);
						escreveDadosRefeicoes();
					}
					else
					{
						wcout << "A data dessa refei��o n�o corresponde � do dia de hoje." << endl;
						Sleep(500);
					}
				}
				i++;
			}
		}
		else
		{
			wcout << "Op��o inv�lida.";
		}
	}
	else
	{
		wcout << "O valor inserido n�o � v�lido. ";
	}
}

/*
Coloca o menu principal no ecr� e realiza fun��es consoante a op��o escolhida pelo utilizador.
*/
void printMainMenu()
{
	wstring resposta;
	int resposta_int;
	bool quit = false;

	leDadosUtilizadores();
	leDadosPlafonds();
	leDadosRefeicoes();

	while (!quit)
	{
		clrConsole();
		//	Imprime texto no ecr�.
		if (!logged)
		{
			wcout << "Bem vindo ao primeiro projecto de EDA." << endl;
			wcout << "\nEscolha a op��o pretendida.\n" << endl;
			wcout << "1. Login.\n\nOpc�o: ";
		}
		else
		{
			wcout << "Escolha a op��o pretendida.\n" << endl;
			wcout << "1. Logout." << endl;
		}

		if (admin && logged) // se o utilizador que estiver logged in for um admin
		{
			wcout << "2. Inserir alunos\n"
				<< "3. Pesquisar pelo Primeiro Nome\n"
				//<< "4. Pesquisar pelo N�mero\n"
				<< "4. Lista alunos por Ordem Alfabetica\n"		//Por enquanto � a quarta, mais para a frente ir� ser a quinta op��o
																//<< "6. Alterar alunos\n"
				<< "5. Remover alunos\n"						//O mesmo que acima	
				<< "6. Consumir Refeic�o\n"						//O mesmo que acima	
				<< "7. Listar refei��es\n"						//O mesmo que acima	
																//<< "10. Listar refei��es num determinado dia\n"
				<< "\nOp��o: ";
		}
		else if (!admin && logged) // se o utilizador n estiver logged in n no admin
		{
			wcout << "2. Encomendar refei��o\n"
				<< "3. Carregar plafond\n"
				<< "\nOp��o: ";
		}

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

			if (resposta_int == 1) // Independentemente se � um admin logado ou utilizador normal ou se simplesmente n�o est� logged in � uma op��o v�lida
			{
				logged = login_logout();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu inserir aluno.\n\n";
				Sleep(1000);
				clrConsole();
				inserirAluno();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && !admin)	// Se tiver um utilizador normal logado isto � uma op��o v�lida para ele
			{
				clrConsole();
				wcout << "Escolheu encomendar refei��o.\n\n";
				Sleep(1000);
				encomendarRefeicao();
				clrConsole();
			}
			else if (resposta_int == 3 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu pesquisar pelo primeiro nome.\n\n";
				Sleep(1000);
				primNome();
				Sleep(500);
				clrConsole();
			}
			else if (resposta_int == 3 && logged && !admin)	// Se tiver um utilizador normal logado isto � uma op��o v�lida para ele
			{
				clrConsole();
				wcout << "Escolheu carregar plafond.\n\n";
				Sleep(1000);
				carregarPlafond();
				clrConsole();
			}
			/*else if (resposta_int == 4 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
			clrConsole();
			wcout << "Escolheu pesquisar pelo n�mero\n";
			Sleep(1000);
			clrConsole();
			}*/
			else if (resposta_int == 4/*5*/ && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu listar alunos por ordem alfab�tica.\n\n";
				Sleep(1000);
				printUsers();
				clrConsole();
			}
			/*else if (resposta_int == 6 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
			clrConsole();
			wcout << "Escolheu alterar alunos\n";
			Sleep(1000);
			clrConsole();
			}*/
			else if (resposta_int == 5/*7*/ && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover alunos.\n";
				Sleep(1000);
				removerAluno();
				clrConsole();
			}

			else if (resposta_int == 6/*8*/ && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover refei��o.\n";
				Sleep(1000);
				consumirRefei��o();
				Sleep(500);
				clrConsole();
			}
			else if (resposta_int == 7/*9*/ && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
				clrConsole();
				wcout << "Escolheu listar refei��es.\n";
				Sleep(1000);
				listarRefeicao();
				Sleep(500);
				clrConsole();
			}
			//else if (resposta_int == 10 && logged && admin)	// se tiver um admin logado isto � uma op��o v�lida para o administrador
			//{
			//	clrconsole();
			//	wcout << "escolheu listar refei��es num determinado dia.\n";
			//	sleep(1000);
			//	clrconsole();
			//}
			else													// Se a op��o inserida pelo utilizador n�o � v�lida.
			{
				clrConsole();
				wcout << "Escolheu a op��o errada\nPor favor escolha a(s) op��o/op��es dispon�veis\n";
				Sleep(1000);
				clrConsole();
			}


		}
	}
}

/* Mecanismo de listar refeicoes num determinada dia */
/* Ideia: Escolher o dia e usar uma tecnica semelhante como foi feito o mecanismo de listar refeicoes*/
void verListaDiaDeterminado()
{

}



