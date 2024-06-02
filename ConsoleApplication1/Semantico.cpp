#include "Semantico.h"
#include "Constants.h"
#include <iostream>
#include <stack>
#include <stack>
#include "TabelaSemantica.h"

using namespace std;
using namespace SymbolTable;

void Semantico::executeAction(int action, const Token* token) throw (SemanticError)
{
	std::cout << "Action: " << action << ", Token: " << token->getId()
		<< ", Lexema: " << token->getLexeme() << std::endl;

	/*
		1 -> Inicializa simbolo novo
		2 -> Define o tipo do símbolo
		3 -> Define o nome da variável / Verifica se já existe uma com o mesmo nome
		4 -> Verifica se variável está declarada no escopo
		5 -> Declara o nome da função / Verifica se existe função com mesmo nome
		6 -> retorna o escopo
		7 -> Verifica se função foi declarada
	*/

	switch (action) {
	case 1:
		currentSymbol = Symbol();

		break;
	case 2:
		currentSymbol.convertAndSetSymbol(token->getLexeme());

		break;

	case 3:
		if (table.find(currentScope, token->getLexeme()) != nullptr)
		{
			throw SemanticError("Variavel com mesmo nome declarada.", token->getPosition());
		}

		currentSymbol.id = token->getLexeme();
		currentSymbol.scope = currentScope;
		table.symbols.push_front(currentSymbol);

		break;

	case 4:
		if (table.find(currentScope, token->getLexeme()) == nullptr)
		{
			throw SemanticError("Tentativa de utilizacao de variavel nao existe no escopo.", token->getPosition());
		}

		break;
	case 5:
		if (table.find(currentScope, "func_" + token->getLexeme()) != nullptr)
		{
			throw SemanticError("Função com mesmo nome declarada.", token->getPosition());
		}

		currentSymbol.id = "func_" + token->getLexeme();
		currentSymbol.scope = currentScope;
		currentSymbol.func = true;
		table.symbols.push_front(currentSymbol);
		currentScope++;

		break;
	case 6:
		currentScope--;

		break;
	case 7:
		if (table.find(currentScope, "func_" + token->getLexeme()) == nullptr)
		{
			throw SemanticError("Função não declarada.", token->getPosition());
		}

		break;

		//case 4:
		//	ptrAtribuir = Tabela.Find(stackEscopo, token->getLexeme());
		//	if (ptrAtribuir == nullptr)
		//	{
		//		ResetaTabela();
		//		throw SemanticError("Tentativa de atribuicao de variavel nao existente.", token->getPosition());
		//	}
		//	lstExp.clear();
		//	store = token->getLexeme();
		//
		//	break;


		//case 6:
		//	setInitialized = true;
		//
		//	switch (semanticTable.atribType(ConvertType(lastSimbol->tipo), return_type)) {
		//
		//	case -1:
		//		ResetaTabela();
		//		throw SemanticError("Erro na atribuicao de variavel.", token->getPosition());
		//	case 1:
		//		Tabela.setWarning(*lastSimbol, "Perda de precisao");
		//		break;
		//	}
		//
		//	for (Simbolo* ptr : lstExp)
		//	{
		//		if (ptr->escopo == lastSimbol->escopo && ptr->id == lastSimbol->id)
		//		{
		//			if (lastSimbol->inicializado == false) {
		//				Tabela.setWarning(*lastSimbol, "Utilizacao da variavel na atribuicao da mesma");
		//			}
		//			setInitialized = false;
		//		}
		//		else
		//		{
		//			ptr->usado = true;
		//			if (!ptr->inicializado)
		//				Tabela.setWarning(*ptr);
		//		}
		//	}
		//	if (setInitialized)
		//	{
		//		lastSimbol->inicializado = true;
		//	}
		//
		//	lstExp.clear();
		//	break;
		//
		//case 7:
		//
		//	if (Tabela.Procurar(stackEscopo, token->getLexeme()))
		//	{
		//		ResetaTabela();
		//		throw SemanticError("Variavel com mesmo nome declarada", token->getPosition());
		//	}
		//
		//	simbolo.funcao = true;
		//	simbolo.parametro = false;
		//	simbolo.vetor = false;
		//	simbolo.id = token->getLexeme();
		//	simbolo.escopo = stackEscopo.top();
		//	func = token->getLexeme();
		//	Tabela.lstSimbolos.push_front(simbolo);
		//	ptrFunc = &Tabela.lstSimbolos.front();
		//
		//	simbolo.parametro = true;
		//	break;
		//
		//case 10:
		//	escopo++;
		//	stackEscopo.push(escopo);
		//	break;
		//
		//case 11:
		//	if (stackEscopo.empty())
		//	{
		//		ResetaTabela();
		//		throw SemanticError("} inesperado", token->getPosition());
		//	}
		//	stackEscopo.pop();
		//	break;
		//
		//
	};
}





//void ResetaTabela()
//{
//	while (!stackEscopo.empty())
//	{
//		stackEscopo.pop();
//	}
//	while (!stackRot.empty())
//	{
//		stackRot.pop();
//	}
//	contIf = 0;
//	escopo = 0;
//	contpar = 0;
//	simbolo.vetor = false;
//	simbolo.parametro = false;
//	lstExp.clear();
//	lstExpType.clear();
//	lstOperators.clear();
//	vectorExp = false;
//	firstVar = true;
//	flagOp = false;
//}



