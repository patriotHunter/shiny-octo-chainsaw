#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Struct.h"
#include "Functions.h"




bool logged = false;
bool admin = false;
int respostaMainMenu;
int const TAMANHO = 500;
int Util_logged;
utilizador array_util[500];


using namespace std;

void ErroConv(int i){
	if (i == INT_MIN){
		cout << "\nErro, valores errados.\n Precione Enter para terminar o programa.\n";
		cin.sync();
		cin.get();
		exit(1);
	}
}



void Utiarray(wchar_t x[500]){
	wstring num, nome, dia, mes, ano, rua, nump, codpostal, pass;
	int u = 0;
	int lu;
	int i = 0;
	while (u < TAMANHO){
		while ( lu < 9)
		{
			lu = 0;
			if (lu == 0){
				num = x[i];
				if (num.compare(L"\n") == 0){
					u = TAMANHO;
				}
				else{
				ErroConv(convert_Str_2_INT(num));
				array_util[u].numero = convert_Str_2_INT(num);
				}
			}
			if (lu == 1){
				nome = x[i];
				array_util[u].nome = nome;
			}
			if (lu == 2){
				dia = x[i];
				ErroConv(convert_Str_2_INT(dia));
				array_util[u].nasc.dia = convert_Str_2_INT(dia);
			}
			if (lu == 3){
				mes = x[i];
				ErroConv(convert_Str_2_INT(mes));
				array_util[u].nasc.mes = convert_Str_2_INT(mes);
			}
			if (lu == 4){
				ano = x[i];
				ErroConv(convert_Str_2_INT(ano));
				array_util[u].nasc.ano = convert_Str_2_INT(ano);
			}
			if (lu == 5){
				rua = x[i];
				array_util[u].morada.rua = rua;
			}
			if (lu == 6){
				nump = x[i];
				array_util[u].morada.numPorta = nump;
			}
			if (lu == 7){
				codpostal = x[i];
				array_util[u].morada.codPost = codpostal;
			}
			if (lu == 8){
				pass = x[i];
				array_util[u].pass = pass;
			}
			lu++;
			i++;
			}
		u++;
		}
	}