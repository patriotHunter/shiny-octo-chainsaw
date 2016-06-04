#pragma once

#include "Functions.h"

/*
ATEN��O:	Neste ficheiro encontram-se todas as fun��es que necessitem de vari�veis globais!!!
*/

bool logged = false;							// O utilizador esta logged in ou n�o
bool admin = false;								// O utilizador � funcion�rio ou n�o
int const TAMANHO = 500;						// Tamanho dos arrays
int Util_logged;								// Numero mecanografico do ultimo/atual utilizador logged in
wchar_t dadU[50] = L"BaseDados.txt";			// Nome do ficheiro contendo a informa��o dos utilizadores 
wchar_t dadR[50] = L"Refeicoes.txt";			// Nome do ficheiro contendo a informa��o dos refeicoes
int numUtils = 0;								// Numero total de utilizadores
int numPlafonds = 0;							// Numero total de utilizadores com plafond
int numRefeicoes = 0;							// Numero total de refeicoes
filaUtilizadores filUtil;
filaRefeicao filRef;


/*
Le a informa��o relativa �s refei��es e coloca-a no array respectivo
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

			//Se for uma data anterior � atual descarta-a 
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
L� ficheiro de dados de utilizador e carrega os dados num array
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

		if (aux != INT_MIN && aux != 0)									// Se aux == INT_MIN ou == 0 significa que n�o h� utilizadores por criar pois o que foi lido j� n�o � um valor v�lido
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
	aluno.money = 0;

	insereNaFila(filUtil, aluno);
	escreveDadosUtilizadores();		//Atualiza a informa��o da base de dados para conter este novo aluno

	return 0;
}

/*
Coloca os utilizadores no array por ordem alfab�tica para facilitar a coloca��o dos utilizadores no ecr� por ordem alfab�tica
*/
void organizearray_bynames()
{
	filUtil = ordenaPorNome(filUtil);
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

	int num;
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

			filaUtilizadores::UTIL * atual = filUtil.atual;

			while (atual != NULL)								//Procura, na lista, por um utilizador com a informa��o que foi passada pelo utilizador do programa
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
		wcout << "Nome: " << atual->util.nome << ". N�mero: " << atual->util.numero << endl;
		atual = atual->anterior;
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

	wcout << "Neste momento vo�� possui " << atual->util.money << "�." << endl;

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

	atual->util.money += aux;

	escreveDadosUtilizadores();
	wcout << "Ap�s o caregamento ficou com: " << atual->util.money << "�." << endl;
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
		wcout << "N�mero: " << atual->util.numero << endl << "Nome: " << atual->util.nome << endl << "Data de Nascimento: " <<
			atual->util.nasc.ano << "-" << atual->util.nasc.mes << "-" << atual->util.nasc.dia << endl << "Morada: " <<
			atual->util.morada.rua << ", n� " << atual->util.morada.numPorta << endl << "C�digo Postal: " << atual->util.morada.codPost <<
			endl << "Curso: " << atual->util.curso << endl << endl;
		wcout << "Tem a certeza que quer eliminar o aluno n� " << numAluno << "?(S/N)";
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
	filaUtilizadores::UTIL * atual = filUtil.atual;
	while (atual != NULL)												// Enquanto o tamanho do array for menor...
	{
		if (atual->util.numero != INT_MIN)						// Verifica se o n�mero � v�lido
		{
			aux = atual->util.nome;								// Coloca em aux o nome do utilizador
			wstring::size_type pos = aux.find(' ');					// Guarda em pos a posi��o do primeiro ' '(espa�o)
			if (pos != string::npos)								// Se a posi��o do espa�o for diferente da �ltima posi��o da string...
			{
				temp = aux.substr(0, pos);							// Guarda em temp o primeiro nome do aluno, que vai da posi��o 0 at� � posi��o do espa�o, guardado em pos
				if (temp.compare(nomeP) == 0)						// Se o nome guardado em temp for igual ao nome inserido...
				{
					wcout << endl << "N�mero: " << atual->util.numero << "  Nome: " << atual->util.nome << endl << endl;
					r++;											// Incrementa a var�avel que d� a quantidade de registos encontrados
				}
			}
		}
		atual = atual->anterior;														// Passa para o aluno seguinte
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
	int num;
	int r = 0;														// Inicializa i a zero
	wcout << "Deseja listar as refei��es de que aluno? (N�mero Mecanogr�fico ou 0 para todos os alunos) ";
	getline(wcin, aux);												// Guarda em aux o valor inserido
	num = convert_Str_2_INT(aux);									// Converte a string em int

	if (num != INT_MIN)												// Se a int inserida for v�lida, isto �, se for realmente um valor n�m�rico...
	{
		filaRefeicao::REF * atual = filRef.atual;
		if (num == 0)												// Se o valor for zero...
		{
			while (atual != NULL)										// Enquanto i for menor que o tamanho do array...
			{
				if (atual->refeicao.numero != INT_MIN)			// Se existe uma refei��o v�lida para aquele aluno...
				{
					if (atual->refeicao.jantar)					// Se a refei��o � jantar...
					{
						wcout << endl << "N�mero: " << atual->refeicao.numero << "  Refei��o: Jantar  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					else
					{
						wcout << endl << "N�mero: " << atual->refeicao.numero << "  Refei��o: Almo�o  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					r++;											// Incrementa o n�mero de refei��es encontradas
				}
				atual = atual->anterior;												// Incrementa a posi��o do array
			}
		}
		else														// Se foi inserido um n�mero mecanogr�fico...
		{
			while (atual != NULL)										// Enquanto i for menor que o tamanho do array...
			{
				if (num == atual->refeicao.numero)				// Se existe uma refei��o encomendada pelo aluno cujo n�mero foi inserido...
				{
					if (atual->refeicao.jantar)					// Se for jantar...
					{
						wcout << endl << "N�mero: " << atual->refeicao.numero << "  Refei��o: Jantar  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					else
					{
						wcout << endl << "N�mero: " << atual->refeicao.numero << "  Refei��o: Almo�o  Data: "
							<< atual->refeicao.data.dia << "-" << atual->refeicao.data.mes << "-" << atual->refeicao.data.ano << endl;
					}
					r++;											// Incrementa a quantidade de refei��es encontradas para o aluno
				}
				atual = atual->anterior;												// Incrementa a posi��o do array
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
	filaUtilizadores::UTIL * atual_util = filUtil.atual;
	while (atual_util != NULL)
	{
		if (atual_util->util.numero == Util_logged)
		{
			if (atual_util->util.money < 3)
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
			atual_util = atual_util->anterior;
		}
	}
	if (atual_util->util.money < 3)
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
				if (atual_util->util.money < (num * 3))
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
			//Pede a data come�ando pelo ano
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

			//Pede o mes
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
				
				insereNaFila(filRef, food);

				j++;
			}
		}
	}
}

/*
Consumir Refei��o
*/
void consumirRefei��o()
{
	filaRefeicao::REF * atual = filRef.atual;
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
			while (atual != NULL)
			{
				if (atual->refeicao.numero == num && atual->refeicao.jantar == false)
				{
					if (dataVerifica(atual->refeicao.data.ano, atual->refeicao.data.mes, atual->refeicao.data.dia))
					{
						retiraDaFila(filRef, atual->refeicao);
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
				atual = atual->anterior;
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

void listarAlunoNumero()
{
	wstring temp;

	pededenovo:
	wcout << "Insira o n�mero a procurar (insira 0 para sair): ";
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
			wcout << "N�mero: " << atual->util.numero << endl <<
				"Nome: " << atual->util.nome << endl <<
				"Data de Nascimento: " << atual->util.nasc.dia << "/" << atual->util.nasc.mes << "/" << atual->util.nasc.ano << endl <<
				"Morada: " << atual->util.morada.rua << ", " << atual->util.morada.numPorta << endl <<
				"C�digo Postal: " << atual->util.morada.codPost << endl <<
				"Curso: " << atual->util.curso << endl << endl <<
				"Pressione ENTER para prosseguir.";
			cin.sync();
			cin.get();
			return;

		}
		else
		{
			wcout << "N�o h� nenhum utilizador com esse n�mero!!" << endl << endl << "Pressione ENTER para prosseguir.";
			cin.sync();
			cin.get();
			return;
		}
	}
	else
	{
		wcout << "Inseriu um n�mero inv�lido." << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		clrConsole();
		goto pededenovo;
	}
}

/*
Coloca o menu principal no ecr� e realiza fun��es consoante a op��o escolhida pelo utilizador.
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
			else if (resposta_int == 4 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
			{
			clrConsole();
			wcout << "Escolheu pesquisar pelo n�mero\n";
			listarAlunoNumero();
			Sleep(1000);
			clrConsole();
			}
			else if (resposta_int == 5 && logged && admin)	// Se tiver um admin logado isto � uma op��o v�lida para o administrador
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