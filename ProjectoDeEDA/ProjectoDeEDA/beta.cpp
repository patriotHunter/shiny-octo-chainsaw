#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
/*
int main()
{
	
	// Método para localizar um tipo de nome neste caso tenta encontrar os modelos R2
	char str[][5] = { "R2D2" , "C3PO" , "R2A6" };
	int n;
	puts("Looking for R2 astromech droids...");
	for (n = 0; n<3; n++)
		if (strncmp(str[n], "R2xx", 2) == 0)
		{
			printf("found %s\n", str[n]);
		}
	return 0;	
	
}

*/

// basic file operations

/*
int main() {
	string line;
	ifstream myfile("example.txt");

	string nomeProcura;

	if (myfile.is_open())
	{
		
		cout << "Qual e o nome que queres que eu encontre:"; // indicar o nome do aluno
		cin >> nomeProcura; // inserir o nome
		

		
		size_t posicao;
		while (myfile.good())
		{
			getline(myfile, line);	// escreve uma string
			posicao = line.find(nomeProcura); // começa a procurar

			if (posicao != string::npos) // npos indica que não foi encontra
			{
				cout << "Foi encontrado"<< endl;
				while (getline(myfile, nomeProcura))
				{
					cout << nomeProcura;
				}
				break;
			}
			else
			{
				cout << "Nao foi encontrado" << endl;
			}
		}
	}
	
		//while(getline(myfile, line)) // enquanto escreve até ao fim
		//cout << line << endl; // mostra como output o que vier do texto

	else cout << "Unable to open file";

	return 0;
}

*/

//const int tamanho = 500;
//int main()
//{
//	fstream ficheiro;
//	char temp [tamanho];
//	wstring input;
//	string line (temp);
//
//	ficheiro.open("Refeicoes.txt", ios::in);
//
//	if (!ficheiro)
//	{
//		cout << "Erro detectado por favor tenta reparar" << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	char *alm = "Almoco";
//	char *jnt = "Jantar";
//
//
//	if (ficheiro.is_open())
//	{
//		while(getline(ficheiro, line))
//		{
//			cout << line << endl;
//		}
//	 ficheiro.close();
//	}
//}

//fstream& GotoLine(fstream& file, unsigned int num)
//{
//	file.seekg(ios::beg);
//	for (int i = 0; i < num - 1; ++i)
//	{
//		file.ignore(numeric_limits<streamsize>max(), '\n');
//	}
//	return file;
//}

int main()
{
	unsigned int dia, mes, ano;
	bool repete = true;


	while (repete)
	{
		cout << "Por favor insira o ano: ";
		cin >> ano;
		if ( ano >= 2016 && ano <= 2120 )
		{
				repete = false;
		}
		else 
		{
				cout << "Valor incorrecto\n";		// se for negativo o ano ou se ultrapassar entre os valores inseridos
				repete;
		}
	}

	repete = true; // forca para true

	while (repete)
	{
		cout << "Por favor insira o mes: ";
		cin >> mes;
		if (mes >= 1 && mes <= 12)
		{
			repete = false;
		}
		else // se for negativo ou se ultrapassar o limite então volta a repetir
		{
			cout << "Valor incorrecto\n"; 
			repete;
		}

	}

	repete = true; // forca para true
	while(repete)
	{
		if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0))
		{
			cout << "O ano e bissexto\n";
			cout << "Por favor insira o dia: ";
			cin >> dia;
			if (dia >= 1 && dia <= 29 && mes == 2)
			{
				repete = false;
			}
			else if (dia >= 1 && dia <= 31 && (mes == 1 || mes == 3 || mes == 5 || mes == 7|| mes == 8 ||  mes == 10 || mes == 12))
			{
				repete = false;
			}
			else if (dia >= 1 && dia <= 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
			{
				repete = false;
			}
			else // se nao for nenhum caso
			{
				repete;
				cout << "Valor incorrecto\n";
			}
		}
		else
		{
			cout << "O ano nao e bissexto\n";
			cout << "Por favor insira o dia: ";
			cin >> dia;
			if (dia >= 1 && dia <= 28 && mes == 2)
			{
				repete = false;
			}
			else if (dia >= 1 && dia <= 31 && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12))
			{
				repete = false;
			}
			else if (dia >= 1 && dia <= 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
			{
				repete = false;
			}
			else {	// se for negativo ou se ultrapassar o limite então volta a repetir
				repete;
				cout << "Valor incorrecto\n";
			}
		}
	}


	cout << "A refeicao sera na data: " << dia << " / " << mes << " / " << ano << endl;
	


}