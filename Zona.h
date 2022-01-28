#ifndef ZONA_H
#define ZONA_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <array>
#include <map>
#include "Trabalhadores.h"
#include "Armazem.h"

using namespace std;

class Edificios;
class Recursos;
class Ilha;

class Zona : public Armazem {

public:
    Zona(string nome, const array<Recursos*, 7> recursos,Ilha& ilha,int capacidade, int armazenamento);
    Zona(const Zona& outro);
    string getNomeZona() const;
    Edificios* getEdificio() const;
    vector<Trabalhadores*> getTipoTrabalhadores();
    int getNTrabalhadores() const;
    void setTrabalhador(Trabalhadores* trabalhador);
    void setEdificio (Edificios* edificio);
	virtual void addRecursos(const array<Recursos*, 7> recursos);
    virtual Zona* cloneZona();
    virtual float getMultiplier(Recursos* recursoExtraido);
    vector<Zona*> getAdjacente();
    void setlocalizacao(int linha,int coluna);
    virtual void extrai(){};
    void destroiEdificio(Edificios* novoEdificio);
	virtual float getMultiplerDemissao(Trabalhadores* trabalhador);
    virtual void efeito(int nDia);
    void sendPurgatorio(Trabalhadores* trabalhadores,int nDia);
    bool killTrabalhador(int id);
    Trabalhadores* getTrabalhador(int id) const;
    void setIlha(Ilha& ilha);
    virtual ~Zona();

protected:
    Ilha* ilha;
    array<Recursos*, 7> recursos;

private:
    int linha;
    int coluna;
    Edificios* edificio;
    string nomeZona;
    vector<Trabalhadores*> tipoTrabalhadores;
    int nTrabalhadores;

};

class Floresta : public Zona{
public:
    Floresta(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    Floresta(const Floresta& outro);
    Floresta* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    void cresceArvore(int nDia);
    float getMultiplier(Recursos* recursoExtraido) override;
    void efeito(int nDia) override;
    void extrai() override;
private:
    int maxArvores;
    int nLenhadores;
    int nArvores;
};

class Pastagem : public Zona{
public:
    Pastagem(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    Pastagem* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    float getMultiplier(Recursos* recursoExtraido) override;
	float getMultiplerDemissao(Trabalhadores* trabalhador) override;
};

class Montanha : public Zona{
public:
    Montanha(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    Montanha* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    void efeito(int nDia) override;
    void extrai() override;
    float getMultiplier(Recursos* recursoExtraido) override;
	float getMultiplerDemissao(Trabalhadores* trabalhador) override;
};

class Deserto : public Zona{
public:
    Deserto(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    Deserto* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    float getMultiplier(Recursos* recursoExtraido) override;
};

class Pantano: public Zona{
public:
    Pantano(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    Pantano* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    void efeito(int nDia) override;
    float getMultiplier(Recursos* recursoExtraido) override;
};

class ZonaX : public Zona{
public:
    ZonaX(string nome, const array<Recursos*, 7> recursos,Ilha& ilha);
    ZonaX* cloneZona() override;
	void addRecursos(const array<Recursos*, 7> recursos) override;
    void extrai() override;
    float getMultiplier(Recursos* recursoExtraido) override;
};

#endif
