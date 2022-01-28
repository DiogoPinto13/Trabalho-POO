#ifndef RECURSOS_H
#define RECURSOS_H
#include <iostream>
#include <string>
using namespace std;

class Recursos {

public:
	Recursos(const string& abreviatura, const float novoValor);
	float getRecurso() const;
	void setRecurso(const float quant);
    virtual Recursos* cloneRecursos()=0;
    float getValor() const;
    string getAbreviatura() const;
protected:
	float quantidade;
    float valor;
    string abreviatura;

private:

};

class Ferro : public Recursos {

public:
	Ferro(const string& abreviatura,const float novoValor);
    Ferro* cloneRecursos() override;

private:


};

class BarraDeAco : public Recursos {

public:
	BarraDeAco(const string& abreviatura,const float novoValor);
    BarraDeAco* cloneRecursos() override;

private:


};

class Carvao : public Recursos {

public:
	Carvao(const string& abreviatura,const float novoValor);
    Carvao* cloneRecursos() override;

private:


};

class Madeira : public Recursos {

public:
	Madeira(const string& abreviatura,const float novoValor);
    Madeira* cloneRecursos() override;

private:


};

class VigasDeMadeira : public Recursos {

public:
	VigasDeMadeira(const string& abreviatura,const float novoValor);
    VigasDeMadeira* cloneRecursos() override;

private:


};

class Eletricidade : public Recursos {

public:
	Eletricidade(const string& abreviatura,const float novoValor);
    Eletricidade* cloneRecursos() override;

private:


};

class Dinheiro : public Recursos {

public:
	Dinheiro(const string& abreviatura,const float novoValor);
    Dinheiro* cloneRecursos() override;

private:


};
#endif
