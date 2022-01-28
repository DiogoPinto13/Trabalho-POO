#include "Trabalhadores.h"
#include "Zona.h"

int Trabalhadores::id{0};
// #################################### CONSTRUTORES #######################################
Trabalhadores::Trabalhadores(char simbolo, const int pagamento, float probEmbora) : simbolo(simbolo), pagamento(pagamento), probIrEmbora(probEmbora),descanso(false)
                                                                                    ,mover(true){
}

Mineiros::Mineiros(char simbolo) : Trabalhadores(simbolo, 10,10) {

}

Lenhador::Lenhador(char simbolo) : Trabalhadores(simbolo, 20, 0) {

}

Operario::Operario(char simbolo) : Trabalhadores(simbolo, 15, 5) {

}
// #################################### FUNCOES #######################################

void Trabalhadores::setPagamento(const int montante) {
    pagamento = montante;
}
int Trabalhadores::getPagamento() const {
    return pagamento;
}

void Trabalhadores::setZona(Zona *novaZona) {
    zona = novaZona;
}




void Trabalhadores::demissao(int ndia) {
    if(ndia - diaContrato <= diasDespedir){
        random_device rd;
        uniform_int_distribution<> d(1, 100);
        mt19937 gen{rd()};
        if(d(gen) <= zona->getMultiplerDemissao(this)){
            zona->sendPurgatorio(this,ndia);
        }
    }
}
void Lenhador::demissao(int ndia) {
    if(ndia - diaContrato >= 2){
        random_device rd;
        uniform_int_distribution<> d(1, 100);
        mt19937 gen{rd()};
        if(d(gen) <= zona->getMultiplerDemissao(this)){
            zona->sendPurgatorio(this,ndia);
        }
    }
}
void Mineiros::demissao(int ndia) {
    if(ndia - diaContrato >= 2){
        random_device rd;
        uniform_int_distribution<> d(1, 100);
        mt19937 gen{rd()};
        if(d(gen) <= zona->getMultiplerDemissao(this)){
            zona->sendPurgatorio(this,ndia);
        }
    }
}
void Operario::demissao(int ndia) {
    if(ndia - diaContrato >= 10){
        random_device rd;
        uniform_int_distribution<> d(1, 100);
        mt19937 gen{rd()};
        if(d(gen) <= zona->getMultiplerDemissao(this)){
            zona->sendPurgatorio(this,ndia);
        }
    }
}





char Trabalhadores::getSimbolo() const{
	return simbolo;
}

Trabalhadores* Trabalhadores::cloneTrabalhador(int moveFlag, int dia) {
    identificador = ++id;
	return new Trabalhadores(*this);
}

float Trabalhadores::getProbIrEmbora() const {
    return probIrEmbora;
}

int Trabalhadores::getId() const{
    return identificador;
}

int Trabalhadores::getDiaContrato() const {
    return diaContrato;
}

void Trabalhadores::setDiaContrato(int diaContrato) {
    Trabalhadores::diaContrato = diaContrato;
}

void Trabalhadores::evento(int ndia) {
    mover=true;
    demissao(ndia);
}

bool Trabalhadores::isDescanso() const {
    return descanso;
}

bool Trabalhadores::podeMover() const {
    return mover;
}

void Trabalhadores::blockMover() {
    mover=false;
}

Trabalhadores* Mineiros::cloneTrabalhador(int moveFlag, int dia) {
    if(!moveFlag){
        identificador = ++id;
        setDiaContrato(dia);
    }
	return new Mineiros(*this);
}

Trabalhadores* Lenhador::cloneTrabalhador(int moveFlag, int dia) {
    if(!moveFlag){
        identificador = ++id;
        setDiaContrato(dia);
    }
	return new Lenhador(*this);
}

void Lenhador::evento(int ndia) {
    if((ndia-diaContrato) % 5 == 0){
        descanso = true;
    }
    mover=true;
    demissao(ndia);
}

void Mineiros::evento(int ndia) {
    mover=true;
    demissao(ndia);
}

void Operario::evento(int ndia) {
    mover=true;
    demissao(ndia);
}

Trabalhadores* Operario::cloneTrabalhador(int moveFlag, int dia) {
    if(!moveFlag){
        identificador = ++id;
        setDiaContrato(dia);
    }
	return new Operario(*this);
}


/*
char Mineiros::getSimbolo() const {
	return simbolo;
}

char Lenhador::getSimbolo() const {
	return simbolo;
}

char Operario::getSimbolo() const {
	return simbolo;
}
*/