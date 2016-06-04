#pragma once

#include "Struct.h"
#include "Other_Functions.h"
#include "Functions_FILAS.h"

/*
Le a informação relativa às refeições e coloca-a no array respectivo
*/
void leDadosRefeicoes();


/*
Escreve os dados de refeicoes nos ficheiros
*/
void escreveDadosRefeicoes();

/*
Lê ficheiro de dados de utilizador e carrega os dados num array
*/
void leDadosUtilizadores();

/*
Escreve os dados de utilizadores nos ficheiros
*/
void escreveDadosUtilizadores();

/*
Cria um aluno e insere-o na lista de alunos, não é feito a confirmação de alguns dados visto esta operação só poder ser realizada por funcionários
*/
int inserirAluno();

/*
Coloca os utilizadores no array por ordem alfabética para facilitar a colocação dos utilizadores no ecrã por ordem alfabética
*/
void organizearray_bynames();

/*
Realiza o login se a informação do utilizador constar na base de dados e o número e a pass estiverem correctos
*/
bool login_logout();

/*
Imprime users por ordem alfabética
*/
void printUsers();

/*
Permite carregar plafond se nao houver informaçao cria um novo plafond na lista
*/
int carregarPlafond();

/*
Remover alunos
*/
void removerAluno();

/*
Pesquisar pelo primeiro nome
*/
void primNome();

/*
Listar Refeições
*/
void listarRefeicao();

/*
Encomendar Refeições
*/
void encomendarRefeicao();

/*
Consumir Refeição
*/
void consumirRefeição();

/*
Coloca o menu principal no ecrã e realiza funções consoante a opção escolhida pelo utilizador.
*/
void printMainMenu();



