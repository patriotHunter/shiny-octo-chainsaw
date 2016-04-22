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



void Utiarray(wfstream & BD){
	wstring num, nome, dia, mes, ano, rua, nump, codpostal, pass;
	int u = 0;
	int lu;
	int i = 0;
	BD.clear();
	BD.seekg(ios::beg);
	while (u < TAMANHO){
		while ( lu < 9)
		{
			lu = 0;
			if (lu == 0){
				BD >> num;
				if (num.compare(L"\n") == 0){
					u = TAMANHO;
				}
				else{
				ErroConv(convert_Str_2_INT(num));
				array_util[u].numero = convert_Str_2_INT(num);
				}
			}
			if (lu == 1){
				BD >> nome;
				array_util[u].nome = nome;
			}
			if (lu == 2){
				BD >> dia;
				ErroConv(convert_Str_2_INT(dia));
				array_util[u].nasc.dia = convert_Str_2_INT(dia);
			}
			if (lu == 3){
				BD >> mes;
				ErroConv(convert_Str_2_INT(mes));
				array_util[u].nasc.mes = convert_Str_2_INT(mes);
			}
			if (lu == 4){
				BD >> ano;
				ErroConv(convert_Str_2_INT(ano));
				array_util[u].nasc.ano = convert_Str_2_INT(ano);
			}
			if (lu == 5){
				BD >> rua;
				array_util[u].morada.rua = rua;
			}
			if (lu == 6){
				BD >> nump;
				array_util[u].morada.numPorta = nump;
			}
			if (lu == 7){
				BD >> codpostal;
				array_util[u].morada.codPost = codpostal;
			}
			if (lu == 6){
				BD >> pass;
				array_util[u].pass = pass;
			}
			lu++;
			i++;
			}
		}
			u++;
	}