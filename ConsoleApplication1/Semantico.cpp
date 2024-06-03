#include "Semantico.h"
#include "Constants.h"
#include <iostream>
#include <stack>
#include <stack>
#include "TabelaSemantica.h"

using namespace std;
using namespace SymbolTable;

int vectorSize;
int vectorPos;
SymbolTable::Symbol* selectedSymbol;

void Semantico::executeAction(int action, const Token* token) throw (SemanticError)
{
	std::cout << "Action: " << action << ", Token: " << token->getId()
		<< ", Lexema: " << token->getLexeme() << std::endl;

	/*
		1 -> Inicializa simbolo novo
		2 -> Define o tipo do s�mbolo
		3 -> Define o nome da vari�vel / Verifica se j� existe uma com o mesmo nome
		4 -> Verifica se vari�vel est� declarada no escopo
		5 -> Declara o nome da fun��o / Verifica se existe fun��o com mesmo nome
		6 -> retorna o escopo
		7 -> Verifica se fun��o foi declarada
		8 -> Especifica que vari�vel � vetor
		9 -> Valida tamanho do vetor
		10 -> Seleciona posi��o atual do vetor
		11 -> Aumenta tamanho do vetor quadno declarado dinamicamente
		12 -> Especifica que � uma matriz
	*/

	switch (action) {
	case 1:
		currentSymbol = new Symbol();

		break;
	case 2:
		(*currentSymbol).convertAndSetSymbol(token->getLexeme());

		break;

	case 3:
		if (table.find(currentScope, token->getLexeme()) != nullptr)
		{
			throw SemanticError("Variavel com mesmo nome declarada.", token->getPosition());
		}

		(*currentSymbol).id = token->getLexeme();
		(*currentSymbol).scope = currentScope;
		table.symbols.push_front(currentSymbol);

		break;

	case 4:
		selectedSymbol = table.find(currentScope, token->getLexeme());

		if (selectedSymbol == nullptr)
		{
			throw SemanticError("Tentativa de utilizacao de variavel nao existe no escopo.", token->getPosition());
		}

		currentSymbol = selectedSymbol;

		break;
	case 5:
		if (table.find(currentScope, "func_" + token->getLexeme()) != nullptr)
		{
			throw SemanticError("Fun��o com mesmo nome declarada.", token->getPosition());
		}

		(*currentSymbol).id = "func_" + token->getLexeme();
		(*currentSymbol).scope = currentScope;
		(*currentSymbol).func = true;
		table.symbols.push_front(currentSymbol);
		currentScope++;

		break;
	case 6:
		currentScope--;

		break;
	case 7:
		if (table.find(currentScope, "func_" + token->getLexeme()) == nullptr)
		{
			throw SemanticError("Fun��o n�o declarada.", token->getPosition());
		}

		break;
	case 8:
		(*currentSymbol).vector = true;

		break;
	case 9:
		vectorSize = stoi(token->getLexeme());

		if (vectorSize < 1) {
			throw SemanticError("Tamanho de vetor n�o pode ser menor que 1.", token->getPosition());
		}

		(*currentSymbol).vectorSize = vectorSize;

		break;
	case 10:
		// verificar a sele��o do vetor
		vectorPos = stoi(token->getLexeme());

		if (!(*currentSymbol).vector) {
			throw SemanticError("Vari�vel selecionada n�o � um vetor.", token->getPosition());
		} else if((vectorPos < 0) || (vectorPos >= (*currentSymbol).vectorSize)) {
			throw SemanticError("Posi��o do vetor inv�lida.", token->getPosition());
		}

		(*currentSymbol).vectorPos = vectorSize;

		break;

	case 11:
		(*currentSymbol).vectorSize++;
		
		break;
	case 12:
		(*currentSymbol).matrix = true;

		break;
	};
}
