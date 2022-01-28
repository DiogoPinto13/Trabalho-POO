#ifndef TRABALHADORES_H
#define TRABALHADORES_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class Zona;

class Trabalhadores {

public:
    Trabalhadores(char simbolo, const int pagamento, float probEmbora);
	virtual ~Trabalhadores() = default;
    void setPagamento(const int montante);
    int getPagamento() const;
    void setZona(Zona* novaZona);
    float getProbIrEmbora() const;
    virtual void demissao(int ndia);
	virtual char getSimbolo() const;
	virtual Trabalhadores* cloneTrabalhador(int moveFlag, int dia);
    int getId() const;
    bool isDescanso() const;
    int getDiaContrato() const;
    bool podeMover() const;
    void blockMover();
    void setDiaContrato(int diaContrato);
    virtual void evento(int ndia);

protected:
    bool descanso;
	char simbolo;
    int diasDespedir;
    int diaContrato;
    int identificador;
    Zona* zona;
    static int id;
    bool mover;
private:
    int pagamento;
    float probIrEmbora;

};

class Mineiros : public Trabalhadores {

public:
    Mineiros(char simbolo);
	Trabalhadores* cloneTrabalhador(int moveFlag, int dia) override;
    void evento(int ndia) override;
    void demissao(int ndia) override;
};

class Lenhador : public Trabalhadores {

public:
    Lenhador(char simbolo);
	Trabalhadores* cloneTrabalhador(int moveFlag, int dia) override;
    void evento(int ndia) override;
    void demissao(int ndia) override;
};

class Operario : public Trabalhadores {

public:
    Operario(char simbolo);
	Trabalhadores* cloneTrabalhador(int moveFlag, int dia) override;
    void evento(int ndia) override;
    void demissao(int ndia) override;
};

#endif