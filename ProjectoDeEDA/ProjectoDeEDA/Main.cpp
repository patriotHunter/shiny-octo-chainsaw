#include "Functions.h"

/*
	Main Function \(^.^ )/
*/
int main()
{
	SetConsoleCP(1252);									//Define a consola de modo a ler carateres especiais
	SetConsoleOutputCP(1252);							//Define a consola de modo a escrever carateres especiais
	
	while (true)										//A maquina so ir� parar de executar o programa se este for for�ado a terminar
	{
		printMainMenu();								//Fun��o que apresenta o menu principal, onde podemos escolher as op��es desejadadas.
	}

	return 0;
}