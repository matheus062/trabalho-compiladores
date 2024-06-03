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
	outputFile << semantico->assembly.data;
	outputFile.close();

	return 0;
}