#pragma once

#include "Struct.h"

bool logged = false;							// O utilizador esta logged in ou não
bool admin = false;								// O utilizador é funcionário ou não
int const TAMANHO = 500;						// Tamanho dos arrays
int Util_logged;								// Numero mecanografico do ultimo/atual utilizador logged in
utilizador array_util[TAMANHO];					// Array de utilizadores
plafond array_plafond[TAMANHO];					// Array de plafonds
wchar_t dadU[50] = L"BaseDados.txt";			// Nome do ficheiro contendo a informação dos utilizadores 
wchar_t dadP[50] = L"Plafond.txt";				// Nome do ficheiro contendo a informação dos plafonds
int numUtils = 0;								// Numero total de utilizadores
int numPlafonds = 0;							// Numero total de utilizadores com plafond

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

			plafonds_guardados++;
		}
		else if (array_plafond[i].numero != INT_MIN && plafonds_guardados == numPlafonds)		// Se for o último plafond válido guarda sem colocar uma linha em branco no fim do ficheiro
		{
			file << array_plafond[i].numero << endl;
			file << array_plafond[i].money << endl;
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
			file << array_util[i].pass;
		}
		i++;
	}
	file.close();
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
		ano = valorInvalido_inserirAluno(L"Dia: ");
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
		dia = valorInvalido_inserirAluno(L"Ano: ");
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

	wstring Pass = PassPrompt();

	utilizador aluno;

	wchar_t conf;

	//insere os dados no ecrã excepto a password para confirmação
	wcout << "Confirmação de Dados" << endl;
	wcout << "Número Mecanográfico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", Código postal: " << mora.codPost << endl << endl;
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
				}
			}
		}
	}

	aluno.morada = mora;
	aluno.nasc = date;
	aluno.nome = nome;
	aluno.numero = num;
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
	Permite carregar plafond
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
	wstring aux, nomeP;
	int i = 0;
	int j = 0;
	int r = 0;
	wcout << "Qual é o nome que quer procurar (primeiro nome)? ";
	getline(wcin, nomeP);

	while (i < TAMANHO)
	{
		
		if (array_util[i].numero != INT_MIN)
		{
			j = 0;
			wstring primeiroNome;
			aux = array_util[i].nome;
			while (j < 50 && aux[j] != 32)
			{
				primeiroNome[j] = aux[j];
				j++;
			}
			if (nomeP.compare(primeiroNome) == 0)
			{
				wcout << "Número: " << array_util[i].numero << endl << "Nome: " << array_util[i].nome << endl << endl;
				r++;
			}
		}
		i++;
	}
	wcout << "Número de resultados encontrados: " << r;
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

	wcout << numPlafonds << endl << numUtils;
	cin.sync();
	cin.get();

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
				<< "6. Remover alunos\n"						//O mesmo que acima	
				<< "7. Remover Refeicão\n"						//O mesmo que acima	
				<< "8. Listar refeições\n"						//O mesmo que acima	
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
				clrConsole();
				//criarRefeição();
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
			else if (resposta_int == 6/*7*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover alunos.\n";
				Sleep(1000);
				removerAluno();
				clrConsole();
			}

			else if (resposta_int == 7/*8*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu remover refeição.\n";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 8/*9*/ && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
				clrConsole();
				wcout << "Escolheu listar refeições.\n";
				Sleep(1000);
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

