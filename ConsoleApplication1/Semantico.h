#ifndef SEMANTICO_H
#define SEMANTICO_H

#include <stack>
#include "Token.h"
#include "SemanticError.h"
#include <list>
#include <iostream>

using namespace std;

class Simbolo {
public:
    string tipo;
    string id;

    int escopo;

    bool inicializado = false;
    bool usado = false;

    bool parametro = false;

    bool funcao = false;
    int posParam = 0;

    bool vetor = false;
    int posVetor = 0;

    void DeclararTipo(std::string t);

};

class Warning {
public:
    string error;
    Simbolo sim;
};

class Temp {
public:
    string name;
    bool livre;
};

class TabelaSimbolo
{
public:
    list<Simbolo> lstSimbolos;
    list<Warning> lstWarning;
    string assembly = "";
    string data;
    list<Temp> temp;
    int contador = 0;

    Temp* GetTemp()
    {
        for (Temp& t : temp)
        {
            if (t.livre) {
                return &t;
            }
        }

        Temp t;

        t.livre = true;
        t.name = "temp" + to_string(contador);
        temp.push_back(t);

        this->contador++;

        for (Temp& t : temp)
        {
            if (t.livre)
                return &t;
        }

        gera_cod("Error:", "nullptr returned.");
        return nullptr;
    }

    void gera_cod(string funcao, string valor)
    {
        assembly.append(funcao);
        assembly.append(" ");
        assembly.append(valor);
        assembly.append("\n");
    }

    void setUnusedWarning()
    {
        Warning war;
        for (Simbolo sim : this->lstSimbolos)
        {
            if (sim.usado == false)
            {
                war.sim = sim;
                if (sim.funcao)
                    war.error = "Funcao nao utilizada";
                else
                    war.error = "Variavel nao utilizada";
                this->lstWarning.push_back(war);
            }
        }
    }

    void setWarning(Simbolo sim, string error = "Variavel nao atribuiada utilizada")
    {
        Warning war;
        war.error = error;
        war.sim = sim;
        this->lstWarning.push_back(war);
    }

    bool Procurar(stack<int> Escopo, string lexema)
    {
        while (!Escopo.empty())
        {
            for (Simbolo sim : this->lstSimbolos)
            {
                if (sim.escopo == Escopo.top() && sim.id == lexema)
                {
                    return true;
                }
            }
            Escopo.pop();
        }
        return false;
    }

    Simbolo* Find(stack<int> Escopo, string lexema)
    {
        while (!Escopo.empty())
        {
            for (Simbolo& sim : this->lstSimbolos)
            {
                if (sim.escopo == Escopo.top() && sim.id == lexema)
                {
                    return &sim;
                }
            }
            Escopo.pop();
        }
        return nullptr;
    }
};

class Semantico
{
public:
    void executeAction(int action, const Token* token) throw (SemanticError);
    std::string getParname(string nome_call, int contpar);
    TabelaSimbolo Tabela;
};

#endif
