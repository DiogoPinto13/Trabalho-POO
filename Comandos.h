#ifndef COMANDOS_H
#define COMANDOS_H
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "UI.h"
#include "Save.h"
class Edificios;
class Recursos;
class Trabalhadores;

using namespace std;

class Ilha;

class Comandos : public Interface {

public:
	Comandos()=default;
    Comandos(const Comandos& outro);

	virtual Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo);
	
protected:
    Save savess;
    Interface interface;
	friend class Ilha;

};

class Constroi : public Comandos {

public:
	Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;



};

class Contrata : public Comandos {

public:
	Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:


};

class List : public Comandos {

public:
	Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:
	void printTab(Ilha& ilha, Jogo& jogo);

};

class Vende : public Comandos {

public:
	Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:
    Interface& vende(string tipo, float quantidade, Jogo& jogo);

};

class Liga : public Comandos{

public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:

};

class Desliga : public Comandos{

public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:

};
class Sai : public Comandos {

public:
	Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


private:

};
class Debash : public Comandos{

public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


};
class Debed : public Constroi{

public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


};
class Debkill : public Comandos{

public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;


};
class Move : public Comandos{
public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};

class Upgrade : public Constroi{
public:
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};


class Savegame : public Comandos{
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};

class Loadgame : public Comandos{
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};

class Deletesave : public Comandos{
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};

class Config : public Comandos{
    Interface& execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) override;

};
#endif
