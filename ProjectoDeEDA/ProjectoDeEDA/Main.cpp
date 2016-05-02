#include "Functions.h"

/*
	Main Function \(^.^ )/
*/
int main()
{
	SetConsoleCP(1252);									//Define a consola de modo a ler carateres especiais
	SetConsoleOutputCP(1252);							//Define a consola de modo a escrever carateres especiais
	
	while (true)										//A maquina so irá parar de executar o programa se este for forçado a terminar
	{
		printMainMenu();								//Função que apresenta o menu principal, onde podemos escolher as opções desejadadas.
	}

	return 0;
}