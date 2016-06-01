#pragma once

#include "Struct.h"
#include "Other_Functions.h"
#include "Functions.h"

/*
ATENÇÂO:	Neste ficheiro encontram-se todas as funções que necessitem de variáveis globais!!!
*/

bool logged = false;							// O utilizador esta logged in ou não
bool admin = false;								// O utilizador é funcionário ou não
int const TAMANHO = 500;						// Tamanho dos arrays
int Util_logged;								// Numero mecanografico do ultimo/atual utilizador logged in
utilizador array_util[TAMANHO];					// Array de utilizadores
plafond array_plafond[TAMANHO];					// Array de plafonds
refeicao array_refeicao[TAMANHO * 10];			// Array de refeicoes
wchar_t dadU[50] = L"BaseDados.txt";			// Nome do ficheiro contendo a informação dos utilizadores 
wchar_t dadP[50] = L"Plafond.txt";				// Nome do ficheiro contendo a informação dos plafonds
wchar_t dadR[50] = L"Refeicoes.txt";			// Nome do ficheiro contendo a informação dos plafonds
int numUtils = 0;								// Numero total de utilizadores
int numPlafonds = 0;							// Numero total de utilizadores com plafond
int numRefeicoes = 0;							// Numero total de refeicoes

												/*
												Preenche o resto dos utilizadores com informação que seja fácil para nós descartarmos esse utilizador como inválido
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
Preenche o resto dos utilizadores com informação que seja fácil para nós descartarmos esse utilizador como inválido
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
Preenche o resto dos utilizadores com informação que seja fácil para nós descartarmos esse utilizador como inválido
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

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que não há utilizadores por criar pois o que foi lido já não é um valor válido
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

	file.open(dadP, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que é para começar o ficheiro como se fosse um novo ficheiro, apagando o conteúdo presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nNão é possível guardar dados!!!\n";
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
		if (array_plafond[i].numero != INT_MIN && plafonds_guardados < numPlafonds)			// Se for um plafond válido guarda caso contrário passa ao próximo plafond
		{
			file << array_plafond[i].numero << endl;
			file << array_plafond[i].money << endl;
			file << "-" << endl;

			plafonds_guardados++;
		}
		else if (array_plafond[i].numero != INT_MIN && plafonds_guardados == numPlafonds)		// Se for o último plafond válido guarda sem colocar uma linha em branco no fim do ficheiro
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
Le a informação relativa às refeições e coloca-a no array respectivo
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

			//Se for uma data anterior à atual descarta-a 
			if (dateValid(array_refeicao[i].data.ano, array_refeicao[i].data.mes, array_refeicao[i].data.dia))
			{
				numRefeicoes++;
				i++;
			}
			else
			{
				refeicao ref;
				ref.numero = INT_MIN;
				array_refeicao[i] = ref;	//Substitui por refeição inválida e irá fazer overwrite desta informação se ainda faltar refeições por meter no array
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

	file.open(dadR, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que é para começar o ficheiro como se fosse um novo ficheiro, apagando o conteúdo presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nNão é possível guardar dados!!!\n";
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
		if (array_refeicao[i].numero != INT_MIN && refeicoes_guardadas < numRefeicoes)			// Se for uma refeicao válida guarda caso contrário passa à próxima refeicao
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
		else if (array_refeicao[i].numero != INT_MIN && refeicoes_guardadas == numRefeicoes)		// Se for a última refeicao válida guarda sem colocar uma linha em branco no fim do ficheiro
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
Lê ficheiro de dados de utilizador e carrega os dados num array
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

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que não há utilizadores por criar pois o que foi lido já não é um valor válido
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

	file.open(dadU, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que é para começar o ficheiro como se fosse um novo ficheiro, apagando o conteúdo presente anteriormente

	if (!file)
	{
		wcout << "\nErro, ficheiros corruptos.\nNão é possível guardar dados!!!\n";
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
		if (array_util[i].numero != INT_MIN && utilizadores_guardados < numUtils)			// Se for um utilizador válido guarda caso contrário passa ao próximo utilizador
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
		else if (array_util[i].numero != INT_MIN && utilizadores_guardados == numUtils)		// Se for o último utilizador a guardar, guarda informação no ficheiro sem colocar uma linha em branco no fim
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
Cria um aluno e insere-o na lista de alunos, não é feito a confirmação de alguns dados visto esta operação só poder ser realizada por funcionários
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
	wcout << "Número Mecanográfico: ";
	getline(wcin, temp);
	num = convert_Str_2_INT(temp);
	clrConsole();

	if (num == INT_MIN)
	{
		num = valorInvalido_inserirAluno(L"Número Mecanográfico: ");
		if (num == -1)
		{
			return -1;
		}
	}

	//Pede a data de nascimento começando pelo ano
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
	wcout << "Mês(número): ";
	getline(wcin, temp);
	mes = convert_Str_2_INT(temp);
	clrConsole();

	if (mes == INT_MIN)
	{
		mes = valorInvalido_inserirAluno(L"Mês(número): ");
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
	wcout << "Nº da porta: ";
	getline(wcin, numPorta);
	clrConsole();

	//Pede o codigo postal da morada
	wcout << "Código Postal: ";
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

	//insere os dados no ecrã excepto a password para confirmação
	wcout << "Confirmação de Dados" << endl;
	wcout << "Número Mecanográfico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", Código postal: " << mora.codPost << endl;
	wcout << "Curso: " << curso << endl << endl;
	wcout << "Os dados estão correctos?(S/N) ";
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
			wcout << "1) Número Mecanográfico" << endl;
			wcout << "2) Nome Completo" << endl;
			wcout << "3) Data de Nascimento" << endl;
			wcout << "4) Morada" << endl;
			wcout << "5) Curso" << endl;
			wcout << "0) Terminar edição" << endl;
			wcout << endl << "Insira o valor da opção pretendida: ";
			getline(wcin, temp);

			answer = convert_Str_2_INT(temp);

			if (answer < 0 || answer > 4)
			{
				wcout << endl << endl << "O valor inserido não é válido!";
				Sleep(1000);
			}
			else
			{
				clrConsole();
				switch (answer)
				{
					//Sair da edição
				case 0:
					wcout << endl << "Deseja mesmo sair da edição de aluno? (S/N) ";
					char answer;
					cin >> answer;
					if (answer == 'n' || answer == 'N')
					{
						repeat = false;
					}
					break;
					//Alterar nº mecanografico
				case 1:
					wcout << endl << "Reinsira o número mecanográfico: ";
					getline(wcin, temp);
					num = convert_Str_2_INT(temp);

					if (num == INT_MIN)
					{
						num = valorInvalido_inserirAluno(L"Número Mecanográfico: ");
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

					wcout << endl << "Mês(número): ";
					getline(wcin, temp);
					mes = convert_Str_2_INT(temp);
					clrConsole();

					if (mes == INT_MIN)
					{
						mes = valorInvalido_inserirAluno(L"Mês(número): ");
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

					wcout << endl << "Nº da porta: " << endl << endl;
					getline(wcin, numPorta);
					clrConsole();

					wcout << endl << "Código Postal: " << endl << endl;
					getline(wcin, codPost);
					clrConsole();
					break;
					//alterar o curso
				case 5:
					wcout << endl << "Reinsira o curso: ";
					getline(wcin, curso);
					break;
					//default: corre quando não for um valor esperado
				default:
					wcout << "Valor inválido!!!!";
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

	//procura um espaço vazio no array para colocar este utilizador
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
		escreveDadosUtilizadores();		//Atualiza a informação da base de dados para conter este novo aluno
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
Coloca os utilizadores no array por ordem alfabética para facilitar a colocação dos utilizadores no ecrã por ordem alfabética
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
Realiza o login se a informação do utilizador constar na base de dados e o número e a pass estiverem correctos
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
		notAdmin = false;									//Reinicia a variável
		wstring temp;
		wcout << "Insira o seu número mecanográfico: ";
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
		if (num == INT_MIN || notAdmin)						//notAdmin significa que alguem tentou entrar como admin mas não meteu a pass correcta, logo não faz sentido pedir novamente a pass
		{
			wcout << "Não é um valor válido!!!" << endl;
			Sleep(1000);
		}
		else
		{
			wcout << "Insira a sua password: ";
			getline(wcin, pass);
			i = 0;
			while (i < TAMANHO)								//Procura, no array, por um utilizador com a informação que foi passada pelo utilizador do programa
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
			wcout << "Não foi possível encontrar um utilizador com a informação que disponibilizou!!\n\nPretende tentar novamente? (S/N): ";
			wcin >> answer;
			if (answer == 'n' || answer == 'N')
			{
				return false;								//Indica que não ocorreu um login correcto
			}
			cin.sync();
			cin.get();										//Retira um ghost "ENTER"
			clrConsole();
		}
	}
	return false;											//Indica que não ocorreu um login correcto
}

/*
Imprime users por ordem alfabética
*/
void printUsers()
{
	organizearray_bynames();
	//organizearray_bynames();			//por alguma razão às vezes não ordena corretamente à primeira NON ISSUE
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
Permite carregar plafond se nao houver informaçao cria um novo plafond na lista
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
		wcout << "Neste momento voçê possui " << array_plafond[i].money << "€." << endl;
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
			wcout << "Tem a certeza que quer carregar " << aux << "€?(S/N)" << endl;
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
			wcout << "Valor inválido!!!!";
			Sleep(500);
		}
		clrConsole();
	}

	if (i == 500)				//Não conseguiu encontrar
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
		wcout << "Após o caregamento ficou com: " << array_plafond[i].money << "€." << endl;
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
		wcout << "Qual o número do aluno que pretende eliminar: ";
		getline(wcin, aux);
		numAluno = convert_Str_2_INT(aux);
		if (numAluno != INT_MIN)
		{
			verd = false;
		}
		else
		{
			wcout << "O número introduzido não é válido." << endl;
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
		wcout << "Número: " << array_util[i].numero << endl << "Nome: " << array_util[i].nome << endl << "Data de Nascimento: " <<
			array_util[i].nasc.ano << "-" << array_util[i].nasc.mes << "-" << array_util[i].nasc.dia << endl << "Morada: " <<
			array_util[i].morada.rua << ", nº " << array_util[i].morada.numPorta << endl << "Código Postal: " << array_util[i].morada.codPost <<
			endl << "Curso: " << array_util[i].curso << endl << endl;
		wcout << "Tem a certeza que quer eliminar o aluno nº " << numAluno << "?(S/N)";
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
		wcout << "O utilizador com o nº " << numAluno << " não foi encontrado" << endl;
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
	wcout << "Qual é o nome que quer procurar (primeiro nome)? ";	// Pede ao utilizador o nome que pretende procurar
	getline(wcin, nomeP);											// Guarda em momeP o nome inserido pelo utilizador
	while (i < TAMANHO)												// Enquanto o tamanho do array for menor...
	{
		if (array_util[i].numero != INT_MIN)						// Verifica se o número é válido
		{
			aux = array_util[i].nome;								// Coloca em aux o nome do utilizador
			wstring::size_type pos = aux.find(' ');					// Guarda em pos a posição do primeiro ' '(espaço)
			if (pos != string::npos)								// Se a posição do espaço for diferente da última posição da string...
			{
				temp = aux.substr(0, pos);							// Guarda em temp o primeiro nome do aluno, que vai da posição 0 até à posição do espaço, guardado em pos
				if (temp.compare(nomeP) == 0)						// Se o nome guardado em temp for igual ao nome inserido...
				{
					wcout << endl << "Número: " << array_util[i].numero << "  Nome: " << array_util[i].nome << endl << endl;
					r++;											// Incrementa a varíavel que dá a quantidade de registos encontrados
				}
			}
		}
		i++;														// Passa para o aluno seguinte
	}
	wcout << "Número de resultados encontrados: " << r << endl << endl;
	wcout << "Para prosseguir pressione Enter. ";
	cin.sync();														// Sincroniza o teclado
	cin.get();														// Detecta o utilizador a pressionar a tecla Enter
}

/*
Listar Refeições
*/
void listarRefeicao()
{
	wstring aux;
	int num, i;
	int r = 0;														// Inicializa i a zero
	wcout << "Deseja listar as refeições de que aluno? (Número Mecanográfico ou 0 para todos os alunos) ";
	getline(wcin, aux);												// Guarda em aux o valor inserido
	num = convert_Str_2_INT(aux);									// Converte a string em int

	if (num != INT_MIN)												// Se a int inserida for válida, isto é, se for realmente um valor númérico...
	{
		if (num == 0)												// Se o valor for zero...
		{
			i = 0;													// Inicializa i a zero
			while (i < TAMANHO)										// Enquanto i for menor que o tamanho do array...
			{
				if (array_refeicao[i].numero != INT_MIN)			// Se existe uma refeição válida para aquele aluno...
				{
					if (array_refeicao[i].jantar)					// Se a refeição é jantar...
					{
						wcout << endl << "Número: " << array_refeicao[i].numero << "  Refeição: Jantar  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					else
					{
						wcout << endl << "Número: " << array_refeicao[i].numero << "  Refeição: Almoço  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					r++;											// Incrementa o número de refeições encontradas
				}
				i++;												// Incrementa a posição do array
			}
		}
		else														// Se foi inserido um número mecanográfico...
		{
			i = 0;													// Inicializa i a zero
			while (i < TAMANHO)										// Enquanto i for menor que o tamanho do array...
			{
				if (num == array_refeicao[i].numero)				// Se existe uma refeição encomendada pelo aluno cujo número foi inserido...
				{
					if (array_refeicao[i].jantar)					// Se for jantar...
					{
						wcout << endl << "Número: " << array_refeicao[i].numero << "  Refeição: Jantar  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					else
					{
						wcout << endl << "Número: " << array_refeicao[i].numero << "  Refeição: Almoço  Data: "
							<< array_refeicao[i].data.dia << "-" << array_refeicao[i].data.mes << "-" << array_refeicao[i].data.ano << endl;
					}
					r++;											// Incrementa a quantidade de refeições encontradas para o aluno
				}
				i++;												// Incrementa a posição do array
			}
		}
		wcout << "\nNúmero total de refeições encontradas: " << r << endl << endl;
		wcout << "Pressione a tecla Enter para prosseguir...";
		cin.sync();													// Sincroniza o teclado
		cin.get();													// Detecta o utilizador a pressionar a tecla Enter
	}
}

/*
Encomendar Refeições
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
				wcout << "Não tem saldo suficiente para encomendar refeições." << endl << endl;
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
		wcout << "Não tem saldo suficiente para encomendar refeições." << endl << endl;
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
			wcout << "Qual a quantidade de refeições que quer encomendar? (Insira 0 para sair) ";
			getline(wcin, aux);
			num = convert_Str_2_INT(aux);
			if (num < 0)
			{
				wcout << "o valor incerido é inválido.";
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
					wcout << "O seu plafond não premite encomendar " << num << " refeições." << endl;
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
			//Pede a data de nascimento começando pelo ano
			wcout << "Data da refeição nº " << j + 1 << endl << "Ano: ";
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
			wcout << "Mês(número): ";
			getline(wcin, temp);
			mes = convert_Str_2_INT(temp);
			clrConsole();

			if (mes == INT_MIN)
			{
				mes = valorInvalido_inserirAluno(L"Mês(número): ");
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
					wcout << "1 - Almoço" << endl;
					wcout << "2 - Jantar" << endl;
					wcout << "Opção: ";
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
						wcout << "Opção Inválida" << endl;
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
					wcout << "Não é possível encomendar mais refeições." << endl;
					Sleep(500);
					clrConsole();
					return;
				}
			}
		}
	}
}

/*
Consumir Refeição
*/
void consumirRefeição()
{
	int i = 0;
	int num, op;
	wstring aux, temp;
	wcout << "Nº do aluno: ";
	getline(wcin, aux);
	num = convert_Str_2_INT(aux);
	if (num != INT_MIN)
	{
		wcout << "1 - Almoço" << endl << "2 - Jantar" << endl << "Opção: ";
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
						wcout << "A refeição foi removida com sucesso." << endl;
						Sleep(500);
						escreveDadosRefeicoes();
					}
					else
					{
						wcout << "A data dessa refeição não corresponde à do dia de hoje." << endl;
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
						wcout << "A refeição foi removida com sucesso." << endl;
						Sleep(500);
						escreveDadosRefeicoes();
					}
					else
					{
						wcout << "A data dessa refeição não corresponde à do dia de hoje." << endl;
						Sleep(500);
					}
				}
				i++;
			}
		}
		else
		{
			wcout << "Opção inválida.";
		}
	}
	else
	{
		wcout << "O valor inserido não é válido. ";
	}
}

/*
Coloca o menu principal no ecrã e realiza funções consoante a opção escolhida pelo utilizador.
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
		//	Imprime texto no ecrã.
		if (!logged)
		{
			wcout << "Bem vindo ao primeiro projecto de EDA." << endl;
			wcout << "\nEscolha a opção pretendida.\n" << endl;
			wcout << "1. Login.\n\nOpcão: ";
		}
		else
		{
			wcout << "Escolha a opção pretendida.\n" << endl;
			wcout << "1. Logout." << endl;
		}

		if (admin && logged) // se o utilizador que estiver logged in for um admin
		{
			wcout << "2. Inserir alunos\n"
				<< "3. Pesquisar pelo Primeiro Nome\n"
				//<< "4. Pesquisar pelo Número\n"
				<< "4. Lista alunos por Ordem Alfabetica\n"		//Por enquanto é a quarta, mais para a frente irá ser a quinta opção
																//<< "6. Alterar alunos\n"
				<< "5. Remover alunos\n"						//O mesmo que acima	
				<< "6. Consumir Refeicão\n"						//O mesmo que acima	
				<< "7. Listar refeições\n"						//O mesmo que acima	
																//<< "10. Listar refeições num determinado dia\n"
				<< "\nOpção: ";
		}
		else if (!admin && logged) // se o utilizador n estiver logged in n no admin
		{
			wcout << "2. Encomendar refeição\n"
				<< "3. Carregar plafond\n"
				<< "\nOpção: ";
		}

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

			if (resposta_int == 1) // Independentemente se é um admin logado ou utilizador normal ou se simplesmente não está logged in é uma opção válida
			{
				logged = login_logout();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu inserir aluno.\n\n";
				Sleep(1000);
				clrConsole();
				inserirAluno();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && !admin)	// Se tiver um utilizador normal logado isto é uma opção válida para ele
			{
				clrConsole();
				wcout << "Escolheu encomendar refeição.\n\n";
				Sleep(1000);
				encomendarRefeicao();
				clrConsole();
			}
			else if (resposta_int == 3 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu pesquisar pelo primeiro nome.\n\n";
				Sleep(1000);
				primNome();
				Sleep(500);
				clrConsole();
			}
			else if (resposta_int == 3 && logged && !admin)	// Se tiver um utilizador normal logado isto é uma opção válida para ele
			{
				clrConsole();
				wcout << "Escolheu carregar plafond.\n\n";
				Sleep(1000);
				carregarPlafond();
				clrConsole();
			}
			/*else if (resposta_int == 4 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
			clrConsole();
			wcout << "Escolheu pesquisar pelo número\n";
			Sleep(1000);
			clrConsole();
			}*/
			else if (resposta_int == 4/*5*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu listar alunos por ordem alfabética.\n\n";
				Sleep(1000);
				printUsers();
				clrConsole();
			}
			/*else if (resposta_int == 6 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
			clrConsole();
			wcout << "Escolheu alterar alunos\n";
			Sleep(1000);
			clrConsole();
			}*/
			else if (resposta_int == 5/*7*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover alunos.\n";
				Sleep(1000);
				removerAluno();
				clrConsole();
			}

			else if (resposta_int == 6/*8*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover refeição.\n";
				Sleep(1000);
				consumirRefeição();
				Sleep(500);
				clrConsole();
			}
			else if (resposta_int == 7/*9*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu listar refeições.\n";
				Sleep(1000);
				listarRefeicao();
				Sleep(500);
				clrConsole();
			}
			//else if (resposta_int == 10 && logged && admin)	// se tiver um admin logado isto é uma opção válida para o administrador
			//{
			//	clrconsole();
			//	wcout << "escolheu listar refeições num determinado dia.\n";
			//	sleep(1000);
			//	clrconsole();
			//}
			else													// Se a opção inserida pelo utilizador não é válida.
			{
				clrConsole();
				wcout << "Escolheu a opção errada\nPor favor escolha a(s) opção/opções disponíveis\n";
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



