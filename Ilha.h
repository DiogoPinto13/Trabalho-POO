#ifndef ILHA_H
#define ILHA_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <array>
#include <iomanip>
#include <map>
#include "Zona.h"
#include "Edificios.h"
#include "Comandos.h"
using namespace std;
class Ilha {

public:
	Ilha() = default;
    Ilha(const Ilha& outro);
    ~Ilha();
    void printTab();
    bool list(istringstream& comand);
	Zona* getZona(const int linhas, const int colunas);
	int getLinhas() const;
	int getColunas() const;
	Ilha& operator=(const Ilha& outro);
private:
	friend class Jogo;
	friend class Comandos;
	Zona*** criaTab(const int linhas, const int colunas, Jogo& jogo);
	void limpaTab(Zona*** tab, const int linhas);
    int linhas;
    int colunas;
    Zona*** tab;
	
};
#endif