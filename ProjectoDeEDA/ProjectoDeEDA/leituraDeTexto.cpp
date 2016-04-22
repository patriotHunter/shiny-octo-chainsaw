#include "Uti.h"
#include "Struct.h"


int main(){
	wfstream BD("BaseDados", ios::in | ios::out);
	wchar_t x[500];
	BD.read(x,500);
	BD.close;
	Utiarray(x);
	int i = 0;
	while (i<TAMANHO){
		if (array_util[i].numero == 0){
			i = 500;
		}
		else{
			wcout << array_util[i].numero << endl;
			wcout << array_util[i].nome << endl;
			wcout << array_util[i].nasc.dia << endl;
			wcout << array_util[i].nasc.mes << endl;
			wcout << array_util[i].nasc.ano << endl;
			wcout << array_util[i].morada.rua << endl;
			wcout << array_util[i].morada.numPorta << endl;
			wcout << array_util[i].morada.codPost << endl;
			wcout << array_util[i].pass << endl;
		}
	}
	return 0;
}