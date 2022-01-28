#ifndef JOGO_H
#define JOGO_H
#include <iostream>
#include <sstream>
#include "Ilha.h"
#include <vector>
#include "Recursos.h"
#include "Comandos.h"
#include "UI.h"
using namespace std;

class Dias;

class Jogo : public Observable {

public:
	Jogo(Comandos& comandos);
    Jogo(const Jogo& outro);
	void comecaJogo();
    void addObserver(Observer &o) override;
    void removeObserver(Observer &o) override;
    void notifyObservers(Interface& interface) override;
    map<string, Edificios *>& getTipos();
    map<string, Trabalhadores*>& getTiposTrabalhadores();
    array<Recursos*, 7>& getListarecursos();
    void setListaRecursos(array<Recursos*, 7> recursos);
    void updateTipos(array<Recursos*, 7> recursos);
    void updateTiposTrabalhadores(array<Recursos*, 7> recursos);
    void setIlha(Ilha ilha);
    Ilha& getIlha();
private:
	Ilha ilha;
	Comandos comando;
	vector<Dias*> dias;
    array<Recursos*, 7> listaRecursos;
    map<string, Edificios *> tipos;
    map<string, Trabalhadores*> tiposTrabalhadores;
};

#endif