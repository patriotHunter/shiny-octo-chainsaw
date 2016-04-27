#pragma once

#include "Struct.h"

bool logged = false;
bool admin = false;
int respostaMainMenu;
int const TAMANHO = 500;
int Util_logged;
utilizador array_util[TAMANHO];
wchar_t filename[50] = L"BaseDados.txt";

/*
	Fun��o para fazer clear � consola.
*/
void clrConsole()
{
	system("cls");
}

/*
	Fun��o que ir� converter, se poss�vel um char num inteiro.
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
		wchar_t c = input[i];

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

	if (possible)												//Se a string passada � um n�mero...
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
	L� ficheiro de dados de utilizador e carrega os dados num array
*/
void leDadosUtilizadores()
{
	wstring temp;

	int aux;

	wfstream file;

	file.open(filename, ios::in);
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

		if (aux != INT_MIN)												// Se aux == INT_MIN significa que n�o h� utilizadores por criar pois o que foi lido j� n�o � um valor v�lido
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

	file.open(filename, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que � para come�ar o ficheiro como se fosse um novo ficheiro, apagando o conte�do presente anteriormente

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

	while (i < TAMANHO)
	{
		if (array_util[i].numero != INT_MIN)			// Se for um utilizador v�lido guarda caso contr�rio passa ao pr�ximo utilizador
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
		}
		i++;
	}
	file.close();
}

/*
	Indica que o valor inserido n�o � v�lido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x)
{
	bool repeat = true;
	wchar_t answer;
	int num;
	wstring temp;

	while (repeat)
	{
		wcout << "O valor inserido n�o � v�lido, quer continuar a inser��o de aluno? (S/N)" << endl;
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
	Cria um aluno e insere-o na lista de alunos
*/
int inserirAluno()
{
	wstring nome, temp, rua, codPost, numPorta;
	int num, dia, mes, ano;


	wcout << "Por favor insira os dados do aluno." << endl << endl << "Nome Completo: ";
	getline(wcin, nome);
	clrConsole();

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

	wcout << "Morada" << endl << "Rua: ";
	getline(wcin, rua);
	clrConsole();

	wcout << "N� da porta: ";
	getline(wcin, numPorta);
	clrConsole();

	wcout << "C�digo Postal: ";
	getline(wcin, codPost);
	clrConsole();

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	wstring Pass = PassPrompt();

	utilizador aluno;

	wchar_t conf;

	wcout << "Confirma��o de Dados" << endl;
	wcout << "N�mero Mecanogr�fico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", C�digo postal: " << mora.codPost << endl << endl;
	wcout << "Os dados est�o correctos?(S/N) ";
	wcin >> conf;
	cin.sync();
	cin.get();										//Retira um ghost "ENTER"
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
					case 0:
						wcout << endl << "Deseja mesmo sair da edi��o de aluno? (S/N) ";
						char answer;
						cin >> answer;
						if (answer == 'n' || answer == 'N')
						{
							repeat = false;
						}
						break;
					case 1:
						wcout << endl << "Reinsira o n�mero mecanogr�fico: ";
						getline(wcin, temp);
						num = convert_Str_2_INT(temp);

						if (num == INT_MIN)
						{
							num = valorInvalido_inserirAluno(L"N�mero Mecanogr�fico: ");
						}
						break;
					case 2:
						wcout << endl << "Reinsira o nome: ";
						getline(wcin, nome);
						break;
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

	while (i < TAMANHO)
	{
		if (array_util[i].numero == INT_MIN)
		{
			array_util[i] = aluno;
			break;
		}
		i++;
	}

	escreveDadosUtilizadores();

	return 0;
}

/*
	Cria a refeicao
*/
void criarRefei��o() // TODO: fazer um ficheiro txt para inspecionar as ementas de um determinado dia escolhido
{
	bool repete = true;					// mecanismo de repeticao, caso cometa algum erro
	bool entrada, carne, peixe, veggie; // escolhas do tipo de prato
	bool almoco, jantar;				// escolha de turno
	char resposta;						// respostas por parte das escolhas dos almocos /jantares
	wstring temp;						// reposta para converter a string em numero
	int dia, mes, ano, num;					// indicar o dia para fa�a o pedido
	bool verifica = true;
	char sair;



	while (verifica)
	{
		wcout << "Por favor insira o n�mero do aluno: "; // aqui suposto a por o nome do aluno completo, ou talvez o primeiro nome
		getline(wcin, temp);
		num = convert_Str_2_INT(temp);
		if (num == INT_MIN)
		{
			// insert number search function here
			wcout << endl << "Escolha o dia: ";						 // neste momento podemos escolher o pr�prio dia
			getline(wcin, temp);
			dia = convert_Str_2_INT(temp);
			clrConsole();

			if (dia == INT_MIN)
			{
				valorInvalido_inserirAluno(L"Escolha o dia: "); // mudar ou criar uma nova fun�ao pois esta fun��o faz parte da insercao do aluno
			}

			wcout << "Escolha o m�s(n�mero): ";
			getline(wcin, temp);
			mes = convert_Str_2_INT(temp);
			clrConsole();

			if (mes == INT_MIN)
			{
				valorInvalido_inserirAluno(L"Escolha o m�s: "); // mudar ou criar uma nova fun�ao pois esta fun��o faz parte da insercao do aluno
			}

			wcout << "Escolha o ano: ";
			getline(wcin, temp);
			ano = convert_Str_2_INT(temp);
			clrConsole();

			if (ano == INT_MIN)
			{
				valorInvalido_inserirAluno(L"Escolha o ano: "); // mudar ou criar uma nova fun�ao pois esta fun��o faz parte da insercao do aluno
			}

			wcout << "Confirmado o dia aluno(a) X\n"			//temos que actualizar o nome
				<< " A(s) refei��o(�es) ser� feita nesta data: "
				<< dia << " /" << mes << " /" << ano << endl;
			Sleep(3000);
			clrConsole();

			dataNasc reservaDia;

			reservaDia.dia = dia;
			reservaDia.mes = mes;
			reservaDia.ano = ano;


			while (repete)
			{
				wcout << "Deseja um almo�o (Insira s/S ou n/N): ";
				cin >> resposta;
				if (resposta == 's' || resposta == 'S')
				{
					almoco = true;
					repete = false;
					wcout << "Ent�o deseja o almo�o\n";
					Sleep(3000);
					clrConsole();
					goto Pratos;

					// temos que abrir algum ficheiro para mostrar a informa��o dos pratos seguintes no que dia que for escolhido
					// caso n�o exista ficheiro para verificar o dia, aparecer� um aviso para o programador para reparar esta zona
					// 1. Prato de Entrada X 
					// 2. Prato de Carne X
					// 3. Prato de Peixe X
					// 4. Prato Vegie X

				}


				else if (resposta == 'n' || resposta == 'N')
				{
					almoco = false;
					repete = false;

					wcout << "Compreendido" << endl;
					Sleep(3000);
					clrConsole();
				}

				else
				{
					clrConsole();
					wcout << "Por insira uma das respostas\n";
					repete;
				}
			}

			repete = true; // for�a a true para decidir o jantar

			while (repete)
			{
				wcout << "Deseja um jantar (Insira s/S ou n/N)";
				cin >> resposta;
				if (resposta == 's' || resposta == 'S')
				{
					jantar = true;
					repete = false;

					wcout << "Ent�o deseja o jantar\n";
					Sleep(3000);
					clrConsole();

					goto Pratos;

					// temos que abrir algum ficheiro para mostrar a informa��o dos pratos seguintes no que dia que for escolhido
					// caso n�o exista ficheiro para verificar o dia, aparecer� um aviso para o programador para reparar esta zona
					// 1. Prato de Carne X
					// 2. Prato de Peixe X
					// 3. Prato Vegie X

				}

				else if (resposta == 'n' || resposta == 'N')
				{
					jantar = false;
					repete = false;
					goto Cancelar;
				}

				else
				{
					clrConsole();
					cout << "Por insira uma das respostas\n";
					repete;
				}
			}

		Cancelar:

			clrConsole();
			wcout << "Pedido cancelado\n";
			Sleep(1000);
			carne = false;
			peixe = false;
			entrada = false;
			veggie = false;

			goto Voltar;



		Pratos:
			int opcao;						// arranja-se logo uma int para fazer a escolha
			bool pratos = true;				// variavel pratos para fazer a escolha dos pratos principais

			do {
				wcout << "Tens 3 pratos para escolher\n"
					<< "1. Prato de Carne X\n"
					<< "2. Prato de Peixe X\n"
					<< "3. Prato de Veggie X\n"
					<< "Escolha uma op��o: ";

				cin >> opcao;
				switch (opcao)
				{
				case 1:
					pratos = false;
					carne = true;
					peixe = false;
					veggie = false;
					break;

				case 2:
					pratos = false;
					peixe = true;
					carne = false;
					veggie = false;
					break;

				case 3:
					pratos = false;
					carne = false;
					peixe = false;
					veggie = true;
					break;

				default:
					wcout << "\nOp��o errada";
					Sleep(1000);
					clrConsole();
					pratos;
				}
			} while (pratos);

			bool extra = true;				// variavel extra para fazer a escolha do prato de entrada
			while (extra)
			{
				wcout << "Deseja o prato de entrada?\n"
					<< "Indica s/S ou n/N: ";
				cin >> resposta;

				if (resposta == 's' || resposta == 'S')
				{
					extra = false;
					entrada = true;
				}
				else if (resposta == 'n' || resposta == 'N')
				{
					extra = false;
					entrada = false;
				}
				else {
					clrConsole();
					wcout << "Por favor insira a resposta correcta\n";
					Sleep(1000);
					clrConsole();
				}
			}

			wcout << "Pedido feito\n";
			Sleep(3000);
			clrConsole();

		Voltar:
			wcout << "Voltando ao Menu...\n";
			Sleep(1000);
			clrConsole();

			refeicao refeicao;

			refeicao.data = reservaDia;
			refeicao.entrada = entrada;
			refeicao.carne = carne;
			refeicao.peixe = peixe;
			refeicao.vegie = veggie;
		}
		else
		{
			wcout << "O n�mero inserido n�o � v�lido." << endl;
			wcout << "Deseja tentar novamente? (S/N) ";
			cin >> sair;
			if (sair == 'n' || sair == 'N')
			{
				verifica = false;
			}
		}
	}

}

/*
	Coloca os utilizadores no array por ordem alfab�tica
*/
void organizearray_bynames()
{
	int i = 0;
	int j;
	wstring aux_str, aux_string;
	while (i < TAMANHO)
	{
		aux_str = array_util[i].nome;
		j = i + 1;
		while (j < TAMANHO)
		{
			aux_string = array_util[j].nome;
			if (aux_string.compare(aux_str) < 0)
			{
				swap(array_util[j], array_util[i]);
				j = TAMANHO;
			}
			j++;
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
				wcout << "Benvindo administrador!" << endl;
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
					wcout << "Benvindo " << array_util[i].nome << "!" << endl;
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
			wcout << "Pretende tentar novamente? (S/N): ";
			wcin >> answer;
			if (answer == 'n' || answer == 'N')
			{
				return false;								//Indica que n�o ocorreu um login correcto
			}
			cin.sync();
			cin.get();										//Retira um ghost "ENTER"
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
	int i = 0;
	while (i < TAMANHO)
	{
		if (array_util[i].numero != INT_MIN)
		{
			wcout << "Nome: " << array_util[i].nome << " NUM: " << array_util[i].numero << endl;
		}
		i++;
	}
	cin.sync();
	cin.get();
}

/*
	Coloca o menu principal no ecr� e devolve valores consoante a op��o escolhida pelo utilizador.
*/
void printMainMenu()
{
	wstring resposta;
	int resposta_int;
	bool quit = false;

	leDadosUtilizadores();

	while (!quit)
	{
		clrConsole();
		//	Imprime texto no ecr�.
		wcout << "Bem vindo ao primeiro projecto de EDA." << endl;
		wcout << "\nEscolha a op��o pretendida.\n" << endl;
		if (!logged)
		{
			wcout << "1. Login.\n\nOpc�o: ";
		}
		else
		{
			wcout << "1. Logout." << endl;
		}

		if (admin && logged) // se o utilizador que estiver logged in for um admin
		{
			wcout << "2. Inserir alunos\n"
				<< "3. Pesquisar pelo Primeiro Nome\n"
				<< "4. Pesquisar pelo N�mero\n"
				<< "5. Lista alunos por Ordem Alfabetica\n"
				<< "6. Alterar alunos\n"
				<< "7. Remover alunos\n"
				<< "8. Remover Refeic�o\n"
				<< "9. Listar refei��es\n"
				<< "10. Listar refei��es num determinado dia\n"
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

			if (resposta_int == 1) // est� dependente de tudo
			{
				logged = login_logout();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu inserir aluno\n";
				Sleep(1000);
				clrConsole();
				inserirAluno();
			}
			else if (resposta_int == 2 && logged && !admin)
			{
				clrConsole();
				wcout << "Escolheu encomendar refei��o\n";
				Sleep(1000);
				clrConsole();
				criarRefei��o();

			}
			else if (resposta_int == 3 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu pesquisar pelo primeiro nome\n";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 3 && logged && !admin)
			{
				clrConsole();
				wcout << "Escolheu carregar plafond";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 4 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu pesquisar pelo n�mero\n";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 5 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu listar alunos por ordem alfab�tica\n";
				Sleep(1000);
				printUsers();
				clrConsole();
			}
			else if (resposta_int == 6 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu alterar alunos\n";
				Sleep(1000);
				clrConsole();
			}

			else if (resposta_int == 7 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu remover alunos\n";
				Sleep(1000);
				clrConsole();
			}

			else if (resposta_int == 8 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu remover refei��o\n";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 9 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu listar refei��es\n";
				Sleep(1000);
				clrConsole();
			}
			else if (resposta_int == 10 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu listar refei��es num determinado dia\n";
				Sleep(1000);
				clrConsole();
			}
			else
			{
				clrConsole();
				wcout << "Escolheu a op��o errada\nPor favor escolha a(s) op��o/op��es dispon�veis\n";
				Sleep(1000);
				clrConsole();
			}


		}
	}
}

