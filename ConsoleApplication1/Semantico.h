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
		string idOnData;
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
		int vectorPos = 0;
		int vectorSize = 0;

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
		list<Symbol*> symbols;

		Symbol* find(int scope, string lexema)
		{
			for (Symbol* sym : this->symbols)
			{
				if (((*sym).scope == scope) && ((*sym).id == lexema))
				{
					return sym;
				}
			}

			return nullptr;
		}
	};

	class Assembly {
	public:
		string data = "";
		string text = "";
		list<Temp> temp;
		int contador = 0;

		Assembly() {
			data.append(".data\n");
			text.append(".text\n");
		}

		Temp* getTemp()
		{
			for (Temp& t : temp)
			{
				if (t.livre) {
					t.livre = false;

					return &t;
				}
			}

			Temp* t = new Temp();
			t->livre = false;
			t->name = "temp" + to_string(contador);
			temp.push_back(*t);
			this->contador++;

			return t;
		}

		void gera_cod(string funcao, string valor)
		{
			text.append(funcao);
			text.append(" ");
			text.append(valor);
			text.append("\n");
		}
	};

}

class Semantico
{
public:
	SymbolTable::Assembly assembly = SymbolTable::Assembly();
	SymbolTable::Table table;
	SymbolTable::Symbol* currentSymbol;
	int currentScope = 0;

	void executeAction(int action, const Token* token) throw (SemanticError);
};

#endif
