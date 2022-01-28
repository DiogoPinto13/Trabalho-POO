#include "Ilha.h"
#include "Jogo.h"
#include <random>
#include <algorithm>
using namespace std;


Ilha::~Ilha() {
    limpaTab(tab, linhas);
}

Zona*** Ilha::criaTab(const int linhas, const int colunas, Jogo& jogo) {
	this->linhas = linhas;
	this->colunas = colunas;
    // "dsr","pas","flr","mnt","pnt","znZ"
    static array<Zona*,6> tipos{new Pastagem{"pas",jogo.getListarecursos(),*this},new Floresta{"flr",jogo.getListarecursos(),*this},new Montanha{"mtn",jogo.getListarecursos(),*this},new Deserto{"dsr",jogo.getListarecursos(),*this},new Pantano{"pnt",jogo.getListarecursos(),*this},new ZonaX{"pur",jogo.getListarecursos(),*this}};
    auto contador{tipos.begin()};
    Zona*** linha = new Zona ** [linhas] {};
    std::random_device rd;
    contador = tipos.begin();
    for (int i = 0; i < linhas; i++) {
        linha[i] = new Zona*[colunas]{};
        for(int j = 0; j < colunas; j++) {

            if(contador==tipos.end()) {
                contador = tipos.begin();
            }
            linha[i][j] = (*contador)->cloneZona();
            contador++;
        }
        std::shuffle(linha[i],linha[i]+colunas,std::mt19937{rd()});
        for(int k = 0; k < colunas; k++)
            linha[i][k]->setlocalizacao(i+1,k+1);
    }

    return linha;
}
void Ilha::limpaTab(Zona*** tab, const int linhas) {
    // apaga
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            delete tab[i][j];
        }
    }
    for (int i = 0; i < linhas; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

Zona* Ilha::getZona(const int linhas, const int colunas) {
    if(linhas > this->linhas  || linhas <= 0 || colunas > this->colunas || colunas <= 0)
        return nullptr;

	return tab[linhas-1][colunas-1];
}

int Ilha::getLinhas() const{
	return linhas;
}
int Ilha::getColunas() const{
	return colunas;
}

Ilha::Ilha(const Ilha& outro) {
    *this=outro;
}

Ilha& Ilha::operator=(const Ilha &outro){
    if(this==&outro){
        return *this;
    }

    linhas=outro.linhas;
    colunas=outro.colunas;

    Zona*** linha = new Zona ** [linhas] {};
    for (int i = 0; i < linhas; i++) {
        linha[i] = new Zona *[colunas]{};
        for (int j = 0; j < colunas; j++) {
            linha[i][j] = nullptr;
        }
    }

    for(int i{0};i<outro.linhas;i++){
        for(int j{0};j<outro.colunas;j++){
            linha[i][j] = outro.tab[i][j]->cloneZona(); // this work ?
            linha[i][j]->setlocalizacao(i+1,j+1);
            linha[i][j]->setIlha(*this);
        }

    }
    tab = linha;
    return *this;
}
