#pragma once

#include "Functions.h"

/*
ATENÇÂO:	Neste ficheiro encontram-se todas as funções que necessitem de variáveis globais!!!
*/

bool logged = false;							// O utilizador esta logged in ou não
bool admin = false;								// O utilizador é funcionário ou não
int const TAMANHO = 500;						// Tamanho dos arrays
int Util_logged;								// Numero mecanografico do ultimo/atual utilizador logged in
wchar_t dadU[50] = L"BaseDados.txt";			// Nome do ficheiro contendo a informação dos utilizadores 
wchar_t dadR[50] = L"Refeicoes.txt";			// Nome do ficheiro contendo a informação dos refeicoes
int numUtils = 0;								// Numero total de utilizadores
int numPlafonds = 0;							// Numero total de utilizadores com plafond
int numRefeicoes = 0;							// Numero total de refeicoes
filaUtilizadores filUtil;
filaRefeicao filRef;


/*
Le a informação relativa às refeições e coloca-a no array respectivo
*/
void leDadosRefeicoes()
{
	wfstream file;
	file.open(dadR, ios::in);
	filaRefeicao::REF * atual = filRef.atual;
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

	refeicao ref;

	while (true)
	{
		getline(file, temp);

		aux = convert_Str_2_INT(temp);

		if (aux != INT_MIN && aux != 0)
		{
			ref.numero = aux;

			getline(file, temp);

			if (convert_Str_2_INT(temp) == 1)
			{
				ref.jantar = true;
			}
			else
			{
				ref.jantar = false;
			}

			getline(file, temp);
			ref.data.ano = convert_Str_2_INT(temp);

			getline(file, temp);
			ref.data.mes = convert_Str_2_INT(temp);

			getline(file, temp);
			ref.data.dia = convert_Str_2_INT(temp);

			getline(file, temp);

			//Se for uma data anterior à atual descarta-a 
			if (dateValid(ref.data.ano, ref.data.mes, ref.data.dia))
			{
				numRefeicoes++;
				insereNaFila(filRef, ref);
			}
		}
		else
		{
			break;
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

	int refeicoes_guardadas = 0;

	filaRefeicao::REF * atual = filRef.atual;

	while (atual != NULL && refeicoes_guardadas != numRefeicoes)
	{
		
		file << atual->refeicao.numero << endl;
		if (atual->refeicao.jantar)
		{
			file << 1 << endl;
		}
		else
		{
			file << 0 << endl;
		}
		file << atual->refeicao.data.ano << endl;
		file << atual->refeicao.data.mes << endl;
		file << atual->refeicao.data.dia << endl;
		file << "-" << endl;

		refeicoes_guardadas++;
		atual = atual->anterior;
	}
	file.close();
}

/*
Lê ficheiro de dados de utilizador e carrega os dados num array
*/
void leDadosUtilizadores()
{
	wstring temp;

	utilizador util;

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

	while (true)
	{
		getline(file, temp);

		aux = convert_Str_2_INT(temp);									// Guarda o valor numerico da string temp em aux

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que não há utilizadores por criar pois o que foi lido já não é um valor válido
		{
			util.numero = aux;

			getline(file, temp);
			util.nome = temp;

			getline(file, temp);
			util.money = convert_Str_2_INT(temp);

			getline(file, temp);
			util.nasc.dia = convert_Str_2_INT(temp);

			getline(file, temp);
			util.nasc.mes = convert_Str_2_INT(temp);

			getline(file, temp);
			util.nasc.ano = convert_Str_2_INT(temp);

			getline(file, temp);
			util.morada.rua = temp;

			getline(file, temp);
			util.morada.numPorta = temp;

			getline(file, temp);
			util.morada.codPost = temp;

			getline(file, temp);
			util.curso = temp;

			getline(file, temp);
			util.pass = temp;

			numUtils++;

			insereNaFila(filUtil, util);
		}
		else
		{
			break;
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

	filaUtilizadores::UTIL * atual = filUtil.atual;

	while (atual != NULL)
	{
		file << atual->util.numero << endl;
		file << atual->util.nome << endl;
		file << atual->util.money << endl;
		file << atual->util.nasc.dia << endl;
		file << atual->util.nasc.mes << endl;
		file << atual->util.nasc.ano << endl;
		file << atual->util.morada.rua << endl;
		file << atual->util.morada.numPorta << endl;
		file << atual->util.morada.codPost << endl;
		file << atual->util.curso << endl;
		file << atual->util.pass << endl;

		atual = atual->anterior;
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
	aluno.money = 0;

	insereNaFila(filUtil, aluno);
	escreveDadosUtilizadores();		//Atualiza a informação da base de dados para conter este novo aluno

	return 0;
}

/*
Coloca os utilizadores no array por ordem alfabética para facilitar a colocação dos utilizadores no ecrã por ordem alfabética
*/
void organizearray_bynames()
{
	filUtil = ordenaPorNome(filUtil);
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

	int num;
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

			filaUtilizadores::UTIL * atual = filUtil.atual;

			while (atual != NULL)								//Procura, na lista, por um utilizador com a informação que foi passada pelo utilizador do programa
			{
				if (num == atual->util.numero && atual->util.pass.compare(pass) == 0)
				{
					clrConsole();
					wcout << "Bem vindo " << atual->util.nome << "!" << endl;
					Sleep(3000);
					Util_logged = num;
					return true;							//Indica que ocorreu login
				}
				atual = atual->anterior;
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
	
	filaUtilizadores::UTIL * atual = filUtil.atual;

	if (vazio(filUtil))
	{
		wcout << "A lista de utilizadores encontra-se vazia!!!" << endl;
		cin.sync();
		cin.get();
		return;
	}

	while (atual != NULL)
	{
		wcout << "Nome: " << atual->util.nome << ". Número: " << atual->util.numero << endl;
		atual = atual->anterior;
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
	int aux;
	wstring temp;

	filaUtilizadores::UTIL * atual = filUtil.atual;

	while (atual != NULL)
	{
		if (Util_logged == atual->util.numero)
		{
			break;
		}
		else
		{
			atual = atual->anterior;
		}
	}

	wcout << "Neste momento voçê possui " << atual->util.money << "€." << endl;

	bool repeat = true;
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

	atual->util.money += aux;

	escreveDadosUtilizadores();
	wcout << "Após o caregamento ficou com: " << atual->util.money << "€." << endl;
	Sleep(500);
	
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
	filaUtilizadores::UTIL * atual = filUtil.atual;
	while (atual != NULL)
	{
		if (numAluno == atual->util.numero)
		{
			break;
		}
		else
		{
			atual = atual->anterior;
		}
	}
	if (atual != NULL)						// Se encontrar um aluno com este numero...
	{
		wcout << "Número: " << atual->util.numero << endl << "Nome: " << atual->util.nome << endl << "Data de Nascimento: " <<
			atual->util.nasc.ano << "-" << atual->util.nasc.mes << "-" << atual->util.nasc.dia << endl << "Morada: " <<
			atual->util.morada.rua << ", nº " << atual->util.morada.numPorta << endl << "Código Postal: " << atual->util.morada.codPost <<
			endl << "Curso: " << atual->util.curso << endl << endl;
		wcout << "Tem a certeza que quer eliminar o aluno nº " << numAluno << "?(S/N)";
		wcin >> val;
		cin.sync();
		cin.get();
		if (val == L's' || val == L'S')
		{
			retiraDaFila(filUtil, atual->util.numero);
			numUtils--;
			escreveDadosUtilizadores();
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
	filaUtilizadores::UTIL * atual = filUtil.atual;
	while (atual != NULL)												// Enquanto o tamanho do array for menor...
	{
		if (atual->util.numero != INT_MIN)						// Verifica se o número é válido
		{
			aux = atual->util.nome;								// Coloca em aux o nome do utilizador
			wstring::size_type pos = aux.find(' ');					// Guarda em pos a posição do primeiro ' '(espaço)
			if (pos != string::npos)								// Se a posição do espaço for diferente da última posição da string...
			{
				temp = aux.substr(0, pos);							// Guarda em temp o primeiro nome do aluno, que vai da posição 0 até à posição do espaço, guardado em pos
				if (temp.compare(nomeP) == 0)						// Se o nome guardado em temp for igual ao nome inserido...
				{
					wcout << endl << "Número: " << atual->util.numero << "  Nome: " << atual->util.nome << endl << endl;
					r++;											// Incrementa a varíavel que dá a quantidade de registos encontrados
				}
			}
		}
		atual = atual->anterior;														// Passa para o aluno seguinte
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
	int num;
	int r = 0;														// Inicializa i a zero
	wcout << "Deseja listar as refeições de que aluno? (Número Mecanográfico ou 0 para todos os alunos) ";
	getline(wcin, aux);												// Guarda em aux o valor inserido
	num = convert_Str_2_INT(aux);									// Converte a string em int

	if (num != INT_MIN)												// Se a int inserida for válida, isto é, se for realmente um valor númérico...
	{
		filaRefeicao::REF * atual = filRef.atual;
		if (num == 0)												// Se o valor for zero...
		{
			while (atual != NULL)										// Enquanto i for menor que o tamanho do array...
			{
				if (atual->refeicao.numero != INT_MIN)			// Se existe uma refeição válida para aquele aluno...
				{
					if (atual->refeicao.jantar)					// Se a refeição é jantar...
					{
						wcout << endl << "Número: " << atual->refeicao.numero << "  Refeição: Jantar  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					else
					{
						wcout << endl << "Número: " << atual->refeicao.numero << "  Refeição: Almoço  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					r++;											// Incrementa o número de refeições encontradas
				}
				atual = atual->anterior;												// Incrementa a posição do array
			}
		}
		else														// Se foi inserido um número mecanográfico...
		{
			while (atual != NULL)										// Enquanto i for menor que o tamanho do array...
			{
				if (num == atual->refeicao.numero)				// Se existe uma refeição encomendada pelo aluno cujo número foi inserido...
				{
					if (atual->refeicao.jantar)					// Se for jantar...
					{
						wcout << endl << "Número: " << atual->refeicao.numero << "  Refeição: Jantar  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					else
					{
						wcout << endl << "Número: " << atual->refeicao.numero << "  Refeição: Almoço  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					r++;											// Incrementa a quantidade de refeições encontradas para o aluno
				}
				atual = atual->anterior;												// Incrementa a posição do array
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
	filaUtilizadores::UTIL * atual_util = filUtil.atual;
	while (atual_util != NULL)
	{
		if (atual_util->util.numero == Util_logged)
		{
			if (atual_util->util.money < 3)
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
			atual_util = atual_util->anterior;
		}
	}
	if (atual_util->util.money < 3)
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
				if (atual_util->util.money < (num * 3))
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
			//Pede a data começando pelo ano
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

			//Pede o mes
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

			//Pede o dia
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
				
				insereNaFila(filRef, food);

				j++;
			}
		}
	}
}

/*
Consumir Refeição
*/
void consumirRefeição()
{
	filaRefeicao::REF * atual = filRef.atual;
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
			while (atual != NULL)
			{
				if (atual->refeicao.numero == num && atual->refeicao.jantar == false)
				{
					if (dataVerifica(atual->refeicao.data.ano, atual->refeicao.data.mes, atual->refeicao.data.dia))
					{
						retiraDaFila(filRef, atual->refeicao);
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
				atual = atual->anterior;
			}
		}
		else if (op == 2)
		{
			while (atual != NULL)
			{
				if (atual->refeicao.numero == num && atual->refeicao.jantar == true)
				{
					if (dataVerifica(atual->refeicao.data.ano, atual->refeicao.data.mes, atual->refeicao.data.dia))
					{
						retiraDaFila(filRef, atual->refeicao);
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
				atual = atual->anterior;
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

void listarAlunoNumero()
{
	wstring temp;

	pededenovo:
	wcout << "Insira o número a procurar (insira 0 para sair): ";
	getline(wcin, temp);

	int num = convert_Str_2_INT(temp);
	if (num != INT_MIN)
	{
		if (num == 0)
		{
			return;
		}
		filaUtilizadores::UTIL * atual = new filaUtilizadores::UTIL();
		atual = filUtil.atual;
		while (atual != NULL)
		{
			if (atual->util.numero == num)
			{
				break;
			}
			else
			{
				atual = atual->anterior;
			}
		}
		if (atual != NULL)
		{
			wcout << "Número: " << atual->util.numero << endl <<
				"Nome: " << atual->util.nome << endl <<
				"Data de Nascimento: " << atual->util.nasc.dia << "/" << atual->util.nasc.mes << "/" << atual->util.nasc.ano << endl <<
				"Morada: " << atual->util.morada.rua << ", " << atual->util.morada.numPorta << endl <<
				"Código Postal: " << atual->util.morada.codPost << endl <<
				"Curso: " << atual->util.curso << endl << endl <<
				"Pressione ENTER para prosseguir.";
			cin.sync();
			cin.get();
			return;

		}
		else
		{
			wcout << "Não há nenhum utilizador com esse número!!" << endl << endl << "Pressione ENTER para prosseguir.";
			cin.sync();
			cin.get();
			return;
		}
	}
	else
	{
		wcout << "Inseriu um número inválido." << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		clrConsole();
		goto pededenovo;
	}
}

/*
Coloca o menu principal no ecrã e realiza funções consoante a opção escolhida pelo utilizador.
*/
void printMainMenu()
{
	novo(filUtil);
	novo(filRef);

	wstring resposta;
	int resposta_int;
	bool quit = false;

	leDadosUtilizadores();
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
			else if (resposta_int == 4 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
			{
			clrConsole();
			wcout << "Escolheu pesquisar pelo número\n";
			listarAlunoNumero();
			Sleep(1000);
			clrConsole();
			}
			else if (resposta_int == 5 && logged && admin)	// Se tiver um admin logado isto é uma opção válida para o administrador
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