#ifndef EDIFICIOS_H
#define EDIFICIOS_H

#include <iostream>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <tuple>
#include "Armazem.h"
using namespace std;
class Recursos;
class Zona;

class Edificios : public Armazem {

public:
    Edificios(const string& nome, const array<Recursos*, 7> recursos,const float capacidade,const float armazenamento,bool podeMelhorar);
	virtual ~Edificios()=default;
    Edificios(const Edificios& outro);
    void setLigado(const bool estado);
    virtual string getNome() const;
	virtual Edificios* cloneEdificios()=0;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos)=0;
    virtual void extrai(){};
    void MudaZona(Zona* novaZona);
    virtual bool upgrade();
    void updatecusto(array<Recursos*, 7> recursos);
    bool setCusto(int euro);
    virtual void evento(int ndia);
    void setListaRecursos(const array<Recursos*, 7>& listarecursos);
    const int getNivel() const;
    bool isLigado() const;

    const vector< tuple<Recursos *, float> > &getUpgradeCusto() const;

    const map<tuple<Recursos *, Recursos *>, tuple<float, float>> &getCusto() const;
protected:
    bool podeMelhorar;
    int nivel;
    bool ligado;
    string nome;
    array<Recursos*, 7> recursos;
    vector< tuple<Recursos*,float> > upgradeCusto;
    Zona* zona;
    map<tuple<Recursos*,Recursos*>, tuple<float,float>> custo;
private:

};

class MinaFerro :  public Edificios{

public:
    MinaFerro(const string& nome, const array<Recursos*, 7> recursos);
    void evento(int ndia) override;
    void desabar();
	Edificios* cloneEdificios() override;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;

private:
    float probDesabar;
};

class MinaCarvao : public Edificios{

public:
    MinaCarvao(const string& nome, const array<Recursos*, 7> recursos);
	Edificios* cloneEdificios() override;
    void evento(int ndia) override;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;
    void desabar();

private:
    float probDesabar;

};


class Bateria : public Edificios {

public:
    Bateria(const string& nome, const array<Recursos*, 7> recursos);
	Edificios* cloneEdificios() override;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;

private:

};
class CentralEletrica : public Edificios{

public:
    CentralEletrica(const string& nome, const array<Recursos*, 7> recursos);
    Edificios* cloneEdificios() override;
    virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;

private:
    using function_t = bool(Armazem::*)(const float);
    static map<string,function_t> funcs;
    static map<string,string> relacoes;
    static map<string,float> funcs_parameters;

};

class Fundicao : public Edificios {

public:
    Fundicao(const string& nome, const array<Recursos*, 7> recursos);
	Edificios* cloneEdificios() override;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;

private:
    using function_t = bool(Armazem::*)(const float);
    static map<string,function_t> funcs;
    static map<string,string> relacoes;
    static map<string,float> funcs_parameters;

};

class Serraria : public Edificios {

public:
    Serraria(const string& nome, const array<Recursos*, 7> recursos);
    Edificios* cloneEdificios() override;
    Recursos* addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;

private:
    using function_t = bool(Armazem::*)(const float);
    static map<string,function_t> funcs;
    static map<string,string> relacoes;
    static map<string,float> funcs_parameters;

};

class EdificioX : public Edificios {

public:
    EdificioX(const string& nome, const array<Recursos*, 7> recursos);
	Edificios* cloneEdificios() override;
	virtual Recursos* addRecursos(const array<Recursos*, 7> recursos) override;

private:

};
#endif