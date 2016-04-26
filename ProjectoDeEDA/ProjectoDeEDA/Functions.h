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
*	Função para fazer clear à consola.
*/
void clrConsole()
{
	system("cls");
}

/*
*	Função que irá converter, se possível um char num inteiro.
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
Lê ficheiro de dados de utilizador e carrega os dados num array
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

		if (aux != INT_MIN)												// Se aux == INT_MIN significa que não há utilizadores por criar pois o que foi lido já não é um valor válido
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

	file.open(filename, ios::out | ios::trunc);		// abre o ficheiro para escrever e com o comando ios::trunc indica que é para começar o ficheiro como se fosse um novo ficheiro, apagando o conteúdo presente anteriormente

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

	while (i < TAMANHO)
	{
		if (array_util[i].numero != INT_MIN)			// Se for um utilizador válido guarda caso contrário passa ao próximo utilizador
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
*	Indica que o valor inserido não é válido e pede um novo valor se o utilizador desejar continuar.
*/
int valorInvalido_inserirAluno(wstring x)
{
	bool repeat = true;
	char answer;
	int num;
	wstring temp;

	while (repeat)
	{
		wcout << "O valor inserido não é válido, quer continuar a inserção de aluno? (S/N)" << endl;
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
			wcout << "As passwords não coincidem!" << endl << endl;
		}
	}
	clrConsole();

	return Pass;
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

	wcout << endl << endl << "Número Mecanográfico: " << endl << endl;
	getline(wcin, temp);
	num = convert_Str_2_INT(temp);
	clrConsole();

	if (num == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Número Mecanográfico: ");
	}

	wcout << endl << endl << "Data de nascimento" << endl << "Dia: ";
	getline(wcin, temp);
	dia = convert_Str_2_INT(temp);
	clrConsole();

	if (dia == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Dia: ");
	}

	wcout << endl << "Mês(número): ";
	getline(wcin, temp);
	mes = convert_Str_2_INT(temp);
	clrConsole();

	if (mes == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Mês(número): ");
	}

	wcout << endl << "Ano: ";
	getline(wcin, temp);
	ano = convert_Str_2_INT(temp);
	clrConsole();

	if (ano == INT_MIN)
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

	wcout << endl << "Nº da porta: " << endl << endl;
	getline(wcin, numPorta);
	clrConsole();

	wcout << endl << "Código Postal: " << endl << endl;
	getline(wcin, codPost);
	clrConsole();

	morada mora;

	mora.codPost = codPost;
	mora.rua = rua;
	mora.numPorta = numPorta;

	wstring Pass = PassPrompt();

	utilizador aluno;

	char conf;

	wcout << "Confirmação de Dados" << endl;
	wcout << "Número Mecanográfico: " << num << endl;
	wcout << "Nome Completo: " << nome << endl;
	wcout << "Data de Nascimento: " << date.dia << "/" << date.mes << "/" << date.ano << endl;
	wcout << "Morada: " << mora.rua << ", " << mora.numPorta << ", Código postal: " << mora.codPost << endl << endl;
	wcout << "Os dados estão correctos?(S/N) ";
	cin >> conf;
	if (conf == 'N' || conf == 'n')
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
			wcout << "0) Cancelar" << endl;
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
				switch (answer)
				{
					case 0:
						wcout << endl << "Deseja mesmo sair da edição de aluno? (S/N) ";
						wchar_t answer;
						wcin >> answer;
						if (answer == 'n' || answer == L'N')
						{
							repeat = false;
						}
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
*	Cria a refeicao
*/
void criarRefeição() // TODO: fazer um ficheiro txt para inspecionar as ementas de um determinado dia escolhido
{
	bool repete = true;					// mecanismo de repeticao, caso cometa algum erro
	bool entrada, carne, peixe, veggie; // escolhas do dia ou noite 
	bool almoco, jantar;				// escolha de turno
	char resposta;						// respostas por parte das escolhas dos almocos /jantares
	wstring temp;						// reposta para converter a string em numero
	int dia, mes, ano;					// indicar o dia para faça o pedido






	wcout << "Por favor insira os dados aluno X\n\n" // aqui suposto a por o nome do aluno completo, ou talvez o primeiro nome
		<< "Escolha o dia: ";						 // neste momento podemos escolher o próprio dia
	getline(wcin, temp);
	dia = convert_Str_2_INT(temp);
	clrConsole();

	if (dia == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Escolha o dia: "); // mudar ou criar uma nova funçao pois esta função faz parte da insercao do aluno
	}

	wcout << "Escolha o mês(número): ";
	getline(wcin, temp);
	mes = convert_Str_2_INT(temp);
	clrConsole();

	if (mes == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Escolha o mês: "); // mudar ou criar uma nova funçao pois esta função faz parte da insercao do aluno
	}

	wcout << "Escolha o ano: ";
	getline(wcin, temp);
	ano = convert_Str_2_INT(temp);
	clrConsole();

	if (ano == INT_MIN)
	{
		valorInvalido_inserirAluno(L"Escolha o ano: "); // mudar ou criar uma nova funçao pois esta função faz parte da insercao do aluno
	}

	wcout << "Confirmado o dia aluno(a) X\n"			//temos que actualizar o nome
		<< " A(s) refeição(ões) será feita nesta data: "
		<< dia << " /" << mes << " /" << ano << endl;
	Sleep(3000);
	clrConsole();

	dataNasc reservaDia;

	reservaDia.dia = dia;
	reservaDia.mes = mes;
	reservaDia.ano = ano;


	while (repete)
	{
		wcout << "Deseja um almoço (Insira s/S ou n/N): ";
		cin >> resposta;
		if (resposta == 's' || resposta == 'S')
		{
			almoco = true;
			repete = false;
			wcout << "Então deseja o almoço\n";
			Sleep(3000);
			clrConsole();
			goto Pratos;

			// temos que abrir algum ficheiro para mostrar a informação dos pratos seguintes no que dia que for escolhido
			// caso não exista ficheiro para verificar o dia, aparecerá um aviso para o programador para reparar esta zona
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

	repete = true; // força a true para decidir o jantar

	while (repete)
	{
		wcout << "Deseja um jantar (Insira s/S ou n/N)";
		cin >> resposta;
		if (resposta == 's' || resposta == 'S')
		{
			jantar = true;
			repete = false;

			wcout << "Então deseja o jantar\n";
			Sleep(3000);
			clrConsole();

			goto Pratos;

			// temos que abrir algum ficheiro para mostrar a informação dos pratos seguintes no que dia que for escolhido
			// caso não exista ficheiro para verificar o dia, aparecerá um aviso para o programador para reparar esta zona
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
			<< "Escolha uma opção: ";

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
			wcout << "\nOpção errada";
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

/*
	Realiza o login se a informação do utilizador constar na base de dados e o número e a pass estiverem correctos
*/
bool login_logout()
{
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
				wcout << "Benvindo administrador!" << endl;
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
				return false;								//Indica que não ocorreu um login correcto
			}
			cin.sync();
			cin.get();										//Retira um ghost "ENTER"
		}
	}
	return false;											//Indica que não ocorreu um login correcto
}


void printUsers()
{
	int i = 0;
	while (i < TAMANHO)
	{
		wcout << "PASS: " << array_util[i].pass << " NUM: " << array_util[i].numero << endl;
		i++;
	}
}

/*
*	Coloca o menu principal no ecrã e devolve valores consoante a opção escolhida pelo utilizador.
*/
void printMainMenu()
{
	wstring resposta;
	int resposta_int;
	bool quit = false;

	leDadosUtilizadores();

	clrConsole();

	while (!quit)
	{
		//	Imprime texto no ecrã.
		wcout << "\n\nBem vindo ao primeiro projecto de EDA." << endl;
		wcout << "\n\nEscolha a opção pretendida.\n" << endl;
		if (!logged)
		{
			wcout << "1. Login." << endl;
		}
		else
		{
			wcout << "1. Logout." << endl;
		}

		if (admin && logged) // se o utilizador que estiver logged in for um admin
		{
			wcout << "2. Inserir alunos\n"
				<< "3. Pesquisar pelo Primeiro Nome\n"
				<< "4. Pesquisar pelo Número\n"
				<< "5. Lista alunos por Ordem Alfabetica\n"
				<< "6. Alterar alunos\n"
				<< "7. Remover alunos\n"
				<< "8. Remover Refeicão\n"
				<< "9. Listar refeições\n"
				<< "10. Listar refeições num determinado dia\n"
				<< "Opção: ";
		}
		else if (!admin && logged) // se o utilizador n estiver logged in n no admin
		{
			wcout << "2. Encomendar refeição\n"
				<< "3. Carregar plafond\n"
				<< "Opção: ";
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

			if (resposta_int == 1) // está dependente de tudo
			{
				logged = login_logout();
				clrConsole();
			}
			else if (resposta_int == 2 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Inserir aluno\n";
				Sleep(3000);
				clrConsole();
				inserirAluno();
			}
			else if (resposta_int == 2 && logged && !admin)
			{
				clrConsole();
				wcout << "Escolheu Encomendar refeição\n";
				Sleep(3000);
				clrConsole();
				criarRefeição();

			}
			else if (resposta_int == 3 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Pesquisar pelo primeiro nome\n";
				Sleep(3000);
				clrConsole();
			}
			else if (resposta_int == 3 && logged && !admin)
			{
				clrConsole();
				wcout << "Escolheu Carregar plafond";
				Sleep(3000);
				clrConsole();
			}
			else if (resposta_int == 4 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Pesquisar pelo número\n";
				Sleep(3000);
				clrConsole();
			}
			else if (resposta_int == 5 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Listar alunos por Ordem Alfabética\n";
				Sleep(3000);
				printUsers();
				clrConsole();
			}
			else if (resposta_int == 6 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Alterar alunos\n";
				Sleep(3000);
				clrConsole();
			}

			else if (resposta_int == 7 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Remover alunos\n";
				Sleep(3000);
				clrConsole();
			}

			else if (resposta_int == 8 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Remover refeição\n";
				Sleep(3000);
				clrConsole();
			}
			else if (resposta_int == 9 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Listar refeições\n";
				Sleep(3000);
				clrConsole();
			}
			else if (resposta_int == 10 && logged && admin)
			{
				clrConsole();
				wcout << "Escolheu Listar refeições num determinado dia\n";
				Sleep(3000);
				clrConsole();
			}
			else
			{
				clrConsole();
				wcout << "Escolheu a opção errada\n"
					<< "Por favor escolha a(s) opção/opções disponíveis\n";
				Sleep(3000);
				clrConsole();
			}


		}
	}
}

