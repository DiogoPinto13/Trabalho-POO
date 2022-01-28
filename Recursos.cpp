#include "Recursos.h"

Recursos::Recursos(const string& abreviatura,const float novoValor) : quantidade(30) ,valor(novoValor),abreviatura(abreviatura){}


Ferro::Ferro(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor){}

Ferro *Ferro::cloneRecursos() {
    return new Ferro(*this);
}

BarraDeAco::BarraDeAco(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor) {}

BarraDeAco *BarraDeAco::cloneRecursos() {
    return new BarraDeAco(*this);
}

Carvao::Carvao(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor) {}

Carvao *Carvao::cloneRecursos() {
    return new Carvao(*this);
}

Madeira::Madeira(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor) {}

Madeira *Madeira::cloneRecursos() {
    return new Madeira(*this);
}

VigasDeMadeira::VigasDeMadeira(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor) {}

VigasDeMadeira *VigasDeMadeira::cloneRecursos() {
    return new VigasDeMadeira(*this);
}

Eletricidade::Eletricidade(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor) {}

Eletricidade *Eletricidade::cloneRecursos() {
    return new Eletricidade(*this);
}

Dinheiro::Dinheiro(const string& abreviatura,const float novoValor) : Recursos(abreviatura,novoValor){
    quantidade = 500;
}

Dinheiro *Dinheiro::cloneRecursos() {
    return new Dinheiro(*this);
}

// FUNCOES

float Recursos::getRecurso() const {
	return quantidade;
}

void Recursos::setRecurso(const float quant){
	quantidade = quant;
}

float Recursos::getValor() const {
    return valor;
}

string Recursos::getAbreviatura() const {
    return abreviatura;
}


