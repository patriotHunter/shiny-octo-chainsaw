#include "Functions.h"
#include <fstream>
bool logged = false;
int respostaMainMenu;

/*
**	Main Function \(^.^ )/
*/
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	/*while (true)
	{
		respostaMainMenu = printMainMenu(logged);
	}
	*/
	ofstream myfile;
	myfile.open("Teste.txt");
	myfile << "It works, he is alive MUHAHAHAHAHAHA .\n";
	myfile.close();
	return 0;
}