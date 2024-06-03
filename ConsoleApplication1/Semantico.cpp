#include "Semantico.h"
#include "Constants.h"
#include <iostream>
#include <stack>
#include <stack>
#include "TabelaSemantica.h"

using namespace std;
using namespace SymbolTable;

string stringTemp;
int vectorSize;
int vectorPos;
SymbolTable::Symbol* symbolOnExp;
Temp* temp;
Temp* temp2;

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
		8 -> Especifica que variável é vetor
		9 -> Valida tamanho do vetor
		10 -> Seleciona posição atual do vetor
		11 -> Aumenta tamanho do vetor quadno declarado dinamicamente
		12 -> Especifica que é uma matriz
		13 -> Gera o .data do assembly
	*/

	switch (action) {
	case 1:
		currentSymbol = new Symbol();

		break;
	case 2:
		currentSymbol->convertAndSetSymbol(token->getLexeme());

		break;

	case 3:
		if (table.find(currentScope, token->getLexeme()) != nullptr)
		{
			throw SemanticError("Variavel com mesmo nome declarada.", token->getPosition());
		}

		stringTemp = token->getLexeme();
		currentSymbol->id = stringTemp;
		currentSymbol->idOnData = stringTemp.replace(0, 1, "");
		currentSymbol->scope = currentScope;
		table.symbols.push_front(currentSymbol);

		break;

	case 4:
		if (table.find(currentScope, token->getLexeme()) == nullptr)
		{
			throw SemanticError("Tentativa de utilizacao de variavel nao existe no escopo.", token->getPosition());
		}

		currentSymbol = table.find(currentScope, token->getLexeme());

		break;
	case 5:
		if (table.find(currentScope, "func_" + token->getLexeme()) != nullptr)
		{
			throw SemanticError("Função com mesmo nome declarada.", token->getPosition());
		}

		currentSymbol->id = "func_" + token->getLexeme();
		currentSymbol->scope = currentScope;
		currentSymbol->func = true;
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
	case 8:
		currentSymbol->vector = true;

		break;
	case 9:
		vectorSize = stoi(token->getLexeme());

		if (vectorSize < 1) {
			throw SemanticError("Tamanho de vetor não pode ser menor que 1.", token->getPosition());
		}

		currentSymbol->vectorSize = vectorSize;

		break;
	case 10:
		vectorPos = stoi(token->getLexeme());

		if (!currentSymbol->vector) {
			throw SemanticError("Variável selecionada não é um vetor.", token->getPosition());
		}
		else if ((vectorPos < 0) || (vectorPos >= currentSymbol->vectorSize)) {
			throw SemanticError("Posição do vetor inválida.", token->getPosition());
		}

		currentSymbol->vectorPos = vectorPos;

		break;

	case 11:
		currentSymbol->vectorSize++;

		break;
	case 12:
		currentSymbol->matrix = true;

		break;
	case 13:
		for (auto t : assembly.temp)
		{
			assembly.data.append(t.name);
			assembly.data.append(" : 0\n");
		}

		for (auto it = table.symbols.rbegin(); it != table.symbols.rend(); ++it)
		{
			Symbol sym = **it;

			assembly.data.append(sym.idOnData);

			if (sym.vector)
			{
				assembly.data.append(":");

				for (int i = 0; i < sym.vectorSize; i++)
				{
					assembly.data.append(" 0,");
				}

				assembly.data.replace((assembly.data.length() - 1), assembly.data.length(), "\n");
			}
			else
			{
				assembly.data.append(": 0\n");
			}
		}

		break;

	case 14:
		currentSymbol->initialized = true;
		assembly.gera_cod("LD", "$in_port");
		assembly.gera_cod("STO", currentSymbol->idOnData);

		break;
	case 15:
		temp = assembly.getTemp();
		temp2 = assembly.getTemp();

		assembly.gera_cod("LDI", to_string(currentSymbol->vectorPos));
		assembly.gera_cod("STO", temp->name);
		assembly.gera_cod("LD", "$in_port");
		assembly.gera_cod("STO", temp2->name);
		assembly.gera_cod("LD", temp->name);
		assembly.gera_cod("STO", "$indr");
		assembly.gera_cod("LD", temp2->name);
		assembly.gera_cod("STOV", currentSymbol->idOnData);

		temp->livre = true;
		temp2->livre = true;

		break;
	case 16:
		currentSymbol = nullptr;

		break;

	case 17:
		if (currentSymbol != nullptr) {
			if (currentSymbol->vector) {
				temp = assembly.getTemp();
				temp2 = assembly.getTemp();

				assembly.gera_cod("LDI", to_string(currentSymbol->vectorPos));
				assembly.gera_cod("STO", "$indr");
				assembly.gera_cod("LDV", currentSymbol->idOnData);
				assembly.gera_cod("STO", "$out_port");

				temp->livre = true;
				temp2->livre = true;
			}
			else {
				assembly.gera_cod("LD", currentSymbol->idOnData);
				assembly.gera_cod("STO", "$out_port");
			}
		}
		else {


			// Receber o valor de uma expressão aritmética (resolver depois)
		}

		break;

	case 18:
		if (currentSymbol->vector) {
			temp = assembly.getTemp();
			temp2 = assembly.getTemp();

			assembly.gera_cod("LDI", to_string(currentSymbol->vectorPos));
			assembly.gera_cod("STO", temp->name);

			if (symbolOnExp != nullptr) {
				if (symbolOnExp->vector) {
					assembly.gera_cod("LDI", to_string(symbolOnExp->vectorPos));
					assembly.gera_cod("STO", "$indr");
					assembly.gera_cod("LDV", symbolOnExp->idOnData);
				}
				else {
					assembly.gera_cod("LD", symbolOnExp->idOnData);
				}
			}
			else {
				assembly.gera_cod("LDI", token->getLexeme());
			}
			
			assembly.gera_cod("STO", temp2->name);
			assembly.gera_cod("LD", temp->name);
			assembly.gera_cod("STO", "$indr");
			assembly.gera_cod("LD", temp2->name);
			assembly.gera_cod("STOV", currentSymbol->idOnData);

			temp->livre = true;
			temp2->livre = true;
		}
		else {
			if (symbolOnExp != nullptr) {
				if (symbolOnExp->vector) {
					assembly.gera_cod("LDI", to_string(symbolOnExp->vectorPos));
					assembly.gera_cod("STO", "$indr");
					assembly.gera_cod("LDV", symbolOnExp->idOnData);
				}
				else {
					assembly.gera_cod("LD", symbolOnExp->idOnData);
				}
			}
			else {
				assembly.gera_cod("LDI", token->getLexeme());
			}

			assembly.gera_cod("STO", currentSymbol->idOnData);
		}

		symbolOnExp = nullptr;

		break;

	case 19:
		symbolOnExp = table.find(currentScope, token->getLexeme());

		if (symbolOnExp == nullptr)
		{
			throw SemanticError("Tentativa de utilizacao de variavel nao existe no escopo.", token->getPosition());
		}

		break;

	case 20:
		vectorPos = stoi(token->getLexeme());

		if (!symbolOnExp->vector) {
			throw SemanticError("Variável selecionada não é um vetor.", token->getPosition());
		}
		else if ((vectorPos < 0) || (vectorPos >= symbolOnExp->vectorSize)) {
			throw SemanticError("Posição do vetor inválida.", token->getPosition());
		}

		symbolOnExp->vectorPos = vectorPos;

		break;
	};
}
