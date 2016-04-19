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
		respostaMainMenu = printMainMenu(logged);
	}

	array_util[0].nome = L"Marcelo José";
	array_util[0].pass = L"kek";
	array_util[0].numero = 123;

	login_logout();

	//inserirAluno();

	return 0;
}