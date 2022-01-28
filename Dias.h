#ifndef RATINHOCORPORATION_DIAS_H
#define RATINHOCORPORATION_DIAS_H
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "UI.h"

using namespace std;
class Ilha;
class Comandos;
class Jogo;
class Interface;
class Dias{

public:
    Dias(Ilha& ilha, Comandos& comandos);
    virtual Dias* cloneDias()=0;
    virtual void executa(Jogo& jogo) = 0;

protected:
    Ilha& ilha;
    Comandos& comandos;
    static int nDia;
    Interface handler;

public:
    static int getNDia();

    static void setNDia(int nDia);

};

class Manha : public Dias {

public:
    Manha(Ilha& ilha, Comandos& comandos);
    Manha* cloneDias() override;
    void executa(Jogo& jogo) override;
};

class MeioDia : public  Dias{

public:
    MeioDia(Ilha& ilha, Comandos& comandos);
    MeioDia* cloneDias() override;
    void executa(Jogo& jogo) override;
private:
    Interface& executa_comando(istringstream& comand,Jogo& jogo);
    void executa_fich(istringstream& comand,Jogo& jogo);
};

class Noite : public  Dias{

public:
    Noite(Ilha& ilha, Comandos& comandos);
    Noite* cloneDias() override;
    void executa(Jogo& jogo) override;
};

#endif //RATINHOCORPORATION_DIAS_H
