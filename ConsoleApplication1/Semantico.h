#ifndef SEMANTICO_H
#define SEMANTICO_H

#include <stack>
#include "Token.h"
#include "SemanticError.h"
#include <list>
#include <iostream>

using namespace std;

namespace SymbolTable {

	class Symbol {
	public:
		enum Type {
			Int,
			Float,
			Boolean,
			String,
			Array,
			Void,
			Null,
		};

		string id;
		Type type;
		int scope;
		bool initialized = false;
		bool used = false;
		bool param = false;
		bool vector = false;
		bool matrix = false;
		bool reference = false;
		bool func = false;
		int posParam = 0;
		int posVetor = 0;

		void convertAndSetSymbol(string type)
		{
			if (type == "int")
				this->type = Type::Int;
			else if (type == "float")
				this->type = Type::Float;
			else if (type == "boolean")
				this->type = Type::Boolean;
			else if (type == "string")
				this->type = Type::String;
			else if (type == "array")
				this->type = Type::Array;
			else if (type == "void")
				this->type = Type::Void;
			else if (type == "null")
				this->type = Type::Null;
		}
	};

	struct WarningMessage {
	public:
		string error;
		Symbol symbol;
	};

	class Warning {
	public:
		void setUnusedWarning(Symbol symbol)
		{
			WarningMessage message;
			message.symbol = symbol;

			if (symbol.func) {
				message.error = "Função não utilizada.";
			}
			else if (symbol.param) {
				message.error = "Parâmetro não utilizado.";
			}
			else {
				message.error = "Variável não utilizada.";
			}

			this->errorList.push_back(message);
		}

		void setWarning(Symbol symbol, string error)
		{
			WarningMessage message;
			message.error = error;
			message.symbol = symbol;

			this->errorList.push_back(message);
		}

	private:
		list<WarningMessage> errorList;
	};

	class Temp {
	public:
		string name;
		bool livre;
	};

	class Table {
	public:
		list<Symbol> symbols;
		// string data;
		// list<Temp> temp;
		// int contador = 0;

		// Temp* GetTemp()
		// {
		// 	for (Temp& t : temp)
		// 	{
		// 		if (t.livre) {
		// 			return &t;
		// 		}
		// 	}
		// 
		// 	Temp t;
		// 
		// 	t.livre = true;
		// 	t.name = "temp" + to_string(contador);
		// 	temp.push_back(t);
		// 
		// 	this->contador++;
		// 
		// 	for (Temp& t : temp)
		// 	{
		// 		if (t.livre)
		// 			return &t;
		// 	}
		// 
		// 	return nullptr;
		// }

		//bool Procurar(stack<int> Escopo, string lexema)
		//{
		//	while (!Escopo.empty())
		//	{
		//		for (Symbol sim : this->lstSimbolos)
		//		{
		//			if (sim.escopo == Escopo.top() && sim.id == lexema)
		//			{
		//				return true;
		//			}
		//		}
		//		Escopo.pop();
		//	}
		//	return false;
		//}
		
		Symbol* find(int scope, string lexema)
		{
			for (Symbol& sym : this->symbols)
			{
				if ((sym.scope == scope) && (sym.id == lexema))
				{
					return &sym;
				}
			}

			return nullptr;
		}
	};

}

class Semantico
{
public:
	SymbolTable::Table table;
	SymbolTable::Symbol currentSymbol;
	int currentScope;

	void executeAction(int action, const Token* token) throw (SemanticError);

	Semantico() {
		this->currentScope = 0;
	}
};

#endif
