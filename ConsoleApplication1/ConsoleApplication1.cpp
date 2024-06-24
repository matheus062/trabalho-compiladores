#include "Lexico.h"
#include "Semantico.h"
#include "Sintatico.h"
#include "Constants.h"
#include <sstream>
#include <string>
#include <istream>
#include <iostream>
#include <fstream>

using namespace std;

void replace_all(
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

int main()
{
	ifstream infile{ "file.txt" };
	string file_contents{ istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };

	std::stringstream string(file_contents);
	Lexico* lexico = new Lexico();
	lexico->setInput(string);

	Sintatico* sintatico = new Sintatico();
	Semantico* semantico = new Semantico();
    
	sintatico->parse(lexico, semantico);

	ofstream outputFile("assembly.txt");

    replace_all(semantico->Tabela.data, "$", "");
    replace_all(semantico->Tabela.data, "out_port", "$out_port");
    replace_all(semantico->Tabela.data, "in_port", "$in_port");

	outputFile << semantico->Tabela.data;
	outputFile.close();

	return 0;
}