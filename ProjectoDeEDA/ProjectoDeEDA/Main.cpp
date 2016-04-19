#include "Functions.h"
#include <Windows.h>

bool logged = false;
int respostaMainMenu;

/*
**	Main Function \(^.^ )/
*/
int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	//_setmode(_fileno(stdout), _O_U16TEXT);
	/*while (true)
	{
		respostaMainMenu = printMainMenu(logged);
	}*/

	inserirAluno();

	return 0;
	/*
	*	paofdnvaojvnaedvfojaeodv+ifndfvjandfvsafdvsgbsfhn
	*/
}