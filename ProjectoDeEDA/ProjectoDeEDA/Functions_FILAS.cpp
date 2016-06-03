#include "Functions_FILAS.h"

void novo(filaUtilizadores& fila)
{
	fila.atual = NULL;
}

void novo(filaRefeicao& fila)
{
	fila.atual = NULL;
}

void insereNaFila(filaUtilizadores& fila, utilizador util)
{
	filaUtilizadores::UTIL * novo = new filaUtilizadores::UTIL();
	novo->util = util;
	novo->proximo = NULL;
	novo->anterior = fila.atual;
	if (fila.atual == NULL)
	{
		fila.atual->proximo = novo;
	}
	fila.atual = novo;
}

void insereNaFila(filaRefeicao& fila, refeicao ref)
{
	filaRefeicao::REF * novo = new filaRefeicao::REF();
	novo->refeicao = ref;
	novo->proximo = NULL;
	novo->anterior = fila.atual;
	if (fila.atual == NULL)
	{
		fila.atual->proximo = novo;
	}
	fila.atual = novo;
}

bool vazio(filaUtilizadores& fila)
{
	if (fila.atual == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool vazio(filaRefeicao& fila)
{
	if (fila.atual == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void retiraDaFila(filaUtilizadores& fila, int numero)
{
	filaUtilizadores::UTIL * atual = new filaUtilizadores::UTIL();

	if (vazio(fila))
	{
		wcout << "Não tem nenhum utilizador na lista!!!" << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		return;
	}

	atual = fila.atual;

	while (atual->util.numero != numero && atual != NULL)
	{
		atual = atual->anterior;
	}

	if (atual == NULL)
	{
		wcout << "Não tem nenhum utilizador na lista com este numero!!!" << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		return;
	}
	else
	{
		filaUtilizadores::UTIL * acima = new filaUtilizadores::UTIL();
		filaUtilizadores::UTIL * abaixo = new filaUtilizadores::UTIL();

		acima = atual->proximo;
		abaixo = atual->anterior;
		
		if (acima != NULL)
		{
			acima->anterior = atual->anterior;
		}
		if (abaixo != NULL)
		{
			abaixo->proximo = atual->proximo;
		}

		delete atual;
	}
}

void retiraDaFila(filaRefeicao& fila, refeicao ref)
{
	filaRefeicao::REF * atual = new filaRefeicao::REF();

	if (vazio(fila))
	{
		wcout << "Não tem nenhuma refeição na lista!!!" << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		return;
	}

	atual = fila.atual;

	while (atual != NULL)
	{
		if (atual->refeicao.numero == ref.numero && atual->refeicao.jantar == ref.jantar && atual->refeicao.data.ano == ref.data.ano &&
			atual->refeicao.data.mes == ref.data.mes && atual->refeicao.data.dia == ref.data.dia)
		{
			break;
		}
		else
		{
			atual = atual->anterior;
		}
	}

	if (atual == NULL)
	{
		wcout << "Não tem nenhuma refeição correspondente na lista!!!" << endl << endl << "Pressione ENTER para prosseguir.";
		cin.sync();
		cin.get();
		return;
	}
	else
	{
		filaRefeicao::REF * acima = new filaRefeicao::REF();
		filaRefeicao::REF * abaixo = new filaRefeicao::REF();

		acima = atual->proximo;
		abaixo = atual->anterior;

		acima->anterior = atual->anterior;
		abaixo->proximo = atual->proximo;

		delete atual;
	}
}

filaUtilizadores ordenaPorNome(filaUtilizadores& fila)
{
	filaUtilizadores temp;
	novo(temp);

	filaUtilizadores::UTIL * atual = new filaUtilizadores::UTIL();

	atual = fila.atual;

	while (atual != NULL)	//Percorre a lista original
	{
		if (temp.atual == NULL)
		{
			insereNaFila(temp, fila.atual->util);
		}
		else
		{
			filaUtilizadores::UTIL * atual_2 = new filaUtilizadores::UTIL();

			atual_2 = temp.atual;

			while (atual_2 != NULL)				//Percorre a lista temporaria
			{
				
				if (atual->util.nome.compare(atual_2->util.nome) <= 0)
				{
					if (atual_2->proximo == NULL)
					{
						insereNaFila(temp, atual->util);
					}
					else
					{
						atual->anterior = atual_2;
						atual->proximo = atual_2->proximo;
						atual_2->proximo->anterior = atual;
						atual_2->proximo = atual;
					}
					break;
				}
				else if (atual_2->anterior == NULL)
				{
					atual_2->anterior = atual;
					break;
				}
				else
				{
					atual_2 = atual_2->anterior;
				}
			}
		}

		atual = atual->anterior;
	}

	return temp;
}

