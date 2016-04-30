#include "Functions.h"

/*
**	Main Function \(^.^ )/
*/
int main()
{
	SetConsoleCP(1252);									//Define a consola de modo a ler carateres especiais
	SetConsoleOutputCP(1252);							//Define a consola de modo a escrever carateres especiais

	//_setmode(_fileno(stdout), _O_U16TEXT);
	
	while (true)
	{
		printMainMenu();
	}

	return 0;
}