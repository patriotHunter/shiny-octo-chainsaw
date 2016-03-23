#include "Functions.h"

bool logged = false;
int respostaMainMenu;

/*
**	Main Function \(^.^ )/
*/
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	while (true)
	{
		respostaMainMenu = printMainMenu(logged);

	}
}